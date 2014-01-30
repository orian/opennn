/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   D E   J O N G   F U N C T I O N   A P P L I C A T I O N                                                    */
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

// OpenNN includes

#include "../../source/opennn.h"

// Examples includes

#include "de_jong_function.h"

using namespace OpenNN;

int main(void)
{
   std::cout << "OpenNN Exception: De Jong Function Example\n"
             << "This example is under development." << std::endl;

   return(1);

   try
   {
      std::cout << "OpenNN. De Jong Function Example." << std::endl;	

      srand((unsigned)time(NULL));

      // Problem parameters 

      unsigned int variables_number = 2;

      // Neural network 

      NeuralNetwork neural_network(variables_number);

      neural_network.randomize_parameters_normal(0.0, 0.1);

	  IndependentParameters* independent_parameters_pointer = neural_network.get_independent_parameters_pointer();

      for(unsigned int i = 0; i < variables_number; i++)
      {
         std::ostringstream buffer;
         buffer << "x" << i+1;
         independent_parameters_pointer->set_name(i, buffer.str());

         independent_parameters_pointer->set_minimum(i, -5.12);
         independent_parameters_pointer->set_maximum(i, 5.12); 
      }

      independent_parameters_pointer->randomize_parameters_uniform(-5.12, 5.12);

      independent_parameters_pointer->set_scaling_method(IndependentParameters::MinimumMaximum);

      // Performance functional

      PerformanceFunctional performance_functional(&neural_network);

      performance_functional.set_objective_type(PerformanceFunctional::USER_OBJECTIVE);

      DeJongFunction* de_Jong_function = new DeJongFunction(&neural_network);

      performance_functional.set_user_objective_pointer(de_Jong_function);
  
      Vector<double> initial_guess(variables_number, 1.0);

      independent_parameters_pointer->set_parameters(initial_guess);
 
      const double performance = performance_functional.calculate_performance();
     
      std::cout << "Performance:\n"
                << performance << std::endl;
             
      const Vector<double> gradient = performance_functional.calculate_gradient();
   
      std::cout << "Gradient:\n"
                << gradient << std::endl;
             
      const Matrix<double> hessian = performance_functional.calculate_Hessian();
   
      std::cout << "Hessian:\n"
                << hessian;

      // Training strategy object

      TrainingStrategy training_strategy(&performance_functional);

      const TrainingStrategy::Results training_strategy_results = training_strategy.perform_training();

      // Print minimal argument 

      const Vector<double> minimal_argument = independent_parameters_pointer->get_parameters();

      std::cout << "Minimal argument:\n"
	            << minimal_argument << std::endl;

      // Save results

      neural_network.save("../data/neural_network.xml");

      training_strategy.save("../data/training_strategy.xml");
      training_strategy_results.save("../data/training_strategy_results.dat");

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
