/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   T E S T I N G   A N A L Y S I S   T E S T   C L A S S                                                      */
/*                                                                                                              */ 
/*   Roberto Lopez                                                                                              */ 
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// Unit testing includes

#include "testing_analysis_test.h"

using namespace OpenNN;


TestingAnalysisTest::TestingAnalysisTest(void) : UnitTesting() 
{
}


TestingAnalysisTest::~TestingAnalysisTest(void)
{
}


void TestingAnalysisTest::test_constructor(void)
{
   message += "test_constructor\n";

   // Neural network constructor

   NeuralNetwork nn2;
   TestingAnalysis ta2(&nn2);

   assert_true(ta2.get_neural_network_pointer() != NULL, LOG);

   // Data set constructor

   DataSet ds3;
   TestingAnalysis ta3(&ds3);

   assert_true(ta3.get_data_set_pointer() != NULL, LOG);

   // Neural network and data set constructor

   NeuralNetwork nn4;
   DataSet ds4;

   TestingAnalysis ta4(&nn4, &ds4);

   assert_true(ta4.get_neural_network_pointer() != NULL, LOG);
   assert_true(ta4.get_data_set_pointer() != NULL, LOG);
}


void TestingAnalysisTest::test_destructor(void)
{
   message += "test_destructor\n";
}


void TestingAnalysisTest::test_get_neural_network_pointer(void)
{
   message += "test_get_neural_network_pointer\n";

   TestingAnalysis ta;

   NeuralNetwork nn;

   ta.set_neural_network_pointer(&nn);
   
   assert_true(ta.get_neural_network_pointer() != NULL, LOG);
}


void TestingAnalysisTest::test_get_data_set_pointer(void)
{
   message += "test_get_data_set_pointer\n";

   TestingAnalysis ta;

   DataSet ds;

   ta.set_data_set_pointer(&ds);
   
   assert_true(ta.get_data_set_pointer() != NULL, LOG);
}


void TestingAnalysisTest::test_get_display(void)
{
   message += "test_get_display\n";
}


void TestingAnalysisTest::test_set_neural_network_pointer(void)
{
   message += "test_set_neural_network_pointer\n";
}


void TestingAnalysisTest::test_set_data_set_pointer(void)
{
   message += "test_set_data_set_pointer\n";
}


void TestingAnalysisTest::test_set_display(void)
{
   message += "test_set_display\n";
}


void TestingAnalysisTest::test_calculate_target_output_data(void)
{
   message += "test_calculate_target_output_data\n";

   NeuralNetwork nn;
   DataSet ds;

   TestingAnalysis ta(&nn, &ds);

   Vector< Matrix<double> > target_output_data;

   // Test

   nn.set(1, 1);
   nn.initialize_parameters(0.0);

   ds.set(1, 1, 1);
   ds.initialize_data(0.0);
   ds.get_instances_pointer()->set_testing();

   target_output_data = ta.calculate_target_output_data();

   assert_true(target_output_data.size() == 1, LOG);

   assert_true(target_output_data[0].get_rows_number() == 1, LOG);
   assert_true(target_output_data[0].get_columns_number() == 2, LOG);
   assert_true(target_output_data[0] == 0.0, LOG);
}


void TestingAnalysisTest::test_calculate_error_data(void)
{
    message += "test_calculate_error_data\n";

    NeuralNetwork nn;

    DataSet ds;
    TestingAnalysis ta(&nn, &ds);

    Vector< Matrix<double> > error_data;

    // Test

    nn.set(1, 1);
    nn.construct_unscaling_layer();
    nn.initialize_parameters(0.0);

    ds.set(1, 1, 1);
    ds.initialize_data(0.0);
    ds.get_instances_pointer()->set_testing();

    error_data = ta.calculate_error_data();

    assert_true(error_data.size() == 1, LOG);
    assert_true(error_data[0].get_rows_number() == 1, LOG);
    assert_true(error_data[0].get_columns_number() == 3, LOG);
    assert_true(error_data[0] == 0.0, LOG);

}


void TestingAnalysisTest::test_calculate_error_data_statistics(void)
{
    message += "test_calculate_error_data_statistics\n";

    NeuralNetwork nn;
    DataSet ds;
    TestingAnalysis ta(&nn, &ds);

    Vector< Vector< Statistics<double> > > error_data_statistics;

    // Test

    nn.set(1, 1);
    nn.construct_unscaling_layer();
    nn.initialize_parameters(0.0);

    ds.set(1, 1, 1);
    ds.get_instances_pointer()->set_testing();
    ds.initialize_data(0.0);

    error_data_statistics = ta.calculate_error_data_statistics();

    assert_true(error_data_statistics.size() == 1, LOG);
    assert_true(error_data_statistics[0].size() == 3, LOG);
    assert_true(error_data_statistics[0][0].minimum == 0.0, LOG);
    assert_true(error_data_statistics[0][0].maximum == 0.0, LOG);
    assert_true(error_data_statistics[0][0].mean == 0.0, LOG);
    assert_true(error_data_statistics[0][0].standard_deviation == 0.0, LOG);
}


void TestingAnalysisTest::test_calculate_error_data_statistics_matrices(void)
{
    message += "test_calculate_error_data_statistics_matrices\n";
}


void TestingAnalysisTest::test_calculate_error_data_histograms(void)
{
    message += "test_calculate_error_data_histograms\n";

    NeuralNetwork nn;
    DataSet ds;
    TestingAnalysis ta(&nn, &ds);

    Vector< Histogram<double> > error_data_histograms;

    // Test

    nn.set(1, 1);
    nn.construct_unscaling_layer();
    nn.initialize_parameters(0.0);

    ds.set(1, 1, 3);
    ds.get_instances_pointer()->set_testing();
    ds.initialize_data(0.0);

    error_data_histograms = ta.calculate_error_data_histograms();

    assert_true(error_data_histograms.size() == 1, LOG);
    assert_true(error_data_histograms[0].get_bins_number() == 10, LOG);
}


void TestingAnalysisTest::test_calculate_linear_regression_parameters(void)
{
   message += "test_calculate_linear_regression_parameters\n";

   NeuralNetwork nn;

   DataSet ds;

   Matrix<double> data;

   TestingAnalysis ta(&nn, &ds);

   Vector< LinearRegressionParameters<double> > linear_regression_parameters;

    // Test

   nn.set(1,1);

   nn.initialize_parameters(0.0);

   ds.set(1,1,1);

   ds.get_instances_pointer()->set_testing();

   ds.initialize_data(0.0);

   linear_regression_parameters = ta.calculate_linear_regression_parameters();

   assert_true(linear_regression_parameters.size() == 1, LOG);




}


void TestingAnalysisTest::test_print_linear_regression_parameters(void)
{
   message += "test_print_linear_regression_parameters\n";

   NeuralNetwork nn(1,1,1);

   nn.initialize_parameters(0.0);

   DataSet ds(1,1,1);

   ds.get_instances_pointer()->set_testing();

   ds.initialize_data(0.0);

   TestingAnalysis ta(&nn, &ds);
//   ta.print_linear_regression_parameters();
}


void TestingAnalysisTest::test_save_linear_regression_parameters(void)
{
   message += "test_save_linear_regression_parameters\n";

   std::string file_name = "../data/linear_regression_parameters.dat";

   NeuralNetwork nn;
   DataSet ds;

   TestingAnalysis ta(&nn, &ds);
//   ta.save_linear_regression_parameters(file_name);
}


void TestingAnalysisTest::test_print_linear_regression_analysis(void)
{
   message += "test_print_linear_regression_analysis\n";
}


void TestingAnalysisTest::test_save_linear_regression_analysis(void)
{
   message += "test_save_linear_regression_analysis\n";
}


void TestingAnalysisTest::test_calculate_confusion(void)
{
   message += "test_calculate_confusion\n";

   NeuralNetwork nn;
   DataSet ds;

   TestingAnalysis ta(&nn, &ds);

   Instances* i;

   Matrix<double> actual;
   Matrix<double> predicted;

   Matrix<unsigned> confusion;

   // Test

   nn.set(1, 1);
   ds.set(1, 1, 10);
   ds.randomize_data_uniform(0.0, 1.0);
   i = ds.get_instances_pointer();
   i->set_testing();

   confusion = ta.calculate_confusion();

   assert_true(confusion.get_rows_number() == 2, LOG);
   assert_true(confusion.get_columns_number() == 2, LOG);
   assert_true(confusion.calculate_sum() == 10, LOG);

   // Test

   actual.set(4, 3);
   predicted.set(4, 3);

   actual[0][0] = 1; actual[0][1] = 0; actual[0][2] = 0;
   actual[1][0] = 0; actual[1][1] = 1; actual[1][2] = 0;
   actual[2][0] = 0; actual[2][1] = 1; actual[2][2] = 0;
   actual[3][0] = 0; actual[3][1] = 0; actual[3][2] = 1;

   predicted[0][0] = 1; predicted[0][1] = 0; predicted[0][2] = 0;
   predicted[1][0] = 0; predicted[1][1] = 1; predicted[1][2] = 0;
   predicted[2][0] = 0; predicted[2][1] = 1; predicted[2][2] = 0;
   predicted[3][0] = 0; predicted[3][1] = 0; predicted[3][2] = 1;

   confusion = ta.calculate_confusion_multiple_classification(actual, predicted);

   assert_true(confusion.calculate_sum() == 4, LOG);
   assert_true(confusion.get_diagonal().calculate_sum() == 4, LOG);
}


void TestingAnalysisTest::test_calculate_binary_classification_test(void)
{
   message += "test_calculate_binary_classification_test\n";
}


void TestingAnalysisTest::run_test_case(void)
{
   message += "Running testing analysis test case...\n";

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

   // Target and output data methods

   test_calculate_target_output_data();

   // Error data methods

   test_calculate_error_data();

   test_calculate_error_data_statistics();
   test_calculate_error_data_statistics_matrices();

   test_calculate_error_data_histograms();

   // Linear regression analysis methods

   test_calculate_linear_regression_parameters();
   test_print_linear_regression_parameters();
   test_save_linear_regression_parameters();

   test_print_linear_regression_analysis();
   test_save_linear_regression_analysis();


   // Binary classification test methods

   test_calculate_binary_classification_test();

   // Confusion matrix methods

   test_calculate_confusion();

   message += "End of testing analysis test case.\n";
}


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
