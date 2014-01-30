/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   D E   J O N G   F U N C T I O N   C L A S S                                                                */
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
#include <string>
#include <sstream>
#include <cmath>   

// Examples includes

#include "de_jong_function.h"

namespace OpenNN
{

// DEFAULT CONSTRUCTOR

DeJongFunction::DeJongFunction(void)       
: PerformanceTerm()
{
}


// GENERAL CONSTRUCTOR

DeJongFunction::DeJongFunction(NeuralNetwork* new_neural_network)       
: PerformanceTerm(new_neural_network)
{
}


// DESTRUCTOR

DeJongFunction::~DeJongFunction(void)
{

}


// METHODS

// double calculate_performance(void) const method

double DeJongFunction::calculate_performance(void) const
{
   IndependentParameters* independent_parameters_pointer = neural_network_pointer->get_independent_parameters_pointer();

   const Vector<double> argument = independent_parameters_pointer->get_parameters();

   return(argument.dot(argument));
}


// double calculate_performance(const Vector<double>&) const method

double DeJongFunction::calculate_performance(const Vector<double>& parameters) const
{
   NeuralNetwork neural_network_copy(*neural_network_pointer);

   neural_network_copy.set_parameters(parameters);

   DeJongFunction de_Jong_function_copy(*this);

   de_Jong_function_copy.set_neural_network_pointer(&neural_network_copy);

   return(de_Jong_function_copy.calculate_performance());
}


// Vector<double> calculate_gradient(void) const method

Vector<double> DeJongFunction::calculate_gradient(void) const
{
   IndependentParameters* independent_parameters_pointer = neural_network_pointer->get_independent_parameters_pointer();

   const Vector<double> argument = independent_parameters_pointer->get_parameters();

   return(argument*2.0);
}


// Matrix<double> calculate_Hessian(void) const method

Matrix<double> DeJongFunction::calculate_Hessian(void) const
{
   IndependentParameters* independent_parameters_pointer = neural_network_pointer->get_independent_parameters_pointer();

   const unsigned int parameters_number = independent_parameters_pointer->get_parameters_number();

   Matrix<double> Hessian(parameters_number, parameters_number, 0.0);

   Hessian.set_diagonal(2.0);

   return(Hessian);
}


// Matrix<double> calculate_inverse_Hessian(void) const method

Matrix<double> DeJongFunction::calculate_inverse_Hessian(void) const
{
   IndependentParameters* independent_parameters_pointer = neural_network_pointer->get_independent_parameters_pointer();

   const unsigned int parameters_number = independent_parameters_pointer->get_parameters_number();

   Matrix<double> inverse_Hessian(parameters_number, parameters_number, 0.0);

   inverse_Hessian.set_diagonal(0.5);

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
