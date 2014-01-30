/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   R A S T R I G I N   F U N C T I O N   A P P L I C A T I O N                                                */
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

#include "rastrigin_function.h"

using namespace OpenNN;

int main(void)
{
   std::cout << "OpenNN Exception: Rastrigin Function Example\n"
             << "This example is under development." << std::endl;

   return(1);

   try
   {
      std::cout << "OpenNN. Rastrigin Function Application." << std::endl;

      srand((unsigned)time(NULL));

      // Problem parameters 

      unsigned int variables_number = 3;

      // Neural network

      NeuralNetwork nn(variables_number);

      IndependentParameters* ipp = nn.get_independent_parameters_pointer();

      for(unsigned int i = 0; i < variables_number; i++)
      {
         std::ostringstream buffer;
         buffer << "x" << i+1;
         ipp->set_name(i, buffer.str());

         ipp->set_minimum(i, -5.12);
	     ipp->set_maximum(i, 5.12);  
      }

      ipp->randomize_parameters_uniform(-5.12, 5.12);

      ipp->set_scaling_method(IndependentParameters::MinimumMaximum);

      // Performance functional

      PerformanceFunctional pf(&nn);

      pf.set_objective_type(PerformanceFunctional::USER_OBJECTIVE);

      RastriginFunction* rf = new RastriginFunction(&nn);

      pf.set_user_objective_pointer(rf);

      // Training strategy

      TrainingStrategy ts(&pf);

      ts.set_initialization_type(TrainingStrategy::EVOLUTIONARY_ALGORITHM);

      EvolutionaryAlgorithm* ea = ts.get_evolutionary_algorithm_pointer();
      ea->randomize_population_uniform(-5.12, 5.12);

      ts.set_main_type(TrainingStrategy::QUASI_NEWTON_METHOD);

      ts.perform_training();

      // Print minimal argument 

      const Vector<double> minimal_argument = ipp->get_parameters();

      std::cout << "Minimal argument:" << std::endl
	            << minimal_argument << std::endl;

      nn.save("../data/neural_network.xml");

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
