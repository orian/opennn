/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   V A R I A B L E S   C L A S S   H E A D E R                                                                */
/*                                                                                                              */ 
/*   Roberto Lopez                                                                                              */ 
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __VARIABLES_H__
#define __VARIABLES_H__

// System includes

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <stdexcept>
#include <ctime>
#include <exception>

// OpenNN includes

#include "vector.h"
#include "matrix.h"

// TinyXml includes

#include "../tinyxml2/tinyxml2.h"

namespace OpenNN
{

/// This class is used to store information about the variables of a data set. 
/// Variables in a data set can be used as inputs and targets.
/// This class also stores information about the name, unit and description of all the variables.

class Variables
{

public:  

   // DEFAULT CONSTRUCTOR

   explicit Variables(void);

   // VARIABLES NUMBER CONSTRUCTOR

   explicit Variables(const unsigned&);

   // INPUT AND TARGET VARIABLES NUMBER

   explicit Variables(const unsigned&, const unsigned&);

   // XML CONSTRUCTOR

   explicit Variables(const tinyxml2::XMLDocument&);

   // COPY CONSTRUCTOR

   Variables(const Variables&);

   // DESTRUCTOR

   virtual ~Variables(void);

   // ASSIGNMENT OPERATOR

   Variables& operator = (const Variables&);

   // EQUAL TO OPERATOR

   bool operator == (const Variables&) const;

   // ENUMERATIONS

   /// This enumeration represents the possible uses of a variable (input, target or unused).

   enum Use{Input, Target, Unused};

   // STRUCTURES

   ///
   /// This structure contains the information of a single variable.
   ///

   struct Item
   {
       /// Name of a variable.

       std::string name;

       /// Units of a variable.

       std::string units;

       /// Description of a variable.

       std::string description;

       /// Use of a variable (none, input or target).

       Use use;
   };

   // METHODS

   /// Returns the total number of variables in the data set.

   inline unsigned get_variables_number(void) const
   {
      return(items.size());
   }

   unsigned count_used_variables_number(void) const;
   unsigned count_unused_variables_number(void) const;
   unsigned count_inputs_number(void) const;
   unsigned count_targets_number(void) const;

   Vector<unsigned> count_uses(void) const;

   // Variables methods

   Vector<Use> arrange_uses(void) const;
   Vector<std::string> write_uses(void) const; 

   const Use& get_use(const unsigned&) const;
   std::string write_use(const unsigned&) const;

   Vector<unsigned> arrange_inputs_indices(void) const;
   Vector<unsigned> arrange_targets_indices(void) const;

   // Information methods

   Vector<std::string> arrange_names(void) const;
   const std::string& get_name(const unsigned&) const;

   Vector<std::string> arrange_units(void) const;
   const std::string& get_unit(const unsigned&) const;

   Vector<std::string> arrange_descriptions(void) const;
   const std::string& get_description(const unsigned&) const;

   const bool& get_display(void) const;

   // Set methods

   void set(void);
   void set(const unsigned&);
   void set(const unsigned&, const unsigned&);
   void set(const tinyxml2::XMLDocument&);

   void set_default(void);

   // Data methods

   void set_variables_number(const unsigned&);

   // Variables methods

   void set_items(const Vector<Item>&);

   void set_uses(const Vector<Use>&); 
   void set_uses(const Vector<std::string>&); 

   void set_use(const unsigned&, const Use&);
   void set_use(const unsigned&, const std::string&);

   void set_input(void);
   void set_target(void);

   void set_default_uses(void);

   // Information methods

   void set_names(const Vector<std::string>&);
   void set_name(const unsigned&, const std::string&);

   void set_units(const Vector<std::string>&);
   void set_units(const unsigned&, const std::string&);

   void set_descriptions(const Vector<std::string>&);
   void set_description(const unsigned&, const std::string&);

   void set_display(const bool&);

   Matrix<std::string> arrange_information(void) const;

   Vector<std::string> arrange_inputs_units(void) const;
   Vector<std::string> arrange_targets_units(void) const;

   Vector<std::string> arrange_inputs_name(void) const;
   Vector<std::string> arrange_targets_name(void) const;

   Vector<std::string> arrange_inputs_description(void) const;
   Vector<std::string> arrange_targets_description(void) const;

   Matrix<std::string> arrange_inputs_information(void) const;
   Matrix<std::string> arrange_targets_information(void) const;


   // Serialization methods

   std::string to_string(void) const;

   tinyxml2::XMLDocument* to_XML(void) const;
   void from_XML(const tinyxml2::XMLDocument&);


private:

   // MEMBERS

   /// Vector of variable items.
   /// Each item contains the name, units, description and use of a single variable.

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
