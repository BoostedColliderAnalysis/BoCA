#pragma once

#include "fastjet/JetDefinition.hh"

namespace qjets
{

class QJetsPlugin: public fastjet::JetDefinition::Plugin
{
private:
    double _zcut, _dcut_fctr, _exp_min, _exp_max, _rigidity, _truncation_fctr;
    bool _rand_seed_set;
    unsigned int _seed;
    int _truncated_length;
public:
    QJetsPlugin(double zcut, double dcut_fctr, double exp_min, double exp_max, double rigidity, double truncation_fctr = 0.);
    void SetRandSeed(unsigned int seed); /* In case you want reproducible behavior */
    double R() const;
    std::string description() const;
    void run_clustering(fastjet::ClusterSequence& cs) const;
};

}

// /*
//  *    Take cells from an event, cluster them into jets, and perform Q-jet pruning on the hardest one
//  *
//  *    Example usage: ./example sample_data/ww_1.txt sample_output/ww_1_out.txt
//  *
//  *    The main parameters governing the behavior of the algorithm are
//  * zcut: this is the z-cut used in the pruning algorithm (typically 0.1 or 0.15)
//  * dcut_fctr: this is used in determining the angular dcut used in pruning.
//  *      as in the pruning algorithm, dcut = dcut_fctr * 2 m / pT (dcut_fctr is typically 0.5)
//  * exp_min and exp_max determine the form of d_ij used in clustering the jet
//  *      we have d_ij = min(pTi,pTj)^exp_min * max(pTi,pTj)^exp_max * R_ij^2
//  *      so for kT clustering, (exp_min,exp_max) = (2,0), while for C/A clustering they are (0,0)
//  * rigidity: this determines how close the algorithm is to "classical" C/A or kT. This
//  *      is denoted as \alpha in the Qjets paper
//  */
// #include "fastjet/ClusterSequence.hh"
// #include "fastjet/PseudoJet.hh"
// #include "QjetsPlugin.h"
// #include <iostream>
// #include <sstream>
// #include <vector>
// #include <fstream>
// #include <algorithm>
//
// using namespace std;
//
// void print_jets(fastjet::ClusterSequence const&, const vector<fastjet::PseudoJet>&);
//
//
// double mean(vector<double>& masses)
// {
//     double ret(0.);
//     for (vector<double>::iterator it = masses.begin(); it != masses.end(); it++)
//         ret += (*it);
//     return ret / masses.size();
// }
//
// double var(vector<double>& masses)
// {
//     double ret(0.), avg(mean(masses));
//     for (vector<double>::iterator it = masses.begin(); it != masses.end(); it++)
//         ret += ((*it) - avg) * ((*it) - avg);
//     return ret / masses.size();
// }
//
// int main(int argc, char** argv)
// {
//     vector<fastjet::PseudoJet> input_particles;
//
//     if (argc != 3) {
//         cout << "Usage: example input_file output_file" << endl;
//         exit(0);
//     }
//
//     ifstream infile(argv[1]);
//     if (!infile.good()) {
//         cout << "Can't open " << argv[1] << endl;
//         exit(0);
//     }
//
//     ofstream outfile(argv[2]);
//     if (!outfile.is_open()) {
//         cout << "Can't open " << argv[2] << endl;
//         exit(0);
//     }
//
//     // read in input particles from the file
//     double px, py , pz, E;
//     while (infile >> px >> py >> pz >> E)
//         input_particles.push_back(fastjet::PseudoJet(px, py, pz, E));
//
//     // set the initial jet radius
//     double jetR = 1.;
//
//     fastjet::JetDefinition jet_def(fastjet::antikt_algorithm, jetR, fastjet::E_scheme, fastjet::Best);
//     fastjet::ClusterSequence clust_seq(input_particles, jet_def);
//     vector<fastjet::PseudoJet> inclusive_jets = clust_seq.inclusive_jets();
//
//     cout << endl <<  "============================================" << endl;
//     cout << "\tJets found in initial clustering" << endl;
//     cout << "============================================" << endl << endl;;
//
//     print_jets(clust_seq, inclusive_jets);
//     cout << "============================================" << endl;
//
//
//     // Now recluster hardest jet many times using path-integral-pruning
//     double zcut(0.1), dcut_fctr(0.5), exp_min(0.), exp_max(0.), rigidity(0.1);
//     double truncation_fctr(0.0);
//
//     QjetsPlugin qjet_plugin(zcut, dcut_fctr, exp_min, exp_max, rigidity, truncation_fctr);
//     fastjet::JetDefinition qjet_def(&qjet_plugin);
//
//     vector<fastjet::PseudoJet> constits = clust_seq.constituents(sorted_by_pt(inclusive_jets)[0]);
//
//     vector<double> masses;
//
//     for (unsigned int i = 0 ; i < 100000 ; i++) {
//         if (i % 100 == 0)
//             cout << i << endl;
//         fastjet::ClusterSequence qjet_seq(constits, qjet_def);
//         vector<fastjet::PseudoJet> inclusive_jets2 = sorted_by_pt(qjet_seq.inclusive_jets());
//         outfile << inclusive_jets2[0].m() << endl;
//         masses.push_back(inclusive_jets2[0].m());
//     }
//
//     cout << endl << endl << "Pruned masses saved in file " << argv[2] << endl << endl;
//     cout << "Mean mass: " << mean(masses) << endl;
//     cout << "Mass variance: " << var(masses) << endl;
//
//     infile.close();
//     outfile.close();
// }
//
// void print_jets(fastjet::ClusterSequence const& clust_seq, const vector<fastjet::PseudoJet>& jets)
// {
//
//     // sort jets into increasing pt
//     vector<fastjet::PseudoJet> sorted_jets = sorted_by_pt(jets);
//
//     // label the columns
//     printf("%5s %15s %15s %15s %15s %15s %15s\n", "jet #", "rapidity",
//            "phi", "pt", "m", "e", "n constituents");
//
//     // print out the details for each jet
//     for (unsigned int i = 0; i < sorted_jets.size(); i++) {
//         int n_constituents = clust_seq.constituents(sorted_jets[i]).size();
//         printf("%5u %15.8f %15.8f %15.8f %15.8f %15.8f %8u\n",
//                i, sorted_jets[i].rap(), sorted_jets[i].phi(),
//                sorted_jets[i].perp(), sorted_jets[i].m(), sorted_jets[i].e(), n_constituents);
//     }
// }
