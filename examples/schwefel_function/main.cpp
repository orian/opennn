/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   S C H W E F E L   F U N C T I O N   A P P L I C A T I O N                                                  */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// This is a benchmark function optimization problem. 

// System includes

#include <iostream>
#include <sstream>
#include <time.h>
#include <stdexcept>

// OpenNN includes

#include "../../source/opennn.h"

// Examples includes

#include "schwefel_function.h"


using namespace OpenNN;

int main(void)
{
   std::cout << "OpenNN Exception: Schwefel Function Example\n"
             << "This example is under development." << std::endl;

   return(1);

   try
   {
      std::cout << "OpenNN. Schwefel Function Application." << std::endl;

      srand( (unsigned)time( NULL ) );

      // Problem parameters 

      unsigned int variables_number = 3;

      // Neural network

      NeuralNetwork neural_network(variables_number);

   
      IndependentParameters* independent_parameters_pointer = neural_network.get_independent_parameters_pointer();

      for(unsigned int i = 0; i < variables_number; i++)
      {
         std::ostringstream buffer;
         buffer << "x" << i+1;
         independent_parameters_pointer->set_name(i, buffer.str());

         independent_parameters_pointer->set_minimum(i, -500.0);
         independent_parameters_pointer->set_maximum(i, 500.0); 
      }
   
      independent_parameters_pointer->randomize_parameters_uniform(-500.0, 500.0);
      independent_parameters_pointer->set_scaling_method(IndependentParameters::MinimumMaximum);

      // Schwefel function object

      PerformanceFunctional performance_functional(&neural_network);

      SchwefelFunction schwefel_function(&neural_network);             

      // Training strategy

      TrainingStrategy training_strategy(&performance_functional);

      training_strategy.set_initialization_type(TrainingStrategy::EVOLUTIONARY_ALGORITHM);

      training_strategy.set_main_type(TrainingStrategy::QUASI_NEWTON_METHOD);
  
      TrainingStrategy::Results training_strategy_results = training_strategy.perform_training();
   
      // Print solution to screen

      Vector<double> minimal_argument = independent_parameters_pointer->get_parameters();

      std::cout << "Minimal argument:" << minimal_argument << std::endl;

      // Save results

      neural_network.save("../data/neural_network.xml");

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
