/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   A I R C R A F T   L A N D I N G   C L A S S                                                                */
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
#include <cstdlib>     
#include <cmath>     

// OpenNN includes

#include "aircraft_landing.h"     

namespace OpenNN
{

// NEURAL NETWORK CONSTRUCTOR

AircraftLanding::AircraftLanding() : OrdinaryDifferentialEquations()
{
   set_default();
}
 

// DESTRUCTOR

AircraftLanding::~AircraftLanding(void) 
{
}


// METHODS

// const double& get_short_period_gain(void) const method

const double& AircraftLanding::get_short_period_gain(void) const
{
   return(short_period_gain);
}


// const double& get_path_time_constant(void) const method

const double& AircraftLanding::get_path_time_constant(void) const
{
   return(path_time_constant);
}


// const double& get_short_period_resonant_frequency(void) const method

const double& AircraftLanding::get_short_period_resonant_frequency(void) const
{
   return(short_period_resonant_frequency);
}


// const double& get_short_period_damping_factor(void) const method

const double& AircraftLanding::get_short_period_damping_factor(void) const
{
   return(short_period_damping_factor);
}


// const double& get_velocity(void) const method

const double& AircraftLanding::get_velocity(void) const
{
   return(velocity);
}


// void set_short_period_gain(const double&) method

void AircraftLanding::set_short_period_gain(const double& new_short_period_gain)
{
   short_period_gain = new_short_period_gain;
}


// void set_short_period_resonant_frequency(const double&) method

void AircraftLanding::set_short_period_resonant_frequency(const double& new_short_period_resonant_frequency)
{
   short_period_resonant_frequency = new_short_period_resonant_frequency;
}


// void set_path_time_constant(const double&) method

void AircraftLanding::set_path_time_constant(const double& new_path_time_constant)
{
   path_time_constant = new_path_time_constant;
}


// void set_short_period_damping_factor(const double&) method

void AircraftLanding::set_short_period_damping_factor(const double& new_short_period_damping_factor)
{
   short_period_damping_factor = new_short_period_damping_factor;
}


// void set_velocity(const double&) method

void AircraftLanding::set_velocity(const double& new_velocity)
{
   velocity = new_velocity;
}


// void set_default(void) method

void AircraftLanding::set_default(void)
{
   independent_variables_number = 1;
   dependent_variables_number = 4;

   solution_method = RungeKuttaFehlberg;

   points_number = 1001;

   tolerance = 1.0e-6;

   initial_size = (unsigned int)1.0e3;
   warning_size = (unsigned int)1.0e6;
   error_size = (unsigned int)1.0e9;

   initial_independent_variable = 0.0;
   final_independent_variable = 20.0;

   initial_dependent_variables.set(4);
   set_initial_dependent_variable(0, 0.0); // rad*s-1
   set_initial_dependent_variable(1, -0.078); // rad

   set_initial_dependent_variable(2, 6.0); // m*s-1
   set_initial_dependent_variable(3, 30.0); // m

   // Aircraft parameters

   short_period_gain = -0.95; // (s-1)
   path_time_constant = 2.5; // (s)
   short_period_resonant_frequency = 1.0; // (rad/s)
   short_period_damping_factor = 0.5; // no units

   // Flying conditions

   velocity = 256.0; // (ft/s)

   display = true;
}


// double calculate_pitch_angle_rate_dot(const NeuralNetwork&, const double&, const double&, const double&, const double&, const double&) const method

double AircraftLanding::calculate_pitch_angle_rate_dot(const NeuralNetwork& neural_network, const double& time, 
const double& pitch_angle_rate, const double& pitch_angle, const double& altitude_rate, const double&) const
{

   const Vector<double> inputs(1, time);
   const Vector<double> outputs = neural_network.calculate_outputs(inputs);

   const double elevator_deflection = outputs[0];

   const double b11 = 1.0/path_time_constant 
              - 2.0*short_period_damping_factor*short_period_resonant_frequency;

   const double b12 = (2.0*short_period_damping_factor*short_period_resonant_frequency) / path_time_constant
              - pow(short_period_resonant_frequency, 2.0)
              - 1.0/( pow(path_time_constant,2.0));

   const double b13 = 1.0/(velocity*pow(path_time_constant,2.0))
              - ( 2.0*short_period_damping_factor*short_period_resonant_frequency) / (velocity*path_time_constant)   
              + ( pow(short_period_resonant_frequency,2.0) / velocity );

   const double c1 = pow(short_period_resonant_frequency,2.0)*short_period_gain*path_time_constant;

   const double pitch_angle_rate_dot = b11*pitch_angle_rate + b12*pitch_angle + b13*altitude_rate + c1*elevator_deflection;

   return(pitch_angle_rate_dot);
}


// double calculate_pitch_angle_dot(const NeuralNetwork&, const double&, const double&, const double&, const double&, const double&) const method

double AircraftLanding::calculate_pitch_angle_dot(const NeuralNetwork&, const double&, const double& pitch_angle_rate, const double&, const double&, const double&) const
{
   const double pitch_angle_dot = pitch_angle_rate;

   return(pitch_angle_dot);
}


// double calculate_altitude_rate_dot(const NeuralNetwork&, const double&, const double&, const double&, const double&, const double&) const method

double AircraftLanding::calculate_altitude_rate_dot(const NeuralNetwork&, const double&, const double&, const double& pitch_angle, const double& altitude_rate, const double&) const
{
   const double b32 = velocity/path_time_constant;

   const double b33 = -(1.0/path_time_constant);

   const double altitude_rate_dot = b32*pitch_angle + b33*altitude_rate;

   return(altitude_rate_dot);
}


// double calculate_altitude_dot(const NeuralNetwork&, const double&, const double&, const double&, const double&, const double&) const method

double AircraftLanding::calculate_altitude_dot(const NeuralNetwork&, const double&, const double&, const double&, const double& altitude_rate, const double&) const
{
   double altitude_dot = altitude_rate;

   return(altitude_dot);
}


// Vector<double> calculate_dependent_variables_dots(const NeuralNetwork&, const double&, const Vector<double>&) const method

Vector<double> AircraftLanding::calculate_dependent_variables_dots(const NeuralNetwork& neural_network, const Vector<double>& variables) const
{
   const double time = variables[0];
   const double pitch_angle_rate = variables[1];
   const double pitch_angle = variables[2];
   const double altitude_rate = variables[3];
   const double altitude = variables[4];

   Vector<double> independent_variables_dots(4);

   independent_variables_dots[0] = calculate_pitch_angle_rate_dot(neural_network, time, pitch_angle_rate, pitch_angle, altitude_rate, altitude);
   independent_variables_dots[1] = calculate_pitch_angle_dot(neural_network, time, pitch_angle_rate, pitch_angle, altitude_rate, altitude);
   independent_variables_dots[2] = calculate_altitude_rate_dot(neural_network, time, pitch_angle_rate, pitch_angle, altitude_rate, altitude);
   independent_variables_dots[3] = calculate_altitude_dot(neural_network, time, pitch_angle_rate, pitch_angle, altitude_rate, altitude);

   return(independent_variables_dots);
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
