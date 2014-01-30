/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   D A T A   S E T   T E S T   C L A S S                                                                      */
/*                                                                                                              */ 
/*   Roberto Lopez                                                                                              */ 
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// Unit testing includes

#include "data_set_test.h"

using namespace OpenNN;

// GENERAL CONSTRUCTOR

DataSetTest::DataSetTest(void) : UnitTesting() 
{
}



// DESTRUCTOR

DataSetTest::~DataSetTest(void)
{
}


// METHODS

// @todo Fix exception in file constructor: basic_string::_S_construct null not valid

void DataSetTest::test_constructor(void)
{
   message += "test_constructor\n";

   const std::string file_name = "../data/data_set.xml";

   // Default constructor

   DataSet ds1;

   assert_true(ds1.get_variables().get_variables_number() == 0, LOG);
   assert_true(ds1.get_instances().get_instances_number() == 0, LOG);

   // Instances and variables number constructor

   DataSet ds2(1, 2);

   assert_true(ds2.get_variables().get_variables_number() == 1, LOG);
   assert_true(ds2.get_instances().get_instances_number() == 2, LOG);

   // Inputs, targets and instances numbers constructor

   DataSet ds3(1, 1, 1);

   assert_true(ds3.get_variables().get_variables_number() == 2, LOG);
   assert_true(ds3.get_instances().get_instances_number() == 1, LOG);

   // XML constructor

   tinyxml2::XMLDocument* document = ds3.to_XML();

   DataSet ds4(*document);

   assert_true(ds4.get_variables().get_variables_number() == 2, LOG);
   assert_true(ds4.get_instances().get_instances_number() == 1, LOG);

   delete document;

   // File constructor

//   ds1.save(file_name);

//   DataSet ds5(file_name);

//   assert_true(ds5.get_variables().get_variables_number() == 0, LOG);
//   assert_true(ds5.get_instances().get_instances_number() == 0, LOG);

   // Copy constructor

   DataSet ds6(ds1);

   assert_true(ds6.get_variables().get_variables_number() == 0, LOG);
   assert_true(ds6.get_instances().get_instances_number() == 0, LOG);

}


void DataSetTest::test_destructor(void)
{
   message += "test_destructor\n";

   DataSet* dsp = new DataSet(1, 1, 1);

   delete dsp;
}


void DataSetTest::test_assignment_operator(void)
{
   message += "test_assignment_operator\n";

   DataSet ds1(1, 1, 1);
   DataSet ds2 = ds1;

   assert_true(ds2.get_instances().get_instances_number() == 1, LOG);
   assert_true(ds2.get_variables().get_variables_number() == 2, LOG);
}


void DataSetTest::test_get_instances_number(void) 
{
   message += "test_get_instances_number\n";

   DataSet ds;

   assert_true(ds.get_instances().get_instances_number() == 0, LOG);
}


void DataSetTest::test_get_variables_number(void) 
{
   message += "test_get_variables_number\n";

   DataSet ds;

   assert_true(ds.get_variables().get_variables_number() == 0, LOG);
}


void DataSetTest::test_get_variables(void) 
{
   message += "test_get_variables\n";

   DataSet ds(1, 3, 2);

   const Variables& variables = ds.get_variables();

   assert_true(variables.count_inputs_number() == 1, LOG);
   assert_true(variables.count_targets_number() == 3, LOG);
}


void DataSetTest::test_get_display(void) 
{
   message += "test_get_display\n";

   DataSet ds;

   ds.set_display(true);

   assert_true(ds.get_display() == true, LOG);

   ds.set_display(false);

   assert_true(ds.get_display() == false, LOG);
}


void DataSetTest::test_get_data(void) 
{
   message += "test_get_data\n";

   DataSet ds(1,1,1);

   ds.initialize_data(0.0);

   const Matrix<double>& data = ds.get_data();

   assert_true(data.get_rows_number() == 1, LOG);
   assert_true(data.get_columns_number() == 2, LOG);
   assert_true(data == 0.0, LOG);
}


void DataSetTest::test_arrange_training_data(void)
{
   message += "test_arrange_training_data\n";
}


void DataSetTest::test_arrange_generalization_data(void)
{
   message += "test_arrange_generalization_data\n";
}


void DataSetTest::test_arrange_testing_data(void)
{
   message += "test_arrange_testing_data\n";
}


void DataSetTest::test_arrange_input_data(void) 
{
   message += "test_arrange_input_data\n";

   DataSet ds(1, 3, 2);

   unsigned instances_number = ds.get_instances().get_instances_number();
   unsigned inputs_number = ds.get_variables().count_inputs_number();

   Matrix<double> input_data = ds.arrange_input_data();

   unsigned rows_number = input_data.get_rows_number();
   unsigned columns_number = input_data.get_columns_number();

   assert_true(instances_number == rows_number, LOG);
   assert_true(inputs_number == columns_number, LOG);
}


void DataSetTest::test_arrange_target_data(void) 
{
   message += "test_arrange_target_data\n";

   DataSet ds(1,3,2);

   unsigned instances_number = ds.get_instances().get_instances_number();
   unsigned targets_number = ds.get_variables().count_targets_number();

   Matrix<double> target_data = ds.arrange_target_data();

   unsigned rows_number = target_data.get_rows_number();
   unsigned columns_number = target_data.get_columns_number();

   assert_true(instances_number == rows_number, LOG);
   assert_true(targets_number == columns_number, LOG);
}


void DataSetTest::test_get_instance(void)
{
   message += "test_get_instance\n";

   DataSet ds;
   Vector<double> instance;

   // Test

   ds.set(1, 1, 1);
   ds.initialize_data(1.0);

   instance = ds.get_instance(0);

   assert_true(instance.size() == 2, LOG);
   assert_true(instance == 1.0, LOG);

}


void DataSetTest::test_get_training_instance(void)
{
   message += "test_get_training_instance\n";

   DataSet ds;
   Vector<double> training_instance;

   Instances* instances_pointer;

   // Test

   ds.set(1,1,1);
   ds.initialize_data(0.0);
  
   instances_pointer = ds.get_instances_pointer();
   instances_pointer->set_training();

   training_instance = ds.get_training_instance(0);

   assert_true(training_instance.size() == 2, LOG);
   assert_true(training_instance == 0.0, LOG);
}


void DataSetTest::test_get_generalization_instance(void)
{
   message += "test_get_generalization_instance\n";

   DataSet ds;
   Vector<double> generalization_instance;

   Instances* instances_pointer;

   // Test

   ds.set(1,1,1);
   ds.initialize_data(0.0);

   instances_pointer = ds.get_instances_pointer();
   instances_pointer->set_generalization();

   generalization_instance = ds.get_generalization_instance(0);

   assert_true(generalization_instance.size() == 2, LOG);
   assert_true(generalization_instance == 0.0, LOG);
}


void DataSetTest::test_get_testing_instance(void)
{
   message += "test_get_testing_instance\n";

   DataSet ds;
   Vector<double> testing_instance;

   Instances* instances_pointer;

   // Test

   ds.set(1, 1, 1);
   ds.initialize_data(0.0);

   instances_pointer = ds.get_instances_pointer();
   instances_pointer->set_testing();

   testing_instance = ds.get_testing_instance(0);

   assert_true(testing_instance.size() == 2, LOG);
   assert_true(testing_instance == 0.0, LOG);
}


void DataSetTest::test_get_input_instance(void)
{
   message += "test_get_input_instance\n";

   DataSet ds;
   Vector<double> input_instance;

   // Test

   ds.set(1, 1, 1);

   ds.initialize_data(1.0);

   input_instance = ds.get_input_instance(0);

   assert_true(input_instance.size() == 1, LOG);
   assert_true(input_instance == 1.0, LOG);
}


void DataSetTest::test_get_target_instance(void)
{
   message += "test_get_target_instance\n";

   DataSet ds;
   Vector<double> target_instance;

   // Test

   ds.set(1, 1, 1);

   ds.initialize_data(1.0);

   target_instance = ds.get_target_instance(0);

   assert_true(target_instance.size() == 1, LOG);
   assert_true(target_instance == 1.0, LOG);
}


void DataSetTest::test_get_training_input_instance(void) 
{
   message += "test_get_training_input_instance\n";

   DataSet ds;
   Vector<double> training_input_instance;

   Instances* instances_pointer;

   // Test

   ds.set(1, 1, 1);
   ds.initialize_data(0.0);

   instances_pointer = ds.get_instances_pointer();
   instances_pointer->set_training();

   training_input_instance = ds.get_training_input_instance(0);

   assert_true(training_input_instance.size() == 1, LOG);
   assert_true(training_input_instance == 0.0, LOG);
}


void DataSetTest::test_get_training_target_instance(void) 
{
   message += "test_get_training_target_instance\n";

   DataSet ds;
   Vector<double> training_target_instance;

   Instances* instances_pointer;

   // Test

   ds.set(1,1,1);
   ds.initialize_data(0.0);

   instances_pointer = ds.get_instances_pointer();
   instances_pointer->set_training();

   training_target_instance = ds.get_training_target_instance(0);

   assert_true(training_target_instance.size() == 1, LOG);
   assert_true(training_target_instance == 0.0, LOG);
}


void DataSetTest::test_get_generalization_input_instance(void) 
{
   message += "test_get_generalization_input_instance\n";

   DataSet ds;
   Vector<double> generalization_input_instance;

   Instances* instances_pointer;

   // Test

   ds.set(1, 1, 1);
   ds.initialize_data(0.0);

   instances_pointer = ds.get_instances_pointer();
   instances_pointer->set_generalization();

   generalization_input_instance = ds.get_generalization_input_instance(0);

   assert_true(generalization_input_instance.size() == 1, LOG);
   assert_true(generalization_input_instance == 0.0, LOG);
}


void DataSetTest::test_get_generalization_target_instance(void) 
{
   message += "test_get_generalization_target_instance\n";

   DataSet ds;
   Vector<double> generalization_target_instance;

   Instances* instances_pointer;

   // Test

   ds.set(1, 1, 1);
   ds.initialize_data(0.0);

   instances_pointer = ds.get_instances_pointer();
   
   instances_pointer->set_generalization();

   generalization_target_instance = ds.get_generalization_target_instance(0);

   assert_true(generalization_target_instance.size() == 1, LOG);
   assert_true(generalization_target_instance == 0.0, LOG);
}


void DataSetTest::test_get_testing_input_instance(void) 
{
   message += "test_get_testing_input_instance\n";

   DataSet ds;
   Vector<double> testing_input_instance;

   Instances* instances_pointer;

   // Test

   ds.set(1,1,1);
   ds.initialize_data(0.0);

   instances_pointer = ds.get_instances_pointer();
   instances_pointer->set_testing();

   testing_input_instance = ds.get_testing_input_instance(0);

   assert_true(testing_input_instance.size() == 1, LOG);
   assert_true(testing_input_instance == 0.0, LOG);
}


void DataSetTest::test_get_testing_target_instance(void) 
{
   message += "test_get_testing_target_instance\n";

   DataSet ds;
   Vector<double> testing_target_instance;

   Instances* instances_pointer;

   // Test

   ds.set(1, 1, 1);
   ds.initialize_data(0.0);

   instances_pointer = ds.get_instances_pointer();
   instances_pointer->set_testing();

   testing_target_instance = ds.get_testing_target_instance(0);

   assert_true(testing_target_instance.size() == 1, LOG);
   assert_true(testing_target_instance == 0.0, LOG);
}


void DataSetTest::test_set(void) 
{
   message += "test_set\n";

   DataSet ds;

   // Instances and inputs and target variables

   ds.set(1, 2, 3);

   assert_true(ds.get_variables().count_inputs_number() == 1, LOG);
   assert_true(ds.get_variables().count_targets_number() == 2, LOG);
   assert_true(ds.get_instances().get_instances_number() == 3, LOG);

   const Matrix<double>& data = ds.get_data();

   assert_true(data.get_rows_number() == 3, LOG);
   assert_true(data.get_columns_number() == 3, LOG);
}


void DataSetTest::test_set_instances_number(void) 
{
   message += "test_set_instances_number\n";

   DataSet ds(1,1,1);

   ds.set_instances_number(2);

   assert_true(ds.get_instances().get_instances_number() == 2, LOG);
}


void DataSetTest::test_set_variables_number(void) 
{
   message += "test_set_variables_number\n";

   DataSet ds(1, 1);

   ds.set_variables_number(2);

   assert_true(ds.get_variables().get_variables_number() == 2, LOG);
}


void DataSetTest::test_set_display(void) 
{
   message += "test_set_display\n";
}


void DataSetTest::test_set_data(void) 
{
   message += "test_set_data\n";

   DataSet ds(1, 1, 1);

   Matrix<double> new_data(1, 2, 0.0);

   ds.set_data(new_data);

   Matrix<double> data = ds.get_data();

   assert_true(data == new_data, LOG);
}


void DataSetTest::test_set_instance(void)
{
   message += "test_set_instance\n";

   DataSet ds(1, 1, 1);

   Vector<double> new_instance(2, 0.0);

   ds.set_instance(0, new_instance);

   Vector<double> instance = ds.get_instance(0);

   assert_true(instance == new_instance, LOG);
}


void DataSetTest::test_set_training_instance(void)
{
   message += "test_set_training_instance\n";

   DataSet ds;
   Vector<double> new_training_instance;
   Vector<double> training_instance;

   Instances* instances_pointer;

   // Test

   ds.set(1,1,1);

   instances_pointer = ds.get_instances_pointer();
   instances_pointer->set_training();

   new_training_instance.set(2, 0.0);

   ds.set_training_instance(0, new_training_instance);

   training_instance = ds.get_training_instance(0);

   assert_true(training_instance == new_training_instance, LOG);
}


void DataSetTest::test_set_generalization_instance(void)
{
   message += "test_set_generalization_instance\n";

   DataSet ds;
   Vector<double> new_generalization_instance;
   Vector<double> generalization_instance;

   Instances* instances_pointer;

   // Test

   ds.set(1,1,1);

   instances_pointer = ds.get_instances_pointer();
   instances_pointer->set_generalization();

   new_generalization_instance.set(2, 0.0);

   ds.set_generalization_instance(0, new_generalization_instance);

   generalization_instance = ds.get_generalization_instance(0);

   assert_true(generalization_instance == new_generalization_instance, LOG);
}


void DataSetTest::test_set_testing_instance(void)
{
   message += "test_set_testing_instance\n";

   DataSet ds;
   Vector<double> new_testing_instance;
   Vector<double> testing_instance;

   Instances* instances_pointer;

   // Test

   ds.set(1, 1, 1);

   instances_pointer = ds.get_instances_pointer();
   instances_pointer->set_testing();

   new_testing_instance.set(2, 0.0);

   ds.set_testing_instance(0, new_testing_instance);

   testing_instance = ds.get_testing_instance(0);

   assert_true(testing_instance == new_testing_instance, LOG);
}


void DataSetTest::test_set_input_instance(void)
{
   message += "test_set_input_instance\n";
}


void DataSetTest::test_set_target_instance(void)
{
   message += "test_set_target_instance\n";
}


void DataSetTest::test_set_training_input_instance(void)
{
   message += "test_set_training_input_instance\n";

   DataSet ds;
   Vector<double> new_training_input_instance;
   Vector<double> training_input_instance;

   Instances* instances_pointer;

   // Test

   ds.set(1, 1, 1);

   instances_pointer = ds.get_instances_pointer();
   instances_pointer->set_training();

   new_training_input_instance.set(1, 0.0);

   ds.set_training_input_instance(0, new_training_input_instance);

   training_input_instance = ds.get_training_input_instance(0);

   assert_true(training_input_instance == new_training_input_instance, LOG);
}


void DataSetTest::test_set_training_target_instance(void)
{
   message += "test_set_training_target_instance\n";

   DataSet ds;

   Vector<double> new_training_target_instance;
   Vector<double> training_target_instance;

   Instances* instances_pointer;

   // Test

   ds.set(1, 1, 1);

   instances_pointer = ds.get_instances_pointer();
   instances_pointer->set_training();

   new_training_target_instance.set(1, 0.0);

   ds.set_training_target_instance(0, new_training_target_instance);

   training_target_instance = ds.get_training_target_instance(0);

   assert_true(training_target_instance == new_training_target_instance, LOG);
}


void DataSetTest::test_set_generalization_input_instance(void)
{
   message += "test_set_generalization_input_instance\n";

   DataSet ds;
   Vector<double> new_generalization_input_instance;
   Vector<double> generalization_input_instance;

   Instances* instances_pointer;

   // Test

   ds.set(1, 1, 1);

   instances_pointer = ds.get_instances_pointer();
   instances_pointer->set_generalization();

   new_generalization_input_instance.set(1, 0.0);

   ds.set_generalization_input_instance(0, new_generalization_input_instance);

   generalization_input_instance = ds.get_generalization_input_instance(0);

   assert_true(generalization_input_instance == new_generalization_input_instance, LOG);
}


void DataSetTest::test_set_generalization_target_instance(void)
{
   message += "test_set_generalization_target_instance\n";

   DataSet ds;
   Vector<double> new_generalization_target_instance;
   Vector<double> generalization_target_instance;

   Instances* instances_pointer;

   // Test

   ds.set(1, 1, 1);

   instances_pointer = ds.get_instances_pointer();
   instances_pointer->set_generalization();

   new_generalization_target_instance.set(1, 0.0);

   ds.set_generalization_target_instance(0, new_generalization_target_instance);

   generalization_target_instance = ds.get_generalization_target_instance(0);

   assert_true(generalization_target_instance == new_generalization_target_instance, LOG);
}


void DataSetTest::test_set_testing_input_instance(void)
{
   message += "test_set_testing_input_instance\n";

   DataSet ds;

   Vector<double> new_testing_input_instance;
   Vector<double> testing_input_instance;

   Instances* instances_pointer;

   // Test

   ds.set(1, 1, 1);

   instances_pointer = ds.get_instances_pointer();
   instances_pointer->set_testing();

   new_testing_input_instance.set(1, 0.0);

   ds.set_testing_input_instance(0, new_testing_input_instance);

   testing_input_instance = ds.get_testing_input_instance(0);

   assert_true(testing_input_instance == new_testing_input_instance, LOG);
}


void DataSetTest::test_set_testing_target_instance(void)
{
   message += "test_set_testing_target_instance\n";

   DataSet ds;

   Vector<double> new_testing_target_instance;
   Vector<double> testing_target_instance;

   Instances* instances_pointer;

   // Test

   ds.set(1, 1, 1);

   instances_pointer = ds.get_instances_pointer();
   instances_pointer->set_testing();

   new_testing_target_instance.set(1, 0.0);

   ds.set_testing_target_instance(0, new_testing_target_instance);

   testing_target_instance = ds.get_testing_target_instance(0);

   assert_true(testing_target_instance == new_testing_target_instance, LOG);
}


void DataSetTest::test_add_instance(void) 
{
   message += "test_add_instance\n";

   DataSet ds(1,1,1);

   Vector<double> new_instance(2, 0.0);

   ds.add_instance(new_instance);

   assert_true(ds.get_instances().get_instances_number() == 2, LOG);

   Vector<double> instance = ds.get_instance(1);

   assert_true(instance == new_instance, LOG);

}


void DataSetTest::test_subtract_instance(void) 
{
   message += "test_subtract_instance\n";

   DataSet ds(1, 1, 3);

   ds.subtract_instance(1);

   assert_true(ds.get_instances().get_instances_number() == 2, LOG);
}


void DataSetTest::test_calculate_data_statistics(void) 
{
   message += "test_calculate_data_statistics\n";

   DataSet ds(2, 2, 2);

   ds.initialize_data(0.0);

   Vector< Statistics<double> > statistics = ds.calculate_data_statistics();

   assert_true(statistics.size() == 4, LOG);

   assert_true(statistics[0].minimum == 0.0, LOG);
   assert_true(statistics[0].maximum == 0.0, LOG);
   assert_true(statistics[0].mean == 0.0, LOG);
   assert_true(statistics[0].standard_deviation == 0.0, LOG);

   assert_true(statistics[1].minimum == 0.0, LOG);
   assert_true(statistics[1].maximum == 0.0, LOG);
   assert_true(statistics[1].mean == 0.0, LOG);
   assert_true(statistics[1].standard_deviation == 0.0, LOG);

   assert_true(statistics[2].minimum == 0.0, LOG);
   assert_true(statistics[2].maximum == 0.0, LOG);
   assert_true(statistics[2].mean == 0.0, LOG);
   assert_true(statistics[2].standard_deviation == 0.0, LOG);

   assert_true(statistics[3].minimum == 0.0, LOG);
   assert_true(statistics[3].maximum == 0.0, LOG);
   assert_true(statistics[3].mean == 0.0, LOG);
   assert_true(statistics[3].standard_deviation == 0.0, LOG);
}


void DataSetTest::test_calculate_training_instances_statistics(void)
{
   message += "test_calculate_training_instances_statistics\n";

   DataSet ds;
   Vector< Statistics<double> > training_instances_statistics;

   Instances* instances_pointer;

   // Test

   ds.set(2, 2, 2);

   instances_pointer = ds.get_instances_pointer();
   instances_pointer->set_training();

   ds.initialize_data(0.0);

   ds.calculate_training_instances_statistics();

}


void DataSetTest::test_calculate_generalization_instances_statistics(void)
{
   message += "test_calculate_generalization_instances_statistics\n";

   DataSet ds;
   Vector< Statistics<double> > generalization_instances_statistics;

   Instances* instances_pointer;

   // Test

   ds.set(2,2,2);

   instances_pointer = ds.get_instances_pointer();
   instances_pointer->set_generalization();

   ds.initialize_data(0.0);

   generalization_instances_statistics = ds.calculate_generalization_instances_statistics();
}


void DataSetTest::test_calculate_testing_instances_statistics(void)
{
   message += "test_calculate_testing_instances_statistics\n";

   DataSet ds;
   Vector< Statistics<double> > testing_instances_statistics;

   Instances* instances_pointer;

   // Test

   ds.set(2, 2, 2);

   instances_pointer = ds.get_instances_pointer();
   instances_pointer->set_testing();
   
   ds.initialize_data(0.0);

   testing_instances_statistics = ds.calculate_testing_instances_statistics();
}


void DataSetTest::test_calculate_input_variables_statistics(void)
{
   message += "test_calculate_input_variables_statistics\n";
}


void DataSetTest::test_calculate_targets_statistics(void)
{
   message += "test_calculate_targets_statistics\n";
}


void DataSetTest::test_scale_inputs_mean_standard_deviation(void) 
{
   message += "test_scale_inputs_mean_standard_deviation\n";

   DataSet ds;

   Vector< Statistics<double> > inputs_statistics;

   // Test

   ds.set(2, 2, 2);
   ds.randomize_data_normal();

   ds.scale_inputs_mean_standard_deviation();

   inputs_statistics = ds.calculate_inputs_statistics();

   assert_true(inputs_statistics[0].has_mean_zero_standard_deviation_one(), LOG);
}


void DataSetTest::test_scale_targets_mean_standard_deviation(void) 
{
   message += "test_scale_targets_mean_standard_deviation\n";

   DataSet ds;

   Vector< Statistics<double> > targets_statistics;

   // Test

   ds.set(2, 2, 2);
   ds.randomize_data_normal();

   ds.scale_targets_mean_standard_deviation();

   targets_statistics = ds.calculate_targets_statistics();

   assert_true(targets_statistics[0].has_mean_zero_standard_deviation_one(), LOG);
}


void DataSetTest::test_scale_inputs_minimum_maximum(void) 
{
   message += "test_scale_inputs_minimum_maximum\n";

   DataSet ds;

   Vector< Statistics<double> > inputs_statistics;

   // Test

   ds.set(2, 2, 2);
   ds.randomize_data_normal();

   ds.scale_inputs_minimum_maximum();

   inputs_statistics = ds.calculate_inputs_statistics();

   assert_true(inputs_statistics[0].has_minimum_minus_one_maximum_one(), LOG);
}


void DataSetTest::test_scale_targets_minimum_maximum(void) 
{
   message += "test_scale_targets_minimum_maximum\n";

   DataSet ds;

   Vector< Statistics<double> > targets_statistics;

   // Test

   ds.set(2, 2, 2);
   ds.randomize_data_normal();

   ds.scale_targets_minimum_maximum();

   targets_statistics = ds.calculate_targets_statistics();

   assert_true(targets_statistics[0].has_minimum_minus_one_maximum_one(), LOG);
}


void DataSetTest::test_scale_data_minimum_maximum(void)
{
   message += "test_scale_data_minimum_maximum\n";

   DataSet ds;

   Vector< Statistics<double> > data_statistics;

   Matrix<double> data;
   Matrix<double> scaled_data;

    // Test

   ds.set(2,2,2);
   ds.initialize_data(0.0);

   ds.set_display(false);

   data = ds.get_data();

   data_statistics = ds.scale_data_minimum_maximum();

   scaled_data = ds.get_data();

   assert_true(scaled_data == data, LOG);
}


void DataSetTest::test_scale_data_mean_standard_deviation(void)
{
   message += "test_scale_data_mean_standard_deviation\n";

   DataSet ds;

   Vector< Statistics<double> > data_statistics;

   Matrix<double> data;
   Matrix<double> scaled_data;

    // Test

   ds.set(2,2,2);
   ds.initialize_data(0.0);

   ds.set_display(false);

   data = ds.get_data();

   data_statistics = ds.scale_data_mean_standard_deviation();

   scaled_data = ds.get_data();

   assert_true(scaled_data == data, LOG);
}


void DataSetTest::test_unscale_data_mean_standard_deviation(void)
{
   message += "test_unscale_data_mean_standard_deviation\n";
}


void DataSetTest::test_unscale_data_minimum_maximum(void)
{
   message += "test_unscale_data_minimum_maximum\n";
}


void DataSetTest::test_unscale_inputs_mean_standard_deviation(void) 
{
   message += "test_unscale_inputs_mean_standard_deviation\n";
/*
   DataSet ds(2, 2, 2);
   ds.initialize_data(0.0);

   ds.set_display(false);

   Matrix<double> input_data = ds.arrange_input_data();

   Vector<double> mean(2, 0.0);
   Vector<double> standard_deviation(2, 1.0);

   ds.unscale_inputs_mean_standard_deviation(mean, standard_deviation);

   Matrix<double> new_input_data = ds.arrange_input_data();

   assert_true(new_input_data == input_data, LOG);
*/
}


void DataSetTest::test_unscale_targets_mean_standard_deviation(void) 
{
   message += "test_unscale_targets_mean_standard_deviation\n";
   
   DataSet ds(2, 2, 2);
   ds.initialize_data(0.0);

   ds.set_display(false);

   Matrix<double> target_data = ds.arrange_target_data();

   Vector<double> mean(2, 0.0);
   Vector<double> standard_deviation(2, 1.0);

//   ds.unscale_targets_mean_standard_deviation(mean, standard_deviation);

   Matrix<double> new_target_data = ds.arrange_target_data();

   assert_true(new_target_data == target_data, LOG);
}


void DataSetTest::test_unscale_variables_mean_standard_deviation(void) 
{
   message += "test_unscale_variables_mean_standard_deviation\n";
}


void DataSetTest::test_unscale_inputs_minimum_maximum(void) 
{
   message += "test_unscale_inputs_minimum_maximum\n"; 
}


void DataSetTest::test_unscale_targets_minimum_maximum(void) 
{
   message += "test_unscale_targets_minimum_maximum\n";
/*
   DataSet ds(2, 2, 2);
   ds.initialize_data(0.0);

   ds.set_display(false);

   Matrix<double> target_data = ds.arrange_target_data();

   Vector<double> minimum(2, -1.0);
   Vector<double> maximum(2,  1.0);

   ds.unscale_targets_minimum_maximum(minimum, maximum);

   Matrix<double> new_target_data = ds.arrange_target_data();

   assert_true(new_target_data == target_data, LOG);
*/
}


void DataSetTest::test_unscale_variables_minimum_maximum(void) 
{
   message += "test_unscale_variables_minimum_maximum\n"; 
}


void DataSetTest::test_subtract_constant_variables(void)
{
   message += "test_subtract_constant_variables\n"; 

   DataSet ds;

   // Test 

   ds.set(1, 1, 2);

   ds.initialize_data(0.0);

   ds.unuse_constant_variables();

   assert_true(ds.get_variables().count_inputs_number() == 0, LOG);
   assert_true(ds.get_variables().count_targets_number() == 0, LOG);
}


void DataSetTest::test_subtract_repeated_instances(void)
{
   message += "test_subtract_repeated_instances\n"; 
}


void DataSetTest::test_initialize_data(void)
{
   message += "test_initialize_data\n";
}


void DataSetTest::test_to_XML(void) 
{
   message += "test_to_XML\n";

   DataSet ds;

   tinyxml2::XMLDocument* document;

   // Test

   document = ds.to_XML();

   assert_true(document != NULL, LOG);
}


void DataSetTest::test_from_XML(void) 
{
   message += "test_from_XML\n";

   DataSet ds;

   Variables* v = ds.get_variables_pointer();
   Instances* i = ds.get_instances_pointer();

   tinyxml2::XMLDocument* document;
   
   // Test

   document = ds.to_XML();

   ds.from_XML(*document);

   // Test

   ds.set(2, 2);

   v->set_use(0, Variables::Target);
   v->set_use(1, Variables::Unused);

   i->set_use(0, Instances::Unused);
   i->set_use(1, Instances::Testing);

   document = ds.to_XML();

   ds.set();

   ds.from_XML(*document);

   assert_true(v->get_variables_number() == 2, LOG);
   assert_true(v->get_use(0) == Variables::Target, LOG);
   assert_true(v->get_use(1) == Variables::Unused, LOG);
   assert_true(i->get_instances_number() == 2, LOG);
   assert_true(i->get_use(0) == Instances::Unused, LOG);
   assert_true(i->get_use(1) == Instances::Testing, LOG);
}


void DataSetTest::test_print(void) 
{
   message += "test_print\n";

   DataSet ds;

   ds.set_display(false);

//   ds.print();
}


// @todo

void DataSetTest::test_save(void) 
{
   message += "test_save\n";

   std::string file_name = "../data/data_set.xml";

//   DataSet ds;

//   ds.set_display(false);

//   ds.save(file_name);
}


// @todo

void DataSetTest::test_load(void) 
{
   message += "test_load\n";
/*
   std::string file_name = "../data/data_set.xml";
   std::string data_file_name = "../data/data.dat";

   DataSet ds;
   DataSet ds_copy;

   Matrix<double> data;

   // Test

   ds.set();

   ds.save(file_name);
   ds.load(file_name);

   // Test;

   ds.set();

   data.set(1, 2, 0.0);

   data.save(data_file_name);

   ds.set_data_file_name(data_file_name);

   ds.get_variables_pointer()->set_name(0, "x");
   ds.get_variables_pointer()->set_units(0, "[m]");
   ds.get_variables_pointer()->set_description(0, "distance");

   ds.get_variables_pointer()->set_name(1, "y");
   ds.get_variables_pointer()->set_units(1, "[s]");
   ds.get_variables_pointer()->set_description(1, "time");

   ds.save(file_name);
   ds_copy.load(file_name);

   assert_true(ds_copy.get_variables().get_variables_number() == 2, LOG);
   assert_true(ds_copy.get_instances().get_instances_number() == 1, LOG);

   assert_true(ds_copy.get_variables_pointer()->get_name(0) == "x", LOG);
   assert_true(ds_copy.get_variables_pointer()->get_unit(0) == "[m]", LOG);
   assert_true(ds_copy.get_variables_pointer()->get_description(0) == "distance", LOG);

   assert_true(ds_copy.get_variables_pointer()->get_name(1) == "y", LOG);
   assert_true(ds_copy.get_variables_pointer()->get_unit(1) == "[s]", LOG);
   assert_true(ds_copy.get_variables_pointer()->get_description(1) == "time", LOG);
*/
}


void DataSetTest::test_print_data(void)
{
   message += "test_print_data\n";
}


void DataSetTest::test_save_data(void)
{
   message += "test_save_data\n";

   std::string data_file_name = "../data/data.dat";

   DataSet ds(2,2,2);

   ds.set_display(false);

   ds.save_data(data_file_name);
}


void DataSetTest::test_load_data(void) 
{
   message += "test_load_data\n";
 
   std::string data_file_name = "../data/data.dat";

   DataSet ds(2, 2, 2);

   ds.initialize_data(0.0);

   ds.set_display(false);

   ds.save_data(data_file_name);

   ds.load_data(data_file_name);

   Matrix<double> data = ds.get_data();

   assert_true(ds.get_data() == 0.0, LOG);
}


void DataSetTest::test_get_data_statistics(void)
{
   message += "test_get_data_statistics\n";

   DataSet ds(1,1,1);
}


void DataSetTest::test_print_data_statistics(void)
{
   message += "test_print_data_statistics\n";
}


void DataSetTest::test_get_training_instances_statistics(void)
{
   message += "test_get_training_instances_statistics\n";

}


void DataSetTest::test_save_training_instances_statistics(void)
{
   message += "test_save_training_instances_statistics\n";
}


void DataSetTest::test_print_training_instances_statistics(void)
{
   message += "test_print_training_instances_statistics\n";
}


void DataSetTest::test_get_generalization_instances_statistics(void)
{
   message += "test_get_generalization_instances_statistics\n";
}


void DataSetTest::test_save_generalization_instances_statistics(void)
{
   message += "test_save_generalization_instances_statistics\n";
}


void DataSetTest::test_print_generalization_instances_statistics(void)
{
   message += "test_print_generalization_instances_statistics\n";
}


void DataSetTest::test_get_testing_instances_statistics(void)
{
   message += "test_get_testing_instances_statistics\n";
}


void DataSetTest::test_save_testing_instances_statistics(void)
{
   message += "test_save_testing_instances_statistics\n";
}


void DataSetTest::test_print_testing_instances_statistics(void)
{
   message += "test_print_testing_instances_statistics\n";
}


void DataSetTest::test_get_instances_statistics(void)
{
   message += "test_get_instances_statistics\n";
}


void DataSetTest::test_save_instances_statistics(void)
{
   message += "test_save_instances_statistics\n";
}


void DataSetTest::test_print_instances_statistics(void)
{
   message += "test_print_instances_statistics\n";
}


void DataSetTest::run_test_case(void)
{
   message += "Running data set test case...\n";

   // Constructor and destructor methods

   test_constructor();
   test_destructor();

   // Assignment operators methods

   test_assignment_operator();

   // Get methods

   test_get_instances_number();
   test_get_variables_number();
 
   test_get_variables();

   test_get_display();

   // Data methods

   test_get_data();

   test_arrange_training_data();
   test_arrange_generalization_data();
   test_arrange_testing_data();

   test_arrange_input_data();
   test_arrange_target_data();

   // Instance methods

   test_get_instance();

   test_get_training_instance();
   test_get_generalization_instance();
   test_get_testing_instance();

   test_get_input_instance();
   test_get_target_instance();

   test_get_training_input_instance();
   test_get_training_target_instance();

   test_get_generalization_input_instance();
   test_get_generalization_target_instance();

   test_get_testing_target_instance();
   test_get_testing_input_instance();

   // Set methods

   test_set();

   test_set_display();

   // Data methods

   test_set_data();

   test_set_instances_number();
   test_set_variables_number();

   // Instance methods

   test_set_instance();

   test_set_training_instance();
   test_set_generalization_instance();
   test_set_testing_instance();

   test_set_input_instance();
   test_set_target_instance();

   test_set_training_input_instance();
   test_set_training_target_instance();
   
   test_set_generalization_target_instance();
   test_set_generalization_input_instance();

   test_set_testing_input_instance();
   test_set_testing_target_instance();

   // Data resizing methods

   test_add_instance();
   test_subtract_instance();

   test_subtract_constant_variables();
   test_subtract_repeated_instances();

   // Initialization methods

   test_initialize_data();

   // Statistics methods

   test_calculate_data_statistics();

   test_calculate_training_instances_statistics();
   test_calculate_generalization_instances_statistics();
   test_calculate_testing_instances_statistics();

   test_calculate_input_variables_statistics();
   test_calculate_targets_statistics();
  

   // Data scaling

   test_scale_data_mean_standard_deviation();  
   test_scale_data_minimum_maximum(); 

   // Input variables scaling

   test_scale_inputs_mean_standard_deviation();
   test_scale_inputs_minimum_maximum();

   // Target variables scaling

   test_scale_targets_mean_standard_deviation();
   test_scale_targets_minimum_maximum();

   // Input-target variables scaling

   test_scale_data_mean_standard_deviation();
   test_scale_data_minimum_maximum();

   // Data unscaling

   test_unscale_data_mean_standard_deviation();
   test_unscale_data_minimum_maximum();

   // Input variables unscaling

   test_unscale_inputs_mean_standard_deviation();
   test_unscale_inputs_minimum_maximum();

   // Target variables unscaling

   test_unscale_targets_mean_standard_deviation();
   test_unscale_targets_minimum_maximum();

   // Input-target variables unscaling

   test_unscale_variables_mean_standard_deviation();
   test_unscale_variables_minimum_maximum();

   // Serialization methods

   test_to_XML();
   test_from_XML();

   test_print();
   test_save();
   test_load();

   test_print_data();
   test_save_data();
   test_load_data();

   test_get_data_statistics();
   test_print_data_statistics();

   test_get_training_instances_statistics();
   test_print_training_instances_statistics();
   test_save_training_instances_statistics();

   test_get_generalization_instances_statistics();
   test_print_generalization_instances_statistics();
   test_save_generalization_instances_statistics();

   test_get_testing_instances_statistics();
   test_print_testing_instances_statistics();
   test_save_testing_instances_statistics();

   test_get_instances_statistics();
   test_print_instances_statistics();
   test_save_instances_statistics();

   message += "End of data set test case.\n";
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

