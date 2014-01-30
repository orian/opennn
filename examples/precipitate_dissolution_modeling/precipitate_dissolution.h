/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   P R E C I P I T A T E   D I S S O L U T I O N   C L A S S   H E A D E R                                    */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __PRECIPITATEDISSOLUTION_H__
#define __PRECIPITATEDISSOLUTION_H__

// System includes

#include <string>

// OpenNN includes

#include "../../source/opennn.h"



namespace OpenNN
{

class PrecipitateDissolution : public MathematicalModel
{

public:

   // GENERAL CONSTRUCTOR

   explicit PrecipitateDissolution(void);

   // DESTRUCTOR

   virtual ~PrecipitateDissolution(void);

   
   // METHODS

   // Evaluation methods

   // Get methods

   const double& get_minimum_Vickers_hardness(void) const;
   const double& get_maximum_Vickers_hardness(void) const;

   const double& get_reference_temperature(void) const;
   const double& get_reference_time(void) const;

   // Set methods

   void set_minimum_Vickers_hardness(const double&);
   void set_maximum_Vickers_hardness(const double&);

   void set_reference_temperature(const double&);
   void set_reference_time(const double&);

   void set_default(void);

   // Evaluation methods

   double calculate_full_dissolution_time(const double&, const double&) const;

   double calculate_volumetric_fraction(const double&) const;

   double calculate_normalized_time(const double&, const double&) const;

   double calculate_Vickers_hardness(const double&) const;

   Vector<double> calculate_volumetric_fraction_data(const double&) const;

   Matrix<double> calculate_dependent_variables(const NeuralNetwork&, const Matrix<double>&) const;  

private:

   double universal_gas_constant;

   double reference_temperature;

   double reference_time;

   double minimum_Vickers_hardness;

   double maximum_Vickers_hardness;
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
