/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   D A T A   S E T   T E S T    C L A S S   H E A D E R                                                       */
/*                                                                                                              */ 
/*   Roberto Lopez                                                                                              */ 
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __DATASETTEST_H__
#define __DATASETTEST_H__

// Unit testing includes

#include "unit_testing.h"

using namespace OpenNN;

class DataSetTest : public UnitTesting 
{

#define STRING(x) #x
#define TOSTRING(x) STRING(x)
#define LOG __FILE__ ":" TOSTRING(__LINE__)"\n"

public:  

   // GENERAL CONSTRUCTOR

   explicit DataSetTest(void);


   // DESTRUCTOR

   virtual ~DataSetTest(void);

    // METHODS

   // Constructor and destructor methods

   void test_constructor(void);
   void test_destructor(void);

   // Assignment operators methods

   void test_assignment_operator(void);

   // Get methods

   void test_get_instances_number(void);
   void test_get_variables_number(void);

   void test_get_variables(void);

   void test_get_display(void);

   // Data methods

   void test_get_data(void);

   void test_arrange_training_data(void);
   void test_arrange_generalization_data(void);
   void test_arrange_testing_data(void);

   void test_arrange_input_data(void);
   void test_arrange_target_data(void);
  
   // Instance methods

   void test_get_instance(void);

   void test_get_training_instance(void);
   void test_get_generalization_instance(void);
   void test_get_testing_instance(void);

   void test_get_input_instance(void);
   void test_get_target_instance(void);

   void test_get_training_input_instance(void);
   void test_get_training_target_instance(void);

   void test_get_generalization_input_instance(void);
   void test_get_generalization_target_instance(void);

   void test_get_testing_input_instance(void); 
   void test_get_testing_target_instance(void);

   // Set methods

   void test_set(void);

   void test_set_instances_number(void);
   void test_set_variables_number(void);

   void test_set_display(void);

   // Data methods

   void test_set_data(void);

   // Instance methods

   void test_set_instance(void);

   void test_set_training_instance(void);
   void test_set_generalization_instance(void);
   void test_set_testing_instance(void);

   void test_set_input_instance(void);
   void test_set_target_instance(void);

   void test_set_training_input_instance(void);
   void test_set_training_target_instance(void);

   void test_set_generalization_input_instance(void); 
   void test_set_generalization_target_instance(void);

   void test_set_testing_input_instance(void);
   void test_set_testing_target_instance(void);

   // Data resizing methods

   void test_add_instance(void);
   void test_subtract_instance(void); 

   void test_subtract_constant_variables(void);
   void test_subtract_repeated_instances(void);

   // Initialization methods

   void test_initialize_data(void);

   // Statistics methods

   void test_calculate_data_statistics(void);

   void test_calculate_training_instances_statistics(void);
   void test_calculate_generalization_instances_statistics(void);
   void test_calculate_testing_instances_statistics(void);

   void test_calculate_input_variables_statistics(void);
   void test_calculate_targets_statistics(void);

   // Data scaling

   void test_scale_data_mean_standard_deviation(void);  
   void test_scale_data_minimum_maximum(void); 

   // Input variables scaling

   void test_scale_inputs_mean_standard_deviation(void);
   void test_scale_inputs_minimum_maximum(void);

   // Target variables scaling

   void test_scale_targets_mean_standard_deviation(void);
   void test_scale_targets_minimum_maximum(void);

   // Input-target variables scaling

   void test_scale_variables_mean_standard_deviation(void);
   void test_scale_variables_minimum_maximum(void);

   // Data unscaling

   void test_unscale_data_mean_standard_deviation(void);
   void test_unscale_data_minimum_maximum(void);

   // Input variables unscaling

   void test_unscale_inputs_mean_standard_deviation(void);
   void test_unscale_inputs_minimum_maximum(void);

   // Target variables unscaling

   void test_unscale_targets_mean_standard_deviation(void);
   void test_unscale_targets_minimum_maximum(void);

   // Input-target variables unscaling

   void test_unscale_variables_mean_standard_deviation(void);
   void test_unscale_variables_minimum_maximum(void);

   // Serialization methods

   void test_to_XML(void);
   void test_from_XML(void);

   void test_print(void);

   void test_save(void);
   void test_load(void);

   void test_print_data(void);
   void test_save_data(void);
   void test_load_data(void);

   void test_get_data_statistics(void);
   void test_print_data_statistics(void);

   void test_get_training_instances_statistics(void);
   void test_print_training_instances_statistics(void);
   void test_save_training_instances_statistics(void);

   void test_get_generalization_instances_statistics(void);
   void test_print_generalization_instances_statistics(void);
   void test_save_generalization_instances_statistics(void);

   void test_get_testing_instances_statistics(void);
   void test_print_testing_instances_statistics(void);
   void test_save_testing_instances_statistics(void);

   void test_get_instances_statistics(void);
   void test_print_instances_statistics(void);
   void test_save_instances_statistics(void);

   // Unit testing methods

   void run_test_case(void);
};

#endif


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
