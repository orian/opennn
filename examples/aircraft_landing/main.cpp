/****************************************************************************************************************/
/*                                                                                                              */ 
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   A I R C R A F T   L A N D I N G   A P P L I C A T I O N                                                    */
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
#include <math.h>

// OpenNN includes

//#include "../../source/opennn.h"

// TinyXml includes

//#include "../../parsers/tinyxml2/tinyxml2.h"


// Examples includes

//#include "aircraft_landing.h"
//#include "aircraft_landing_solution_error.h"

//using namespace OpenNN;

int main(void)
{

   std::cout << "OpenNN Exception: Aircraft Landing Example\n"
             << "This example is under development." << std::endl;

   try
   {
/*
      std::cout << "OpenNN. Aircraft Landing Application." << std::endl;

      srand((unsigned)time(NULL));

      // Problem parameters

      // Mathematical model

      AircraftLanding aircraft_landing;

      // Neural network

      NeuralNetwork neural_network(1, 3, 1);    

      {
		 neural_network.initialize_parameters_normal(0.0, 0.1);

         // Inputs outptus

         neural_network.construct_inputs();
         Inputs* inputs_pointer = neural_network.get_inputs_pointer();

         inputs_pointer->set_name(0, "time");
         inputs_pointer->set_units(0, "seconds");

         neural_network.construct_outputs();
         Outputs* outputs_pointer = neural_network.get_outputs_pointer();

         outputs_pointer->set_name(0, "elevator_deflection_angle");
         outputs_pointer->set_units(0, "degrees");

         // Scaling layer

         neural_network.construct_scaling_layer();

         ScalingLayer* scaling_layer_pointer = neural_network.get_scaling_layer_pointer();

         scaling_layer_pointer->set_minimum(0, 0.0);
         scaling_layer_pointer->set_maximum(0, 20.0);

         // Unscaling layer

         neural_network.construct_unscaling_layer();

         UnscalingLayer* unscaling_layer_pointer = neural_network.get_unscaling_layer_pointer();

         unscaling_layer_pointer->set_minimum(0, -5.0);
         unscaling_layer_pointer->set_maximum(0,  5.0);

         // Bounding layer

         neural_network.construct_bounding_layer();

         BoundingLayer* bounding_layer_pointer = neural_network.get_bounding_layer_pointer();

         bounding_layer_pointer->set_lower_bound(0, -35.0);
         bounding_layer_pointer->set_upper_bound(0,  15.0);
      }

      // Performance functional 

      PerformanceFunctional performance_functional(&neural_network);

      {
         // Objective term 

         AircraftLandingSolutionError* aircraft_landing_solution_error_pointer = new AircraftLandingSolutionError(&neural_network, &aircraft_landing);

         aircraft_landing_solution_error_pointer->set_solution_error_weight(0, 0.0);
         aircraft_landing_solution_error_pointer->set_solution_error_weight(1, 0.0);
         aircraft_landing_solution_error_pointer->set_solution_error_weight(2, 0.0);
         aircraft_landing_solution_error_pointer->set_solution_error_weight(3, 0.01);

         performance_functional.set_objective_term_pointer(aircraft_landing_solution_error_pointer);

         // Regularization term 

         NeuralParametersNorm* neural_parameters_norm_pointer = new NeuralParametersNorm(&neural_network);

         neural_parameters_norm_pointer->set_neural_parameters_norm_weight(1.0e-3);

         performance_functional.set_regularization_term_pointer(neural_parameters_norm_pointer);

         // Constraints term 

         FinalSolutionsError* final_solutions_error_pointer = new FinalSolutionsError(&neural_network, &aircraft_landing);

         final_solutions_error_pointer->set_target_final_solution(0, 0.0);
         final_solutions_error_pointer->set_target_final_solution(1, 2.0*3.1416/360.0);
         final_solutions_error_pointer->set_target_final_solution(2, 0.0);
         final_solutions_error_pointer->set_target_final_solution(3, 0.0);

         final_solutions_error_pointer->set_final_solution_error_weight(0, 0.0);
         final_solutions_error_pointer->set_final_solution_error_weight(1, 0.001);
         final_solutions_error_pointer->set_final_solution_error_weight(2, 0.0);
         final_solutions_error_pointer->set_final_solution_error_weight(3, 0.001);

         performance_functional.set_constraints_term_pointer(final_solutions_error_pointer);
      }

      // Training strategy

      TrainingStrategy training_strategy(&performance_functional);

      {
         training_strategy.construct_main_training_algorithm(TrainingStrategy::QUASI_NEWTON_METHOD);
      }

      TrainingStrategy::Results training_strategy_results = training_strategy.perform_training();

      // Save results

      aircraft_landing.save("../data/aircraft_landing/aircraft_landing.xml");
      aircraft_landing.save_data(neural_network, "../data/aircraft_landing/aircraft_landing_data.dat");

      neural_network.save("../data/aircraft_landing/neural_network.xml");
      neural_network.save_data("../data/aircraft_landing/neural_network_data.dat");
      neural_network.save_expression("../data/aircraft_landing/expression.txt");

      performance_functional.save("../data/aircraft_landing/performance_functional.xml");
      
      training_strategy.save("../data/aircraft_landing/training_strategy.xml");
      training_strategy_results.save("../data/aircraft_landing/training_strategy_results.dat");
*/
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
