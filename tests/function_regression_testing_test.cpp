/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   http://flood.sourceforge.net                                                                               */
/*                                                                                                              */
/*   F U N C T I O N   R E G R E S S I O N   T E S T I N G   T E S T   C L A S S                                */
/*                                                                                                              */ 
/*   Roberto Lopez                                                                                              */ 
/*   E-mail: roberto-lopez@users.sourceforge.net                                                                */ 
/*                                                                                                              */
/****************************************************************************************************************/

// System includes

#include <iostream>

// Unit testing includes

#include "function_regression_testing_test.h"

using namespace OpenNN;


// GENERAL CONSTRUCTOR

FunctionRegressionTestingTest::FunctionRegressionTestingTest(void) : UnitTesting() 
{
}


// DESTRUCTOR

FunctionRegressionTestingTest::~FunctionRegressionTestingTest(void)
{
}


// METHODS

// void test_constructor(void) method

void FunctionRegressionTestingTest::test_constructor(void)
{
   message += "test_constructor\n";

   // Default constructor

   FunctionRegressionTesting mu1;

   assert_true(mu1.get_neural_network_pointer() == NULL, LOG);
   assert_true(mu1.get_data_set_pointer() == NULL, LOG);

   // Neural network constructor

   NeuralNetwork nn2;
   FunctionRegressionTesting mu2(&nn2);

   assert_true(mu2.get_neural_network_pointer() != NULL, LOG);
   assert_true(mu2.get_data_set_pointer() == NULL, LOG);

   // Data set constructor

   DataSet ds3;
   FunctionRegressionTesting mu3(&ds3);

   assert_true(mu3.get_neural_network_pointer() == NULL, LOG);
   assert_true(mu3.get_data_set_pointer() != NULL, LOG);

   // Neural network and input-target data set constructor

   NeuralNetwork nn4;
   DataSet ds4;

   FunctionRegressionTesting mu4(&nn4, &ds4);

   assert_true(mu4.get_neural_network_pointer() != NULL, LOG);
   assert_true(mu4.get_data_set_pointer() != NULL, LOG);
}


// void test_destructor(void) method

void FunctionRegressionTestingTest::test_destructor(void)
{
   message += "test_destructor\n";
}


// Get methods

// void test_get_neural_network_pointer(void) method

void FunctionRegressionTestingTest::test_get_neural_network_pointer(void)
{
   message += "test_get_get_neural_network_pointer\n";

   FunctionRegressionTesting mu;

   assert_true(mu.get_neural_network_pointer() == NULL, LOG);

   NeuralNetwork nn;

   mu.set_neural_network_pointer(&nn);
   
   assert_true(mu.get_neural_network_pointer() != NULL, LOG);
}


// void test_get_data_set_pointer(void) method

void FunctionRegressionTestingTest::test_get_data_set_pointer(void)
{
   message += "test_get_data_set_pointer\n";

   FunctionRegressionTesting mu;

   assert_true(mu.get_data_set_pointer() == NULL, LOG);

   DataSet ds;

   mu.set_data_set_pointer(&ds);
   
   assert_true(mu.get_data_set_pointer() != NULL, LOG);
}


// void test_get_display(void) method

void FunctionRegressionTestingTest::test_get_display(void)
{
   message += "test_get_display\n";
}


// void test_set_neural_network_pointer(void) method

void FunctionRegressionTestingTest::test_set_neural_network_pointer(void)
{
   message += "test_set_neural_network_pointer\n";
}


// void test_set_data_set_pointer(void) method

void FunctionRegressionTestingTest::test_set_data_set_pointer(void)
{
   message += "test_set_data_set_pointer\n";
}


// void test_set_display(void) method

void FunctionRegressionTestingTest::test_set_display(void)
{
   message += "test_set_display\n";
}


// void test_calculate_scaled_target_output_data(void) method

void FunctionRegressionTestingTest::test_calculate_scaled_target_output_data(void)
{
   message += "test_calculate_scaled_target_output_data\n";
   
   NeuralNetwork nn(1,1,1);
   nn.initialize_parameters(0.0);

   DataSet ds(1,1,1);
   ds.initialize_data(0.0);
   ds.get_instances_pointer()->set_testing();

   FunctionRegressionTesting fru(&nn, &ds);

   Vector< Matrix<double> > scaled_target_output_data = fru.calculate_scaled_target_output_data();

   assert_true(scaled_target_output_data.size() == 1, LOG);

   assert_true(scaled_target_output_data[0].get_rows_number() == 1, LOG);
   assert_true(scaled_target_output_data[0].get_columns_number() == 2, LOG);
   assert_true(scaled_target_output_data[0] == 0.0, LOG);
}



// void test_print_scaled_target_output_data(void) method

void FunctionRegressionTestingTest::test_print_scaled_target_output_data(void)
{
   message += "test_print_scaled_target_output_data\n";

   NeuralNetwork nn(1,1,1);
   nn.initialize_parameters(0.0);

   DataSet ds(1,1,1);
   ds.initialize_data(0.0);
   ds.get_instances_pointer()->set_testing();

   FunctionRegressionTesting fru(&nn, &ds);
//   fru.print_scaled_target_output_data();
}


// void test_save_scaled_target_output_data(void) method

void FunctionRegressionTestingTest::test_save_scaled_target_output_data(void)
{
   message += "test_save_scaled_target_output_data\n";

   NeuralNetwork nn(1,1,1);
   nn.initialize_parameters(0.0);

   DataSet ds(1,1,1);
   ds.initialize_data(0.0);
   ds.get_instances_pointer()->set_testing();

   FunctionRegressionTesting fru(&nn, &ds);
//   fru.save_scaled_target_output_data("../data/opennn_tests/TestingTargetOutputData.dat");
}


// void test_calculate_linear_regression_parameters(void) method

void FunctionRegressionTestingTest::test_calculate_linear_regression_parameters(void)
{
   message += "test_calculate_linear_regression_parameters\n";

   NeuralNetwork nn(1,1,1);

   nn.initialize_parameters(0.0);

   DataSet ds(1,1,1);

   ds.get_instances_pointer()->set_testing();

   ds.initialize_data(0.0);

   FunctionRegressionTesting mu(&nn, &ds);

   Vector< Vector<double> > linear_regression_parameters = mu.calculate_linear_regression_parameters();

   assert_true(linear_regression_parameters.size() == 1, LOG);
}


// void test_print_linear_regression_parameters(void) method

void FunctionRegressionTestingTest::test_print_linear_regression_parameters(void)
{
   message += "test_print_linear_regression_parameters\n";

   NeuralNetwork nn(1,1,1);

   nn.initialize_parameters(0.0);

   DataSet ds(1,1,1);

   ds.get_instances_pointer()->set_testing();

   ds.initialize_data(0.0);

   FunctionRegressionTesting fru(&nn, &ds);
   //fru.print_linear_regression_parameters();
}


// void test_save_linear_regression_parameters(void) method

void FunctionRegressionTestingTest::test_save_linear_regression_parameters(void)
{
   message += "test_save_linear_regression_parameters\n";

   NeuralNetwork nn;
   DataSet ds;

   FunctionRegressionTesting fru(&nn, &ds);
//   fru.save_linear_regression_parameters("../data/opennn_tests/LinearRegressionParameters");
}


// void test_print_linear_regression_analysis(void) method

void FunctionRegressionTestingTest::test_print_linear_regression_analysis(void)
{
   message += "test_print_linear_regression_analysis\n";
}


// void test_save_linear_regression_analysis(void) method

void FunctionRegressionTestingTest::test_save_linear_regression_analysis(void)
{
   message += "test_save_linear_regression_analysis\n";
}


// void run_test_case(void) method

void FunctionRegressionTestingTest::run_test_case(void)
{
   message += "Running function regression testing test case...\n";

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

   // Testing target output data methods

   test_calculate_scaled_target_output_data();
   test_print_scaled_target_output_data();
   test_save_scaled_target_output_data();

   // Linear regression parameters methods

   test_calculate_linear_regression_parameters();
   test_print_linear_regression_parameters();
   test_save_linear_regression_parameters();

   // Linear regression analysis methods

   test_print_linear_regression_analysis();
   test_save_linear_regression_analysis();

   message += "End of function regression testing test case\n";
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
