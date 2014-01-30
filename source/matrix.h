/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   M A T R I X   C O N T A I N E R                                                                            */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __MATRIX_H__
#define __MATRIX_H__

// System includes

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

// OpenNN includes

#include "vector.h"

namespace OpenNN
{

/// This template class defines a matrix for general purpose use.
/// This matrix also implements some mathematical methods which can be useful. 

template <class Type>
class Matrix 
{

public:


// CONSTRUCTORS

/// Default constructor. It creates a matrix with zero rows and zero columns.

explicit Matrix(void) 
{
   rows_number = 0;
   columns_number = 0;
   data = NULL;
}


/// Constructor. It creates a matrix with n rows and m columns, containing n*m copies of the default value for Type.
/// @param new_rows_number Number of rows in matrix.
/// @param new_columns_number Number of columns in matrix.


explicit Matrix(const unsigned& new_rows_number, const unsigned& new_columns_number) 
{
   if(new_rows_number == 0 && new_columns_number == 0)
   {
      rows_number = 0;
      columns_number = 0;
      data = NULL;
   }
   else if(new_rows_number == 0)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "Constructor Matrix(const unsigned&, const unsigned&).\n"
             << "Number of rows must be greater than zero.\n";

      throw std::logic_error(buffer.str());
   }
   else if(new_columns_number == 0)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "Constructor Matrix(const unsigned&, const unsigned&).\n"
             << "Number of columns must be greater than zero.\n";

      throw std::logic_error(buffer.str());
   }
   else
   {
      rows_number = new_rows_number;
      columns_number = new_columns_number;

      data = new Type*[rows_number];
      data[0] = new Type[rows_number*columns_number];

      for(unsigned i = 1; i < rows_number; i++)
      {
         data[i] = data[i-1] + columns_number;
      }
   }
}


/// Constructor. It creates a matrix with n rows and m columns, containing n*m copies of the type value of Type. 
/// @param new_rows_number Number of rows in matrix.
/// @param new_columns_number Number of columns in matrix.
/// @param type Value of Type.

explicit Matrix(const unsigned& new_rows_number, const unsigned& new_columns_number, const Type& type) 
{
   if(new_rows_number == 0 && new_columns_number == 0)
   {
      rows_number = 0;
      columns_number = 0;
      data = NULL;
   }
   else if(new_rows_number == 0)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "Constructor Matrix(const unsigned&, const unsigned&, const Type&).\n"
             << "Number of rows must be greater than zero.\n";

      throw std::logic_error(buffer.str());
   }
   else if(new_columns_number == 0)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "Constructor Matrix(const unsigned&, const unsigned&, const Type&).\n"
             << "Number of columns must be greater than zero.\n";

      throw std::logic_error(buffer.str());
   }
   else
   {
      // Set sizes

      rows_number = new_rows_number;
      columns_number = new_columns_number;

      data = new Type*[new_rows_number];
      data[0] = new Type[rows_number*columns_number];

      for(unsigned i = 1; i < rows_number; i++)
      {
         data[i] = data[i-1] + columns_number;
      }

      // Initialize

      for(unsigned i = 0; i < rows_number; i++)
      {
         for(unsigned j = 0; j < columns_number; j++)
         {
            data[i][j] = type;
         }
      }
   }
}


/// File constructor. It creates a matrix which members are loaded froma a data file.
/// @param file_name Name of matrix data file.

explicit Matrix(const std::string& file_name)
{
   rows_number = 0;
   columns_number = 0;
   data = NULL;

   load(file_name);
}


/// Copy constructor. It creates a copy of an existing matrix. 
/// @param other_matrix Matrix to be copied.

Matrix(const Matrix& other_matrix) 
{
   const unsigned new_rows_number = other_matrix.rows_number;
   const unsigned new_columns_number = other_matrix.columns_number;

   data = NULL;

   if(new_rows_number == 0 && new_columns_number == 0)
   {
      rows_number = 0;
      columns_number = 0;
      data = NULL;
   }
   else if(new_rows_number == 0)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "Copy constructor.\n"
             << "Number of rows must be greater than zero.\n";

      throw std::logic_error(buffer.str());
   }
   else if(new_columns_number == 0)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "Copy constructor.\n"
             << "Number of columns must be greater than zero.\n";

      throw std::logic_error(buffer.str());
   }
   else
   {
      rows_number = new_rows_number;
      columns_number = new_columns_number;

      data = new Type*[rows_number];
      data[0] = new Type[rows_number*columns_number];

      for(unsigned i = 1; i < rows_number; i++)
      {
         data[i] = data[i-1] + columns_number;
      }
   }

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         data[i][j] = other_matrix[i][j];
      }
   }
}


// DESTRUCTOR

/// Destructor. 

~Matrix(void)
{
   if(data != NULL) 
   {
      delete[] (data[0]);
      delete[] (data);
   }
}


// ASSIGNMENT OPERATORS

/// Assignment operator. It assigns to self a copy of an existing matrix.
/// @param other_matrix Matrix to be assigned.

inline Matrix<Type>& operator = (const Matrix<Type>& other_matrix)
{
   if(this != &other_matrix) 
   {
      if(rows_number != other_matrix.rows_number || columns_number != other_matrix.columns_number) // other sizes
      {
         if(data != NULL) 
         {
            delete[] (data[0]);
            delete[] (data);
         }

         rows_number = other_matrix.rows_number;
         columns_number = other_matrix.columns_number;

         data = new Type*[rows_number];
         data[0] = new Type[rows_number*columns_number];

         for(unsigned i = 1; i < rows_number; i++)
         {
            data[i] = data[i-1] + columns_number;
         }
      }

      for(unsigned i = 0; i < rows_number; i++)
      {
         for(unsigned j = 0; j < columns_number; j++)
         {
            data[i][j] = other_matrix[i][j];
         }
      }
   }

   return(*this);
}


// REFERENCE OPERATORS

/// Reference operator.  

inline Type* operator [] (const unsigned& i)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(i >= rows_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "operator [] (unsigned).\n"
             << "Row index (" << i << ") must be less than number of rows (" << rows_number << ").\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   // Return matrix element

   return(data[i]);
}


/// Reference operator.  

inline const Type* operator [] (const unsigned& i) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 
   
   if(i >= rows_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "operator [] (const unsigned&) const.\n"
             << "Row index must be less than number of rows.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   // Return matrix element

   return(data[i]);
}


// bool operator == (const Matrix<Type>&) const

/// Equivalent relational operator between this matrix and other matrix.
/// It produces true if all the elements of the two matrices are equal, and false otherwise.
/// @param other_matrix Matrix to be compared with.

inline bool operator == (const Matrix<Type>& other_matrix) const
{       
   // Control sentence (if debug)      
       
   #ifndef NDEBUG 

   const unsigned other_rows_number = other_matrix.get_rows_number();
   const unsigned other_columns_number = other_matrix.get_columns_number();

   if(other_rows_number != rows_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "bool operator == (const Matrix<Type>&) const.\n"
             << "Both numbers of rows must be the same.\n";

      throw std::logic_error(buffer.str());
   }
   else if(other_columns_number != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "bool operator == (const Matrix<Type>&) const.\n"
             << "Both numbers of columns must be the same.\n";

      throw std::logic_error(buffer.str());
   }
      
   #endif

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         if(data[i][j] != other_matrix[i][j])
         {
            return(false);
         }     
      }
   }
   
   return(true);
}


// bool operator == (const Type&)

/// Equivalent relational operator between this matrix and a Type value.
/// It produces true if all the elements of this matrix are equal to the Type value, and false otherwise.
/// @param value Type value to be compared with.

inline bool operator == (const Type& value) const
{       
   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         if(data[i][j] != value)
         {
            return(false);
         }     
      }
   }
   
   return(true);
}


// bool operator != (const Matrix<Type>&)

/// Not equivalent relational operator between this matrix and other matrix.
/// It produces true if the two matrices have any not equal element, and false otherwise.
/// @param other_matrix Matrix to be compared with.

inline bool operator != (const Matrix<Type>& other_matrix) const
{       
   // Control sentence (if debug)      
       
   #ifndef NDEBUG 

   const unsigned other_rows_number = other_matrix.get_rows_number();
   const unsigned other_columns_number = other_matrix.get_columns_number();

   if(other_rows_number != rows_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "bool operator != (const Matrix<Type>&) const.\n"
             << "Both numbers of rows must be the same.\n";

      throw std::logic_error(buffer.str());
   }
   else if(other_columns_number != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "bool operator != (const Matrix<Type>&) const.\n"
             << "Both numbers of columns must be the same.\n";

      throw std::logic_error(buffer.str());
   }
      
   #endif

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         if(data[i][j] != other_matrix[i][j])
        {
            return(true);
        }     
      }
   }

   return(false);
}


// bool operator != (const Type&) const

/// Not equivalent relational operator between this matrix and a Type value.
/// It produces true if some element of this matrix is not equal to the Type value, and false otherwise.
/// @param value Type value to be compared with.

inline bool operator != (const Type& value) const
{            
   // Control sentence (if debug)      
       
   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         if(data[i][j] != value)
         {
            return(true);
         }     
      }
   }

   return(false);
}


// bool operator > (const Matrix<Type>&) const

/// Greater than relational operator between this matrix and other vector.
/// It produces true if all the elements of this matrix are greater than the corresponding elements of the other matrix,
/// and false otherwise.
/// @param other_matrix matrix to be compared with.

inline bool operator > (const Matrix<Type>& other_matrix) const
{       
   // Control sentence (if debug)      
       
   #ifndef NDEBUG 

   const unsigned other_rows_number = other_matrix.get_rows_number();
   const unsigned other_columns_number = other_matrix.get_columns_number();

   if(other_rows_number != rows_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "bool operator > (const Matrix<Type>&) const.\n"
             << "Both numbers of rows must be the same.\n";

      throw std::logic_error(buffer.str());
   }
   else if(other_columns_number != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "bool operator > (const Matrix<Type>&) const.\n"
             << "Both numbers of columns must be the same.\n";

      throw std::logic_error(buffer.str());
   }
      
   #endif

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < rows_number; j++)
      {
         if(data[i][j] <= other_matrix[i][j])
          {
            return(false);
         }     
      }
   }
   
   return(true);
}


// bool operator > (const Type&) const

/// Greater than relational operator between this matrix and a Type value.
/// It produces true if all the elements of this matrix are greater than the Type value, and false otherwise.
/// @param value Type value to be compared with.

inline bool operator > (const Type& value) const
{       
   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < rows_number; j++)
      {
         if(data[i][j] <= value)
          {
            return(false);
         }     
      }
   }
   
   return(true);
}


// bool operator < (const Matrix<Type>&) const

/// Less than relational operator between this matrix and other matrix.
/// It produces true if all the elements of this matrix are less than the corresponding elements of the other matrix,
/// and false otherwise.
/// @param other_matrix Matrix to be compared with.

inline bool operator < (const Matrix<Type>& other_matrix) const
{       
   // Control sentence (if debug)      
       
   #ifndef NDEBUG 

   const unsigned other_rows_number = other_matrix.get_rows_number();
   const unsigned other_columns_number = other_matrix.get_columns_number();

   if(other_rows_number != rows_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "bool operator < (const Matrix<Type>&) const.\n"
             << "Both numbers of rows must be the same.\n";

      throw std::logic_error(buffer.str());
   }
   else if(other_columns_number != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "bool operator < (const Matrix<Type>&) const.\n"
             << "Both numbers of columns must be the same.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         if(data[i][j] >= other_matrix[i][j])
         {
           return(false);
         }      
      }
   }

   return(true);
}


// bool operator < (const Type&) const

/// Less than relational operator between this matrix and a Type value.
/// It produces true if all the elements of this matrix are less than the Type value, and false otherwise.
/// @param value Type value to be compared with.

inline bool operator < (const Type& value) const
{       
   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         if(data[i][j] >= value)
         {
           return(false);
         }      
      }
   }

   return(true);
}


// bool operator >= (const Matrix<Type>&) const

/// Greater than or equal to relational operator between this matrix and other matrix.
/// It produces true if all the elements of this matrix are greater than or equal to the corresponding elements of the
/// other matrix, and false otherwise.
/// @param other_matrix Matrix to be compared with.

inline bool operator >= (const Matrix<Type>& other_matrix) const
{       
   // Control sentence (if debug)      
       
   #ifndef NDEBUG 

   const unsigned other_rows_number = other_matrix.get_rows_number();
   const unsigned other_columns_number = other_matrix.get_columns_number();

   if(other_rows_number != rows_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "bool operator >= (const Matrix<Type>&) const.\n"
             << "Both numbers of rows must be the same.\n";

      throw std::logic_error(buffer.str());
   }
   else if(other_columns_number != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "bool operator >= (const Matrix<Type>&) const.\n"
             << "Both numbers of columns must be the same.\n";

      throw std::logic_error(buffer.str());
   }
      
   #endif

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         if(data[i][j] < other_matrix[i][j])
         {
            return(false);
         }     
      }
   }
   
   return(true);
}


// bool operator >= (const Type&) const

/// Greater than or equal to than relational operator between this matrix and a Type value.
/// It produces true if all the elements of this matrix are greater than or equal to the Type value, and false otherwise.
/// @param value Type value to be compared with.

inline bool operator >= (const Type& value) const
{       
   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         if(data[i][j] < value)
         {
            return(false);
         }     
      }
   }
   
   return(true);
}


// bool operator <= (const Matrix<Type>&) const

/// Less than or equal to relational operator between this matrix and other matrix.
/// It produces true if all the elements of this matrix are less than or equal to the corresponding elements of the
/// other matrix, and false otherwise.
/// @param other_matrix Matrix to be compared with.

inline bool operator <= (const Matrix<Type>& other_matrix) const
{       
   // Control sentence (if debug)      
       
   #ifndef NDEBUG 

   const unsigned other_rows_number = other_matrix.get_rows_number();
   const unsigned other_columns_number = other_matrix.get_columns_number();

   if(other_rows_number != rows_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "bool operator >= (const Matrix<Type>&) const.\n"
             << "Both numbers of rows must be the same.\n";

      throw std::logic_error(buffer.str());
   }
   else if(other_columns_number != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "bool operator >= (const Matrix<Type>&) const.\n"
             << "Both numbers of columns must be the same.\n";

      throw std::logic_error(buffer.str());
   }
      
   #endif

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         if(data[i][j] > other_matrix[i][j])
         {
            return(false);
         }     
      }
   }

   return(true);
}


// bool operator <= (const Type&) const

/// Less than or equal to than relational operator between this matrix and a Type value.
/// It produces true if all the elements of this matrix are less than or equal to the Type value, and false otherwise.
/// @param value Type value to be compared with.

inline bool operator <= (const Type& value) const
{       
   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         if(data[i][j] > value)
          {
            return(false);
         }     
      }
   }

   return(true);
}


// METHODS

// unsigned get_rows_number(void) const method

/// Returns the number of rows in the matrix. 

const unsigned& get_rows_number(void) const
{
   return(rows_number);
}


// unsigned get_columns_number(void) const method

/// Returns the number of columns in the matrix. 

const unsigned& get_columns_number(void) const
{
   return(columns_number);
}


// void set(void) method

/// This method set the numbers of rows and columns of the matrix to zero. 

void set(void)
{
   if(data != NULL) 
   {
      delete[] (data[0]);
      delete[] (data);
   }

   rows_number = 0;
   columns_number = 0;
   data = NULL;
}


// void set(const unsigned&, const unsigned&) method

/// This method set new numbers of rows and columns in the matrix. 
/// @param new_rows_number Number of rows.
/// @param new_columns_number Number of columns.

void set(const unsigned& new_rows_number, const unsigned& new_columns_number)
{
   // Control sentence (if debug)

   if(new_rows_number == rows_number && new_columns_number == columns_number)
   {
      // do nothing
   }
   else if(new_rows_number == 0 && new_columns_number == 0)
   {
      set();
   }
   else if(new_rows_number == 0)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "void set(const unsigned&, const unsigned&) method.\n"
             << "Number of rows must be greater than zero.\n";

      throw std::logic_error(buffer.str());
   }
   else if(new_columns_number == 0)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "void set(const unsigned&, const unsigned&) method.\n"
             << "Number of columns must be greater than zero.\n";

      throw std::logic_error(buffer.str());
   }
   else
   {
      rows_number = new_rows_number;
      columns_number = new_columns_number;

      if(data != NULL) 
      {
         delete[] (data[0]);
         delete[] (data);
      }

      data = new Type*[rows_number];
      data[0] = new Type[rows_number*columns_number];

      for(unsigned i = 1; i < rows_number; i++)
      {
         data[i] = data[i-1] + columns_number;
      }
   }
}


// void set(const unsigned&, const unsigned&, const Type&) method

/// This method set new numbers of rows and columns in the matrix.
/// It also initializes all the matrix elements to a given value. 
/// @param new_rows_number Number of rows.
/// @param new_columns_number Number of columns.
/// @param value Initialization value.

void set(const unsigned& new_rows_number, const unsigned& new_columns_number, const Type& value)
{
   if(new_rows_number == 0 && new_columns_number == 0)
   {
      set();
   }
   else if(new_rows_number == 0)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "void set(const unsigned&, const unsigned&, const Type&) method.\n"
             << "Number of rows must be greater than zero.\n";

      throw std::logic_error(buffer.str());
   }
   else if(new_columns_number == 0)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
            << "void set(const unsigned&, const unsigned&, const Type&) method.\n"
            << "Number of columns must be greater than zero.\n";

      throw std::logic_error(buffer.str());
   }
   else
   {
      set(new_rows_number, new_columns_number);
      initialize(value);     
   }
}


// void set(const Matrix&) method

/// Sets all the members of the matrix to those of another matrix.
/// @param other_matrix Setting matrix. 

void set(const Matrix& other_matrix)
{
}


// void set(const std::string&) method

/// Sets the members of this object by loading them from a data file. 
/// @param file_name Name of data file.

void set(const std::string& file_name)
{
   load(file_name);
}


// void set_identity(unsigned) method

/// Sets the matrix to be squared, with elements equal one in the diagonal and zero outside the diagonal. 
/// @param new_size New number of rows and columns in this matrix.

void set_identity(const unsigned& new_size)
{
   set(new_size, new_size);
   initialize_identity();
}


// void set_rows_number(unsigned) method

/// Sets a new number of rows in the matrix. 
/// @param new_rows_number Number of matrix rows. 

void set_rows_number(const unsigned& new_rows_number)
{
   if(new_rows_number != rows_number) 
   {
      set(new_rows_number, columns_number);
   }
}


// void set_columns_number(unsigned) method

/// Sets a new number of columns in the matrix. 
/// @param new_columns_number Number of matrix columns. 

void set_columns_number(const unsigned& new_columns_number)
{
   if(new_columns_number != columns_number) 
   {
      set(rows_number, new_columns_number);
   }   
}


// void resize(const unsigned&, const unsigned&) method

/// Sets new numbers of rows and columns in the vector.
/// It does initialize the new matrix with the previous values. 
/// @param new_rows_number New number of rows.
/// @param new_columns_number New number of columns.

void resize(const unsigned& new_rows_number, const unsigned& new_columns_number)
{
   // Resize

   if(new_rows_number == rows_number && new_columns_number == columns_number)
   {   
      // Do nothing
   }
   else if(new_rows_number == 0 && new_columns_number == 0)
   {
      rows_number = 0;
      columns_number = 0;

      if(data != NULL) 
      {
         delete[] (data[0]);
         delete[] (data);
      }

      data = NULL;    
   }
   else if(new_rows_number == 0)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "void resize(const unsigned&, const unsigned&) method.\n"
             << "Number of rows must be greater than zero.\n";

      throw std::logic_error(buffer.str());
   }
   else if(new_columns_number == 0)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "void resize(const unsigned&, const unsigned&) method.\n"
             << "Number of columns must be greater than zero.\n";

      throw std::logic_error(buffer.str());
   }
   else
   {
      if(new_rows_number >= rows_number && new_columns_number >= columns_number)
      {
         const Matrix<Type> copy(*this);

         set(new_rows_number, new_columns_number);

         for(unsigned i = 0; i < copy.get_rows_number(); i++)
         {
            for(unsigned j = 0; j < copy.get_columns_number(); j++)
            {
    	         data[i][j] = copy[i][j];   
            }		 
         } 
      }     
      else if(new_rows_number >= rows_number && new_columns_number <= columns_number)
      {
         const Matrix<Type> copy(*this);

    	 set(new_rows_number, new_columns_number);

         for(unsigned i = 0; i < copy.get_rows_number(); i++)
         {
            for(unsigned j = 0; j < new_columns_number; j++)
	         {
               data[i][j] = copy[i][j];
            }		 
         }
      }
      else if(new_rows_number <= rows_number && new_columns_number >= columns_number)
      {
         const Matrix<Type> copy(*this);

   	     set(new_rows_number, new_columns_number);

         for(unsigned i = 0; i < new_rows_number; i++)
		 {
            for(unsigned j = 0; j < copy.get_columns_number(); j++)
		    {
			      data[i][j] = copy[i][j];
            }		 
	     }
	  }
	  else if(new_rows_number <= rows_number && new_columns_number >= columns_number)
	  {
	     const Matrix<Type> copy(*this);

         set(new_rows_number, new_columns_number);

		 for(unsigned i = 0; i < new_rows_number; i++)
		 {
            for(unsigned j = 0; j < new_columns_number; j++)
            {
			    data[i][j] = copy[i][j];
            }		 
         }
      }
   }
}



// void tuck_in(const unsigned&, const unsigned&, const Matrix<Type>&) const method

/// Tuck in another matrix starting from a given position.
/// @param row_position Insertion row position.
/// @param column_position Insertion row position.
/// @param other_matrix Matrix to be inserted.

void tuck_in(const unsigned& row_position, const unsigned& column_position, const Matrix<Type>& other_matrix)
{
   const unsigned other_rows_number = other_matrix.get_rows_number();
   const unsigned other_columns_number = other_matrix.get_columns_number();

   // Control sentence (if debug)            

   #ifndef NDEBUG 

   if(row_position + other_rows_number > rows_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "void tuck_in(const unsigned&, const unsigned&, const Matrix<Type>&) const method.\n"
             << "Cannot tuck in matrix.\n";

      throw std::logic_error(buffer.str());
   }

   if(column_position + other_columns_number > columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "void tuck_in(const unsigned&, const unsigned&, const Matrix<Type>&) const method.\n"
             << "Cannot tuck in matrix.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   for(unsigned i = 0; i < other_rows_number; i++)
   {
      for(unsigned j = 0; j < other_columns_number; j++)
      {
         data[row_position+i][column_position+j] = other_matrix[i][j];
	  }
   }
}


// unsigned count_diagonal_elements(void) const method

/// Returns the number of elements in the diagonal which are not zero.
/// This method is only defined for square matrices.

unsigned count_diagonal_elements(void) const
{
    #ifndef NDEBUG

    if(!is_square())
    {
       std::ostringstream buffer;

       buffer << "OpenNN Exception: Matrix Template.\n"
              << "unsigned count_diagonal_elements(void) const method.\n"
              << "The matrix is not square.\n";

       throw std::logic_error(buffer.str());
    }

    #endif

    const unsigned rows_number = get_rows_number();

    unsigned count = 0;

    for(unsigned i = 0; i < rows_number; i++)
    {
        if(data[i][i] != 0)
        {
            count++;
        }
    }

    return(count);
}


// unsigned count_off_diagonal_elements(void) const method

/// Returns the number of elements outside the diagonal which are not zero.
/// This method is only defined for square matrices.

unsigned count_off_diagonal_elements(void) const
{
    #ifndef NDEBUG

    if(!is_square())
    {
       std::ostringstream buffer;

       buffer << "OpenNN Exception: Matrix Template.\n"
              << "unsigned count_off_diagonal_elements(void) const method.\n"
              << "The matrix is not square.\n";

       throw std::logic_error(buffer.str());
    }

    #endif

    const unsigned rows_number = get_rows_number();
    const unsigned columns_number = get_columns_number();

    unsigned count = 0;

    for(unsigned i = 0; i < rows_number; i++)
    {
        for(unsigned j = 0; j < columns_number; j++)
        {
            if(i != j && data[i][j] != 0)
            {
                count++;
            }
        }
    }

    return(count);
}



// Matrix<Type> arrange_submatrix(const Vector<unsigned>&, const Vector<unsigned>&) const method

/// Returns a matrix with the values of given rows and columns from this matrix. 
/// @param row_indices Indices of matrix rows. 
/// @param column_indices Indices of matrix columns. 

Matrix<Type> arrange_submatrix(const Vector<unsigned>& row_indices, const Vector<unsigned>& column_indices) const
{
   const unsigned row_indices_size = row_indices.size();
   const unsigned column_indices_size = column_indices.size();

   Matrix<Type> sub_matrix(row_indices_size, column_indices_size);

   unsigned row_index;
   unsigned column_index;

   for(unsigned i = 0; i < row_indices_size; i++)
   {
      row_index = row_indices[i];

      for(unsigned j = 0; j < column_indices_size; j++)
	  {
         column_index = column_indices[j];
          
		 sub_matrix[i][j] = data[row_index][column_index];
	  }
   }

   return(sub_matrix);
}


// Matrix<Type> arrange_submatrix_rows(const Vector<unsigned>&) const method

/// Returns a submatrix with the values of given rows from this matrix. 
/// @param row_indices Indices of matrix rows. 

Matrix<Type> arrange_submatrix_rows(const Vector<unsigned>& row_indices) const
{
   const unsigned row_indices_size = row_indices.size();

   Matrix<Type> sub_matrix(row_indices_size, columns_number);

   unsigned row_index;

   for(unsigned i = 0; i < row_indices_size; i++)
   {
      row_index = row_indices[i];

      for(unsigned j = 0; j < columns_number; j++)
	  {
		 sub_matrix[i][j] = data[row_index][j];
	  }
   }

   return(sub_matrix);
}


// Matrix<Type> arrange_submatrix_columns(const Vector<unsigned>&) const method

/// Returns a submatrix with the values of given columns from this matrix. 
/// @param column_indices Indices of matrix columns. 

Matrix<Type> arrange_submatrix_columns(const Vector<unsigned>& column_indices) const
{
   const unsigned column_indices_size = column_indices.size();

   Matrix<Type> sub_matrix(rows_number, column_indices_size);

   unsigned column_index;

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < column_indices_size; j++)
	  {
         column_index = column_indices[j];
          
		 sub_matrix[i][j] = data[i][column_index];
	  }
   }

   return(sub_matrix);
}


// Vector<Type> arrange_row(const unsigned&) const method

/// Returns the row i of the matrix. 
/// @param i Index of row.

Vector<Type> arrange_row(const unsigned& i) const
{
   // Control sentence (if debug)            

   #ifndef NDEBUG 

   if(i >= rows_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "Vector<Type> arrange_row(const unsigned&) const method.\n"
             << "Row index (" << i << ") must be less than number of rows (" << rows_number << ").\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   Vector<Type> row(columns_number);

   for(unsigned j = 0; j < columns_number; j++)
   {
      row[j] = data[i][j];
   }

   return(row);
}


// Vector<Type> arrange_row(const unsigned&, const Vector<unsigned>&) const method

/// Returns the row i of the matrix, but only the elements specified by given indices. 
/// @param row_index Index of row.
/// @param column_indices Column indices of row.

Vector<Type> arrange_row(const unsigned& row_index, const Vector<unsigned>& column_indices) const
{
   // Control sentence (if debug)            

   #ifndef NDEBUG 

   if(row_index >= rows_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "Vector<Type> arrange_row(const unsigned&, const Vector<unsigned>&) const method.\n"
             << "Row index (" << row_index << ") must be less than number of rows (" << rows_number << ").\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   const unsigned size = column_indices.size();

   Vector<Type> row(size);

   for(unsigned i = 0; i < size; i++)
   {
      row[i] = data[row_index][column_indices[i]];
   }

   return(row);
}



// Vector<Type> arrange_column(const unsigned&) const method

/// Returns the column j of the matrix. 
/// @param j Index of column.

Vector<Type> arrange_column(const unsigned& j) const
{
   // Control sentence (if debug)            

   #ifndef NDEBUG 

   if(j >= columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "Vector<Type> arrange_column(const unsigned&) const method.\n"
             << "Column index (" << j << ") must be less than number of rows (" << columns_number << ").\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   Vector<Type> column(rows_number);

   for(unsigned i = 0; i < rows_number; i++)
   {
      column[i] = data[i][j];
   }

   return(column);
}


// Vector<Type> arrange_column(const unsigned&) const method

/// Returns the column j of the matrix, but only those elements specified by given indices. 
/// @param column_index Index of column.
/// @param row_indices Row indices of column.

Vector<Type> arrange_column(const unsigned& column_index, const Vector<unsigned>& row_indices) const
{
   // Control sentence (if debug)            

   #ifndef NDEBUG 

   if(column_index >= columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "Vector<Type> arrange_column(const unsigned&) const method.\n"
             << "Column index (" << column_index << ") must be less than number of rows (" << columns_number << ").\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   const unsigned size = row_indices.size();

   Vector<Type> column(size);

   for(unsigned i = 0; i < size; i++)
   {
      column[i] = data[row_indices[i]][column_index];
   }

   return(column);
}


// Vector<Type> get_diagonal(void) const method

/// Returns the diagonal of the matrix. 

Vector<Type> get_diagonal(void) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 
       
   if(rows_number != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "Vector<Type> get_diagonal(void) const method.\n"
             << "Matrix must be squared.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   Vector<Type> diagonal(rows_number);

   for(unsigned i = 0; i < rows_number; i++)
   {
      diagonal[i] = data[i][i];
   }

   return(diagonal);
}


// void set_row(const unsigned&, const Vector<Type>&) const method

/// Sets new values of a single row in the matrix. 
/// @param row_index Index of row. 
/// @param new_row New values of single row. 

void set_row(const unsigned& row_index, const Vector<Type>& new_row)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(row_index >= rows_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "set_row(const unsigned&, const Vector<Type>&) method.\n"
             << "Index must be less than number of rows.\n";

      throw std::logic_error(buffer.str());
   }

   const unsigned size = new_row.size();

   if(size != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "set_row(const unsigned&, const Vector<Type>&) method.\n"
             << "Size must be equal to number of columns.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   // Set new row

   for(unsigned i = 0; i < columns_number; i++)
   {
      data[row_index][i] = new_row[i];
   }
}


// void set_row(const unsigned&, const Type&) method

/// Sets a new value of a single row in the matrix. 
/// @param row_index Index of row. 
/// @param value New value of single row.

void set_row(const unsigned& row_index, const Type& value) 
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(row_index >= rows_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "set_row(const unsigned&, const Type&) method.\n"
             << "Index must be less than number of rows.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   // Set new row

   for(unsigned i = 0; i < columns_number; i++)
   {
      data[row_index][i] = value;
   }
}


// void set_column(const unsigned&, const Vector<Type>&) method

/// Sets new values of a single column in the matrix. 
/// @param column_index Index of column. 
/// @param new_column New values of single column. 

void set_column(const unsigned& column_index, const Vector<Type>& new_column)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(column_index >= columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "set_column(const unsigned&, const Vector<Type>&).\n"
             << "Index must be less than number of columns.\n";

      throw std::logic_error(buffer.str());
   }

   const unsigned size = new_column.size();

   if(size != rows_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "set_column(const unsigned&, const Vector<Type>&).\n"
             << "Size must be equal to number of rows.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   // Set new column

   for(unsigned i = 0; i < rows_number; i++)
   {
      data[i][column_index] = new_column[i];
   }
}


// void set_column(const unsigned&, const Type&) method

/// Sets a new values of a single column in the matrix. 
/// @param column_index Index of column. 
/// @param value New value of single column. 

void set_column(const unsigned& column_index, const Type& value)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(column_index >= columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "set_column(const unsigned&, const Type&).\n"
             << "Index must be less than number of columns.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   // Set new column

   for(unsigned i = 0; i < rows_number; i++)
   {
      data[i][column_index] = value;
   }
}


// void set_diagonal(const Type&) method


/// Sets a new value for the diagonal elements in the matrix. 
/// The matrix must be square. 
/// @param new_diagonal New value of diagonal. 

void set_diagonal(const Type& new_diagonal)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(rows_number != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "set_diagonal(const Type&).\n"
             << "Matrix must be square.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   // Set new column

   for(unsigned i = 0; i < rows_number; i++)
   {
      data[i][i] = new_diagonal;
   }
}


// void set_diagonal(const Vector<Type>&) method

/// Sets new values of the diagonal in the matrix. 
/// The matrix must be square. 
/// @param new_diagonal New values of diagonal. 

void set_diagonal(const Vector<Type>& new_diagonal)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(rows_number != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "set_diagonal(const Vector<Type>&) const.\n"
             << "Matrix is not square.\n";

      throw std::logic_error(buffer.str());
   }

   const unsigned size = new_diagonal.size();

   if(size != rows_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "set_diagonal(const Vector<Type>&) const.\n"
             << "Size of diagonal (" << size << ") is not equal to size of matrix (" << rows_number << ").\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   // Set new column

   for(unsigned i = 0; i < rows_number; i++)
   {
      data[i][i] = new_diagonal[i];
   }
}


// void initialize_diagonal(const unsigned&, const Type&) method

/// Sets this matrix to be diagonal. 
/// A diagonal matrix is a square matrix in which the entries outside the main diagonal are all zero.
/// It also initializes the elements on the main diagonal to a unique given value. 
/// @param new_size Number of rows and colums in the matrix. 
/// @param new_value Value of all the elements in the main diagonal. 

void initialize_diagonal(const unsigned& new_size, const Type& new_value)
{
   set(new_size, new_size, 0.0);
   set_diagonal(new_value);
}


// void initialize_diagonal(const unsigned&, const Vector<Type>&) method

/// Sets this matrix to be diagonal. 
/// A diagonal matrix is a square matrix in which the entries outside the main diagonal are all zero.
/// It also initializes the elements on the main diagonal to given values. 
/// @param new_size Number of rows and colums in the matrix. 
/// @param new_values Values of the elements in the main diagonal. 

void initialize_diagonal(const unsigned& new_size, const Vector<Type>& new_values)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned new_values_size = new_values.size();

   if(new_values_size != new_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "initialize_diagonal(const unsigned&, const unsigned&) const.\n"
             << "Size of new values is not equal to size of square matrix.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   set(new_size, new_size, 0.0);
   set_diagonal(new_values);
}


// Matrix<Type> sum_diagonal(const Type&) const method

/// This method sums a new value to the diagonal elements in the matrix. 
/// The matrix must be square. 
/// @param new_summing_value New summing value. 

Matrix<Type> sum_diagonal(const Type& new_summing_value) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(rows_number != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "sum_diagonal(const Type&) const.\n"
             << "Matrix must be square.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   Matrix<Type> sum(*this);

   for(unsigned i = 0; i < rows_number; i++)
   {
      sum[i][i] += new_summing_value;
   }

   return(sum);
}


// Matrix<Type> sum_diagonal(const Vector<Type>&) const method

/// This method sums new values to the diagonal in the matrix. 
/// The matrix must be square. 
/// @param new_summing_values Vector of summing values. 

Matrix<Type> sum_diagonal(const Vector<Type>& new_summing_values) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(rows_number != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "sum_diagonal(const Vector<Type>&) const.\n"
             << "Matrix must be square.\n";

      throw std::logic_error(buffer.str());
   }

   const unsigned size = new_summing_values.size();

   if(size != rows_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "sum_diagonal(const Vector<Type>&) const.\n"
             << "Size must be equal to number of rows.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   Matrix<Type> sum(*this);

   for(unsigned i = 0; i < rows_number; i++)
   {
      data[i][i] += new_summing_values[i];
   }

   return(sum);
}


// void append_row(const Vector<Type>&) const method

/// This method appends a new row to the matrix. 
/// The size of the row vector must be equal to the number of columns of the matrix.
/// Note that resizing is necessary here and therefore this method can be very inefficient. 
/// @param new_row Row to be appended.

void append_row(const Vector<Type>& new_row)
{
   #ifndef NDEBUG 

   const unsigned size = new_row.size();

   if(size != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "append_row(const Vector<Type>&) const.\n"
             << "Size must be equal to number of columns.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   resize(rows_number+1, columns_number);

   set_row(rows_number-1, new_row);
}


// void append_column(const Vector<Type>&) const method

/// This method appends a new column to the matrix. 
/// The size of the column vector must be equal to the number of rows of the matrix.
/// Note that resizing is necessary here and therefore this method can be very inefficient. 
/// @param new_column Column to be appended.

void append_column(const Vector<Type>& new_column) 
{
   #ifndef NDEBUG 

   const unsigned size = new_column.size();

   if(size != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "append_column(const Vector<Type>&) const.\n"
             << "Size must be equal to number of columns.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   resize(rows_number, columns_number+1);

   set_column(columns_number-1, new_column);
}


// void subtract_row(const unsigned&) const method

/// This method removes the row with given index. 
/// Note that resizing is here necessary and this method can be very inefficient. 
/// @param row_index Index of row to be removed. 

void subtract_row(const unsigned& row_index) 
{
   #ifndef NDEBUG 

   if(row_index >= rows_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "subtract_row(const unsigned&) const.\n"
             << "Index of row must be less than number of rows.\n";

      throw std::logic_error(buffer.str());
   }
   else if(rows_number < 2)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "subtract_row(const unsigned&) const.\n"
             << "Number of rows must be equal or greater than two.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   Matrix<Type> new_matrix(rows_number-1, columns_number);

   for(unsigned i = 0; i < row_index; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
        new_matrix[i][j] = data[i][j];
      }
   }

   for(unsigned i = row_index+1; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         new_matrix[i-1][j] = data[i][j];
      }
   }

   *this = new_matrix;
}


// void subtract_column(unsigned) method

/// This method removes the column with given index. 
/// Note that resizing is here necessary and this method can be very inefficient. 
/// @param column_index Index of column to be removed. 

void subtract_column(const unsigned& column_index)
{
   #ifndef NDEBUG 

   if(column_index >= columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "subtract_column(const unsigned&) const.\n"
             << "Index of column must be less than number of columns.\n";

      throw std::logic_error(buffer.str());
   }
   else if(columns_number < 2)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "subtract_column(const unsigned&) const.\n"
             << "Number of columns must be equal or greater than two.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   Matrix<Type> new_matrix(rows_number, columns_number-1);

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < column_index; j++)
      {
        new_matrix[i][j] = data[i][j];
      }
   }

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = column_index+1; j < columns_number; j++)
      {
         new_matrix[i][j-1] = data[i][j];
      }
   }

   *this = new_matrix;
}


// Matrix<Type> assemble_rows(const Matrix<Type>&) const method

/// Assemble two matrices.
/// @param other_matrix matrix to be get_assembled to this matrix.

Matrix<Type> assemble_rows(const Matrix<Type>& other_matrix) const
{
   #ifndef NDEBUG

   const unsigned other_columns_number = other_matrix.get_columns_number();

   if(other_columns_number != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "Matrix<Type> assemble_rows(const Matrix<Type>&) const method.\n"
             << "Number of columns of other matrix (" << other_columns_number << ") must be equal to number of columns of this matrix (" << columns_number << ").\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   const unsigned other_rows_number = other_matrix.get_rows_number();

   Matrix<Type> assembly(rows_number + other_rows_number, columns_number);

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         assembly[i][j] = data[i][j];
      }
   }

   for(unsigned i = 0; i < other_rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         assembly[rows_number+i][j] = other_matrix[i][j];
      }
   }

   return(assembly);
}


// Matrix<Type> assemble_columns(const Matrix<Type>&) const method

/// Assemble two matrices.
/// @param other_matrix matrix to be get_assemblyd to this matrix. 

Matrix<Type> assemble_columns(const Matrix<Type>& other_matrix) const
{
   #ifndef NDEBUG 

   const unsigned other_rows_number = other_matrix.get_rows_number();

   if(other_rows_number != rows_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "Matrix<Type> assemble_columns(const Matrix<Type>&) const method.\n"
             << "Number of rows of other matrix (" << other_rows_number << ") must be equal to number of rows of this matrix (" << rows_number << ").\n";

      throw std::logic_error(buffer.str());
   }

   #endif
	
   const unsigned other_columns_number = other_matrix.get_columns_number();

   Matrix<Type> assembly(rows_number, columns_number + other_columns_number);

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)   
	  {
         assembly[i][j] = data[i][j];
	  }
	  for(unsigned j = 0; j < other_columns_number; j++)
	  {
         assembly[i][columns_number+j] = other_matrix[i][j];
	  }
   }

   return(assembly);
}


// void initialize(const Type&) const method

/// Initializes all the elements of the matrix with a given value.
/// @param value Type value.

void initialize(const Type& value) const
{
   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         data[i][j] = value;
      }
   }
}


// void randomize_uniform(void) const method

/// Initializes all the elements in the matrix with random values comprised between -1 and 1.

void randomize_uniform(void) const
{
   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         data[i][j] =  calculate_random_uniform(-1.0, 1.0);
      }
   }
}


// void randomize_uniform(const double&, const double&) const method

/// Initializes all the elements in the matrix with random values comprised between a minimum and a maximum
/// values.
/// @param minimum Minimum possible value. 
/// @param maximum Maximum possible value. 

void randomize_uniform(const double& minimum, double maximum) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(minimum > maximum)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "void randomize_uniform(const double&, const double&) const method.\n"
             << "Minimum value must be less or equal than maximum value.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         data[i][j] = calculate_random_uniform(minimum, maximum);
      }
   }
}


// void randomize_uniform(const Matrix<double>&, const Matrix<double>&) const method

/// Initializes all the elements in the matrix with random values comprised between a minimum and a maximum
/// values for each element.
/// @param minimum Minimum possible values. 
/// @param maximum Maximum possible values. 

void randomize_uniform(const Matrix<double>& minimum, const Matrix<double>& maximum) const 
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(minimum > maximum)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "void randomize_uniform(const Matrix<double>&, const Matrix<double>&) const method.\n"
             << "Minimum values must be less or equal than their respective maximum values.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         data[i][j] = calculate_random_uniform(minimum[i][j], maximum[i][j]);
      }
   }
}


// void randomize_normal(void) const method

/// Assigns random values to each element in the matrix, taken from a normal distribution with
/// mean 0 and standard deviation 1. 

void randomize_normal(void) const
{
   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         data[i][j] = calculate_random_normal(0.0, 1.0);
      }
   }
}


// void randomize_normal(const double&, const double&) const method

/// Assigns random values to each element in the matrix, taken from a normal distribution with
/// a given mean and a given standard deviation. 
/// @param mean Mean value of uniform distribution.  
/// @param standard_deviation Standard deviation value of uniform distribution.

void randomize_normal(const double& mean, double standard_deviation) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(standard_deviation < 0.0)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "void randomize_normal(const double&, const double&) const method.\n"
             << "Standard deviation must be equal or greater than zero.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         data[i][j] = calculate_random_normal(mean, standard_deviation);
      }
   }
}


// void randomize_normal(const Matrix<double>&, const Matrix<double>&) const method

/// Assigns random values to each element in the vector, taken from normal distributions with
/// given means and standard deviations for each element. 
/// @param mean Mean values of uniform distributions.  
/// @param standard_deviation Standard deviation values of uniform distributions.

void randomize_normal(const Matrix<double>& mean, const Matrix<double>& standard_deviation) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(standard_deviation < 0.0)
   { 
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "void randomize_normal(const Matrix<double>&, const Matrix<double>&) const method.\n"
             << "Standard deviations must be equal or greater than zero.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         data[i][j] = calculate_random_uniform(mean[i][j], standard_deviation[i][j]);
      }
   }
}


// void initialize_identity(void) const method

/// Sets the diagonal elements in the matrix with ones and the rest elements with zeros. The matrix 
/// must be square. 

void initialize_identity(void) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 
   
   if(rows_number != columns_number)
   {
      std::ostringstream buffer;

      std::cout << "OpenNN Exception: Matrix Template.\n"
                << "initialize_identity(void) const method.\n"
                << "Matrix must be square.\n";
      
      throw std::logic_error(buffer.str());
   }

   #endif

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         if(i==j)
         {
            data[i][j] = 1;
         }
         else
         {
            data[i][j] = 0;      
         }
      }
   }
}


// void initialize_diagonal(const Type&) const method

/// Sets the diagonal elements in the matrix with ones and the rest elements with a given value. 
/// The matrix must be square. 

void initialize_diagonal(const Type& value) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 
   
   if(rows_number != columns_number)
   {
      std::ostringstream buffer;

      std::cout << "OpenNN Exception: Matrix Template.\n"
                << "initialize_diagonal(const Type&) const method.\n"
                << "Matrix must be square.\n";
      
      throw std::logic_error(buffer.str());
   }

   #endif

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         if(i==j)
         {
            data[i][j] = value;
         }
         else
         {
            data[i][j] = 0;      
         }
      }
   }
}


// Type calculate_sum(void) const method

/// Returns the sum of all the elements in the matrix.

Type calculate_sum(void) const
{
    const unsigned rows_number = get_rows_number();
    const unsigned columns_number = get_columns_number();

   Type sum = 0;

   for(unsigned i = 0; i < rows_number; i++)
   {
       for(unsigned j = 0; j < columns_number; j++)
       {
            sum += data[i][j];
       }
   }

   return(sum);
}


// double calculate_trace(void) const method

/// Returns the trace of the matrix, which is defined to be the sum of the main diagonal elements. 
/// The matrix must be square. 

double calculate_trace(void) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(!this->is_square())
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix template.\n"
             << "double calculate_trace(void) const method.\n" 
             << "Matrix is not square.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   double trace = 0.0;

   for(unsigned i = 0; i < rows_number; i++)
   {
      trace += data[i][i];
   }

   return(trace);
}


// Vector<double> calculate_mean(void) const method

/// Returns a vector with the mean values of all the matrix columns. 
/// The size is equal to the number of columns in the matrix. 

Vector<double> calculate_mean(void) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(rows_number == 0)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix template.\n"
             << "Vector<double> calculate_mean(void) const method.\n" 
             << "Number of rows must be greater than one.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   // Mean 

   Vector<double> mean(columns_number, 0.0);

   for(unsigned j = 0; j < columns_number; j++)
   {
      for(unsigned i = 0; i < rows_number; i++)
      {
         mean[j] += data[i][j];
      }

      mean[j] /= (double)rows_number;
   }

   return(mean);
}


// Vector<double> calculate_mean(const Vector<unsigned>&) const method

/// Returns a vector with the mean values of given columns. 
/// The size of the vector is equal to the size of the column indices vector. 
/// @param column_indices Indices of columns.  

Vector<double> calculate_mean(const Vector<unsigned>& column_indices) const
{
   const unsigned column_indices_size = column_indices.size();

   unsigned column_index;

   // Mean 

   Vector<double> mean(column_indices_size, 0.0);

   for(unsigned j = 0; j < column_indices_size; j++)
   {
      column_index = column_indices[j];

      for(unsigned i = 0; i < rows_number; i++)
      {
         mean[j] += data[i][column_index];
      }

      mean[j] /= (double)rows_number;
   }

   return(mean);
}


// Vector<double> calculate_mean(const Vector<unsigned>&, const Vector<unsigned>&) const method

/// Returns a vector with the mean values of given columns for given rows. 
/// The size of the vector is equal to the size of the column indices vector. 
/// @param row_indices Indices of rows.  
/// @param column_indices Indices of columns.  

Vector<double> calculate_mean(const Vector<unsigned>& row_indices, const Vector<unsigned>& column_indices) const
{
   const unsigned row_indices_size = row_indices.size();
   const unsigned column_indices_size = column_indices.size();

   // Control sentence (if debug)

   #ifndef NDEBUG 

   // Rows check

   if(row_indices_size > rows_number)
   {
      std::ostringstream buffer;

	  buffer << "OpenNN Exception: Matrix template.\n"
             << "Vector<double> calculate_mean(const Vector<unsigned>&, const Vector<unsigned>&) const method.\n" 
             << "Size of row indices (" << row_indices_size << ") is greater than number of rows (" << rows_number << ").\n";

      throw std::logic_error(buffer.str());
   }

   for(unsigned i = 0; i < row_indices_size; i++)
   {
      if(row_indices[i] >= rows_number)
	  {
         std::ostringstream buffer;

   	     buffer << "OpenNN Exception: Matrix template.\n"
                << "Vector<double> calculate_mean(const Vector<unsigned>&, const Vector<unsigned>&) const method.\n" 
                << "Row index " << i << " must be less than rows number.\n";

         throw std::logic_error(buffer.str());
	  }  
   }

   if(row_indices_size == 0)
   {
      std::ostringstream buffer;

	  buffer << "OpenNN Exception: Matrix template.\n"
             << "Vector<double> calculate_mean(const Vector<unsigned>&, const Vector<unsigned>&) const method.\n" 
             << "Size of row indices must be greater than zero.\n";

      throw std::logic_error(buffer.str());
   }

   // Columns check

   if(column_indices_size > columns_number)
   {
      std::ostringstream buffer;

	  buffer << "OpenNN Exception: Matrix template.\n"
             << "Vector<double> calculate_mean(const Vector<unsigned>&, const Vector<unsigned>&) const method.\n" 
             << "Column indices size must be equal or less than columns number.\n";

      throw std::logic_error(buffer.str());
   }

   for(unsigned i = 0; i < column_indices_size; i++)
   {
      if(column_indices[i] >= columns_number)
	  {
         std::ostringstream buffer;

   	     buffer << "OpenNN Exception: Matrix template.\n"
                << "Vector<double> calculate_mean(const Vector<unsigned>&, const Vector<unsigned>&) const method.\n" 
                << "Column index " << i << " must be less than columns number.\n";

         throw std::logic_error(buffer.str());
	  }  
   }

   #endif

   unsigned row_index;
   unsigned column_index;

   // Mean 

   Vector<double> mean(column_indices_size, 0.0);

   for(unsigned j = 0; j < column_indices_size; j++)
   {
	  column_index = column_indices[j];
	   
      for(unsigned i = 0; i < row_indices_size; i++)
      {
         row_index = row_indices[i];

         mean[j] += data[row_index][column_index];
      }

      mean[j] /= (double)rows_number;
   }

   return(mean);
}


// Vector<double> calculate_mean_standard_deviation(void) const method

/// Returns a vector of vectors with the mean and standard deviation values of all the matrix columns. 
/// The size of the vector is two.
/// The size of each element is equal to the number of columns in the matrix. 

Vector< Vector<double> > calculate_mean_standard_deviation(void) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(rows_number == 0)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix template.\n"
             << "Vector<double> calculate_mean_standard_deviation(void) const method.\n" 
             << "Number of rows must be greater than one.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   // Mean 

   Vector<double> mean(columns_number, 0.0);
   Vector<double> standard_deviation(columns_number, 0.0);

   for(unsigned i = 0; i < columns_number; i++)
   {
      mean[i] = this->arrange_column(i).calculate_mean();
      standard_deviation[i] = this->arrange_column(i).calculate_standard_deviation();

   }

   // Mean and standard deviation of data

   Vector< Vector<double> > mean_standard_deviation(2);

   mean_standard_deviation[0] = mean;
   mean_standard_deviation[1] = standard_deviation;

   return(mean_standard_deviation);
}


// Vector<double> calculate_mean_standard_deviation(const Vector<unsigned>&) const method

/// Returns a vector of vectors with the mean and standard deviation values of given columns. 
/// The size of the vector is two.
/// The size of each element is equal to the size of the column indices vector. 
/// @param column_indices Indices of columns.  

Vector< Vector<double> > calculate_mean_standard_deviation(const Vector<unsigned>& column_indices) const
{
   const unsigned column_indices_size = column_indices.size();

   Vector<double> mean(column_indices_size);
   Vector<double> standard_deviation(column_indices_size);

   unsigned column_index;

   Vector<double> column(rows_number);

   for(unsigned i = 0; i < column_indices_size; i++)
   {
      column_index = column_indices[i];

      column = this->arrange_column(column_index);

      mean[i] = column.calculate_mean();
      standard_deviation[i] = column.calculate_standard_deviation();
   }

   // Mean and standard deviation

   Vector< Vector<double> > mean_standard_deviation(2);

   mean_standard_deviation[0] = mean;
   mean_standard_deviation[1] = standard_deviation;

   return(mean_standard_deviation);
}


// Vector<double> calculate_mean_standard_deviation(const Vector<unsigned>&, const Vector<unsigned>&) const method

/// Returns a vector of vectors with the mean and standard deviation values of given columns for given rows. 
/// The size of the vector is two.
/// The size of each element is equal to the size of the column indices vector. 
/// @param row_indices Indices of rows.  
/// @param column_indices Indices of columns.  

Vector< Vector<double> > calculate_mean_standard_deviation(const Vector<unsigned>& row_indices, const Vector<unsigned>& column_indices) const
{
   const unsigned row_indices_size = row_indices.size();
   const unsigned column_indices_size = column_indices.size();

   // Control sentence (if debug)

   #ifndef NDEBUG 

   // Rows check

   if(row_indices_size > rows_number)
   {
      std::ostringstream buffer;

	  buffer << "OpenNN Exception: Matrix template.\n"
             << "Vector<double> calculate_mean_standard_deviation(const Vector<unsigned>&, const Vector<unsigned>&) const method.\n" 
             << "Row indices size must be equal or less than rows number.\n";

      throw std::logic_error(buffer.str());
   }

   for(unsigned i = 0; i < row_indices_size; i++)
   {
      if(row_indices[i] >= rows_number)
	  {
         std::ostringstream buffer;

   	     buffer << "OpenNN Exception: Matrix template.\n"
                << "Vector<double> calculate_mean_standard_deviation(const Vector<unsigned>&, const Vector<unsigned>&) const method.\n" 
                << "Row index " << i << " must be less than rows number.\n";

         throw std::logic_error(buffer.str());
	  }  
   }

   if(row_indices_size == 0)
   {
      std::ostringstream buffer;

	  buffer << "OpenNN Exception: Matrix template.\n"
             << "Vector<double> calculate_mean_standard_deviation(const Vector<unsigned>&, const Vector<unsigned>&) const method.\n" 
             << "Size of row indices must be greater than zero.\n";

      throw std::logic_error(buffer.str());
   }

   // Columns check

   if(column_indices_size > columns_number)
   {
      std::ostringstream buffer;

	  buffer << "OpenNN Exception: Matrix template.\n"
             << "Vector<double> calculate_mean_standard_deviation(const Vector<unsigned>&, const Vector<unsigned>&) const method.\n" 
             << "Column indices size must be equal or less than columns number.\n";

      throw std::logic_error(buffer.str());
   }

   for(unsigned i = 0; i < column_indices_size; i++)
   {
      if(column_indices[i] >= columns_number)
	  {
         std::ostringstream buffer;

   	     buffer << "OpenNN Exception: Matrix template.\n"
                << "Vector<double> calculate_mean_standard_deviation(const Vector<unsigned>&, const Vector<unsigned>&) const method.\n" 
                << "Column index " << i << " must be less than columns number.\n";

         throw std::logic_error(buffer.str());
	  }  
   }

   #endif

   unsigned row_index;
   unsigned column_index;

   // Mean 

   Vector<double> mean(column_indices_size, 0.0);

   for(unsigned j = 0; j < column_indices_size; j++)
   {
	  column_index = column_indices[j];
	   
	  mean[j] = 0.0;    

      for(unsigned i = 0; i < row_indices_size; i++)
      {
         row_index = row_indices[i];

         mean[j] += data[row_index][column_index];
      }

      mean[j] /= (double)rows_number;
   }

   // Standard deviation

   Vector<double> standard_deviation(column_indices_size, 0.0);

   for(unsigned j = 0; j < column_indices_size; j++)
   {
	  column_index = column_indices[j];
   
      standard_deviation[j] = 0.0;

      for(unsigned i = 0; i < row_indices_size; i++)
      {
         row_index = row_indices[i];

         standard_deviation[j] += (data[row_index][column_index] - mean[j])*(data[row_index][column_index] - mean[j]);
      }

      standard_deviation[j] = sqrt(standard_deviation[j]/(rows_number-1.0));
   }

   // Mean and standard deviation

   Vector< Vector<double> > mean_standard_deviation(2);

   mean_standard_deviation[0] = mean;
   mean_standard_deviation[1] = standard_deviation;

   return(mean_standard_deviation);
}


// Type calculate_minimum(void) const method

/// Returns the minimum value from all elements in the matrix.

Type calculate_minimum(void) const
{
   Type minimum = 1.0e99;

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         if(data[i][j] < minimum)
         {
            minimum = data[i][j];
         }
      }
   }

   return(minimum);
}


// Type calculate_maximum(void) const method

/// Returns the maximum value from all elements in the matrix.

Type calculate_maximum(void) const
{
   Type maximum = -1.0e99;

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         if(data[i][j] > maximum)
         {
            maximum = data[i][j];
         }
      }
   }

   return(maximum);
}


// Vector< Vector<Type> > calculate_minimum_maximum(void) const method

/// Returns a vector of vectors with the minimum and maximum values of all the matrix columns. 
/// The size of the vector is two.
/// The size of each element is equal to the number of columns in the matrix. 

Vector< Vector<Type> > calculate_minimum_maximum(void) const
{
   Vector< Vector<Type> > minimum_maximum(2);

   Vector<Type> minimum(columns_number,  1.0e99);
   Vector<Type> maximum(columns_number, -1.0e99);

   for(unsigned j = 0; j < columns_number; j++)
   {
      for(unsigned i = 0; i < rows_number; i++)
      {    
         if(data[i][j] < minimum[j])
         {
            minimum[j] = data[i][j];
         }

         if(data[i][j] > maximum[j])
         {
            maximum[j] = data[i][j];
         }
      }
   }

   // Minimum and maximum

   minimum_maximum[0] = minimum;
   minimum_maximum[1] = maximum;

   return(minimum_maximum);
}


// Vector<double> calculate_minimum_maximum(const Vector<unsigned>&) const method

/// Returns a vector of vectors with the minimum and maximum values of given columns. 
/// The size of the vector is two.
/// The size of each element is equal to the size of the column indices vector. 
/// @param column_indices Indices of columns.  

Vector< Vector<Type> > calculate_minimum_maximum(const Vector<unsigned>& column_indices) const
{
   const unsigned column_indices_size = column_indices.size();

   #ifndef NDEBUG 

   for(unsigned i = 0; i < column_indices_size; i++)
   {      
      if(column_indices[i] >= columns_number)
      {
         std::ostringstream buffer;

         buffer << "OpenNN Exception: Matrix template." 
                << "Vector<Type> calculate_minimum_maximum(const Vector<unsigned>&) const method.\n" 
                << "Index of column must be less than number of columns.\n";

         throw std::logic_error(buffer.str());
      }
   }   

   #endif

   unsigned column_index;

   Vector<Type> minimum(column_indices_size,  1.0e99);
   Vector<Type> maximum(column_indices_size, -1.0e99);

   for(unsigned j = 0; j < column_indices_size; j++)
   {
      column_index = column_indices[j];

      for(unsigned i = 0; i < rows_number; i++)
      {    
         if(data[i][column_index] < minimum[j])
         {
            minimum[j] = data[i][column_index];
         }

         if(data[i][column_index] > maximum[j])
         {
            maximum[j] = data[i][column_index];
         }
      }
   }

   // Minimum and maximum

   Vector< Vector<Type> > minimum_maximum(2);

   minimum_maximum[0] = minimum;
   minimum_maximum[1] = maximum;

   return(minimum_maximum);
}


// Vector<double> calculate_minimum_maximum(const Vector<unsigned>&, const Vector<unsigned>&) const method

/// Returns a vector of vectors with the minimum and maximum values of given columns for given rows. 
/// The size of the vector is two.
/// The size of each element is equal to the size of the column indices vector. 
/// @param row_indices Indices of rows.  
/// @param column_indices Indices of columns.  

Vector< Vector<Type> > calculate_minimum_maximum(const Vector<unsigned>& row_indices, const Vector<unsigned>& column_indices) const
{
   const unsigned row_indices_size = row_indices.size();
   const unsigned column_indices_size = column_indices.size();

   Vector<Type> minimum(column_indices_size,  1.0e99);
   Vector<Type> maximum(column_indices_size, -1.0e99);

   unsigned row_index;
   unsigned column_index;

   for(unsigned j = 0; j < column_indices_size; j++)
   {
      column_index = column_indices[j];

      for(unsigned i = 0; i < row_indices_size; i++)
      {    
         row_index = row_indices[i];

         if(data[row_index][column_index] < minimum[j])
         {
            minimum[j] = data[row_index][column_index];
         }

         if(data[row_index][column_index] > maximum[j])
         {
            maximum[j] = data[row_index][column_index];
         }
      }
   }

   // Minimum and maximum

   Vector< Vector<Type> > minimum_maximum(2);

   minimum_maximum[0] = minimum;
   minimum_maximum[1] = maximum;

   return(minimum_maximum);
}


// Vector< Statistics<Type> > calculate_statistics(void) const method

/// Returns the basic statistics of the columns. 
/// The format is a vector of statistics structures.
/// The size of that vector is equal to the number of columns in this matrix.

Vector< Statistics<Type> > calculate_statistics(void) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(rows_number == 0)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix template.\n"
             << "Vector< Statistics<double> > calculate_statistics(void) const method.\n"
             << "Number of rows must be greater than one.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   Vector< Statistics<Type> > statistics(columns_number);

   Vector<Type> column(rows_number);

   for(unsigned i = 0; i < columns_number; i++)
   {
      column = arrange_column(i);

      statistics[i] = column.calculate_statistics();
   }

   return(statistics);
}


// Vector< Statistics<Type> > calculate_statistics(const Vector<unsigned>&, const Vector<unsigned>&) const method

/// Returns the basic statistics of given columns for given rows.
/// The format is a vector of statistics structures.
/// The size of that vector is equal to the number of given columns.
/// @param row_indices Indices of the rows for which the statistics are to be computed.
/// @param column_indices Indices of the columns for which the statistics are to be computed.

Vector< Statistics<Type> > calculate_statistics(const Vector<unsigned>& row_indices, const Vector<unsigned>& column_indices) const
{
    const unsigned row_indices_size = row_indices.size();
    const unsigned column_indices_size = column_indices.size();

    Vector< Statistics<Type> > statistics(column_indices_size);

    unsigned index;

    Vector<Type> column(row_indices_size);

    for(unsigned i = 0; i < column_indices_size; i++)
    {
        index = column_indices[i];

        column = arrange_column(index, row_indices);

        statistics[i] = column.calculate_statistics();
    }

    return statistics;
}


// Vector< Statistics<Type> > calculate_rows_statistics(const Vector<unsigned>&) const method

/// Returns the basic statistics of all the columns for given rows.
/// The format is a vector of statistics structures.
/// The size of that vector is equal to the number of columns in this matrix.
/// @param row_indices Indices of the rows for which the statistics are to be computed.

Vector< Statistics<Type> > calculate_rows_statistics(const Vector<unsigned>& row_indices) const
{
    const unsigned row_indices_size = row_indices.size();

    Vector< Statistics<Type> > statistics(columns_number);

    Vector<Type> column(row_indices_size);

    for(unsigned i = 0; i < columns_number; i++)
    {
        column = arrange_column(i, row_indices);

        statistics[i] = column.calculate_statistics();
    }

    return statistics;
}


// Vector< Statistics<Type> > calculate_columns_statistics(const Vector<unsigned>&) const method

/// Returns the basic statistics of given columns.
/// The format is a vector of statistics structures.
/// The size of that vector is equal to the number of given columns.
/// @param column_indices Indices of the columns for which the statistics are to be computed.

Vector< Statistics<Type> > calculate_columns_statistics(const Vector<unsigned>& column_indices) const
{
    const unsigned column_indices_size = column_indices.size();

    Vector< Statistics<Type> > statistics(column_indices_size);

    unsigned index;
    Vector<Type> column(rows_number);

    for(unsigned i = 0; i < column_indices_size; i++)
    {
        index = column_indices[i];

        column = arrange_column(index);

        statistics[i] = column.calculate_statistics();
    }

    return statistics;
}


// Vector<Histogram<Type> > calculate_histograms(const unsigned&) const method

/// Calculates a histogram for each column, each having a given number of bins.
/// It returns a vector of vectors of vectors.
/// The size of the main vector is the number of columns. 
/// Each subvector contains the frequencies and centers of that colums.
/// @param bins_number Number of bins for each histogram.  

Vector< Histogram<Type> > calculate_histograms(const unsigned& bins_number = 10) const
{
   Vector< Histogram<Type> > histograms(columns_number);

   Vector<Type> column(rows_number);

   for(unsigned i = 0; i < columns_number; i++)
   {
      column = arrange_column(i);

      histograms[i] = column.calculate_histogram(bins_number);
   }

   return(histograms);
}


// void scale_mean_standard_deviation(const Vector< Statistics<Type> >&) method

/// Scales the matrix elements with the mean and standard deviation method.
/// It updates the data in the matrix.
/// @param statistics Vector of statistics structures conatining the mean and standard deviation values for the scaling.
/// The size of that vector must be equal to the number of columns in this matrix.

void scale_mean_standard_deviation(const Vector< Statistics<Type> >& statistics)
{
   #ifndef NDEBUG 

   const unsigned size = statistics.size();

   if(size != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix template." 
             << "void scale_mean_standard_deviation(const Vector< Statistics<Type> >&) const method.\n"
             << "Size of statistics vector must be equal to number of columns.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   // Rescale data

   for(unsigned j = 0; j < columns_number; j++)
   {
      if(statistics[j].standard_deviation < 1e-99)
      {
         // Do nothing
      }
      else
      {
         for(unsigned i = 0; i < rows_number; i++)
         {
            data[i][j] = (data[i][j] - statistics[j].mean)/statistics[j].standard_deviation;
         }
      }
   }
}


// Vector< Statistics<Type> > scale_mean_standard_deviation(void) method

/// Scales the data using the mean and standard deviation method and
/// the mean and standard deviation values calculated from the matrix.
/// It also returns the statistics of all the columns.

Vector< Statistics<Type> > scale_mean_standard_deviation(void)
{
    const Vector< Statistics<Type> > statistics = calculate_statistics();

    scale_mean_standard_deviation(statistics);

    return(statistics);
}


// void scale_rows_mean_standard_deviation(const Vector< Statistics<Type> >&, const Vector<unsigned>&) const

/// Scales given rows from the matrix using the mean and standard deviation method.
/// @param statistics Vector of statistics for all the columns.
/// @param row_indices Indices of rows to be scaled.

void scale_rows_mean_standard_deviation(const Vector< Statistics<Type> >& statistics, const Vector<unsigned>& row_indices) const
{
    // Control sentence (if debug)

    #ifndef NDEBUG

    const unsigned statistics_size = statistics.size();

    if(statistics_size != columns_number)
    {
       std::ostringstream buffer;

       buffer << "OpenNN Exception: DataSet class.\n"
              << "void scale_rows_mean_standard_deviation(const Vector< Statistics<Type> >&, const Vector<unsigned>&) method.\n"
              << "Size of statistics must be equal to number of columns.\n";

       throw std::logic_error(buffer.str());
    }

    #endif

    unsigned row_index;

    // Scale columns

    for(unsigned j = 0; j < columns_number; j++)
    {
       if(statistics[j].standard_deviation < 1e-99)
       {
          // Do nothing
       }
       else
       {
          for(unsigned i = 0; i < row_indices.size(); i++)
          {
             row_index = row_indices[i];

             data[row_index][j] = (data[row_index][j] - statistics[j].mean)/statistics[j].standard_deviation;
          }
       }
    }
}


// void scale_columns_mean_standard_deviation(const Vector< Statistics<Type> >&, const Vector<unsigned>&) method

/// Scales given columns of this matrix with the mean and standard deviation method.
/// @param statistics Vector of statistics structure containing the mean and standard deviation values for the scaling.
/// The size of that vector must be equal to the number of columns to be scaled.
/// @param columns_indices Vector of indices with the columns to be scaled.
/// The size of that vector must be equal to the number of columns to be scaled.

void scale_columns_mean_standard_deviation(const Vector< Statistics<Type> >& statistics, const Vector<unsigned>& columns_indices)
{
   const unsigned columns_indices_size = columns_indices.size();

   // Control sentence (if debug)

   #ifndef NDEBUG

   const unsigned statistics_size = statistics.size();

   if(statistics_size != columns_indices_size)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: DataSet class.\n"
             << "void scale_columns_mean_standard_deviation(const Vector< Statistics<Type> >&, const Vector<unsigned>&) method.\n"
             << "Size of statistics must be equal to size of columns indices.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   unsigned column_index;

   // Scale columns

   for(unsigned j = 0; j < columns_indices_size; j++)
   {
      if(statistics[j].standard_deviation < 1e-99)
      {
         // Do nothing
      }
      else
      {
         column_index = columns_indices[j];

         for(unsigned i = 0; i < rows_number; i++)
         {
            data[i][column_index] = (data[i][column_index] - statistics[j].mean)/statistics[j].standard_deviation;
         }
      }
   }
}


// void scale_rows_columns_mean_standard_deviation(const Vector< Statistics<Type> >&, const Vector<unsigned>&, const Vector<unsigned>&) const

/// @todo

void scale_rows_columns_mean_standard_deviation(const Vector< Statistics<Type> >& statistics, const Vector<unsigned>& row_indices, const Vector<unsigned>& column_indices) const
{

}


// void scale_minimum_maximum(const Vector< Statistics<Type> >&) method

/// Scales the matrix columns with the minimum and maximum method.
/// It updates the data in the matrix.
/// @param statistics Vector of statistics structures containing the minimum and maximum values for the scaling.
/// The size of that vector must be equal to the number of columns in this matrix.

void scale_minimum_maximum(const Vector< Statistics<Type> >& statistics) const
{
   #ifndef NDEBUG 

   const unsigned size = statistics.size();

   if(size != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix template." 
             << "void scale_minimum_maximum(const Vector< Statistics<Type> >&) const method.\n"
             << "Size of statistics vector must be equal to number of columns.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   // Rescale data

   for(unsigned j = 0; j < columns_number; j++)
   {
      if(statistics[j].maximum - statistics[j].minimum < 1e-99)
      {
            // Do nothing
      }
      else
      {
         for(unsigned i = 0; i < rows_number; i++)
         {
            data[i][j] = 2.0*(data[i][j] - statistics[j].minimum)/(statistics[j].maximum-statistics[j].minimum)-1.0;
         }
      }
   }
}


// Vector< Statistics<Type> > scale_minimum_maximum(void) method

/// Scales the data using the minimum and maximum method and
/// the minimum and maximum values calculated from the matrix.
/// It also returns the statistics of all the columns.

Vector< Statistics<Type> > scale_minimum_maximum(void)
{
    const Vector< Statistics<Type> > statistics = calculate_statistics();

    scale_minimum_maximum(statistics);

    return(statistics);
}


// void scale_rows_minimum_maximum(const Vector< Statistics<Type> >&, const Vector<unsigned>&) const

/// Scales given rows from the matrix using the minimum and maximum method.
/// @param statistics Vector of statistics for all the columns.
/// @param row_indices Indices of rows to be scaled.

void scale_rows_minimum_maximum(const Vector< Statistics<Type> >& statistics, const Vector<unsigned>& row_indices) const
{
    // Control sentence (if debug)

    const unsigned row_indices_size = row_indices.size();

    #ifndef NDEBUG

    const unsigned statistics_size = statistics.size();

    if(statistics_size != columns_number)
    {
       std::ostringstream buffer;

       buffer << "OpenNN Exception: DataSet class.\n"
              << "void scale_rows_minimum_maximum(const Vector< Statistics<Type> >&, const Vector<unsigned>&) method.\n"
              << "Size of statistics must be equal to number of columns.\n";

       throw std::logic_error(buffer.str());
    }

    #endif

    // Rescale targets data

    unsigned row_index;

    for(unsigned j = 0; j < columns_number; j++)
    {
       if(statistics[j].maximum - statistics[j].minimum < 1e-99)
       {
          // Do nothing
       }
       else
       {
          for(unsigned i = 0; i < row_indices_size; i++)
          {
             row_index = row_indices[i];

             data[row_index][j] = 2.0*(data[row_index][j] - statistics[j].minimum)/(statistics[j].maximum-statistics[j].minimum) - 1.0;
          }
       }
    }
}


// void scale_columns_minimum_maximum(const Vector< Statistics<Type> >&, const Vector<unsigned>&) const

/// Scales given columns of this matrix with the minimum and maximum method.
/// @param statistics Vector of statistics structure containing the minimum and maximum values for the scaling.
/// The size of that vector must be equal to the number of columns to be scaled.
/// @param column_indices Vector of indices with the columns to be scaled.
/// The size of that vector must be equal to the number of columns to be scaled.

void scale_columns_minimum_maximum(const Vector< Statistics<Type> >& statistics, const Vector<unsigned>& column_indices) const
{
    // Control sentence (if debug)

    const unsigned column_indices_size = column_indices.size();

    #ifndef NDEBUG

    const unsigned statistics_size = statistics.size();

    if(statistics_size != column_indices_size)
    {
       std::ostringstream buffer;

       buffer << "OpenNN Exception: DataSet class.\n"
              << "void scale_columns_minimum_maximum(const Vector< Statistics<Type> >&, const Vector<unsigned>&) method.\n"
              << "Size of statistics must be equal to size of columns indices.\n";

       throw std::logic_error(buffer.str());
    }

    #endif

    unsigned column_index;

    // Rescale targets data

    for(unsigned j = 0; j < column_indices_size; j++)
    {
       column_index = column_indices[j];

       if(statistics[j].maximum - statistics[j].minimum < 1e-99)
       {
          // Do nothing
       }
       else
       {
          for(unsigned i = 0; i < rows_number; i++)
          {
             data[i][column_index] = 2.0*(data[i][column_index] - statistics[j].minimum)/(statistics[j].maximum-statistics[j].minimum) - 1.0;
          }
       }
    }
}


// void scale_rows_columns_minimum_maximum(const Vector< Statistics<Type> >&, const Vector<unsigned>&, const Vector<unsigned>&) const

/// @todo

void scale_rows_columns_minimum_maximum(const Vector< Statistics<Type> >& statistics, const Vector<unsigned>& row_indices, const Vector<unsigned>& column_indices) const
{

}


// void unscale_mean_standard_deviation(const Vector< Statistics<Type> >&) method

/// Unscales the matrix columns with the mean and standard deviation method.
/// It updates the matrix elements.
/// @param statistics Vector of statistics structures containing the mean and standard deviations for the unscaling.
/// The size of that vector must be equal to the number of columns in this matrix.

void unscale_mean_standard_deviation(const Vector< Statistics<Type> >& statistics)
{
   #ifndef NDEBUG 

   const unsigned size = statistics.size();

   if(size != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix template." 
             << "void unscale_mean_standard_deviation(const Vector< Statistics<Type> >&) const method.\n"
             << "Size of statistics vector must be equal to number of columns.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   for(unsigned j = 0; j < columns_number; j++)
   {
      if(statistics[j].standard_deviation < 1e-99)
      {
         // Do nothing
      }
      else
      {
         for(unsigned i = 0; i < rows_number; i++)
         {
            data[i][j] = data[i][j]*statistics[j].standard_deviation + statistics[j].mean;
         }
      }
   }
}


// void unscale_rows_mean_standard_deviation(const Vector< Statistics<Type> >&, const Vector<unsigned>&) method

/// Unscales given rows using the mean and standard deviation method.
/// @param statistics Vector of statistics structures for all the columns.
/// The size of this vector must be equal to the number of columns.
/// @param row_indices Indices of rows to be unscaled.
///
void unscale_rows_mean_standard_deviation(const Vector< Statistics<Type> >& statistics, const Vector<unsigned>& row_indices)
{
    unsigned row_index;

    // Unscale columns

    for(unsigned j = 0;  j < columns_number; j++)
    {
       if(statistics[j].standard_deviation < 1e-99)
       {
          // Do nothing
       }
       else
       {
          for(unsigned i = 0; i < rows_number; i++)
          {
             row_index = row_indices[i];

             data[row_index][j] = data[row_index][j]*statistics[j].standard_deviation + statistics[j].mean;
          }
       }
    }
}


// void unscale_columns_mean_standard_deviation(const Vector< Statistics<Type> >&, const Vector<unsigned>&) method

/// Scales given columns of this matrix with the mean and standard deviation method.
/// @param statistics Vector of statistics structure containing the mean and standard deviation values for the scaling.
/// The size of that vector must be equal to the number of columns in the matrix.
/// @param column_indices Vector of indices with the columns to be scaled.
/// The size of that vector must be equal to the number of columns to be scaled.

void unscale_columns_mean_standard_deviation(const Vector< Statistics<Type> >& statistics, const Vector<unsigned>& column_indices)
{
   unsigned column_index;

   // Unscale columns

   for(unsigned j = 0;  j < column_indices.size(); j++)
   {
      column_index = column_indices[j];

      if(statistics[column_index].standard_deviation < 1e-99)
      {
         // Do nothing
      }
      else
      {
         for(unsigned i = 0; i < rows_number; i++)
         {
            data[i][column_index] = data[i][column_index]*statistics[column_index].standard_deviation + statistics[column_index].mean;
         }
      }
   }
}


// void unscale_rows_columns_mean_standard_deviation(const Vector< Statistics<Type> >&, const Vector<unsigned>&) method

/// @todo

void unscale_rows_columns_mean_standard_deviation(const Vector< Statistics<Type> >& statistics, const Vector<unsigned>& row_indices, const Vector<unsigned>& column_indices)
{
}


// void unscale_minimum_maximum(const Vector< Statistics<Type> >&) method

/// Unscales the matrix columns with the minimum and maximum method.
/// @param statistics Vector of statistics which contains the minimum and maximum scaling values.
/// The size of that vector must be equal to the number of columns in this matrix.

void unscale_minimum_maximum(const Vector< Statistics<Type> >& statistics)
{
   #ifndef NDEBUG 

   const unsigned size = statistics.size();

   if(size != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix template." 
             << "void unscale_minimum_maximum(const Vector< Statistics<Type> >&) method.\n"
             << "Size of minimum vector must be equal to number of columns.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   for(unsigned j = 0; j < columns_number; j++)
   {
      if(statistics[j].maximum - statistics[j].minimum < 1e-99)
      {
         std::cout << "OpenNN Warning: Matrix template.\n"
                   << "void unscale_minimum_maximum(const Vector< Statistics<Type> >&) const method.\n"
                   << "Minimum and maximum values of column " << j << " are equal.\n"
                   << "Those columns won't be unscaled.\n";

         // Do nothing
      }
      else
      {
         for(unsigned i = 0; i < rows_number; i++)
         {
            data[i][j] = 0.5*(data[i][j] + 1.0)*(statistics[j].maximum-statistics[j].minimum) + statistics[j].minimum;
         }
      }
   }
}


// void unscale_rows_minimum_maximum(const Vector< Statistics<Type> >&, const Vector<unsigned>&) method

/// Unscales given rows using the minimum and maximum method.
/// @param statistics Vector of statistics structures for all the columns.
/// The size of this vector must be equal to the number of columns.
/// @param row_indices Indices of rows to be unscaled.

void unscale_rows_minimum_maximum(const Vector< Statistics<Type> >& statistics, const Vector<unsigned>& row_indices)
{
    unsigned row_index;

    // Unscale rows

    for(unsigned j = 0; j < columns_number; j++)
    {
       if(statistics[j].maximum - statistics[j].minimum < 1e-99)
       {
          // Do nothing
       }
       else
       {
          for(unsigned i = 0; i < rows_number; i++)
          {
              row_index = row_indices[i];

             data[row_index][j] = 0.5*(data[row_index][j] + 1.0)*(statistics[j].maximum-statistics[j].minimum)
             + statistics[j].minimum;
          }
       }
    }
}


// void unscale_columns_minimum_maximum(const Vector< Statistics<Type> >&, const Vector<unsigned>&) method

/// Unscales given columns in the matrix with the minimum and maximum method.
/// @param statistics Vector of statistics structures containing the minimum and maximum values for the unscaling.
/// The size of that vector must be equal to the number of columns in the matrix.
/// @param column_indices Vector of indices of the columns to be unscaled.
/// The size of that vector must be equal to the number of columns to be unscaled.

void unscale_columns_minimum_maximum(const Vector< Statistics<Type> >& statistics, const Vector<unsigned>& column_indices)
{
    unsigned column_index;

    // Unscale columns

    for(unsigned j = 0; j < column_indices.size(); j++)
    {
        column_index = column_indices[j];

       if(statistics[column_index].maximum - statistics[column_index].minimum < 1e-99)
       {
          // Do nothing
       }
       else
       {
          for(unsigned i = 0; i < rows_number; i++)
          {
             data[i][column_index] = 0.5*(data[i][column_index] + 1.0)*(statistics[column_index].maximum-statistics[column_index].minimum)
             + statistics[column_index].minimum;
          }
       }
    }
}


// void unscale_rows_columns_minimum_maximum(const Vector< Statistics<Type> >&, const Vector<unsigned>&) method

/// @todo

void unscale_rows_columns_minimum_maximum(const Vector< Statistics<Type> >& statistics, const Vector<unsigned>& row_indices, const Vector<unsigned>& column_indices)
{
}


// Vector<unsigned> calculate_minimal_indices(void) const method

/// Returns the row and column indices corresponding to the entry with minimum value. 

Vector<unsigned> calculate_minimal_indices(void) const
{
   Type minimum = data[0][0];
   Vector<unsigned> minimal_indices(2, 0);

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         if(data[i][j] < minimum)
         {
            minimum = data[i][j];
            minimal_indices[0] = i;
            minimal_indices[1] = j;
		 }
      }
   }
   
   return(minimal_indices);
}


// Vector<unsigned> calculate_maximal_indices(void) const method

/// Returns the row and column indices corresponding to the entry with maximum value. 

Vector<unsigned> calculate_maximal_indices(void) const
{
   Type maximum = data[0][0];

   Vector<unsigned> maximal_indices(2, 0);

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         if(data[i][j] > maximum)
         {
            maximum = data[i][j];
            maximal_indices[0] = i;
            maximal_indices[1] = j;
		 }
      }
   }
   
   return(maximal_indices);
}


// Vector< Vector<unsigned> > calculate_minimal_maximal_indices(void) const method

/// Returns the row and column indices corresponding to the entries with minimum and maximum values. 
/// The format is a vector of two vectors.
/// Each subvector also has two elements. 
/// The first vector contains the minimal indices, and the second vector contains the maximal indices.  

Vector< Vector<unsigned> > calculate_minimal_maximal_indices(void) const
{
   Type minimum = data[0][0];
   Type maximum = data[0][0];

   Vector<unsigned> minimal_indices(2, 0);
   Vector<unsigned> maximal_indices(2, 0);

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         if(data[i][j] < minimum)
         {
            minimum = data[i][j];
            minimal_indices[0] = i;
            minimal_indices[1] = j;
		 }

         if(data[i][j] > maximum)
         {
            maximum = data[i][j];
            maximal_indices[0] = i;
            maximal_indices[1] = j;
		 }
      }
   }

   Vector< Vector<unsigned> > minimal_maximal_indices(2);
   minimal_maximal_indices[0] = minimal_indices;
   minimal_maximal_indices[1] = maximal_indices;
   
   return(minimal_maximal_indices);
}


// double calculate_sum_squared_error(const Matrix<double>&) const method

/// Returns the sum squared error between the elements of this matrix and the elements of another matrix. 
/// @param other_matrix Other matrix. 

double calculate_sum_squared_error(const Matrix<double>& other_matrix) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned other_rows_number = other_matrix.get_rows_number();

   if(other_rows_number != rows_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "double calculate_sum_squared_error(const Matrix<double>&) const method.\n"
             << "Other number of rows must be equal to this number of rows.\n";

      throw std::logic_error(buffer.str());
   }

   const unsigned other_columns_number = other_matrix.get_columns_number();

   if(other_columns_number != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "double calculate_sum_squared_error(const Matrix<double>&) const method.\n"
             << "Other number of columns must be equal to this number of columns.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   double sum_squared_error = 0.0;

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
	  {
         sum_squared_error += (data[i][j] - other_matrix[i][j])*(data[i][j] - other_matrix[i][j]);
	  }
   }

   return(sum_squared_error);
}


// double calculate_sum_squared_error(const Vector<double>&) const method

/// This method retuns the sum squared error between the elements of this matrix and the elements of a vector, by columns.
/// The size of the vector must be equal to the number of columns of this matrix.
/// @param vector Vector to be compared to this matrix. 

double calculate_sum_squared_error(const Vector<double>& vector) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned size = vector.size();

   if(size != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "double calculate_sum_squared_error(const Vector<double>&) const method.\n"
             << "Size must be equal to number of columns.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   double sum_squared_error = 0.0;

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
	  {
         sum_squared_error += (data[i][j] - vector[j])*(data[i][j] - vector[j]);
	  }
   }

   return(sum_squared_error);
}


// Vector<double> calculate_rows_norm(void) const method

/// Returns a vector with the norm of each row. 
/// The size of that vector is the number of rows. 

Vector<double> calculate_rows_norm(void) const
{
   Vector<Type> rows_norm(rows_number, 0.0);

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
	     rows_norm[i] += data[i][j]*data[i][j];
      }     

      rows_norm[i] = sqrt(rows_norm[i]);
   }

   return(rows_norm);
}


// Matrix<Type> calculate_absolute_value(void) const method

/// Returns a matrix with the absolute values of this matrix. 

Matrix<Type> calculate_absolute_value(void) const
{
   Matrix<Type> absolute_value(rows_number, columns_number);

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         if(data[i][j] > 0)
         {
	        absolute_value[i][j] = data[i][j];
	     }
	     else
         {
            absolute_value[i][j] = -data[i][j];
         }
      }     
   }

   return(absolute_value);
}



// Matrix<Type> calculate_transpose(void) const method

/// Returns the transpose of the matrix. 

Matrix<Type> calculate_transpose(void) const
{
   Matrix<Type> transpose(columns_number, rows_number);

   for(unsigned i = 0; i < columns_number; i++)
   {
      for(unsigned j = 0; j < rows_number; j++)
      {
         transpose[i][j] = data[j][i];
      }     
   }

   return(transpose);
}


// Type calculate_determinant(void) const method

/// Returns the determinant of a square matrix. 

Type calculate_determinant(void) const
{ 
   // Control sentence (if debug)

   #ifndef NDEBUG 

   if(rows_number != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "calculate_determinant(void) const method.\n"
             << "Matrix must be square.\n";
      
      throw std::logic_error(buffer.str());
   }

   #endif

   Type determinant = 0;
   
   if(rows_number == 0)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "calculate_determinant(void) const method.\n"
             << "Size of matrix is zero.\n";
      
      throw std::logic_error(buffer.str());
   }
   else if(rows_number == 1)
   {
      determinant = data[0][0];                   
   }
   else if(rows_number == 2)
   {
      determinant = data[0][0]*data[1][1] - data[1][0]*data[0][1];
   }
   else
   {
      int sign;

      for(unsigned row_index = 0; row_index < rows_number; row_index++) 
      {
         // Calculate sub data
 
         Matrix<Type> sub_matrix(rows_number-1, columns_number-1);     
     
         for(unsigned i = 1; i < rows_number; i++) 
         {
            unsigned j2 = 0;
      
            for(unsigned j = 0; j < columns_number; j++) 
            {
               if(j == row_index)
               {
                  continue;
               }

               sub_matrix[i-1][j2] = data[i][j];

               j2++;
            }
         }

         //sign = (unsigned)(pow(-1.0, row_index+2.0));
       
         sign = static_cast<int>( (((row_index + 2) % 2) == 0) ? 1 : -1 );

         determinant += sign*data[0][row_index]*sub_matrix.calculate_determinant();    
      }
   }
     
   return(determinant);
}


// Matrix<Type> calculate_cofactor(void) const method

/// Returns the cofactor matrix.

Matrix<Type> calculate_cofactor(void) const
{
   Matrix<double> cofactor(rows_number, columns_number);
                  
   Matrix<double> c(rows_number-1, columns_number-1);

   for(unsigned j = 0; j < rows_number; j++) 
   {
      for(unsigned i = 0; i < rows_number; i++) 
      {
         // Form the adjoint a[i][j]

         unsigned i1 = 0;

         for(unsigned ii = 0; ii < rows_number; ii++) 
         {
            if(ii == i)
            {
               continue;
            }
            
            unsigned j1 = 0;

            for(unsigned jj = 0; jj < rows_number; jj++) 
            {
               if(jj == j)
               {
                  continue;
               }

               c[i1][j1] = data[ii][jj];
               j1++;
            }
            i1++;
         }

         const double determinant = c.calculate_determinant();

         cofactor[i][j] = static_cast<Type>((((i + j) % 2) == 0) ? 1 : -1)*determinant;
         //cofactor[i][j] = pow(-1.0, i+j+2.0)*determinant;
      }
   }

   return(cofactor);
}


// Matrix<Type> calculate_inverse(void) const method

/// Returns the inverse of a square matrix.
/// An error message is printed if the matrix is singular.

Matrix<Type> calculate_inverse(void) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 
   
   if(rows_number != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "calculate_inverse(void) const method.\n"
             << "Matrix must be square.\n";
      
      throw std::logic_error(buffer.str());
   }

   #endif

   const double determinant = calculate_determinant();

   if(determinant == 0.0)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n"
             << "calculate_inverse(void) const method.\n"
             << "Matrix is singular.\n";
      
      throw std::logic_error(buffer.str());
   }
   
   // Calculate cofactor matrix
   
   const Matrix<double> cofactor = calculate_cofactor();

   // Adjoint matrix is the transpose of cofactor matrix

   const Matrix<double> adjoint = cofactor.calculate_transpose();
   
   // Inverse matrix is adjoint matrix divided by matrix determinant

   const Matrix<double> inverse = adjoint/determinant;

   return(inverse);
}


// Matrix<Type> operator + (const Type&) const method

/// Sum matrix+scalar arithmetic operator. 
/// @param scalar Scalar value to be added to this matrix.

inline Matrix<Type> operator + (const Type& scalar) const
{
   Matrix<Type> sum(rows_number, columns_number);

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         sum[i][j] = data[i][j] + scalar;    
      }     
   }

   return(sum);
}


// Matrix<Type> operator + (const Vector<Type>&) const method

/// Sum matrix+vector arithmetic operator. 
/// @param vector Vector to be added to this matrix.

inline Matrix<Type> operator + (const Vector<Type>& vector) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned size = vector.size();    
       
   if(size != rows_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "Matrix<Type> operator + (const Vector<Type>&) const.\n"
             << "Size of vector must be equal to number of rows.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   Matrix<Type> sum(rows_number, columns_number);

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         sum[i][j] = data[i][j] + vector[i];    
      }     
   }

   return(sum);
}


// Matrix<Type> operator + (const Matrix<Type>&) const method

/// Sum matrix+matrix arithmetic operator. 
/// @param other_matrix Matrix to be added to this vector.

inline Matrix<Type> operator + (const Matrix<Type>& other_matrix) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned other_rows_number = other_matrix.get_rows_number();    
   const unsigned other_columns_number = other_matrix.get_columns_number();    
       
   if(other_rows_number != rows_number || other_columns_number != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "Matrix<Type> operator + (const Matrix<Type>&) const.\n"
             << "Sizes of other matrix (" << other_rows_number << "," << other_columns_number << ") must be the same than sizes of this matrix (" << rows_number << "," << columns_number << ").\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   Matrix<Type> sum(rows_number, columns_number);

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         sum[i][j] = data[i][j] + other_matrix[i][j];    
      }     
   }

   return(sum);
}


// Matrix<Type> operator - (const Type&) const method

/// Difference matrix-scalar arithmetic operator. 
/// @param scalar Scalar value to be subtracted to this matrix.

inline Matrix<Type> operator - (const Type& scalar) const
{
   Matrix<Type> difference(rows_number, columns_number);

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         difference[i][j] = data[i][j] - scalar;    
      }     
   }

   return(difference);
}


// Matrix<Type> operator - (const Vector<Type>&) const method

/// Sum matrix-vector arithmetic operator. 
/// @param vector Vector to be subtracted to this matrix.

inline Matrix<Type> operator - (const Vector<Type>& vector) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned size = vector.size();    
       
   if(size != rows_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "Matrix<Type> operator - (const Vector<Type>&) const.\n"
             << "Size of vector must be equal to number of rows.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   Matrix<Type> difference(rows_number, columns_number);

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         difference[i][j] = data[i][j] - vector[i];    
      }     
   }

   return(difference);
}


// Matrix<Type> operator - (const Matrix<Type>&) const method 

/// Difference matrix-matrix arithmetic operator. 
/// @param other_matrix Matrix to be subtracted to this matrix.

inline Matrix<Type> operator - (const Matrix<Type>& other_matrix) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned other_rows_number = other_matrix.get_rows_number();    
   const unsigned other_columns_number = other_matrix.get_columns_number();    
       
   if(other_rows_number != rows_number || other_columns_number != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "Matrix<Type> operator - (const Matrix<Type>&) const method.\n"
             << "Sizes of other matrix (" << other_rows_number << "," << other_columns_number << ") must be equal to sizes of this matrix ("<< rows_number << "," << columns_number <<").\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   Matrix<Type> difference(rows_number, columns_number);

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         difference[i][j] = data[i][j] - other_matrix[i][j];    
      }     
   }

   return(difference);
}


// Matrix<Type> operator * (const Type&) const method

/// Product matrix*scalar arithmetic operator. 
/// @param scalar Scalar value to be multiplied to this matrix.

inline Matrix<Type> operator * (const Type& scalar) const
{
   Matrix<Type> product(rows_number, columns_number);

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
          product[i][j] = data[i][j]*scalar;     
      }      
   }

   return(product);
}


// Matrix<Type> operator * (const Vector<Type>&) const  method

/// Row by element matrix*row arithmetic operator. 
/// @param vector vector to be multiplied to this matrix.

inline Matrix<Type> operator * (const Vector<Type>& vector) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned size = vector.size();    
       
   if(size != rows_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "Matrix<Type> operator * (const Vector<Type>&) const method.\n"
             << "Vector size (" << size << ")  must be equal to number of matrix rows (" << rows_number << ").\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   Matrix<Type> product(rows_number, columns_number);

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         product[i][j] = data[i][j]*vector[i];    
      }     
   }

   return(product);
}


// Matrix<Type> operator * (const Matrix<Type>&) const  method

/// Product matrix*matrix arithmetic operator. 
/// @param other_matrix Matrix to be multiplied to this matrix.

inline Matrix<Type> operator * (const Matrix<Type>& other_matrix) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned other_rows_number = other_matrix.get_rows_number();    
   const unsigned other_columns_number = other_matrix.get_columns_number();    
       
   if(other_rows_number != rows_number || other_columns_number != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "Matrix<Type> operator * (const Matrix<Type>&) const method.\n"
             << "Sizes of other matrix (" << other_rows_number << "," << other_columns_number << ") must be equal to sizes of this matrix (" << rows_number << "," << columns_number << ").\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   Matrix<Type> product(rows_number, columns_number);

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         product[i][j] = data[i][j]*other_matrix[i][j];    
      }     
   }

   return(product);
}


// Matrix<Type> operator / (const Type&) const method

/// Cocient Matrix/scalar arithmetic operator. 
/// @param scalar Value of scalar. 

inline Matrix<Type> operator / (const Type& scalar) const
{
   Matrix<Type> cocient(rows_number, columns_number);

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         cocient[i][j] = data[i][j]/scalar;     
      }      
   }

   return(cocient);
}


// Matrix<Type> operator / (const Vector<Type>&) const method

/// Cocient matrix/vector arithmetic operator. 
/// @param vector Vector to be divided to this matrix.

inline Matrix<Type> operator / (const Vector<Type>& vector) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned size = vector.size();    
       
   if(size != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "Matrix<Type> operator / (const Vector<Type>&) const.\n"
             << "Size of vector must be equal to number of columns.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   Matrix<Type> cocient(rows_number, columns_number);

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         cocient[i][j] = data[i][j]/vector[j];    
      }     
   }

   return(cocient);
}


// Matrix<Type> operator / (const Matrix<Type>&) const  method

/// Cocient matrix/matrix arithmetic operator. 
/// @param other_matrix Matrix to be divided to this vector.

inline Matrix<Type> operator / (const Matrix<Type>& other_matrix) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned other_rows_number = other_matrix.get_rows_number();    
   const unsigned other_columns_number = other_matrix.get_columns_number();    
       
   if(other_rows_number != rows_number || other_columns_number != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "Matrix<Type> operator / (const Matrix<Type>&) const method.\n"
             << "Both matrix sizes must be the same.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   Matrix<Type> cocient(rows_number, columns_number);

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         cocient[i][j] = data[i][j]/other_matrix[i][j];    
      }     
   }

   return(cocient);
}


// void operator += (const Type&)

/// Scalar sum and assignment operator.
/// @param value Scalar value to be added to this matrix.

inline void operator += (const Type& value) 
{         
   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         data[i][j] += value;
      }
   }
}


// void operator += (const Matrix<Type>&)

/// Matrix sum and assignment operator.
/// @param other_matrix Matrix to be added to this matrix.

inline void operator += (const Matrix<Type>& other_matrix)
{       
   // Control sentence (if debug)            

   #ifndef NDEBUG 

   const unsigned other_rows_number = other_matrix.get_rows_number();

   if(other_rows_number != rows_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "void operator += (const Matrix<Type>&).\n"
             << "Both numbers of rows must be the same.\n";

      throw std::logic_error(buffer.str());
   }

   const unsigned other_columns_number = other_matrix.get_columns_number();

   if(other_columns_number != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "void operator += (const Matrix<Type>&).\n"
             << "Both numbers of columns must be the same.\n";

      throw std::logic_error(buffer.str());
   }

   #endif
  
   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         data[i][j] += other_matrix[i][j];
	  }
   }
}


// void operator -= (const Type&)

/// Scalar rest and assignment operator.
/// @param value Scalar value to be subtracted to this matrix.

inline void operator -= (const Type& value)
{         
   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         data[i][j] -= value;
	  }
   }
}


// void operator -= (const Matrix<Type>&)

/// Matrix rest and assignment operator.
/// @param other_matrix Matrix to be subtracted to this matrix.

inline void operator -= (const Matrix<Type>& other_matrix)
{       
   // Control sentence (if debug)            

   #ifndef NDEBUG 

   const unsigned other_rows_number = other_matrix.get_rows_number();

   if(other_rows_number != rows_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "void operator -= (const Matrix<Type>&).\n"
             << "Both numbers of rows must be the same.\n";

      throw std::logic_error(buffer.str());
   }

   const unsigned other_columns_number = other_matrix.get_columns_number();

   if(other_columns_number != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "void operator -= (const Matrix<Type>&).\n"
             << "Both numbers of columns must be the same.\n";

      throw std::logic_error(buffer.str());
   }

   #endif
  
   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         data[i][j] -= other_matrix[i][j];
      }
   }
}


// void operator *= (const Type&)

/// Scalar product and assignment operator.
/// @param value Scalar value to be multiplied to this matrix.

inline void operator *= (const Type& value)
{         
   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         data[i][j] *= value;
	  }
   }
}


// void operator *= (const Matrix<Type>&) 

/// Matrix product and assignment operator.
/// @param other_matrix Matrix to be multiplied to this matrix.

inline void operator *= (const Matrix<Type>& other_matrix)
{       
   // Control sentence (if debug)            

   #ifndef NDEBUG 

   const unsigned other_rows_number = other_matrix.get_rows_number();

   const unsigned rows_number = this->get_rows_number();

   if(other_rows_number != rows_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "void operator *= (const Matrix<Type>&).\n"
             << "The number of rows in the other matrix (" << other_rows_number << ")"
             << " is not equal to the number of rows in this matrix (" << rows_number << ").\n";

      throw std::logic_error(buffer.str());
   }

   #endif
  
   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         data[i][j] *= other_matrix[i][j];
      }
   }
}


// void operator /= (const Type&) 

/// Scalar division and assignment operator.
/// @param value Scalar value to be divided to this matrix.

inline void operator /= (const Type& value)
{         
   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         data[i][j] /= value;
	  }
   }
}


// void operator /= (const Matrix<Type>&)

/// Matrix division and assignment operator.
/// @param other_matrix Matrix to be divided to this matrix.

inline void operator /= (const Matrix<Type>& other_matrix)
{       
   // Control sentence (if debug)            

   #ifndef NDEBUG 

   const unsigned other_rows_number = other_matrix.get_rows_number();

   if(other_rows_number != rows_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "void operator /= (const Matrix<Type>&).\n"
             << "Both numbers of rows must be the same.\n";

      throw std::logic_error(buffer.str());
   }

   const unsigned other_columns_number = other_matrix.get_columns_number();

   if(other_columns_number != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "void operator /= (const Matrix<Type>&).\n"
             << "Both numbers of columns must be the same.\n";

      throw std::logic_error(buffer.str());
   }

   #endif
  
   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         data[i][j] /= other_matrix[i][j];
      }
   }
}


// Vector<Type> dot(const Vector<Type>&) const method

/// Returns the dot product of this matrix with a vector.
/// The size of the vector must be equal to the number of columns of the matrix.
/// @param vector Vector to be multiplied to this matrix.

Vector<Type> dot(const Vector<Type>& vector) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 
       
   const unsigned size = vector.size();

   if(size != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "Vector<Type> dot(const Vector<Type>&) const method.\n"
             << "Vector size must be equal to matrix number of columns.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   // Calculate matrix-vector poduct   
      
   Vector<Type> product(rows_number);

   for(unsigned i = 0; i < rows_number; i++)
   {     
      product[i] = 0;      

      for(unsigned j = 0; j < columns_number; j++)
      {
         product[i] += vector[j]*data[i][j];
      }
   }

   return(product);
}


// Matrix<Type> dot(const Matrix<Type>&) const method

/// Returns the dot product of this matrix with another matrix. 
///
/// @param other_matrix Matrix to be multiplied to this matrix.

Matrix<Type> dot(const Matrix<Type>& other_matrix) const
{
   const unsigned other_columns_number = other_matrix.get_columns_number();

   // Control sentence (if debug)

   #ifndef NDEBUG 
       
   const unsigned other_rows_number = other_matrix.get_rows_number();

   if(other_rows_number != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "Matrix<Type> dot(const Matrix<Type>&) const method.\n"
             << "The number of rows of the other matrix (" << other_rows_number << ") must be equal to the number of columns of this matrix (" << columns_number << ").\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   Matrix<Type> product(rows_number, other_columns_number, 0.0);

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < other_columns_number; j++)
      { 
         for(unsigned k = 0; k < columns_number; k++)
         {
             product[i][j] += data[i][k]*other_matrix[k][j];
         }
      }
   }

   return(product);
}


// Matrix<Type> direct(const Matrix<Type>&) const method 

/// Calculates the direct product of this matrix with another matrix. 
/// This product is also known as the Kronecker product. 
/// @param other_matrix Second product term. 
/// @todo

Matrix<Type> direct(const Matrix<Type>& other_matrix) const
{
   const unsigned other_rows_number = other_matrix.get_rows_number();   
   const unsigned other_columns_number = other_matrix.get_columns_number();   

   const Matrix<Type> direct(rows_number*other_rows_number, columns_number*other_columns_number);

   return(direct);
}

// bool empty(void) const method

/// Returns true if number of rows and columns is zero.

bool empty(void) const
{
   if(rows_number == 0 && columns_number == 0)
   {
      return(true);
   }
   else
   {
      return(false);
   }

}


// bool is_square(void) const method

/// Returns true if this matrix is square.
/// A square matrix has the same numbers of rows and columns.

bool is_square(void) const
{
   if(rows_number == columns_number)
   {
      return(true);
   }
   else
   {
      return(false);
   }

}


// bool is_symmetric(void) const method

/// Returns true if this matrix is symmetric.
/// A symmetric matrix is a squared matrix which is equal to its transpose.

bool is_symmetric(void) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 
       
   if(rows_number != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "bool is_symmetric(void) const method.\n"
             << "Matrix must be squared.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   const Matrix<Type> transpose = calculate_transpose();

   if((*this) == transpose)
   {
       return(true);
   }
   else
   {
       return(false);
   }
}


// bool is_antisymmetric(void) const method

/// Returns true if this matrix is antysymmetric.
/// A symmetric matrix is a squared matrix which its opposed is equal to its transpose.

bool is_antisymmetric(void) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 
       
   if(rows_number != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "bool is_antisymmetric(void) const method.\n"
             << "Matrix must be squared.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   const Matrix<Type> transpose = calculate_transpose();

   if((*this) == transpose*(-1))
   {
       return(true);
   }
   else
   {
       return(false);
   }
}


// bool is_diagonal(void) const method

/// Returns true if this matrix is diagonal.
/// A diagonal matrix is which the entries outside the main diagonal are zero.

bool is_diagonal(void) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 
       
   if(rows_number != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "bool is_diagonal(void) const method.\n"
             << "Matrix must be squared.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         if(i != j && data[i][j] != 0)
         {
            return(false);
         }
      }
   }

   return(true);
}


// bool is_scalar(void) const method

/// Returns true if this matrix is scalar.
/// A scalar matrix is a diagonal matrix whose diagonal elements all contain the same scalar. 

bool is_scalar(void) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 
       
   if(rows_number != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "bool is_scalar(void) const method.\n"
             << "Matrix must be squared.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   // To do

   return(false);
}


/// Returns true if this matrix is the identity.
/// The identity matrix or unit matrix is a square matrix with ones on the main diagonal and zeros elsewhere.

bool is_identity(void) const
{
   // Control sentence (if debug)
       
   #ifndef NDEBUG 

   if(rows_number != columns_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix Template.\n" 
             << "bool is_unity(void) const method.\n"
             << "Matrix must be squared.\n";

      throw std::logic_error(buffer.str());
   }

   #endif

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         if(i != j && data[i][j] != 0)
         {
            return(false);
         }
         else if(i == j && data[i][j] != 1)
         {
            return(false);
         } 
      }
   }

   return(true);
}


// void print(void) const method

/// Prints to the screen in the matrix object. 

void print(void) const
{
   std::cout << *this;
}


// void load(const std::string&) method

/// Loads the numbers of rows and columns and the values of the matrix from a data file. 
///
/// @param file_name File name.

void load(const std::string& file_name)
{
   std::ifstream file(file_name.c_str());
  
   if(!file.is_open())
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix template.\n"
             << "void load(const std::string&) method.\n"
             << "Cannot open matrix data file: " << file_name << "\n";

      throw std::logic_error(buffer.str());
   }

   // Set matrix sizes

   std::string line;

   std::getline(file, line);

   if(line.empty())
   {
      set();
   }
   else
   {
      std::istringstream buffer(line);

      std::istream_iterator<std::string> it(buffer); 
      std::istream_iterator<std::string> end; 

      const std::vector<std::string> results(it, end); 

      const unsigned new_columns_number = results.size();

      unsigned new_rows_number = 1;

      while(file.good()) 
      { 
         getline(file, line);

         if(!line.empty()) 
         {
            new_rows_number++;      
         }
      }

      set(new_rows_number, new_columns_number);

      // Clear file 

      file.clear(); 
      file.seekg(0, std::ios::beg); 

      for(unsigned i = 0; i < rows_number; i++)
      {
         for(unsigned j = 0; j < columns_number; j++)
         {
            file >> data[i][j];
         }     
      }
   }   

   // Close file

   file.close();
}


// void save(const std::string&) const method

/// Saves the numbers of rows and columns and the values of the matrix to a data file. 
/// @param file_name File name.

void save(const std::string& file_name) const
{
   std::ofstream file(file_name.c_str());
    
   if(!file.is_open())
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Matrix template." << std::endl
             << "void save(const std::string) method." << std::endl
             << "Cannot open matrix data file." << std::endl;

	  throw std::logic_error(buffer.str());
   }
 
   // Write file
 
   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         file << data[i][j] << " ";
      }     

      file << std::endl;
   }
 
   // Close file
 
   file.close();
}


// void parse(const std::string&) method

/// This method takes a string representation of a matrix and sets this matrix
/// from that data.
/// @param str String to be parsed.

void parse(const std::string& str)
{
   if(str.empty())
   {
       set();
   }
   else
   {
       // Set matrix sizes

       std::istringstream str_buffer(str);

       std::string line;

       std::getline(str_buffer, line);

      std::istringstream line_buffer(line);

      std::istream_iterator<std::string> it(line_buffer);
      std::istream_iterator<std::string> end;

      const std::vector<std::string> results(it, end);

      const unsigned new_columns_number = results.size();

      unsigned new_rows_number = 1;

      while(str_buffer.good())
      {
         getline(str_buffer, line);

         if(!line.empty())
         {
            new_rows_number++;
         }
      }

      set(new_rows_number, new_columns_number);

      // Clear file

      str_buffer.clear();
      str_buffer.seekg(0, std::ios::beg);

      for(unsigned i = 0; i < rows_number; i++)
      {
         for(unsigned j = 0; j < columns_number; j++)
         {
            str_buffer >> data[i][j];
         }
      }
   }
}


// Matrix<bool> to_boolean(void) const method

/// Returns a matrix of boolean values.
/// If the elements of this matrix are less than 0.5 the boolean elements will be false.
/// If the elements of this matrix are greater than 0.5 the boolean elements will be true.

Matrix<bool> to_boolean(void) const
{
   Matrix<bool> boolean(rows_number, columns_number, false);

   for(unsigned i = 0; i < rows_number; i++)
   {
       for(unsigned j = 0; j < columns_number; j++)
       {
           if(data[i][j] > 0.5)
           {
               boolean[i][j] = true;
           }
       }
    }

   return(boolean);
}


// std::string to_string(const std::string&) const method

/// Returns a string representation of this matrix. 
/// The elements are separated by spaces. 
/// The rows are separated by the character "\n".

std::string to_string(const std::string& separator = " ") const
{
   std::ostringstream buffer;
   
   if(rows_number > 0 && columns_number > 0)
   {
       buffer << arrange_row(0).to_string(separator);

       for(unsigned i = 1; i < rows_number; i++)
       {
           buffer << "\n"
                  << arrange_row(i).to_string(separator);
       }
   }

   return(buffer.str());
}


// Matrix<std::string> write_string_matrix(const unsigned&) const

/// Returns a new matrix in which each entry has been converted to a string. 

Matrix<std::string> write_string_matrix(const unsigned precision = 3) const
{
   Matrix<std::string> string_matrix(rows_number, columns_number);

   std::ostringstream buffer;

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         buffer.str("");
         buffer << std::setprecision(precision) << (*this)[i][j];
   
         string_matrix[i][j] = buffer.str();
      }
   }

   return(string_matrix);
}


// Vector<Type> to_vector(void) const

/// Returns a vector representation of this matrix.
/// The size of the new vector is equal to the number of elements of this matrix. 
/// The entries of the new vector are the entries of this matrix ordered by rows. 

Vector<Type> to_vector(void) const
{
   Vector<Type> vector(rows_number*columns_number);

   unsigned index = 0;

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         vector[index] = data[i][j];
         index++;
      }
   }

   return(vector);
}


private:

/// Number of rows in the matrix.

unsigned rows_number;

/// Number of columns in the matrix.

unsigned columns_number;

/// Double pointer to a Type.

Type** data;

};



/// This method re-writes the input operator >> for the Matrix template.
/// @param is Input stream.
/// @param m Input matrix.

template<typename Type>
std::istream& operator >> (std::istream& is, Matrix<Type>& m)
{
   const unsigned rows_number = m.get_rows_number();
   const unsigned columns_number = m.get_columns_number();

   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         is >> m[i][j];
      }     
   }

   return(is);
}


// Output operator

/// This method re-writes the output operator << for the Matrix template.
/// @param os Output stream.
/// @param m Output matrix.

template<typename Type>
std::ostream& operator << (std::ostream& os, const Matrix<Type>& m)
{
   const unsigned rows_number = m.get_rows_number();
   const unsigned columns_number = m.get_columns_number();

   if(rows_number > 0 && columns_number > 0)
   {
       os << m.arrange_row(0);

       for(unsigned i = 1; i < rows_number; i++)
       {
           os << "\n"
              << m.arrange_row(i);
       }
   }

   return(os);
}


// Output operator

/// This method re-writes the output operator << for matrices of vectors.
/// @param os Output stream.
/// @param m Output matrix of vectors.

template<typename Type>
std::ostream& operator << (std::ostream& os, const Matrix< Vector<Type> >& m)
{
   const unsigned rows_number = m.get_rows_number();
   const unsigned columns_number = m.get_columns_number();
   
   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         os << "subvector_" << i << "_" << j << "\n"  
            << m[i][j] << std::endl;
      }     
   }

   return(os);
}


// Output operator

/// This method re-writes the output operator << for matrices of matrices.
/// @param os Output stream.
/// @param m Output matrix of matrices.

template<typename Type>
std::ostream& operator << (std::ostream& os, const Matrix< Matrix<Type> >& m)
{
   const unsigned rows_number = m.get_rows_number();
   const unsigned columns_number = m.get_columns_number();
   
   for(unsigned i = 0; i < rows_number; i++)
   {
      for(unsigned j = 0; j < columns_number; j++)
      {
         os << "submatrix_" << i << "_" << j << "\n"  
            << m[i][j];
      }     
   }

   return(os);
}

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

