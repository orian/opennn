/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   P E R I M E T E R   C L A S S   H E A D E R                                                                */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __PERIMETER_H__
#define __PERIMETER_H__

// OpenNN includes

#include "../../source/opennn.h"

namespace OpenNN
{

class Perimeter : public OrdinaryDifferentialEquations
{

public:

   // GENERAL CONSTRUCTOR

   explicit Perimeter(void);

   // DESTRUCTOR

   virtual ~Perimeter(void);

   // METHODS
    
   Vector<double> calculate_dependent_variables_dots(const NeuralNetwork&, const Vector<double>&) const;
      
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
