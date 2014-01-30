/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   S C H W E F E L   F U N C T I O N   C L A S S                                                              */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>   

#include "schwefel_function.h"

namespace OpenNN
{

// GENERAL CONSTRUCTOR

SchwefelFunction::SchwefelFunction(NeuralNetwork* new_neural_network)       
: PerformanceTerm(new_neural_network)
{
}


// DESTRUCTOR

SchwefelFunction::~SchwefelFunction(void)
{

}


// METHODS


// double calculate_performance(void) const method

double SchwefelFunction::calculate_performance(void) const
{
   const unsigned variables_number = neural_network_pointer->get_independent_parameters_pointer()->get_parameters_number();
   const Vector<double> argument = neural_network_pointer->get_independent_parameters_pointer()->get_parameters();

   double objective = 0.0;

   for(unsigned int i = 0; i < variables_number; i++)
   {
      objective += -argument[i]*sin(sqrt(fabs(argument[i])));
   }

   return(objective);
}


// double calculate_performance(const Vector<double>&) const method

double SchwefelFunction::calculate_performance(const Vector<double>& parameters) const
{
   NeuralNetwork neural_network_copy(*neural_network_pointer);

   neural_network_copy.set_parameters(parameters);

   SchwefelFunction Schwefel_function_copy(*this);

   Schwefel_function_copy.set_neural_network_pointer(&neural_network_copy);

   return(Schwefel_function_copy.calculate_performance());
}


// Vector<double> calculate_gradient(void) const method

Vector<double> SchwefelFunction::calculate_gradient(void) const
{
   const unsigned int variables_number = neural_network_pointer->get_independent_parameters_pointer()->get_parameters_number();
   const Vector<double> argument = neural_network_pointer->get_independent_parameters_pointer()->get_parameters();

   Vector<double> objective_gradient(variables_number);

   for(unsigned int i = 0; i < variables_number; i++)
   {
      objective_gradient[i] = -sin(sqrt(fabs(argument[i])))-0.5*(sqrt(fabs(argument[i])))*cos(sqrt(fabs(argument[i])));
   }
   
   return(objective_gradient);
}


// Matrix<double> calculate_Hessian(void) const method

Matrix<double> SchwefelFunction::calculate_Hessian(void) const
{
   const unsigned int variables_number = neural_network_pointer->get_independent_parameters_pointer()->get_parameters_number();
   const Vector<double> argument = neural_network_pointer->get_independent_parameters_pointer()->get_parameters();

   Matrix<double> hessian(variables_number, variables_number);


   for(unsigned int i = 0; i < variables_number; i++)
   {
      for(unsigned int j = 0; j < variables_number; j++)
      {
         if(i == j)
         {
            hessian[i][j] = -3*cos(sqrt(fabs(argument[i])))/(4*(sqrt(fabs(argument[i])))) 
                          + 0.25*sin(sqrt(fabs(argument[i])));
         }
         else
         {
            hessian[i][j] = 0.0;
         }
      }
   }

   return(hessian);
}


// Matrix<double> calculate_inverse_Hessian(void) const method

Matrix<double> SchwefelFunction::calculate_inverse_Hessian(void) const
{
   const unsigned int variables_number = neural_network_pointer->get_independent_parameters_pointer()->get_parameters_number();
   Vector<double> argument = neural_network_pointer->get_independent_parameters_pointer()->get_parameters();

   Matrix<double> inverse_Hessian(variables_number, variables_number);

   for(unsigned int i = 0; i < variables_number; i++)
   {
      for(unsigned int j = 0; j < variables_number; j++)
      {
         if(i == j)
         {
            inverse_Hessian[i][j] 
            = 1.0/(-3*cos(sqrt(fabs(argument[i])))/(4*(sqrt(fabs(argument[i]))))
            + 0.25*sin(sqrt(fabs(argument[i]))));
         }
         else
         {
            inverse_Hessian[i][j] = 0.0;
         }
      }
   }

   return(inverse_Hessian);
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
