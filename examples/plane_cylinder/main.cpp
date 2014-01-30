/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   P L A N E - C Y L I N D E R   A P P L I C A T I O N                                                        */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// This is a function optimization problem. 

// System includes

#include <iostream>
#include <time.h>
#include <stdexcept>

// OpenNN includes

#include "../../source/opennn.h"

// Examples includes

#include "plane.h"
#include "cylinder.h"

using namespace OpenNN;

int main(void)
{
   std::cout << "OpenNN Exception: Plane-Cylinder Example\n"
             << "This example is under development." << std::endl;

   return(1);

   try
   {
      std::cout << "OpenNN Neural Network: Plane-Cylinder Application." << std::endl;

      srand( (unsigned)time( NULL ) );

	  // Mathematical models

	  Plane plane;

	  Cylinder cylinder;

      // Neural network

      NeuralNetwork neural_network(2);

      IndependentParameters* independent_parameters_pointer = neural_network.get_independent_parameters_pointer();

      independent_parameters_pointer->set_name(0, "x");
      independent_parameters_pointer->set_name(1, "y");
   
      independent_parameters_pointer->set_minimum(0, -5.12);
      independent_parameters_pointer->set_minimum(1, -5.12);
   
      independent_parameters_pointer->set_maximum(0, 5.12);
      independent_parameters_pointer->set_maximum(1, 5.12);
	  
      independent_parameters_pointer->randomize_parameters_uniform(-5.12, 5.12);

      independent_parameters_pointer->set_scaling_method(IndependentParameters::MinimumMaximum);

      PerformanceFunctional performance_functional(&neural_network);
 
	  {
	     // Objective term

          performance_functional.set_objective_type(PerformanceFunctional::SOLUTIONS_ERROR_OBJECTIVE);

         SolutionsError* objective_term_pointer = performance_functional.get_solutions_error_objective_pointer();

         objective_term_pointer->set_solution_error_weight(0, 1.0e-3);

         // Constraints term

         performance_functional.set_constraints_type(PerformanceFunctional::SOLUTIONS_ERROR_CONSTRAINTS);
	  }

      const unsigned variables_number = independent_parameters_pointer->get_parameters_number();
   
      Vector<double> initial_guess(variables_number, 1.2);

      independent_parameters_pointer->set_parameters(initial_guess);

      // Print initial guess

      std::cout << "Initial guess:\n"
    	        << initial_guess << std::endl;
	          
      // Evaluation
  
      const double performance = performance_functional.calculate_performance();
   
      std::cout << "Performance:\n"
                << performance << std::endl;
             
      // Gradient vector

      const Vector<double> gradient = performance_functional.calculate_gradient();
   
      std::cout << "Gradient:\n"
    	        << gradient << std::endl;            

      // Hessian matrix

      const Matrix<double> hessian = performance_functional.calculate_Hessian();
   
      std::cout << "Hessian:\n"
	            << hessian;

      // Inverse Hessian matrix

      const Matrix<double> inverse_Hessian = performance_functional.calculate_inverse_Hessian();
   
      std::cout << "Inverse Hessian:\n"
                << inverse_Hessian;
             
      // Training strategy 

      TrainingStrategy training_strategy(&performance_functional);

      // Print minimal argument

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
