/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   V E C T O R   C O N T A I N E R                                                                            */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __VECTOR_H__
#define __VECTOR_H__

// System includes

#include <algorithm> 
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator> 
#include <istream> 
#include <ostream> 
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// OpenNN includes

namespace OpenNN
{

// Forward declarations

template<class Type> class Matrix;

double calculate_random_uniform(const double&, const double&);
double calculate_random_normal(const double&, const double&);

template<class Type> struct Histogram;
template<class Type> struct Statistics;
template<class Type> struct LinearRegressionParameters;


/// This template class defines a vector for general purpose use.
/// This vector also implements some mathematical methods which can be useful. 

template <class Type> 
class Vector : public std::vector<Type>
{

public:

// CONSTRUCTORS

/// Default constructor. It creates a vector of size zero.

explicit Vector(void) : std::vector<Type>()
{
}


/// General constructor. It creates a vector of size n, containing n copies of the default value for Type.
/// @param new_size Size of vector.

explicit Vector(const unsigned& new_size) : std::vector<Type>(new_size)
{
}


/// Constant reference initialization constructor.
/// It creates a vector of size n, containing n copies of the type value of Type. 
/// @param new_size Size of Vector.
/// @param value Initialization value of Type.

explicit Vector(const unsigned& new_size, const Type& value) : std::vector<Type>(new_size, value)
{
}


/// File constructor. It creates a vector object by loading its members from a data file.
/// @param file_name Name of vector data file.

explicit Vector(const std::string& file_name) : std::vector<Type>()
{
   load(file_name);
}


/// Sequential constructor. 

explicit Vector(const Type& first, const double& step, const Type& last) : std::vector<Type>()
{
   set(first, step, last);
}


/// Input iterators constructor 

template<class InputIterator>
Vector(InputIterator first, InputIterator last) : std::vector<Type>(first, last)
{
}

  
/// Copy constructor. It creates a copy of an existing Vector. 
/// @param other_vector Vector to be copied.

Vector(const Vector<Type>& other_vector) : std::vector<Type>(other_vector)
{
}


// DESTRUCTOR

/// Destructor. 

~Vector(void)
{
}


// bool  == (const Type&) const

/// Equal to operator between this vector and a Type value.
/// It produces true if all the elements of this vector are equal to the Type value, and false otherwise.
/// @param value Type value to be compared with.

inline bool operator == (const Type& value) const
{  
   const unsigned this_size = this->size();
     
   for(unsigned i = 0; i < this_size; i++)
   {
      if((*this)[i] != value)
      {
         return(false);
      }     
   }
   
   return(true);
}


// bool operator != (const Type&) const

/// Not equivalent relational operator between this vector and a Type value.
/// It produces true if some element of this vector is not equal to the Type value, and false otherwise.
/// @param value Type value to be compared with.

inline bool operator != (const Type& value) const
{            
   const unsigned this_size = this->size(); 

   for(unsigned i = 0; i < this_size; i++)
   {
      if((*this)[i] != value)
      {
         return(true);
      }     
   }

   return(false);
}


// bool operator > (const Type&) const

/// Greater than relational operator between this vector and a Type value.
/// It produces true if all the elements of this vector are greater than the Type value, and false otherwise.
/// @param value Type value to be compared with.

inline bool operator > (const Type& value) const
{
   const unsigned this_size = this->size();      
       
   for(unsigned i = 0; i < this_size; i++)
   {
      if((*this)[i] <= value)
      {
         return(false);
      }     
   }
   
   return(true);
}


// bool operator < (const Type&) const

/// Less than relational operator between this vector and a Type value.
/// It produces true if all the elements of this vector are less than the Type value, and false otherwise.
/// @param value Type value to be compared with.

inline bool operator < (const Type& value) const
{ 
   const unsigned this_size = this->size(); 
       
   for(unsigned i = 0; i < this_size; i++)
   {
      if((*this)[i] >= value)
      {
         return(false);
      }     
   }
   
   return(true);
}


// bool operator >= (const Type&) const

/// Greater than or equal to than relational operator between this vector and a Type value.
/// It produces true if all the elements of this vector are greater than or equal to the Type value, and false otherwise.
/// @param value Type value to be compared with.

inline bool operator >= (const Type& value) const
{       
   const unsigned this_size = this->size();

   for(unsigned i = 0; i < this_size; i++)
   {
      if((*this)[i] < value)
      {
         return(false);
      }     
   }
   
   return(true);
}


// bool operator <= (const Type&) const

/// Less than or equal to than relational operator between this vector and a Type value.
/// It produces true if all the elements of this vector are less than or equal to the Type value, and false otherwise.
/// @param value Type value to be compared with.

inline bool operator <= (const Type& value) const
{   
   const unsigned this_size = this->size(); 

   for(unsigned i = 0; i < this_size; i++)
   {
      if((*this)[i] > value)
      {
         return(false);
      }     
   }
   
   return(true);
}


// METHODS

// void set(void) method

/// Sets the size of a vector to zero.

void set(void) 
{
   this->resize(0);
}


// void set(unsigned) method

/// Sets a new size to the vector. It does not initialize the data.
/// @param new_size Size for the vector.

void set(const unsigned& new_size)
{
   this->resize(new_size);
}


// void set(const unsigned&, const Type&) method

/// Sets a new size to the vector and initializes all its elements with a given value.
/// @param new_size Size for the vector.
/// @param new_value Value for all the elements.

void set(const unsigned& new_size, const Type& new_value)
{
   this->resize(new_size);

   initialize(new_value);
}


// void set(const std::string&) method

/// Sets all the members of a vector object by loading them from a data file.
/// The format is specified in the OpenNN manual. 
/// @param file_name Name of vector data file.

void set(const std::string& file_name)
{
   load(file_name);
}


// void set(const Type&, const double&, const Type&) method

/// Makes this vector to have elements starting from a given value, continuing with a step value and finishing with a given value.
/// Depending on the starting, step and finishin values, this method can produce a variety of sizes and data. 
/// @param first Starting value. 
/// @param step Step value. 
/// @param last Finishing value. 

void set(const Type& first, const double& step, const Type& last) 
{
   if(first > last && step > 0 )
   {
      this->resize(0);
   }
   else if(first < last && step < 0)
   {
      this->resize(0);
   }
   else
   {
      const unsigned new_size = 1 + (unsigned)((last - first)/step + 0.5);

      this->resize(new_size);

      for(unsigned i = 0; i < new_size; i++)
      {
         (*this)[i] = first + i*step;
      }
   }
}


// void set(const Vector&) method

/// Sets the members of this object with the values of another vector.
/// @param other_vector Object to set this vector. 

void set(const Vector& other_vector)
{
   *this = other_vector;
}


// void initialize(const Type&) method

/// Initializes all the elements of the vector with a given value.
/// @param value Type value.

void initialize(const Type& value)
{
   const unsigned this_size = this->size();

   for(unsigned i = 0; i < this_size; i++)
   {
      (*this)[i] = value;
   }
}


// void initialize_sequential(void) method

/// Initializes all the elements of the vector in a sequential order.

void initialize_sequential(void)
{
   const unsigned this_size = this->size();

   for(unsigned i = 0; i < this_size; i++)
   {
      (*this)[i] = i;
   }
}


// void randomize_uniform(void) method

/// Assigns a random value comprised between -1 and 1 to each element in the vector.

void randomize_uniform(void)
{   
   const unsigned this_size = this->size();

   for(unsigned i = 0; i < this_size; i++)
   {
      (*this)[i] = calculate_random_uniform(-1.0, 1.0);
   }
}


// void randomize_uniform(const double&, const double&) method

/// Assigns a random value comprised between a minimum value and a maximum value to each element in
/// the vector. 
/// @param minimum Minimum initialization value.  
/// @param maximum Maximum initialization value.

void randomize_uniform(const double& minimum, double maximum)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(minimum > maximum)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "void randomize_uniform(const double&, const double&) method.\n"
             << "Minimum value must be less or equal than maximum value.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   const unsigned this_size = this->size();

   for(unsigned i = 0; i < this_size; i++)
   {
      (*this)[i] = calculate_random_uniform(minimum, maximum);
   }
}


// void randomize_uniform(const Vector<double>&, const Vector<double>&) method

/// Assigns a random value comprised between given minimum and a maximum values to every element in the
/// vector. 
/// @param minimums Minimum initialization values.
/// @param maximums Maximum initialization values.

void randomize_uniform(const Vector<double>& minimums, const Vector<double>& maximums)
{
   const unsigned this_size = this->size();

   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned minimums_size = minimums.size();
   const unsigned maximums_size = maximums.size();

   if(minimums_size != this_size || maximums_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "void randomize_uniform(const Vector<double>&, const Vector<double>&) method.\n"
             << "Minimum and maximum sizes must be equal to vector size.\n";

	  throw std::logic_error(buffer.str());
   }

   if(minimums > maximums)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "void randomize_uniform(const Vector<double>&, const Vector<double>&) method.\n"
             << "Minimum values must be less or equal than their corresponding maximum values.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   for(unsigned i = 0; i < this_size; i++)
   {
      (*this)[i] = calculate_random_uniform(minimums[i], maximums[i]);
   }
}


// void randomize_normal(void) method

/// Assigns random values to each element in the vector. These are taken from a normal distribution with
/// mean 0 and standard deviation 1. 

void randomize_normal(void)
{
   const unsigned this_size = this->size();

   for(unsigned i = 0; i < this_size; i++)
   {
      (*this)[i] = calculate_random_normal(0.0, 1.0);
   }
}


// void randomize_normal(const double&, const double&) method

/// Assigns random values to each element in the vector.
/// These are taken from a normal distribution with single mean and standard deviation values for all the elements. 
/// @param mean Mean value of uniform distribution.  
/// @param standard_deviation Standard deviation value of uniform distribution.

void randomize_normal(const double& mean, double standard_deviation)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(standard_deviation < 0.0)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "void randomize_normal(const double&, const double&) method.\n"
             << "Standard deviation must be equal or greater than zero.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   const unsigned this_size = this->size();

   for(unsigned i = 0; i < this_size; i++)
   {
      (*this)[i] = calculate_random_normal(mean, standard_deviation);
   }
}


// void randomize_normal(const Vector<double>, const Vector<double>) method

/// Assigns random values to each element in the vector.
/// These are taken from normal distributions with given means and standard deviations for each element. 
/// @param mean Mean values of normal distributions.  
/// @param standard_deviation Standard deviation values of normal distributions.

void randomize_normal(const Vector<double>& mean, const Vector<double>& standard_deviation)
{
   const unsigned this_size = this->size();

   // Control sentence (if debug)

   #ifndef NDEBUG 
 
   const unsigned mean_size = mean.size();
   const unsigned standard_deviation_size = standard_deviation.size();

   if(mean_size != this_size || standard_deviation_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "void randomize_normal(const Vector<double>&, const Vector<double>&) method.\n"
             << "Mean and standard deviation sizes must be equal to vector size.\n";

	  throw std::logic_error(buffer.str());
   }

   if(standard_deviation < 0.0)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "void randomize_normal(const Vector<double>&, const Vector<double>&) method.\n"
             << "Standard deviations must be equal or greater than zero.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   for(unsigned i = 0; i < this_size; i++)
   {
      (*this)[i] = calculate_random_normal(mean[i], standard_deviation[i]);
   }
}


// bool contains(const Type&) const method

/// Returns true if the vector contains a certain value, and false otherwise.

bool contains(const Type& value) const
{
   const unsigned this_size = this->size();

   for(unsigned i = 0; i < this_size; i++)
   {
      if((*this)[i] == value)
      {
          return(true);
      }
   }

   return(false);
}


// bool contains(const Vector<Type>&) const method

/// Returns true if the vector contains a certain value from a given set, and false otherwise.

bool contains(const Vector<Type>& values) const
{
   const unsigned this_size = this->size();

   const unsigned values_size = values.size();

   for(unsigned i = 0; i < this_size; i++)
   {
       for(unsigned j = 0; j < values_size; j++)
       {
           if((*this)[i] == values[j])
           {
              return(true);
           }
       }
   }

   return(false);
}


// bool is_in(const Type&, const Type&) const method

/// Returns true if the value of all the elements fall in some given range,
/// and false otherwise.
/// @param minimum Minimum value of the range.
/// @param maximum Maximum value of the range.

bool is_in(const Type& minimum, const Type& maximum) const
{
    const unsigned this_size = this->size();

    for(unsigned i = 0; i < this_size; i++)
    {
       if((*this)[i] < minimum || (*this)[i] > maximum)
       {
           return(false);
       }
    }

    return(true);
}


// bool is_constant(const double&) const method

/// Returns true if all the elements have the same value within a defined tolerance ,
/// and false otherwise.
/// @param tolerance Tolerance value, so that if abs(max-min) <= tol, then the vector is considered constant.

bool is_constant(const double& tolerance = 0.0) const
{
    const unsigned this_size = this->size();

    if(this_size == 0)
    {
        return(false);
    }

    const Type minimum = calculate_minimum();
    const Type maximum = calculate_maximum();

    if(fabs(maximum-minimum) <= tolerance)
    {
        return(true);
    }
    else
    {
        return(false);
    }
}


// unsigned count_occurrences(const Type&) const method

/// Returns the number of times that a certain value is contained in the vector.

unsigned count_occurrences(const Type& value) const
{
   const unsigned this_size = this->size();

   unsigned count = 0;

   for(unsigned i = 0; i < this_size; i++)
   {
      if((*this)[i] == value)
      {
          count++;
      }
   }

   return(count);
}


// Vector<unsigned> calculate_occurrence_indices(const Type&) const method

/// Returns the vector indices at which the vector elements take some given value.
/// @param value Value.

Vector<unsigned> calculate_occurrence_indices(const Type& value) const
{
   const unsigned this_size = this->size();

   const unsigned occurrences_number = count_occurrences(value);

   Vector<unsigned> occurrence_indices(occurrences_number);

   unsigned index = 0;

   for(unsigned i = 0; i < this_size; i++)
   {
      if((*this)[i] == value)
      {
          occurrence_indices[index] = i;
          index++;
      }
   }

   return(occurrence_indices);
}


// Type calculate_minimum(void) const method

/// Returns the smallest element in the vector.

Type calculate_minimum(void) const
{
   const unsigned this_size = this->size();

   Type minimum = (*this)[0];

   for(unsigned i = 1; i < this_size; i++)
   {
      if((*this)[i] < minimum)
      {
         minimum = (*this)[i];
      }
   }
   
   return(minimum);
}


// Type calculate_maximum(void) const method

/// Returns the largest element in the vector.

Type calculate_maximum(void) const
{
   const unsigned this_size = this->size();

   Type maximum = (*this)[0];

   for(unsigned i = 1; i < this_size; i++)
   {
      if((*this)[i] > maximum)
      {
         maximum = (*this)[i];
      }
   }
   
   return(maximum);
}


// Vector<Type> calculate_minimum_maximum(void) const method

/// Returns a vector containing the smallest and the largest elements in the vector.

Vector<Type> calculate_minimum_maximum(void) const
{
   unsigned this_size = this->size();

   Type minimum = (*this)[0];
   Type maximum = (*this)[0];

   for(unsigned i = 1; i < this_size; i++)
   {
      if((*this)[i] < minimum)
      {
         minimum = (*this)[i];
      }

      if((*this)[i] > maximum)
      {
         maximum = (*this)[i];
      }
   }

   Vector<Type> minimum_maximum(2);
   minimum_maximum[0] = minimum;
   minimum_maximum[1] = maximum;

   return(minimum_maximum);
}


// Histogram<Type> calculate_histogram(const unsigned&) const method

/// This method bins the elements of the vector into a given number of equally spaced containers.
/// It returns a vector of two vectors. 
/// The size of both subvectors is the number of bins. 
/// The first subvector contains the frequency of the bins. 
/// The second subvector contains the center of the bins. 

Histogram<Type> calculate_histogram(const unsigned& bins_number = 10) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(bins_number < 1)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "Histogram<Type> calculate_histogram(const unsigned&) const method.\n"
             << "Number of bins is less than one.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   Vector<Type> minimums(bins_number);
   Vector<Type> maximums(bins_number);

   Vector<Type> centers(bins_number);
   Vector<unsigned> frequencies(bins_number, 0);

   const Vector<Type> minimum_maximum = calculate_minimum_maximum();
  
   const Type minimum = minimum_maximum[0];
   const Type maximum = minimum_maximum[1];

   const double length = (maximum-minimum)/(double)bins_number;

   minimums[0] = minimum;
   maximums[0] = minimum + length;
   centers[0] = (maximums[0] + minimums[0])/2.0;

   // Calculate bins center

   for(unsigned i = 1; i < bins_number; i++)
   {
      minimums[i] = minimums[i-1] + length;
      maximums[i] = maximums[i-1] + length;

      centers[i] = (maximums[i] + minimums[i])/2.0;
   }

   // Calculate bins frequency

   const unsigned this_size = this->size();

   for(unsigned i = 0; i < this_size; i++)
   {
      if((*this)[i] < centers[0])
      {
         frequencies[0]++;
      }

      for(unsigned j = 1; j < bins_number-1; j++)
      {
         if((*this)[i] >= minimums[j] && (*this)[i] < maximums[j])
		 {
            frequencies[j]++;
		 }
	  }

      if((*this)[i] >= centers[bins_number-1])
      {
         frequencies[bins_number-1]++;
      }
   }

   Histogram<Type> histogram(bins_number);
   histogram.centers = centers;
   histogram.frequencies = frequencies;

   return(histogram);
}


// unsigned calculate_minimal_index(void) const method

/// Returns the index of the smallest element in the vector.

unsigned calculate_minimal_index(void) const
{
   const unsigned this_size = this->size();

   Type minimum = (*this)[0];
   unsigned minimal_index = 0;

   for(unsigned i = 1; i < this_size; i++)
   {
      if((*this)[i] < minimum)
      {
         minimum = (*this)[i];
         minimal_index = i;
      }
   }
   
   return(minimal_index);
}


// unsigned calculate_maximal_index(void) const method

/// Returns the index of the largest element in the vector.

unsigned calculate_maximal_index(void) const
{
   const unsigned this_size = this->size();

   Type maximum = (*this)[0];
   unsigned maximal_index = 0;

   for(unsigned i = 1; i < this_size; i++)
   {
      if((*this)[i] > maximum)
      {
         maximum = (*this)[i];
         maximal_index = i;
      }
   }
   
   return(maximal_index);
}


// Vector<unsigned> calculate_minimal_indices(const unsigned&) const method

/// Returns the indices of the smallest elements in the vector.
/// @param number Number of minimal indices to be computed.

Vector<unsigned> calculate_minimal_indices(const unsigned& number) const
{
   const unsigned this_size = this->size();

   const Vector<unsigned> rank = this->calculate_less_rank();

   Vector<unsigned> minimal_indices(number);

   for(unsigned i = 0; i < this_size; i++)
   {
       for(unsigned j = 0; j < number; j++)
       {
           if(rank[i] == j)
           {
               minimal_indices[j] = i;
           }
       }
   }

   return(minimal_indices);
}


// Vector<unsigned> calculate_maximal_indices(const unsigned&) const method

/// Returns the indices of the largest elements in the vector.
/// @param number Number of maximal indices to be computed.

Vector<unsigned> calculate_maximal_indices(const unsigned& number) const
{
    const unsigned this_size = this->size();

    const Vector<unsigned> rank = this->calculate_greater_rank();

    Vector<unsigned> maximal_indices(number);

    for(unsigned i = 0; i < this_size; i++)
    {
        for(unsigned j = 0; j < number; j++)
        {
            if(rank[i] == j)
            {
                maximal_indices[j] = i;
            }
        }
    }

   return(maximal_indices);
}


// Vector<unsigned> calculate_minimal_maximal_index(void) const method

/// Returns a vector with the indexes of the smallest and the largest elements in the vector.

Vector<unsigned> calculate_minimal_maximal_index(void) const
{
   const unsigned this_size = this->size();

   Type minimum = (*this)[0];
   Type maximum = (*this)[0];

   unsigned minimal_index = 0;
   unsigned maximal_index = 0;

   for(unsigned i = 1; i < this_size; i++)
   {
      if((*this)[i] < minimum)
      {
         minimum = (*this)[i];
         minimal_index = i;
      }
      if((*this)[i] > maximum)
      {
         maximum = (*this)[i];
         maximal_index = i;
      }
   }

   Vector<unsigned> minimal_maximal_index(2);
   minimal_maximal_index[0] = minimal_index;
   minimal_maximal_index[1] = maximal_index;
   
   return(minimal_maximal_index);
}


// Vector<double> calculate_pow(const Type&) const method

/// Returns a vector with the elements of this vector raised to a power exponent.
/// @param exponent Pow exponent. 

Vector<Type> calculate_pow(const Type& exponent) const
{
   const unsigned this_size = this->size();

   Vector<Type> power(this_size);

   for(unsigned i = 0; i < this_size; i++)
   {
      power[i] = pow((*this)[i], exponent);
   }

   return(power);
}


// Vector<double> calculate_competitive(void) const method

/// Returns the competitive vector of this vector,
/// whose elements are one the bigest element of this vector, and zero for the other elements. 

Vector<Type> calculate_competitive(void) const
{
   const unsigned this_size = this->size();

   Vector<Type> competitive(this_size, 0);

   const unsigned maximal_index = calculate_maximal_index();

   competitive[maximal_index] = 1;

   return(competitive);
}


// Vector<Type> calculate_softmax(void) const method 

/// Returns the softmax vector of this vector,
/// whose elements sum one, and can be interpreted as probabilities. 

Vector<Type> calculate_softmax(void) const
{
   const unsigned this_size = this->size();

   Vector<Type> softmax(this_size);

   Type sum = 0;

   for(unsigned i = 0; i < this_size; i++)
   {
      sum += exp((*this)[i]);
   }

   for(unsigned i = 0; i < this_size; i++)
   {
      softmax[i] = exp((*this)[i])/sum;
   }

   return(softmax);
}


// Matrix<Type> calculate_softmax_Jacobian(void) const method 

/// Returns the softmax Jacobian of this vector.

Matrix<Type> calculate_softmax_Jacobian(void) const
{
   const unsigned this_size = this->size();

   Matrix<Type> softmax_Jacobian(this_size, this_size);

   for(unsigned i = 0; i < this_size; i++)
   {
       for(unsigned j = 0; j < this_size; j++)
       {
           if(i == j)
           {
               softmax_Jacobian[i][i] = (*this)[i]*(1.0 - (*this)[i]);
           }
           else
           {
               softmax_Jacobian[i][i] = (*this)[i]*(*this)[j];
           }
       }
   }

   return(softmax_Jacobian);
}


// Vector<bool> calculate_binary(void) const method 

/// This method converts the values of the vector to be binary. 
/// The threshold value used is 0.5.

Vector<bool> calculate_binary(void) const
{
   const unsigned this_size = this->size();

   Vector<bool> binary(this_size);

   for(unsigned i = 0; i < this_size; i++)
   {
      if((*this)[i] < 0.5)
	  {
	     binary[i] = false;
	  }
	  else
	  {
	     binary[i] = true;	  
	  }
   }

   return(binary);
}


// Vector<Type> calculate_cumulative(void) const method

/// Return the cumulative vector of this vector,
/// where each element is summed up with all the previous ones.

Vector<Type> calculate_cumulative(void) const
{
    const unsigned this_size = this->size();

    Vector<Type> cumulative(this_size);

    if(this_size > 0)
    {
        cumulative[0] = (*this)[0];

        for(unsigned i = 1; i < this_size; i++)
        {
           cumulative[i] = cumulative[i-1] + (*this)[i];
        }
    }

    return(cumulative);
}


// unsigned calculate_cumulative_index(const Type&) const method

/// This method applies only to cumulative vectors. 
/// It returns the index of the first element which is greater than a given value.
/// @param value Value. 

unsigned calculate_cumulative_index(const Type& value) const
{
   const unsigned this_size = this->size();

   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(this_size == 0)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "unsigned calculate_cumulative_index(const Type&) const.\n"
             << "Size must be greater than zero.\n";

	  throw std::logic_error(buffer.str());
   }

   Type cumulative_value = (*this)[this_size-1];

   if(value > cumulative_value)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "unsigned calculate_cumulative_index(const Type&) const.\n"
             << "Value (" << value << ") must be less than cumulative value (" << cumulative_value << ").\n";

	  throw std::logic_error(buffer.str());
   }

   for(unsigned i = 1; i < this_size; i++)
   {
      if((*this)[i] < (*this)[i-1])
      {
         std::ostringstream buffer;

         buffer << "OpenNN Exception: Vector Template.\n" 
                << "int calculate_cumulative_index(const Type&) const.\n"
                << "Vector elements must be crescent.\n";

	  throw std::logic_error(buffer.str());
      }   
   }

   #endif

   if(value <= (*this)[0])
   {
      return(0);         
   }

   for(unsigned i = 1; i < this_size; i++)
   {
      if(value > (*this)[i-1] && value <= (*this)[i])
      {
         return(i);         
	  }
   }
   
   return(this_size-1);
}


// unsigned calculate_closest_index(const Type&) const method

/// Returns the index of the closest element in the vector to a given value.

unsigned calculate_closest_index(const Type& value) const
{
   const Vector<Type> difference = (*this - value).calculate_absolute_value();

   const unsigned closest_index = difference.calculate_minimal_index();
   
   return(closest_index);
}


// Type calculate_sum(void) const method

/// Returns the sum of the elements in the vector.

Type calculate_sum(void) const
{
   const unsigned this_size = this->size();

   Type sum = 0;

   for(unsigned i = 0; i < this_size; i++)
   {
      sum += (*this)[i];
   }
   
   return(sum);
}


// Type calculate_product(void) const method

/// Returns the product of the elements in the vector.

Type calculate_product(void) const 
{   
   const unsigned this_size = this->size();

   Type product = 1;

   for(unsigned i = 0; i < this_size; i++)
   {
      product *= (*this)[i];
   }
   
   return(product);
}


// double calculate_mean(void) const method

/// Returns the mean of the elements in the vector.

double calculate_mean(void) const
{
   const unsigned this_size = this->size();

   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(this_size == 0)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "double calculate_mean(void) const method.\n"
             << "Size must be greater than zero.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   const Type sum = calculate_sum();

   const double mean = sum/(double)this_size;
   
   return(mean);
}


// double calculate_standard_deviation(void) method

/// Returns the standard deviation of the elements in the vector.

double calculate_standard_deviation(void) const
{
   const unsigned this_size = this->size();

   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(this_size == 0)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "double calculate_standard_deviation(void) const method.\n"
             << "Size must be greater than zero.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   if(this_size == 1)
   {
       return(0.0);
   }

   double sum = 0.0;
   double squared_sum = 0.0;

   for(unsigned i = 0; i < this_size; i++)
   {
       sum += (*this)[i];
       squared_sum += (*this)[i]*(*this)[i];
   }

   const double numerator = squared_sum - (sum*sum)/this_size;
   const double denominator = this_size - 1.0;

   return(sqrt(numerator/denominator));
}


// Vector<double> calculate_mean_standard_deviation(void) const method

/// Returns the mean and the standard deviation of the elements in the vector.

Vector<double> calculate_mean_standard_deviation(void) const
{
   const unsigned this_size = this->size();

   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(this_size == 0)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "double calculate_mean_standard_deviation(void).\n"
             << "Size must be greater than zero.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   const double mean = calculate_mean();
   const double standard_deviation = calculate_standard_deviation();

   Vector<double> mean_standard_deviation(2);
   mean_standard_deviation[0] = mean;
   mean_standard_deviation[1] = standard_deviation;

   return(mean_standard_deviation);
}


// Statistics<Type> calculate_statistics(void) const method

/// Returns the minimum, maximum, mean and the standard deviation of the elements in the vector.

Statistics<Type> calculate_statistics(void) const
{
    const unsigned this_size = this->size();

   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(this_size == 0)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "double calculate_statistics(void).\n"
             << "Size must be greater than zero.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   Statistics<Type> statistics;
   statistics.minimum = calculate_minimum();
   statistics.maximum = calculate_maximum();
   statistics.mean = calculate_mean();
   statistics.standard_deviation = calculate_standard_deviation();

   return(statistics);
}


// double calculate_norm(void) const method

/// Returns the vector norm.

double calculate_norm(void) const
{
   const unsigned this_size = this->size();

   // Control sentence (if debug)

   double norm = 0.0;

   for(unsigned i = 0; i < this_size; i++)
   {
      norm += (*this)[i]*(*this)[i];
   }
   
   norm = sqrt(norm);
   
   return(norm);
}


// Vector<Type> calculate_norm_gradient(void) const method

/// Returns the gradient of the vector norm.

Vector<Type> calculate_norm_gradient(void) const
{
   const unsigned this_size = this->size();

   // Control sentence (if debug)

   Vector<Type> gradient(this_size);

   const double norm = calculate_norm();

   if(norm == 0.0)
   {
        gradient.initialize(0.0);
   }
   else
   {
       gradient = (*this)/norm;
   }

   return(gradient);
}


// Matrix<Type> calculate_norm_Hessian(void) const method

/// Returns the Hessian of the vector norm.

Matrix<Type> calculate_norm_Hessian(void) const
{
   const unsigned this_size = this->size();

   // Control sentence (if debug)

   Matrix<Type> Hessian(this_size, this_size);

   const double norm = calculate_norm();

   if(norm == 0.0)
   {
       Hessian.initialize(0.0);
   }
   else
   {
       Hessian = (*this).direct(*this)/pow(norm, 3);
   }

   return(Hessian);
}


// double calculate_p_norm(const double&) const method

/// Returns the vector p-norm.

double calculate_p_norm(const double& p) const
{
    // Control sentence (if debug)

    #ifndef NDEBUG

    std::ostringstream buffer;

    if(p <= 0)
    {
       buffer << "OpenNN Exception: Vector Template.\n"
              << "double calculate_p_norm(const double&) const method.\n"
              << "p value must be greater than zero.\n";

       throw std::logic_error(buffer.str());
    }

    #endif

   const unsigned this_size = this->size();

   // Control sentence (if debug)

   double norm = 0.0;

   for(unsigned i = 0; i < this_size; i++)
   {
      norm += pow(fabs((*this)[i]), p);
   }

   norm = pow(norm, 1.0/p);

   return(norm);
}


// Vector<double> calculate_p_norm_gradient(const double&) const method

/// Returns the gradient of the vector norm.

Vector<double> calculate_p_norm_gradient(const double& p) const
{
    // Control sentence (if debug)

    #ifndef NDEBUG

    std::ostringstream buffer;

    if(p <= 0)
    {
       buffer << "OpenNN Exception: Vector Template.\n"
              << "Vector<double> calculate_p_norm_gradient(const double&) const method.\n"
              << "p value must be greater than zero.\n";

       throw std::logic_error(buffer.str());
    }

    #endif

   const unsigned this_size = this->size();

   // Control sentence (if debug)

   Vector<double> gradient(this_size);

   const double p_norm = calculate_p_norm(p);

   if(p_norm == 0.0)
   {
        gradient.initialize(0.0);
   }
   else
   {
       for(unsigned i = 0; i < this_size; i++)
       {
           gradient[i] = (*this)[i]*pow(fabs((*this)[i]),p-2.0)/pow(p_norm, p-1.0);
       }

//       gradient = (*this)*(*this).calculate_pow(p-2.0)/pow(p_norm, p-1.0);
   }

   return(gradient);
}


// double calculate_normalized(void) const method

/// Returns this vector divided by its norm.

Vector<Type> calculate_normalized(void) const
{
    const unsigned this_size = (*this).size();

    Vector<Type> normalized(this_size);

    const double norm = calculate_norm();

    if(norm == 0.0)
    {
        normalized.initialize(0.0);
    }
    else
    {
        normalized = (*this)/norm;
    }

    return(normalized);
}


// double calculate_distance(const Vector<double>&) const method

/// Returns the distance between the elements of this vector and the elements of another vector.
/// @param other_vector Other vector. 

double calculate_distance(const Vector<double>& other_vector) const
{
   return( sqrt(calculate_sum_squared_error(other_vector)) );
}


// double calculate_sum_squared_error(const Vector<double>&) const method

/// Returns the sum squared error between the elements of this vector and the elements of another vector.
/// @param other_vector Other vector. 

double calculate_sum_squared_error(const Vector<double>& other_vector) const
{
   const unsigned this_size = this->size();

   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned other_size = other_vector.size();

   if(other_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "double calculate_sum_squared_error(const Vector<double>&) const method.\n"
             << "Size must be equal to this size.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   double sum_squared_error = 0.0;

   for(unsigned i = 0; i < this_size; i++)
   {
      sum_squared_error += ((*this)[i] - other_vector[i])*((*this)[i] - other_vector[i]);
   }

   return(sum_squared_error);
}


// double calculate_Minkowski_error(const Vector<double>&) const method

/// Returns the Minkowski squared error between the elements of this vector and the elements of another vector.
/// @param other_vector Other vector. 
/// @param Minkowski_parameter Minkowski exponent. 

double calculate_Minkowski_error(const Vector<double>& other_vector, double Minkowski_parameter) const
{
   const unsigned this_size = this->size();

   // Control sentence (if debug)

   #ifndef NDEBUG 

   std::ostringstream buffer;

   if(this_size == 0)
   {
      buffer << "OpenNN Exception: Vector Template.\n" 
             << "double calculate_Minkowski_error(const Vector<double>&) const method.\n"
             << "Size must be greater than zero.\n";

	  throw std::logic_error(buffer.str());
   }

   const unsigned other_size = other_vector.size();

   if(other_size != this_size)
   {
      buffer << "OpenNN Exception: Vector Template.\n" 
             << "double calculate_Minkowski_error(const Vector<double>&) const method.\n"
             << "Other size must be equal to this size.\n";

	  throw std::logic_error(buffer.str());
   }

   // Control sentence

   if(Minkowski_parameter < 1.0 || Minkowski_parameter > 2.0)
   {
      buffer << "OpenNN Exception: Vector Template.\n" 
             << "double calculate_Minkowski_error(const Vector<double>&) const method.\n"
             << "The Minkowski parameter must be comprised between 1 and 2\n";
    
      throw std::logic_error(buffer.str());
   }

   #endif

   double Minkowski_error = 0.0;

   for(unsigned i = 0; i < this_size; i++)
   {
      Minkowski_error += pow(fabs((*this)[i] - other_vector[i]), Minkowski_parameter);
   }   

   Minkowski_error = pow(Minkowski_error, 1.0/Minkowski_parameter);

   return(Minkowski_error);
}


// Type calculate_linear_correlation(const Vector<Type>&) const method

/// Calculates the linear correlation coefficient (R-value) between another vector and this vector.
/// @param other Vector for computing the linear correlation with this vector.

Type calculate_linear_correlation(const Vector<Type>& other) const
{
    const unsigned n = this->size();

    // Control sentence (if debug)

    #ifndef NDEBUG

    const unsigned other_size = other.size();

    std::ostringstream buffer;

    if(other_size != n)
    {
       buffer << "OpenNN Exception: Vector Template.\n"
              << "Type calculate_linear_correlation(const Vector<Type>&) const method.\n"
              << "Other size must be equal to this size.\n";

       throw std::logic_error(buffer.str());
    }

    #endif

    Type s_x = 0;
    Type s_y = 0;

    Type s_xx = 0;
    Type s_yy = 0;

    Type s_xy = 0;

    for(unsigned i = 0; i < n; i++)
    {
        s_x += other[i];
        s_y += (*this)[i];

        s_xx += other[i]*other[i];
        s_yy += (*this)[i]*(*this)[i];

        s_xy += other[i]*(*this)[i];
    }

    Type linear_correlation;

    if(s_x == 0 && s_y == 0 && s_xx == 0 && s_yy == 0 && s_xy == 0)
    {
        linear_correlation = 1;
    }
    else
    {
        linear_correlation = (n*s_xy - s_x*s_y)
        /sqrt((n*s_xx - s_x*s_x)*(n*s_yy - s_y*s_y));
    }

    return(linear_correlation);
}


// LinearRegressionParameters<Type> calculate_linear_regression_parameters(const Vector<Type>&) const method

/// Calculates the linear regression parameters (intercept, slope and correlation) between another vector and this vector.
/// It returns a linear regression parameters structure.
/// @param other Other vector for the linear regression analysis.

LinearRegressionParameters<Type> calculate_linear_regression_parameters(const Vector<Type>& other) const
{
    const unsigned n = this->size();

    // Control sentence (if debug)

    #ifndef NDEBUG

    const unsigned other_size = other.size();

    std::ostringstream buffer;

    if(other_size != n)
    {
       buffer << "OpenNN Exception: Vector Template.\n"
              << "LinearRegressionParameters<Type> calculate_linear_regression_parameters(const Vector<Type>&) const method.\n"
              << "Other size must be equal to this size.\n";

       throw std::logic_error(buffer.str());
    }

    #endif

    Type s_x = 0;
    Type s_y = 0;

    Type s_xx = 0;
    Type s_yy = 0;

    Type s_xy = 0;

    for(unsigned i = 0; i < n; i++)
    {
        s_x += other[i];
        s_y += (*this)[i];

        s_xx += other[i]*other[i];
        s_yy += (*this)[i]*(*this)[i];

        s_xy += other[i]*(*this)[i];
    }

    LinearRegressionParameters<Type> linear_regression_parameters;

    if(s_x == 0 && s_y == 0 && s_xx == 0 && s_yy == 0 && s_xy == 0)
    {
        linear_regression_parameters.intercept = 0;

        linear_regression_parameters.slope = 0;

        linear_regression_parameters.correlation = 1;
    }
    else
    {
        linear_regression_parameters.intercept = (s_y*s_xx - s_x*s_xy)
        /(n*s_xx - s_x*s_x);

        linear_regression_parameters.slope = (n*s_xy - s_x*s_y)
        /(n*s_xx - s_x*s_x);

        linear_regression_parameters.correlation = (n*s_xy - s_x*s_y)
        /sqrt((n*s_xx - s_x*s_x)*(n*s_yy - s_y*s_y));
    }

    return(linear_regression_parameters);
}


// void calculate_absolute_value(void) const method

/// Returns a vector with the absolute values of the current vector.

Vector<Type> calculate_absolute_value(void) const
{
   const unsigned this_size = this->size();

   Vector<Type> absolute_value(this_size);

   for(unsigned i = 0; i < this_size; i++)
   {
      if((*this)[i] > 0)
	  {
	     absolute_value[i] = (*this)[i];
	  }
	  else
      {
         absolute_value[i] = -(*this)[i];
      }
   }

   return(absolute_value);
}


// void apply_absolute_value(void) method

/// Sets the elements of the vector to their absolute values.

void apply_absolute_value(void)
{
   const unsigned this_size = this->size();

   for(unsigned i = 0; i < this_size; i++)
   {
      if((*this)[i] < 0)
      {
         (*this)[i] = -(*this)[i];
      }
   }
}


// Vector<Type> calculate_lower_bounded(const Type&) const method

/// Returns a vector with the bounded elements from below of the current vector.
/// @param lower_bound Lower bound values.

Vector<Type> calculate_lower_bounded(const Type& lower_bound) const
{
   const unsigned this_size = this->size();

   Vector<Type> bounded_vector(this_size);

   for(unsigned i = 0; i < this_size; i++)
   {
      if((*this)[i] < lower_bound)
      {
         bounded_vector[i] = lower_bound;
      }
	  else
      {
         bounded_vector[i] = (*this)[i];
      }
   }

   return(bounded_vector);
}


// Vector<Type> calculate_lower_bounded(const Vector<Type>&) const method

/// Returns a vector with the bounded elements from above of the current vector.
/// @param lower_bound Lower bound values.

Vector<Type> calculate_lower_bounded(const Vector<Type>& lower_bound) const
{
   const unsigned this_size = this->size();

   // Control sentence (if debug)

   #ifndef NDEBUG 
 
   const unsigned lower_bound_size = lower_bound.size();

   if(lower_bound_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "Vector<Type> calculate_lower_bounded(const Vector<Type>&) const method.\n"
             << "Lower bound size must be equal to vector size.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   Vector<Type> bounded_vector(this_size);

   // Apply lower bound

   for(unsigned i = 0; i < this_size; i++)
   {
      if((*this)[i] < lower_bound[i])
      {
         bounded_vector[i] = lower_bound[i];
      }
      else
      {
         bounded_vector[i] = (*this)[i];
      }
   }

   return(bounded_vector);
}


// Vector<Type> calculate_upper_bounded(const Type&) const method

/// This method bounds the elements of the vector if they fall above an upper bound value.
/// @param upper_bound Upper bound value.

Vector<Type> calculate_upper_bounded(const Type& upper_bound) const
{
   const unsigned this_size = this->size();

   Vector<Type> bounded_vector(this_size);

   for(unsigned i = 0; i < this_size; i++)
   {
      if((*this)[i] > upper_bound)
      {
         bounded_vector[i] = upper_bound;
      }
      else
      {
         bounded_vector[i] = (*this)[i];
      }
   }

   return(bounded_vector);
}


// Vector<Type> calculate_upper_bounded(const Vector<Type>&) const method

/// This method bounds the elements of the vector if they fall above their corresponding upper bound values.
/// @param upper_bound Upper bound values.

Vector<Type> calculate_upper_bounded(const Vector<Type>& upper_bound) const
{
   const unsigned this_size = this->size();

   // Control sentence (if debug)

   #ifndef NDEBUG 
 
   const unsigned upper_bound_size = upper_bound.size();

   if(upper_bound_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "Vector<Type> calculate_upper_bounded(const Vector<Type>&) const method.\n"
             << "Upper bound size must be equal to vector size.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   Vector<Type> bounded_vector(this_size);

   // Apply upper bound

   for(unsigned i = 0; i < this_size; i++)
   {
      if((*this)[i] > upper_bound[i])
      {
         bounded_vector[i] = upper_bound[i];
      }
      else
      {
         bounded_vector[i] = (*this)[i];
      }
   }

   return(bounded_vector);
}


// Vector<Type> calculate_lower_upper_bounded(const Type&, const Type&) const method

/// This method bounds the elements of the vector if they fall above or below their lower or upper
/// bound values, respectively.
/// @param lower_bound Lower bound value.
/// @param upper_bound Upper bound value.

Vector<Type> calculate_lower_upper_bounded(const Type& lower_bound, const Type& upper_bound) const
{
   const unsigned this_size = this->size();

   Vector<Type> bounded_vector(this_size);

   for(unsigned i = 0; i < this_size; i++)
   {
      if((*this)[i] < lower_bound)
      {
         bounded_vector[i] = lower_bound;
      }
      else if((*this)[i] > upper_bound)
      {
         bounded_vector[i] = upper_bound;
      }
      else
      {
         bounded_vector[i] = (*this)[i];
      }
   }

   return(bounded_vector);
}


// Vector<Type> calculate_lower_upper_bounded(const Vector<Type>&, const Vector<Type>&) const method

/// This method bounds the elements of the vector if they fall above or below their corresponding lower or upper
/// bound values, respectively.
/// @param lower_bound Lower bound values.
/// @param upper_bound Upper bound values.

Vector<Type> calculate_lower_upper_bounded(const Vector<Type>& lower_bound, const Vector<Type>& upper_bound) const
{
   const unsigned this_size = this->size();

   // Control sentence (if debug)

   #ifndef NDEBUG 
 
   const unsigned lower_bound_size = lower_bound.size();
   const unsigned upper_bound_size = upper_bound.size();

   if(lower_bound_size != this_size || upper_bound_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "Vector<Type> calculate_lower_upper_bounded(const Vector<Type>&, const Vector<Type>&) const method.\n"
             << "Lower and upper bound sizes must be equal to vector size.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   Vector<Type> bounded_vector(this_size);

   // Apply lower and upper bounds

   for(unsigned i = 0; i < this_size; i++)
   {
      if((*this)[i] < lower_bound[i])
      {
         bounded_vector[i] = lower_bound[i];
      }
      else if((*this)[i] > upper_bound[i])
      {
         bounded_vector[i] = upper_bound[i];
      }
      else
      {
         bounded_vector[i] = (*this)[i];
      }
   }

   return(bounded_vector);
}


// void apply_lower_bound(const Type&) method

/// Sets the elements of the vector to a given value if they fall below that value.
/// @param lower_bound Lower bound value.

void apply_lower_bound(const Type& lower_bound) 
{       
   const unsigned this_size = this->size();

   for(unsigned i = 0; i < this_size; i++)
   {
      if((*this)[i] < lower_bound)
      {
         (*this)[i] = lower_bound;
      }
   }
}


// void apply_lower_bound(const Vector<Type>&) method

/// Sets the elements of the vector to given values if they fall below that values.
/// @param lower_bound Lower bound values.

void apply_lower_bound(const Vector<Type>& lower_bound)
{
   const unsigned this_size = this->size();

   for(unsigned i = 0; i < this_size; i++)
   {
      if((*this)[i] < lower_bound[i])
      {
         (*this)[i] = lower_bound[i];
      }
   }
}


// void apply_upper_bound(const Type&) method

/// Sets the elements of the vector to a given value if they fall above that value.
/// @param upper_bound Upper bound value.

void apply_upper_bound(const Type& upper_bound)
{
   const unsigned this_size = this->size();

   for(unsigned i = 0; i < this_size; i++)
   {
      if((*this)[i] > upper_bound)
      {
         (*this)[i] = upper_bound;
      }
   }
}


// void apply_upper_bound(const Vector<Type>&) method

/// Sets the elements of the vector to given values if they fall above that values.
/// @param upper_bound Upper bound values.

void apply_upper_bound(const Vector<Type>& upper_bound)
{
   const unsigned this_size = this->size();

   for(unsigned i = 0; i < this_size; i++)
   {
      if((*this)[i] > upper_bound[i])
      {
         (*this)[i] = upper_bound[i];
      }
   }
}


// void apply_lower_upper_bounds(const Type&, const Type&) method

/// Sets the elements of the vector to a given lower bound value if they fall below that value,
/// or to a given upper bound value if they fall above that value.
/// @param lower_bound Lower bound value.
/// @param upper_bound Upper bound value.

void apply_lower_upper_bounds(const Type& lower_bound, const Type& upper_bound)
{
   const unsigned this_size = this->size();

   for(unsigned i = 0; i < this_size; i++)
   {
      if((*this)[i] < lower_bound)
      {
         (*this)[i] = lower_bound;
      }
      else if((*this)[i] > upper_bound)
      {
         (*this)[i] = upper_bound;
      }
   }
}


// void apply_lower_upper_bounds(const Vector<Type>&, const Vector<Type>&) method

/// Sets the elements of the vector to given lower bound values if they fall below that values,
/// or to given upper bound values if they fall above that values.
/// @param lower_bound Lower bound values.
/// @param upper_bound Upper bound values.

void apply_lower_upper_bounds(const Vector<Type>& lower_bound, const Vector<Type>& upper_bound)
{
   const unsigned this_size = this->size();

   for(unsigned i = 0; i < this_size; i++)
   {
      if((*this)[i] < lower_bound[i])
      {
         (*this)[i] = lower_bound[i];
      }
      else if((*this)[i] > upper_bound[i])
      {
         (*this)[i] = upper_bound[i];
      }
   }
}


// Vector<unsigned> calculate_less_rank(void) const method

/// Returns a vector with the rank of the elements of this vector.
/// The smallest element will have rank 0, and the greatest element will have size-1.
/// That is, small values correspond with small ranks.

Vector<unsigned> calculate_less_rank(void) const
{
    const unsigned this_size = this->size();

    Vector<unsigned> rank(this_size);

    Vector<double> sorted_vector(*this);

    std::sort(sorted_vector.begin(), sorted_vector.end(), std::less<double>());

    for(unsigned i = 0; i < this_size; i++)
    {
       for(unsigned j = 0; j < this_size; j++)
       {
          if((*this)[i] == sorted_vector[j])
          {
             rank[i] = j;
          }
       }
    }

    return(rank);
}


// Vector<unsigned> calculate_greater_rank(void) const method

/// Returns a vector with the rank of the elements of this vector.
/// The smallest element will have rank size-1, and the greatest element will have 0.
/// That is, small values correspond to big ranks.

Vector<unsigned> calculate_greater_rank(void) const
{
    const unsigned this_size = this->size();

    Vector<unsigned> rank(this_size);

    Vector<double> sorted_vector(*this);

    std::sort(sorted_vector.begin(), sorted_vector.end(), std::greater<double>());

    for(unsigned i = 0; i < this_size; i++)
    {
       for(unsigned j = 0; j < this_size; j++)
       {
          if((*this)[i] == sorted_vector[j])
          {
             rank[i] = j;
          }
       }
    }

    return(rank);
}


// Vector<Type> operator + (const Type&) const method 

/// Sum vector+scalar arithmetic operator. 
/// @param scalar Scalar value to be added to this vector.

inline Vector<Type> operator + (const Type& scalar) const
{       
   const unsigned this_size = this->size();

   Vector<Type> sum(this_size);

   for(unsigned i = 0; i < this_size; i++)
   {
      sum[i] = (*this)[i] + scalar;
   }
   
   return(sum);
}


// Vector<Type> operator + (const Vector<Type>&) const method

/// Sum vector+vector arithmetic operator. 
/// @param other_vector Vector to be added to this vector.

inline Vector<Type> operator + (const Vector<Type>& other_vector) const
{       
   const unsigned this_size = this->size();

   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned other_size = other_vector.size();

   if(other_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n"
             << "Vector<Type> operator + (const Vector<Type>) const.\n"
             << "Size of vectors is " << this_size << " and " << other_size << " and they must be the same.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   Vector<Type> sum(this_size);
  
   for(unsigned i = 0; i < this_size; i++)
   {
      sum[i] = (*this)[i] + other_vector[i];
   }
   
   return(sum);
}


//Vector<Type> operator - (const Type&) const method 

/// Difference vector-scalar arithmetic operator.
/// @param scalar Scalar value to be subtracted to this vector.

inline Vector<Type> operator - (const Type& scalar) const
{       
   const unsigned this_size = this->size();

   Vector<Type> difference(this_size);

   for(unsigned i = 0; i < this_size; i++)
   {
      difference[i] = (*this)[i] - scalar;
   }
   
   return(difference);
}


// Vector<Type> operator - (const Vector<Type>&) const method

/// Difference vector-vector arithmetic operator.
/// @param other_vector vector to be subtracted to this vector.

inline Vector<Type> operator - (const Vector<Type>& other_vector) const
{
   const unsigned this_size = this->size();
       
   // Control sentence (if debug)      
       
   #ifndef NDEBUG 

   const unsigned other_size = other_vector.size();

   if(other_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "Vector<Type> operator - (const Vector<Type>&) const.\n"
             << "Size of vectors is " << this_size << " and " << other_size << " and they must be the same.\n";

	  throw std::logic_error(buffer.str());
   }
      
   #endif

   Vector<Type> difference(this_size);
  
   for(unsigned i = 0; i < this_size; i++)
   {
      difference[i] = (*this)[i] - other_vector[i];
   }
   
   return(difference);
}


// Vector<Type> operator * (const Type&) const method 

/// Product vector*scalar arithmetic operator.
/// @param scalar Scalar value to be multiplied to this vector.

inline Vector<Type> operator * (const Type& scalar) const
{       
   const unsigned this_size = this->size();

   Vector<Type> product(this_size);

   for(unsigned i = 0; i < this_size; i++)
   {
      product[i] = (*this)[i]*scalar;
   }
   
   return(product);
}


// Type operator * (const Vector<Type>&) const method

/// Element by element product vector*vector arithmetic operator.
/// @param other_vector vector to be multiplied to this vector.

inline Vector<Type> operator * (const Vector<Type>& other_vector) const
{  
   const unsigned this_size = this->size();
  
   // Control sentence (if debug)      
       
   #ifndef NDEBUG 

   const unsigned other_size = other_vector.size();

   if(other_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "Vector<Type> operator * (const Vector<Type>&) const.\n"
             << "Size of other vector (" << other_size << ") must be equal to size of this vector (" << this_size << ").\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   Vector<Type> product(this_size);
  
   for(unsigned i = 0; i < this_size; i++)
   {
      product[i] = (*this)[i]*other_vector[i];
   }
   
   return(product);
}


// Matrix<Type> operator * (const Matrix<Type>&) const method

/// Element by row product vector*matrix arithmetic operator.
/// @param matrix matrix to be multiplied to this vector.

inline Matrix<Type> operator * (const Matrix<Type>& matrix) const
{       
   const unsigned rows_number = matrix.get_rows_number();
   const unsigned columns_number = matrix.get_columns_number();

   // Control sentence (if debug)      
       
   #ifndef NDEBUG 

   const unsigned this_size = this->size();

   if(rows_number != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "Vector<Type> operator * (const Matrix<Type>&) const.\n"
             << "Number of matrix rows (" << rows_number << ") must be equal to vector size (" << this_size << ").\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   Matrix<Type> product(rows_number, columns_number);
  
   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
	  {
         product[i][j] = (*this)[i]*matrix[i][j];
	  }
   }
   
   return(product);
}


// Vector<Type> dot(const Matrix<Type>&) const method

/// Returns the dot product of this vector with a matrix.
/// The number of rows of the matrix must be equal to the size of the vector.
/// @param matrix matrix to be multiplied to this vector.

Vector<Type> dot(const Matrix<Type>& matrix) const
{
   const unsigned rows_number = matrix.get_rows_number();

   // Control sentence (if debug)      

   #ifndef NDEBUG 

   const unsigned this_size = this->size();

   if(rows_number != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "Vector<Type> dot(const Matrix<Type>&) const method.\n"
             << "Matrix number of rows must be equal to vector size.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   const unsigned columns_number = matrix.get_columns_number();

   Vector<Type> product(columns_number);
  
   for(unsigned j = 0; j < columns_number; j++)
   {     
      product[j] = 0;      

      for(unsigned i = 0; i < rows_number; i++)
      {
         product[j] += (*this)[i]*matrix[i][j];
      }
   }
    
   return(product);
}


// Vector<Type> dot(const Vector<Type>&) const method

/// Dot product vector*vector arithmetic operator.
/// @param other_vector vector to be multiplied to this vector.

Type dot(const Vector<Type>& other_vector) const
{
   const unsigned this_size = this->size();
            
   // Control sentence (if debug)      

   #ifndef NDEBUG 

   const unsigned other_size = other_vector.size();

   if(other_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "Type dot(const Vector<Type>&) const method.\n"
             << "Both vector sizes must be the same.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   Type dot_product = 0;
  
   for(unsigned i = 0; i < this_size; i++)
   {
      dot_product += (*this)[i]*other_vector[i];
   }
   
   return(dot_product);
}


// Matrix<Type> direct(const Vector<Type>&) const method

/// Outer product vector*vector arithmetic operator.
/// @param other_vector vector to be multiplied to this vector.

Matrix<Type> direct(const Vector<Type>& other_vector) const
{  
   const unsigned this_size = this->size();
          
   // Control sentence (if debug)      

   #ifndef NDEBUG 

   const unsigned other_size = other_vector.size();

   if(other_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "Matrix<Type> direct(const Vector<Type>&) const method.\n"
             << "Both vector sizes must be the same.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif
 
   Matrix<Type> direct(this_size, this_size);

   // Upper diagonal

   for(unsigned i = 0; i < this_size; i++)
   {
      for(unsigned j = 0; j < this_size; j++)
      {
         direct[i][j] = (*this)[i]*other_vector[j];
      }           
   }

   return(direct);
}


//Vector<Type> operator / (const Type&) const method 

/// Cocient vector/scalar arithmetic operator.
/// @param scalar Scalar value to be divided to this vector.

Vector<Type> operator / (const Type& scalar) const
{  
   const unsigned this_size = this->size();
   
   Vector<Type> cocient(this_size);

   for(unsigned i = 0; i < this_size; i++)
   {
      cocient[i] = (*this)[i]/scalar;
   }
   
   return(cocient);
}


// Vector<Type> operator / (const Vector<Type>&) const method

/// Cocient vector/vector arithmetic operator.
/// @param other_vector vector to be divided to this vector.

Vector<Type> operator / (const Vector<Type>& other_vector) const
{  
   const unsigned this_size = this->size();
     
   // Control sentence (if debug)            

   #ifndef NDEBUG 

   const unsigned other_size = other_vector.size();

   if(other_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "Vector<Type> operator / (const Vector<Type>&) const.\n"
             << "Both vector sizes must be the same.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   Vector<Type> cocient(this_size);
  
   for(unsigned i = 0; i < this_size; i++)
   {
      cocient[i] = (*this)[i]/other_vector[i];
   }
   
   return(cocient);
}


// void operator += (const Type&)

/// Scalar sum and assignment operator.
/// @param value Scalar value to be added to this vector.

void operator += (const Type& value)
{         
   const unsigned this_size = this->size();

   for(unsigned i = 0; i < this_size; i++)
   {
      (*this)[i] += value;
   }
}


// void operator += (const Vector<Type>&)

/// Vector sum and assignment operator.
/// @param other_vector Vector to be added to this vector.

void operator += (const Vector<Type>& other_vector)
{
   const unsigned this_size = this->size();
      
   // Control sentence (if debug)            

   #ifndef NDEBUG 

   const unsigned other_size = other_vector.size();

   if(other_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "void operator += (const Vector<Type>&).\n"
             << "Both vector sizes must be the same.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif
  
   for(unsigned i = 0; i < this_size; i++)
   {
      (*this)[i] += other_vector[i];
   }
}


// void operator -= (const Type&)

/// Scalar rest and assignment operator.
/// @param value Scalar value to be subtracted to this vector.

void operator -= (const Type& value)
{         
   const unsigned this_size = this->size();

   for(unsigned i = 0; i < this_size; i++)
   {
      (*this)[i] -= value;
   }
}


// void operator -= (const Vector<Type>&)

/// Vector rest and assignment operator.
/// @param other_vector Vector to be subtracted to this vector.

void operator -= (const Vector<Type>& other_vector)
{       
   const unsigned this_size = this->size();

   // Control sentence (if debug)            

   #ifndef NDEBUG 

   const unsigned other_size = other_vector.size();

   if(other_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "void operator -= (const Vector<Type>&).\n"
             << "Both vector sizes must be the same.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif
  
   for(unsigned i = 0; i < this_size; i++)
   {
      (*this)[i] -= other_vector[i];
   }
}


// void operator *= (const Type&) 

/// Scalar product and assignment operator.
/// @param value Scalar value to be multiplied to this vector.

void operator *= (const Type& value)
{  
   const unsigned this_size = this->size();
       
   for(unsigned i = 0; i < this_size; i++)
   {
      (*this)[i] *= value;
   }
}


// void operator *= (const Vector<Type>&)

/// Vector product and assignment operator.
/// @param other_vector Vector to be multiplied to this vector.

void operator *= (const Vector<Type>& other_vector)
{       
   const unsigned this_size = this->size();

   // Control sentence (if debug)            

   #ifndef NDEBUG 

   const unsigned other_size = other_vector.size();

   if(other_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "void operator *= (const Vector<Type>&).\n"
             << "Both vector sizes must be the same.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif
  
   for(unsigned i = 0; i < this_size; i++)
   {
      (*this)[i] *= other_vector[i];
   }
}


// void operator /= (const Type&)

/// Scalar division and assignment operator.
/// @param value Scalar value to be divided to this vector.

void operator /= (const Type& value)
{         
   const unsigned this_size = this->size();

   for(unsigned i = 0; i < this_size; i++)
   {
      (*this)[i] /= value;
   }
}


// void operator /= (const Vector<Type>&)

/// Vector division and assignment operator.
/// @param other_vector Vector to be divided to this vector.

void operator /= (const Vector<Type>& other_vector)
{       
   const unsigned this_size = this->size();

   // Control sentence (if debug)            

   #ifndef NDEBUG 

   const unsigned other_size = other_vector.size();

   if(other_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "void operator /= (const Vector<Type>&).\n"
             << "Both vector sizes must be the same.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif
  
   for(unsigned i = 0; i < this_size; i++)
   {
      (*this)[i] /= other_vector[i];
   }
}


// void scale_minimum_maximum(const Type&, const Type&) method

/// Normalizes the elements of this vector using the minimum and maximum method.
/// @param minimum Minimum value for the scaling.
/// @param maximum Maximum value for the scaling.

void scale_minimum_maximum(const Type& minimum, const Type& maximum)
{
    if(maximum - minimum < 1.0e-99)
    {
        return;
    }

    const unsigned this_size = this->size();

    for(unsigned i = 0; i < this_size; i++)
    {
        (*this)[i] = 2.0*((*this)[i]-minimum)/(maximum-minimum)-1.0;
    }
}


// void scale_minimum_maximum(const Statistics<Type>&) method

/// Normalizes the elements of this vector using the minimum and maximum method.
/// @param statistics Statistics structure, which contains the minimum and maximum values for the scaling.

void scale_minimum_maximum(const Statistics<Type>& statistics)
{
    scale_minimum_maximum(statistics.minimum, statistics.maximum);
}


// Statistics<Type> scale_minimum_maximum(void) method

/// Normalizes the elements of the vector with the minimum and maximum method.
/// The minimum and maximum values used are those calculated from the vector.
/// It also returns the statistics from the vector.

Statistics<Type> scale_minimum_maximum(void)
{
    const Statistics<Type> statistics = calculate_statistics();

    scale_minimum_maximum(statistics);

    return(statistics);
}


// void scale_mean_standard_deviation(const Type&, const Type&) method

/// Normalizes the elements of this vector using the mean and standard deviation method.
/// @param mean Mean value for the scaling.
/// @param standard_deviation Standard deviation value for the scaling.

void scale_mean_standard_deviation(const Type& mean, const Type& standard_deviation)
{
    if(standard_deviation < 1.0e-99)
    {
        return;
    }

    const unsigned this_size = this->size();

    for(unsigned i = 0; i < this_size; i++)
    {
        (*this)[i] = ((*this)[i]-mean)/standard_deviation;
    }
}


// void scale_mean_standard_deviation(const Statistics<Type>&) method

/// Normalizes the elements of this vector using the mean and standard deviation method.
/// @param statistics Statistics structure,
/// which contains the mean and standard deviation values for the scaling.

void scale_mean_standard_deviation(const Statistics<Type>& statistics)
{
    scale_mean_standard_deviation(statistics.mean, statistics.standard_deviation);
}


// Statistics<Type> scale_mean_standard_deviation(void) method

/// Normalizes the elements of the vector with the mean and standard deviation method.
/// The values used are those calculated from the vector.
/// It also returns the statistics from the vector.

Statistics<Type> scale_mean_standard_deviation(void)
{
    const Statistics<Type> statistics = calculate_statistics();

    scale_mean_standard_deviation(statistics);

    return(statistics);
}


// void scale_minimum_maximum(const Vector<Type>&, const Vector<Type>&) method

/// Scales the vectir elements with given minimum and maximum values.
/// It updates the data in the vector.
/// The size of the minimum and maximum vectors must be equal to the size of the vector.
/// @param minimum Minimum values.
/// @param maximum Maximum values.

void scale_minimum_maximum(const Vector<Type>& minimum, const Vector<Type>& maximum)
{
   const unsigned this_size = this->size();

   #ifndef NDEBUG

   const unsigned minimum_size = minimum.size();

   if(minimum_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector template."
             << "void scale_minimum_maximum(const Vector<Type>&, const Vector<Type>&) method.\n"
             << "Size of minimum vector must be equal to size.\n";

      throw std::logic_error(buffer.str());
   }

   const unsigned maximum_size = maximum.size();

   if(maximum_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector template."
             << "void scale_minimum_maximum(const Vector<Type>&, const Vector<Type>&) method.\n"
             << "Size of maximum vector must be equal to size.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   // Rescale data

   for(unsigned i = 0; i < this_size; i++)
   {
      if(maximum[i] - minimum[i] < 1e-99)
      {
         std::cout << "OpenNN Warning: Vector class.\n"
                   << "void scale_minimum_maximum(const Vector<Type>&, const Vector<Type>&) method.\n"
                   << "Minimum and maximum values of variable " << i << " are equal.\n"
                   << "Those elements won't be scaled.\n";

           // Do nothing
      }
      else
      {
         (*this)[i] = 2.0*((*this)[i] - minimum[i])/(maximum[i]-minimum[i])-1.0;
      }
   }
}


// void scale_mean_standard_deviation(const Vector<Type>&, const Vector<Type>&) method

/// Scales the vector elements with given mean and standard deviation values.
/// It updates the data in the vector.
/// The size of the mean and standard deviation vectors must be equal to the size of the vector. 
/// @param mean Mean values.
/// @param standard_deviation Standard deviation values.

void scale_mean_standard_deviation(const Vector<Type>& mean, const Vector<Type>& standard_deviation)
{
   const unsigned this_size = this->size();

   #ifndef NDEBUG 

   const unsigned mean_size = mean.size();

   if(mean_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector template." 
             << "void scale_mean_standard_deviation(const Vector<Type>&, const Vector<Type>&) method.\n" 
             << "Size of mean vector must be equal to size.\n";

	  throw std::logic_error(buffer.str());
   }

   const unsigned standard_deviation_size = standard_deviation.size();

   if(standard_deviation_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector template." 
             << "void scale_mean_standard_deviation(const Vector<Type>&, const Vector<Type>&) method.\n" 
             << "Size of standard deviation vector must be equal to size.\n";

	  throw std::logic_error(buffer.str());
   }   

   #endif

   // Rescale data

   for(unsigned i = 0; i < this_size; i++)
   {
      if(standard_deviation[i] < 1e-99)
      {
         std::cout << "OpenNN Warning: Vector class.\n"
                   << "void scale_mean_standard_deviation(const Vector<Type>&, const Vector<Type>&) method.\n"
                   << "Standard deviation of variable " << i << " is zero.\n"
                   << "Those elements won't be scaled.\n";

         // Do nothing
      }
      else
      {
         (*this)[i] = ((*this)[i] - mean[i])/standard_deviation[i];
      }
   }
}


// Vector<Type> calculate_scaled_minimum_maximum(const Vector<Type>&, const Vector<Type>&) const method

/// Returns a vector with the scaled elements of this vector acording to the minimum and maximum method.
/// The size of the minimum and maximum vectors must be equal to the size of the vector. 
/// @param minimum Minimum values.
/// @param maximum Maximum values.

Vector<Type> calculate_scaled_minimum_maximum(const Vector<Type>& minimum, const Vector<Type>& maximum) const
{
   const unsigned this_size = this->size();

   #ifndef NDEBUG 

   const unsigned minimum_size = minimum.size();

   if(minimum_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector template." 
             << "Vector<Type> calculate_scaled_minimum_maximum(const Vector<Type>&, const Vector<Type>&) const method.\n" 
             << "Size of minimum vector must be equal to size.\n";

	  throw std::logic_error(buffer.str());
   }

   const unsigned maximum_size = maximum.size();

   if(maximum_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector template." 
             << "Vector<Type> calculate_scaled_minimum_maximum(const Vector<Type>&, const Vector<Type>&) const method.\n" 
             << "Size of maximum vector must be equal to size.\n";

	  throw std::logic_error(buffer.str());
   }   

   #endif

   Vector<Type> scaled_minimum_maximum(this_size);

   // Rescale data

   for(unsigned i = 0; i < this_size; i++)
   {
      if(maximum[i] - minimum[i] < 1e-99)
      {
         std::cout << "OpenNN Warning: Vector class.\n"
                   << "Vector<Type> calculate_scaled_minimum_maximum(const Vector<Type>&, const Vector<Type>&) const method.\n"
                   << "Minimum and maximum values of variable " << i << " are equal.\n"
                   << "Those elements won't be scaled.\n";

		 scaled_minimum_maximum[i] = (*this)[i];
      }
      else
      {
         scaled_minimum_maximum[i] = 2.0*((*this)[i] - minimum[i])/(maximum[i]-minimum[i])-1.0;
      }
   }

   return(scaled_minimum_maximum);
}


// Vector<Type> calculate_scaled_mean_standard_deviation(const Vector<Type>&, const Vector<Type>&) const method

/// Returns a vector with the scaled elements of this vector acording to the mean and standard deviation method.
/// The size of the mean and standard deviation vectors must be equal to the size of the vector. 
/// @param mean Mean values.
/// @param standard_deviation Standard deviation values.

Vector<Type> calculate_scaled_mean_standard_deviation(const Vector<Type>& mean, const Vector<Type>& standard_deviation) const
{
   const unsigned this_size = this->size();

   #ifndef NDEBUG 

   std::ostringstream buffer;

   const unsigned mean_size = mean.size();

   if(mean_size != this_size)
   {
      buffer << "OpenNN Exception: Vector template." 
             << "Vector<Type> calculate_scaled_mean_standard_deviation(const Vector<Type>&, const Vector<Type>&) const method.\n" 
             << "Size of mean vector must be equal to size.\n";

	  throw std::logic_error(buffer.str());
   }

   const unsigned standard_deviation_size = standard_deviation.size();

   if(standard_deviation_size != this_size)
   {
      buffer << "OpenNN Exception: Vector template.\n"
             << "Vector<Type> calculate_scaled_mean_standard_deviation(const Vector<Type>&, const Vector<Type>&) const method.\n" 
             << "Size of standard deviation vector must be equal to size.\n";

	  throw std::logic_error(buffer.str());
   }   

   #endif

   Vector<Type> scaled_mean_standard_deviation(this_size);

   for(unsigned i = 0; i < this_size; i++)
   {
      if(standard_deviation[i] < 1e-99)
      {
         std::cout << "OpenNN Warning: Vector template.\n"
                   << "Vector<Type> calculate_scaled_mean_standard_deviation(const Vector<Type>&, const Vector<Type>&) const method.\n" 
                   << "Standard deviation of variable " << i << " is zero.\n"
                   << "Those elements won't be scaled.\n";

         scaled_mean_standard_deviation = (*this)[i];
      }
      else
      {
         scaled_mean_standard_deviation[i] = (*this)[i]*standard_deviation[i] + mean[i];
      }
   }

   return(scaled_mean_standard_deviation);
}


// Vector<Type> calculate_unscaled_minimum_maximum(const Vector<Type>&, const Vector<Type>&) const method

/// Returns a vector with the unscaled elements of this vector acording to the minimum and maximum method.
/// The size of the minimum and maximum vectors must be equal to the size of the vector. 
/// @param minimum Minimum values.
/// @param maximum Maximum values.

Vector<Type> calculate_unscaled_minimum_maximum(const Vector<Type>& minimum, const Vector<Type>& maximum) const 
{
   const unsigned this_size = this->size();

   #ifndef NDEBUG 

   const unsigned minimum_size = minimum.size();

   if(minimum_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector template." 
             << "Vector<Type> calculate_unscaled_minimum_maximum(const Vector<Type>&, const Vector<Type>&) const method.\n" 
             << "Size of minimum vector must be equal to size.\n";

	  throw std::logic_error(buffer.str());
   }

   const unsigned maximum_size = maximum.size();

   if(maximum_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector template." 
             << "Vector<Type> calculate_unscaled_minimum_maximum(const Vector<Type>&, const Vector<Type>&) const method.\n" 
             << "Size of maximum vector must be equal to size.\n";

	  throw std::logic_error(buffer.str());
   }   

   #endif

   Vector<Type> unscaled_minimum_maximum(this_size);

   for(unsigned i = 0; i < this_size; i++)
   {
      if(maximum[i] - minimum[i] < 1e-99)
      {
         std::cout << "OpenNN Warning: Vector template.\n"
                   << "Vector<Type> calculate_unscaled_minimum_maximum(const Vector<Type>&, const Vector<Type>&) const method.\n" 
                   << "Minimum and maximum values of variable " << i << " are equal.\n"
                   << "Those elements won't be unscaled.\n";

         unscaled_minimum_maximum[i] = (*this)[i];
	  }
      else
      {
         unscaled_minimum_maximum[i] = 0.5*((*this)[i] + 1.0)*(maximum[i]-minimum[i]) + minimum[i]; 
      }
   }

   return(unscaled_minimum_maximum);
}


// Vector<Type> calculate_unscaled_mean_standard_deviation(const Vector<Type>&, const Vector<Type>&) const method

/// Returns a vector with the unscaled elements of this vector acording to the mean and standard deviation method.
/// The size of the mean and standard deviation vectors must be equal to the size of the vector. 
/// @param mean Mean values.
/// @param standard_deviation Standard deviation values.

Vector<Type> calculate_unscaled_mean_standard_deviation(const Vector<Type>& mean, const Vector<Type>& standard_deviation) const
{
   const unsigned this_size = this->size();

   #ifndef NDEBUG 

   const unsigned mean_size = mean.size();

   if(mean_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector template." 
             << "Vector<Type> calculate_unscaled_mean_standard_deviation(const Vector<Type>&, const Vector<Type>&) const method.\n" 
             << "Size of mean vector must be equal to size.\n";

	  throw std::logic_error(buffer.str());
   }

   const unsigned standard_deviation_size = standard_deviation.size();

   if(standard_deviation_size != this_size)
   {
      std::ostringstream buffer;

	  buffer << "OpenNN Exception: Vector template.\n"
             << "Vector<Type> calculate_unscaled_mean_standard_deviation(const Vector<Type>&, const Vector<Type>&) const method.\n" 
             << "Size of standard deviation vector must be equal to size.\n";

      throw std::logic_error(buffer.str());
   }   

   #endif

   Vector<Type> unscaled_mean_standard_deviation(this_size);

   for(unsigned i = 0; i < this_size; i++)
   {
      if(standard_deviation[i] < 1e-99)
      {
         std::cout << "OpenNN Warning: Vector template.\n"
                   << "Vector<Type> calculate_unscaled_mean_standard_deviation(const Vector<Type>&, const Vector<Type>&) const method.\n" 
                   << "Standard deviation of variable " << i << " is zero.\n"
                   << "Those elements won't be scaled.\n";

         unscaled_mean_standard_deviation[i] = (*this)[i];
      }
      else
      {
         unscaled_mean_standard_deviation[i] = (*this)[i]*standard_deviation[i] + mean[i];
      }
   }

   return(unscaled_mean_standard_deviation);
}




// void unscale_minimum_maximum(const Vector<Type>&, const Vector<Type>&) method

/// Unscales the vector elements with given minimum and maximum values.
/// It updates the vector elements.
/// The size of the minimum and maximum vectors must be equal to the size of the vector. 
/// @param minimum Minimum values.
/// @param maximum Maximum deviation values.

void unscale_minimum_maximum(const Vector<Type>& minimum, const Vector<Type>& maximum)
{
   const unsigned this_size = this->size();

   #ifndef NDEBUG 

   const unsigned minimum_size = minimum.size();

   if(minimum_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector template." 
             << "void unscale_minimum_maximum(const Vector<Type>&, const Vector<Type>&) method.\n" 
             << "Size of minimum vector must be equal to size.\n";

      throw std::logic_error(buffer.str());
   }

   const unsigned maximum_size = maximum.size();

   if(maximum_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector template." 
             << "void unscale_minimum_maximum(const Vector<Type>&, const Vector<Type>&) method.\n" 
             << "Size of maximum vector must be equal to size.\n";

      throw std::logic_error(buffer.str());
   }   

   #endif

   for(unsigned i = 0; i < this_size; i++)
   {
      if(maximum[i] - minimum[i] < 1e-99)
      {
         std::cout << "OpenNN Warning: Vector template.\n"
                   << "void unscale_minimum_maximum(const Vector<Type>&, const Vector<Type>&) method.\n" 
                   << "Minimum and maximum values of variable " << i << " are equal.\n"
                   << "Those elements won't be unscaled.\n";

         // Do nothing
      }
      else
      {
         (*this)[i] = 0.5*((*this)[i] + 1.0)*(maximum[i]-minimum[i]) + minimum[i]; 
      }
   }
}


// void unscale_mean_standard_deviation(const Vector<Type>&, const Vector<Type>&) method

/// Unscales the vector elements with given mean and standard deviation values.
/// It updates the vector elements.
/// The size of the mean and standard deviation vectors must be equal to the size of the vector. 
/// @param mean Mean values.
/// @param standard_deviation Standard deviation values.

void unscale_mean_standard_deviation(const Vector<Type>& mean, const Vector<Type>& standard_deviation)
{
   const unsigned this_size = this->size();

   #ifndef NDEBUG 

   const unsigned mean_size = mean.size();

   if(mean_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector template." 
             << "void unscale_mean_standard_deviation(const Vector<Type>&, const Vector<Type>&) method.\n" 
             << "Size of mean vector must be equal to size.\n";

      throw std::logic_error(buffer.str());
   }

   const unsigned standard_deviation_size = standard_deviation.size();

   if(standard_deviation_size != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector template.\n"
             << "void unscale_mean_standard_deviation(const Vector<Type>&, const Vector<Type>&) method.\n" 
             << "Size of standard deviation vector must be equal to size.\n";

      throw std::logic_error(buffer.str());
   }   

   #endif

   for(unsigned i = 0; i < this_size; i++)
   {
      if(standard_deviation[i] < 1e-99)
      {
         std::cout << "OpenNN Warning: Vector template.\n"
                   << "void unscale_mean_standard_deviation(const Vector<Type>&, const Vector<Type>&) method.\n" 
                   << "Standard deviation of variable " << i << " is zero.\n"
                   << "Those elements won't be scaled.\n";

         // Do nothing
      }
      else
      {
         (*this)[i] = (*this)[i]*standard_deviation[i] + mean[i];
      }
   }
}


// Matrix<Type> arrange_diagonal_matrix(void) const method

/// Returns a squared matrix in which the entries outside the main diagonal are all zero.
/// The elements in the diagonal are the elements in this vector. 

Matrix<Type> arrange_diagonal_matrix(void) const
{
   const unsigned this_size = this->size();

   Matrix<Type> matrix(this_size, this_size, 0.0);

   for(unsigned i = 0; i < this_size; i++)
   {
      matrix[i][i] = (*this)[i];
   }

   return(matrix);
}


// Vector<Type> arrange_subvector(const Vector<unsigned>&) const

/// Returns another vector whose elements are given by some elements of this vector.
/// @param indices Indices of this vector whose elements are required.

Vector<Type> arrange_subvector(const Vector<unsigned>& indices) const
{
    const unsigned new_size = indices.size();

   // Control sentence (if debug)

   #ifndef NDEBUG

   const unsigned this_size = this->size();

   for(unsigned i = 0; i < new_size; i++)
   {
       if(indices[i] > this_size)
       {
          std::ostringstream buffer;

          buffer << "OpenNN Exception: Vector Template.\n"
                 << "Vector<Type> arrange_subvector(const Vector<Type>&) const method.\n"
                 << "Index is equal or greater than this size.\n";

          throw std::logic_error(buffer.str());
       }
   }

   #endif

   Vector<Type> subvector(new_size);

   for(unsigned i = 0; i < new_size; i++)
   {
       subvector[i] = (*this)[indices[i]];
   }

   return(subvector);
}


// void load(const std::string&) method

/// Loads the members of a vector from an data file.
/// Please be careful with the file format, which is specified in the OpenNN manual.
/// @param file_name Name of vector file.

void load(const std::string& file_name)
{
   std::ifstream file(file_name.c_str());

   std::stringstream buffer;

   std::string line;

   while(file.good())
   {
      getline(file, line);

      buffer << line;
   }
     
   std::istream_iterator<std::string> it(buffer); 
   std::istream_iterator<std::string> end; 

   const std::vector<std::string> results(it, end); 

   const unsigned new_size = results.size();

   this->resize(new_size);

   file.clear();
   file.seekg(0, std::ios::beg); 

   // Read data

   for(unsigned i = 0; i < new_size; i++)
   {
      file >> (*this)[i];
   }

   file.close();
}


// void save(const std::string&) const method

/// Saves to a data file the elements of the vector.
/// The file format is as follows:
/// element_0 element_1 ... element_N-1
/// @param file_name Name of vector data file.

void save(const std::string& file_name) const
{
   std::ofstream file(file_name.c_str());

   if(!file.is_open())
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector template.\n"
             << "void save(const std::string&) const method.\n"
             << "Cannot open vector data file.\n";

      throw std::logic_error(buffer.str());
   }

   // Write file

   const unsigned this_size = this->size();

   if(this_size > 0)
   {
      file << (*this)[0];

      const char space = ' ';

      for(unsigned  i = 1; i < this_size; i++)
      {
         file << space << (*this)[i];
      }

      file << std::endl;
   }

   // Close file

   file.close();
}


// void tuck_in(const unsigned&, const Vector<Type>&) const method

/// Insert another vector starting from a given position.
/// @param position Insertion position.
/// @param other_vector Vector to be inserted.

void tuck_in(const unsigned& position, const Vector<Type>& other_vector)
{
   const unsigned other_size = other_vector.size();

   // Control sentence (if debug)            

   #ifndef NDEBUG 

   const unsigned this_size = this->size();

   if(position + other_size > this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "void tuck_in(const unsigned&, const Vector<Type>&) const method.\n"
             << "Cannot tuck in vector.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   for(unsigned i = 0; i < other_size; i++)
   {
      (*this)[position + i] = other_vector[i];
   }
}


// Vector<Type> take_out(const unsigned&, const unsigned&) method

/// Extract a vector of a given size from a given position
/// @param position Extraction position.
/// @param other_size Size of vector to be extracted.

Vector<Type> take_out(const unsigned& position, const unsigned& other_size) const
{
   // Control sentence (if debug)            

   #ifndef NDEBUG 

   const unsigned this_size = this->size();

   if(position + other_size > this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "Vector<Type> take_out(const unsigned&, const unsigned&) method.\n"
             << "Cannot take out vector.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   Vector<Type> other_vector(other_size);

   for(unsigned i = 0; i < other_size; i++)
   {
      other_vector[i] = (*this)[position + i];
   }

   return(other_vector);
}


// Vector<Type> remove_element(const unsigned) const

/// Returns a new vector which is a copy of this vector but with a given element removed.
/// Therefore, the size of the new vector is the size of this vector minus one.
/// @param index Index of element to be removed.

Vector<Type> remove_element(const unsigned& index) const
{
    const unsigned this_size = this->size();

    // Control sentence (if debug)

    #ifndef NDEBUG

    if(index >= this_size)
    {
       std::ostringstream buffer;

       buffer << "OpenNN Exception: Vector Template.\n"
              << "Vector<Type> remove_element(const unsigned&) const method.\n"
              << "Index is equal or greater than vector size.\n";

       throw std::logic_error(buffer.str());
    }

    #endif

    Vector<Type> other_vector(this_size-1);

    for(unsigned i = 0; i < this_size; i++)
    {
        if(i < index)
        {
            other_vector[i] = (*this)[i];
        }
        else if(i > index)
        {
            other_vector[i-1] = (*this)[i];
        }
    }

    return(other_vector);
}


// Vector<Type> remove_value(const Type&) const

/// Construct a copy of this vector but without a certain value. 
/// Note that the new vector might have a different size than this vector. 
/// @param value Value of elements to be removed. 

Vector<Type> remove_value(const Type& value) const
{
   const unsigned this_size = this->size();

    unsigned value_count = 0;

	for(unsigned i = 0; i < this_size; i++)
	{
	   if((*this)[i] == value)
	   {
          value_count++;
	   }
	}

    if(value_count == 0)
	{
	   return(*this);
	}
	else
	{
       const unsigned other_size = this_size - value_count;

	   Vector<Type> other_vector(other_size);
	
	   unsigned other_index = 0;

   	   for(unsigned i = 0; i < this_size; i++)
	   {
	      if((*this)[i] != value)
	      {
	         other_vector[other_index] = (*this)[i];

			 other_index++;
	      }
	   }	   

       return(other_vector);
	}
}


// Vector<Type> assemble(const Vector<Type>&) const method

/// Assemble two vectors.
/// @param other_vector Vector to be get_assemblyd to this vector. 

Vector<Type> assemble(const Vector<Type>& other_vector) const
{
   const unsigned this_size = this->size();
   const unsigned other_size = other_vector.size();

   if(this_size == 0 && other_size == 0)
   {
      Vector<Type> assembly;

      return(assembly);
   }
   else if(this_size == 0)
   {
      return(other_vector);
   }
   else if(other_size == 0)
   {
      return(*this);
   }
   else
   {
      Vector<Type> assembly(this_size + other_size);

      for(unsigned i = 0; i < this_size; i++)
      {
         assembly[i] = (*this)[i];
      }

      for(unsigned i = 0; i < other_size; i++)
      {
         assembly[this_size+i] = other_vector[i];
      } 
   
      return(assembly);
   }
}


// std::vector<Type> to_std_vector(void) const method

/// Returns a std vector with the size and elements of this OpenNN vector.

std::vector<Type> to_std_vector(void) const
{
   const unsigned this_size = this->size();

   std::vector<Type> std_vector(this_size);

   for(unsigned i = 0; i < this_size; i++)
   {
      std_vector[i] = (*this)[i];
   }


   return(std_vector);
}


// void parse(const std::string&) method

/// This method takes a string representation of a vector and sets this vector to have size equal to the number of words and values equal to that words.
/// @param str String to be parsed. 

void parse(const std::string& str)
{
   if(str.empty())
   {
       set();
   }
   else
   {
      std::istringstream buffer(str); 
        
      std::istream_iterator<std::string> first(buffer); 
      std::istream_iterator<std::string> last; 

      Vector<std::string> str_vector(first, last); 

      const unsigned new_size = str_vector.size();

      if(new_size > 0)
      {
         this->resize(new_size);

         buffer.clear();
         buffer.seekg(0, std::ios::beg); 

         for(unsigned i = 0; i < new_size; i++)
         {
            buffer >> (*this)[i];
         }
      }
   }
}


// std::string to_string(const std::string&)

/// Returns a string representation of this vector.

std::string to_string(const std::string& separator = " ") const
{
   std::ostringstream buffer;

   const unsigned this_size = this->size();

   if(this_size > 0)
   {
      buffer << (*this)[0];

      for(unsigned  i = 1; i < this_size; i++)
      {
         buffer << separator << (*this)[i];
      }
   }

   return(buffer.str());
}


// std::string to_text()

/// Returns a string representation of this vector which can be inserted in a text.

std::string to_text() const
{
   std::ostringstream buffer;

   const unsigned this_size = this->size();

   if(this_size > 0)
   {
      buffer << (*this)[0];

      for(unsigned i = 1; i < this_size-1; i++)
      {
            buffer << ", " << (*this)[i];
      }

      if(this_size > 1)
      {
            buffer << " and " << (*this)[this_size-1];
      }
   }

   return(buffer.str());
}


// Vector<std::string> write_string_vector(const unsigned& precision) const

/// This method retuns a vector of strings with size equal to the size of this vector and elements equal to string representations of the elements of this vector. 

Vector<std::string> write_string_vector(const unsigned& precision = 3) const
{
   const unsigned this_size = this->size();

   Vector<std::string> string_vector(this_size);

   std::ostringstream buffer;

   for(unsigned i = 0; i < this_size; i++)
   {
      buffer.str("");
      buffer << std::setprecision(precision) << (*this)[i];
   
      string_vector[i] = buffer.str();
   }

   return(string_vector);
}


// Matrix<Type> to_matrix(const unsigned&, const unsigned&) method

/// Returns a matrix with given numbers of rows and columns and with the elements of this vector ordered by rows.
/// The number of rows multiplied by the number of columns must be equal to the size of this vector. 
/// @param rows_number Number of rows in the new matrix. 
/// @param columns_number Number of columns in the new matrix. 


Matrix<Type> to_matrix(const unsigned& rows_number, const unsigned& columns_number) const
{
   // Control sentence (if debug)            

   #ifndef NDEBUG 

   const unsigned this_size = this->size();

   if(rows_number*columns_number != this_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Vector Template.\n" 
             << "Matrix<Type> to_matrix(const unsigned&, const unsigned&) method.\n"
             << "The number of rows (" << rows_number << ") times the number of colums (" << columns_number  <<") must be equal to the size of the vector (" << this_size << ").\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   Matrix<Type> matrix(rows_number, columns_number);

   unsigned index = 0;

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         matrix[i][j] = (*this)[index];
         index++;
      }   
   }

   return(matrix);
}


private:

};


// Vector input operator

/// This method re-writes the inputs operator >> for the Vector template. 
/// @param is Input stream.
/// @param v Input vector.

template<typename Type>
std::istream& operator >> (std::istream& is, Vector<Type>& v)
{
   const unsigned size = v.size();
   
   for(unsigned i = 0; i < size; i++)
   {
      is >> v[i];
   }

   return(is);
}


// Vector output operator

/// This method re-writes the output operator << for the Vector template.
/// @param os Output stream.
/// @param v Output vector.

template<typename Type>
std::ostream& operator << (std::ostream& os, const Vector<Type>& v)
{
   const unsigned this_size = v.size();
 
   if(this_size > 0)
   {
      os << v[0];

      const char space = ' ';

      for(unsigned  i = 1; i < this_size; i++)
      {
         os << space << v[i];
      }
   }

   return(os);
}


// Vector of vectors output operator

/// This method re-writes the output operator << for vectors of vectors.
/// @param os Output stream.
/// @param v Output vector of vectors.

template<typename Type>
std::ostream& operator << (std::ostream& os, const Vector< Vector<Type> >& v)
{ 
   for(unsigned i = 0; i < v.size(); i++)
   {
      os << "subvector_" << i  << "\n"
         << v[i] << std::endl;
   }

   return(os);
}


// Vector of matrices output operator

/// This method re-writes the output operator << for vectors of matrices.
/// @param os Output stream.
/// @param v Output vector of matrices.

template<typename Type>
std::ostream& operator << (std::ostream& os, const Vector< Matrix<Type> >& v)
{  
   for(unsigned i = 0; i < v.size(); i++)
   {
      os << "submatrix_" << i  << "\n"
         << v[i];
   }

   return(os);
}


// double calculate_random_uniform(const double&, const double&) method

/// Returns a random number chosen from a uniform distribution.
/// @param minimum Minimum value.
/// @param maximum Maximum value.

inline double calculate_random_uniform(const double& minimum, const double& maximum)
{
   const double random = (double)rand()/(RAND_MAX+1.0);

   const double random_uniform = minimum + (maximum-minimum)*random;

   return(random_uniform);
}


// double calculate_random_normal(const double&, const double&) method

/// Returns a random number chosen from a normal distribution.
/// @param mean Mean value of normal distribution.
/// @param standard_deviation Standard deviation value of normal distribution.

inline double calculate_random_normal(const double& mean, const double& standard_deviation)
{
   const double pi = 4.0*atan(1.0);

   double random_uniform_1;

   do
   {
      random_uniform_1 = (double)rand()/(RAND_MAX+1.0);

   }while(random_uniform_1 == 0.0);

   const double random_uniform_2 = (double)rand()/(RAND_MAX+1.0);

   // Box-Muller transformation

   const double random_normal = mean + sqrt(-2.0*log(random_uniform_1))*sin(2.0*pi*random_uniform_2)*standard_deviation;

   return(random_normal);
}


/// This template defines the most important statistic results of a set, function, etc.
/// This includes the minimum, maximum, mean and standard deviation values.

template <class Type>
struct Statistics
{
    /// Default constructor.

    Statistics(void)
    {
        minimum = -1.0;
        maximum = 1.0;
        mean = 0.0;
        standard_deviation = 1.0;
    }

    /// Values constructor.

    Statistics(const Type& new_minimum, const Type& new_maximum, const Type& new_mean, const Type& new_standard_deviation)
    {
        minimum = new_minimum;
        maximum = new_maximum;
        mean = new_mean;
        standard_deviation = new_standard_deviation;
    }

    /// Destructor.

    virtual ~Statistics(void)
    {
    }

    /// Sets a new minimum value in the statistics structure.
    /// @param new_minimum Minimum value.

    void set_minimum(const double& new_minimum)
    {
        minimum = new_minimum;
    }

    /// Sets a new maximum value in the statistics structure.
    /// @param new_maximum Maximum value.

    void set_maximum(const double& new_maximum)
    {
        maximum = new_maximum;
    }

    /// Sets a new mean value in the statistics structure.
    /// @param new_mean Mean value.

    void set_mean(const double& new_mean)
    {
        mean = new_mean;
    }

    /// Sets a new standard deviation value in the statistics structure.
    /// @param new_standard_deviation Standard deviation value.

    void set_standard_deviation(const double& new_standard_deviation)
    {
        standard_deviation = new_standard_deviation;
    }

    /// Returns all the statistical parameters contained in a single vector.
    /// The size of that vector is four.
    /// The elements correspond to the minimum, maximum, mean and standard deviation values, respectively.

    Vector<Type> to_vector(void) const
    {
        Vector<Type> statistics_vector(4);
        statistics_vector[0] = minimum;
        statistics_vector[1] = maximum;
        statistics_vector[2] = mean;
        statistics_vector[3] = standard_deviation;

        return(statistics_vector);
    }

    /// Initializes the statistics structure with a random
    /// minimum (between -1 and 1), maximum (between 0 and 1),
    /// mean (between -1 and 1) and standard deviation (between 0 and 2).

    void initialize_random(void)
    {
        minimum = calculate_random_uniform(-1.0, 0.0);
        maximum = calculate_random_uniform(0.0, 1.0);
        mean = calculate_random_uniform(-1.0, 1.0);
        standard_deviation = calculate_random_uniform(0.0, 2.0);
    }

    /// Returns true if the minimum value is -1 and the maximum value is +1,
    /// and false otherwise.

    bool has_minimum_minus_one_maximum_one(void)
    {
        if(-1.000001 < minimum && minimum < -0.999999
        &&  0.999999 < maximum && maximum <  1.000001)
        {
            return(true);
        }
        else
        {
            return(false);
        }
    }

    /// Returns true if the mean value is 0 and the standard deviation value is 1,
    /// and false otherwise.

    bool has_mean_zero_standard_deviation_one(void)
    {               
        if(-0.000001 < mean && mean < 0.000001
        &&  0.999999 < standard_deviation && standard_deviation < 1.000001)
        {
            return(true);
        }
        else
        {
            return(false);
        }
    }

    /// Smallest value of a set, function, etc.

    Type minimum;

    /// Biggest value of a set, function, etc.

    Type maximum;

    /// Mean value of a set, function, etc.

    Type mean;

    /// Standard deviation value of a set, function, etc.

    Type standard_deviation;
};


template<typename Type>
std::ostream& operator << (std::ostream& os, const Statistics<Type>& statistics)
{
    os << "Statistics:\n"
       << "Minimum: " << statistics.minimum << "\n"
       << "Maximum: " << statistics.maximum << "\n"
       << "Mean: " << statistics.mean << "\n"
       << "Standard deviation: " << statistics.standard_deviation << std::endl;

   return(os);
}


///
/// This template contains the data needed to represent a histogram.
///

template <class Type>
struct Histogram
{
    /// Default constructor.

    Histogram(void)
    {
    }

    /// Destructor.

    virtual ~Histogram(void)
    {
    }

    /// Bins number constructor.
    /// @param bins_number Number of bins in the histogram.

    Histogram(const unsigned& bins_number)
    {
        centers.resize(bins_number);
        frequencies.resize(bins_number);
    }

    /// Values constructor.
    /// @param new_centers Center values for the bins.
    /// @param new_frequencies Number of variates in each bin.

    Histogram(const Vector<Type>& new_centers, const Vector<unsigned>& new_frequencies)
    {
        centers = new_centers;
        frequencies = new_frequencies;
    }

    /// Returns the number of bins in the histogram.

    unsigned get_bins_number(void) const
    {
        return(centers.size());
    }

    /// Returns the number of bins with zero variates.

    unsigned count_empty_bins(void) const
    {
        return(frequencies.count_occurrences(0));
    }


    /// Returns the number of variates in the less populated bin.

    unsigned calculate_minimum_frequency(void) const
    {
        return(frequencies.calculate_minimum());
    }


    /// Returns the number of variates in the most populated bin.

    unsigned calculate_maximum_frequency(void) const
    {
        return(frequencies.calculate_maximum());
    }

    /// Returns a vector with the centers of the less populated bins.

    Vector<Type> calculate_minimal_centers(void) const
    {
        const unsigned minimum_frequency = calculate_minimum_frequency();

        const Vector<unsigned> minimal_indices = frequencies.calculate_occurrence_indices(minimum_frequency);

        return(centers.arrange_subvector(minimal_indices));
    }

    /// Returns a vector with the centers of the most populated bins.

    Vector<Type> calculate_maximal_centers(void) const
    {
        const unsigned maximum_frequency = calculate_maximum_frequency();

        const Vector<unsigned> maximal_indices = frequencies.calculate_occurrence_indices(maximum_frequency);

        return(centers.arrange_subvector(maximal_indices));
    }

    /// Vector of center values for each bin.
    /// The size of this vector is the number of bins.

    Vector<Type> centers;

    /// Vector of variates in each bin.
    /// The size of this vector is the number of bins.

    Vector<unsigned> frequencies;
};


template<typename Type>
std::ostream& operator << (std::ostream& os, const Histogram<Type>& histogram)
{
    os << "Histogram:\n"
       << "Centers: " << histogram.centers << "\n"
       << "Frequencies: " << histogram.frequencies << std::endl;

   return(os);
}


///
/// This template defines the parameters of a linear regression analysis between two sets x-y.
///

template <class Type>
struct LinearRegressionParameters
{
    /// Y-intercept of the linear regression.

    double intercept;

    /// Slope of the linear regression.

    double slope;

    /// Correlation coefficient (R-value) of the linear regression.

    double correlation;
};


template<typename Type>
std::ostream& operator << (std::ostream& os, const LinearRegressionParameters<Type>& linear_regression_parameters)
{
    os << "Linear regression parameters:\n"
       << "Intercept: " << linear_regression_parameters.intercept << "\n"
       << "Slope: " << linear_regression_parameters.slope << "\n"
       << "Correlation: " << linear_regression_parameters.correlation << std::endl;

   return(os);
}


}// end namespace OpenNN

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

