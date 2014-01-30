/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   C A R   N E U R O C O M P U T I N G   C L A S S                                                            */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// System includees

#include <iostream>     
#include <fstream>     
#include <math.h>     

// Examples includes

#include "car_neurocomputing.h"


namespace OpenNN
{

// GENERAL CONSTRUCTOR

CarNeurocomputing::CarNeurocomputing(void) : OrdinaryDifferentialEquations()
{
   set_default();
}


// DESTRUCTOR

CarNeurocomputing::~CarNeurocomputing(void)
{

}


// METHODS


// void set_default(void) method

void CarNeurocomputing::set_default(void)
{
   independent_variables_number = 1;
   dependent_variables_number = 1;

   solution_method = RungeKuttaFehlberg;

   points_number = 1001;

   tolerance = 1.0e-6;

   initial_size = (unsigned int)1.0e3;
   warning_size = (unsigned int)1.0e6;
   error_size = (unsigned int)1.0e9;

   initial_independent_variable = 0.0;
   final_independent_variable = 1.0;

   initial_dependent_variables.set(1, 0.0);

   display = true;
}


// Vector<double> calculate_dependent_variables_dots(const NeuralNetwork&, const Vector<double>&) const method

Vector<double> CarNeurocomputing::calculate_dependent_variables_dots(const NeuralNetwork& neural_network, const Vector<double>& variables) const
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   std::ostringstream buffer;

   const IndependentParameters* independent_parameters_pointer = neural_network.get_independent_parameters_pointer();

   if(!independent_parameters_pointer)
   {
      buffer << "OpenNN Error CarNeurocomputing class.\n"
             << "Vector<double> calculate_dependent_variables_dots(const NeuralNetwork&, const Vector<double>&) const method.\n"
             << "Pointer to independent parameters in neural network is NULL.\n";

      throw std::logic_error(buffer.str());

   }

   const unsigned int independent_parameters_number = independent_parameters_pointer->count_parameters_number();

   if(independent_parameters_number != 1)
   {
      buffer << "OpenNN Error CarNeurocomputing class.\n"
             << "Vector<double> calculate_dependent_variables_dots(const NeuralNetwork&, const Vector<double>&) const method.\n"
             << "Number of independent parameters in neural network must be one.\n";

      throw std::logic_error(buffer.str());
   }

   const unsigned int variables_size = variables.size();

   if(variables_size != 2)
   {
      buffer << "OpenNN Error CarNeurocomputing class.\n"
             << "Vector<double> calculate_dependent_variables_dots(const NeuralNetwork&, const Vector<double>&) const method.\n"
             << "Size of variables must be 2.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   const double time = variables[0];
   const double velocity = variables[1];

   const Vector<double> inputs(1, time);

   const Vector<double> outputs = neural_network.calculate_outputs(inputs);

   const double acceleration = outputs[0];

   Vector<double> dependent_variables_dots(2);
   dependent_variables_dots[0] = velocity;
   dependent_variables_dots[1] = acceleration;

   return(dependent_variables_dots);
}


// Vector<double> calculate_final_solutions(const NeuralNetwork&) const method

Vector<double> CarNeurocomputing::calculate_final_solutions(const NeuralNetwork& neural_network) const
{
   // Control sentence (if debug)

   #ifdef _DEBUG 

   std::ostringstream buffer;

   const IndependentParameters* independent_parameters_pointer = neural_network.get_independent_parameters_pointer();

   if(!independent_parameters_pointer)
   {
      buffer << "OpenNN Error CarNeurocomputing class.\n"
             << "Vector<double> calculate_final_solutions(const NeuralNetwork&) const method.\n"
             << "Pointer to independent parameters in neural network is NULL.\n";

      throw std::logic_error(buffer.str());
   }

   const unsigned independent_parameters_number = independent_parameters_pointer->count_parameters_number();

   if(independent_parameters_number != 1)
   {
      buffer << "OpenNN Error CarNeurocomputing class.\n"
             << "Vector<double> calculate_final_solutions(const NeuralNetwork&) const method.\n"
             << "Number of independent parameters in neural network must be one.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   CarNeurocomputing car_neurocomputing_copy(*this);

   car_neurocomputing_copy.set_final_independent_variable(neural_network.get_independent_parameters_pointer()->get_parameter(0));

   switch(solution_method)
   {
      case OrdinaryDifferentialEquations::RungeKutta:
      {
         return(car_neurocomputing_copy.calculate_Runge_Kutta_final_solution(neural_network));
      }            
      break;

      case OrdinaryDifferentialEquations::RungeKuttaFehlberg:
      {
         return(car_neurocomputing_copy.calculate_Runge_Kutta_Fehlberg_final_solution(neural_network));
      }
      break;

      default:
      {
         std::ostringstream buffer;

         buffer << "OpenNN Exception: CarNeurocomputing class\n"
                << "Vector<double> calculate_final_solutions(const NeuralNetwork&) const method.\n"               
                << "Unknown solution method.\n";

         throw std::logic_error(buffer.str());

      }
      break;
   }

   Vector<double> final_solutions;
   return(final_solutions);
}

}


// OpenNN: Open Neural Networks Library.
// Copyright (C) 2005-2014 Roberto Lopez 
//
// This library is free software; you can redistribute it and/or
// modify it under the s of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

