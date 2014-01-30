/****************************************************************************************************************/
/*                                                                                                              */ 
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   B R A C H I S T O C H R O N E   P R O B L E M   A P P L I C A T I O N                                      */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */  
/****************************************************************************************************************/

// This is a classical problem in the calculus of variations,
// which can be seen as an optimal control problem.

// System includes

#include <iostream>
#include <time.h>

// OpenNN includes

#include "../../source/opennn.h"

// Examples includes

#include "descent_time.h"

using namespace OpenNN;

int main(void)
{
   std::cout << "OpenNN Error: Brachistochrone Problem Example.\n"
             << "This example is under development." << std::endl;

   return(1);

   try
   {
      std::cout << "OpenNN. Brachistochrone Problem Application." << std::endl;	

      srand((unsigned)time(NULL));

	  // Problem parameters

      const double xa = 0.0;
	  const double ya = 1.0;

	  const double xb =  1.0;
	  const double yb =  0.0;

      // Mathematical model

      DescentTime descent_time;

      const double small = 1.0e-3;

      descent_time.set_initial_independent_variable(xa+small);
      descent_time.set_final_independent_variable(xb);

      // Neural network

      NeuralNetwork neural_network(1, 3, 1);

      {
          neural_network.randomize_parameters_normal(0.0, 0.1);

         // Inputs

         neural_network.construct_inputs();
            
         Inputs* inputs_pointer = neural_network.get_inputs_pointer();
      
         inputs_pointer->set_name(0, "x");

         // Outputs

         neural_network.construct_outputs();

         Outputs* outputs_pointer = neural_network.get_outputs_pointer();

         outputs_pointer->set_name(0, "y");

         // Conditions layer

         neural_network.construct_conditions_layer();

         ConditionsLayer* conditions_layer_pointer = neural_network.get_conditions_layer_pointer();

	      Vector<double> external_input_values(2);
	      external_input_values[0] = xa;
	      external_input_values[1] = xb;

	      conditions_layer_pointer->set_external_input_values(external_input_values);

	      Matrix<double> output_values(1, 2);
	      output_values[0][0] = ya;
	      output_values[0][1] = yb;

	      conditions_layer_pointer->set_output_values(output_values);

          // Bounding layer 

         neural_network.construct_bounding_layer();

         BoundingLayer* bounding_layer_pointer = neural_network.get_bounding_layer_pointer();

         bounding_layer_pointer->set_upper_bound(0, 0.0-1.0e-3);
      }

      // Performance functional

      PerformanceFunctional performance_functional(&neural_network);

	  {
         // Objective term

         performance_functional.set_objective_type(PerformanceFunctional::FINAL_SOLUTIONS_ERROR_OBJECTIVE);

		 Vector<double> parameters = neural_network.arrange_parameters();

         std::cout << performance_functional.calculate_performance() << std::endl;
		 std::cout << performance_functional.calculate_gradient() << std::endl;
         std::cout << performance_functional.calculate_performance(parameters) << std::endl;
	  }

      // Training strategy object

      TrainingStrategy training_strategy(&performance_functional);

      TrainingStrategy::Results training_strategy_results = training_strategy.perform_training();

      // Save results

      neural_network.save("../data/neural_network.xml");
      neural_network.save_expression("../data/expression.txt");
   
      descent_time.save_data(neural_network, "../data/descent_time.dat");

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
