/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   D E   J O N G   F U N C T I O N   C L A S S   H E A D E R                                                  */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/


#ifndef __DEJONGFUNCTION_H__
#define __DEJONGFUNCTION_H__

#include "../../source/performance_term.h"

namespace OpenNN
{

class DeJongFunction : public PerformanceTerm
{

public:

   // DEFAULT CONSTRUCTOR

   explicit DeJongFunction(void);

   // GENERAL CONSTRUCTOR

   explicit DeJongFunction(NeuralNetwork*);

   // DESTRUCTOR

   virtual ~DeJongFunction(void);


   // METHODS

   // Get methods

   // Set methods

   // Objective methods

   double calculate_performance(void) const;
   double calculate_performance(const Vector<double>&) const;

   Vector<double> calculate_gradient(void) const;

   Matrix<double> calculate_Hessian(void) const;

   Matrix<double> calculate_inverse_Hessian(void) const;

private:

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
