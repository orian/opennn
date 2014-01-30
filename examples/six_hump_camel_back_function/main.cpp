/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   S I X   H U M P   C A M E L   B A C K   F U N C T I O N   A P P L I C A T I O N                            */
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

#include "six_hump_camel_back_function.h"

using namespace OpenNN;

int main(void)
{
   std::cout << "OpenNN Exception: Six Hump Camel Back Function Example\n"
             << "This example is under development." << std::endl;

   return(1);

   try
   {
      std::cout << "OpenNN. Six Hump Camel Back Function Application." << std::endl;

      srand( (unsigned)time( NULL ) );

      // Neural network 

      NeuralNetwork neural_network(2);

      IndependentParameters* independent_parameters_pointer = neural_network.get_independent_parameters_pointer();

      independent_parameters_pointer->set_name(0, "x");
      independent_parameters_pointer->set_name(1, "y");

      Vector<double> independent_parameters_minimum(2, 0.0);
      independent_parameters_minimum[0] = -3.0;
      independent_parameters_minimum[1] = -2.0;
      independent_parameters_pointer->set_minimums(independent_parameters_minimum);

      Vector<double> independent_parameters_maximum(2, 0.0);
      independent_parameters_maximum[0] = 3.0;
      independent_parameters_maximum[1] = 2.0;
      independent_parameters_pointer->set_maximums(independent_parameters_maximum);

      independent_parameters_pointer->randomize_parameters_uniform(independent_parameters_minimum, independent_parameters_maximum);

      independent_parameters_pointer->set_scaling_method(IndependentParameters::MinimumMaximum);

      // Performance functional

      PerformanceFunctional performance_functional(&neural_network);

      performance_functional.set_objective_type(PerformanceFunctional::USER_OBJECTIVE);

      SixHumpCamelBackFunction* six_hump_camel_back_function = new SixHumpCamelBackFunction(&neural_network); 

      performance_functional.set_user_objective_pointer(six_hump_camel_back_function);

      // Training strategy 

      TrainingStrategy training_strategy(&performance_functional);

      training_strategy.set_initialization_type(TrainingStrategy::EVOLUTIONARY_ALGORITHM);

      training_strategy.perform_training();

      // Print minimal argument to screen

      const Vector<double> minimal_argument = independent_parameters_pointer->get_parameters();

      std::cout << "Minimal argument:\n"
	            << minimal_argument << std::endl;

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
