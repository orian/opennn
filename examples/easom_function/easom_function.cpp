/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   E A S O M   F U N C T I O N   C L A S S                                                                    */
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

#include "easom_function.h"


namespace OpenNN
{

// GENERAL CONSTRUCTOR

EasomFunction::EasomFunction(NeuralNetwork* new_neural_network_pointer)       
: PerformanceTerm(new_neural_network_pointer)
{
}


// DESTRUCTOR

EasomFunction::~EasomFunction(void)
{
}


// METHODS

// double calculate_performance(void) const method

double EasomFunction::calculate_performance(void) const
{
   Vector<double> argument = neural_network_pointer->get_independent_parameters_pointer()->get_parameters();
         
   double a = exp(-(pow((argument[0]- PI), 2) + pow((argument[1] - PI), 2))); 
    
   double objective = -cos(argument[0])*cos(argument[1])*a;
    
   return(objective);
}


// double calculate_performance(const Vector<double>&) const method

double EasomFunction::calculate_performance(const Vector<double>& parameters) const
{
   const double a = exp(-(pow((parameters[0]- PI), 2) + pow((parameters[1] - PI), 2)));

   const double performance = -cos(parameters[0])*cos(parameters[1])*a;

   return(performance);
}


// Vector<double> calculate_gradient(void) const method

Vector<double> EasomFunction::calculate_gradient(void) const
{
   const int variables_number = 2;

   Vector<double> objective_gradient(variables_number);

   Vector<double> argument = neural_network_pointer->get_independent_parameters_pointer()->get_parameters();
   
   double a = exp(-(pow((argument[0]-PI), 2) + pow((argument[1]-PI), 2)));
   
   objective_gradient[0] = a*(sin(argument[0])*cos(argument[1])+2*cos(argument[0])*cos(argument[1])*(argument[0]-PI));
   objective_gradient[1] = a*(cos(argument[0])*sin(argument[1])+2*cos(argument[0])*cos(argument[1])*(argument[1]-PI));
   
   return(objective_gradient);
}


// Matrix<double> calculate_Hessian(void) const method

Matrix<double> EasomFunction::calculate_Hessian(void) const
{ 
   const int variables_number = 2;

   Matrix<double> Hessian(variables_number, variables_number);

   const double pi = 3.1415927;

   Vector<double> argument = neural_network_pointer->get_independent_parameters_pointer()->get_parameters();

   double a = exp(-(pow((argument[0]-pi), 2) + pow((argument[1]-pi), 2)));
   double b = cos(argument[0])*cos(argument[1]);
   double c = sin(argument[0])*cos(argument[1]);
   double d = sin(argument[0])*sin(argument[1]);
   double e = cos(argument[0])*sin(argument[1]);
   
   Hessian[0][0] = a*(3.0*b - 4.0*c*(argument[0] - pi) - 4.0*b*pow((argument[0]-pi), 2));
   Hessian[0][1] = a*(-d    - 2.0*c*(argument[1] - pi) - 2.0*e*(argument[0]-pi) - 4.0*b*(argument[0]-pi)*(argument[1]-pi));
   Hessian[1][0] = a*(-d    - 2.0*c*(argument[1] - pi) - 2.0*e*(argument[0]-pi) - 4.0*b*(argument[0]-pi)*(argument[1]-pi));
   Hessian[1][1] = a*(3.0*b - 4.0*e*(argument[1] - pi) - 4.0*b*pow((argument[1]-pi), 2));

   return(Hessian);
}


// Matrix<double> calculate_inverse_Hessian(void) const method

Matrix<double> EasomFunction::calculate_inverse_Hessian(void) const
{
   const int variables_number = 2;

   Matrix<double> inverse_Hessian(variables_number, variables_number);
    
   Vector<double> argument = neural_network_pointer->get_independent_parameters_pointer()->get_parameters();

   Matrix<double> Hessian = calculate_Hessian();
   
   double HessianDeterminant = Hessian[0][0]*Hessian[1][1] - Hessian[0][1]*Hessian[1][0];
 
   inverse_Hessian[0][0] = Hessian[1][1]/HessianDeterminant;
   inverse_Hessian[0][1] = -Hessian[0][1]/HessianDeterminant;
   inverse_Hessian[1][0] = -Hessian[1][0]/HessianDeterminant;
   inverse_Hessian[1][1] = Hessian[0][0]/HessianDeterminant;
 
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
