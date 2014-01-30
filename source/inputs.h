/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   I N P U T S   C L A S S   H E A D E R                                                                      */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __INPUTS_H__
#define __INPUTS_H__

// System includes

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

// OpenNN includes

#include "vector.h"
#include "matrix.h"

// TinyXml includes

#include "../tinyxml2/tinyxml2.h"

namespace OpenNN
{

/// This class is used to store some information about the input variables of a neural network.
/// That information basically consists on the names, units and descriptions of the input variables.

class Inputs
{

public:

   // DEFAULT CONSTRUCTOR

   explicit Inputs(void);

   // INPUTS NUMBER CONSTRUCTOR

   explicit Inputs(const unsigned&);

   // XML CONSTRUCTOR

   explicit Inputs(const tinyxml2::XMLDocument&);


   // COPY CONSTRUCTOR

   Inputs(const Inputs&);

   // DESTRUCTOR

   virtual ~Inputs(void);

   // ASSIGNMENT OPERATOR

   Inputs& operator = (const Inputs&);

   // EQUAL TO OPERATOR

   bool operator == (const Inputs&) const;

   ///
   /// This structure contains the information of a single input.
   ///

   struct Item
   {
       /// Name of output variable.
       std::string name;

       /// Units of output variable.

       std::string units;

       /// Description of output variable.

       std::string description;
   };

   // METHOD

   bool is_empty(void) const;

   /// Returns the number of inputs in the multilayer perceptron

   inline unsigned get_inputs_number(void) const
   {
      return(items.size());
   }

   // Inputs information

   Vector<std::string> arrange_names(void) const;
   const std::string& get_name(const unsigned&) const;

   Vector<std::string> arrange_units(void) const;
   const std::string& get_unit(const unsigned&) const;

   Vector<std::string> arrange_descriptions(void) const;
   const std::string& get_description(const unsigned&) const;

   // Variables

   Matrix<std::string> arrange_information(void) const;


   // Display messages

   const bool& get_display(void) const;

   // SET METHODS

   void set(void);
   void set(const unsigned&);
   void set(const Vector< Vector<std::string> >&);
   void set(const Inputs&);

   void set_inputs_number(const unsigned&);

   virtual void set_default(void);

   // Input variables information

   void set_names(const Vector<std::string>&);
   void set_name(const unsigned&, const std::string&);

   void set_units(const Vector<std::string>&);
   void set_unit(const unsigned&, const std::string&);

   void set_descriptions(const Vector<std::string>&);
   void set_description(const unsigned&, const std::string&);

   // Variables

   void set_information(const Matrix<std::string>&);

   void set_display(const bool&);

   // Growing and pruning

   void grow_input(void);

   void prune_input(const unsigned&);

   // Default names

   Vector<std::string> write_default_names(void) const;

   // Serialization methods

   std::string to_string(void) const;

   virtual tinyxml2::XMLDocument* to_XML(void) const;
   virtual void from_XML(const tinyxml2::XMLDocument&);

protected:

   // MEMBERS

   /// Input variables.

   Vector<Item> items;

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

