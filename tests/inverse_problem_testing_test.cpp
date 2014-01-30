/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   http://flood.sourceforge.net                                                                               */
/*                                                                                                              */
/*   I N V E R S E   P R O B L E M   T E S T I N G   T E S T   C L A S S                                        */
/*                                                                                                              */ 
/*   Roberto Lopez                                                                                              */ 
/*   E-mail: roberto-lopez@users.sourceforge.net                                                                */ 
/*                                                                                                              */
/****************************************************************************************************************/

// System includes

#include <iostream>

// Unit testing includes

#include "inverse_problem_testing_test.h"

using namespace OpenNN;


// GENERAL CONSTRUCTOR

InverseProblemTestingTest::InverseProblemTestingTest(void) : UnitTesting() 
{
}


// DESTRUCTOR

InverseProblemTestingTest::~InverseProblemTestingTest(void)
{
}


// METHODS

// void test_constructor(void) method

void InverseProblemTestingTest::test_constructor(void)
{
   message += "test_constructor\n";

   // Default constructor

   FunctionRegressionTesting mu1;

   assert_true(mu1.get_neural_network_pointer() == NULL, LOG);
   assert_true(mu1.get_data_set_pointer() == NULL, LOG);

   // Neural network constructor

   NeuralNetwork mlp2;
   FunctionRegressionTesting mu2(&mlp2);

   assert_true(mu2.get_neural_network_pointer() != NULL, LOG);
   assert_true(mu2.get_data_set_pointer() == NULL, LOG);

   // Data set constructor

   DataSet itds3;
   FunctionRegressionTesting mu3(&itds3);

   assert_true(mu3.get_neural_network_pointer() == NULL, LOG);
   assert_true(mu3.get_data_set_pointer() != NULL, LOG);

   // Neural network and data set constructor

   NeuralNetwork mlp4;
   DataSet itds4;

   FunctionRegressionTesting mu4(&mlp4, &itds4);

   assert_true(mu4.get_neural_network_pointer() != NULL, LOG);
   assert_true(mu4.get_data_set_pointer() != NULL, LOG);
}


// void test_destructor(void) method

void InverseProblemTestingTest::test_destructor(void)
{
   message += "test_destructor\n";
}


// Get methods

// void test_get_neural_network_pointer(void) method

void InverseProblemTestingTest::test_get_neural_network_pointer(void)
{
   message += "test_get_neural_network_pointer\n";

   FunctionRegressionTesting mu;

   assert_true(mu.get_neural_network_pointer() == NULL, LOG);

   NeuralNetwork nn;

   mu.set_neural_network_pointer(&nn);
   
   assert_true(mu.get_neural_network_pointer() != NULL, LOG);
}


// void test_get_data_set_pointer(void) method

void InverseProblemTestingTest::test_get_data_set_pointer(void)
{
   message += "test_get_data_set_pointer\n";

   FunctionRegressionTesting mu;

   assert_true(mu.get_data_set_pointer() == NULL, LOG);

   DataSet ds;

   mu.set_data_set_pointer(&ds);
   
   assert_true(mu.get_data_set_pointer() != NULL, LOG);
}


// void test_get_display(void) method

void InverseProblemTestingTest::test_get_display(void)
{
   message += "test_get_display\n";
}


// void test_set_neural_network_pointer(void) method

void InverseProblemTestingTest::test_set_neural_network_pointer(void)
{
   message += "test_set_neural_network_pointer\n";
}


// void test_set_data_set_pointer(void) method

void InverseProblemTestingTest::test_set_data_set_pointer(void)
{
   message += "test_set_data_set_pointer\n";
}


// void test_set_display(void) method

void InverseProblemTestingTest::test_set_display(void)
{
   message += "test_set_display\n";
}


// void run_test_case(void) method

void InverseProblemTestingTest::run_test_case(void)
{
   message += "Running inverse problem testing test case...\n";

   // Constructor and destructor methods

   test_constructor();
   test_destructor();

   // Get methods

   test_get_neural_network_pointer();
   test_get_data_set_pointer();
   
   test_get_display();

   // Set methods

   test_set_neural_network_pointer();
   test_set_data_set_pointer();

   test_set_display();

   message += "End of inverse problem testing test case\n";
}


// OpenNN: Open Neural Networks Library.
// Copyright (C) 2005-2013 Roberto Lopez 
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
