/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   P R E C I P I T A T E   D I S S O L U T I O N   M O D E L I N G   A P P L I C A T I O N                    */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// This is an inverse problem. 

// System includes

#include <iostream>
#include <time.h>

// OpenNN includes

#include "../../source/opennn.h"

// Examples includes

#include "precipitate_dissolution.h"

using namespace OpenNN;

int main(void)
{
   std::cout << "OpenNN Exception: Precipitate Dissolution Example\n"
             << "This example is under development." << std::endl;

   return(1);

   try
   {
      std::cout << "OpenNN. Precipitate Dissolution Application." << std::endl;	

//   srand((unsigned)time(NULL));

      // Mathematical model

      PrecipitateDissolution precipitate_dissolution;

      precipitate_dissolution.set_reference_temperature(573.16); // K
      precipitate_dissolution.set_reference_time(1000); // s

      precipitate_dissolution.set_minimum_Vickers_hardness(66.9124);
      precipitate_dissolution.set_maximum_Vickers_hardness(151.9350);


      // Data set 

      DataSet data_set;

      data_set.load_data("../data/precipitate_dissolution/DataAA-2014-T6.dat");

      Variables* variables_pointer = data_set.get_variables_pointer();

	  variables_pointer->set(2, 1);

      variables_pointer->set_name(0, "temperature");
      variables_pointer->set_name(1, "time");
      variables_pointer->set_name(2, "vickers_hardness");

      variables_pointer->set_units(0, "celsius");
      variables_pointer->set_units(1, "s");
      variables_pointer->set_units(2, "none");

	  const Matrix<double> input_data = data_set.arrange_input_data();

      // Neural network

      NeuralNetwork neural_network(1, 3, 1);

	  {   
         // Inputs-outputs information

         neural_network.construct_inputs();

         Inputs* inputs_pointer = neural_network.get_inputs_pointer();

         inputs_pointer->set_name(0, "log(t/t*)");
         inputs_pointer->set_unit(0, "none");

         neural_network.construct_outputs();

         Outputs* outputs_pointer = neural_network.get_outputs_pointer();

         outputs_pointer->set_name(0, "1-f/f0");
         outputs_pointer->set_unit(0, "none");

		 // Multilayer perceptron

         MultilayerPerceptron* multilayer_perceptron_pointer = neural_network.get_multilayer_perceptron_pointer();

		 multilayer_perceptron_pointer->randomize_parameters_normal(0.0, 1.0e-2);

		 // Scaling layer

         neural_network.construct_scaling_layer();

         ScalingLayer* scaling_layer_pointer = neural_network.get_scaling_layer_pointer();

         scaling_layer_pointer->set_minimum(0, -6.0);
         scaling_layer_pointer->set_maximum(0, 6.0);

		 // Unscaling layer

         neural_network.construct_unscaling_layer();

         UnscalingLayer* unscaling_layer_pointer = neural_network.get_unscaling_layer_pointer();

         unscaling_layer_pointer->set_minimum(0, 0.0);
         unscaling_layer_pointer->set_maximum(0, 1.0);

         // Bounding layer

         neural_network.construct_bounding_layer();

         BoundingLayer* bounding_layer_pointer = neural_network.get_bounding_layer_pointer();

         bounding_layer_pointer->set_lower_bound(0, 0.0);
         bounding_layer_pointer->set_upper_bound(0, 1.0);

		 // Independent parameters

         neural_network.construct_independent_parameters();

         IndependentParameters* independent_parameters_pointer = neural_network.get_independent_parameters_pointer();

         independent_parameters_pointer->set_parameters_number(1);
         independent_parameters_pointer->set_name(0, "effective_activation_energy");

         independent_parameters_pointer->set_minimum(0, 100.0);
         independent_parameters_pointer->set_maximum(0, 200.0);

         independent_parameters_pointer->set_lower_bound(0, 0.0);   

		 independent_parameters_pointer->set_parameter(0, 150.0);
	  }

	  precipitate_dissolution.calculate_dependent_variables(neural_network, input_data);

      // Performance functional

      PerformanceFunctional performance_functional(&neural_network);

	  {
         // Objective term

         performance_functional.set_objective_type(PerformanceFunctional::INVERSE_SUM_SQUARED_ERROR_OBJECTIVE);

		 std::cout << performance_functional.calculate_gradient() << std::endl;
	  }

      // Training strategy

      TrainingStrategy training_strategy(&performance_functional);

//      training_strategy.perform_training();

      // Save results

      neural_network.save("../data/AA-7449-T79/NeuralNetworkAA-7449-T79.dat");

//      neural_network.save_expression("../data/AA-7449-T79/ExpressionAA-7449-T79.dat");

//   pd.save_precipitate_dissolution_model("../data/AA-7449-T79/PrecipitateDissolutionModelAA-7449-T79.dat");
//   pd.save_Vickers_hardness_model("../data/AA-7449-T79/VickersHardnessModelOneNeuronAA-7449-T79.dat");
//   pd.save_inverse_Vickers_hardness_test("../data/AA-7449-T79/InverseVickersHardnessTestAA-7449-T79.dat");

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
