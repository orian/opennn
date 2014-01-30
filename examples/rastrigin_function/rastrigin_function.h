/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   R A S T R I G I N   F U N C T I O N   C L A S S   H E A D E R                                              */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __RASTRIGINFUNCTION_H__
#define __RASTRIGINFUNCTION_H__

// OpenNN includes

#include "../../source/opennn.h"

namespace OpenNN
{

class RastriginFunction : public PerformanceTerm
{

public:

   // GENERAL CONSTRUCTOR

   explicit RastriginFunction(NeuralNetwork*);

   // DESTRUCTOR

   virtual ~RastriginFunction(void);


   // METHODS

   // Get methods

   int get_variables_number(void) const;

   // Set methods

   void set_variables_number(int);

   // Objective methods

   double calculate_performance(void) const;

   // @todo

   double calculate_performance(const Vector<double>&) const
   {
      return(0.0);
   };

   // Objective gradient vector methods

   Vector<double> calculate_gradient(void) const;

   // Objective function Hessian matrix methods

   Matrix<double> calculate_Hessian(void) const;
   
   Matrix<double> calculate_inverse_Hessian(void) const;

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
