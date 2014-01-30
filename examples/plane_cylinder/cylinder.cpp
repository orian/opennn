/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   C Y L I N D E R   C L A S S                                                                                */
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
#include <cmath>

// OpenNN includes

#include "cylinder.h"


namespace OpenNN
{

// GENERAL CONSTRUCTOR

Cylinder::Cylinder(void) : MathematicalModel()
{
   set_default();
}


// DESTRUCTOR

Cylinder::~Cylinder(void)
{

}


// METHODS

// void set_default(void) method

void Cylinder::set_default(void)
{
   independent_variables_number = 2;
   dependent_variables_number = 1;

   display = true;

}


// Matrix<double> calculate_solutions(const NeuralNetwork&) const method

Matrix<double> Cylinder::calculate_solutions(const NeuralNetwork& neural_network) const
{
   IndependentParameters* independent_parameters_pointer = neural_network.get_independent_parameters_pointer();

   const Vector<double> argument = independent_parameters_pointer->get_parameters();

   double x = argument[0];
   double y = argument[1];

   Matrix<double> solutions(1, 1);

   if(pow(x,2) + pow(y,2) <= 1.0)
   {
      solutions[0][0] = 0.0;
   }
   else
   {
      solutions[0][0] = pow(x,2) + pow(y,2) - 1.0;
   } 
   
   return(solutions);       
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
