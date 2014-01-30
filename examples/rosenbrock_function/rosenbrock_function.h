/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   R O S E N B R O C K   F U N C T I O N   C L A S S   H E A D E R                                            */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/***************************************************************************************************************/

#ifndef __ROSENBROCKFUNCTION_H__
#define __ROSENBROCKFUNCTION_H__

// OpenNN includes

#include "../../source/opennn.h"


namespace OpenNN
{

class RosenbrockFunction : public PerformanceTerm
{

public:

   // GENERAL CONSTRUCTOR

   explicit RosenbrockFunction(NeuralNetwork*);

   // COPY CONSTRUCTOR

   RosenbrockFunction(const RosenbrockFunction&);

   // DESTRUCTOR

   virtual ~RosenbrockFunction(void);


   // METHODS

   // Objective methods


   double calculate_performance(void) const;

   double calculate_performance(const Vector<double>&) const;

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
