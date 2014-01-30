/****************************************************************************************************************/
/*                                                                                                              */ 
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   I S O P E R I M E T R I C   P R O B L E M   A P P L I C A T I O N                                          */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */ 
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */  
/****************************************************************************************************************/

// This is a classical problem in the calculus of variations.

// System includes

#include <iostream>
#include <time.h>

// OpenNN includes

#include "../../source/opennn.h"

// Examples includes

#include "area.h"
#include "perimeter.h"

using namespace OpenNN;

int main(void)
{
   std::cout << "OpenNN Exception: Isoperimetric Problem Example\n"
             << "This example is under development." << std::endl;

   return(1);

   try
   {
      std::cout << "OpenNN. Isoperimetric Problem Application." << std::endl;	

      srand((unsigned)time(NULL));

	  // Mathematical models

 	  Area area;

 	  Perimeter perimeter;

      // Neural network     

      NeuralNetwork neural_network(1, 3, 2);
      {
         // Inputs outputs information

         neural_network.construct_inputs();

         Inputs* inputs_pointer = neural_network.get_inputs_pointer();

         inputs_pointer->set_name(0, "t");

         neural_network.construct_outputs();

         Outputs* outputs_pointer = neural_network.get_outputs_pointer();

         outputs_pointer->set_name(0, "x");
         outputs_pointer->set_name(1, "y");

		 // Scaling layer

		 // Unscaling layer

		 // Conditions layer

		 neural_network.construct_conditions_layer();

		 ConditionsLayer* conditions_layer_pointer = neural_network.get_conditions_layer_pointer();

		 conditions_layer_pointer->set_conditions_method(ConditionsLayer::TwoConditions);

//	     conditions_layer_pointer->set_external_input_value(0, 0.0);
//	     conditions_layer_pointer->set_external_input_value(1, 1.0);

//	     conditions_layer_pointer->set_output_value(0, 0, 0.0);
//	     conditions_layer_pointer->set_output_value(0, 1, 0.0);

//	     neural_network.set_conditions_layer_flag(true);

      }

      // Performance functional

      PerformanceFunctional performance_functional(&neural_network);

	  {
	     // Objective term

         FinalSolutionsError* area_term_pointer = new FinalSolutionsError(&neural_network, &area);      

         std::cout << area_term_pointer->calculate_performance() << std::endl;

         // Constraints term

         FinalSolutionsError* perimeter_error_term_pointer = new FinalSolutionsError(&neural_network, &perimeter);      

         std::cout << perimeter_error_term_pointer->calculate_performance() << std::endl;
	  }

      // Training strategy

      TrainingStrategy training_strategy(&performance_functional);

	  {
		  // Initialization training algorithm

		  // Main training algorithm

	  }
//      TrainingStrategy::Results training_strategy_results = training_strategy.perform_training(); 

      // Save results 

      area.save("../data/area.xml");
      perimeter.save("../data/perimeter.xml");

      neural_network.save("../data/neural_network.xml");
      neural_network.save_data("../data/expression.txt");
      neural_network.save_expression("../data/expression.txt");

      performance_functional.save("../data/performance_functional.xml");

      training_strategy.save("../data/training_strategy.xml");
//      training_strategy_results.save("../data/training_strategy_results.dat");

        return(0);
   }
   catch(std::exception& e)
   {
      std::cerr << e.what() << std::endl;

      return(1);
   }
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
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
