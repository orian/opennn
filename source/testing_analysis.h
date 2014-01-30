/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   T E S T I N G   A N A L Y S I S   C L A S S   H E A D E R                                                  */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __TESTINGANALYSIS_H__
#define __TESTINGANALYSIS_H__

// System includes

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

// OpenNN includes

#include "vector.h"
#include "matrix.h"

#include "data_set.h"
#include "mathematical_model.h"

#include "neural_network.h"

namespace OpenNN
{

/// This class contains tools for testing neural networks in different learning tasks. 
/// In particular, it can be used for testing function regression, pattern recognition
/// or time series prediction problems.

class TestingAnalysis
{

public:  

   // DEFAULT CONSTRUCTOR

   explicit TestingAnalysis(void);

   // NEURAL NETWORK CONSTRUCTOR

   explicit TestingAnalysis(NeuralNetwork*);

   // MATHEMATICAL MODEL CONSTRUCTOR

   explicit TestingAnalysis(MathematicalModel*);

   // DATA SET CONSTRUCTOR

   explicit TestingAnalysis(DataSet*);

   // NEURAL NETWORK AND DATA SET CONSTRUCTOR

   explicit TestingAnalysis(NeuralNetwork*, DataSet*);

   // NEURAL NETWORK AND MATHEMATICAL MODEL CONSTRUCTOR

   explicit TestingAnalysis(NeuralNetwork*, MathematicalModel*);

   // NEURAL NETWORK, DATA SET AND MATHEMATICAL MODEL CONSTRUCTOR

   explicit TestingAnalysis(NeuralNetwork*, DataSet*, MathematicalModel*);

   // XML CONSTRUCTOR

   explicit TestingAnalysis(const tinyxml2::XMLDocument&);

   // FILE CONSTRUCTOR

   explicit TestingAnalysis(const std::string&);


   // DESTRUCTOR

   virtual ~TestingAnalysis(void);

    // STRUCTURES

    ///
    /// Structure with the results from a linear regression analysis.
    ///

    struct LinearRegressionResults
    {
       /// Intercept, slope and correlation coefficient for each output variable.

       Vector< LinearRegressionParameters<double> > linear_regression_parameters;

       /// Target data from data set and output data from neural network.

       Vector< Matrix<double> > target_output_data;

       void save(const std::string&) const;
    };

   // METHODS

   // Get methods

   NeuralNetwork* get_neural_network_pointer(void) const;
   DataSet* get_data_set_pointer(void) const;
   MathematicalModel* get_mathematical_model_pointer(void) const;

   const bool& get_display(void) const;

   // Set methods

   void set_neural_network_pointer(NeuralNetwork*);
   void set_data_set_pointer(DataSet*);
   void set_mathematical_model_pointer(MathematicalModel*);

   void set_display(const bool&);

   void set_default(void);

   // Checking methods

   void check(void) const;

   // Target and output data methods

   Vector< Matrix<double> > calculate_target_output_data(void) const;

   // Error data methods

   Vector< Matrix<double> > calculate_error_data(void) const;

   Vector< Vector< Statistics<double> > > calculate_error_data_statistics(void) const;
   Vector< Matrix<double> > calculate_error_data_statistics_matrices(void) const;

   Vector< Histogram<double> > calculate_error_data_histograms(const unsigned& = 10) const;

   // Linear regression analysis methods

   Vector< LinearRegressionParameters<double> > calculate_linear_regression_parameters(void) const;

   LinearRegressionResults perform_linear_regression_analysis(void) const;

   // Binary classifcation methods

   Vector<double> calculate_binary_classification_tests(void) const;

   // Confusion methods

   Matrix<unsigned> calculate_confusion_binary_classification(const Matrix<double>&, const Matrix<double>&) const;
   Matrix<unsigned> calculate_confusion_multiple_classification(const Matrix<double>&, const Matrix<double>&) const;

   Matrix<unsigned> calculate_confusion(void) const;

   // Serialization methods 

   std::string to_string(void) const;

   void print(void) const;

   virtual tinyxml2::XMLDocument* to_XML(void) const;
   virtual void from_XML(const tinyxml2::XMLDocument&);

   void save(const std::string&) const;
   void load(const std::string&);


private: 

   // MEMBERS

   /// Pointer to the neural network object to be tested. 

   NeuralNetwork* neural_network_pointer;

   /// Pointer to a data set object.

   DataSet* data_set_pointer;

   /// Pointer to a mathematical model object.

   MathematicalModel* mathematical_model_pointer;

   /// Display messages to screen.
   
   bool display;
};

}

#endif

// OpenNN: Open Neural Networks Library.
// Neural Designer Copyright © 2013 Roberto López and Ismael Santana (Intelnics)
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
