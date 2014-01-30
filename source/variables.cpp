/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   V A R I A B L E S   C L A S S                                                                              */
/*                                                                                                              */ 
/*   Roberto Lopez                                                                                              */ 
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// OpenNN includes

#include "variables.h"

namespace OpenNN
{

// DEFAULT CONSTRUCTOR

/// Default constructor. 
/// It creates a variables object with zero variables.
/// It also initializes the rest of class members to their default values.

Variables::Variables(void)
{
   set();  
}


// VARIABLES NUMBER CONSTRUCTOR

/// Variables number constructor. 
/// It creates a variables object with a given number of variables.
/// All the variables are set as inputs but the last, which is set as targets. 
/// It also initializes the rest of class members to their default values.
/// @param new_variables_number Number of variables.

Variables::Variables(const unsigned& new_variables_number)
{
   set(new_variables_number);
}


// INPUT AND TARGET VARIABLES NUMBERS CONSTRUCTOR

/// Variables number constructor. 
/// It creates a variables object with a given number of input and target variables.
/// It also initializes the rest of class members to their default values.
/// @param new_inputs_number Number of input variables.
/// @param new_targets_number Number of target variables.

Variables::Variables(const unsigned& new_inputs_number, const unsigned& new_targets_number)
{
   set(new_inputs_number, new_targets_number);
}


// XML CONSTRUCTOR

/// XML constructor. 
/// It creates a variables object and loads its members from a XML document.
/// @param variables_document TinyXML document with the member data. 

Variables::Variables(const tinyxml2::XMLDocument& variables_document)
{
   set(variables_document);
}


// COPY CONSTRUCTOR

/// Copy constructor. 
/// It creates a copy of an existing variables object.
/// @param other_variables Variables information object to be copied.

Variables::Variables(const Variables& other_variables)
{
   // Items

   items = other_variables.items;

   // Utilities

   display = other_variables.display;
}


// DESTRUCTOR

/// Destructor. 

Variables::~Variables(void)
{
}


// ASSIGNMENT OPERATOR

/// Assignment operator. 
/// It assigns to the current object the members of an existing variables object.
/// @param other_variables Variables information object to be assigned.

Variables& Variables::operator=(const Variables& other_variables)
{
   if(this != &other_variables) 
   {
      // Items

      items = other_variables.items;

      // Utilities

      display = other_variables.display;
   }

   return(*this);
}


// EQUAL TO OPERATOR

// bool operator == (const Variables&) const method

/// Equal to operator. 
/// It compares this object with another object of the same class. 
/// It returns true if the members of the two objects have the same values, and false otherwise.
/// @ param other_variables Variables information object to be compared with.

bool Variables::operator == (const Variables& other_variables) const
{
   if(/*items == other_variables.items
   &&*/ display == other_variables.display)
   {
      return(true);
   }
   else
   {
      return(false);
   }
}


// METHODS

// unsigned count_used_variables_number(void) const method

/// Returns the number of variables which are either input or target.

unsigned Variables::count_used_variables_number(void) const
{
    const unsigned variables_number = get_variables_number();

    const unsigned unused_variables_number = count_unused_variables_number();

    return(variables_number - unused_variables_number);
}


// unsigned count_unused_variables_number(void) const method

/// Returns the number of variables which will neither be used as input nor as target.

unsigned Variables::count_unused_variables_number(void) const
{
   const unsigned variables_number = get_variables_number();

   unsigned count = 0;

   for(unsigned i = 0; i < variables_number; i++)
   {
      if(items[i].use == Unused)
	  {
	     count++;
	  }
   }

   return(count);
}


// unsigned count_inputs_number(void) const method

/// Returns the number of input variables of the data set.

unsigned Variables::count_inputs_number(void) const
{
   const unsigned variables_number = get_variables_number();

   unsigned count = 0;

   for(unsigned i = 0; i < variables_number; i++)
   {
      if(items[i].use == Input)
	  {
	     count++;
	  }
   }

   return(count);
}


// unsigned count_targets_number(void) const method

/// Returns the number of target variables of the data set.

unsigned Variables::count_targets_number(void) const
{
   const unsigned variables_number = get_variables_number();

   unsigned count = 0;

   for(unsigned i = 0; i < variables_number; i++)
   {
      if(items[i].use == Target)
	  {
	     count++;
	  }
   }

   return(count);
}


// Vector<unsigned> count_uses(void) const method

/// Returns a vector containing the numbers of input, target and unused variables,
/// respectively.
/// The size of that vector is three.

Vector<unsigned> Variables::count_uses(void) const
{
    Vector<unsigned> count(3, 0);

    const unsigned variables_number = get_variables_number();

    for(unsigned i = 0; i < variables_number; i++)
    {
        if(items[i].use == Input)
        {
           count[0]++;
        }
        else if(items[i].use == Target)
        {
           count[1]++;
        }
        else
        {
           count[2]++;
        }
    }

    return(count);
}


// Vector<Use> arrange_uses(void) const method

/// Returns a vector containing the use of each variable.
/// The size of the vector is equal to the number of variables.

Vector<Variables::Use> Variables::arrange_uses(void) const
{
    const unsigned variables_number = get_variables_number();

    Vector<Variables::Use> uses(variables_number);

    for(unsigned i = 0; i < variables_number; i++)
    {
        uses[i] = items[i].use;
    }

   return(uses);
}


// Vector<std::string> write_uses(void) const method

/// Returns a vector of strings with the use of each variable.
/// The size of the vector is equal to the number of variables.
/// The possible values for the elements are "Unused", "Input" and "Target".

Vector<std::string> Variables::write_uses(void) const
{
   const unsigned variables_number = get_variables_number();

   Vector<std::string> uses_string(variables_number);

   for(unsigned i = 0; i < variables_number; i++)
   {
      if(items[i].use == Unused)
	  {	  
         uses_string[i] = "Unused";
	  }
      else if(items[i].use == Input)
	  {	  
	     uses_string[i] = "Input";    	     
	  }
      else if(items[i].use == Target)
	  {	  
	     uses_string[i] = "Target";    
	  }
	  else
	  {
         std::ostringstream buffer;

         buffer << "OpenNN Exception Variables class.\n"
                << "Vector<std::string> write_uses(void) const method.\n"
                << "Unknown use.\n";
 
	     throw std::logic_error(buffer.str());
	  }
   }

   return(uses_string);
}


// const Use& get_use(const unsigned&) const method

/// Returns the use of a single variable.
/// @param i Variable index.

const Variables::Use& Variables::get_use(const unsigned& i) const
{
    return(items[i].use);
}


// std::string write_use(const unsigned&) const method

/// Returns a string the use of a variable.
/// @param i Variable index.

std::string Variables::write_use(const unsigned& i) const
{
    if(items[i].use == Unused)
    {
       return("Unused");
    }
    else if(items[i].use == Input)
    {
       return("Input");
    }
    else if(items[i].use == Target)
    {
       return("Target");
    }
    else
    {
       std::ostringstream buffer;

       buffer << "OpenNN Exception Variables class.\n"
              << "std::string write_use(const unsigned&) const method.\n"
              << "Unknown use.\n";

       throw std::logic_error(buffer.str());
    }
}


// Matrix<std::string> arrange_information(void) const method

/// Returns all the available information about the variables as a matrix of strings.
/// The number of rows is the number of variables.
/// The number of columns is four.
/// Each row contains the information of a single variable (name, units, description and use).

Matrix<std::string> Variables::arrange_information(void) const
{
    const unsigned variables_number = get_variables_number();

    Matrix<std::string> information(variables_number, 4);

    for(unsigned i = 0; i < variables_number; i++)
    {
        information[i][0] = items[i].name;
        information[i][1] = items[i].units;
        information[i][2] = items[i].description;
        information[i][3] = write_use(i);
    }

    return(information);
}


// Vector<unsigned> arrange_inputs_indices(void) const method

/// Returns the indices of the input variables.

Vector<unsigned> Variables::arrange_inputs_indices(void) const
{
   const unsigned variables_number = get_variables_number();
   const unsigned inputs_number = count_inputs_number();

   Vector<unsigned> inputs_indices(inputs_number);

   unsigned index = 0;

   for(unsigned i = 0; i < variables_number; i++)
   {
      if(items[i].use == Input)
	  {
	     inputs_indices[index] = i;
		 index++;
	  }
   }

   return(inputs_indices);
}


// Vector<unsigned> arrange_targets_indices(void) const method

/// Returns the indices of the target variables.

Vector<unsigned> Variables::arrange_targets_indices(void) const
{
   const unsigned variables_number = get_variables_number();
   const unsigned targets_number = count_targets_number();

   Vector<unsigned> targets_indices(targets_number);

   unsigned index = 0;

   for(unsigned i = 0; i < variables_number; i++)
   {
      if(items[i].use == Target)
	  {
	     targets_indices[index] = i;
		 index++;
	  }
   }

   return(targets_indices);
}


// Vector<std::string> arrange_names(void) const method

/// Returns the names of all the variables in the data set.

Vector<std::string> Variables::arrange_names(void) const
{
   const unsigned variables_number = get_variables_number();

   Vector<std::string> names(variables_number);

   for(unsigned i = 0; i < variables_number; i++)
   {
       names[i] = items[i].name;
   }

   return(names);
}


// std::string& get_name(unsigned) method

/// Returns the name of a single variable in the data set.
/// @param i Index of variable. 

const std::string& Variables::get_name(const unsigned& i) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned variables_number = get_variables_number();

   if(i >= variables_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Variables class.\n"
             << "std::string& get_name(unsigned) method.\n"
             << "Index of variable must be less than number of variables.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   return(items[i].name);
}


// Vector<std::string> arrange_inputs_name(void) const method

/// Returns the names of the input variables in the data set.

Vector<std::string> Variables::arrange_inputs_name(void) const
{
   const unsigned inputs_number = count_inputs_number();

   const Vector<unsigned> inputs_indices = arrange_inputs_indices();

   Vector<std::string> inputs_name(inputs_number);

   unsigned index;

   for(unsigned i = 0; i < inputs_number; i++)
   {        
      index = inputs_indices[i];

      inputs_name[i] = items[index].name;
   }

   return(inputs_name);
}


// Vector<std::string> arrange_targets_name(void) const method

/// Returns the names of the target variables in the data set.

Vector<std::string> Variables::arrange_targets_name(void) const
{
   const unsigned targets_number = count_targets_number();

   const Vector<unsigned> targets_indices = arrange_targets_indices();

   Vector<std::string> targets_name(targets_number);

   unsigned index;

   for(unsigned i = 0; i < targets_number; i++)
   {        
      index = targets_indices[i];

      targets_name[i] = items[index].name;
   } 

   return(targets_name);
}


// Vector<std::string> arrange_units(void) const method

/// Returns the units of all the variables in the data set. 

Vector<std::string> Variables::arrange_units(void) const
{
    const unsigned variables_number = get_variables_number();

    Vector<std::string> units(variables_number);

    for(unsigned i = 0; i < variables_number; i++)
    {
        units[i] = items[i].units;
    }

   return(units);
}


// const std::string& get_units(const unsigned&) const method

/// Returns the units of a single variable in the data set. 
/// @param i Index of variable. 

const std::string& Variables::get_unit(const unsigned& i) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned variables_number = get_variables_number();

   if(i >= variables_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Variables class.\n"
             << "const std::string& get_units(const unsigned&) const method.\n"
             << "Index of variable must be less than number of variables.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   return(items[i].units);
}


// Vector<std::string> arrange_inputs_units(void) const method

/// Returns the units of the input variables in the data set. 

Vector<std::string> Variables::arrange_inputs_units(void) const
{
   const Vector<unsigned> inputs_indices = arrange_inputs_indices();

   const unsigned inputs_number = count_inputs_number();

   Vector<std::string> inputs_units(inputs_number);

   unsigned index;

   for(unsigned i = 0; i < inputs_number; i++)
   {
      index = inputs_indices[i];

      inputs_units[i] = items[index].units;
   }

   return(inputs_units);
}


// Vector<std::string> arrange_targets_units(void) const method

/// Returns the units of the target variables in the data set. 

Vector<std::string> Variables::arrange_targets_units(void) const
{
   const Vector<unsigned> targets_indices = arrange_targets_indices();

   const unsigned targets_number = count_targets_number();

   Vector<std::string> targets_units(targets_number);

   unsigned index;

   for(unsigned i = 0; i < targets_number; i++)
   {
      index = targets_indices[i];

      targets_units[i] = items[index].units;
   }

   return(targets_units);
}


// Vector<std::string> arrange_descriptions(void) const method

/// Returns the description of all the variables in the data set. 

Vector<std::string> Variables::arrange_descriptions(void) const
{
    const unsigned variables_number = get_variables_number();

    Vector<std::string> descriptions(variables_number);

    for(unsigned i = 0; i < variables_number; i++)
    {
        descriptions[i] = items[i].description;
    }

   return(descriptions);
}


// const std::string& get_description(const unsigned&) const method

/// Returns the description of a single variable in the data set. 
/// @param i Index of variable.

const std::string& Variables::get_description(const unsigned& i) const
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned variables_number = get_variables_number();

   if(i >= variables_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Variables class.\n"
             << "const std::string& get_description(const unsigned&) const method.\n"
             << "Index of variable must be less than number of variables.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   return(items[i].description);
}


// Vector<std::string> arrange_inputs_description(void) const method

/// Returns the description of the input variables in the data set. 

Vector<std::string> Variables::arrange_inputs_description(void) const
{
   const unsigned inputs_number = count_inputs_number();

   const Vector<unsigned> inputs_indices = arrange_inputs_indices();

   Vector<std::string> inputs_description(inputs_number);

   unsigned index;

   for(unsigned i = 0; i < inputs_number; i++)
   {
      index = inputs_indices[i];

      inputs_description[i] = items[index].description;
   }

   return(inputs_description);
}


// Vector<std::string> arrange_targets_descriptions(void) const method

/// Returns the description of the target variables in the data set. 

Vector<std::string> Variables::arrange_targets_description(void) const
{
   const Vector<unsigned> targets_indices = arrange_targets_indices();

   const unsigned targets_number = count_targets_number();

   Vector<std::string> target_descriptions(targets_number);

   unsigned index;

   for(unsigned i = 0; i < targets_number; i++)
   {
      index = targets_indices[i];

      target_descriptions[i] = items[index].description;
   }

   return(target_descriptions);
}


// Matrix<std::string> arrange_inputs_information(void) const method

/// Returns a single matrix with the names, units and descriptions of all the input variables.
/// The number of rows is the number of inputs, and the number of columns is 3.

Matrix<std::string> Variables::arrange_inputs_information(void) const
{
    const unsigned inputs_number = count_inputs_number();

    const Vector<unsigned> inputs_indices = arrange_inputs_indices();

    unsigned input_index;

    Matrix<std::string> inputs_information(inputs_number, 3);

    for(unsigned i = 0; i < inputs_number; i++)
    {
        input_index = inputs_indices[i];

        inputs_information[i][0] = items[input_index].name;
        inputs_information[i][1] = items[input_index].units;
        inputs_information[i][2] = items[input_index].description;
    }

    return(inputs_information);
}


// Matrix<std::string> arrange_targets_information(void) const method

/// Returns a single matrix with the names, units and descriptions of all the target variables.
/// The number of rows is the number of targets, and the number of columns is 3.

Matrix<std::string> Variables::arrange_targets_information(void) const
{
    const unsigned targets_number = count_targets_number();

    const Vector<unsigned> targets_indices = arrange_targets_indices();

    unsigned target_index;

    Matrix<std::string> targets_information(targets_number, 3);

    for(unsigned i = 0; i < targets_number; i++)
    {
        target_index = targets_indices[i];

        targets_information[i][0] = items[target_index].name;
        targets_information[i][1] = items[target_index].units;
        targets_information[i][2] = items[target_index].description;
    }

    return(targets_information);
}


// const bool& get_display(void) const method

/// Returns true if messages from this class can be displayed on the screen,
/// or false if messages from this class can't be displayed on the screen.

const bool& Variables::get_display(void) const
{
   return(display);   
}


// void set(void) method

/// Sets a variables object with zero variables.

void Variables::set(void)
{
   set_variables_number(0); 

   set_default();
}


// void set(const unsigned&) method

/// Sets a new number of variables in the current object. 
/// All the variables are set as inputs, but the last one, wich is set as targets. 
/// @param new_variables_number Number of variables.

void Variables::set(const unsigned& new_variables_number)
{
   set_variables_number(new_variables_number);

   set_default();
}


// void set(const unsigned&, const unsigned&) method

/// Sets new numbers of of inputs and target variables in the current object. 
/// The total number of variables is the number of inputs plus the number of targets. 
/// The first variables are set as inputs, and last ones are set as targets. 
/// @param inputs_number Number of input variables.
/// @param targets_number Number of target variables.

void Variables::set(const unsigned& inputs_number, const unsigned& targets_number)
{
   const unsigned variables_number = inputs_number + targets_number;

   set_variables_number(variables_number);

   for(unsigned i = 0; i < inputs_number; i++)
   {
      items[i].use = Input;
   }

   for(unsigned i = inputs_number; i < variables_number; i++)
   {
      items[i].use = Target;
   }

   set_default();
}


// void set(const tinyxml2::XMLElement*) method

/// Sets the variables information members from a XML document. 
/// @param variables_document Pointer to a TinyXML document containing the member data.

void Variables::set(const tinyxml2::XMLDocument& variables_document)
{
    set_default();

   from_XML(variables_document);
}


// void set_default(void) method

/// Sets the default values to the variables object:
/// <ul>
/// <li>display: true</li>
/// </ul>

void Variables::set_default(void)
{
   display = true;
}


// void set_items(const Vector<Item>&) method

/// Sets new variable items in this object.
/// @param new_items Vector of item structures to be set.

void Variables::set_items(const Vector<Item>& new_items)
{
    items = new_items;
}


// void set_uses(const Vector<Use>&) method 

/// Sets new uses for the all the variables from a single vector.
/// It does not modify the other information on the variables (name, units or description).
/// @param new_uses Vector of use elements.

void Variables::set_uses(const Vector<Variables::Use>& new_uses)
{
    const unsigned variables_number = get_variables_number();

    for(unsigned i = 0; i < variables_number; i++)
    {
        items[i].use = new_uses[i];
    }
}


// void set_uses(const Vector<std::string>&) method 

/// Sets new uses for the all the variables from a vector of strings.
/// The possible values for that strings are "Input", "Target" and "Unused".
/// @param new_uses Vector of use strings.

void Variables::set_uses(const Vector<std::string>& new_uses)
{
   const unsigned new_variables_number = new_uses.size();

   for(unsigned i = 0; i < new_variables_number; i++)
   {   
      if(new_uses[i] == "Input")
	  {	  
         items[i].use = Input;
	  }
      else if(new_uses[i] == "Target")
	  {	  
         items[i].use = Target;
	  }
      else if(new_uses[i] == "Unused")
       {
          items[i].use = Unused;
       }
      else
	  {
         std::ostringstream buffer;

         buffer << "OpenNN Exception Variables class.\n"
                << "void set_uses(const Vector<std::string>&) method.\n"
                << "Unknown use: " << new_uses[i] <<  "\n";
 
	     throw std::logic_error(buffer.str());
	  }
   }   
}


// void set_use(const unsigned&, const Use&) method

/// Sets the use of a single variable.
/// @param i Index of variable.
/// @param new_use Use for that variable.

void Variables::set_use(const unsigned& i, const Use& new_use)
{
    // Control sentence (if debug)

    #ifndef NDEBUG

    const unsigned variables_number = get_variables_number();

    if(i >= variables_number)
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception Variables class.\n"
               << "void set_use(const unsigned&, const Use&) method.\n"
               << "Index of variable must be less than number of variables.\n";

        throw std::logic_error(buffer.str());
    }

    #endif

    items[i].use = new_use;
}


// void set_use(const unsigned&, const std::string&) method

/// Sets the use of a single variable from a string.
/// The possible values for that string are "Unused", "Input" and "Target".
/// @param i Index of variable.
/// @param new_use Use for that variable.

void Variables::set_use(const unsigned& i, const std::string& new_use)
{
    // Control sentence (if debug)

    #ifndef NDEBUG

    const unsigned variables_number = get_variables_number();

    if(i >= variables_number)
    {
        std::ostringstream buffer;

        buffer << "OpenNN Exception Variables class.\n"
               << "void set_use(const unsigned&, const std::string&) method.\n"
               << "Index of variable must be less than number of variables.\n";

        throw std::logic_error(buffer.str());
    }

    #endif

    if(new_use == "Unused")
    {
       items[i].use = Unused;
    }
    else if(new_use == "Input")
    {
       items[i].use = Input;
    }
    else if(new_use == "Target")
    {
       items[i].use = Target;
    }
    else
    {
       std::ostringstream buffer;

       buffer << "OpenNN Exception Variables class.\n"
              << "void set_use(const std::string&) method.\n"
              << "Unknown use.\n";

       throw std::logic_error(buffer.str());
    }
}


// void set_input(void) method

/// Sets all the variables in the data set as input variables. 

void Variables::set_input(void)
{
    const unsigned variables_number = get_variables_number();

    for(unsigned i = 0; i < variables_number; i++)
    {
        items[i].use = Input;
    }
}


// void set_target(void) method

/// Sets all the variables in the data set as target variables. 

void Variables::set_target(void)
{
    const unsigned variables_number = get_variables_number();

    for(unsigned i = 0; i < variables_number; i++)
    {
        items[i].use = Target;
    }
}


// void set_default_uses(void) method

/// Sets the default uses for the input and target variables:
/// <ul>
/// <li> Input indices: 0, ..., variables number-2.
/// <li> Target indices: variables number-1.
/// </ul>

void Variables::set_default_uses(void)
{
   const unsigned variables_number = get_variables_number();

   if(variables_number == 0)
   {
      return;
   }
   else if(variables_number == 1)
   {
      items[0].use = Unused;
   }
   else
   {
       set_input();

       items[variables_number-1].use = Target;
   }
}


// void set_names(const Vector<std::string>&) method

/// Sets new names for the variables in the data set from a vector of strings. 
/// The size of that vector must be equal to the total number of variables. 
/// @param new_names Name of variables. 

void Variables::set_names(const Vector<std::string>& new_names)
{
    const unsigned variables_number = get_variables_number();

   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned size = new_names.size();

   if(size != variables_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Variables class.\n"
             << "void set_names(const Vector<std::string>&) method.\n"
             << "Size must be equal to number of variables.\n";

	  throw std::logic_error(buffer.str());
   }
   
   #endif

   for(unsigned i = 0; i < variables_number; i++)
   {
       items[i].name = new_names[i];
   }
}


// void set_name(const unsigned&, const std::string&) method

/// This method set the name of a single variable. 
/// If the vector of names is zero the rest of elements are initialized as empty strings. 
/// @param i Index of variable. 
/// @param new_name Name of variable. 

void Variables::set_name(const unsigned& i, const std::string& new_name)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned variables_number = get_variables_number();

   if(i >= variables_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Variables class.\n"
             << "void set_name(const unsigned&, const std::string&) method.\n"
             << "Index of variable must be less than number of variables.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   // Set name of single variable

   items[i].name = new_name;
}


// void set_units(const Vector<std::string>&) method

/// Sets new units for the variables in the data set from a vector of strings. 
/// The size of that vector must be equal to the total number of variables. 
/// @param new_units Units of variables. 

void Variables::set_units(const Vector<std::string>& new_units)
{
    const unsigned variables_number = get_variables_number();

   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned size = new_units.size();

   if(size != variables_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Variables class.\n"
             << "void set_units(const Vector<std::string>&) method.\n"
             << "Size must be equal to number of variables.\n";

	  throw std::logic_error(buffer.str());
   }
   
   #endif

   for(unsigned i = 0; i < variables_number; i++)
   {
       items[i].units = new_units[i];
   }
}


// void set_units(const unsigned&, const std::string&) method

/// This method set the units of a single variable. 
/// If the vector of units is zero the rest of elements are initialized as empty strings. 
/// @param i Index of variable. 
/// @param new_units Units of variable. 

void Variables::set_units(const unsigned& i, const std::string& new_units)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

    const unsigned variables_number = get_variables_number();

   if(i >= variables_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Variables class.\n"
             << "void set_units(const unsigned&, const std::string&) method.\n"
             << "Index of variable must be less than number of variables.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   // Set units of single variable

   items[i].units = new_units;
}


// void set_descriptions(const Vector<std::string>&) method

/// Sets new descriptions for the variables in the data set from a vector of strings. 
/// The size of that vector must be equal to the total number of variables. 
/// @param new_descriptions Description of variables. 

void Variables::set_descriptions(const Vector<std::string>& new_descriptions)
{
    const unsigned variables_number = get_variables_number();

   // Control sentence (if debug)

   #ifndef NDEBUG 

   const unsigned size = new_descriptions.size();

   if(size != variables_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Variables class.\n"
             << "void set_descriptions(const Vector<std::string>&) method.\n"
             << "Size must be equal to number of variables.\n";

	  throw std::logic_error(buffer.str());
   }
   
   #endif

   for(unsigned i = 0; i < variables_number; i++)
   {
       items[i].description = new_descriptions[i];
   }
}


// void set_description(const unsigned&, const std::string&) method

/// This method set the description of a single variable. 
/// If the vector of descriptions is zero the rest of elements are initialized as empty strings. 
/// @param i Index of variable. 
/// @param new_description Description of variable. 

void Variables::set_description(const unsigned& i, const std::string& new_description)
{
   // Control sentence (if debug)

   #ifndef NDEBUG 

    const unsigned variables_number = get_variables_number();

   if(i >= variables_number)
   {
      std::ostringstream buffer;

      buffer << "OpenNN Exception: Variables class.\n"
             << "void set_description(const unsigned&, const std::string&) method.\n"
             << "Index of variable must be less than number of variables.\n";

	  throw std::logic_error(buffer.str());
   }

   #endif

   // Set description of single variable

   items[i].description = new_description;
}


// void set_display(const bool&) method

/// Sets a new display value. 
/// If it is set to true messages from this class are to be displayed on the screen;
/// if it is set to false messages from this class are not to be displayed on the screen.
/// @param new_display Display value.

void Variables::set_display(const bool& new_display)
{
   display = new_display;
}


// void set_variables_number(const unsigned&) method

/// Sets a new number of variables in the variables object.
/// All variables are set as inputs but the last one, which is set as targets. 
/// @param new_variables_number Number of variables. 

void Variables::set_variables_number(const unsigned& new_variables_number)
{
   items.set(new_variables_number);
   set_default_uses();
}


// std::string to_string(void) const method

/// Returns a string representation of the current variables object.

std::string Variables::to_string(void) const
{
   std::ostringstream buffer;

   const unsigned variables_number = get_variables_number();
   const unsigned inputs_number = count_inputs_number();
   const unsigned targets_number = count_targets_number();

   buffer << "Variables information object\n"
          << "Variables number: " << variables_number << "\n"
          << "Inputs number: " << inputs_number << "\n"
          << "Target number: " << targets_number << "\n";

   buffer << "Items:\n";

   const Vector<std::string> uses_string = write_uses();

   for(unsigned i = 0; i < variables_number; i++)
   {
      buffer << "Variable " << i+1 << ":\n"
             << "Name: " << items[i].name << "\n"
             << "Units: " << items[i].units << "\n"
             << "Description: " << items[i].description << "\n"
             << "Use: " << write_use(i) << "\n";
   }

   buffer << "Display: " << display << "\n";

   return(buffer.str());
}


// tinyxml2::XMLDocument* to_XML(void) const method

/// Serializes the variables object into a XML document of the TinyXML library.
/// See the OpenNN manual for more information about the format of this document. 

tinyxml2::XMLDocument* Variables::to_XML(void) const
{
   tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument;

   std::ostringstream buffer;

   // Variables

   tinyxml2::XMLElement* variables_element = document->NewElement("Variables");

   document->InsertFirstChild(variables_element);


   tinyxml2::XMLElement* element = NULL;
   tinyxml2::XMLText* text = NULL;

   const unsigned variables_number = get_variables_number();

   // Variables number
   {
      element = document->NewElement("VariablesNumber");
      variables_element->LinkEndChild(element);

      buffer.str("");
      buffer << variables_number;

      text = document->NewText(buffer.str().c_str());
      element->LinkEndChild(text);
   }

   for(unsigned i = 0; i < variables_number; i++)
   {
       element = document->NewElement("Item");
       element->SetAttribute("Index", i+1);
       variables_element->LinkEndChild(element);

       // Name

       tinyxml2::XMLElement* name_element = document->NewElement("Name");
       element->LinkEndChild(name_element);

       tinyxml2::XMLText* name_text = document->NewText(items[i].name.c_str());
       name_element->LinkEndChild(name_text);

       // Units

       tinyxml2::XMLElement* units_element = document->NewElement("Units");
       element->LinkEndChild(units_element);

       tinyxml2::XMLText* units_text = document->NewText(items[i].units.c_str());
       units_element->LinkEndChild(units_text);

       // Description

       tinyxml2::XMLElement* description_element = document->NewElement("Description");
       element->LinkEndChild(description_element);

       tinyxml2::XMLText* descriptionText = document->NewText(items[i].description.c_str());
       description_element->LinkEndChild(descriptionText);

       // Use

       tinyxml2::XMLElement* use_element = document->NewElement("Use");
       element->LinkEndChild(use_element);

       tinyxml2::XMLText* use_text = document->NewText(write_use(i).c_str());
       use_element->LinkEndChild(use_text);
   }

   // Display
   {
      element = document->NewElement("Display");
      variables_element->LinkEndChild(element);

      buffer.str("");
      buffer << display;

      text = document->NewText(buffer.str().c_str());
      element->LinkEndChild(text);
   }

   return(document);
}


// void from_XML(const tinyxml2::XMLDocument&) method

/// Deserializes a TinyXML document into this variables object.
/// @param document XML document containing the member data.

void Variables::from_XML(const tinyxml2::XMLDocument& document)
{
   std::ostringstream buffer;

   unsigned index = 0;

   // Variables

   const tinyxml2::XMLElement* variables_element = document.FirstChildElement("Variables");

   if(!variables_element)
   {
      buffer << "OpenNN Exception: Variables class.\n"
             << "void from_XML(const tinyxml2::XMLElement*) method.\n"
             << "Pointer to variables element is NULL.\n";

      throw std::logic_error(buffer.str());
   }

   // Variables number

   const tinyxml2::XMLElement* variables_number_element = variables_element->FirstChildElement("VariablesNumber");

   if(!variables_number_element)
   {
      buffer << "OpenNN Exception: Variables class.\n"
             << "void from_XML(const tinyxml2::XMLElement*) method.\n"
             << "Pointer to variables number is NULL.\n";

      throw std::logic_error(buffer.str());
   }

   const unsigned variables_number = atoi(variables_number_element->GetText());

   set_variables_number(variables_number);   

   // Items

   const tinyxml2::XMLElement* start_element = variables_number_element;

   for(unsigned i = 0; i < variables_number; i++)
   {      
      const tinyxml2::XMLElement* item_element = start_element->NextSiblingElement("Item");
      start_element = item_element;

      if(!item_element)
      {
          buffer << "OpenNN Exception: Variables class.\n"
                 << "void from_XML(const tinyxml2::XMLElement*) method.\n"
                 << "Item " << i+1 << " is NULL.\n";

          throw std::logic_error(buffer.str());
      }

     item_element->QueryUnsignedAttribute("Index", &index);

     if(index != i+1)
     {
         buffer << "OpenNN Exception: Variables class.\n"
                << "void from_XML(const tinyxml2::XMLElement*) method.\n"
                << "Index " << index << " is not correct.\n";

         throw std::logic_error(buffer.str());
     }

     // Name

     const tinyxml2::XMLElement* name_element = item_element->FirstChildElement("Name");

     if(!name_element)
     {
        buffer << "OpenNN Exception: Variables class.\n"
               << "void from_XML(const tinyxml2::XMLElement*) method.\n"
               << "Pointer to name element is NULL.\n";

        throw std::logic_error(buffer.str());
     }

     if(name_element->GetText())
     {
        items[index-1].name = name_element->GetText();
     }

     // Units

     const tinyxml2::XMLElement* units_element = item_element->FirstChildElement("Units");

     if(!units_element)
     {
        buffer << "OpenNN Exception: Variables class.\n"
               << "void from_XML(const tinyxml2::XMLElement*) method.\n"
               << "Pointer to units element is NULL.\n";

        throw std::logic_error(buffer.str());
     }

     if(units_element->GetText())
     {
        items[index-1].units = units_element->GetText();
     }

     // Description

     const tinyxml2::XMLElement* description_element = item_element->FirstChildElement("Description");

     if(!description_element)
     {
        buffer << "OpenNN Exception: Variables class.\n"
               << "void from_XML(const tinyxml2::XMLElement*) method.\n"
               << "Pointer to description element is NULL.\n";

        throw std::logic_error(buffer.str());
     }

     if(description_element->GetText())
     {
        items[index-1].description = description_element->GetText();
     }

     // Use

     const tinyxml2::XMLElement* use_element = item_element->FirstChildElement("Use");

     if(!use_element)
     {
        buffer << "OpenNN Exception: Variables class.\n"
               << "void from_XML(const tinyxml2::XMLElement*) method.\n"
               << "Pointer to use element is NULL.\n";

        throw std::logic_error(buffer.str());
     }

     if(use_element->GetText())
     {
        set_use(index-1, use_element->GetText());
     }
   }
}

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
