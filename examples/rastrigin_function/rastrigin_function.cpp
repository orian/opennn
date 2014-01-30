/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   R A S T R I G I N   F U N C T I O N   C L A S S                                                            */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// System includes

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>   

// Examples includes

#include "rastrigin_function.h"

namespace OpenNN
{

// GENERAL CONSTRUCTOR

RastriginFunction::RastriginFunction(NeuralNetwork* new_neural_network_pointer)       
: PerformanceTerm(new_neural_network_pointer)
{
}


// DESTRUCTOR

RastriginFunction::~RastriginFunction(void)
{
}


// METHODS

// double calculate_performance(void) const method

double RastriginFunction::calculate_performance(void) const
{
   const double pi = 3.1415927;

   const unsigned int variables_number = neural_network_pointer->count_parameters_number();
   const Vector<double> argument = neural_network_pointer->arrange_parameters();

   double objective = 10.0*variables_number;

   for(unsigned int i = 0; i < variables_number; i++)
   {
      objective += pow(argument[i], 2) - 10.0*cos(2.0*pi*argument[i]);
   }

   return(objective);
}


// Vector<double> calculate_gradient(void) const method

Vector<double> RastriginFunction::calculate_gradient(void) const
{
   const double pi = 3.1415927;

   const unsigned int variables_number = neural_network_pointer->count_parameters_number();
   const Vector<double> argument = neural_network_pointer->arrange_parameters();

   Vector<double> gradient(variables_number);

   for(unsigned int i = 0; i < variables_number; i++)
   {
      gradient[i] = 2.0*argument[i] + 10.0*sin(2.0*pi*argument[i])*2.0*pi;
   }

   return(gradient);
}


// Matrix<double> calculate_Hessian(void) const method

Matrix<double> RastriginFunction::calculate_Hessian(void) const
{
   const double pi = 3.1415927;

   const unsigned int variables_number = neural_network_pointer->count_parameters_number();
   const Vector<double> argument = neural_network_pointer->arrange_parameters();

   Matrix<double> Hessian(variables_number, variables_number, 0.0);

   for(unsigned int i = 0; i < variables_number; i++)
   {
      Hessian[i][i] = 2.0 + 10.0*cos(2.0*pi*argument[i])*4.0*pow(pi,2);
   }

   return(Hessian);
}


// Matrix<double> calculate_evaluation_inverse_Hessian(void) const method

Matrix<double> RastriginFunction::calculate_inverse_Hessian(void) const
{
   const double pi = 3.1415927;

   const unsigned int variables_number = neural_network_pointer->count_parameters_number();
   const Vector<double> argument = neural_network_pointer->arrange_parameters();

   Matrix<double> inverse_Hessian(variables_number, variables_number, 0.0);

   for(unsigned int i = 0; i < variables_number; i++)
   {
      inverse_Hessian[i][i] = 1.0/(2.0 + 10.0*cos(2.0*pi*argument[i])*4.0*pow(pi,2));
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
