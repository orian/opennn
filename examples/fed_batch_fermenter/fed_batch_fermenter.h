/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   F E D   B A T C H   F E R M E N T E R   C L A S S   H E A D E R                                            */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __FEDBATCHFERMENTER_H__
#define __FEDBATCHFERMENTER_H__

// OpenNN includes

#include "../../source/opennn.h"

namespace OpenNN
{

class FedBatchFermenter : public OrdinaryDifferentialEquations
{

public:

   // GENERAL CONSTRUCTOR  

   explicit FedBatchFermenter(void);


   // DESTRUCTOR

   virtual ~FedBatchFermenter(void);

   // METHODS

   // Get methods

   // Set methods

   void set_default(void);

   // State equation methods

   double calculate_specific_growth_rate(const double&, const double&) const;
   double calculate_specific_productivity(const double&, const double&) const;

   double calculate_cell_mass_concentration_dot(const NeuralNetwork&, const double&, const double&, const double&, const double&, const double&) const;
   double calculate_substrate_concentration_dot(const NeuralNetwork&, const double&, const double&, const double&, const double&, const double&) const;
   double calculate_product_concentration_dot(const NeuralNetwork&, const double&, const double&, const double&, const double&, const double&) const;
   double calculate_broth_volume_dot(const NeuralNetwork&, const double&, const double&, const double&, const double&, const double&) const;

   Vector<double> calculate_dependent_variables_dots(const NeuralNetwork&, const Vector<double>&) const;

private:

   double yield_coefficient;

   double feed_substrate_concentration;

   double kinetic_constant_mu0;

   double kinetic_constant_eta0;

   double kinetic_constant_kp;

   double kinetic_constant_kp_dash;

   double kinetic_constant_ks;

   double kinetic_constant_ks_dash;
};

}

#endif


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
