/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   http://flood.sourceforge.net                                                                               */
/*                                                                                                              */
/*   T I M E   S E R I E S   P R E D I C T I O N   T E S T I N G   T E S T   C L A S S   H E A D E R            */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */ 
/*   E-mail: roberto-lopez@users.sourceforge.net                                                                */ 
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __TIMESERIESPREDICTIONTESTINGTEST_H__
#define __TIMESERIESPREDICTIONTESTINGTEST_H__

// Unit testing includes

#include "unit_testing.h"

using namespace OpenNN;


class TimeSeriesPredictionTestingTest : public UnitTesting 
{

#define	STRING(x) #x
#define TOSTRING(x) STRING(x)
#define LOG __FILE__ ":" TOSTRING(__LINE__)"\n"

public:  

   // GENERAL CONSTRUCTOR

   explicit TimeSeriesPredictionTestingTest(void);


   // DESTRUCTOR

   virtual ~TimeSeriesPredictionTestingTest(void);


   // METHODS

   // Constructor and destructor methods

   void test_constructor(void);
   void test_destructor(void);

   // Get methods

   void test_get_neural_network_pointer(void);
   void test_get_data_set_pointer(void);
   
   void test_get_display(void);

   // Set methods

   void test_set_neural_network_pointer(void);
   void test_set_data_set_pointer(void);

   void test_set_display(void);

   // Unit testing methods

   void run_test_case(void);

};


#endif

// OpenNN: An Open Source Neural Networks C++ Library.
// Copyright (C) 2005-2013 Roberto Lopez 
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
