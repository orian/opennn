/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: An Open Source Neural Networks C++ Library                                                         */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   M O D E L   S E L E C T I O N   T E S T   C L A S S   H E A D E R                                          */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __MODELSELECTIONTEST_H__
#define __MODELSELECTIONTEST_H__

#include "unit_testing.h"

using namespace OpenNN;


class ModelSelectionTest : public UnitTesting 
{

#define	STRING(x) #x
#define TOSTRING(x) STRING(x)
#define LOG __FILE__ ":" TOSTRING(__LINE__)"\n"

public:

   // GENERAL CONSTRUCTOR

   explicit ModelSelectionTest(void);


   // DESTRUCTOR

   virtual ~ModelSelectionTest(void);


   // METHODS

   // Constructor and destructor methods

   void test_constructor(void);
   void test_destructor(void);

   // Get methods

   void test_get_training_strategy_pointer(void);

   void test_get_hidden_layer_sizes(void);
   void test_get_sample_size(void);

   void test_get_display(void);

   // Set methods

   void test_set_training_strategy_pointer(void);

   void test_set_default(void);

   void test_set_hidden_layer_sizes(void);
   void test_set_sample_size(void);

   void test_set_assays_numbers(void);

   void test_set_display(void);

   // Model order selection methods

   void test_perform_model_order_selection(void);

   // Serialization methods

   void test_to_XML(void);   
   void test_print(void);
   void test_save(void);
   void test_load(void);

   // Unit testing methods

   void run_test_case(void);
};


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
