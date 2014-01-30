/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   D A T A   S E T   C L A S S   H E A D E R                                                                  */
/*                                                                                                              */ 
/*   Roberto Lopez                                                                                              */ 
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __DATASET_H__
#define __DATASET_H__

// System includes

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <stdexcept>
#include <ctime>
#include <exception>

// OpenNN includes

#include "vector.h"
#include "matrix.h"

#include "variables.h"
#include "instances.h"

// TinyXml includes

#include "../tinyxml2/tinyxml2.h"


namespace OpenNN
{

/// This class represents the concept of data set for data modelling problems, 
/// such as function regression, pattern recognition and time series prediction.
/// It basically consists of a data matrix plus a variables and an instances objects. 

class DataSet 
{

public:  

    // DEFAULT CONSTRUCTOR

    explicit DataSet(void);

   // INSTANCES AND VARIABLES CONSTRUCTOR

   explicit DataSet(const unsigned&, const unsigned&);

   // INSTANCES AND INPUT AND TARGET VARIABLES CONSTRUCTOR

   explicit DataSet(const unsigned&, const unsigned&, const unsigned&);

   // XML CONSTRUCTOR

   explicit DataSet(const tinyxml2::XMLDocument&);

   // FILE CONSTRUCTOR

   explicit DataSet(const std::string&);

   // COPY CONSTRUCTOR

   DataSet(const DataSet&);

   // DESTRUCTOR

   virtual ~DataSet(void);

   // ASSIGNMENT OPERATOR

   DataSet& operator = (const DataSet&);

   // EQUAL TO OPERATOR

   bool operator == (const DataSet&) const;

   // ENUMERATIONS

   /// Enumeration of available methods for scaling and unscaling the data.  
   
   enum ScalingUnscalingMethod{MinimumMaximum, MeanStandardDeviation};

   // METHODS

   // Get methods

   const std::string& get_data_file_name(void) const;

   static ScalingUnscalingMethod get_scaling_unscaling_method(const std::string&);

   const Variables& get_variables(void) const;
   Variables* get_variables_pointer(void);

   const Instances& get_instances(void) const;
   Instances* get_instances_pointer(void);

   const bool& get_display(void) const;

   // Data methods

   bool empty(void) const;

   const Matrix<double>& get_data(void) const;

   Matrix<double> arrange_training_data(void) const;
   Matrix<double> arrange_generalization_data(void) const;
   Matrix<double> arrange_testing_data(void) const;

   Matrix<double> arrange_input_data(void) const;
   Matrix<double> arrange_target_data(void) const;

   Matrix<double> arrange_training_input_data(void) const;
   Matrix<double> arrange_training_target_data(void) const;  
   Matrix<double> get_generalization_input_data(void) const;
   Matrix<double> get_generalization_target_data(void) const;
   Matrix<double> arrange_testing_input_data(void) const;
   Matrix<double> arrange_testing_target_data(void) const;

   // Instance methods

   Vector<double> get_instance(const unsigned&) const;

   Vector<double> get_training_instance(const unsigned&) const;
   Vector<double> get_generalization_instance(const unsigned&) const;
   Vector<double> get_testing_instance(const unsigned&) const;

   Vector<double> get_input_instance(const unsigned&) const;
   Vector<double> get_target_instance(const unsigned&) const;

   Vector<double> get_training_input_instance(const unsigned&) const;
   Vector<double> get_training_target_instance(const unsigned&) const;

   Vector<double> get_generalization_input_instance(const unsigned&) const;
   Vector<double> get_generalization_target_instance(const unsigned&) const;

   Vector<double> get_testing_input_instance(const unsigned&) const;
   Vector<double> get_testing_target_instance(const unsigned&) const;

   // Variable methods

   Vector<double> get_variable(const unsigned&) const;

   // Set methods

   void set(void);
   void set(const unsigned&, const unsigned&);
   void set(const unsigned&, const unsigned&, const unsigned&);
   void set(const DataSet&);
   void set(const tinyxml2::XMLDocument&);
   void set(const std::string&);

   // Data methods

   void set_data(const Matrix<double>&);

   void set_instances_number(const unsigned&);
   void set_variables_number(const unsigned&);

   void set_data_file_name(const std::string&);

   // Utilities

   void set_display(const bool&);

   void set_default(void);

   // Instance methods

   void set_instance(const unsigned&, const Vector<double>&);

   void set_training_instance(const unsigned&, const Vector<double>&);
   void set_generalization_instance(const unsigned&, const Vector<double>&);
   void set_testing_instance(const unsigned&, const Vector<double>&);

   void set_input_instance(const unsigned&, const Vector<double>&);
   void set_target_instance(const unsigned&, const Vector<double>&);

   void set_training_input_instance(const unsigned&, const Vector<double>&);
   void set_training_target_instance(const unsigned&, const Vector<double>&);

   void set_generalization_input_instance(const unsigned&, const Vector<double>&);
   void set_generalization_target_instance(const unsigned&, const Vector<double>&);

   void set_testing_input_instance(const unsigned&, const Vector<double>&); 
   void set_testing_target_instance(const unsigned&, const Vector<double>&);

   // Data resizing methods

   void add_instance(const Vector<double>&);
   void subtract_instance(const unsigned&);

   void append_variable(const Vector<double>&);
   void subtract_variable(const unsigned&);

   Vector<unsigned> unuse_constant_variables(void);
   Vector<unsigned> unuse_repeated_instances(void);

   // Initialization methods

   void initialize_data(const double&);

   void randomize_data_uniform(const double& minimum = -1.0, const double& maximum = 1.0);
   void randomize_data_normal(const double& mean = 0.0, const double& standard_deviation = 1.0);

   // Statistics methods

   Vector< Statistics<double> > calculate_data_statistics(void) const;

   Matrix<double> calculate_data_statistics_matrix(void) const;

   Vector< Statistics<double> > calculate_training_instances_statistics(void) const;
   Vector< Statistics<double> > calculate_generalization_instances_statistics(void) const;
   Vector< Statistics<double> > calculate_testing_instances_statistics(void) const;

   Vector< Statistics<double> > calculate_inputs_statistics(void) const;
   Vector< Statistics<double> > calculate_targets_statistics(void) const;
   
   Vector<double> calculate_training_target_data_mean(void) const;
   Vector<double> calculate_generalization_target_data_mean(void) const;
   Vector<double> calculate_testing_target_data_mean(void) const;

   // Correlation methods

   Matrix<double> calculate_linear_correlations(void) const;

   // Histrogram methods

   Vector< Histogram<double> > calculate_data_histograms(const unsigned& = 10) const;

   // Data scaling

   void scale_data_minimum_maximum(const Vector< Statistics<double> >&);
   void scale_data_mean_standard_deviation(const Vector< Statistics<double> >&);

   Vector< Statistics<double> > scale_data_minimum_maximum(void);
   Vector< Statistics<double> > scale_data_mean_standard_deviation(void);

   void scale_data(const std::string&, const Vector< Statistics<double> >&);

   Vector< Statistics<double> > scale_data(const std::string&);

   // Input variables scaling

   void scale_inputs_minimum_maximum(const Vector< Statistics<double> >&);
   Vector< Statistics<double> > scale_inputs_minimum_maximum(void);

   void scale_inputs_mean_standard_deviation(const Vector< Statistics<double> >&);
   Vector< Statistics<double> > scale_inputs_mean_standard_deviation(void);

   Vector< Statistics<double> > scale_inputs(const std::string&);
   void scale_inputs(const std::string&, const Vector< Statistics<double> >&);

   // Target variables scaling

   void scale_targets_minimum_maximum(const Vector< Statistics<double> >&);
   Vector< Statistics<double> > scale_targets_minimum_maximum(void);

   void scale_targets_mean_standard_deviation(const Vector< Statistics<double> >&);
   Vector< Statistics<double> > scale_targets_mean_standard_deviation(void);

   Vector< Statistics<double> > scale_targets(const std::string&);
   void scale_targets(const std::string&, const Vector< Statistics<double> >&);

   // Data unscaling

   void unscale_data_minimum_maximum(const Vector< Statistics<double> >&);
   void unscale_data_mean_standard_deviation(const Vector< Statistics<double> >&);

   // Input variables unscaling

   void unscale_inputs_minimum_maximum(const Vector< Statistics<double> >&);
   void unscale_inputs_mean_standard_deviation(const Vector< Statistics<double> >&);

   // Target variables unscaling

   void unscale_targets_minimum_maximum(const Vector< Statistics<double> >&);
   void unscale_targets_mean_standard_deviation(const Vector< Statistics<double> >&);

   // Pattern recognition methods

   Vector<unsigned> calculate_target_class_distribution(void) const;

   // Serialization methods

   std::string to_string(void) const;

   void print(void) const;

   tinyxml2::XMLDocument* to_XML(void) const;
   void from_XML(const tinyxml2::XMLDocument&);

   void save(const std::string&) const;
   void load(const std::string&);

   void print_data(void) const;

   void save_data(void) const;
   void save_data(const std::string&) const;

   void load_data(void);
   void load_data(const std::string&);

   bool has_data(void) const;

private:

   // MEMBERS

   /// Data file_name 

   std::string data_file_name;

   //std::string column_separator;
   //unsigned header_lines_number;

   /// Data Matrix.

   Matrix<double> data;

   /// Variables object (inputs and target variables).

   Variables variables;

   /// Instances  object (training, generalization and testing instances).

   Instances instances;

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

