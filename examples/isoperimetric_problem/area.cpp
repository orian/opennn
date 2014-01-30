/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   A R E A   C L A S S                                                                                        */
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


// Examples includes

#include "area.h"     


namespace OpenNN
{

// GENERAL CONSTRUCTOR

Area::Area() : OrdinaryDifferentialEquations()
{
}


// DESTRUCTOR

Area::~Area(void) 
{
}


// METHODS


// Vector<double> calculate_dependent_variables_dots(const NeuralNetwork&, const Vector<double>&) const method

Vector<double> Area::calculate_dependent_variables_dots(const NeuralNetwork& neural_network, const Vector<double>& variables) const
{
   const double t = variables[0];
   
   // Set inputs 

   const Vector<double> inputs(1, t);

   // Get outputs

   const Vector<double> outputs = neural_network.calculate_outputs(inputs);

   const double x = outputs[0];
   const double y = outputs[1];

   // Get Jacobian
   
   const Matrix<double> Jacobian = neural_network.calculate_Jacobian(inputs);

   const double dxdt = Jacobian[0][0];
   const double dydt = Jacobian[0][1];

   const Vector<double> dependent_variables_dots(1, x*dydt - y*dxdt);

   return(dependent_variables_dots);
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
