/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   C A R   C L A S S   H E A D E R                                                                            */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __CAR_H__
#define __CAR_H__

// OpenNN includes

#include "../../source/opennn.h"

namespace OpenNN
{

class Car : public OrdinaryDifferentialEquations
{

public:

   // GENERAL CONSTRUCTOR

   explicit Car(void);

   // COPY CONSTRUCTOR

   Car(const Car&);

   // DESTRUCTOR

   virtual ~Car(void);


   // METHODS

   // Get methods
   
   // Set methods

   void set_default(void);

   // State equation methods

   Vector<double> calculate_dependent_variables_dots(const NeuralNetwork&, const Vector<double>&) const;

   // Solution methods

   Vector<double> calculate_final_solutions(const NeuralNetwork&) const;
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
