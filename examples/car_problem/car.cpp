/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   C A R   P R O B L E M   C L A S S                                                                          */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// System includes

#include <string>
#include <sstream>
#include <iostream>     
#include <cstdlib>     
#include <fstream>     
#include <cmath>     

// OpenNN includes

#include "../../source/opennn.h"

// Examples includes

#include "car.h"

namespace OpenNN
{

// GENERAL CONSTRUCTOR

Car::Car() : OrdinaryDifferentialEquations()
{
   set_default();
}


// COPY CONSTRUCTOR

Car::Car(const Car& other_car) : OrdinaryDifferentialEquations()
{
   set(other_car);
}


// DESTRUCTOR

Car::~Car(void)
{
}


// METHODS

// void set_default(void) method

void Car::set_default(void)
{
   independent_variables_number = 1;
   dependent_variables_number = 2;   

   solution_method = RungeKuttaFehlberg;

   points_number = 1001;

   tolerance = 1.0e-6;

   initial_size = (unsigned int)1.0e3;
   warning_size = (unsigned int)1.0e6;
   error_size = (unsigned int)1.0e9;

   initial_independent_variable = 0;
   final_independent_variable = 1;

   initial_dependent_variables.set(2, 0.0);

   display = true;
}


// Vector<double> calculate_dependent_variables_dots(const NeuralNetwork&, const Vector<double>&) const method

Vector<double> Car::calculate_dependent_variables_dots(const NeuralNetwork& neural_network, const Vector<double>& variables) const
{
   const double time = variables[0];
//   const double position = variables[1];
   const double velocity = variables[2];

   const Vector<double> inputs(1, time);

   const Vector<double> outputs = neural_network.calculate_outputs(inputs);

   const double acceleration = outputs[0];
   const double deceleration = outputs[1];

   const double position_dot = velocity;
   const double velocity_dot = acceleration + deceleration;

   Vector<double> dependent_variables_dots(dependent_variables_number, 0.0);

   dependent_variables_dots[0] = position_dot;
   dependent_variables_dots[1] = velocity_dot;

   return(dependent_variables_dots);
}



// Vector<double> calculate_final_solutions(const NeuralNetwork& neural_network) const method

Vector<double> Car::calculate_final_solutions(const NeuralNetwork& neural_network) const
{ 
   Car car_copy(*this);

   car_copy.set_final_independent_variable(neural_network.get_independent_parameters_pointer()->get_parameter(0));

   switch(solution_method)
   {
      case RungeKutta:
      {
         return(car_copy.calculate_Runge_Kutta_final_solution(neural_network));
      }            
      break;

      case RungeKuttaFehlberg:
      {
         return(car_copy.calculate_Runge_Kutta_Fehlberg_final_solution(neural_network));
      }
      break;

      default:
      {
         std::ostringstream buffer;

         buffer << "OpenNN Exception: Car class\n"
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
