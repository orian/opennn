/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   M O C K   T R A I N I N G   A L G O R I T H M   C L A S S   H E A D E R                                    */
/*                                                                                                              */ 
/*   Roberto Lopez                                                                                              */ 
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __MOCKTRAININGALGORITHM_H__
#define __MOCKTRAININGALGORITHM_H__

// OpenNN includes

#include "../source/opennn.h"

using namespace OpenNN;


class MockTrainingAlgorithm : public TrainingAlgorithm
{

public:

   // DEFAULT CONSTRUCTOR

   explicit MockTrainingAlgorithm(void); 


   // GENERAL CONSTRUCTOR

   explicit MockTrainingAlgorithm(PerformanceFunctional*); 


   // DESTRUCTOR

   virtual ~MockTrainingAlgorithm(void);


   // STRUCTURES 

   struct MockTrainingAlgorithmResults : public Results
   {
   };


   // METHODS

   // Training methods

   MockTrainingAlgorithmResults* perform_training(void);

   // Serialization methods

   tinyxml2::XMLDocument* to_XML(void) const;
   void from_XML(const tinyxml2::XMLDocument&);

};


#endif


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
