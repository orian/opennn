/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   T E S T I N G   A N A L Y S I S   C L A S S                                                                */
/*                                                                                                              */ 
/*   Roberto Lopez                                                                                              */ 
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// OpenNN includes

#include "testing_analysis.h"

namespace OpenNN
{

// DEFAULT CONSTRUCTOR

/// Default constructor. 
/// It creates a testing analysis object neither associated to a neural network nor to a mathematical model or a data set.
/// By default, it constructs the function regression testing object. 

TestingAnalysis::TestingAnalysis(void)
 : neural_network_pointer(NULL),
   data_set_pointer(NULL),
   mathematical_model_pointer(NULL)
{
   set_default();
}


// NEURAL NETWORK CONSTRUCTOR

/// Neural network constructor. 
/// It creates a testing analysis object associated to a neural network but not to a mathematical model or a data set.
/// By default, it constructs the function regression testing object. 
/// @param new_neural_network_pointer Pointer to a neural network object.

TestingAnalysis::TestingAnalysis(NeuralNetwork* new_neural_network_pointer)
: neural_network_pointer(new_neural_network_pointer),
   data_set_pointer(NULL),
   mathematical_model_pointer(NULL)
{
   set_default();
}


// MATHEMATICAL MODEL CONSTRUCTOR

/// Mathematical mmodel constructor. 
/// It creates a testing analysis object not associated to a neural network, not associated to a data set, and associated to a mathematical model. 
/// By default, it constructs the inverse problem testing object. 
/// @param new_mathematical_model_pointer Pointer to a mathematical model object.

TestingAnalysis::TestingAnalysis(MathematicalModel* new_mathematical_model_pointer)
: neural_network_pointer(NULL),
   data_set_pointer(NULL),
   mathematical_model_pointer(new_mathematical_model_pointer)
{
   set_default();
}


// DATA SET CONSTRUCTOR

/// Data set constructor. 
/// It creates a testing analysis object not associated to a neural network, associated to a data set and not associated to a mathematical model. 
/// By default, it constructs the function regression testing object. 
/// @param new_data_set_pointer Pointer to a data set object.

TestingAnalysis::TestingAnalysis(DataSet* new_data_set_pointer)
: neural_network_pointer(NULL),
   data_set_pointer(new_data_set_pointer),
   mathematical_model_pointer(NULL)
{
   set_default();
}


// NEURAL NETWORK AND MATHEMATICAL MODEL CONSTRUCTOR

/// Neural network and mathematical model constructor. 
/// It creates a testing analysis object associated to a neural network and to a mathematical model, but not to a data set.
/// By default, it constructs the inverse problem testing object. 
/// @param new_neural_network_pointer Pointer to a neural network object.
/// @param new_mathematical_model_pointer Pointer to a mathematical model object.

TestingAnalysis::TestingAnalysis(NeuralNetwork* new_neural_network_pointer, MathematicalModel* new_mathematical_model_pointer)
 : neural_network_pointer(new_neural_network_pointer),
   data_set_pointer(NULL),
   mathematical_model_pointer(new_mathematical_model_pointer)
{
   set_default();
}


// NEURAL NETWORK AND DATA SET CONSTRUCTOR

/// Neural network and data set constructor. 
/// It creates a testing analysis object associated to a neural network and to a data set.
/// By default, it constructs the function regression testing object. 
/// @param new_neural_network_pointer Pointer to a neural network object.
/// @param new_data_set_pointer Pointer to a data set object.

TestingAnalysis::TestingAnalysis(NeuralNetwork* new_neural_network_pointer, DataSet* new_data_set_pointer)
 : neural_network_pointer(new_neural_network_pointer),
   data_set_pointer(new_data_set_pointer),
   mathematical_model_pointer(NULL)
{
   set_default();
}


// NEURAL NETWORK, MATHEMATICAL MODEL AND DATA SET CONSTRUCTOR

/// Neural network, mathematical model and data set constructor. 
/// It creates a testing analysis object associated to a neural network, a mathematical model and a data set.
/// By default, it constructs the inverse problem testing object. 
/// @param new_neural_network_pointer Pointer to a neural network object.
/// @param new_mathematical_model_pointer Pointer to a mathematical model object.
/// @param new_data_set_pointer Pointer to a data set object.

TestingAnalysis::TestingAnalysis(NeuralNetwork* new_neural_network_pointer, DataSet* new_data_set_pointer, MathematicalModel* new_mathematical_model_pointer)
 : neural_network_pointer(new_neural_network_pointer),
   data_set_pointer(new_data_set_pointer),
   mathematical_model_pointer(new_mathematical_model_pointer)
{
   set_default();
}


// XML CONSTRUCTOR

/// XML constructor. 
/// It creates a testing analysis object neither associated to a neural network nor to a mathematical model or a data set. 
/// It also loads the members of this object from a TinyXML document.
/// @param testing_analysis_document XML document containing the member data.

TestingAnalysis::TestingAnalysis(const tinyxml2::XMLDocument& testing_analysis_document)
 : neural_network_pointer(NULL),
   data_set_pointer(NULL),
   mathematical_model_pointer(NULL)
{
   set_default();

   from_XML(testing_analysis_document);
}


// FILE CONSTRUCTOR

/// File constructor. 
/// It creates a testing analysis object neither associated to a neural network nor to a mathematical model or a data set. 
/// It also loads the members of this object from XML file. 
/// @param file_name Name of testing analysis XML file.  

TestingAnalysis::TestingAnalysis(const std::string& file_name)
 : neural_network_pointer(NULL),
   data_set_pointer(NULL),
   mathematical_model_pointer(NULL)
{
   set_default();

   load(file_name);
}

// DESTRUCTOR

/// Destructor. 
/// It deletes the function regression testing, pattern recognition testing, time series prediction testing and inverse problem testing objects. 

TestingAnalysis::~TestingAnalysis()
{
}


// METHODS

// NeuralNetwork* get_neural_network_pointer(void) const method

/// Returns a pointer to the neural network object which is to be tested.

NeuralNetwork* TestingAnalysis::get_neural_network_pointer(void) const
{
    #ifndef NDEBUG

    if(!neural_network_pointer)
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: TestingAnalysis class.\n"
               << "NeuralNetwork* get_neural_network_pointer(void) const method.\n"
               << "Neural network pointer is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    #endif

   return(neural_network_pointer);   
}


// DataSet* get_data_set_pointer(void) const method

/// Returns a pointer to the data set object on which the neural network is tested. 

DataSet* TestingAnalysis::get_data_set_pointer(void) const
{
    #ifndef NDEBUG

    if(!data_set_pointer)
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: TestingAnalysis class.\n"
               << "DataSet* get_data_set_pointer(void) const method.\n"
               << "Data set pointer is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    #endif

   return(data_set_pointer);
}


// MathematicalModel* get_mathematical_model_pointer(void) const method

/// Returns a pointer to the mathematical model object on which the neural network is tested. 

MathematicalModel* TestingAnalysis::get_mathematical_model_pointer(void) const
{
    #ifndef NDEBUG

    if(!mathematical_model_pointer)
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception: TestingAnalysis class.\n"
               << "MathematicalModel* get_mathematical_model_pointer(void) const method.\n"
               << "Mathematical model pointer is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    #endif

   return(mathematical_model_pointer);
}


// const bool& get_display(void) const method

/// Returns true if messages from this class can be displayed on the screen,
/// or false if messages from this class can't be displayed on the screen.

const bool& TestingAnalysis::get_display(void) const
{
   return(display);     
}


// void set_default(void) method

/// Sets some default values to the testing analysis object:
/// <ul>
/// <li> Display: True.
/// </ul>

void TestingAnalysis::set_default(void)
{
   display = true;
}


// void set_neural_network_pointer(NeuralNetwork*) method

/// Sets a new neural network object to be tested.
/// @param new_neural_network_pointer Pointer to a neural network object.

void TestingAnalysis::set_neural_network_pointer(NeuralNetwork* new_neural_network_pointer)
{
   neural_network_pointer = new_neural_network_pointer;   
}


// void set_mathematical_model_pointer(MathematicalModel*) method

/// Sets a mathematical model to be used for validating the quality of a trained neural network.
/// @param new_mathematical_model_pointer Pointer to a mathematical model object.

void TestingAnalysis::set_mathematical_model_pointer(MathematicalModel* new_mathematical_model_pointer)
{
   mathematical_model_pointer = new_mathematical_model_pointer;   
}


// void set_data_set_pointer(DataSet*) method

/// Sets a new data set to be used for validating the quality of a trained neural network.
/// @param new_data_set_pointer Pointer to a data set object.

void TestingAnalysis::set_data_set_pointer(DataSet* new_data_set_pointer)
{
   data_set_pointer = new_data_set_pointer;   
}


// void set_display(const bool&) method

/// Sets a new display value. 
/// If it is set to true messages from this class are to be displayed on the screen;
/// if it is set to false messages from this class are not to be displayed on the screen.
/// @param new_display Display value.

void TestingAnalysis::set_display(const bool& new_display)
{
   display = new_display;
}


// void check(void) const method

/// Checks that:
/// <ul>
/// <li> The neural network pointer is not NULL.
/// <li> The data set pointer is not NULL.
/// </ul>

void TestingAnalysis::check(void) const
{
   std::ostringstream buffer;

   if(!neural_network_pointer)
   {
      buffer << "OpenNN Exception: TestingAnalysis class.\n"
             << "void check(void) const method.\n"
             << "Neural network pointer is NULL.\n";

      throw std::logic_error(buffer.str());
   }

   if(!data_set_pointer)
   {
      buffer << "OpenNN Exception: TestingAnalysis class.\n"
             << "void check(void) const method.\n"
             << "Data set pointer is NULL.\n";

      throw std::logic_error(buffer.str());
   }
}


// Vector< Matrix<double> > calculate_target_output_data(void) const method

/// Returns a vector of matrices with number of rows equal to number of testing instances and
/// number of columns equal to two (the targets value and the outputs value).

Vector< Matrix<double> > TestingAnalysis::calculate_target_output_data(void) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG

   check();

   #endif

   // Data set stuff

   const Instances& instances = data_set_pointer->get_instances();

   const unsigned testing_instances_number = instances.count_testing_instances_number();

   const Matrix<double> testing_input_data = data_set_pointer->arrange_testing_input_data();

   const Matrix<double> target_data = data_set_pointer->arrange_testing_target_data();

   // Neural network stuff

   const MultilayerPerceptron* multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();

   const unsigned outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   const Matrix<double> output_data = neural_network_pointer->calculate_output_data(testing_input_data);

   // Function regression testing stuff

   Vector< Matrix<double> > target_output_data(outputs_number);

   for(unsigned i = 0; i < outputs_number; i++)
   {
      target_output_data[i].set(testing_instances_number, 2);

      target_output_data[i].set_column(0, target_data.arrange_column(i));
      target_output_data[i].set_column(1, output_data.arrange_column(i));
   }

   return(target_output_data);
}



// Vector< LinearRegressionParameters<double> > calculate_linear_regression_parameters(void) const method

/// Performs a linear regression analysis between the testing instances in the data set and
/// the corresponding neural network outputs.
/// It returns all the provided parameters in a vector of vectors.
/// The number of elements in the vector is equal to the number of output variables.
/// The size of each element is equal to the number of regression parameters (2).
/// In this way, each subvector contains the regression parameters intercept and slope of an output variable.

Vector< LinearRegressionParameters<double> > TestingAnalysis::calculate_linear_regression_parameters(void) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG

   check();

   #endif

   // Data set stuff

   const Instances& instances = data_set_pointer->get_instances();

   const unsigned testing_instances_number = instances.count_testing_instances_number();

   // Neural network stuff

   const MultilayerPerceptron* multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();

   const unsigned outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   #ifndef NDEBUG

   std::ostringstream buffer;

   if(testing_instances_number == 0)
   {
      buffer << "OpenNN Exception: TestingAnalysis class.\n"
             << "Vector< LinearRegressionParameters<double> > calculate_linear_regression_parameters(void) const method.\n"
             << "Number of testing instances is zero.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   // Calculate regression parameters

   const Matrix<double> input_data = data_set_pointer->arrange_testing_input_data();
   const Matrix<double> target_data = data_set_pointer->arrange_testing_target_data();
   const Matrix<double> output_data = neural_network_pointer->calculate_output_data(input_data);

   Vector<double> target_variable(testing_instances_number);
   Vector<double> output_variable(testing_instances_number);

   Vector< LinearRegressionParameters<double> > linear_regression_parameters(outputs_number);

   for(unsigned i = 0; i < outputs_number; i++)
   {
       target_variable = target_data.arrange_column(i);
       output_variable = output_data.arrange_column(i);

       linear_regression_parameters[i] = output_variable.calculate_linear_regression_parameters(target_variable);
   }

   return(linear_regression_parameters);
}


// TestingAnalysis::LinearRegressionResults TestingAnalysis::perform_linear_regression_analysis(void) const

/// Performs a linear regression analysis of a neural network on the testing indices of a data set.
/// It returns a linear regression analysis results structure, which consists on:
/// <ul>
/// <li> Linear regression parameters.
/// <li> Scaled target and output data.
/// </ul>

TestingAnalysis::LinearRegressionResults TestingAnalysis::perform_linear_regression_analysis(void) const
{
   LinearRegressionResults linear_regression_results;

   linear_regression_results.target_output_data = calculate_target_output_data();
   linear_regression_results.linear_regression_parameters = calculate_linear_regression_parameters();

   return(linear_regression_results);
}


// void LinearRegressionResults::save(const std::string&) const method

/// Saves a linear regression analysis results structure to a data file.
/// @param file_name Name of results data file.

void TestingAnalysis::LinearRegressionResults::save(const std::string& file_name) const
{
   std::ofstream file(file_name.c_str());

   file << linear_regression_parameters
        << "Target-output data:\n"
        << target_output_data;

   file.close();
}


// Matrix<double> calculate_error_data(void) const method

/// Calculates the errors between the outputs from a neural network and the testing instances in a data set.
/// It returns a vector of tree matrices:
/// <ul>
/// <li> Absolute error.
/// <li> Relative error.
/// <li> Percentage error.
/// </ul>
/// The number of rows in each matrix is the number of testing instances in the data set.
/// The number of columns is the number of outputs in the neural network.

Vector< Matrix<double> > TestingAnalysis::calculate_error_data(void) const
{
   // Data set stuff

   #ifndef NDEBUG

   check();

   #endif

   const unsigned testing_instances_number = data_set_pointer->get_instances().count_testing_instances_number();

    #ifndef NDEBUG

    std::ostringstream buffer;

    if(testing_instances_number == 0)
    {
       buffer << "OpenNN Exception: TestingAnalysis class.\n"
              << "Vector< Matrix<double> > calculate_error_data(void) const.\n"
              << "Number of testing instances is zero.\n";

       throw std::logic_error(buffer.str());
    }

    #endif


   const Matrix<double> input_data = data_set_pointer->arrange_testing_input_data();

   const Matrix<double> target_data = data_set_pointer->arrange_testing_target_data();

   // Neural network stuff

   const Matrix<double> output_data = neural_network_pointer->calculate_output_data(input_data);

   const UnscalingLayer* unscaling_layer_pointer = neural_network_pointer->get_unscaling_layer_pointer();

   #ifndef NDEBUG

   if(!unscaling_layer_pointer)
   {
      buffer << "OpenNN Exception: TestingAnalysis class.\n"
             << "Vector< Matrix<double> > calculate_error_data(void) const.\n"
             << "Unscaling layer is NULL.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   const Vector<double>& outputs_minimum = unscaling_layer_pointer->arrange_minimums();
   const Vector<double>& outputs_maximum = unscaling_layer_pointer->arrange_maximums();

   const unsigned outputs_number = unscaling_layer_pointer->get_unscaling_neurons_number();

   // Error data

   Vector< Matrix<double> > error_data(outputs_number);

   Vector<double> targets(testing_instances_number);
   Vector<double> outputs(testing_instances_number);

   for(unsigned i = 0; i < outputs_number; i++)
   {
       error_data[i].set(testing_instances_number, 3, 0.0);

       // Absolute error

       targets = target_data.arrange_column(i);
       outputs = output_data.arrange_column(i);

       error_data[i].set_column(0, (targets - outputs).calculate_absolute_value());

       // Relative error

       error_data[i].set_column(1, (targets - outputs).calculate_absolute_value()/(outputs_maximum[i]-outputs_minimum[i]));

       // Percentage error

       error_data[i].set_column(2, (targets - outputs).calculate_absolute_value()*100.0/(outputs_maximum[i]-outputs_minimum[i]));
    }

   return(error_data);
}


// Vector< Vector< Vector<double> > > calculate_error_data_statistics(void) const method
// @todo

/// Calculates the basic statistics on the error data.
/// <ul>
/// <li> Minimum.
/// <li> Maximum.
/// <li> Mean.
/// <li> Standard deviation
/// </ul>

Vector< Vector< Statistics<double> > > TestingAnalysis::calculate_error_data_statistics(void) const
{
    // Neural network stuff

    const MultilayerPerceptron* multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();

    const unsigned outputs_number = multilayer_perceptron_pointer->get_outputs_number();

    // Testing analysis stuff

    Vector< Vector< Statistics<double> > > statistics(outputs_number);

   const Vector< Matrix<double> > error_data = calculate_error_data();

   for(unsigned i = 0; i < outputs_number; i++)
   {
       statistics[i] = error_data[i].calculate_statistics();
   }

   return(statistics);
}


// Vector< Matrix<double> > calculate_error_data_statistics_matrices(void) const method

/// Returns a vector of matrices with the statistics of the errors between the neural network outputs and the testing targets in the data set.
/// The size of the vector is the number of output variables.
/// The number of rows in each submatrix is three (absolute, relative and percentage errors).
/// The number of columns in each submatrix is four (minimum, maximum, mean and standard deviation).

Vector< Matrix<double> > TestingAnalysis::calculate_error_data_statistics_matrices(void) const
{
    const Vector< Vector< Statistics<double> > > error_data_statistics = calculate_error_data_statistics();

    const unsigned outputs_number = error_data_statistics.size();

    Vector< Matrix<double> > statistics(outputs_number);

    for(unsigned i = 0; i < outputs_number; i++)
    {
        statistics[i].set(3, 4);
        statistics[i].set_row(0, error_data_statistics[i][0].to_vector());
        statistics[i].set_row(1, error_data_statistics[i][1].to_vector());
        statistics[i].set_row(2, error_data_statistics[i][2].to_vector());
    }

    return(statistics);
}


// Vector< Histogram<double> > calculate_error_data_histograms(const unsigned&) const method

/// Calculates histograms for the relative errors of all the output variables.
/// The number of bins is set by the user.
/// @param bins_number Number of bins in the histograms.

Vector< Histogram<double> > TestingAnalysis::calculate_error_data_histograms(const unsigned& bins_number) const
{
   const Vector< Matrix<double> > error_data = calculate_error_data();

   const unsigned outputs_number = error_data.size();

   Vector< Histogram<double> > histograms(outputs_number);

   for(unsigned i = 0; i < outputs_number; i++)
   {
       histograms[i] = error_data[i].arrange_column(0).calculate_histogram(bins_number);
   }

   return(histograms);
}


// Matrix<unsigned> calculate_confusion_binary_classification(const Matrix<double>&, const Matrix<double>&) const method

/// Returns the confusion matrix for a binary classification problem.
/// @param actual_data Testing target data.
/// @param predicted_data Testing output data.

Matrix<unsigned> TestingAnalysis::calculate_confusion_binary_classification(const Matrix<double>& actual_data, const Matrix<double>& predicted_data) const
{
    const unsigned rows_number = actual_data.get_rows_number();

    Matrix<unsigned> confusion(2, 2, 0);

    unsigned actual_index = 0;
    unsigned predicted_index = 0;

    for(unsigned i = 0; i < rows_number; i++)
    {
        if(actual_data[i][0] < 0.5)
        {
            actual_index = 0;
        }
        else
        {
            actual_index = 1;
        }

        if(predicted_data[i][0] < 0.5)
        {
            predicted_index = 0;
        }
        else
        {
            predicted_index = 1;
        }

        confusion[actual_index][predicted_index]++;
    }

    return(confusion);
}


// Matrix<unsigned> calculate_confusion_multiple_classification(const Matrix<double>&, const Matrix<double>&) const method

/// Returns the confusion matrix for a binary classification problem.
/// @param actual_data Testing target data.
/// @param predicted_data Testing output data.

Matrix<unsigned> TestingAnalysis::calculate_confusion_multiple_classification(const Matrix<double>& actual_data, const Matrix<double>& predicted_data) const
{
    const unsigned rows_number = actual_data.get_rows_number();
    const unsigned columns_number = actual_data.get_columns_number();

    Matrix<unsigned> confusion(columns_number, columns_number, 0);

    unsigned actual_index = 0;
    unsigned predicted_index = 0;

    for(unsigned i = 0; i < rows_number; i++)
    {
        actual_index = actual_data.arrange_row(i).calculate_maximal_index();
        predicted_index = predicted_data.arrange_row(i).calculate_maximal_index();

        confusion[actual_index][predicted_index]++;
    }

    return(confusion);
}


// Matrix<unsigned> calculate_confusion(void) const method

/// Returns the confusion matrix of a neural network on the testing instances of a data set.
/// If the number of outputs is one, the size of the confusion matrix is two.
/// If the number of outputs is greater than one, the size of the confusion matrix is the number of outputs.

Matrix<unsigned> TestingAnalysis::calculate_confusion(void) const
{

   #ifndef NDEBUG

    check();

   #endif

   const MultilayerPerceptron* multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();

   #ifndef NDEBUG

   if(!multilayer_perceptron_pointer)
   {
       std::ostringstream buffer;

      buffer << "OpenNN Exception: TestingAnalysis class.\n"
             << "Matrix<unsigned> calculate_confusion(void) const method.\n"
             << "Pointer to multilayer perceptron in neural network is NULL.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   const unsigned outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   #ifndef NDEBUG

   const unsigned inputs_number = multilayer_perceptron_pointer->get_inputs_number();

   // Control sentence

   const Variables& variables = data_set_pointer->get_variables();

   if(inputs_number != variables.count_inputs_number())
   {      
       std::ostringstream buffer;

       buffer << "OpenNN Exception: TestingAnalysis class." << std::endl
             << "Matrix<unsigned> calculate_confusion(void) const method." << std::endl
             << "Number of inputs in neural network must be equal to number of inputs in data set." << std::endl;

      throw std::logic_error(buffer.str());
   }

   if(outputs_number != variables.count_targets_number())
   {
       std::ostringstream buffer;

      buffer << "OpenNN Exception: TestingAnalysis class." << std::endl
             << "Matrix<unsigned> calculate_confusion(void) const method." << std::endl
             << "Number of outputs in neural network must be equal to number of targets in data set." << std::endl;

      throw std::logic_error(buffer.str());
   }

   #endif

    const Matrix<double> input_data = data_set_pointer->arrange_testing_input_data();
    const Matrix<double> target_data = data_set_pointer->arrange_testing_target_data();

    const Matrix<double> output_data = neural_network_pointer->calculate_output_data(input_data);

    if(outputs_number == 1)
    {
        return(calculate_confusion_binary_classification(target_data, output_data));
    }
    else
    {
        return(calculate_confusion_multiple_classification(target_data, output_data));

    }
}


// Vector<double> calculate_binary_classification_tests(void) method

/// Returns the results of a binary classification test in a single vector.
/// The size of that vector is six.
/// The elements are:
/// <ul>
/// <li> Classification accuracy
/// <li> Error rate
/// <li> Sensitivity
/// <li> Specifity
/// <li> Positive likelihood
/// <li> Negative likelihood
/// </ul>

Vector<double> TestingAnalysis::calculate_binary_classification_tests(void) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG

   const MultilayerPerceptron* multilayer_perceptron_pointer = neural_network_pointer->get_multilayer_perceptron_pointer();

   const unsigned inputs_number = multilayer_perceptron_pointer->get_inputs_number();

   if(!data_set_pointer)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: TestingAnalysis class." << std::endl
             << "Vector<double> calculate_binary_classification_tests(void) const." << std::endl
             << "Data set is NULL." << std::endl;

      throw std::logic_error(buffer.str());
   }

   const Variables& variables = data_set_pointer->get_variables();

   const unsigned targets_number = variables.count_targets_number();

   const unsigned outputs_number = multilayer_perceptron_pointer->get_outputs_number();

   // Control sentence

   if(inputs_number != variables.count_inputs_number())
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: TestingAnalysis class." << std::endl
             << "Vector<double> calculate_binary_classification_tests(void) const." << std::endl
             << "Number of inputs in neural network is not equal to number of inputs in data set." << std::endl;

      throw std::logic_error(buffer.str());
   }
   else if(outputs_number != 1)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: TestingAnalysis class." << std::endl
             << "Vector<double> calculate_binary_classification_tests(void) const." << std::endl
             << "Number of outputs in neural network must be one." << std::endl;

      throw std::logic_error(buffer.str());
   }
   else if(targets_number != 1)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: TestingAnalysis class." << std::endl
             << "Vector<double> calculate_binary_classification_tests(void) const." << std::endl
             << "Number of targets in data set must be one." << std::endl;

      throw std::logic_error(buffer.str());
   }

   #endif

   // Confusion matrix

   const Matrix<unsigned> confusion = calculate_confusion();

   const unsigned true_positive = confusion[0][0];
   const unsigned false_positive = confusion[0][1];
   const unsigned false_negative = confusion[1][0];
   const unsigned true_negative = confusion[1][1];

   // Classification accuracy

   double classification_accuracy;

   if(true_positive + true_negative + false_positive + false_negative == 0)
   {
       classification_accuracy = 0.0;
   }
   else
   {
       classification_accuracy = (double)(true_positive + true_negative)/double(true_positive + true_negative + false_positive + false_negative);
   }

   // Error rate

   double error_rate;

   if(true_positive + true_negative + false_positive + false_negative == 0)
   {
       error_rate = 0.0;
   }
   else
   {
       error_rate = (double)(false_positive + false_negative)/(double)(true_positive + true_negative + false_positive + false_negative);
   }

   // Sensitivity

   double sensitivity;

   if(true_positive + false_negative == 0)
   {
       sensitivity = 0.0;
   }
   else
   {
       sensitivity = (double)true_positive/(double)(true_positive + false_negative);
   }

   // Specifity

   double specifity;

   if(true_negative + false_positive == 0)
   {
       specifity = 0.0;
   }
   else
   {
       specifity = (double)true_negative/(double)(true_negative + false_positive);
   }

   // Positive likelihood

   double positive_likelihood;

   if(classification_accuracy == 1.0)
   {
       positive_likelihood = 1.0;
   }
   else if(1.0 - specifity == 0.0)
   {
       positive_likelihood = 0.0;
   }
   else
   {
       positive_likelihood = sensitivity/(1.0 - specifity);
   }

   // Negative likelihood

   double negative_likelihood;

   if(classification_accuracy == 1.0)
   {
       negative_likelihood = 1.0;
   }
   else if(1.0 - sensitivity == 0.0)
   {
       negative_likelihood = 0.0;
   }
   else
   {
       negative_likelihood = specifity/(1.0 - sensitivity);
   }

   // Arrange vector

   Vector<double> binary_classification_test(6);
   binary_classification_test[0] = classification_accuracy;
   binary_classification_test[1] = error_rate;
   binary_classification_test[2] = sensitivity;
   binary_classification_test[3] = specifity;
   binary_classification_test[4] = positive_likelihood;
   binary_classification_test[5] = negative_likelihood;

   return(binary_classification_test);
}


// std::string to_string(void) const method

/// Returns a string representation of the testing analysis object. 

std::string TestingAnalysis::to_string(void) const
{
   std::ostringstream buffer;

   buffer << "Testing analysis\n"
          << "Display: " << display << "\n";

   return(buffer.str());
}


// void print(void) const method

/// Prints to the standard output the string representation of this testing analysis object. 

void TestingAnalysis::print(void) const
{
   std::cout << to_string();
}


// tinyxml2::XMLDocument* to_XML(void) const method

/// Serializes the testing analysis object into a XML document of the TinyXML library. 
/// See the OpenNN manual for more information about the format of this element. 

tinyxml2::XMLDocument* TestingAnalysis::to_XML(void) const
{
    tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument;

    std::ostringstream buffer;

    // Root element

    tinyxml2::XMLElement* testing_analysis_element = document->NewElement("TestingAnalysis");

    document->InsertFirstChild(testing_analysis_element);

    // Display

    tinyxml2::XMLElement* display_element = document->NewElement("Display");
    testing_analysis_element->LinkEndChild(display_element);

    buffer.str("");
    buffer << display;

    tinyxml2::XMLText* display_text = document->NewText(buffer.str().c_str());
    testing_analysis_element->LinkEndChild(display_text);

    return(document);
}


// void from_XML(const tinyxml2::XMLDocument&) method

/// Deserializes a TinyXML document into this testing analysis object.
/// @param document XML document containing the member data.

void TestingAnalysis::from_XML(const tinyxml2::XMLDocument& document)
{
    std::ostringstream buffer;

    const tinyxml2::XMLElement* root_element = document.FirstChildElement("TestingAnalysis");

    if(!root_element)
    {
        buffer << "OpenNN Exception: TestingAnalysis class.\n"
               << "void from_XML(const tinyxml2::XMLDocument&) method.\n"
               << "Testing analysis element is NULL.\n";

        throw std::logic_error(buffer.str());
    }

    // Display

    const tinyxml2::XMLElement* element = root_element->FirstChildElement("Display");

    if(element)
    {
       std::string new_display_string = element->GetText();

       try
       {
          set_display(new_display_string != "0");
       }
       catch(const std::logic_error& e)
       {
          std::cout << e.what() << std::endl;
       }
    }
}


// void save(const std::string&) const method

/// Saves to a XML file the members of this testing analysis object.
/// @param file_name Name of testing analysis XML file.

void TestingAnalysis::save(const std::string& file_name) const
{
    tinyxml2::XMLDocument* document = to_XML();

    document->SaveFile(file_name.c_str());

    delete document;
}


// void load(const std::string&) method

/// Loads from a XML file the members for this testing analysis object.
/// @param file_name Name of testing analysis XML file.

void TestingAnalysis::load(const std::string& file_name)
{
    set_default();

   tinyxml2::XMLDocument document;

   if(document.LoadFile(file_name.c_str()))
   {
       std::ostringstream buffer;

      buffer << "OpenNN Exception: Testing analysis class.\n"
             << "void load(const std::string&) method.\n"
             << "Cannot load XML file " << file_name << ".\n";

      throw std::logic_error(buffer.str());
   }

   from_XML(document);
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
