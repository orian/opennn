/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   D E S C E N T   T I M E    C L A S S                                                                       */
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

// Examples includes

#include "descent_time.h"
 
namespace OpenNN
{

// GENERAL CONSTRUCTOR

DescentTime::DescentTime() : OrdinaryDifferentialEquations()
{
   set_default();
}


// DESTRUCTOR

DescentTime::~DescentTime(void) 
{
}


// METHODS

// void set_default(void) methode

void DescentTime::set_default(void)
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

Vector<double> DescentTime::calculate_dependent_variables_dots(const NeuralNetwork& neural_network, const Vector<double>& variables) const
{
   const double x = variables[0];

   const Vector<double> inputs(1, x);

   const Vector<double> outputs = neural_network.calculate_outputs(inputs);

   double y = outputs[0];

   const Matrix<double> Jacobian = neural_network.calculate_Jacobian(inputs);

   double dydt = Jacobian[0][0];

   // This problem is very sensitive to this parameter!

   const double small = 1.0e-3;

   if(y >= 0.0)
   {
      y = small;
      dydt = 0.0;
   }

   // Get descent time integrand

   const double g = 9.81;

   const double numerator = 1.0 + pow(dydt,2);
   const double denominator = -y;

   const Vector<double> dependent_parameters_dots(1, sqrt(numerator/denominator)/sqrt(2.0*g));

   return(dependent_parameters_dots);
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
