/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.intelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   P R E C I P I T A T E   D I S S O L U T I O N   C L A S S                                                  */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Intelnics - The artificial intelligence company                                                            */
/*   robertolopez@intelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// System includes

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <cmath>

// Examples includes

#include "precipitate_dissolution.h"     


namespace OpenNN
{

// GENERAL CONSTRUCTOR

PrecipitateDissolution::PrecipitateDissolution()       
: MathematicalModel()
{
   set_default();
}


// DESTRUCTOR

PrecipitateDissolution::~PrecipitateDissolution(void) 
{

}


// METHODS

// const double& get_minimum_Vickers_hardness(void) const method

const double& PrecipitateDissolution::get_minimum_Vickers_hardness(void) const
{
   return(minimum_Vickers_hardness);
}


// const double& get_maximum_Vickers_hardness(void) const method

const double& PrecipitateDissolution::get_maximum_Vickers_hardness(void) const
{
   return(maximum_Vickers_hardness);
}


// const double& get_reference_temperature(void) const method

const double& PrecipitateDissolution::get_reference_temperature(void) const
{
   return(reference_temperature);
}


// const double& get_reference_time(void) const method

const double& PrecipitateDissolution::get_reference_time(void) const
{
   return(reference_time);
}


// void set_minimum_Vickers_hardness(const double&) method

void PrecipitateDissolution::set_minimum_Vickers_hardness(const double& newMinimumVickersHardness)
{
   minimum_Vickers_hardness = newMinimumVickersHardness;
}


// void set_maximum_Vickers_hardness(const double&) method

void PrecipitateDissolution::set_maximum_Vickers_hardness(const double& newMaximumVickersHardness)
{
   maximum_Vickers_hardness = newMaximumVickersHardness;
}


// void set_reference_temperature(const double&) method

void PrecipitateDissolution::set_reference_temperature(const double& newReferenceTemperature)
{
   reference_temperature = newReferenceTemperature;
}


// void set_reference_time(const double&) method

void PrecipitateDissolution::set_reference_time(const double& newReferenceTime)
{
   reference_time = newReferenceTime;
}


// void set_default(void) method

void PrecipitateDissolution::set_default(void)
{
   universal_gas_constant = 8.314e-3; // kJ / mol K

   reference_temperature = 0.0; // K
   reference_time = 0.0; // s

   minimum_Vickers_hardness = 0.0;
   maximum_Vickers_hardness = 0.0;

   independent_variables_number = 2;
   dependent_variables_number = 1;

   display = true;
}


// double calculate_full_dissolution_time(const double&, const double&) const method

double PrecipitateDissolution::calculate_full_dissolution_time(const double& effective_activation_energy, const double& temperature) const
{
   return(reference_time*exp((effective_activation_energy/universal_gas_constant)*(1.0/temperature-1.0/reference_temperature)));
}


// double calculate_volumetric_fraction(const double&) const method

double PrecipitateDissolution::calculate_volumetric_fraction(const double& Vickers_hardness) const
{
   return((Vickers_hardness - minimum_Vickers_hardness)/(maximum_Vickers_hardness - minimum_Vickers_hardness));
}


// double calculate_Vickers_hardness(const double&) const method

double PrecipitateDissolution::calculate_Vickers_hardness(const double& volumetric_fraction) const
{
   return(minimum_Vickers_hardness + (maximum_Vickers_hardness-minimum_Vickers_hardness)*(1.0 - volumetric_fraction));
}


// double calculate_normalized_time(void) const method

double PrecipitateDissolution::calculate_normalized_time(const double& time, const double& full_dissolution_time) const
{

   return(log10(time/full_dissolution_time));
}


// Matrix<double> calculate_dependent_variables(const NeuralNetwork&, const Matrix<double>&) const method

Matrix<double> PrecipitateDissolution::calculate_dependent_variables(const NeuralNetwork& neural_network, const Matrix<double>& independent_variables) const
{ 
   const unsigned int rows_number = independent_variables.get_rows_number();

   // Neural network stuff  

   Vector<double> inputs(1);
   Vector<double> outputs(1);

   const IndependentParameters* independent_parameters_pointer = neural_network.get_independent_parameters_pointer();

   const double effective_activation_energy = independent_parameters_pointer->get_parameter(0);

   double time;
   double temperature;

   double full_dissolution_time;

   double normalized_time;

   double volumetric_fraction;

   double Vickers_hardness;

   Matrix<double> dependent_variables(rows_number, 1);

   for(unsigned int i = 0; i < rows_number; i++)
   {
      temperature = 273.16 + independent_variables[i][0];

      time = independent_variables[i][1];

	  full_dissolution_time =  calculate_full_dissolution_time(effective_activation_energy, temperature);

      normalized_time = calculate_normalized_time(time, full_dissolution_time);

	  inputs[0] = normalized_time;

	  outputs = neural_network.calculate_outputs(inputs);

	  volumetric_fraction = outputs[0];

	  Vickers_hardness = calculate_Vickers_hardness(volumetric_fraction);

      dependent_variables[i][0] = Vickers_hardness;
   }

   return(dependent_variables);
}


// double calculate_performance(void) const method
/*
double PrecipitateDissolution::calculate_performance(void) const
{
   Vector<double> normalized_time_data = calculate_normalized_time_data();
   Vector<double> volumetric_fraction_data = calculate_volumetric_fraction_data();

   Vector<double> inputs(1);
   Vector<double> outputs(1);

   Vector<double> volumetric_fraction_model(instances_number);

   double Minkowski_error = 0.0;

   for(unsigned int i = 0; i < instances_number; i++)
   {
      inputs[0] = normalized_time_data[i];
      outputs = neural_network_pointer->calculate_outputs(inputs);
      
      volumetric_fraction_model[i] = outputs[0];

      Minkowski_error += pow(fabs(volumetric_fraction_data[i] - volumetric_fraction_model[i]), Minkowski_parameter);
   }

   double objective = pow(Minkowski_error/(double)instances_number, 1.0/Minkowski_parameter);
  
   return(objective);
}


// void print_Vickers_hardness_test(void) const method

void PrecipitateDissolution::print_Vickers_hardness_test(void) const
{
   std::cout << "Dissolution modeling. Vickers hardness test.\n"
             << "Minimum Vickers hardness:" << minimum_Vickers_hardness << "\n"
             << "Maximum Vickers hardness:" << maximum_Vickers_hardness << "\n"
             << "Reference time [s]:" << reference_time << "\n"
             << "Reference temperature [K]:" << reference_temperature << "\n"
             << "Instances number:" << instances_number << "\n"
             << "Experimental data:\n";
 
   for(unsigned int i = 0; i < instances_number; i++)
   {
      std::cout << temperature_data[i] << " " << time_data[i] << " " << Vickers_hardness_data[i] << "\n";
   }
}


// void print_information(void) const method

void PrecipitateDissolution::print_information(void) const
{
   double effective_activation_energy = neural_network_pointer->get_independent_parameters_pointer()->get_parameter(0);

   std::cout << "Effective activation energy: " << effective_activation_energy << std::endl;
}


// void save_precipitate_dissolution_model(const std::string&) const method

void PrecipitateDissolution::save_precipitate_dissolution_model(const std::string& filename) const
{
   std::ofstream file(filename.c_str());

   // Control sentence

   if(!file.is_open())
   {
      std::cout << "Cannot open precipitate dissolution model data file." << std::endl;
      
      exit(1);
   }

   const unsigned int inputs_number = neural_network_pointer->get_multilayer_perceptron_pointer()->count_inputs_number();
   const Vector<unsigned int> layers_size = neural_network_pointer->get_multilayer_perceptron_pointer()->arrange_layers_perceptrons_numbers();
   const unsigned int outputs_number = neural_network_pointer->get_multilayer_perceptron_pointer()->count_outputs_number();

   const double effective_activation_energy = neural_network_pointer->get_independent_parameters_pointer()->get_parameter(0);

   const Vector<double> normalized_time_data = calculate_normalized_time_data();
   const Vector<double> volumetric_fraction_data = calculate_volumetric_fraction_data();

   Vector<double> inputs(1);
   Vector<double> outputs(1);

   Vector<double> volumetric_fraction_model(instances_number);

   for(unsigned int i = 0; i < instances_number; i++)
   {
      inputs[0] = normalized_time_data[i];
      outputs = neural_network_pointer->calculate_outputs(inputs);

      volumetric_fraction_model[i] = outputs[0];
   }

   // Sort data

   Vector<double> sorted_normalized_time_data = normalized_time_data;

   std::sort(sorted_normalized_time_data.begin(), sorted_normalized_time_data.end(), std::less<double>());

   Vector<double> sorted_volumetric_fraction_data(instances_number);
   Vector<double> sorted_volumetric_fraction_model(instances_number);

   for(unsigned int i = 0; i < instances_number; i++)
   {
      for(unsigned int j = 0; j < instances_number; j++)
      {
         if(normalized_time_data[j] == sorted_normalized_time_data[i])
         {
            sorted_volumetric_fraction_data[i] = volumetric_fraction_data[j];
            sorted_volumetric_fraction_model[i] = volumetric_fraction_model[j];
         }
      }
   }

   file << "% OpenNN. Precipitate Dissolution Model Data File." << std::endl;

   file << "% Network architecture: " << inputs_number << ":" << layers_size << ":" << outputs_number 
        << std::endl;
   
   file << "% Effective activation energy: " << effective_activation_energy << std::endl;

   file << std::endl
        << "% Column data: " << std::endl
        << "% 1. Experimental X" << std::endl
        << "% 2. Experimental Y" << std::endl;

   
   for(unsigned int i = 0; i < instances_number; i++)
   {
     file << normalized_time_data[i] << " " << volumetric_fraction_data[i] << std::endl;
   }

   file << std::endl
       << "% Column data: " << std::endl
       << "% 1. Normalized time (log(t/t*))" << std::endl
       << "% 2. Volumetric fraction (1-f/f0)" << std::endl;

   for(unsigned int i = 0; i < instances_number; i++)
   {
     file << sorted_normalized_time_data[i] << " " << sorted_volumetric_fraction_data[i] << std::endl;
   }

   file.close();
}


// void save_Vickers_hardness_model(const std::string&) const method

void PrecipitateDissolution::save_Vickers_hardness_model(const std::string& filename) const
{
   std::ofstream file(filename);

   // Control sentence

   if(!file.is_open())
   {
      std::cout << std::endl
                << "Cannot open Vickers hardness model data file."
                << std::endl;
      
      exit(1);
   }

   unsigned int inputs_number = neural_network_pointer->get_multilayer_perceptron_pointer()->count_inputs_number();
   Vector<unsigned int> layers_size = neural_network_pointer->get_multilayer_perceptron_pointer()->arrange_layers_perceptrons_numbers();
   unsigned int outputs_number = neural_network_pointer->get_multilayer_perceptron_pointer()->count_outputs_number();

   double effective_activation_energy = neural_network_pointer->get_independent_parameters_pointer()->get_parameter(0);

   Vector<double> normalized_time_data = calculate_normalized_time_data();
   Vector<double> volumetric_fraction_data = calculate_volumetric_fraction_data();

   Vector<double> inputs(1);
   Vector<double> outputs(1);

   Vector<double> volumetric_fraction_model(instances_number);

   for(unsigned int i = 0; i < instances_number; i++)
   {
      inputs[0] = normalized_time_data[i];
      outputs = neural_network_pointer->calculate_outputs(inputs);

      volumetric_fraction_model[i] = outputs[0];
   }

   // Sort data

   Vector<double> sorted_normalized_time_data = normalized_time_data;

   std::sort(sorted_normalized_time_data.begin(), sorted_normalized_time_data.end(), std::less<double>());

   Vector<double> sorted_volumetric_fraction_data(instances_number);
   Vector<double> sorted_volumetric_fraction_model(instances_number);

   for(unsigned int i = 0; i < instances_number; i++)
   {
      for(unsigned int j = 0; j < instances_number; j++)
      {
         if(normalized_time_data[j] == sorted_normalized_time_data[i])
         {
            sorted_volumetric_fraction_data[i] = volumetric_fraction_data[j];
            sorted_volumetric_fraction_model[i] = volumetric_fraction_model[j];
         }
      }
   }

   file << "% OpenNN. Precipitate Dissolution Model Data File." << std::endl;

   file << "% Network architecture: " << inputs_number << ":" << layers_size << ":" << outputs_number 
        << std::endl;
   
   file << "% Effective activation energy: " << effective_activation_energy << std::endl;

   file << std::endl
        << "% Column data: " << std::endl
        << "% 1. Normalized time data (log(t/t*))" << std::endl
        << "% 2. Vickers hardness data" << std::endl;

   
   for(unsigned int i = 0; i < instances_number; i++)
   {
     file << normalized_time_data[i] << " " << Vickers_hardness_data[i] << std::endl;
   }

   file << std::endl
        << "% Column data: " << std::endl
        << "% 1. Sorted normalized time data (log(t/t*))" << std::endl
        << "% 2. Sorted Vickers hardness model" << std::endl;

   for(unsigned int i = 0; i < instances_number; i++)
   {
     file << sorted_normalized_time_data[i] << " " << calculate_Vickers_hardness(sorted_volumetric_fraction_model[i]) << std::endl;
   }

   file.close();
}


// void save_inverse_Vickers_hardness_test(const std::string&) const  method

void PrecipitateDissolution::save_inverse_Vickers_hardness_test(const std::string& filename) const
{
   std::ofstream file(filename.c_str());

   // Control sentence

   if(!file.is_open())
   {
      std::cout << std::endl
                << "Cannot open reverse Vickers hardness test data file."
                << std::endl;
      
      exit(1);
   }

   unsigned int temperatures_number = 7;

   Vector<double> temperature(temperatures_number);

   temperature[0] = 200.0 + 273.16;
   temperature[1] = 250.0 + 273.16;
   temperature[2] = 300.0 + 273.16;
   temperature[3] = 350.0 + 273.16;
   temperature[4] = 400.0 + 273.16;
   temperature[5] = 450.0 + 273.16;
   temperature[6] = 500.0 + 273.16;

   unsigned int points_number = 11;

   Vector<double> time(points_number);

   time[0] = 1.0;
   time[1] = 5.0;
   time[2] = 10.0;
   time[3] = 50.0;
   time[4] = 100.0;
   time[5] = 500.0;
   time[6] = 1000.0;
   time[7] = 5000.0;
   time[8] = 10000.0;
   time[9] = 50000.0;
   time[10] = 100000.0;

   // Calculate and write inverse Vickers hardness test

   for(unsigned int i  = 0; i < points_number; i++)
   {
      file << time[i] << " ";

      for(unsigned int j = 0; j < temperatures_number; j++)
      {
         double full_dissolution_time = calculate_full_dissolution_time(temperature[j]);
          
         Vector<double> inputs(1, log10(time[i]/full_dissolution_time));
         Vector<double> outputs = neural_network_pointer->calculate_outputs(inputs);
             
         double volumetric_fraction = outputs[0];
         double Vickers_hardness = calculate_Vickers_hardness(volumetric_fraction);

         file << Vickers_hardness << " ";
      }
 
      file << std::endl;
   }

   // Close file

   file.close();
}
*/
}


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
