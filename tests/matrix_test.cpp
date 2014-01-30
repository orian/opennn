/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   M A T R I X   T E S T   C L A S S                                                                          */
/*                                                                                                              */ 
/*   Roberto Lopez                                                                                              */ 
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// Unit testing includes

#include "matrix_test.h"

// GENERAL CONSTRUCTOR

MatrixTest::MatrixTest(void) : UnitTesting() 
{   
}


// DESTRUCTOR

MatrixTest::~MatrixTest(void)
{
}


// METHODS

void MatrixTest::test_constructor(void)
{
   message += "test_constructor\n";

   std::string file_name = "../data/matrix.dat";

   // Default

   Matrix<bool> m1;

   assert_true(m1.get_rows_number() == 0, LOG);
   assert_true(m1.get_columns_number() == 0, LOG);

   // Rows and columns numbers

   Matrix<bool> m2(0, 0);

   assert_true(m2.get_rows_number() == 0, LOG);
   assert_true(m2.get_columns_number() == 0, LOG);
  
   Matrix<double> m3(1, 1, 1.0);
   assert_true(m3.get_rows_number() == 1, LOG);
   assert_true(m3.get_columns_number() == 1, LOG);

   // Rows and columns numbers and initialization

   Matrix<bool> m4(0, 0, true);

   assert_true(m4.get_rows_number() == 0, LOG);
   assert_true(m4.get_columns_number() == 0, LOG);

   Matrix<bool> m5(1, 1, true);

   assert_true(m5.get_rows_number() == 1, LOG);
   assert_true(m5.get_columns_number() == 1, LOG);
   assert_true(m5 == true, LOG);

   // File constructor

   m1.save(file_name);

   Matrix<bool> m6(file_name);
   assert_true(m6.get_rows_number() == 0, LOG);
   assert_true(m6.get_columns_number() == 0, LOG);

   m2.save(file_name);
   Matrix<bool> m7(file_name);
   assert_true(m7.get_rows_number() == 0, LOG);
   assert_true(m7.get_columns_number() == 0, LOG);

   m3.save(file_name);

   Matrix<double> m8(file_name);
   assert_true(m8.get_rows_number() == 1, LOG);
   assert_true(m8.get_columns_number() == 1, LOG);

   m4.save(file_name);
   Matrix<bool> m9(file_name);
   assert_true(m9.get_rows_number() == 0, LOG);
   assert_true(m9.get_columns_number() == 0, LOG);

   m5.save(file_name);

   Matrix<bool> m10(file_name);
   assert_true(m10.get_rows_number() == 1, LOG);
   assert_true(m10.get_columns_number() == 1, LOG);
   assert_true(m10 == true, LOG); 

   // Copy constructor

   Matrix<double> a5;
   Matrix<double> b5(a5);

   assert_true(b5.get_rows_number() == 0, LOG);
   assert_true(b5.get_columns_number() == 0, LOG);

   Matrix<bool> a6(1, 1, true);

   Matrix<bool> b6(a6);

   assert_true(b6.get_rows_number() == 1, LOG);
   assert_true(b6.get_columns_number() == 1, LOG);
   assert_true(b6 == true, LOG);

   // Operator ++

   Matrix<unsigned> m11(2, 2, 0);
   m11[0][0]++;
   m11[1][1]++;

   assert_true(m11[0][0] == 1, LOG);
   assert_true(m11[0][1] == 0, LOG);
   assert_true(m11[1][0] == 0, LOG);
   assert_true(m11[1][1] == 1, LOG);

}


void MatrixTest::test_destructor(void)
{  
   message += "test_destructor\n";
}


void MatrixTest::test_assignment_operator(void)
{
   message += "test_assignment_operator\n";

   Matrix<int> a(1, 1, 0);

   Matrix<int> b = a;

   for(unsigned int i = 0; i < 2; i++)
   {
      b = a;
   }

   assert_true(b.get_rows_number() == 1, LOG);
   assert_true(b.get_columns_number() == 1, LOG);
   assert_true(b == 0, LOG);
}


void MatrixTest::test_reference_operator(void)
{
   message += "test_reference_operator\n";
}


void MatrixTest::test_sum_operator(void)
{
   message += "test_sum_operator\n";

   Matrix<int> a(1, 1, 1);
   Matrix<int> b(1, 1, 1);
   Matrix<int> c(1, 1);
   
   c = a + 1;

   for(unsigned int i = 0; i < 2; i++)
   {
      c = a + 1;
   }  

   assert_true(c.get_rows_number() == 1, LOG);
   assert_true(c.get_columns_number() == 1, LOG);
   assert_true(c == 2, LOG);

   c = a + b;

   assert_true(c.get_rows_number() == 1, LOG);
   assert_true(c.get_columns_number() == 1, LOG);
   assert_true(c == 2, LOG);
}


void MatrixTest::test_rest_operator(void)
{
   message += "test_rest_operator\n";

   Matrix<int> a(1, 1, 1);
   Matrix<int> b(1, 1, 1);
   Matrix<int> c(1, 1);
   
   c = a - 1;

   assert_true(c.get_rows_number() == 1, LOG);
   assert_true(c.get_columns_number() == 1, LOG);
   assert_true(c == 0, LOG);

   c = a - b;

   assert_true(c.get_rows_number() == 1, LOG);
   assert_true(c.get_columns_number() == 1, LOG);
   assert_true(c == 0, LOG);
}


void MatrixTest::test_multiplication_operator(void)
{
   message += "test_multiplication_operator\n";

   Matrix<int> a;
   Matrix<int> b;
   Matrix<int> c;
   
   Vector<int> v;

   // Scalar

   a.set(1, 1, 2);

   c = a*2;

   assert_true(c.get_rows_number() == 1, LOG);
   assert_true(c.get_columns_number() == 1, LOG);
   assert_true(c == 4, LOG);

   // Vector

   a.set(1, 1, 1);
   v.set(1, 1);
  
   b = a*v;

   assert_true(b.get_rows_number() == 1, LOG);
   assert_true(b.get_columns_number() == 1, LOG);
   assert_true(b == 1, LOG);  

   // Matrix

   a.set(1, 1, 2);
   b.set(1, 1, 2);

   c = a*b;

   assert_true(c.get_rows_number() == 1, LOG);
   assert_true(c.get_columns_number() == 1, LOG);
   assert_true(c == 4, LOG);

}


void MatrixTest::test_division_operator(void)
{
   message += "test_division_operator\n";

   Matrix<int> a(1, 1, 2);
   Matrix<int> b(1, 1, 2);
   Matrix<int> c(1, 1);
   
   c = a/2;

   assert_true(c.get_rows_number() == 1, LOG);
   assert_true(c.get_columns_number() == 1, LOG);
   assert_true(c == 1, LOG);

   c = a/b;

   assert_true(c.get_rows_number() == 1, LOG);
   assert_true(c.get_columns_number() == 1, LOG);
   assert_true(c == 1, LOG);
}


void MatrixTest::test_sum_assignment_operator(void)
{
   message += "test_sum_assignment_operator\n";
}


void MatrixTest::test_rest_assignment_operator(void)
{
   message += "test_rest_assignment_operator\n";
}


void MatrixTest::test_multiplication_assignment_operator(void)
{
   message += "test_multiplication_assignment_operator\n";
}


void MatrixTest::test_division_assignment_operator(void)
{
   message += "test_division_assignment_operator\n";
}


void MatrixTest::test_equal_to_operator(void)
{
	message += "test_equal_to_operator\n";

   Matrix<int> a(1,1,0);
   Matrix<int> b(1,1,0);
   Matrix<int> c(1,1,1);

   assert_true(a == b, LOG);
   assert_false(a == c, LOG);
}


void MatrixTest::test_not_equal_to_operator(void)
{
   message += "test_not_equal_to_operator\n";

   Matrix<int> a(1,1,0);
   Matrix<int> b(1,1,0);
   Matrix<int> c(1,1,1);

   assert_false(a != b, LOG);
   assert_true(a != c, LOG);
}


void MatrixTest::test_greater_than_operator(void)
{
   message += "test_greater_than_operator\n";

   Matrix<double> a(1,1,1.0);
   Matrix<double> b(1,1,0.0);

   assert_true(a > 0.0, LOG);
   assert_true(a > b, LOG);
}


void MatrixTest::test_less_than_operator(void)
{
   message += "test_less_than_operator\n";

   Matrix<double> a(1,1,0.0);
   Matrix<double> b(1,1,1.0);

   assert_true(a < 1.0, LOG);
   assert_true(a < b, LOG);
}


void MatrixTest::test_greater_than_or_equal_to_operator(void)
{
   message += "test_greater_than_or_equal_to_operator\n";

   Matrix<double> a(1,1,1.0);
   Matrix<double> b(1,1,1.0);

   assert_true(a >= 1.0, LOG);
   assert_true(a >= b, LOG);
}


void MatrixTest::test_less_than_or_equal_to_operator(void)
{
   message += "test_less_than_or_equal_to_operator\n";

   Matrix<double> a(1,1,1.0);
   Matrix<double> b(1,1,1.0);

   assert_true(a <= 1.0, LOG);
   assert_true(a <= b, LOG);
}


void MatrixTest::test_output_operator(void)
{
   message += "test_output_operator\n";

   Matrix<double> m1;
   Matrix< Vector<double> > m2;
   Matrix< Matrix<bool> > m3;

   // Test

   m1.set(2, 3, 0.0);

   // Test

   m2.set(2, 2);
   m2[0][0].set(1, 0.0);
   m2[0][1].set(1, 1.0);
   m2[1][0].set(1, 0.0);
   m2[1][1].set(1, 1.0);

   // Test

   m3.set(2, 2);
   m3[0][0].set(1, 1, 0.0);
   m3[0][1].set(1, 1, 1.0);
   m3[1][0].set(1, 1, 0.0);
   m3[1][1].set(1, 1, 1.0);
}


void MatrixTest::test_get_rows_number(void)
{
   message += "test_get_rows_number\n";

   Matrix<bool> m(2,3);

   unsigned int rows_number = m.get_rows_number();

   assert_true(rows_number == 2, LOG);
}


void MatrixTest::test_get_columns_number(void)  
{
   message += "test_get_columns_number\n";

   Matrix<bool> m(2,3);

   unsigned int columns_number = m.get_columns_number();

   assert_true(columns_number == 3, LOG);
}


void MatrixTest::test_arrange_row(void)
{
   message += "test_arrange_row\n";

   Matrix<int> m(1, 1, 0);

   Vector<int> row = m.arrange_row(0);

   assert_true(row == 0, LOG);
}


void MatrixTest::test_arrange_column(void)
{
   message += "test_arrange_column\n";

   Matrix<int> m(1, 1, 0);

   Vector<int> column = m.arrange_column(0);

   assert_true(column == 0, LOG);
}


void MatrixTest::test_arrange_submatrix(void)
{
   message += "test_arrange_submatrix\n";
}


void MatrixTest::test_set(void)
{
   message += "test_set\n";

   std::string file_name = "../data/matrix.dat";

   Matrix<double> m;

   // Default

   m.set();

   assert_true(m.get_rows_number() == 0, LOG);
   assert_true(m.get_columns_number() == 0, LOG);

   // Numbers of rows and columns

   m.set(0, 0);

   assert_true(m.get_rows_number() == 0, LOG);
   assert_true(m.get_columns_number() == 0, LOG);

   m.set(2, 3);

   assert_true(m.get_rows_number() == 2, LOG);
   assert_true(m.get_columns_number() == 3, LOG);

   m.set(0, 0);

   assert_true(m.get_rows_number() == 0, LOG);
   assert_true(m.get_columns_number() == 0, LOG);

   // Initialization 

   m.set(3, 2, 1.0);

   assert_true(m.get_rows_number() == 3, LOG);
   assert_true(m.get_columns_number() == 2, LOG);
   assert_true(m == 1.0, LOG);

   // File 

   m.save(file_name);
   m.set(file_name);

   assert_true(m.get_rows_number() == 3, LOG);
   assert_true(m.get_columns_number() == 2, LOG);
   assert_true(m == 1.0, LOG);

}


void MatrixTest::test_set_rows_number(void)
{
   message += "test_set_rows_number\n";
}


void MatrixTest::test_set_columns_number(void)
{
   message += "test_set_columns_number\n";

}


void MatrixTest::test_set_row(void)
{
   message += "test_set_row\n";

   Matrix<double> m(1,1);

   Vector<double> row(1, 1.0);

   m.set_row(0, row);

   assert_true(m.arrange_row(0) == row, LOG);
}


void MatrixTest::test_set_column(void)
{
   message += "test_set_column\n";

   Matrix<double> m(1,1);

   Vector<double> column(1, 1.0);

   m.set_column(0, column);

   assert_true(m.arrange_column(0) == column, LOG);
}


void MatrixTest::test_get_diagonal(void)
{
   message += "test_get_diagonal\n";

   Matrix<bool> m(2, 2, true);

   Vector<bool> diagonal = m.get_diagonal();

   assert_true(diagonal.size() == 2, LOG);
   assert_true(diagonal == true, LOG);
}


void MatrixTest::test_set_diagonal(void)
{
   message += "test_set_diagonal\n";

   Matrix<bool> m;
   Vector<bool> diagonal;

   // Test

   m.set(2, 2, true);

   m.set_diagonal(false);

   diagonal = m.get_diagonal();

   assert_true(diagonal.size() == 2, LOG);
   assert_true(diagonal == false, LOG);

   // Test

   diagonal.set(2);
   diagonal[0] = true;
   diagonal[1] = false;

   m.set_diagonal(diagonal);

   diagonal = m.get_diagonal();

   assert_true(diagonal.size() == 2, LOG);
   assert_true(diagonal[0] == true, LOG);
   assert_true(diagonal[1] == false, LOG);
}


void MatrixTest::test_sum_diagonal(void)
{
   message += "test_sum_diagonal\n";

   Matrix<int> m;
   Matrix<int> sum;  
   Vector<int> diagonal;

   // Test

   m.set(2, 2, 1);

   sum = m.sum_diagonal(1);

   diagonal = sum.get_diagonal();

   assert_true(diagonal.size() == 2, LOG);
   assert_true(diagonal == 2, LOG);

}


void MatrixTest::test_resize(void)
{
   message += "test_resize\n";

   Matrix<int> m(1,1);
   
   m.resize(0, 0);

   assert_true(m.get_rows_number() == 0, LOG);
   assert_true(m.get_columns_number() == 0, LOG);

   m.resize(1,1);   

   assert_true(m.get_rows_number() == 1, LOG);
   assert_true(m.get_columns_number() == 1, LOG);

   m.initialize(1);

   m.resize(2,2);

   assert_true(m.get_rows_number() == 2, LOG);
   assert_true(m.get_columns_number() == 2, LOG);
   assert_true(m[0][0] == 1, LOG);
}


void MatrixTest::test_append_row(void)
{
   message += "test_append_row\n";

   Matrix<bool> m(1, 1, false);

   Vector<bool> v(1, true);

   m.append_row(v);

   assert_true(m.get_rows_number() == 2, LOG);
   assert_true(m[1][0] == true, LOG);
}


void MatrixTest::test_append_column(void)
{
   message += "test_append_column\n";

   Matrix<bool> m(1, 1, false);

   Vector<bool> v(1, true);

   m.append_column(v);

   assert_true(m.get_columns_number() == 2, LOG);
   assert_true(m[0][1] == true, LOG);
}


void MatrixTest::test_subtract_row(void)
{
   message += "test_subtract_row\n";

   Matrix<bool> m(2, 1);
   m[0][0] = true;
   m[1][0] = false;

   m.subtract_row(0);

   assert_true(m.get_rows_number() == 1, LOG);
   assert_true(m[0][0] == false, LOG);  
}


void MatrixTest::test_subtract_column(void)
{
   message += "test_subtract_column\n";

   Matrix<bool> m(1, 2, false);
   m[0][0] = true;
   m[0][1] = false;

   m.subtract_column(0);

   assert_true(m.get_columns_number() == 1, LOG);
   assert_true(m[0][0] == false, LOG);  
}


void MatrixTest::test_initialize(void)
{
   message += "test_initialize\n";
}


void MatrixTest::test_randomize_uniform(void)
{
   message += "test_randomize_uniform\n";

   Matrix<double> m(1, 1);

   m.randomize_uniform();

   assert_true(m >= -1.0, LOG);
   assert_true(m <=  1.0, LOG);

   m.randomize_uniform(-1.0, 0.0);

   assert_true(m >= -1.0, LOG);
   assert_true(m <=  0.0, LOG);
}


void MatrixTest::test_randomize_normal(void)
{
   message += "test_randomize_normal\n";
}


void MatrixTest::test_set_to_identity(void)
{
   message += "test_set_to_identity\n";

   Matrix<int> a(2, 2);
   a.initialize_identity();

   Matrix<int> b(2, 2);
   b[0][0] = 1;
   b[0][1] = 0;
   b[1][0] = 0;
   b[1][1] = 1;

   assert_true(a == b, LOG);
}


void MatrixTest::test_dot(void)
{
   message += "test_dot\n";
}


void MatrixTest::test_calculate_mean_standard_deviation(void)
{
   message += "test_calculate_mean_standard_deviation\n";
}


void MatrixTest::test_calculate_statistics(void)
{
   message += "test_calculate_statistics\n";
}


void MatrixTest::test_calculate_histogram(void)
{
   message += "test_calculate_histogram\n";

   Matrix<double> m;

   Vector< Histogram<double> >  histograms;

   unsigned int bins_number;

   // Test

   m.set(2, 3);
   m.randomize_normal();

   bins_number = 1;

   histograms = m.calculate_histograms(bins_number);

   assert_true(histograms.size() == m.get_columns_number(), LOG);
   assert_true(histograms[0].get_bins_number() == bins_number, LOG);

   // Test

   m.set(2, 3);
   m.randomize_normal();

   bins_number = 4;

   histograms = m.calculate_histograms(bins_number);

   assert_true(histograms.size() == m.get_columns_number(), LOG);
   assert_true(histograms[0].get_bins_number() == bins_number, LOG);
}


void MatrixTest::test_calculate_minimal_indices(void)
{
   message += "test_calculate_minimal_indices\n";
}


void MatrixTest::test_calculate_maximal_indices(void)
{
   message += "test_calculate_maximal_indices\n";
}


void MatrixTest::test_calculate_minimal_maximal_indices(void)
{
   message += "test_calculate_minimal_maximal_indices\n";
}


void MatrixTest::test_calculate_sum_squared_error(void)
{
   message += "test_calculate_sum_squared_error\n";
}


void MatrixTest::test_calculate_mean_squared_error(void)
{
   message += "test_calculate_mean_squared_error\n";
}


void MatrixTest::test_calculate_root_mean_squared_error(void)
{
   message += "test_calculate_root_mean_squared_error\n";
}


void MatrixTest::test_calculate_minimum_maximum(void)
{
   message += "test_calculate_minimum_maximum\n";
}


void MatrixTest::test_calculate_determinant(void)
{
   message += "test_calculate_determinant\n";

   Matrix<int> m(1, 1, 1);

   assert_true(m.calculate_determinant() == 1, LOG);

   m.resize(2, 2);

   m[0][0] = 1;
   m[0][1] = 2;

   m[1][0] = 3;
   m[1][1] = 4;

   assert_true(m.calculate_determinant() == -2, LOG);

   m.resize(3, 3);

   m[0][0] = 1;
   m[0][1] = 2;
   m[0][2] = 3;

   m[1][0] = 4;
   m[1][1] = 5;
   m[1][2] = 6;

   m[2][0] = 7;
   m[2][1] = 8;
   m[2][2] = 9;

   assert_true(m.calculate_determinant() == 0, LOG);

   m.resize(4, 4);

   m[0][0] = 1;
   m[0][1] = 2;
   m[0][2] = 3;
   m[0][3] = 4;

   m[1][0] = 5;
   m[1][1] = 6;
   m[1][2] = 7;
   m[1][3] = 8;

   m[2][0] = 9;
   m[2][1] = 10;
   m[2][2] = 11;
   m[2][3] = 12;

   m[3][0] = 13;
   m[3][1] = 14;
   m[3][2] = 15;
   m[3][3] = 16;

   assert_true(m.calculate_determinant() == 0, LOG);
}


void MatrixTest::test_calculate_transpose(void)
{
   message += "test_calculate_transpose\n";

   Matrix<int> m(1, 1, 0);

   Matrix<int> transpose = m.calculate_transpose();

   assert_true(transpose == m, LOG);
}


void MatrixTest::test_calculate_cofactor(void)
{
   message += "test_calculate_cofactor\n";
}


// @todo

void MatrixTest::test_calculate_inverse(void)
{
   message += "test_calculate_inverse\n";

   Matrix<double> m(1, 1, 1.0);

//   assert_true(m.calculate_inverse() == 1.0, LOG);

   m.resize(2, 2);

   m[0][0] = 1.0;
   m[0][1] = 2.0;

   m[1][0] = 3.0;
   m[1][1] = 4.0;

//   assert_true(m.calculate_inverse() == -2, LOG);

   m.resize(3, 3);

   m[0][0] = 1.0;
   m[0][1] = 2.0;
   m[0][2] = 3.0;

   m[1][0] = 4.0;
   m[1][1] = 5.0;
   m[1][2] = 6.0;

   m[2][0] = 7.0;
   m[2][1] = 8.0;
   m[2][2] = 9.0;

//   assert_true(m.calculate_inverse() == 0, LOG);

   m.resize(4, 4);

   m[0][0] = 1.0;
   m[0][1] = 2.0;
   m[0][2] = 3.0;
   m[0][3] = 4.0;

   m[1][0] = 5.0;
   m[1][1] = 6.0;
   m[1][2] = 7.0;
   m[1][3] = 8.0;

   m[2][0] = 9.0;
   m[2][1] = 10.0;
   m[2][2] = 11.0;
   m[2][3] = 12.0;

   m[3][0] = 13.0;
   m[3][1] = 14.0;
   m[3][2] = 15.0;
   m[3][3] = 16.0;

//   assert_true(m.calculate_inverse() == 0, LOG);
}


void MatrixTest::test_is_symmetric(void)
{
   message += "test_is_symmetric\n";

   Matrix<int> m(1, 1, 1);

   assert_true(m.is_symmetric(), LOG);

   m.set(2, 2);

   m.initialize_identity();

   assert_true(m.is_symmetric(), LOG);
}


void MatrixTest::test_is_antisymmetric(void)
{
   message += "test_is_antisymmetric\n";

   Matrix<int> m;

   // Test

   m.set(1, 1, 0);

   assert_true(m.is_antisymmetric() == true, LOG);

   // Test

   m.set(2, 2, 1);

   assert_true(m.is_antisymmetric() == false, LOG);

   // Test

   m.set(2, 2, 1);

   m[0][0] = 0;
   m[0][1] = -2;
   m[1][0] = 2;
   m[1][1] = 0;

   assert_true(m.is_antisymmetric() == true, LOG);

}


void MatrixTest::test_scale_mean_standard_deviation(void)
{
   message += "test_scale_mean_standard_deviation\n";

   Matrix<double> m;

   Vector< Statistics<double> > statistics;

   // Test

   m.set(2, 2);
   m.randomize_uniform();

   m.scale_mean_standard_deviation();

   statistics = m.calculate_statistics();

   assert_true(statistics[0].has_mean_zero_standard_deviation_one(), LOG);
   assert_true(statistics[1].has_mean_zero_standard_deviation_one(), LOG);

}


void MatrixTest::test_scale_rows_mean_standard_deviation(void)
{
   message += "test_scale_rows_mean_standard_deviation\n";

}


void MatrixTest::test_scale_columns_mean_standard_deviation(void)
{
   message += "test_scale_columns_mean_standard_deviation\n";

}


void MatrixTest::test_scale_rows_columns_mean_standard_deviation(void)
{
   message += "test_scale_rows_columns_mean_standard_deviation\n";

}


void MatrixTest::test_scale_minimum_maximum(void)
{
   message += "test_scale_minimum_maximum\n";

}


void MatrixTest::test_scale_rows_minimum_maximum(void)
{
   message += "test_scale_rows_minimum_maximum\n";

}


void MatrixTest::test_scale_columns_minimum_maximum(void)
{
   message += "test_scale_columns_minimum_maximum\n";

}


void MatrixTest::test_scale_rows_columns_minimum_maximum(void)
{
   message += "test_scale_rows_columns_minimum_maximum\n";

}


void MatrixTest::test_unscale_mean_standard_deviation(void)
{
   message += "test_unscale_mean_standard_deviation\n";
}


void MatrixTest::test_unscale_rows_mean_standard_deviation(void)
{
   message += "test_unscale_rows_mean_standard_deviation\n";
}


void MatrixTest::test_unscale_columns_mean_standard_deviation(void)
{
   message += "test_unscale_columns_mean_standard_deviation\n";
}


void MatrixTest::test_unscale_rows_columns_mean_standard_deviation(void)
{
   message += "test_unscale_rows_columns_mean_standard_deviation\n";
}


void MatrixTest::test_unscale_minimum_maximum(void)
{
   message += "test_unscale_minimum_maximum\n";

}


void MatrixTest::test_unscale_rows_minimum_maximum(void)
{
   message += "test_unscale_rows_minimum_maximum\n";

}


void MatrixTest::test_unscale_columns_minimum_maximum(void)
{
   message += "test_unscale_columns_minimum_maximum\n";

}


void MatrixTest::test_unscale_rows_columns_minimum_maximum(void)
{
   message += "test_unscale_rows_columns_minimum_maximum\n";

}


void MatrixTest::test_print(void)
{
   message += "test_print\n";

   Matrix<bool> m(6, 1, true);
   //m.print();
}


void MatrixTest::test_save(void)
{
   message += "test_save\n";

   std::string file_name = "../data/matrix.dat";

   Matrix<int> m;

   m.save(file_name);

}


void MatrixTest::test_load(void)
{
   message += "test_load\n";

   std::string file_name = "../data/matrix.dat";

   Matrix<int> m;

   m.save(file_name);
   m.load(file_name);

   assert_true(m.get_rows_number() == 0, LOG);
   assert_true(m.get_columns_number() == 0, LOG);

   m.set(1, 2, 3);

   m.save(file_name);
   m.load(file_name);

   assert_true(m.get_rows_number() == 1, LOG);
   assert_true(m.get_columns_number() == 2, LOG);
   assert_true(m == 3, LOG);   

   m.set(2, 1, 1);

   m.save(file_name);
   m.load(file_name);

   assert_true(m.get_rows_number() == 2, LOG);
   assert_true(m.get_columns_number() == 1, LOG);

   m.set(4, 4, 0);

   m.save(file_name);
   m.load(file_name);

   assert_true(m.get_rows_number() == 4, LOG);
   assert_true(m.get_columns_number() == 4, LOG);
   assert_true(m == 0, LOG);

   m.set(1, 1, -99);

   m.save(file_name);
   m.load(file_name);

   assert_true(m.get_rows_number() == 1, LOG);
   assert_true(m.get_columns_number() == 1, LOG);
   assert_true(m == -99, LOG);

}


void MatrixTest::test_parse(void)
{
    message += "test_parse\n";

    Matrix<int> m;
    std::string str;

    // Test

    str = "";

    m.parse(str);

    assert_true(m.get_rows_number() == 0, LOG);
    assert_true(m.get_columns_number() == 0, LOG);

    // Test

    str =
    "1 2 3\n"
    "4 5 6\n";

    m.parse(str);

    assert_true(m.get_rows_number() == 2, LOG);
    assert_true(m.get_columns_number() == 3, LOG);

    // Test

    str =
    "1 2\n"
    "3 4\n"
    "5 6\n";

    m.parse(str);

    assert_true(m.get_rows_number() == 3, LOG);
    assert_true(m.get_columns_number() == 2, LOG);
}


void MatrixTest::run_test_case(void)
{
   message += "Running matrix test case...\n";  

   // Constructor and destructor methods

   test_constructor();
   test_destructor();

   // Assignment operators methods

   test_assignment_operator();   

   // Reference operator methods

   test_reference_operator();   

   // Arithmetic operators

   test_sum_operator();
   test_rest_operator();
   test_multiplication_operator();
   test_division_operator();

   // Arithmetic and assignment operators

   test_sum_assignment_operator();
   test_rest_assignment_operator();
   test_multiplication_assignment_operator();
   test_division_assignment_operator();

   // Equality and relational operators

   test_equal_to_operator();
   test_not_equal_to_operator();
   test_greater_than_operator();
   test_less_than_operator();
   test_greater_than_or_equal_to_operator();
   test_less_than_or_equal_to_operator();

   // Output operators

   test_output_operator();

   // Get methods

   test_get_rows_number();
   test_get_columns_number();  

   test_arrange_row();
   test_arrange_column();

   test_arrange_submatrix();

   // Set methods

   test_set();
   
   test_set_rows_number();
   test_set_columns_number();

   test_set_row();
   test_set_column();

   // Diagonal methods

   test_get_diagonal();
   test_set_diagonal();
   test_sum_diagonal();
   
   // Resize methods

   test_resize();
    
   test_append_row();
   test_append_column();
   
   test_subtract_row();
   test_subtract_column();

   // Initialization methods

   test_initialize();
   test_randomize_uniform();
   test_randomize_normal();

   test_set_to_identity();

   // Mathematical methods

   test_dot();

   test_calculate_minimum_maximum();
   test_calculate_mean_standard_deviation();

   test_calculate_statistics();

   test_calculate_histogram();

   test_calculate_minimal_indices();
   test_calculate_maximal_indices();
   
   test_calculate_minimal_maximal_indices();

   test_calculate_sum_squared_error();
   test_calculate_mean_squared_error();
   test_calculate_root_mean_squared_error();

   test_calculate_determinant();
   test_calculate_transpose();
   test_calculate_cofactor();
   test_calculate_inverse();

   test_is_symmetric();
   test_is_antisymmetric();

   // Scaling methods
 
   test_scale_mean_standard_deviation();
   test_scale_rows_mean_standard_deviation();
   test_scale_columns_mean_standard_deviation();
   test_scale_rows_columns_mean_standard_deviation();

   test_scale_minimum_maximum();
   test_scale_rows_minimum_maximum();
   test_scale_columns_minimum_maximum();
   test_scale_rows_columns_minimum_maximum();

   // Unscaling methods

   test_unscale_mean_standard_deviation();
   test_unscale_rows_mean_standard_deviation();
   test_unscale_columns_mean_standard_deviation();
   test_unscale_rows_columns_mean_standard_deviation();

   test_unscale_minimum_maximum();
   test_unscale_rows_minimum_maximum();
   test_unscale_columns_minimum_maximum();
   test_unscale_rows_columns_minimum_maximum();

   // Serialization methods

   test_print();

   test_load();

   test_save();

   test_parse();

   message += "End of matrix test case.\n";
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
