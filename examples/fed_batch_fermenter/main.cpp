/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   F E D   B A T C H   F E R M E N T E R   A P P L I C A T I O N                                              */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// This is an optimal control problem.

// System includes

#include <iostream>
#include <time.h>

// OpenNN includes

#include "../../source/opennn.h"

// Examples includes

#include "fed_batch_fermenter.h"

using namespace OpenNN;

int main(void)
{
   std::cout << "OpenNN Exception: Fed Batch Fermenter Example\n"
             << "This example is under development." << std::endl;

   return(1);

   try
   {
      std::cout << "OpenNN. Fed Batch Fermenter Application." << std::endl;

      srand((unsigned)time(NULL));

      // Problem parameters

      double fermenter_volume = 200.0; 

      double maximum_feed_rate = 12.0;
      
      double final_time = 54.0;

      // Mathematical model

      FedBatchFermenter fed_batch_fermenter;

      // Neural network

      NeuralNetwork neural_network(1, 2, 1);

	  {
         // Inputs-outputs information

         neural_network.construct_inputs();

         Inputs* inputs_pointer = neural_network.get_inputs_pointer();

         inputs_pointer->set_name(0, "time");
         inputs_pointer->set_unit(0, "seconds");

         neural_network.construct_outputs();

         Outputs* outputs_pointer = neural_network.get_outputs_pointer();

         outputs_pointer->set_name(0, "feed_rate");
         outputs_pointer->set_unit(0, "grams");

		 // Scaling layer 

         neural_network.construct_scaling_layer();

         ScalingLayer* scaling_layer_pointer = neural_network.get_scaling_layer_pointer();

         scaling_layer_pointer->set_minimum(0, 0.0);
         scaling_layer_pointer->set_maximum(0, final_time);

		 // Unscaling layer

         neural_network.construct_unscaling_layer();

         UnscalingLayer* unscaling_layer_pointer = neural_network.get_unscaling_layer_pointer();

         unscaling_layer_pointer->set_minimum(0, 0.0);
         unscaling_layer_pointer->set_maximum(0, maximum_feed_rate);

		 // Bounding layer

         neural_network.construct_bounding_layer();

         BoundingLayer* bounding_layer_pointer = neural_network.get_bounding_layer_pointer();

         bounding_layer_pointer->set_lower_bound(0, 0.0);
         bounding_layer_pointer->set_upper_bound(0, maximum_feed_rate);

         neural_network.randomize_parameters_normal(0.0, 1.0e-3);
	  }

      // Performance functional

      PerformanceFunctional performance_functional(&neural_network);

	  {
         // Objective term 

          performance_functional.set_objective_type(PerformanceFunctional::FINAL_SOLUTIONS_ERROR_OBJECTIVE);

         FinalSolutionsError* objective_term_pointer = performance_functional.get_final_solutions_error_objective_pointer();

         objective_term_pointer->set_final_solution_error_weight(0, 0.0);
         objective_term_pointer->set_final_solution_error_weight(1, 0.0);
         objective_term_pointer->set_final_solution_error_weight(2, -1.0e-9);
         objective_term_pointer->set_final_solution_error_weight(3, 0.0);

		 // Constraints term

         performance_functional.set_constraints_type(PerformanceFunctional::FINAL_SOLUTIONS_ERROR_CONSTRAINTS);

         FinalSolutionsError* constraints_term_pointer = performance_functional.get_final_solutions_error_constraints_pointer();

         constraints_term_pointer->set_target_final_solution(3, fermenter_volume);

         constraints_term_pointer->set_final_solution_error_weight(0, 0.0);
         constraints_term_pointer->set_final_solution_error_weight(1, 0.0);
         constraints_term_pointer->set_final_solution_error_weight(2, 0.0);
         constraints_term_pointer->set_final_solution_error_weight(3, 1.0e-6);
	  }

	  Vector<double> parameters = neural_network.arrange_parameters();

      std::cout << performance_functional.calculate_performance() << std::endl;
      std::cout << performance_functional.calculate_performance(parameters) << std::endl;
      std::cout << performance_functional.calculate_gradient() << std::endl;


      // Training strategy

      TrainingStrategy training_strategy(&performance_functional);

	  {
         // Initialization training algorithm

//         training_strategy.construct_initialization_training_algorithm(TrainingStrategy::EVOLUTIONARY_ALGORITHM);

         // Main training algorithm

         training_strategy.set_main_type(TrainingStrategy::QUASI_NEWTON_METHOD);
	  }

      TrainingStrategy::Results training_strategy_results = training_strategy.perform_training();

      // Save results

      fed_batch_fermenter.save("../data/fed_batch_fermenter.xml");
      fed_batch_fermenter.save_data(neural_network, "../data/fed_batch_fermenter_data.dat");

      neural_network.save("../data/neural_network.xml");
      neural_network.save_expression("../data/expression.txt");
      neural_network.save_data("../data/neural_network_data.dat");

      performance_functional.save("../data/performance_functional.xml");

      training_strategy.save("../data/training_strategy.xml");
      training_strategy_results.save("../data/training_strategy_results.dat");

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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
