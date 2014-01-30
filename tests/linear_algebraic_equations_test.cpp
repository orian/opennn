/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   L I N E A R   A L G E B R A I C   E Q U A T I O N S   T E S T   C L A S S                                  */
/*                                                                                                              */ 
/*   Roberto Lopez                                                                                              */ 
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// Unit testing includes

#include "linear_algebraic_equations_test.h"

using namespace OpenNN;

// GENERAL CONSTRUCTOR

LinearAlgebraicEquationsTest::LinearAlgebraicEquationsTest(void) : UnitTesting() 
{
}



// DESTRUCTOR

LinearAlgebraicEquationsTest::~LinearAlgebraicEquationsTest(void)
{
}


// METHODS

void LinearAlgebraicEquationsTest::test_constructor(void)
{
   message += "test_constructor\n";

   LinearAlgebraicEquations lae;
}


void LinearAlgebraicEquationsTest::test_destructor(void)
{
   message += "test_destructor\n";

   LinearAlgebraicEquations* laep = new LinearAlgebraicEquations();

   assert_true(laep != NULL, LOG);

   delete laep;
}


void LinearAlgebraicEquationsTest::test_perform_Gauss_Jordan_elimination(void)
{
   message += "test_perform_Gauss_Jordan_elimination\n";

   LinearAlgebraicEquations lae;

   Matrix<double> a;
   Vector<double> b;

   Matrix<double> inverse;

   // Test 

   a.set(1, 1, 1.0);

   b.set(1, 0.0);

   lae.perform_Gauss_Jordan_elimination(a, b);

   assert_true(a == 1.0, LOG);
   assert_true(b == 0.0, LOG);

   // Test 

   a.set(2, 2);
   a.initialize_identity();

   b.set(2, 0.0);

   lae.perform_Gauss_Jordan_elimination(a, b);

   inverse.set(2, 2);
   inverse.initialize_identity();

   assert_true(a == inverse, LOG);
   assert_true(b == 0.0, LOG);

   // Test

   a.set(100, 100);
   a.randomize_normal();
   b.set(100);
   b.randomize_normal();

   lae.perform_Gauss_Jordan_elimination(a, b);

   assert_true(a.get_rows_number() == 100, LOG);
   assert_true(a.get_columns_number() == 100, LOG);
   assert_true(b.size() == 100, LOG);
}


void LinearAlgebraicEquationsTest::run_test_case(void)
{
   message += "Running linear algebraic equations test case...\n";

   // Constructor and destructor methods

   test_constructor();
   test_destructor();

   // Gauss-Jordan elimination methods

   test_perform_Gauss_Jordan_elimination();

   message += "End of linear algebraic equations test case.\n";
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
