#include "onevoter.h"
/****************************************************************
* Implementation for the 'OneVoter' class.
* This class creates in instance of one voter and will assign
* randomly generated data for the values for the times.
* Since the times are calculated in seconds, there are functions
* to change them to minutes and hours.
*
* Author/copyright:  Duncan Buell. All rights reserved.
* Used with permission and modified by: Group 4
 *                                       Erik Akeyson
 *                                       Matthew Clapp
 *                                       Harrison Goodman
 *                                       Andy Michels
 *                                       Steve Smero
 * Date: 1 December 2016
*
**/

static const string kTag = "ONEVOTER: ";

/****************************************************************
* Constructor.
**/
OneVoter::OneVoter() {
}
/****************************************************************
* Parameters:
* 
*     sequence - an integer number to represent the sequence number
*     arrival_seconds - the time it took for them to arive in seconds
*     duration_seconds - the amount of time it took the voter to vote  
*                        in secs  
**/
OneVoter::OneVoter(int sequence, int arrival_seconds, int duration_seconds) {
  sequence_ = sequence;
  time_arrival_seconds_ = arrival_seconds;
  time_start_voting_seconds_ = 0;
  time_vote_duration_seconds_ = duration_seconds;
  which_station_ = -1;
}

/****************************************************************
**/
OneVoter::~OneVoter() {
}

/****************************************************************
* Accessors and mutators.
**/
/****************************************************************
**/
int OneVoter::GetTimeArrival() const {
  return time_arrival_seconds_;
}

/****************************************************************
**/
int OneVoter::GetTimeWaiting() const {
  return time_waiting_seconds_;
}

/****************************************************************
**/
int OneVoter::GetStationNumber() const {
  return which_station_;
}

/****************************************************************
* General functions.
**/

/****************************************************************
* Function 'AssignStation'
*
* This function will assign a voter to a specific station. It also
* calculates how long it took the voter to vote at the station
* and how long it took them to reach it 
*
* Parameters:
*
*     station_number - an interger value to represent the station number
*     start_time_seconds - The amount of time it took start voting in secs
**/
void OneVoter::AssignStation(int station_number, int start_time_seconds) {
  which_station_ = station_number;
  time_start_voting_seconds_ = start_time_seconds;
  time_done_voting_seconds_ = time_start_voting_seconds_
                            + time_vote_duration_seconds_;
  time_waiting_seconds_ = time_start_voting_seconds_
                        - time_arrival_seconds_;
}

/****************************************************************
**/
int OneVoter::GetTimeDoneVoting() const {
  return time_start_voting_seconds_ + time_vote_duration_seconds_;
}

/****************************************************************
**/
int OneVoter::GetTimeInQ() const {
  return time_start_voting_seconds_ - time_arrival_seconds_;
}

/****************************************************************
**/
string OneVoter::GetTOD(int time_in_seconds) const {
  //  int offset_hours = 6;
  int offset_hours = 0;
  string s = "";
  return this->ConvertTime(time_in_seconds + offset_hours*3600);
}

/****************************************************************
* Parameter: An integer of time in second
*
* This method uses an certain amount of second, calulates how many
* hours and minutes. It then does checking to see if any values are
* under zero, if not, then it prints the hours, second, or minutes.
**/
string OneVoter::ConvertTime(int time_in_seconds) const {
  int hours = 0;
  int minutes = 0;
  int seconds = 0;
  string s = "";

  hours = time_in_seconds / 3600;
  //minutes = (time_in_seconds - 3600 * hours) / 60;
  //seconds = (time_in_seconds - 3600 * hours - 60 * minutes);
  
  //------REVISED CODE ---------------
  
  minutes = time_in_seconds / 60;
  second = time_in_seconds;
  
  //----------------------------------

  s += Utils::Format(time_in_seconds, 6);

  if (hours < 0)
    s += " 00";
  else if (hours < 10)
    s += " 0" + Utils::Format(hours, 1);
  else
    s += " " + Utils::Format(hours, 2);

  if (minutes < 0)
    s += ":00";
  else if (minutes < 10)
    s += ":0" + Utils::Format(minutes, 1);
  else
    s += ":" + Utils::Format(minutes, 2);

  if (seconds < 0)
    s += ":00";
  else if (seconds < 10)
    s += ":0" + Utils::Format(seconds, 1);
  else
    s += ":" + Utils::Format(seconds, 2);

  return s;
} // string OneVoter::ConvertTime(int time_in_seconds) const

/****************************************************************
**/
string OneVoter::ToString() {
  string s = kTag;

  s += Utils::Format(sequence_, 7);
  s += ": ";
  s += Utils::Format(this->GetTOD(time_arrival_seconds_));
  s += " ";
  s += Utils::Format(this->GetTOD(time_start_voting_seconds_));
  s += " ";
  s += Utils::Format(this->ConvertTime(time_vote_duration_seconds_));
  s += " ";
  s += Utils::Format(this->GetTOD(time_start_voting_seconds_ + time_vote_duration_seconds_));
  s += " ";
  s += Utils::Format(this->ConvertTime(GetTimeInQ()));
  s += ": ";
  s += Utils::Format(which_station_, 4);

  return s;
} // string OneVoter::toString()

/****************************************************************
* 
**/
string OneVoter::ToStringHeader() {
  string s = kTag;
  s += "    Seq        Arr           Start             Dur             End            Wait         Stn";
  return s;
}

