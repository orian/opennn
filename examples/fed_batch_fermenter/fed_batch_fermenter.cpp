/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   F E D   B A T C H   F E R M E N T E R   C L A S S                                                          */
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

#include "fed_batch_fermenter.h"


namespace OpenNN
{

// GENERAL CONSTRUCTOR

FedBatchFermenter::FedBatchFermenter(void) : OrdinaryDifferentialEquations()
{
   set_default();
}


// DESTRUCTOR

FedBatchFermenter::~FedBatchFermenter(void)
{

}


// METHODS

// void set_default(void) method

void FedBatchFermenter::set_default(void)
{
   independent_variables_number = 1;
   dependent_variables_number = 4;

   initial_independent_variable = 0.0;
   final_independent_variable = 54.0;

   initial_dependent_variables.set(4);

   initial_dependent_variables[0] = 1.0;
   initial_dependent_variables[1] = 150.0;
   initial_dependent_variables[2] = 0.0;
   initial_dependent_variables[3] = 10.0;

   yield_coefficient = 0.1; // no units
   feed_substrate_concentration = 150.0; // g/l

   kinetic_constant_mu0 =0.408; // 1/h
   kinetic_constant_eta0 = 1.0; // 1/h
   kinetic_constant_kp = 16.0; // g/l
   kinetic_constant_kp_dash = 71.5; // g/l
   kinetic_constant_ks = 0.22; // g/l
   kinetic_constant_ks_dash = 0.44; // g/l

   display = true;
}


// double calculate_specific_growth_rate(const double&, const double&) const method

double FedBatchFermenter::calculate_specific_growth_rate(const double& product_concentration, const double& substrate_concentration) const
{
   const double specific_growth_rate = (kinetic_constant_mu0/(1.0+product_concentration/kinetic_constant_kp))
   *(substrate_concentration/(kinetic_constant_ks+substrate_concentration));

   return(specific_growth_rate);
}


// double calculate_specific_productivity(const double&, const double&) const method

double FedBatchFermenter
::calculate_specific_productivity(const double& product_concentration, const double& substrate_concentration) const
{
   const double specific_productivity = (kinetic_constant_eta0/(1.0+product_concentration/kinetic_constant_kp_dash))
   *(substrate_concentration/(kinetic_constant_ks_dash+substrate_concentration));

   return(specific_productivity);
}


// void calculate_cell_mass_concentration_dot(double, double, double, double, double) const method

double FedBatchFermenter::calculate_cell_mass_concentration_dot(const NeuralNetwork& neural_network, const double& time, 
const double& cell_mass_concentration, const double& substrate_concentration, const double& product_concentration, const double& broth_volume) const
{
   // Obtain control 

   const Vector<double> inputs(1, time);

   const Vector<double> outputs = neural_network.calculate_outputs(inputs);

   const double feed_rate = outputs[0];

   // Calculate cell mass concentration derivative

   const double specific_growth_rate = calculate_specific_growth_rate(product_concentration, substrate_concentration);

   const double cell_mass_concentration_dot = 
   specific_growth_rate*cell_mass_concentration - feed_rate*(cell_mass_concentration/broth_volume);
    
   return(cell_mass_concentration_dot);
}


// void calculate_substrate_concentration_dot(const NeuralNetwork& neural_network, const double&, const double&, const double&, const double&, const double&) const method

double FedBatchFermenter::calculate_substrate_concentration_dot(const NeuralNetwork& neural_network, const double& time, 
const double& cell_mass_concentration, const double& substrate_concentration, const double& product_concentration, const double& broth_volume) const
{

   // Obtain control 

   const Vector<double> inputs(1, time);

   const Vector<double> outputs = neural_network.calculate_outputs(inputs);

   const double feed_rate = outputs[0];

   // Calculate substrate concentration derivative

   const double specific_growth_rate = calculate_specific_growth_rate(product_concentration, substrate_concentration);

   double substrate_concentration_dot = 
   -1.0*specific_growth_rate*cell_mass_concentration/yield_coefficient 
   + feed_rate*(feed_substrate_concentration-substrate_concentration)/broth_volume;

   return(substrate_concentration_dot);
}


// void calculate_product_concentration_dot(const NeuralNetwork&, const double&, const double&, const double&, const double&, const double&) const method

double FedBatchFermenter::calculate_product_concentration_dot(const NeuralNetwork& neural_network, const double& time, 
const double& cell_mass_concentration, const double& substrate_concentration, const double& product_concentration, const double& broth_volume) const
{
   // Obtain control

   const Vector<double> inputs(1, time);

   const Vector<double> outputs = neural_network.calculate_outputs(inputs);

   const double feed_rate = outputs[0];
   
   // calculate product concentration derivative

   const double specific_productivity = calculate_specific_productivity(product_concentration, substrate_concentration);

   const double product_concentration_dot = specific_productivity*cell_mass_concentration
   - feed_rate*product_concentration/broth_volume;

   return(product_concentration_dot);
}


// void calculate_broth_volume_dot(const NeuralNetwork&, const double&, const double&, const double&, const double&, const double&) const method

double FedBatchFermenter::calculate_broth_volume_dot(const NeuralNetwork& neural_network, const double& time, const double&, const double&, const double&, const double&) const
{

   // Obtain control
   
   Vector<double> inputs(1, time);

   Vector<double> outputs = neural_network.calculate_outputs(inputs);

   // Bound control

   double feed_rate = outputs[0];  

   // Calculate broth volume derivative

   double broth_volume_dot = feed_rate;

   return(broth_volume_dot);
}


// Vector<double> calculate_dependent_variables_dots(const NeuralNetwork&, const Vector<double>&) const method

Vector<double> FedBatchFermenter::calculate_dependent_variables_dots(const NeuralNetwork& neural_network, const Vector<double>& variables) const
{

   const double time = variables[0];
   const double cell_mass_concentration = variables[1]; 
   const double substrate_concentration = variables[2]; 
   const double product_concentration = variables[3]; 
   const double broth_volume = variables[4];

   Vector<double> dependent_variables_dots(4, 0.0);

   dependent_variables_dots[0] = calculate_cell_mass_concentration_dot(neural_network, time, cell_mass_concentration, substrate_concentration, product_concentration, broth_volume);
   dependent_variables_dots[1] = calculate_substrate_concentration_dot(neural_network, time, cell_mass_concentration, substrate_concentration, product_concentration, broth_volume);
   dependent_variables_dots[2] = calculate_product_concentration_dot(neural_network, time, cell_mass_concentration, substrate_concentration, product_concentration, broth_volume);
   dependent_variables_dots[3] = calculate_broth_volume_dot(neural_network, time, cell_mass_concentration, substrate_concentration, product_concentration, broth_volume);

   return(dependent_variables_dots);
}

}


// OpenNN: Open Neural Networks Library.
// Copyright (C) 2005-2014 Roberto Lopez 
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
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
