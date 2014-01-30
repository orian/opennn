/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   O U T P U T S   C L A S S   H E A D E R                                                                    */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __OUTPUTS_H__
#define __OUTPUTS_H__

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

/// This class is used to store some information about the output variables of a neural network.
/// That information basically consists on the names, units and descriptions of the output variables.

class Outputs
{

public:

   // DEFAULT CONSTRUCTOR

   explicit Outputs(void);


   // OUTPUTS NUMBER CONSTRUCTOR

   explicit Outputs(const unsigned&);


   // XML CONSTRUCTOR

   explicit Outputs(const tinyxml2::XMLDocument&);


   // COPY CONSTRUCTOR

   Outputs(const Outputs&);

   // DESTRUCTOR

   virtual ~Outputs(void);

   // ASSIGNMENT OPERATOR

   Outputs& operator = (const Outputs&);

   // EQUAL TO OPERATOR

   bool operator == (const Outputs&) const;

   ///
   /// This structure contains the information of a single output.
   ///

   struct Item
   {
       /// Name of neural network output.

       std::string name;

       /// Units of neural network output.

       std::string units;

       /// Description of neural network output.

       std::string description;
   };

   // METHODS

   bool is_empty(void) const;

   /// Returns the number of outputs neurons in the neural network

   inline int get_outputs_number(void) const
   {
      return(items.size());
   }

   // Output variables information

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
   void set(const Vector<Item>&);
   void set(const Outputs&);

   void set_outputs_number(const unsigned&);

   virtual void set_default(void);

   // Output variables information

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

   void grow_output(void);

   void prune_output(const unsigned&);

   // Default names

   Vector<std::string> write_default_names(void) const;

   // Serialization methods

   std::string to_string(void) const;

   virtual tinyxml2::XMLDocument* to_XML(void) const;
   virtual void from_XML(const tinyxml2::XMLDocument&);

protected:

   // MEMBERS

   /// Name of output variables.

   Vector<Item> items;

   /// Units of output variables.

   Vector<std::string> units;

   /// Description of output variables.

   Vector<std::string> descriptions;

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

