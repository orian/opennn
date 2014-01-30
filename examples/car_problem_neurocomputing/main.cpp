/****************************************************************************************************************/
/*                                                                                                              */ 
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   C A R   P R O B L E M   N E U R O C O M P U T I N G   A P P L I C A T I O N                                */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */ 
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */  
/****************************************************************************************************************/

// This is a classical optimal control problem.

// System includes

#include <iostream>
#include <time.h>

// OpenNN includes

#include "../../source/opennn.h"

// Examples includes

#include "car_neurocomputing.h"


using namespace OpenNN;

int main(void)
{
   std::cout << "OpenNN Exception: Car Problem Neurocomputing Example\n"
             << "This example is under development." << std::endl;

   return(1);

   try
   {
	  std::cout << "OpenNN. Car Problem Neurocomputing Application." << std::endl;

      srand((unsigned)time(NULL));

      // Problem parameters

	  double maximum_deceleration = -1.0;
	  double maximum_acceleration =  1.0;

      // Mathematical model

      CarNeurocomputing car_neurocomputing;
   
      car_neurocomputing.set_initial_independent_variable(0.0);
      car_neurocomputing.set_final_independent_variable(1.0);
   
      car_neurocomputing.set_initial_dependent_variable(0, 0.0);

      // Neural network

      NeuralNetwork neural_network(1, 3, 1);

	  {
         neural_network.randomize_parameters_normal(0.0, 0.1);

         // Inputs outputs information

         neural_network.construct_inputs();

         Inputs* inputs_pointer = neural_network.get_inputs_pointer();

         inputs_pointer->set_name(0, "time");

         neural_network.construct_outputs();

         Outputs* outputs_pointer = neural_network.get_outputs_pointer();

         outputs_pointer->set_name(0, "acceleration");

		 // Conditions layer

		 // Bounding layer

         neural_network.construct_bounding_layer();

         BoundingLayer* bounding_layer_pointer = neural_network.get_bounding_layer_pointer();

         bounding_layer_pointer->set_lower_bound(0, maximum_deceleration);
         bounding_layer_pointer->set_upper_bound(0, maximum_acceleration);

		 // Independent parameters

         neural_network.construct_independent_parameters();

         IndependentParameters* independent_parameters_pointer = neural_network.get_independent_parameters_pointer();

         independent_parameters_pointer->set_parameters_number(1); 

         independent_parameters_pointer->set_name(0, "final_time");   
         independent_parameters_pointer->set_lower_bound(0, 0.0);

         independent_parameters_pointer->set_parameter(0, 3.1415927);
	  }

      // Performance functional

      PerformanceFunctional performance_functional(&neural_network);

	  {
         // Objective term

          performance_functional.set_objective_type(PerformanceFunctional::INDEPENDENT_PARAMETERS_ERROR_OBJECTIVE);

         IndependentParametersError* independent_parameters_error = performance_functional.get_independent_parameters_error_objective_pointer();

         independent_parameters_error->set_independent_parameter_error_weight(0, 1.0e-3);

		 Vector<double> parameters = neural_network.arrange_parameters();

		 // Constraints term

         performance_functional.set_constraints_type(PerformanceFunctional::FINAL_SOLUTIONS_ERROR_CONSTRAINTS);

         FinalSolutionsError* final_solutions_error_pointer = performance_functional.get_final_solutions_error_constraints_pointer();

		 final_solutions_error_pointer->set_target_final_solution(0, 0.0);

		 final_solutions_error_pointer->set_final_solution_error_weight(0, 1.0);

         std::cout << final_solutions_error_pointer->calculate_performance() << std::endl;
         std::cout << final_solutions_error_pointer->calculate_performance(parameters) << std::endl;
         std::cout << final_solutions_error_pointer->calculate_gradient() << std::endl;
	  }

      // Training strategy

      TrainingStrategy training_strategy(&performance_functional);

	  {
		  // Initialization training algorithm

          training_strategy.set_initialization_type(TrainingStrategy::RANDOM_SEARCH);

		  // Main training algorithm

          training_strategy.set_main_type(TrainingStrategy::QUASI_NEWTON_METHOD);
	  }

      TrainingStrategy::Results training_strategy_results = training_strategy.perform_training();

	  const double final_time = neural_network.get_independent_parameters_pointer()->get_parameter(0);

	  car_neurocomputing.set_final_independent_variable(final_time);

      // Save results 

      car_neurocomputing.save_data(neural_network, "../data/car_neurocomputing_data.dat");

      neural_network.save("../data/neural_network.xml");
      neural_network.load("../data/neural_network.xml");

      neural_network.save_data("../data/neural_network_data.dat");
      neural_network.save_expression("../data/expression.txt");

      performance_functional.save("../data/performance_functional.xml");
      performance_functional.load("../data/performance_functional.xml");

      training_strategy.save("../data/training_strategy.xml");
      training_strategy.load("../data/training_strategy.xml");

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
