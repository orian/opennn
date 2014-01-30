/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   L I N E A R   A L G E B R A I C   E Q U A T I O N S   C L A S S                                            */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */ 
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// OpenNN includes

#include "linear_algebraic_equations.h"

namespace OpenNN
{

// GENERAL CONSTRUCTOR

/// General constructor.

LinearAlgebraicEquations::LinearAlgebraicEquations(void)
{	

}


// DESTRUCTOR

/// Destructor.

LinearAlgebraicEquations::~LinearAlgebraicEquations(void)
{

}


// ASSIGNMENT OPERATOR

// LinearAlgebraicEquations& operator = (const LinearAlgebraicEquations&) method

/// Assignment operator. 
/// Assigns the members of another object to this object.

LinearAlgebraicEquations& LinearAlgebraicEquations::operator = (const LinearAlgebraicEquations&)
{
   return(*this);
}


// EQUAL TO OPERATOR

// bool operator == (const LinearAlgebraicEquations&) const method

/// Equal to operator. 
/// Compares this object with anothe object.
/// It returns true if both objects are equal and false otherwise. 

bool LinearAlgebraicEquations::operator == (const LinearAlgebraicEquations&) const
{
   return(true);
}


// METHODS


// static Matrix<double> perform_Gauss_Jordan_elimination(Matrix<double>&, Matrix<double>&) method

/// Performs a linear equation solution by Gauss-Jordan eliminiation with full pivoting. 
/// On outputs, a is replaced by its matrix inverse, and b is replaced by the
/// corresponding set of solution vectors.
/// @param a Input matrix.
/// @param b Input containing a set of right-hand side vectors.

void LinearAlgebraicEquations::perform_Gauss_Jordan_elimination(Matrix<double>& a, Matrix<double>& b)
{
   unsigned icol = 0;
   unsigned irow = 0;

   double big = 0.0;
   double dum = 0.0;
   double pivinv = 0.0;

   const unsigned n = a.get_rows_number(); // Number of equations
   const unsigned m = b.get_columns_number(); // Number of right hand side vectors
	
   Vector<unsigned> column_index(n, 0);
   Vector<unsigned> row_index(n, 0);
   Vector<unsigned> pivoting_index(n, 0);

   // Main loop over the colums to be reduced

   for(unsigned i = 0; i < n; i++) 
   {
      big = 0.0;

      // Outer loop of the search for a pivot element

      for(unsigned j = 0; j < n; j++)
      {
         if(pivoting_index[j] != 1)
         {
            for(unsigned k = 0; k < n; k++) 
            {
               if(pivoting_index[k] == 0) 
               {
                  if(fabs(a[j][k]) >= big) 
                  {
                     big = fabs(a[j][k]);
                     irow = j;
                     icol = k;
                  }
               }
            }
         }
      }

      ++(pivoting_index[icol]);

      if(irow != icol) 
      {
         for(unsigned l = 0; l < n; l++)
         {
            swap(a[irow][l],a[icol][l]);
         }

         for(unsigned l = 0; l < m; l++) 
         {
            swap(b[irow][l],b[icol][l]);
         }
      }

      row_index[i] = irow;
      column_index[i] = icol;

      // Divide the povot row by the pivot element

      if (a[icol][icol] == 0.0)
      {
         std::ostringstream buffer;

         buffer << "OpenNN Exception: LinearAlgebraicEquations class. "
                << "perform_Gauss_Jordan_elimination(Matrix<double>&, Matrix<double>&) method.\n"
                << "Matrix A is singular\n";

          throw std::logic_error(buffer.str());	      
      }

      pivinv = 1.0/a[icol][icol];

      a[icol][icol] = 1.0;
		
      for(unsigned l = 0; l < n; l++) 
      {
         a[icol][l] *= pivinv;
      }

      for(unsigned l = 0; l < m; l++) 
      {
         b[icol][l] *= pivinv;
      }

      for(unsigned ll = 0; ll < n; ll++)
      {
         if(ll != icol) 
         {
	        dum=a[ll][icol];

     	    a[ll][icol] = 0.0;

            for(unsigned l = 0; l < n; l++) 
      	    { 
               a[ll][l] -= a[icol][l]*dum;
     	    }

            for(unsigned l = 0; l < m; l++) 
            {
               b[ll][l] -= b[icol][l]*dum;
	        }		
	     }
      }
   }

   // Loop

   for(int l = n-1; l >= 0; l--) 
   {
      if(row_index[l] != column_index[l])
      {
         for(unsigned k = 0; k < n; k++)
         {
            swap(a[k][row_index[l]], a[k][column_index[l]]);
         }
      }
   }
}


// static void perform_Gauss_Jordan_elimination(Matrix<double>& a, Vector<double>& b) method

/// Performs a linear equation solution by Gauss-Jordan eliminiation with full pivoting. 
/// On output, a is replaced by its matrix inverse, and b is replaced by the corresponding solution vector.
/// @param a A matrix.
/// @param b b vector.

void LinearAlgebraicEquations::perform_Gauss_Jordan_elimination(Matrix<double>& a, Vector<double>& b)
{
   unsigned icol = 0;
   unsigned irow = 0;

   double big = 0.0;
   double dum = 0.0;
   double pivinv = 0.0;

   const unsigned n = a.get_rows_number(); // Number of equations
	
   Vector<unsigned> column_index(n, 0);
   Vector<unsigned> row_index(n, 0);
   Vector<unsigned> pivoting_index(n, 0);

   // Main loop over the colums to be reduced

   for(unsigned i = 0; i < n; i++) 
   {
      big = 0.0;

      // Outer loop of the search for a pivot element

      for(unsigned j = 0; j < n; j++)
      {
         if(pivoting_index[j] != 1)
         {
            for(unsigned k = 0; k < n; k++) 
            {
               if(pivoting_index[k] == 0) 
               {
                  if(fabs(a[j][k]) >= big) 
                  {
                     big = fabs(a[j][k]);
                     irow = j;
                     icol = k;
                  }
               }
            }
         }
      }

      ++(pivoting_index[icol]);

      if(irow != icol) 
      {
         for(unsigned l = 0; l < n; l++)
         {
            swap(a[irow][l],a[icol][l]);
         }

         swap(b[irow],b[icol]);
      }

      row_index[i] = irow;
      column_index[i] = icol;

      // Divide the povot row by the pivot element

      if (a[icol][icol] == 0.0)
      {
         std::ostringstream buffer;

         buffer << "OpenNN Exception: LinearAlgebraicEquations class. "
                << "perform_Gauss_Jordan_elimination(const Matrix<double>&, const Matrix<double>&) method.\n"
                << "Matrix A is singular\n";

         throw std::logic_error(buffer.str());
      }

      pivinv = 1.0/a[icol][icol];

      a[icol][icol] = 1.0;
		
      for(unsigned l = 0; l < n; l++) 
      {
         a[icol][l] *= pivinv;
      }

      b[icol] *= pivinv;

      for(unsigned ll = 0; ll < n; ll++)
      {
         if(ll != icol) 
         {
	        dum=a[ll][icol];

     	    a[ll][icol] = 0.0;

            for(unsigned l = 0; l < n; l++) 
      	    { 
               a[ll][l] -= a[icol][l]*dum;
     	    }

            b[ll] -= b[icol]*dum;
	     }
      }
   }

   // Loop

   for(int l = n-1; l >= 0; l--) 
   {
      if(row_index[l] != column_index[l])
      {
         for(unsigned k = 0; k < n; k++)
         {
            swap(a[k][row_index[l]], a[k][column_index[l]]);
         }
      }
   }
}


// static Vector<double> calculate_Gauss_Jordan_solution(Matrix<double>, Vector<double>) method

/// Returns the solution vector x to the linear equation Ax = b, using the Gauss-Jordan elimination method. 
/// @param a A matrix. 
/// @param b b vector. 

Vector<double> LinearAlgebraicEquations::calculate_Gauss_Jordan_solution(Matrix<double> a, const Vector<double>& b)
{  
   const unsigned n = a.get_rows_number();

   Matrix<double> b_matrix(n, 1);
  
   b_matrix.set_column(0, b);

   perform_Gauss_Jordan_elimination(a, b_matrix);

   return(b_matrix.arrange_column(0));
}


// static void swap(double&, double&) const method

/// Swaps to real numbers a and b, so that they become a=b and b=a.
/// @param a First real number.
/// @param b Second real number.

void LinearAlgebraicEquations::swap(double& a, double& b)
{
   double temp = a;
   a = b;
   b = temp;
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
