/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   I N S T A N C E S   C L A S S   H E A D E R                                                                */
/*                                                                                                              */ 
/*   Roberto Lopez                                                                                              */ 
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

#ifndef __INSTANCES_H__
#define __INSTANCES_H__

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

/// This class is used to store information about the instances of a data set. 
/// Instances in a data set can be used for training, generalization and testing.    

class Instances
{

public:  

   // DEFAULT CONSTRUCTOR

   explicit Instances(void);

   // INSTANCES NUMBER CONSTRUCTOR

   explicit Instances(const unsigned&);

   // XML CONSTRUCTOR

   explicit Instances(const tinyxml2::XMLDocument&);


   // COPY CONSTRUCTOR

   Instances(const Instances&);


   // DESTRUCTOR

   virtual ~Instances(void);

   // ASSIGNMENT OPERATOR

   Instances& operator = (const Instances&);

   // EQUAL TO OPERATOR

   bool operator == (const Instances&) const;

   // ENUMERATIONS

   /// This enumeration represents the possible uses of an instance
   /// (no use, training, generalization or testing).

   enum Use{Unused, Training, Generalization, Testing};

   /// This is an enumeration of the available methods for dividing the instances
   /// into training, generalization and testing subsets.

   enum SplittingMethod{Sequential, Random};

   // STRUCTURES

   ///
   /// This structure contains the information of a single instance,
   /// which is only its use (training, generalization, testing or unused).
   ///

   struct Item
   {
       /// Default constructor.

       Item(void)
       {
           use = Training;
       }

       /// Use constructor.

       Item(const Use& new_use)
       {
           use = new_use;
       }

       /// Destructor.

       virtual ~Item(void)
       {
       }

       /// Use of an instance (training, generalization, testing or unused).

       Use use;
   };


   // METHODS

   static SplittingMethod get_splitting_method(const std::string&);

   /// Returns the number of instances in the data set.

   inline unsigned get_instances_number(void) const
   {
      return(items.size());
   }

   // Instances methods

   Vector<Use> arrange_uses(void) const;
   Vector<std::string> write_uses(void) const;
   Vector<std::string> write_abbreviated_uses(void) const;

   const Use& get_use(const unsigned&) const;
   std::string write_use(const unsigned&) const;

   unsigned count_training_instances_number(void) const;
   unsigned count_generalization_instances_number(void) const;
   unsigned count_testing_instances_number(void) const;
   unsigned count_unused_instances_number(void) const;
   unsigned count_used_instances_number(void) const;

   Vector<unsigned> count_uses(void) const;

   Vector<unsigned> arrange_training_indices(void) const;
   Vector<unsigned> arrange_generalization_indices(void) const;
   Vector<unsigned> arrange_testing_indices(void) const;

   const bool& get_display(void) const;

   // Set methods

   void set(void);
   void set(const unsigned&);
   void set(const tinyxml2::XMLDocument&);

   void set_default(void);

   // Data methods

   void set_instances_number(const unsigned&);

   // Instances methods

   void set_uses(const Vector<Use>&);
   void set_uses(const Vector<std::string>&);

   void set_use(const unsigned&, const Use&);
   void set_use(const unsigned&, const std::string&);

   void set_training(void);
   void set_generalization(void);
   void set_testing(void);

   void set_display(const bool&);

   // Splitting methods

   void split_sequential_indices(const double& training_ratio = 0.6, const double& generalization_ratio = 0.2, const double& testing_ratio = 0.2);

   void split_random_indices(const double& training_ratio = 0.6, const double& generalization_ratio = 0.2, const double& testing_ratio = 0.2);

   void split_instances(const SplittingMethod& splitting_method = Random, const double& training_ratio = 0.6, const double& generalization_ratio = 0.2, const double& testing_ratio = 0.2);

   Vector<double> calculate_uses_percentage(void) const;

   // Serialization methods

   std::string to_string(void) const;

   tinyxml2::XMLDocument* to_XML(void) const;
   void from_XML(const tinyxml2::XMLDocument&);

private:

   // MEMBERS

   /// Uses of instances (none, training, generalization or testing).

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

