/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   D A T A   S E T   C L A S S                                                                                */
/*                                                                                                              */ 
/*   Roberto Lopez                                                                                              */ 
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// OpenNN includes

#include "data_set.h"


namespace OpenNN
{

// DEFAULT CONSTRUCTOR

/// Default constructor. It creates a data set object with zero instances and zero inputs and target variables. 
/// It also initializes the rest of class members to their default values.

DataSet::DataSet(void)
{
   set();  

   set_default();
}


// GENERAL CONSTRUCTOR

/// Instances and variables number constructor. 
/// It creates a data set object with given instances and variables numbers.
/// All the variables are set as inputs. 
/// It also initializes the rest of class members to their default values.
/// @param new_variables_number Number of variables.
/// @param new_instances_number Number of instances in the data set.

DataSet::DataSet(const unsigned& new_variables_number, const unsigned& new_instances_number)
{
   set(new_variables_number, new_instances_number);

   set_default();
}


// INSTANCES, INPUTS AND TARGETS NUMBERS CONSTRUCTORS

/// Instances number, input variables number and target variables number constructor. 
/// It creates a data set object with given instances and inputs and target variables numbers.
/// It also initializes the rest of class members to their default values.
/// @param new_inputs_number Number of input variables.
/// @param new_targets_number Number of target variables.
/// @param new_instances_number Number of instances in the data set.

DataSet::DataSet(const unsigned& new_inputs_number, const unsigned& new_targets_number, const unsigned& new_instances_number)
{
   set(new_inputs_number, new_targets_number, new_instances_number);

   set_default();
}


// XML CONSTRUCTOR

/// Sets the data set members from a XML document.
/// @param data_set_document TinyXML document containing the member data.

DataSet::DataSet(const tinyxml2::XMLDocument& data_set_document)
{
   set_default();

   from_XML(data_set_document);
}


// FILE CONSTRUCTOR

/// File constructor. It creates a data set object by loading the object members from a XML-type file. 
/// Please mind about the file format. This is specified in the User's Guide.
/// @param file_name Data set file name.

DataSet::DataSet(const std::string& file_name)
{
   set();

   set_default();

   load(file_name);
}


// COPY CONSTRUCTOR

/// Copy constructor. 
/// It creates a copy of an existing inputs targets data set object. 
/// @param other_data_set Data set object to be copied.

DataSet::DataSet(const DataSet& other_data_set)
{
   set_default();

   set(other_data_set);
}


// DESTRUCTOR

/// Destructor. 

DataSet::~DataSet(void)
{
}


// ASSIGNMENT OPERATOR

/// Assignment operator. 
/// It assigns to the current object the members of an existing data set object.
/// @param other_data_set Data set object to be assigned.

DataSet& DataSet::operator = (const DataSet& other_data_set)
{
   if(this != &other_data_set) 
   {
      data_file_name = other_data_set.data_file_name;

      // Data matrix

      data = other_data_set.data;

      // Variables

      variables = other_data_set.variables;

      // Instances

      instances = other_data_set.instances;

      // Utilities

      display = other_data_set.display;
   }

   return(*this);
}


// EQUAL TO OPERATOR

// bool operator == (const DataSet&) const method

/// Equal to operator. 
/// It compares this object with another object of the same class. 
/// It returns true if the members of the two objects have the same values, and false otherwise.
/// @ param other_data_set Data set object to be compared with.

bool DataSet::operator == (const DataSet& other_data_set) const
{
   if(data_file_name == other_data_set.data_file_name
   && data == other_data_set.data
   && variables == other_data_set.variables
   && instances == other_data_set.instances
   && display == other_data_set.display)
   {
      return(true);
   }
   else
   {
      return(false);
   }

}


// METHODS

// const Variables& get_variables(void) const

/// Returns a constant reference to the variables object composing this data set object. 

const Variables& DataSet::get_variables(void) const
{
   return(variables);
}


// Variables* get_variables_pointer(void) const

/// Returns a pointer to the variables object composing this data set object. 

Variables* DataSet::get_variables_pointer(void) 
{
   return(&variables);
}


// const Instances& get_instances(void) const

/// Returns a constant reference to the instances object composing this data set object. 

const Instances& DataSet::get_instances(void) const
{
   return(instances);
}


// Instances* get_instances_pointer(void)

/// Returns a pointer to the variables object composing this data set object. 

Instances* DataSet::get_instances_pointer(void) 
{
   return(&instances);
}


// const bool& get_display(void) const method

/// Returns true if messages from this class can be displayed on the screen,
/// or false if messages from this class can't be displayed on the screen.

const bool& DataSet::get_display(void) const
{
   return(display);   
}


// bool empty(void) const method

/// Returns true if the data matrix is empty, and false otherwise.

bool DataSet::empty(void) const
{
   return(data.empty());
}


// const Matrix<double>& get_data(void) const method

/// Returns a reference to the data matrix in the data set. 
/// The number of rows is equal to the number of instances.
/// The number of columns is equal to the number of variables. 

const Matrix<double>& DataSet::get_data(void) const
{
   return(data);
}


// const std::string& get_data_file_name(void) const method

/// Returns the name of the data file. 

const std::string& DataSet::get_data_file_name(void) const
{
   return(data_file_name);
}


// static ScalingUnscalingMethod get_scaling_unscaling_method(const std::string&) method

/// Returns a value of the scaling-unscaling method enumeration from a string containing the name of that method.
/// @param scaling_unscaling_method String with the name of the scaling and unscaling method.

DataSet::ScalingUnscalingMethod DataSet::get_scaling_unscaling_method(const std::string& scaling_unscaling_method)
{
    if(scaling_unscaling_method == "MinimumMaximum")
    {
        return(MinimumMaximum);
    }
    else if(scaling_unscaling_method == "MeanStandardDeviation")
    {
        return(MeanStandardDeviation);
    }
    else
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: DataSet class.\n"
               << "static ScalingUnscalingMethod get_scaling_unscaling_method(const std::string).\n"
               << "Unknown scaling-unscaling method: " << scaling_unscaling_method << ".\n";

        throw std::logic_error(buffer.str());
    }
}


// Matrix<double> arrange_training_data(void) const method

/// Returns a matrix with the training instances in the data set. 
/// The number of rows is the number of training instances.
/// The number of columns is the number of variables. 

Matrix<double> DataSet::arrange_training_data(void) const
{
   const unsigned variables_number = variables.get_variables_number();
   
   Vector<unsigned> variables_indices(0, 1, variables_number-1);

   const Vector<unsigned> training_indices = instances.arrange_training_indices();

   return(data.arrange_submatrix(training_indices, variables_indices));
}


// Matrix<double> arrange_generalization_data(void) const method

/// Returns a matrix with the generalization instances in the data set. 
/// The number of rows is the number of generalization instances.
/// The number of columns is the number of variables. 

Matrix<double> DataSet::arrange_generalization_data(void) const
{
   const unsigned variables_number = variables.get_variables_number();

   const Vector<unsigned> generalization_indices = instances.arrange_generalization_indices();

   Vector<unsigned> variables_indices(0, 1, variables_number-1);

   return(data.arrange_submatrix(generalization_indices, variables_indices));
}


// Matrix<double> arrange_testing_data(void) const method

/// Returns a matrix with the testing instances in the data set. 
/// The number of rows is the number of testing instances.
/// The number of columns is the number of variables. 

Matrix<double> DataSet::arrange_testing_data(void) const
{
   const unsigned variables_number = variables.get_variables_number();
   Vector<unsigned> variables_indices(0, 1, variables_number-1);

   const Vector<unsigned> testing_indices = instances.arrange_testing_indices();

   return(data.arrange_submatrix(testing_indices, variables_indices));
}


// Matrix<double> arrange_input_data(void) const method

/// Returns a matrix with the input variables in the data set.
/// The number of rows is the number of instances.
/// The number of columns is the number of input variables. 

Matrix<double> DataSet::arrange_input_data(void) const
{
   const unsigned instances_number = instances.get_instances_number();   
   Vector<unsigned> indices(0, 1, instances_number-1);

   const Vector<unsigned> inputs_indices = variables.arrange_inputs_indices();

   return(data.arrange_submatrix(indices, inputs_indices));
}


// Matrix<double> arrange_target_data(void) const method

/// Returns a matrix with the target variables in the data set.
/// The number of rows is the number of instances.
/// The number of columns is the number of target variables. 

Matrix<double> DataSet::arrange_target_data(void) const
{
   const unsigned instances_number = instances.get_instances_number();
   Vector<unsigned> indices(0, 1, instances_number-1);

   const Vector<unsigned> targets_indices = variables.arrange_targets_indices();

   return(data.arrange_submatrix(indices, targets_indices));
}


// Matrix<double> arrange_training_input_data(void) const method

/// Returns a matrix with training instances and input variables.
/// The number of rows is the number of training instances.
/// The number of columns is the number of input variables. 

Matrix<double> DataSet::arrange_training_input_data(void) const
{
   const Vector<unsigned> inputs_indices = variables.arrange_inputs_indices();

   const Vector<unsigned> training_indices = instances.arrange_training_indices();

   return(data.arrange_submatrix(training_indices, inputs_indices));
}


// Matrix<double> arrange_training_target_data(void) const method

/// Returns a matrix with training instances and target variables.
/// The number of rows is the number of training instances.
/// The number of columns is the number of target variables. 

Matrix<double> DataSet::arrange_training_target_data(void) const 
{
   const Vector<unsigned> training_indices = instances.arrange_training_indices();

   const Vector<unsigned> targets_indices = variables.arrange_targets_indices();

   return(data.arrange_submatrix(training_indices, targets_indices));
}


// Matrix<double> get_generalization_input_data(void) const method

/// Returns a matrix with generalization instances and input variables.
/// The number of rows is the number of generalization instances.
/// The number of columns is the number of input variables. 

Matrix<double> DataSet::get_generalization_input_data(void) const
{
   const Vector<unsigned> generalization_indices = instances.arrange_generalization_indices();

   const Vector<unsigned> inputs_indices = variables.arrange_inputs_indices();

   return(data.arrange_submatrix(generalization_indices, inputs_indices));
}


// Matrix<double> get_generalization_target_data(void) const method

/// Returns a matrix with generalization instances and target variables.
/// The number of rows is the number of generalization instances.
/// The number of columns is the number of target variables. 

Matrix<double> DataSet::get_generalization_target_data(void) const
{
   const Vector<unsigned> generalization_indices = instances.arrange_generalization_indices();

   const Vector<unsigned> targets_indices = variables.arrange_targets_indices();

   return(data.arrange_submatrix(generalization_indices, targets_indices));
}


// Matrix<double> arrange_testing_input_data(void) const method

/// Returns a matrix with testing instances and input variables.
/// The number of rows is the number of testing instances.
/// The number of columns is the number of input variables. 

Matrix<double> DataSet::arrange_testing_input_data(void) const
{
   const Vector<unsigned> inputs_indices = variables.arrange_inputs_indices();

   const Vector<unsigned> testing_indices = instances.arrange_testing_indices();

   return(data.arrange_submatrix(testing_indices, inputs_indices));
}


// Matrix<double> arrange_testing_target_data(void) const method

/// Returns a matrix with testing instances and target variables.
/// The number of rows is the number of testing instances.
/// The number of columns is the number of target variables. 

Matrix<double> DataSet::arrange_testing_target_data(void) const
{
   const Vector<unsigned> targets_indices = variables.arrange_targets_indices();

   const Vector<unsigned> testing_indices = instances.arrange_testing_indices();

   return(data.arrange_submatrix(testing_indices, targets_indices));
}


// Vector<double> get_instance(const unsigned&) const method

/// Returns the inputs and target values of a single instance in the data set. 
/// @param i Index of the instance. 

Vector<double> DataSet::get_instance(const unsigned& i) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned instances_number = instances.get_instances_number();

   if(i >= instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "Vector<double> get_instance(const unsigned&) const method.\n"
             << "Index of instance must be less than number of instances.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   // Get instance

   return(data.arrange_row(i));
}


// Vector<double> get_training_instance(const unsigned&) const method

/// Returns the inputs and target values of a single training instance in the data set. 
/// @param training_instance_index Index of the training instance. 

Vector<double> DataSet::get_training_instance(const unsigned& training_instance_index) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 
  
   const unsigned training_instances_number = instances.count_training_instances_number();

   if(training_instance_index >= training_instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "Vector<double> get_training_instance(const unsigned&) const method.\n"
             << "Index of training instance must be less than number of training instances.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   const Vector<unsigned> training_indices = instances.arrange_training_indices();

   return(data.arrange_row(training_indices[training_instance_index]));
}


// Vector<double> get_generalization_instance(const unsigned&) const method

/// Returns the inputs and target values of a single generalization instance in the data set. 
/// @param generalization_instance_index Index of the generalization instance. 

Vector<double> DataSet::get_generalization_instance(const unsigned& generalization_instance_index) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 
 
   const unsigned generalization_instances_number = instances.count_generalization_instances_number();

   if(generalization_instance_index >= generalization_instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "Vector<double> get_generalization_instance(const unsigned&) const method.\n"
             << "Index of generalization instance must be less than number of generalization instances.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   const Vector<unsigned> generalization_indices = instances.arrange_generalization_indices();

   return(data.arrange_row(generalization_indices[generalization_instance_index]));
}


// Vector<double> get_testing_instance(const unsigned&) const method

/// Returns the inputs and target values of a single testing instance in the data set. 
/// @param testing_instance_index Index of the testing instance. 

Vector<double> DataSet::get_testing_instance(const unsigned& testing_instance_index) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned testing_instances_number = instances.count_testing_instances_number();

   if(testing_instance_index >= testing_instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "Vector<double> get_testing_instance(const unsigned&) const method.\n"
             << "Index of testing instance must be less than number of testing instances.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   const Vector<unsigned> testing_indices = instances.arrange_testing_indices();

   return(data.arrange_row(testing_indices[testing_instance_index]));
}


// Vector<double> get_input_instance(const unsigned&) const method

/// Returns a vector with the input values of a single instance in the data set. 
/// @param instance_index Index of the instance. 

Vector<double> DataSet::get_input_instance(const unsigned& instance_index) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned instances_number = instances.get_instances_number();

   if(instance_index >= instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "Vector<double> get_input_instance(const unsigned&) const method.\n"
             << "Index of instance must be less than number of instances.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   const Vector<unsigned> inputs_indices = variables.arrange_inputs_indices();

   return(data.arrange_row(instance_index, inputs_indices));
}


// Vector<double> get_target_instance(const unsigned&) const method

/// Returns a vector with the target values of a single instance in the data set. 
/// @param instance_index Index of the instance. 

Vector<double> DataSet::get_target_instance(const unsigned& instance_index) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned instances_number = instances.get_instances_number();

   if(instance_index >= instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "Vector<double> get_target_instance(const unsigned&) const method.\n"
             << "Index of instance must be less than number of instances.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   const Vector<unsigned> targets_indices = variables.arrange_targets_indices();

   return(data.arrange_row(instance_index, targets_indices));
}



// Vector<double> get_training_input_instance(const unsigned&) const method

/// Returns the input values of a given training instance.
/// @param training_instance_index Index of training instance.

Vector<double> DataSet::get_training_input_instance(const unsigned& training_instance_index) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned training_instances_number = instances.count_training_instances_number();

   if(training_instance_index >= training_instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "Vector<double> get_training_input_instance(const unsigned&) const method.\n"
             << "Index of training instance (" << training_instance_index << ") must be less than number of training instances (" << training_instances_number << ").\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   const Vector<unsigned> inputs_indices = variables.arrange_inputs_indices();

   const Vector<unsigned> training_indices = instances.arrange_training_indices();

   return(data.arrange_row(training_indices[training_instance_index], inputs_indices));
}


// Vector<double> get_generalization_input_instance(const unsigned&) const method

/// Returns the input values of a given generalization instance.
/// @param generalization_instance_index Index of generalization instance.

Vector<double> DataSet::get_generalization_input_instance(const unsigned& generalization_instance_index) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned generalization_instances_number = instances.count_generalization_instances_number();
 
   if(generalization_instance_index >= generalization_instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "Vector<double> get_generalization_input_instance(const unsigned&) const method.\n"
             << "Index of generalization instance must be less than number of generalization instances.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   const Vector<unsigned> inputs_indices = variables.arrange_inputs_indices();

   const Vector<unsigned> generalization_indices = instances.arrange_generalization_indices();

   return(data.arrange_row(generalization_indices[generalization_instance_index], inputs_indices));
}


// Vector<double> get_testing_input_instance(const unsigned&) const method

/// Returns the input values of a given testing instance.
/// @param testing_instance_index Index of testing instance.

Vector<double> DataSet::get_testing_input_instance(const unsigned& testing_instance_index) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned testing_instances_number = instances.count_testing_instances_number();

   if(testing_instance_index >= testing_instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "Vector<double> get_testing_input_instance(const unsigned&) const method.\n"
             << "Index of testing instance must be less than number of testing instances.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   const Vector<unsigned> testing_indices = instances.arrange_testing_indices();

   const Vector<unsigned> inputs_indices = variables.arrange_inputs_indices();

   return(data.arrange_row(testing_indices[testing_instance_index], inputs_indices));
}

   
// Vector<double> get_training_target_instance(const unsigned&) const method

/// Returns the target values of a given training instance.
/// @param training_instance_index Index of training instance.

Vector<double> DataSet::get_training_target_instance(const unsigned& training_instance_index) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned training_instances_number = instances.count_training_instances_number();

   if(training_instance_index >= training_instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "Vector<double> get_training_target_instance(const unsigned&) const method.\n"
             << "Index of training instance must be less than number of training instances.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   const Vector<unsigned> targets_indices = variables.arrange_targets_indices();

   const Vector<unsigned> training_indices = instances.arrange_training_indices();

   return(data.arrange_row(training_indices[training_instance_index], targets_indices));
}


// Vector<double> get_generalization_target_instance(const unsigned&) const method

/// Returns the target values of a given generalization instance.
/// @param generalization_instance_index Index of generalization instance.

Vector<double> DataSet::get_generalization_target_instance(const unsigned& generalization_instance_index) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned generalization_instances_number = instances.count_generalization_instances_number();

   if(generalization_instance_index >= generalization_instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "Vector<double> get_generalization_target_instance(const unsigned&) const method.\n"
             << "Index of generalization instance must be less than number of generalization instances.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   const Vector<unsigned> targets_indices = variables.arrange_targets_indices();

   const Vector<unsigned> generalization_indices = instances.arrange_generalization_indices();

   return(data.arrange_row(generalization_indices[generalization_instance_index], targets_indices));
}


// Vector<double> get_testing_target_instance(const unsigned&) const method

/// Returns the target values of a given testing instance.
/// @param testing_instance_index Index of testing instance.

Vector<double> DataSet::get_testing_target_instance(const unsigned& testing_instance_index) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned testing_instances_number = instances.count_testing_instances_number();

   if(testing_instance_index >= testing_instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "Vector<double> get_testing_target_instance(const unsigned&) const method.\n"
             << "Index of testing instance must be less than number of testing instances.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   const Vector<unsigned> targets_indices = variables.arrange_targets_indices();

   const Vector<unsigned> testing_indices = instances.arrange_testing_indices();

   return(data.arrange_row(testing_indices[testing_instance_index], targets_indices));
}


// Vector<double> get_variable(const unsigned&) const method

/// Returns all the instances of a single variable in the data set. 
/// @param i Index of the variable. 

Vector<double> DataSet::get_variable(const unsigned& i) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned variables_number = variables.get_variables_number();

   if(i >= variables_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "Vector<double> get_variable(const unsigned&) const method.\n"
             << "Index of variable must be less than number of instances.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   // Get variable

   return(data.arrange_column(i));
}


// void set(void) method

/// Sets zero instances and zero variables in the data set. 

void DataSet::set(void)
{
   data_file_name = "";

   data.set();

   variables.set();
   instances.set();

   display = true;
}


// void set(const unsigned&, const unsigned&) method

/// Sets new numbers of instances and variables in the inputs targets data set. 
/// All the instances are set for training. 
/// All the variables are set as inputs. 
/// @param new_variables_number Number of variables.
/// @param new_instances_number Number of instances.

void DataSet::set(const unsigned& new_variables_number, const unsigned& new_instances_number)
{
   data_file_name = "";

   data.set(new_instances_number, new_variables_number);

   instances.set(new_instances_number);

   variables.set(new_variables_number);

   display = true;
}


// void set(const unsigned&, const unsigned&, const unsigned&) method

/// Sets new numbers of instances and inputs and target variables in the data set.
/// The variables in the data set are the number of inputs plus the number of targets. 
///
/// @param new_inputs_number Number of input variables.
/// @param new_targets_number Number of target variables.
/// @param new_instances_number Number of instances.

void DataSet::set(const unsigned& new_inputs_number, const unsigned& new_targets_number, const unsigned& new_instances_number)
{   
   data_file_name = "";

   const unsigned new_variables_number = new_inputs_number + new_targets_number; 

   data.set(new_instances_number, new_variables_number);

   // Variables

   variables.set(new_inputs_number, new_targets_number);

   // Instances

   instances.set(new_instances_number);

   display = true;
}


// void set(const DataSet& other_data_set)

/// Sets the members of this data set object with those from another data set object. 
/// @param other_data_set Data set object to be copied. 

void DataSet::set(const DataSet& other_data_set)
{
   data_file_name = other_data_set.data_file_name;

   data = other_data_set.data;

   variables = other_data_set.variables;

   instances = other_data_set.instances;

   display = other_data_set.display;
}


// void set(const tinyxml2::XMLDocument&) method

/// Sets the data set members from a XML document.
/// @param data_set_document TinyXML document containing the member data.

void DataSet::set(const tinyxml2::XMLDocument& data_set_document)
{
    set_default();

   from_XML(data_set_document);
}


// void set(const std::string&) method

/// Sets the data set members by loading them from a XML file. 
/// @param file_name Data set XML file_name.

void DataSet::set(const std::string& file_name)
{
   load(file_name);
}


// void set_display(const bool&) method

/// Sets a new display value. 
/// If it is set to true messages from this class are to be displayed on the screen;
/// if it is set to false messages from this class are not to be displayed on the screen.
/// @param new_display Display value.

void DataSet::set_display(const bool& new_display)
{
   display = new_display;
}


// void set_default(void) method

/// Sets the default member values:
/// <ul>
/// <li> Display: True.
/// </ul>

void DataSet::set_default(void)
{
   display = true;
}


// void set_data(const Matrix<double>&) method

/// Sets a new data matrix. 
/// The number of rows must be equal to the number of instances.
/// The number of columns must be equal to the number of variables. 
/// Indices of all training, generalization and testing instances and inputs and target variables do not change.
/// @param new_data Data matrix.

void DataSet::set_data(const Matrix<double>& new_data)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned rows_number = new_data.get_rows_number();
   const unsigned instances_number = instances.get_instances_number();

   if(rows_number != instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void set_data(const Matrix<double>&) method.\n"
             << "Number of rows must be equal to number of instances.\n";

	  throw std::logic_error(buffer.str());
   }

   const unsigned columns_number = new_data.get_columns_number();
   const unsigned variables_number = variables.get_variables_number();

   if(columns_number != variables_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void set_data(const Matrix<double>&) method.\n"
             << "Number of columns must be equal to number of variables.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   // Set data
   
   data = new_data;   
}


// void set_data_file_name(const std::string&) method

/// Sets the name of the data file.
/// It also loads the data from that file. 
/// Moreover, it sets the variables and instances objects. 
/// @param new_data_file_name Name of the file containing the data.

void DataSet::set_data_file_name(const std::string& new_data_file_name)
{   
   data_file_name = new_data_file_name;
}


// void set_instances_number(unsigned) method

/// Sets a new number of instances in the data set. 
/// All instances are also set for training. 
/// The indices of the inputs and target variables do not change. 
/// @param new_instances_number Number of instances. 

void DataSet::set_instances_number(const unsigned& new_instances_number)
{
   const unsigned variables_number = variables.get_variables_number();

   data.set(new_instances_number, variables_number);

   instances.set(new_instances_number);
}


// void set_variables_number(unsigned) method

/// Sets a new number of input variables in the data set. 
/// The indices of the training, generalization and testing instances do not change. 
/// All variables are set as inputs. 
/// @param new_variables_number Number of variables. 

void DataSet::set_variables_number(const unsigned& new_variables_number)
{
   const unsigned instances_number = instances.get_instances_number();

   data.set(instances_number, new_variables_number);

   variables.set(new_variables_number);
}


// void set_instance(const unsigned&, const Vector<double>&)

/// Sets new inputs and target values of a single instance in the data set. 
/// @param instance_index Index of the instance. 
/// @param instance New inputs and target values of the instance.

void DataSet::set_instance(const unsigned& instance_index, const Vector<double>& instance)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned instances_number = instances.get_instances_number();

   if(instance_index >= instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void set_instance(const unsigned&, const Vector<double>&) method.\n"
             << "Index of instance must be less than number of instances.\n";

	  throw std::logic_error(buffer.str());
   }

   const unsigned size = instance.size();
   const unsigned variables_number = variables.get_variables_number();

   if(size != variables_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void set_instance(const unsigned&, const Vector<double>&) method.\n"
             << "Size (" << size << ") must be equal to number of variables (" << variables_number << ").\n";

	  throw std::logic_error(buffer.str());
   } 

   #endif

   // Set instance

   data.set_row(instance_index, instance);
}


// void set_training_instance(const unsigned&, const Vector<double>&) method

/// Sets new inputs and target values of a single training instance in the data set. 
/// @param i Index of the training instance. 
/// @param new_training_instance New inputs and target values of the training instance.

void DataSet::set_training_instance(const unsigned& i, const Vector<double>& new_training_instance)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned training_instances_number = instances.count_training_instances_number();

   if(i >= training_instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void set_training_instance(const unsigned&, const Vector<double>&) method.\n"
             << "Training instance index must be less than number of training instances.\n";

	  throw std::logic_error(buffer.str());
   }
   
   #endif

   const Vector<unsigned> training_indices = instances.arrange_training_indices();

   const unsigned index = training_indices[i];

   set_instance(index, new_training_instance);
}


// void set_generalization_instance(const unsigned&, const Vector<double>&) method

/// Sets new inputs and target values of a single generalization instance in the data set. 
/// @param i Index of the generalization instance. 
/// @param new_generalization_instance New inputs and target values of the generalization instance.

void DataSet::set_generalization_instance(const unsigned& i, const Vector<double>& new_generalization_instance)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned generalization_instances_number = instances.count_generalization_instances_number();

   if(i >= generalization_instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void set_generalization_instance(const unsigned&, const Vector<double>&) method.\n"
             << "Generalization instance index must be less than number of generalization instances.\n";

	  throw std::logic_error(buffer.str());
   }
   
   #endif

   const Vector<unsigned> generalization_indices = instances.arrange_generalization_indices();

   const unsigned index = generalization_indices[i];

   set_instance(index, new_generalization_instance);
}


// void set_testing_instance(const unsigned&, const Vector<double>&) method

/// Sets new inputs and target values of a single testing instance in the data set. 
/// @param i Index of the testing instance. 
/// @param new_testing_instance New inputs and target values of the testing instance.

void DataSet::set_testing_instance(const unsigned& i, const Vector<double>& new_testing_instance)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned testing_instances_number = instances.count_testing_instances_number();

   if(i >= testing_instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void set_testing_instance(const unsigned&, const Vector<double>&) method.\n"
             << "Testing instance index must be less than number of testing instances.\n";

	  throw std::logic_error(buffer.str());
   }
   
   #endif

   const Vector<unsigned> testing_indices = instances.arrange_testing_indices();

   const unsigned index = testing_indices[i];

   set_instance(index, new_testing_instance);
}


// void set_input_instance(const unsigned&, const Vector<double>&) method

/// Sets new input values of a single instance in the data set. 
/// @param instance_index Index of the instance. 
/// @param input_instance New input values of the instance.

void DataSet::set_input_instance(const unsigned& instance_index, const Vector<double>& input_instance)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned instances_number = instances.get_instances_number();

   if(instance_index >= instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void set_input_instance(const unsigned&, const Vector<double>&) method.\n"
             << "Index of instance must be less than number of instances.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   const unsigned inputs_number = variables.count_inputs_number();

   #ifndef NDEBUG 

   const unsigned size = input_instance.size();

   if(size != inputs_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void set_input_instance(const unsigned&, const Vector<double>&) method.\n"
             << "Size of inputs instance must be equal to number of input variables.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   const Vector<unsigned> inputs_indices = variables.arrange_inputs_indices();

   unsigned input_variable_index;

   for(unsigned i = 0; i < inputs_number; i++)
   {
      input_variable_index = inputs_indices[i];

      data[instance_index][input_variable_index] = input_instance[i];
   }
}


// void set_target_instance(const unsigned&, const Vector<double>&) method

/// Sets new target values of a single instance in the data set. 
/// @param instance_index Index of the instance. 
/// @param target_instance New target values of the instance.

void DataSet::set_target_instance(const unsigned& instance_index, const Vector<double>& target_instance)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned instances_number = instances.get_instances_number();

   if(instance_index >= instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void set_target_instance(const unsigned&, const Vector<double>&) method.\n"
             << "Index of instance must be less than number of instances.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   const unsigned targets_number = variables.count_targets_number();

   #ifndef NDEBUG 

   const unsigned size = target_instance.size();

   if(size != targets_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void set_target_instance(const unsigned&, const Vector<double>&) method.\n"
             << "Size of targets instance must be equal to number of target variables.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   const Vector<unsigned> targets_indices = variables.arrange_targets_indices();

   unsigned target_variable_index;

   for(unsigned i = 0; i < targets_number; i++)
   {
      target_variable_index = targets_indices[i];

      data[instance_index][target_variable_index] = target_instance[i];
   }
}


// void set_training_input_instance(const unsigned&, const Vector<double>&) method

/// Sets new input values of a single training instance in the data set. 
/// @param i Index of the training instance. 
/// @param new_training_input_instance New input values of that instance.

void DataSet::set_training_input_instance(const unsigned& i, const Vector<double>& new_training_input_instance)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned training_instances_number = instances.count_training_instances_number();

   if(i >= training_instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void set_training_input_instance(const unsigned&, const Vector<double>&) method.\n"
             << "Training instance index must be less than number of training instances.\n";

	  throw std::logic_error(buffer.str());
   }
   
   #endif

   const Vector<unsigned> training_indices = instances.arrange_training_indices();

   const unsigned index = training_indices[i];

   set_input_instance(index, new_training_input_instance);
}


// void set_generalization_input_instance(const unsigned&, const Vector<double>&) method

/// Sets new input values of a single generalization instance in the data set. 
/// @param i Index of the generalization instance. 
/// @param new_generalization_input_instance New input values of that instance.

void DataSet::set_generalization_input_instance(const unsigned& i, const Vector<double>& new_generalization_input_instance)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned generalization_instances_number = instances.count_generalization_instances_number();

   if(i >= generalization_instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void set_generalization_input_instance(const unsigned&, const Vector<double>&) method.\n"
             << "Generalization instance index must be less than number of generalization instances.\n";

	  throw std::logic_error(buffer.str());
   }
   
   #endif

   const Vector<unsigned> generalization_indices = instances.arrange_generalization_indices();

   const unsigned index = generalization_indices[i];

   set_input_instance(index, new_generalization_input_instance);
}


// void set_testing_input_instance(const unsigned&, const Vector<double>&) method

/// Sets new input values of a single testing instance in the data set. 
/// @param i Index of the testing instance. 
/// @param new_testing_input_instance New input values of that instance.

void DataSet::set_testing_input_instance(const unsigned& i, const Vector<double>& new_testing_input_instance)
{   
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned testing_instances_number = instances.count_testing_instances_number();

   if(i >= testing_instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void set_testing_input_instance(const unsigned&, const Vector<double>&) method.\n"
             << "Testing instance index must be less than number of testing instances.\n";

	  throw std::logic_error(buffer.str());
   }
   
   #endif

   const Vector<unsigned> testing_indices = instances.arrange_testing_indices();

   const unsigned index = testing_indices[i];

   set_input_instance(index, new_testing_input_instance);
}


// void set_training_target_instance(const unsigned&, const Vector<double>&) method

/// Sets new target values of a single training instance in the data set. 
/// @param i Index of the training instance. 
/// @param new_training_target_instance New target values of that instance.

void DataSet::set_training_target_instance(const unsigned& i, const Vector<double>& new_training_target_instance)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned training_instances_number = instances.count_training_instances_number();

   if(i >= training_instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void set_training_target_instance(const unsigned&, const Vector<double>&) method.\n"
             << "Training instance index must be less than number of training instances.\n";

	  throw std::logic_error(buffer.str());
   }
   
   #endif

   const Vector<unsigned> training_indices = instances.arrange_training_indices();

   const unsigned index = training_indices[i];

   set_target_instance(index, new_training_target_instance);
}


// void set_generalization_target_instance(const unsigned&, const Vector<double>&) method

/// Sets new target values of a single generalization instance in the data set. 
/// @param i Index of the generalization instance. 
/// @param new_generalization_target_instance New target values of that instance.

void DataSet::set_generalization_target_instance(const unsigned& i, const Vector<double>& new_generalization_target_instance)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned generalization_instances_number = instances.count_generalization_instances_number();

   if(i >= generalization_instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void set_generalization_target_instance(const unsigned&, const Vector<double>&) method.\n"
             << "Generalization instance index must be less than number of generalization instances.\n";

	  throw std::logic_error(buffer.str());
   }
   
   #endif

   const Vector<unsigned> generalization_indices = instances.arrange_generalization_indices();

   const unsigned index = generalization_indices[i];

   set_target_instance(index, new_generalization_target_instance);
}


// void set_testing_target_instance(const unsigned&, const Vector<double>&) method

/// Sets new target values of a single testing instance in the data set. 
/// @param i Index of the testing instance. 
/// @param new_testing_target_instance New target values of that instance.

void DataSet::set_testing_target_instance(const unsigned& i, const Vector<double>& new_testing_target_instance)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned testing_instances_number = instances.count_testing_instances_number();

   if(i >= testing_instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void set_testing_target_instance(const unsigned&, const Vector<double>&) method.\n"
             << "Testing instance index must be less than number of testing instances.\n";

	  throw std::logic_error(buffer.str());
   }
   
   #endif

   const Vector<unsigned> testing_indices = instances.arrange_testing_indices();

   const unsigned index = testing_indices[i];

   set_target_instance(index, new_testing_target_instance);
}


// void add_instance(const Vector<double>&) method

/// Adds a new instance to the data matrix from a vector of real numbers.
/// The size of that vector must be equal to the number of variables. 
/// Note that resizing is here necessary and therefore computationally expensive. 
/// All instances are also set for training. 
/// @param instance Input and target values of the instance to be added. 

void DataSet::add_instance(const Vector<double>& instance)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned size = instance.size();
   const unsigned variables_number = variables.get_variables_number();

   if(size != variables_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void add_instance(const Vector<double>&) method.\n"
             << "Size of instance must be equal to number of variables.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   const unsigned instances_number = instances.get_instances_number();

   data.append_row(instance);

   instances.set(instances_number+1);
}


// void subtract_instance(unsigned) method

/// Substracts the inputs-targets instance with a given index from the data set.
/// All instances are also set for training. 
/// Note that resizing is here necessary and therefore computationally expensive. 
/// @param instance_index Index of instance to be removed. 

void DataSet::subtract_instance(const unsigned& instance_index)
{
    const unsigned instances_number = instances.get_instances_number();

   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(instance_index >= instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void subtract_instance(unsigned) method.\n"
             << "Index of instance must be less than number of instances.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   data.subtract_row(instance_index);

   instances.set_instances_number(instances_number-1);

}


// void append_variable(const Vector<double>&) method

/// Appends a variable with given values to the data matrix.
/// @param variable Vector of values. The size must be equal to the number of instances. 

void DataSet::append_variable(const Vector<double>& variable)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned size = variable.size();
   const unsigned instances_number = instances.get_instances_number();

   if(size != instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void append_variable(const Vector<double>&) method.\n"
             << "Size of variable must be equal to number of instances.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   const unsigned variables_number = variables.get_variables_number();

   data.append_column(variable);

   Matrix<double> new_data(data);

   const unsigned new_variables_number = variables_number + 1;

   set_variables_number(new_variables_number);

   set_data(new_data);
}


// void subtract_variable(unsigned) method

/// Removes a variable with given index from the data matrix.
/// @param variable_index Index of variable to be subtracted. 

void DataSet::subtract_variable(const unsigned& variable_index)
{
   const unsigned variables_number = variables.get_variables_number();

   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(variable_index >= variables_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void subtract_variable(unsigned) method.\n"
             << "Index of variable must be less than number of variables.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   data.subtract_column(variable_index);

   Matrix<double> new_data(data);

   const unsigned new_variables_number = variables_number - 1;

   set_variables_number(new_variables_number);

   set_data(new_data);
}


// Vector<unsigned> unuse_constant_variables(void) method

/// Removes the input of target indices of that variables with zero standard deviation.
/// It might change the size of the vectors containing the inputs and targets indices. 

Vector<unsigned> DataSet::unuse_constant_variables(void)
{
   const unsigned variables_number = variables.get_variables_number();   

   // Control sentence (if debug)

   #ifndef NDEBUG

   if(variables_number == 0)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "Vector<unsigned> unuse_constant_variables(void) method.\n"
             << "Number of variables is zero.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   Vector<unsigned> constant_variables;

   for(unsigned i = 0; i < variables_number; i++)
   {
      if(variables.get_use(i) != Variables::Unused
      && data.arrange_column(i).is_constant())
      {
         variables.set_use(i, Variables::Unused);
         constant_variables.push_back(i);
	  }
   }

   return(constant_variables);
}


// Vector<unsigned> unuse_repeated_instances(void) method

/// Removes the training, generalization and testing indices of that instances which are repeated in the data matrix.
/// It might change the size of the vectors containing the training, generalization and testing indices. 

Vector<unsigned> DataSet::unuse_repeated_instances(void)
{
	const unsigned instances_number = instances.get_instances_number();

    // Control sentence (if debug)

    #ifndef NDEBUG

    if(instances_number == 0)
    {
       std::ostringstream buffer;

       buffer << "OpenNN Exception: DataSet class.\n"
              << "Vector<unsigned> unuse_repeated_indices(void) method.\n"
              << "Number of instances is zero.\n";

       throw std::logic_error(buffer.str());
    }

    #endif

    Vector<unsigned> repeated_instances;

	Vector<double> instance_i;
	Vector<double> instance_j;    

	for(unsigned i = 0; i < instances_number; i++)
	{
	   instance_i = get_instance(i);

	   for(unsigned j = i+1; j < instances_number; j++)
	   {	      
          instance_j = get_instance(j);

          if(instances.get_use(j) != Instances::Unused
          && instance_j == instance_i)
		  {
              instances.set_use(j, Instances::Unused);
              repeated_instances.push_back(j);
		  }
	   }	    
	}

    return(repeated_instances);
}


// Vector<Histogram> calculate_data_histograms(const unsigned&) const method

/// Returns a histogram for each variable with a given number of bins. 
/// The default number of bins is 10.
/// The format is a vector of subvectors of subsubvectors.
/// The size of the vector is the number of variables. 
/// The size of the subvectors is 2 (centers and frequencies).
/// The size of the subsubvectors is the number of bins.
/// @param bins_number Number of bins.

Vector< Histogram<double> > DataSet::calculate_data_histograms(const unsigned& bins_number) const
{
   return(data.calculate_histograms(bins_number));
}


// Vector< Vector<double> > calculate_data_statistics(void) const method

/// Returns a vector of vectors containing some basic statistics of all the variables in the data set. 
/// The size of this vector is four. The subvectors are:
/// <ul>
/// <li> Minimum.
/// <li> Maximum.
/// <li> Mean.
/// <li> Standard deviation.
/// </ul> 

Vector< Statistics<double> > DataSet::calculate_data_statistics(void) const
{
   return(data.calculate_statistics());
}


// Matrix<double> calculate_data_statistics_matrix(void) const method

/// Returns all the variables statistics from a single matrix.
/// The number of rows is the number of variables.
/// The number of columns is four (minimum, maximum, mean and standard deviation).

Matrix<double> DataSet::calculate_data_statistics_matrix(void) const
{
    const Vector< Statistics<double> > data_statistics = calculate_data_statistics();

    const unsigned variables_number = data_statistics.size();

    Matrix<double> data_statistics_matrix(variables_number, 4);

    for(unsigned i = 0; i < variables_number; i++)
    {
        data_statistics_matrix.set_row(i, data_statistics[i].to_vector());
    }

    return(data_statistics_matrix);
}


// Vector< Statistics<double> > calculate_training_instances_statistics(void) const method

/// Returns a vector of vectors containing some basic statistics of all variables on the training instances. 
/// The size of this vector is four. The subvectors are:
/// <ul>
/// <li> Training data mean.
/// <li> Training data standard deviation.
/// <li> Training data minimum.
/// <li> Training data maximum.
/// </ul> 

Vector< Statistics<double> > DataSet::calculate_training_instances_statistics(void) const
{
   const Vector<unsigned> training_indices = instances.arrange_training_indices();

   return(data.calculate_rows_statistics(training_indices));
}


// Vector< Statistics<double> > calculate_generalization_instances_statistics(void) const method

/// Returns a vector of vectors containing some basic statistics of all variables on the generalization instances. 
/// The size of this vector is four. The subvectors are:
/// <ul>
/// <li> Generalization data mean.
/// <li> Generalization data standard deviation.
/// <li> Generalization data minimum.
/// <li> Generalization data maximum.
/// </ul> 

Vector< Statistics<double> > DataSet::calculate_generalization_instances_statistics(void) const
{
   const Vector<unsigned> generalization_indices = instances.arrange_generalization_indices();

   return(data.calculate_rows_statistics(generalization_indices));
}


// Vector< Statistics<double> > calculate_testing_instances_statistics(void) const method

/// Returns a vector of vectors containing some basic statistics of all variables on the testing instances. 
/// The size of this vector is four. The subvectors are:
/// <ul>
/// <li> Testing data mean.
/// <li> Testing data standard deviation.
/// <li> Testing data minimum.
/// <li> Testing data maximum.
/// </ul> 

Vector< Statistics<double> > DataSet::calculate_testing_instances_statistics(void) const
{
   const Vector<unsigned> testing_indices = instances.arrange_testing_indices();

   return(data.calculate_rows_statistics(testing_indices));
}


// Vector< Statistics<double> > calculate_inputs_statistics(void) const method

/// Returns a vector of vectors with some basic statistics of the input variables on all instances. 
/// The size of this vector is four. The subvectors are:
/// <ul>
/// <li> Input variables mean.
/// <li> Input variables standard deviation.
/// <li> Input variables minimum.
/// <li> Input variables maximum.
/// </ul> 

Vector< Statistics<double> > DataSet::calculate_inputs_statistics(void) const
{
   const Vector<unsigned> inputs_indices = variables.arrange_inputs_indices();

   return(data.calculate_columns_statistics(inputs_indices));
}


// Vector< Statistics<double> > calculate_targets_statistics(void) const method

/// Returns a vector of vectors with some basic statistics of the target variables on all instances. 
/// The size of this vector is four. The subvectors are:
/// <ul>
/// <li> Target variables mean.
/// <li> Target variables standard deviation.
/// <li> Target variables minimum.
/// <li> Target variables maximum.
/// </ul> 

Vector< Statistics<double> > DataSet::calculate_targets_statistics(void) const
{
   const Vector<unsigned> targets_indices = variables.arrange_targets_indices();

   return(data.calculate_columns_statistics(targets_indices));
}


// Vector<double> calculate_training_target_data_mean(void) const method

/// Returns the mean values of the target variables on the training instances. 

Vector<double> DataSet::calculate_training_target_data_mean(void) const
{
   const Vector<unsigned> targets_indices = variables.arrange_targets_indices();

   const Vector<unsigned> training_indices = instances.arrange_training_indices();

   return(data.calculate_mean(training_indices, targets_indices));
}


// Vector<double> calculate_generalization_target_data_mean(void) const method

/// Returns the mean values of the target variables on the generalization instances. 

Vector<double> DataSet::calculate_generalization_target_data_mean(void) const
{
   const Vector<unsigned> targets_indices = variables.arrange_targets_indices();

   const Vector<unsigned> generalization_indices = instances.arrange_generalization_indices();

   return(data.calculate_mean(generalization_indices, targets_indices));
}


// Vector<double> calculate_testing_target_data_mean(void) const method

/// Returns the mean values of the target variables on the testing instances. 

Vector<double> DataSet::calculate_testing_target_data_mean(void) const
{
   const Vector<unsigned> testing_indices = instances.arrange_testing_indices();

   const Vector<unsigned> targets_indices = variables.arrange_targets_indices();

   return(data.calculate_mean(testing_indices, targets_indices));
}


// Matrix<double> calculate_linear_correlations(void) const method

/// Calculates the linear correlations between all outputs and all inputs.
/// It returns a matrix with number of rows the targets number and number of columns the inputs number.
/// Each element contains the linear correlation between a single target and a single output.

Matrix<double> DataSet::calculate_linear_correlations(void) const
{
   const unsigned inputs_number = variables.count_inputs_number();
   const unsigned targets_number = variables.count_targets_number();

   const Vector<unsigned> input_indices = variables.arrange_inputs_indices();
   const Vector<unsigned> target_indices = variables.arrange_targets_indices();

   unsigned input_index;
   unsigned target_index;

   const unsigned instances_number = instances.get_instances_number();

   Vector<double> input_variable(instances_number);
   Vector<double> target_variable(instances_number);

   Matrix<double> linear_correlations(targets_number, inputs_number);

   for(unsigned i = 0; i < targets_number; i++)
   {
       target_index = target_indices[i];

       target_variable = data.arrange_column(target_index);

       for(unsigned j = 0; j < inputs_number; j++)
       {
           input_index = input_indices[i];

           input_variable = data.arrange_column(input_index);

           linear_correlations[i][j] = target_variable.calculate_linear_correlation(input_variable);
       }
   }

   return(linear_correlations);
}


// void scale_data_mean_standard_deviation(const Vector< Statistics<double> >&) const method

/// Scales the data matrix with given mean and standard deviation values.
/// It updates the data matrix.
/// @param data_statistics Vector of statistics structures for all the variables in the data set.
/// The size of that vector must be equal to the number of variables.

void DataSet::scale_data_mean_standard_deviation(const Vector< Statistics<double> >& data_statistics)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   std::ostringstream buffer;

   const unsigned columns_number = data.get_columns_number();

   const unsigned statistics_size = data_statistics.size();

   if(statistics_size != columns_number)
   {
      buffer << "OpenNN Exception: DataSet class.\n"
             << "void scale_data_mean_standard_deviation(const Vector< Statistics<double> >&) method.\n"
             << "Size of statistics must be equal to number of columns.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   const unsigned variables_number = variables.get_variables_number();

   for(unsigned i = 0; i < variables_number; i++)
   {
       if(display && data_statistics[i].standard_deviation < 1.0e-99)
       {
          std::cout << "OpenNN Warning: DataSet class.\n"
                    << "void scale_data_mean_standard_deviation(const Vector< Statistics<Type> >&) method.\n"
                    << "Standard deviation of variable " <<  i << " is zero.\n"
                    << "That variable won't be scaled.\n";
        }
    }

   data.scale_mean_standard_deviation(data_statistics);
}


// Vector< Statistics<double> > scale_data_minimum_maximum(void) method

/// Scales the data using the minimum and maximum method,
/// and the minimum and maximum values calculated from the data matrix.
/// It also returns the statistics from all columns.

Vector< Statistics<double> > DataSet::scale_data_minimum_maximum(void)
{
    const Vector< Statistics<double> > data_statistics = calculate_data_statistics();

    scale_data_minimum_maximum(data_statistics);

    return(data_statistics);
}


// Vector< Statistics<double> > scale_data_mean_standard_deviation(void) method

/// Scales the data using the mean and standard deviation method,
/// and the mean and standard deviation values calculated from the data matrix.
/// It also returns the statistics from all columns.

Vector< Statistics<double> > DataSet::scale_data_mean_standard_deviation(void)
{
    const Vector< Statistics<double> > data_statistics = calculate_data_statistics();

    scale_data_mean_standard_deviation(data_statistics);

    return(data_statistics);
}


// void scale_data_minimum_maximum(const Vector< Statistics<double> >&) method

/// Scales the data matrix with given minimum and maximum values.
/// It updates the data matrix.
/// @param data_statistics Vector of statistics structures for all the variables in the data set.
/// The size of that vector must be equal to the number of variables.

void DataSet::scale_data_minimum_maximum(const Vector< Statistics<double> >& data_statistics)
{
    const unsigned variables_number = variables.get_variables_number();

   // Control sentence (if debug)

   #ifndef NDEBUG 

   std::ostringstream buffer;

   const unsigned statistics_size = data_statistics.size();

   if(statistics_size != variables_number)
   {
      buffer << "OpenNN Exception: DataSet class.\n"
             << "void scale_data_minimum_maximum(const Vector< Statistics<double> >&) method.\n"
             << "Size of data statistics must be equal to number of variables.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   for(unsigned i = 0; i < variables_number; i++)
   {
       if(display && data_statistics[i].maximum-data_statistics[i].minimum < 1.0e-99)
       {
          std::cout << "OpenNN Warning: DataSet class.\n"
                    << "void scale_data_minimum_maximum(const Vector< Statistics<Type> >&) method.\n"
                    << "Range of variable " <<  i << " is zero.\n"
                    << "That variable won't be scaled.\n";
        }
    }


   data.scale_minimum_maximum(data_statistics);
}


// void scale_data(const std::string&, const Vector< Statistics<double> >&) method

/// Scales the data matrix.
/// The method to be used is that in the scaling and unscaling method variable. 
/// @param scaling_unscaling_method_string String with the name of the scaling-unscaling method
/// (MinimumMaximum or MeanStandardDeviation).
/// @param data_statistics Vector of statistics structures for all the variables in the data set.
/// The size of that vector must be equal to the number of variables.

void DataSet::scale_data(const std::string& scaling_unscaling_method_string, const Vector< Statistics<double> >& data_statistics)
{
   switch(get_scaling_unscaling_method(scaling_unscaling_method_string))
   {
      case MinimumMaximum:
      {
         scale_data_minimum_maximum(data_statistics);
      }            
      break;

      case MeanStandardDeviation:
      {
         scale_data_mean_standard_deviation(data_statistics);
      }
      break;

      default:
      {
         std::ostringstream buffer;

         buffer << "OpenNN Exception: DataSet class\n"
                << "void scale_data(const std::string&, const Vector< Vector<double> >&) method.\n"
                << "Unknown data scaling and unscaling method.\n";

	     throw std::logic_error(buffer.str());
      }
      break;
   }
}


// Vector< Statistics<double> > scale_data(void) method

/// Calculates the data statistics, scales the data with that values and returns the statistics. 
/// The method to be used is that in the scaling and unscaling method variable. 

Vector< Statistics<double> > DataSet::scale_data(const std::string& scaling_unscaling_method)
{
   const Vector< Statistics<double> > statistics = data.calculate_statistics();

   switch(get_scaling_unscaling_method(scaling_unscaling_method))
   {
      case MinimumMaximum:
      {
         scale_data_minimum_maximum(statistics);
      }            
      break;

      case MeanStandardDeviation:
      {
         scale_data_mean_standard_deviation(statistics);
      }
      break;

      default:
      {
         std::ostringstream buffer;

         buffer << "OpenNN Exception: DataSet class\n"
                << "Vector< Statistics<double> > scale_data(const std::string&) method.\n"
                << "Unknown scaling and unscaling method.\n";

	     throw std::logic_error(buffer.str());
      }
      break;
   }

   return(statistics);
}


// void scale_inputs_mean_standard_deviation(const Vector< Statistics<double> >&) method

/// Scales the input variables with given mean and standard deviation values.
/// It updates the input variables of the data matrix.
/// @param inputs_statistics Vector of statistics structures for the input variables.
/// The size of that vector must be equal to the number of inputs.

void DataSet::scale_inputs_mean_standard_deviation(const Vector< Statistics<double> >& inputs_statistics)
{
    const Vector<unsigned> inputs_indices = variables.arrange_inputs_indices();

    data.scale_columns_mean_standard_deviation(inputs_statistics, inputs_indices);
}


// Vector< Statistics<double> > scale_inputs_mean_standard_deviation(void) method

/// Scales the input variables with the calculated mean and standard deviation values from the data matrix.
/// It updates the input variables of the data matrix.
/// It also returns a vector of vectors with the variables statistics. 

Vector< Statistics<double> > DataSet::scale_inputs_mean_standard_deviation(void)
{
   const Vector< Statistics<double> > inputs_statistics = calculate_inputs_statistics();

   scale_inputs_mean_standard_deviation(inputs_statistics);

   return(inputs_statistics);
}


// void scale_inputs_minimum_maximum(const Vector< Statistics<double> >&) method

/// Scales the input variables with given minimum and maximum values.
/// It updates the input variables of the data matrix.
/// @param inputs_statistics Vector of statistics structures for all the inputs in the data set.
/// The size of that vector must be equal to the number of input variables.

void DataSet::scale_inputs_minimum_maximum(const Vector< Statistics<double> >& inputs_statistics)
{
    const Vector<unsigned> inputs_indices = variables.arrange_inputs_indices();

    data.scale_columns_minimum_maximum(inputs_statistics, inputs_indices);
}


// Vector< Vector<double> > scale_inputs_minimum_maximum(void) method

/// Scales the input variables with the calculated minimum and maximum values from the data matrix.
/// It updates the input variables of the data matrix.
/// It also returns a vector of vectors with the minimum and maximum values of the input variables. 

Vector< Statistics<double> > DataSet::scale_inputs_minimum_maximum(void)
{
   const Vector< Statistics<double> > inputs_statistics = calculate_inputs_statistics();

   scale_inputs_minimum_maximum(inputs_statistics);

   return(inputs_statistics);
}


// Vector< Vector<double> > scale_inputs(const std::string&) method

/// Calculates the input and target variables statistics. 
/// Then it scales the input variables with that values.
/// The method to be used is that in the scaling and unscaling method variable. 
/// Finally, it returns the statistics. 

Vector< Statistics<double> > DataSet::scale_inputs(const std::string& scaling_unscaling_method)
{
    switch(get_scaling_unscaling_method(scaling_unscaling_method))
   {
      case MinimumMaximum:
      {
         return(scale_inputs_minimum_maximum());
      }            
      break;

      case MeanStandardDeviation:
      {
         return(scale_inputs_mean_standard_deviation());
      }
      break;

      default:
      {
         std::ostringstream buffer;

         buffer << "OpenNN Exception: DataSet class\n"
                << "Vector< Statistics<double> > scale_inputs(void) method.\n"
                << "Unknown scaling and unscaling method.\n";

	     throw std::logic_error(buffer.str());
      }
      break;
   }
}


// void scale_inputs(const std::string&, const Vector< Statistics<double> >&) method

/// Calculates the input and target variables statistics.
/// Then it scales the input variables with that values.
/// The method to be used is that in the scaling and unscaling method variable.

void DataSet::scale_inputs(const std::string& scaling_unscaling_method, const Vector< Statistics<double> >& inputs_statistics)
{
   switch(get_scaling_unscaling_method(scaling_unscaling_method))
   {
      case MinimumMaximum:
      {
         scale_inputs_minimum_maximum(inputs_statistics);
      }
      break;

      case MeanStandardDeviation:
      {
         scale_inputs_mean_standard_deviation(inputs_statistics);
      }
      break;

      default:
      {
         std::ostringstream buffer;

         buffer << "OpenNN Exception: DataSet class\n"
                << "void scale_inputs(const std::string&, const Vector< Statistics<double> >&) method.\n"
                << "Unknown scaling and unscaling method.\n";

         throw std::logic_error(buffer.str());
      }
      break;
   }
}


// void scale_targets_mean_standard_deviation(const Vector< Statistics<double> >&)

/// Scales the target variables with given mean and standard deviation values.
/// It updates the target variables of the data matrix.
/// @param targets_statistics Vector of statistics structures for all the targets in the data set.
/// The size of that vector must be equal to the number of target variables.

void DataSet::scale_targets_mean_standard_deviation(const Vector< Statistics<double> >& targets_statistics)
{
    const Vector<unsigned> targets_indices = variables.arrange_targets_indices();

    data.scale_columns_mean_standard_deviation(targets_statistics, targets_indices);
}


// Vector< Statistics<double> > scale_targets_mean_standard_deviation(void) method

/// Scales the target variables with the calculated mean and standard deviation values from the data matrix.
/// It updates the target variables of the data matrix.
/// It also returns a vector of statistics structures with the basic statistics of all the variables.

Vector< Statistics<double> > DataSet::scale_targets_mean_standard_deviation(void)
{    
   const Vector< Statistics<double> > targets_statistics = calculate_targets_statistics();

   scale_targets_mean_standard_deviation(targets_statistics);

   return(targets_statistics);
}


// void scale_targets_minimum_maximum(const Vector< Statistics<double> >&) method

/// Scales the target variables with given minimum and maximum values.
/// It updates the target variables of the data matrix.
/// @param targets_statistics Vector of statistics structures for all the targets in the data set.
/// The size of that vector must be equal to the number of target variables.

void DataSet::scale_targets_minimum_maximum(const Vector< Statistics<double> >& targets_statistics)
{
    const Vector<unsigned> targets_indices = variables.arrange_targets_indices();

    data.scale_columns_minimum_maximum(targets_statistics, targets_indices);
}


// Vector< Statistics<double> > scale_targets_minimum_maximum(void) method

/// Scales the target variables with the calculated minimum and maximum values from the data matrix.
/// It updates the target variables of the data matrix.
/// It also returns a vector of vectors with the statistics of the input target variables. 

Vector< Statistics<double> > DataSet::scale_targets_minimum_maximum(void)
{
   const Vector< Statistics<double> > targets_statistics = calculate_targets_statistics();

   scale_targets_minimum_maximum(targets_statistics);

   return(targets_statistics);
}


// Vector< Statistics<double> > scale_targets(const std::string&) method

/// Calculates the input and target variables statistics. 
/// Then it scales the target variables with that values.
/// The method to be used is that in the scaling and unscaling method variable. 
/// Finally, it returns the statistics. 

Vector< Statistics<double> > DataSet::scale_targets(const std::string& scaling_unscaling_method)
{
    switch(get_scaling_unscaling_method(scaling_unscaling_method))
   {
      case MinimumMaximum:
      {
         return(scale_targets_minimum_maximum());
      }            
      break;

      case MeanStandardDeviation:
      {
         return(scale_targets_mean_standard_deviation());
      }
      break;

      default:
      {
         std::ostringstream buffer;

         buffer << "OpenNN Exception: DataSet class\n"
                << "Vector< Statistics<double> > scale_targets(const std::string&) method.\n"
                << "Unknown scaling and unscaling method.\n";

	     throw std::logic_error(buffer.str());
      }
      break;
   }
}


// void scale_targets(const std::string&, const Vector< Statistics<double> >&) method

/// It scales the input variables with that values.
/// The method to be used is that in the scaling and unscaling method variable.

void DataSet::scale_targets(const std::string& scaling_unscaling_method, const Vector< Statistics<double> >& targets_statistics)
{
   switch(get_scaling_unscaling_method(scaling_unscaling_method))
   {
      case MinimumMaximum:
      {
         scale_targets_minimum_maximum(targets_statistics);
      }
      break;

      case MeanStandardDeviation:
      {
         scale_targets_mean_standard_deviation(targets_statistics);
      }
      break;

      default:
      {
         std::ostringstream buffer;

         buffer << "OpenNN Exception: DataSet class\n"
                << "void scale_targets(const std::string&, const Vector< Statistics<double> >&) method.\n"
                << "Unknown scaling and unscaling method.\n";

         throw std::logic_error(buffer.str());
      }
      break;
   }
}


// void unscale_data_mean_standard_deviation(const Vector< Statistics<double> >&) method

/// Unscales the data matrix with given mean and standard deviation values.
/// It updates the data matrix.
/// @param data_statistics Vector of statistics structures for all the variables in the data set.
/// The size of that vector must be equal to the number of variables.

void DataSet::unscale_data_mean_standard_deviation(const Vector< Statistics<double> >& data_statistics)
{
   data.unscale_mean_standard_deviation(data_statistics);
}


// void unscale_data_minimum_maximum(const Vector< Statistics<double> >&) method

/// Unscales the data matrix with given minimum and maximum values.
/// It updates the data matrix.
/// @param data_statistics Vector of statistics structures for all the variables in the data set.
/// The size of that vector must be equal to the number of variables.

void DataSet::unscale_data_minimum_maximum(const Vector< Statistics<double> >& data_statistics)
{
   data.unscale_minimum_maximum(data_statistics);
}


// void unscale_inputs_mean_standard_deviation(const Vector< Statistics<double> >&) method

/// Unscales the input variables with given mean and standard deviation values.
/// It updates the input variables of the data matrix.
/// @param inputs_statistics Vector of statistics structures for all the inputs in the data set.
/// The size of that vector must be equal to the number of input variables.

void DataSet::unscale_inputs_mean_standard_deviation(const Vector< Statistics<double> >& inputs_statistics)
{
    const Vector<unsigned> inputs_indices = variables.arrange_inputs_indices();

    data.unscale_columns_mean_standard_deviation(inputs_statistics, inputs_indices);
}


// void unscale_inputs_minimum_maximum(const Vector< Statistics<double> >&) method

/// Unscales the input variables with given minimum and maximum values.
/// It updates the input variables of the data matrix.
/// @param inputs_statistics Vector of statistics structures for all the inputs in the data set.
/// The size of that vector must be equal to the number of input variables.

void DataSet::unscale_inputs_minimum_maximum(const Vector< Statistics<double> >& inputs_statistics)
{
    const Vector<unsigned> inputs_indices = variables.arrange_inputs_indices();

    data.unscale_columns_minimum_maximum(inputs_statistics, inputs_indices);
}


// void unscale_targets_mean_standard_deviation(const Vector< Statistics<double> >&) method

/// Unscales the target variables with given mean and standard deviation values.
/// It updates the target variables of the data matrix.
/// @param targets_statistics Vector of statistics structures for all the targets in the data set.
/// The size of that vector must be equal to the number of targets.

void DataSet::unscale_targets_mean_standard_deviation(const Vector< Statistics<double> >& targets_statistics)
{
    const Vector<unsigned> targets_indices = variables.arrange_targets_indices();

    data.unscale_columns_mean_standard_deviation(targets_statistics, targets_indices);
}


// void unscale_targets_minimum_maximum(const Vector< Statistics<double> >&) method

/// Unscales the target variables with given minimum and maximum values.
/// It updates the target variables of the data matrix.
/// @param targets_statistics Vector of statistics structures for all the targets.
/// The size of that vector must be equal to the number of target variables.

void DataSet::unscale_targets_minimum_maximum(const Vector< Statistics<double> >& targets_statistics)
{
    const Vector<unsigned> targets_indices = variables.arrange_targets_indices();

    data.unscale_columns_minimum_maximum(targets_statistics, targets_indices);
}


// void initialize_data(const double& value) method

/// Initializes the data matrix with a given value.
/// @param new_value Initialization value. 

void DataSet::initialize_data(const double& new_value)
{
   data.initialize(new_value);
}


// void randomize_data_uniform(const double&, const double&) method

/// Initializes the data matrix with random values chosen from a uniform distribution
/// with given minimum and maximum.

void DataSet::randomize_data_uniform(const double& minimum, const double& maximum)
{
   data.randomize_uniform(minimum, maximum);
}


// void randomize_data_normal(const double&, const double&) method

/// Initializes the data matrix with random values chosen from a normal distribution
/// with given mean and standard deviation.

void DataSet::randomize_data_normal(const double& mean, const double& standard_deviation)
{
   data.randomize_normal(mean, standard_deviation);
}


// tinyxml2::XMLDocument* to_XML(void) const method

/// Serializes the data set object into a XML document of the TinyXML library. 

tinyxml2::XMLDocument* DataSet::to_XML(void) const
{
   tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument;

   std::ostringstream buffer;

   // Data set

   tinyxml2::XMLElement* data_set_element = document->NewElement("DataSet");
   document->InsertFirstChild(data_set_element);

   tinyxml2::XMLElement* element = NULL;
   tinyxml2::XMLText* text = NULL;

   // Data file_name
   {
      element = document->NewElement("DataFileName");
      data_set_element->LinkEndChild(element);

      text = document->NewText(data_file_name.c_str());
      element->LinkEndChild(text);
   }

   // Variables 
   {
      element = document->NewElement("Variables");
      data_set_element->LinkEndChild(element);

      const tinyxml2::XMLDocument* variables_document = variables.to_XML();

      const tinyxml2::XMLElement* variables_element = variables_document->FirstChildElement("Variables");

      DeepClone(element, variables_element, document, NULL);

      delete variables_document;
   }

   // Instances
   {
       element = document->NewElement("Instances");
       data_set_element->LinkEndChild(element);

       const tinyxml2::XMLDocument* instances_document = instances.to_XML();

       const tinyxml2::XMLElement* instances_element = instances_document->FirstChildElement("Instances");

       DeepClone(element, instances_element, document, NULL);

       delete instances_document;
   }

   // Display
   {
      element = document->NewElement("Display");
      data_set_element->LinkEndChild(element);

      buffer.str("");
      buffer << display;

      text = document->NewText(buffer.str().c_str());
      element->LinkEndChild(text);
   }  

   return(document);
}


// void from_XML(const tinyxml2::XMLDocument&) method

/// Deserializes a TinyXML document into this data set object.
/// @param data_set_document XML document containing the member data.

void DataSet::from_XML(const tinyxml2::XMLDocument& data_set_document)
{
   std::ostringstream buffer;

   // Data set element

   const tinyxml2::XMLElement* data_set_element = data_set_document.FirstChildElement("DataSet");

   if(!data_set_element)
   {
       buffer << "OpenNN Exception: DataSet class.\n"
              << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
              << "Data set element is NULL.\n";

       throw std::logic_error(buffer.str());
   }

   // Data file_name

   const tinyxml2::XMLElement* data_file_name_element = data_set_element->FirstChildElement("DataFileName");

   if(!data_file_name_element)
   {
       buffer << "OpenNN Exception: DataSet class.\n"
              << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
              << "Data file name element is NULL.\n";

       throw std::logic_error(buffer.str());
   }

  const std::string new_data_file_name = data_file_name_element->GetText();

  set_data_file_name(new_data_file_name);

   // Variables

   const tinyxml2::XMLElement* variables_element = data_set_element->FirstChildElement("Variables");

   if(variables_element)
   {
       tinyxml2::XMLDocument variables_document;

       tinyxml2::XMLElement* variables_element_clone = variables_document.NewElement("Variables");
       variables_document.InsertFirstChild(variables_element_clone);

       DeepClone(variables_element_clone, variables_element, &variables_document, NULL);

       variables.from_XML(variables_document);
   }

   // Instances

   const tinyxml2::XMLElement* instances_element = data_set_element->FirstChildElement("Instances");

   if(instances_element)
   {
       tinyxml2::XMLDocument instances_document;

       tinyxml2::XMLElement* instances_element_clone = instances_document.NewElement("Instances");
       instances_document.InsertFirstChild(instances_element_clone);

       DeepClone(instances_element_clone, instances_element, &instances_document, NULL);

       instances.from_XML(instances_document);
   }
}


// std::string to_string(void) const method

/// Returns a string representation of the current data set object. 

std::string DataSet::to_string(void) const
{
   std::ostringstream buffer;

   buffer << "Data set object\n"
          << "Data file_name: " << data_file_name << "\n"
          << "Data:\n" << data << "\n"
          << "Display: " << display << "\n"
          << variables.to_string()
          << instances.to_string();

   return(buffer.str());
}

// void print(void) const method

/// Prints to the screen in text format the members of the data set object.

void DataSet::print(void) const
{
   if(display)
   {
      std::cout << to_string();
   }
}


// void save(const std::string&) const method

/// Saves the members of a data set object to a XML-type file in an XML-type format.
/// @param file_name Name of data set XML-type file.

void DataSet::save(const std::string& file_name) const
{
   tinyxml2::XMLDocument* document = to_XML();

   document->SaveFile(file_name.c_str());

   delete document;
}


// void load(const std::string&) method

/// Loads the members of a data set object from a XML-type file:
/// <ul>
/// <li> Instances number.
/// <li> Training instances number.
/// <li> Training instances indices.
/// <li> Generalization instances number.
/// <li> Generalization instances indices.
/// <li> Testing instances number.
/// <li> Testing instances indices.
/// <li> Input variables number.
/// <li> Input variables indices.
/// <li> Target variables number.
/// <li> Target variables indices.
/// <li> Input variables name. 
/// <li> Target variables name.
/// <li> Input variables description. 
/// <li> Target variables description.
/// <li> Display.
/// <li> Data.
/// </ul> 
/// Please mind about the file format. This is specified in the User's Guide.
/// @param file_name Name of data set XML-type file.

void DataSet::load(const std::string& file_name)
{
   tinyxml2::XMLDocument document;

   if(document.LoadFile(file_name.c_str()))
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void load(const std::string&) method.\n"
             << "Cannot load XML file " << file_name << ".\n";

      throw std::logic_error(buffer.str());
   }

   from_XML(document);
}


// void print_data(void) const method

/// Prints to the sceen the values of the data matrix.

void DataSet::print_data(void) const
{
   if(display)
   {
      std::cout << data << std::endl;
   }
}


// void save_data(void) const method

/// Saves to the data file the values of the data matrix.

void DataSet::save_data(void) const
{
   std::ofstream file(data_file_name.c_str());

   if(!file.is_open())
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n" 
             << "void save_data(void) const method.\n"
             << "Cannot open data file.\n";

      throw std::logic_error(buffer.str());	  
   }
  
   // Write data

   file << data;

   // Close file

   file.close();
}


// void save_data(const std::string&) const method

/// Saves to a file the values of the data matrix.
/// @param file_name Name of data file. 

void DataSet::save_data(const std::string& file_name) const
{
   std::ofstream file(file_name.c_str());

   if(!file.is_open())
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n" 
             << "void save_data(const std::string&) const method.\n"
             << "Cannot open data file.\n";

      throw std::logic_error(buffer.str());	  
   }
  
   // Write data

   file << data;

   // Close file

   file.close();
}


// void load_data(void)

/// Loads from the data file the values of the data matrix.

void DataSet::load_data(void)
{
   data.load(data_file_name);

   const unsigned columns_number = data.get_columns_number();

   if(columns_number != variables.get_variables_number())
   {
      variables.set(columns_number);
   }

   const unsigned rows_number = data.get_rows_number();

   if(rows_number != instances.get_instances_number())
   {
       instances.set(rows_number);
   }
}


// void load_data(const std::string& file_name)

/// Loads from a file the values of the data matrix.
/// The number of rows will be the number of instances.
/// The number of columns will be the number of variables.

void DataSet::load_data(const std::string& new_data_file_name)
{
   data_file_name = new_data_file_name;

   load_data();
}


// Vector<unsigned> calculate_target_class_distribution(void) const method

/// Returns a vector containing the number of instances of each class in the data set.
/// If the number of target variables is one then the number of classes is two.
/// If the number of target variables is greater than one then the number of classes is equal to the number 
/// of target variables.

Vector<unsigned> DataSet::calculate_target_class_distribution(void) const
{ 
   // Control sentence (if debug)

   const unsigned instances_number = instances.get_instances_number();   
   const unsigned targets_number = variables.count_targets_number();
   const Vector<unsigned> targets_indices = variables.arrange_targets_indices();

   Vector<unsigned> class_distribution;

   if(targets_number == 1) // Two classes
   {
      class_distribution.set(2, 0);

      unsigned target_index = targets_indices[0];

      for(unsigned instance_index = 0; instance_index < instances_number; instance_index++)
      {
          if(instances.get_use(instance_index) != Instances::Unused)
          {
             if(data[instance_index][target_index] < 0.5)
             {
                class_distribution[0]++;
             }
             else
             {
                class_distribution[1]++;
             }
          }
      }
   }
   else // More than two classes
   {
      class_distribution.set(targets_number, 0);
   
      for(unsigned i = 0; i < instances_number; i++)
      {
          if(instances.get_use(i) != Instances::Unused)
          {
             for(unsigned j = 0; j < targets_number; j++)
             {
                if(data[i][targets_indices[j]] > 0.5)
                {
                   class_distribution[j]++;
                }
             }
          }
      }
   }

   // Check data consistency

   const unsigned used_instances_number = instances.count_used_instances_number();

   if(class_distribution.calculate_sum() != used_instances_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n" 
             << "Vector<int> calculate_target_class_distribution(void) const method.\n"
             << "Sum of class distributions is not equal to number of used instances.\n"
             << "Class distribution: " << class_distribution << std::endl; 

      throw std::logic_error(buffer.str());   
   }

   return(class_distribution);
}


// bool has_data(void) const method

/// Returns true if the data matrix is not empty (it has not been loaded),
/// and false otherwise.

bool DataSet::has_data(void) const
{
    if(data.empty())
    {
        return(false);
    }
    else
    {
        return(true);
    }
}

}


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
