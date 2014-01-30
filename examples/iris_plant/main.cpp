/****************************************************************************************************************/
/*                                                                                                              */ 
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   I R I S   P L A N T   A P P L I C A T I O N                                                                */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */ 
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */  
/****************************************************************************************************************/

// This is a classical pattern recognition problem.

// System includes

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <time.h>

// OpenNN includes

#include "../../source/opennn.h"

using namespace OpenNN;

int main(void)
{
   try
   {
      std::cout << "OpenNN. Iris Plant Application." << std::endl;	

      srand((unsigned)time(NULL));

      // Data set 
  
      DataSet data_set;

      data_set.load_data("../data/iris_plant.dat");

      // Variables

      Variables* variables_pointer = data_set.get_variables_pointer(); 

      variables_pointer->set_name(0, "sepal_length");
      variables_pointer->set_units(0, "centimeters");
      variables_pointer->set_use(0, Variables::Input);

      variables_pointer->set_name(1, "sepal_width");
      variables_pointer->set_units(1, "centimeters");
      variables_pointer->set_use(1, Variables::Input);

      variables_pointer->set_name(2, "petal_length");
      variables_pointer->set_units(2, "centimeters");
      variables_pointer->set_use(2, Variables::Input);

      variables_pointer->set_name(3, "petal_width");
      variables_pointer->set_units(3, "centimeters");
      variables_pointer->set_use(3, Variables::Input);

      variables_pointer->set_name(4, "iris_setosa");
      variables_pointer->set_use(4, Variables::Target);

      variables_pointer->set_name(5, "iris_versicolour");
      variables_pointer->set_use(5, Variables::Target);

      variables_pointer->set_name(6, "iris_virginica");
      variables_pointer->set_use(6, Variables::Target);

      const Matrix<std::string> inputs_information = variables_pointer->arrange_inputs_information();
      const Matrix<std::string> targets_information = variables_pointer->arrange_targets_information();

	  // Instances 
    
      Instances* instances_pointer = data_set.get_instances_pointer(); 

      instances_pointer->split_random_indices(75.0, 0.0, 25.0);
   
      const Vector< Statistics<double> > inputs_statistics = data_set.scale_inputs_minimum_maximum();

      // Neural network

      NeuralNetwork neural_network(4, 6, 3);

      Inputs* inputs_pointer = neural_network.get_inputs_pointer();

      inputs_pointer->set_information(inputs_information);

      Outputs* outputs_pointer = neural_network.get_outputs_pointer();

      outputs_pointer->set_information(targets_information);

      neural_network.construct_scaling_layer();

	  ScalingLayer* scaling_layer_pointer = neural_network.get_scaling_layer_pointer();

      scaling_layer_pointer->set_statistics(inputs_statistics);

      scaling_layer_pointer->set_scaling_method(ScalingLayer::NoScaling);

      neural_network.construct_probabilistic_layer();

      ProbabilisticLayer* probabilistic_layer_pointer = neural_network.get_probabilistic_layer_pointer();

//      probabilistic_layer_pointer->set_statistics(targets_statistics);

      probabilistic_layer_pointer->set_probabilistic_method(ProbabilisticLayer::Softmax);

      // Performance functional

      PerformanceFunctional performance_functional(&neural_network, &data_set);

      // Training strategy

      TrainingStrategy training_strategy(&performance_functional);

      QuasiNewtonMethod* quasi_Newton_method_pointer = training_strategy.get_quasi_Newton_method_pointer();

      quasi_Newton_method_pointer->set_minimum_performance_increase(1.0e-3);

      TrainingStrategy::Results training_strategy_results = training_strategy.perform_training();

      // Pattern recognition testing
                  
      TestingAnalysis testing_analysis(&neural_network, &data_set);

      const Matrix<unsigned> confusion = testing_analysis.calculate_confusion();

      // Save results

      scaling_layer_pointer->set_scaling_method(ScalingLayer::MinimumMaximum);

      data_set.save("../data/data_set.xml");

      neural_network.save("../data/neural_network.xml");
      neural_network.save_expression("../data/expression.txt");

      training_strategy.save("../data/training_strategy.xml");
      training_strategy_results.save("../data/training_strategy_results.dat");

      confusion.save("../data/confusion.dat");

      return(0);
   }
   catch(std::exception& e)
   {
      std::cout << e.what() << std::endl;

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
