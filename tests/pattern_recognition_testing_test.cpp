/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   http://flood.sourceforge.net                                                                               */
/*                                                                                                              */
/*   P A T T E R N   R E C O G N I T I O N   T E S T I N G   T E S T   C L A S S                                */
/*                                                                                                              */ 
/*   Roberto Lopez                                                                                              */ 
/*   E-mail: roberto-lopez@users.sourceforge.net                                                                */ 
/*                                                                                                              */
/****************************************************************************************************************/


// Unit testing includes

#include "pattern_recognition_testing_test.h"

using namespace OpenNN;

// GENERAL CONSTRUCTOR

PatternRecognitionTestingTest::PatternRecognitionTestingTest(void) : UnitTesting() 
{   
}


// DESTRUCTOR

PatternRecognitionTestingTest::~PatternRecognitionTestingTest(void)
{
}


// void test_constructor(void) method

void PatternRecognitionTestingTest::test_constructor(void)
{
   message += "test_constructor\n";

   // Default constructor

   PatternRecognitionTesting cu1;

   assert_true(cu1.get_neural_network_pointer() == NULL, LOG);
   assert_true(cu1.get_data_set_pointer() == NULL, LOG);

   // Neural network constructor

   NeuralNetwork mlp2;
   PatternRecognitionTesting cu2(&mlp2);

//   assert_true(cu1.get_multilayer_perceptron_pointer() != NULL, LOG);
   assert_true(cu1.get_data_set_pointer() == NULL, LOG);

   // Data set constructor

   DataSet itds3;
   PatternRecognitionTesting cu3(&itds3);

   assert_true(cu3.get_neural_network_pointer() == NULL, LOG);
   assert_true(cu3.get_data_set_pointer() != NULL, LOG);

   // Multilayer perceptron and input-target data set constructor

   NeuralNetwork mlp4;
   DataSet itds4;

   PatternRecognitionTesting cu4(&mlp4, &itds4);

//   assert_true(cu3.get_multilayer_perceptron_pointer() != NULL, LOG);
   assert_true(cu3.get_data_set_pointer() != NULL, LOG);
}


// void test_destructor(void) method

void PatternRecognitionTestingTest::test_destructor(void)
{
   message += "test_destructor\n";

   PatternRecognitionTesting* prt = new PatternRecognitionTesting();
   
   delete prt;
}


// void test_get_neural_network_pointer(void) method

void PatternRecognitionTestingTest::test_get_neural_network_pointer(void)
{
   message += "test_get_neural_network_pointer\n";

   NeuralNetwork nn;
   DataSet ds;

   PatternRecognitionTesting cu(&nn, &ds);

   NeuralNetwork* mlpp = cu.get_neural_network_pointer();

   assert_true(mlpp != 0, LOG);
}


// void test_get_data_set_pointer(void) method

void PatternRecognitionTestingTest::test_get_data_set_pointer(void)
{
   message += "test_get_data_set_pointer\n";

   NeuralNetwork nn;
   DataSet ds;

   PatternRecognitionTesting cu(&nn, &ds);

   DataSet* itdsp = cu.get_data_set_pointer();

   assert_true(itdsp != 0, LOG);
}


// void test_get_display(void) method

void PatternRecognitionTestingTest::test_get_display(void)
{
   message += "test_get_display\n";
}


// void test_set_neural_network_pointer(void) method

void PatternRecognitionTestingTest::test_set_neural_network_pointer(void)
{
   message += "test_set_neural_network_pointer\n";

   NeuralNetwork nn;

   PatternRecognitionTesting cu;

   cu.set_neural_network_pointer(&nn);

   NeuralNetwork* mlpp = cu.get_neural_network_pointer();

   assert_true(mlpp != 0, LOG);
}


// void test_set_data_set_pointer(void) method

void PatternRecognitionTestingTest::test_set_data_set_pointer(void)
{
   message += "test_set_data_set_pointer\n";

   DataSet ds;

   PatternRecognitionTesting cu;

   cu.set_data_set_pointer(&ds);

   DataSet* itdsp = cu.get_data_set_pointer();

   assert_true(itdsp != 0, LOG);
}


// void test_set_display(void) method

void PatternRecognitionTestingTest::test_set_display(void)
{
   message += "test_set_display\n";
}


// void test_calculate_binary_output_data(void) method

void PatternRecognitionTestingTest::test_calculate_binary_output_data(void)
{
   message += "test_calculate_binary_output_data\n";

   NeuralNetwork nn(1,1,1);
   nn.initialize_parameters(0.0);

   DataSet ds(1,1,1);
   ds.initialize_data(0.0);

   PatternRecognitionTesting cu(&nn, &ds);

   Matrix<bool> binary_output_data = cu.calculate_binary_output_data();

   assert_true(binary_output_data.get_rows_number() == 1, LOG);
   assert_true(binary_output_data.get_columns_number() == 1, LOG);
   assert_true(binary_output_data == false, LOG);
}


// void test_calculate_binary_training_output_data(void) method

void PatternRecognitionTestingTest::test_calculate_binary_training_output_data(void)
{
   message += "test_calculate_binary_training_output_data\n";

   NeuralNetwork nn(1,1,1);
   nn.initialize_parameters(0.0);

   DataSet ds(1,1,1);
   ds.initialize_data(0.0);

   PatternRecognitionTesting cu(&nn, &ds);

   Matrix<bool> binary_training_output_data = cu.calculate_binary_training_output_data();

   assert_true(binary_training_output_data.get_rows_number() == 1, LOG);
   assert_true(binary_training_output_data.get_columns_number() == 1, LOG);
   assert_true(binary_training_output_data == false, LOG);
}


// void test_calculate_binary_validation_output_data(void) method

void PatternRecognitionTestingTest::test_calculate_binary_validation_output_data(void)
{
   message += "test_calculate_binary_validation_output_data\n";
}


// void test_calculate_binary_testing_output_data(void) method

void PatternRecognitionTestingTest::test_calculate_binary_testing_output_data(void)
{
   message += "test_calculate_binary_testing_output_data\n";
}


// void test_get_binary_target_data(void) method

void PatternRecognitionTestingTest::test_get_binary_target_data(void)
{
   message += "test_get_binary_target_data\n";
}


// void test_get_binary_training_target_data(void) method

void PatternRecognitionTestingTest::test_get_binary_training_target_data(void)
{
   message += "test_get_binary_training_target_data\n";
}


// void test_get_binary_validation_target_data(void) method

void PatternRecognitionTestingTest::test_get_binary_validation_target_data(void)
{
   message += "test_get_binary_validation_target_data\n";
}


// void test_get_binary_testing_target_data(void) method

void PatternRecognitionTestingTest::test_get_binary_testing_target_data(void)
{
   message += "test_get_binary_testing_target_data\n";
}


// void test_calculate_confusion(void) method

void PatternRecognitionTestingTest::test_calculate_confusion(void)
{
   message += "test_calculate_confusion\n";

//   NeuralNetwork nn;
//   DataSet ds;

//   PatternRecognitionTesting prt(&nn, &ds); 

//   Matrix<unsigned> confusion = prt.calculate_confusion();

}


// void test_calculate_binary_classification_test(void) method

void PatternRecognitionTestingTest::test_calculate_binary_classification_test(void)
{
   message += "test_calculate_binary_classification_test\n";
}


// void test_save_confusion(void) method
// @todo

void PatternRecognitionTestingTest::test_save_confusion(void)
{
   message += "test_save_confusion\n";

//   NeuralNetwork nn(1,1,1);

//   nn.initialize_parameters(0.0);

//   DataSet ds(1,1,1);

//   ds.get_instances_pointer()->set_testing();

//   ds.initialize_data(0.0);

//   PatternRecognitionTesting cu(&nn, &ds); 
   
//   cu.save_confusion("../data/opennn_tests/confusion.dat");
}


// void test_get_testing_results(void) method

void PatternRecognitionTestingTest::test_get_testing_results(void)
{
   message += "test_get_testing_results\n";
   
}


// void test_print_testing_results(void) method

void PatternRecognitionTestingTest::test_print_testing_results(void)
{
   message += "test_print_testing_results\n";
   
}


// void test_save_testing_results(void) method

void PatternRecognitionTestingTest::test_save_testing_results(void)
{
   message += "test_save_testing_results\n";
}


// void run_test_case(void) method

void PatternRecognitionTestingTest::run_test_case(void)
{
   message += "Running pattern recognition utilities test case...\n";

   // Constructor methods

   test_constructor();

   // Destructor methods
   
   test_destructor();

   // Get methods

   test_get_neural_network_pointer();
   test_get_data_set_pointer();
   
   test_get_display();

   // Set methods

   test_set_neural_network_pointer();
   test_set_data_set_pointer();

   test_set_display();

   // Output data methods
   
   test_calculate_binary_output_data();

   test_calculate_binary_training_output_data();
   test_calculate_binary_validation_output_data();
   test_calculate_binary_testing_output_data();

   // Target data methods

   test_get_binary_target_data();

   test_get_binary_training_target_data();
   test_get_binary_validation_target_data();
   test_get_binary_testing_target_data();
   
   // Binary classification test methods

   test_calculate_binary_classification_test();

   // Confusion matrix methods
   
   test_calculate_confusion();
   test_save_confusion();

   // Testing results methods

   test_get_testing_results();
   test_print_testing_results();
   test_save_testing_results();

   message += "End of pattern recognition utilities test case\n";
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
