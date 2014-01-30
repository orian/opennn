/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   A I R C R A F T   L A N D I N G   S O L U T I O N   E R R O R   C L A S S                                  */
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
#include <fstream>     
#include <cstdlib>     
#include <cmath>     

// OpenNN includes

#include "aircraft_landing_solution_error.h"     

namespace OpenNN
{

// DEFAULT CONSTRUCTOR

AircraftLandingSolutionError::AircraftLandingSolutionError() : SolutionsError()
{
}
 

// NEURAL NETWORK CONSTRUCTOR

AircraftLandingSolutionError::AircraftLandingSolutionError(NeuralNetwork* new_neural_network_pointer)
: SolutionsError(new_neural_network_pointer)
{
}


// MATHEMATICAL MODEL CONSTRUCTOR

AircraftLandingSolutionError::AircraftLandingSolutionError(MathematicalModel* new_mathematical_model_pointer)
: SolutionsError(new_mathematical_model_pointer)
{
}


// NEURAL NETWORK AND MATHEMATICAL MODEL  CONSTRUCTOR

AircraftLandingSolutionError::AircraftLandingSolutionError(NeuralNetwork* new_neural_network_pointer, MathematicalModel* new_mathematical_model_pointer)
 : SolutionsError(new_neural_network_pointer, new_mathematical_model_pointer)
{
}


// XML CONSTRUCTOR

AircraftLandingSolutionError::AircraftLandingSolutionError(const tinyxml2::XMLDocument& solutions_error_element)
 : SolutionsError(solutions_error_element)
{
}


// COPY CONSTRUCTOR

AircraftLandingSolutionError::AircraftLandingSolutionError(const AircraftLandingSolutionError& other_aircraft_landing_solutions_error)
 : SolutionsError(other_aircraft_landing_solutions_error)
{
}



// DESTRUCTOR

AircraftLandingSolutionError::~AircraftLandingSolutionError(void) 
{
}


// METHODS

// void set(const AircraftLandingSolutionError&) method

void AircraftLandingSolutionError::set(const AircraftLandingSolutionError& other_solutions_error)
{
   neural_network_pointer = other_solutions_error.neural_network_pointer;

   data_set_pointer = other_solutions_error.data_set_pointer;

   mathematical_model_pointer = other_solutions_error.mathematical_model_pointer;

   if(other_solutions_error.numerical_differentiation_pointer)
   {
      numerical_differentiation_pointer = new NumericalDifferentiation(*other_solutions_error.numerical_differentiation_pointer);
   }

   display = other_solutions_error.display;  
   
   solutions_errors_weights = other_solutions_error.solutions_errors_weights;
}


// Matrix<double> calculate_target_dependent_variables(const Matrix<double>&) const method

Matrix<double> AircraftLandingSolutionError::calculate_target_dependent_variables(const Matrix<double>& independent_variables) const
{
   #ifdef _DEBUG 

   check();

   #endif

   const unsigned int rows_number = independent_variables.get_rows_number();

   double time;

   Matrix<double> target_dependent_variables(rows_number, 4, 0.0);

   for(unsigned int i = 0; i < rows_number; i++)
   {
      time = independent_variables[i][0];

      if(time <= 15.0)
      {
         target_dependent_variables[i][3] = 30.0*exp(-time/5.0);
      }
      else
      {
         target_dependent_variables[i][3] = 6.0 - 0.3*time;   
      }
   }

   return(target_dependent_variables);
}


// double calculate_performance(void) const method

double AircraftLandingSolutionError::calculate_performance(void) const
{
   // Control sentence

   #ifdef _DEBUG 

   check();

   #endif

   switch(solutions_error_method)
   {
      case SolutionsErrorSum:
      {
         return(calculate_solutions_error_sum());
      }            
      break;

      case SolutionsErrorIntegral:
      {
         return(calculate_solutions_error_integral());
      }
      break;

      default:
      {
         std::ostringstream buffer;

         buffer << "OpenNN Exception: AircraftLandingSolutionError class\n"
                << "double calculate_performance(void) const method.\n"               
                << "Unknown solutions error method.\n";

	     throw std::logic_error(buffer.str());
      }
      break;
   }
}


// double calculate_performance(const Vector<double>&) const method

double AircraftLandingSolutionError::calculate_performance(const Vector<double>& parameters) const   
{
   // Control sentence

   #ifdef _DEBUG 

   check();

   #endif

   NeuralNetwork neural_network_copy(*neural_network_pointer);

   neural_network_copy.set_parameters(parameters);

   AircraftLandingSolutionError solutions_error_copy(*this);

   solutions_error_copy.set_neural_network_pointer(&neural_network_copy);
   solutions_error_copy.set_mathematical_model_pointer(mathematical_model_pointer);

   return(solutions_error_copy.calculate_performance());
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
