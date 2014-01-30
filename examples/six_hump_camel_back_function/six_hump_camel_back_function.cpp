/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   S I X   H U M P   C A M E L   B A C K   F U N C T I O N   C L A S S                                        */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#include <iostream>
#include <fstream>
#include <math.h>

#include "six_hump_camel_back_function.h"

namespace OpenNN
{

// GENERAL CONSTRUCTOR

SixHumpCamelBackFunction::SixHumpCamelBackFunction(NeuralNetwork* new_neural_network)
: PerformanceTerm(new_neural_network)
{
}


// DESTRUCTOR

SixHumpCamelBackFunction::~SixHumpCamelBackFunction(void)
{

}


// METHODS

// double calculate_performance(void) const method

double SixHumpCamelBackFunction::calculate_performance(void) const
{
   const Vector<double> argument = neural_network_pointer->get_independent_parameters_pointer()->get_parameters();
      
   const double performance 
   = pow(argument[0],2)*(4.0 - 2.1*pow(argument[0],2)+pow(argument[0],4.0)/3.0)
   + argument[0]*argument[1]+pow(argument[1],2)*(4*pow(argument[1],2)-4);

   return(performance);
}


// double calculate_performance(const Vector<double>&) const method

double SixHumpCamelBackFunction::calculate_performance(const Vector<double>& argument) const
{
   const double performance
   = pow(argument[0],2)*(4.0 - 2.1*pow(argument[0],2)+pow(argument[0],4.0)/3.0)
   + argument[0]*argument[1]+pow(argument[1],2)*(4*pow(argument[1],2)-4);

   return(performance);
}


// Vector<double> calculate_gradient(void) const method

Vector<double> SixHumpCamelBackFunction::calculate_gradient(void) const
{
   const unsigned int variables_number = 2;

   const Vector<double> argument = neural_network_pointer->get_independent_parameters_pointer()->get_parameters();

   Vector<double> gradient(variables_number);

   gradient[0] = 2*pow(argument[0],5) - 8.4*pow(argument[0],3) + 8*argument[0]+argument[1];
   gradient[1] = argument[0]-8*argument[1]+16*pow(argument[1],3);

   return(gradient);
}


// Matrix<double> calculate_Hessian(void) const method

Matrix<double> SixHumpCamelBackFunction::calculate_Hessian(void) const
{
   const unsigned int variables_number = 2;

   const Vector<double> argument = neural_network_pointer->get_independent_parameters_pointer()->get_parameters();

   Matrix<double> hessian(variables_number, variables_number);

   hessian[0][0] = 10* pow(argument[0],4) - 25.2 * pow(argument[0],2) + 8;
   hessian[0][1] = 1.0;
   hessian[1][0] = 1.0;
   hessian[1][1] = 48*pow(argument[1],2)-8;

   return(hessian);
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
