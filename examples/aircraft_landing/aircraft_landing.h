/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   A I R C R A F T   L A N D I N G   C L A S S   H E A D E R                                                  */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __AIRCRAFTLANDING_H__
#define __AIRCRAFTLANDING_H__

#include "../../source/opennn.h"

namespace OpenNN
{

class AircraftLanding : public OrdinaryDifferentialEquations
{

#define PI 4.0*atan(1.0)

public:

   // GENERAL CONSTRUCTOR

   explicit AircraftLanding(void);

   // DESTRUCTOR

   virtual ~AircraftLanding(void);

   // METHODS

   // Get methods

   const double& get_short_period_gain(void) const;
   const double& get_path_time_constant(void) const;
   const double& get_short_period_resonant_frequency(void) const;
   const double& get_short_period_damping_factor(void) const;

   const double& get_velocity(void) const;

   // Set methods

   void set_short_period_gain(const double&);
   void set_short_period_resonant_frequency(const double&);
   void set_short_period_damping_factor(const double&);
   void set_path_time_constant(const double&);

   void set_velocity(const double&);

   void set_default(void);

   // State equation methods

   double calculate_pitch_angle_rate_dot(const NeuralNetwork&, const double&, const double&, const double&, const double&, const double&) const;
   double calculate_pitch_angle_dot(const NeuralNetwork&, const double&, const double&, const double&, const double&, const double&) const;
   double calculate_altitude_rate_dot(const NeuralNetwork&, const double&, const double&, const double&, const double&, const double&) const;
   double calculate_altitude_dot(const NeuralNetwork&, const double&, const double&, const double&, const double&, const double&) const;

   Vector<double> calculate_dependent_variables_dots(const NeuralNetwork&, const Vector<double>&) const;

private:

   // Aircraft parameters

   double short_period_gain;
   double short_period_resonant_frequency;
   double short_period_damping_factor;
   double path_time_constant;

   // Flying conditions

   double velocity;
};

}

#endif

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
