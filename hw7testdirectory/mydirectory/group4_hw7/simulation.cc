#include "simulation.h"
/****************************************************************
 * Implementation for the 'Simulation' class.
 * This class is the one running the whole simulation for the
 * program. It will iterate through the precincts and simulate
 * all of them. However, OnePct does most of the simulation work,
 * but this class will simulate all precincts.
 *
 * Author/copyright:  Duncan Buell
 * Used with permission and modified by: Group 4
 *                                       Erik Akeyson
 *                                       Matthew Clapp
 *                                       Harrison Goodman
 *                                       Andy Michels
 *                                       Steve Smero
 * Date: 1 December 2016
*
**/

static const string kTag = "SIM: ";

/****************************************************************
* Constructor.
**/
Simulation::Simulation() {
}

/****************************************************************
* Destructor.
**/
Simulation::~Simulation() {
}

/****************************************************************
* Accessors and mutators.
**/

/****************************************************************
* General functions.
**/
void Simulation::ReadPrecincts(Scanner& infile) {
  while (infile.HasNext()) {
    OnePct new_pct;
    new_pct.ReadData(infile);
    pcts_[new_pct.GetPctNumber()] = new_pct;
  } // while (infile.HasNext()) {
} // void Simulation::ReadPrecincts(Scanner& infile) {
/****************************************************************
* Function 'Run Simulation'
*
* Parameters:
*     config -
*     random - An instance of a MyRandom class
*     out_stream - The output stream 
* 
* This function iterates threw the map of OnePct and its going to get each 
* expected voter for each pct. It does checking to make sure it is not
* less than that minimum expected and larger than the expected maximum.
**/
void Simulation::RunSimulation(const Configuration& config,
                               MyRandom& random, ofstream& out_stream) {
  string outstring = "XX";
  int pct_count_this_batch = 0;
  for (auto iterPct = pcts_.begin(); iterPct != pcts_.end(); ++iterPct) {
    OnePct pct = iterPct->second;
    int expected_voters = pct.GetExpectedVoters();
    if ((expected_voters <=  config.min_expected_to_simulate_) ||
        (expected_voters >   config.max_expected_to_simulate_)) {
      continue;
    }

    outstring = kTag + "RunSimulation for pct " + "\n";
    outstring += kTag + pct.ToString() + "\n";
    Utils::Output(outstring, out_stream, Utils::log_stream);

    ++pct_count_this_batch;
    pct.RunSimulationPct(config, random, out_stream);

    //    break; // we only run one pct right now
  } // for(auto iterPct = pcts_.begin(); iterPct != pcts_.end(); ++iterPct)

  outstring = kTag + "PRECINCT COUNT THIS BATCH "
            + Utils::Format(pct_count_this_batch, 4) + "\n";
  //  Utils::Output(outstring, out_stream);
  Utils::Output(outstring, out_stream, Utils::log_stream);
  //out_stream << outstring << endl;
  //out_stream.flush();
  //Utils::log_stream << outstring << endl;
  //Utils::log_stream.flush();

} // void Simulation::RunSimulation()

/****************************************************************
* Usual 'ToString'.
**/
string Simulation::ToString() {
  string s = "";

  for (auto iterPct = pcts_.begin(); iterPct != pcts_.end(); ++iterPct) {
    s += kTag + (iterPct->second).ToString() + "\n";
  }

  return s;
} // string Simulation::ToString()

