#include "configuration.h"
/****************************************************************
 * Implementation for the 'Configuration' class.
 * This is class the user will primarily deal with in order
 * to configure the simulation with the data given. All the
 * values found in this class will be used to affect the outcome
 * of the simulation.
 * 
 *
 * Author/copyright:  Duncan Buell. All rights reserved.
 * Used with permission and modified by: Group 4
 *                                       Erik Akeyson
 *                                       Matthew Clapp
 *                                       Harrison Goodman
 *                                       Andy Michels
 *                                       Steve Smero
 * Date: 1 December 2016
**/

static const string kTag = "CONFIG: ";

/****************************************************************
 * Constructor.
**/
Configuration::Configuration() {
}

/****************************************************************
 * Destructor.
**/
Configuration::~Configuration() {
}

/****************************************************************
 * Accessors and mutators.
**/
/****************************************************************
**/
int Configuration::GetMaxServiceSubscript() const {
  return static_cast<int>(actual_service_times_.size()) - 1;
}

/****************************************************************
 * General functions.
**/
/****************************************************************
**/
void Configuration::ReadConfiguration(Scanner& instream) {
/*
* Makes a string on the first line in the file. It then tokenizes 
* the seed as the first integer it encouters. It then sets the election
* day length hours, length second, min and max expected to simulate, the
* time of waiting too long in minutes and lastly the number of 
* iterations. These are all integer values.
*/
  string line;
  ScanLine scanline;

  line = instream.NextLine();
  scanline.OpenString(line);
  seed_ = scanline.NextInt();
  election_day_length_hours_ = scanline.NextInt();
  election_day_length_seconds_ = election_day_length_hours_ * 3600;
  time_to_vote_mean_seconds_ = scanline.NextInt();
  min_expected_to_simulate_ = scanline.NextInt();
  max_expected_to_simulate_ = scanline.NextInt();
  wait_time_minutes_that_is_too_long_ = scanline.NextInt();
  number_of_iterations_ = scanline.NextInt();
/*
* The program then moves to the next line in the file and set the
* first value to an arrival zero double. The rest of the line is 
* the input, which are double values. Then those values are pushed
* onto the vector of arrival fractions.
*/
  
  line = instream.NextLine();
  scanline.OpenString(line);
  arrival_zero_ = scanline.NextDouble();
  for (int sub = 0; sub < election_day_length_hours_; ++sub) {
    double input = scanline.NextDouble();
    arrival_fractions_.push_back(input);
  }

  Scanner service_times_file;
  service_times_file.OpenFile("dataallsorted.txt");
  while (service_times_file.HasNext()) {
    int thetime = service_times_file.NextInt();
    actual_service_times_.push_back(thetime);
  }
}

/****************************************************************
**/
string Configuration::ToString() {
 /*
  * This is a ToString function that will print out and format the
  * the simulation's configuration. Any data that is expressed in
  * seconds will be converted to hours for the user's readability.
  * Additionally, it will offset the arrival fractions, iterate
  * through them, and format them.
  */
  string s = "\n";
  
  s += kTag;
  s += "RN seed:              ";
  s += Utils::Format(seed_, 8) + "\n";
  s += kTag;
  
  s += "Election Day length:  ";
  s += Utils::Format(election_day_length_seconds_, 8) + " =";
  s += Utils::Format(election_day_length_seconds_/3600.0, 8, 2) + " (";
  s += Utils::Format(election_day_length_hours_, 8, 2) + ") hours\n";
  s += kTag;
  
  s += "Time to vote mean:    ";
  s += Utils::Format(time_to_vote_mean_seconds_, 8) + " =";
  s += Utils::Format(time_to_vote_mean_seconds_/60.0, 8, 2) + " minutes\n";
  s += kTag;
  
  s += "Min and max expected voters for this simulation:     ";
  s += Utils::Format(min_expected_to_simulate_, 8);
  s += Utils::Format(max_expected_to_simulate_, 8) + "\n"; 
  s += "Wait time (minutes) that is 'too long': ";
  s += Utils::Format(wait_time_minutes_that_is_too_long_, 8) + "\n";
  s += "Number of iterations to perform: ";
  s += Utils::Format(number_of_iterations_, 4) + "\n";
  s += "Max service time subscript: ";
  s += Utils::Format(GetMaxServiceSubscript(), 6) + "\n";
  
  int offset = 6;
  s += kTag;
  s += Utils::Format(0, 2) + "-" + Utils::Format(0, 2);
  s += " : " + Utils::Format(arrival_zero_, 7, 2) + "\n";
  for (UINT sub = 0; sub < arrival_fractions_.size(); ++sub) {
    s += kTag;
    s += Utils::Format(offset+sub, 2) + "-" + Utils::Format(offset+sub+1, 2);
    s += " : " + Utils::Format(arrival_fractions_.at(sub), 7, 2) + "\n";
  }
  
  s += "\n";
  return s;
}
