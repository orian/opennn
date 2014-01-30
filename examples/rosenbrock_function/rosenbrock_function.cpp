/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   R O S E N B R O C K   F U N C T I O N   C L A S S                                                          */
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
#include <cmath>   

// Examples includes

#include "rosenbrock_function.h"

namespace OpenNN
{

// GENERAL CONSTRUCTOR

RosenbrockFunction::RosenbrockFunction(NeuralNetwork* new_neural_network)       
: PerformanceTerm(new_neural_network)
{
   construct_numerical_differentiation();
}


// COPY CONSTRUCTOR

RosenbrockFunction::RosenbrockFunction(const RosenbrockFunction& new_Rosenbrock_function)       
: PerformanceTerm(new_Rosenbrock_function)
{
}


// DESTRUCTOR

RosenbrockFunction::~RosenbrockFunction(void)
{

}


// METHODS

// double calculate_performance(void) const method

double RosenbrockFunction::calculate_performance(void) const
{
   const unsigned int variables_number = neural_network_pointer->count_parameters_number();

   const Vector<double> argument = neural_network_pointer->arrange_parameters();

   // Calculate evaluation

   double evaluation = 0.0;

   for(unsigned int i = 0; i < variables_number-1; i++)
   {
      evaluation += 100.0*pow(argument[i+1] - pow(argument[i],2), 2) + pow(1.0 - argument[i], 2);
   }

   return(evaluation);
}


// double calculate_performance(const Vector<double>&) const method

double RosenbrockFunction::calculate_performance(const Vector<double>& parameters) const
{
   const unsigned int parameters_number = neural_network_pointer->count_parameters_number();
   
   // Calculate evaluation

   double evaluation = 0.0;

   for(unsigned int i = 0; i < parameters_number-1; i++)
   {
      evaluation += 100.0*pow(parameters[i+1] - pow(parameters[i],2), 2) + pow(1.0 - parameters[i], 2);
   }

   return(evaluation);
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
