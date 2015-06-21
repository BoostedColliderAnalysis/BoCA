///////////////////////////////////////////////////////////////////////////////////////
// Example code with Top-Tagger - according to 1006.2833 (T.Plehn, M.Spannowsky, M.Takeuchi, D.Zerwas)    //////////////////
//                                                                   //////////////////
//                                                                   //////////////////
// Code last modified on May 21, 2011                                ///////////////////
// Michihisa Takeuchi      M.Takeuchi@Thphys.uni-heidelberg.de                     ///////////////////
///////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <sstream> 
#include <iomanip>  
#include <cmath>
#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <exception>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <ext/hash_map>

#include "fastjet/PseudoJet.hh"
#include "fastjet/ClusterSequence.hh"
// #include "fastjet/CDFJetCluPlugin.hh"
#include "fastjet/internal/BasicRandom.hh"

using namespace std;

//////////////////
#include "HEPTopTagger.hh"
#include "example.hh"
#include "output_gnuplot_display.hh"

//----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  vector<fastjet::PseudoJet> hadrons;
  
  ifstream fin("sample_event.dat",ifstream::in );  
  ReadEvent(fin,hadrons); 
  ofstream fout("sample_event_display.dat",ifstream::out );   
  ofstream fout2("sample_event_out.dat",ifstream::out );  
  output_vec_pseudojet(fout2,hadrons);

//  jet definition 
  double conesize=1.5;
  fastjet::JetDefinition jet_def(fastjet::cambridge_algorithm,conesize);

  // start of granularization of the hadronic calorimeter to redefine hadrons
  double eta_cell=0.1;
  double phi_cell=0.1;
  double pt_cutoff=0.5;
  vector<fastjet::PseudoJet> gran_hadrons 
    = gran_jets(hadrons,eta_cell,phi_cell,pt_cutoff);

  // run the jet finding; find the hardest jet
  fastjet::ClusterSequence clust_seq(gran_hadrons, jet_def);  
  double ptmin_jet=200.;
  vector<fastjet::PseudoJet> jets
    = sorted_by_pt(clust_seq.inclusive_jets(ptmin_jet));

  unsigned candsizesum=0;
  for(unsigned ijet=0; ijet<jets.size(); ijet++)
    {
      double topmass=172.3;
      double wmass=80.4;
      HEPTopTagger cm_toptag(clust_seq,jets[ijet],topmass,wmass);
      cm_toptag.set_top_range(150.,200.);
      cout<< "========= Top Tagger ============" << endl;
      cm_toptag.run_tagger();
      cout<< "-------- setting  --------" << endl;
      cm_toptag.get_setting();
      cout<< "-------- resutls  --------" << endl;
      cm_toptag.get_info();

      if(cm_toptag.is_masscut_passed()){
	cout << "### masscut_passed ###" << endl;
	PseudoJet top=cm_toptag.top_candidate();
	PseudoJet b=cm_toptag.top_subjets().at(0);
	PseudoJet W1=cm_toptag.top_subjets().at(1);
	PseudoJet W2=cm_toptag.top_subjets().at(2);
	cout << "top mass: " << top.m() << endl;
	cout << "bottom mass: "<< b.m() << endl;
	cout << "W mass: "<< (W1+W2).m() << endl;
	// for event display
	set_header_for_display(fout);
	circle(fout,top,0.1,1);
	circle(fout,b,0.1,2);
	circle(fout,W1,0.1,3);
	circle(fout,W2,0.1,3);
	set_footer_for_display(fout);
      }

    } // end of top tagger
  
  //*********************
  return 0;  // end of main  
}
