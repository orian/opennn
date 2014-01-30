/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   A I R C R A F T   L A N D I N G   S O L U T I O N   E R R O R   C L A S S   H E A D E R                    */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __AIRCRAFTLANDINGSOLUTIONERROR_H__
#define __AIRCRAFTLANDINGSOLUTIONERROR_H__

#include "../../source/opennn.h"

namespace OpenNN
{

class AircraftLandingSolutionError : public SolutionsError
{

public:

   // DEFAULT CONSTRUCTOR

   explicit AircraftLandingSolutionError(void);

   // NEURAL NETWORK CONSTRUCTOR

   explicit AircraftLandingSolutionError(NeuralNetwork*);

   // DATA SET CONSTRUCTOR

   explicit AircraftLandingSolutionError(MathematicalModel*);

   // GENERAL CONSTRUCTOR

   explicit AircraftLandingSolutionError(NeuralNetwork*, MathematicalModel*);

   // XML CONSTRUCTOR

   explicit AircraftLandingSolutionError(const tinyxml2::XMLDocument&);

   // COPY CONSTRUCTOR

   AircraftLandingSolutionError(const AircraftLandingSolutionError&);

   // DESTRUCTOR

   virtual ~AircraftLandingSolutionError(void);

   // METHODS

   // Get methods

   // Set methods

   void set(const AircraftLandingSolutionError&);

   // Target solution methods

   Matrix<double> calculate_target_dependent_variables(const Matrix<double>&) const;

   double calculate_performance(void) const;   
   double calculate_performance(const Vector<double>&) const;   

};

}

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
