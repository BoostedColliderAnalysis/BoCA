#pragma once

#include "external/TopTaggerFixedR.hh"

namespace hep
{

class TopTagger2
{

public:
  
    TopTagger2();

    TopTagger2(const fastjet::PseudoJet& jet);

    TopTagger2(const fastjet::PseudoJet& jet, double mtmass, double mwmass );

    //run tagger
    void run();

    //get information
    bool is_maybe_top() const;
    bool is_masscut_passed() const;
    bool is_minptcut_passed() const;
    bool is_tagged() const;

    double delta_top() const;
    double djsum() const;
    double pruned_mass() const;
    double unfiltered_mass() const;

    double f_rec();
    const fastjet::PseudoJet& t() const;
    const fastjet::PseudoJet& b() const;
    const fastjet::PseudoJet& W() const;
    const fastjet::PseudoJet& W1() const;
    const fastjet::PseudoJet& W2() const;
    const std::vector<fastjet::PseudoJet>& top_subjets() const;
    const fastjet::PseudoJet& j1() const;
    const fastjet::PseudoJet& j2() const;
    const fastjet::PseudoJet& j3() const;
    const std::vector<fastjet::PseudoJet>& top_hadrons() const;
    const std::vector<fastjet::PseudoJet>& hardparts() const;
    const fastjet::PseudoJet& fat_initial();
    const fastjet::PseudoJet& fat_Ropt();
    TopTaggerFixedR TopTagger2agger(int i);

    double Ropt() const;
    double Ropt_calc() const;

    int optimalR_type();
    double nsub_unfiltered(int order, fastjet::contrib::Njettiness::AxesMode axes = fastjet::contrib::Njettiness::kt_axes, double beta = 1., double R0 = 1.);
    double nsub_filtered(int order, fastjet::contrib::Njettiness::AxesMode axes = fastjet::contrib::Njettiness::kt_axes, double beta = 1., double R0 = 1.);

    void get_setting() const;;
    void get_info() const;;

    double q_weight();

    //settings
    void do_optimalR(bool optimalR);

    void set_mass_drop_threshold(double x);
    void set_max_subjet_mass(double x);

    void set_filtering_n(unsigned nfilt);
    void set_filtering_R(double Rfilt);
    void set_filtering_minpt_subjet(double x);
    void set_filtering_jetalgorithm(fastjet::JetAlgorithm jet_algorithm);

    void set_reclustering_jetalgorithm(fastjet::JetAlgorithm jet_algorithm);

    void set_mode(enum Mode mode);
    void set_mt(double x);
    void set_mw(double x);
    void set_top_mass_range(double xmin, double xmax);
    void set_fw(double fw);
    void set_mass_ratio_range(double rmin, double rmax);
    void set_mass_ratio_cut(double m23cut, double m13cutmin, double m13cutmax);
    void set_top_minpt(double x);

    void set_optimalR_max(double x);
    void set_optimalR_min(double x);
    void set_optimalR_step(double x);
    void set_optimalR_threshold(double x);

    void set_filtering_optimalR_calc_R(double x);
    void set_filtering_optimalR_calc_n(unsigned x);
    void set_optimalR_calc_fun(double(*f)(double));

    void set_optimalR_type_top_mass_range(double x, double y);
    void set_optimalR_type_fw(double x);
    void set_optimalR_type_max_diff(double x);

    void set_filtering_optimalR_pass_R(double x);
    void set_filtering_optimalR_pass_n(unsigned x);
    void set_filtering_optimalR_fail_R(double x);
    void set_filtering_optimalR_fail_n(unsigned x);

    void set_pruning_zcut(double zcut);
    void set_pruning_rcut_factor(double rcut_factor);

    void set_debug(bool debug);
    void do_qjets(bool qjets);
    void set_qjets(double q_zcut, double q_dcut_fctr, double q_exp_min, double q_exp_max, double q_rigidity, double q_truncation_fctr);


private:
    bool _do_optimalR, _do_qjets;

    fastjet::PseudoJet _jet;
    fastjet::PseudoJet _initial_jet;

    double _mass_drop_threshold;
    double _max_subjet_mass;

    Mode _mode;
    double _mtmass, _mwmass;
    double _mtmin, _mtmax;
    double _rmin, _rmax;
    double _m23cut, _m13cutmin, _m13cutmax;
    double _minpt_tag;

    unsigned _nfilt;
    double _Rfilt;
    fastjet::JetAlgorithm _jet_algorithm_filter;
    double _minpt_subjet;

    fastjet::JetAlgorithm _jet_algorithm_recluster;

    double _zcut;
    double _rcut_factor;

    double _max_fatjet_R, _min_fatjet_R, _step_R, _optimalR_threshold;

    double  _R_filt_optimalR_calc, _N_filt_optimalR_calc;
    double(*_r_min_exp_function)(double);

    double _optimalR_mmin, _optimalR_mmax, _optimalR_fw, _R_opt_calc, _R_opt_diff;
    double _R_filt_optimalR_pass, _N_filt_optimalR_pass, _R_filt_optimalR_fail, _N_filt_optimalR_fail;

    double _q_zcut, _q_dcut_fctr, _q_exp_min, _q_exp_max, _q_rigidity, _q_truncation_fctr;
    fastjet::JetDefinition _qjet_def;

    fastjet::PseudoJet _fat, _filt_fat;
    std::map<int, int> _n_small_fatjets;
    std::map<int, TopTaggerFixedR> _TopTagger2;
    TopTaggerFixedR _TopTagger2_opt;

    int _Ropt;

    bool _debug;
    double _qweight;

    void UnclusterFatjets(const std::vector<fastjet::PseudoJet>& big_fatjets, std::vector<fastjet::PseudoJet>& small_fatjets, const fastjet::ClusterSequence& cs, const double small_radius);

};

}

// int main(int argc, char *argv[])
// {
//   vector<fastjet::PseudoJet> hadrons;
//
//   //  jet definition
//   double conesize=1.5;
//   fastjet::JetDefinition jet_def(fastjet::cambridge_algorithm,conesize);
//
//   // Read input and convert MeV->GeV
//   ifstream fin("input.dat",ifstream::in );
//   vector<fastjet::PseudoJet> input_clusters(0);
//   while(!fin.eof()){
//     double x,y,z,e;
//     fastjet::PseudoJet p;
//     fin >> x >> y >> z >> e;
//     if(!fin.eof()){
//       p.reset(x/1000., y/1000., z/1000., e/1000.);
//       input_clusters.push_back(p);
//     }
//   }
//   cout << "ReadEvent: " << input_clusters.size() << " particles are read" << endl;
//
//   // run the jet finding; find the hardest jet
//   fastjet::ClusterSequence clust_seq(input_clusters, jet_def);
//   double ptmin_jet=200.;
//   vector<fastjet::PseudoJet> jets = sorted_by_pt(clust_seq.inclusive_jets(ptmin_jet));
//
//
//   for(unsigned ijet=0; ijet<jets.size(); ijet++)
//   {
//     HEPTopTagger::HEPTopTagger tagger(jets[ijet]);
//
//     // Unclustering, Filtering & Subjet Settings
//     tagger.set_max_subjet_mass(30.);
//     tagger.set_mass_drop_threshold(0.8);
//     tagger.set_filtering_R(0.3);
//     tagger.set_filtering_n(5);
//     tagger.set_filtering_minpt_subjet(30.);
//
//     // How to select among candidates
//     tagger.set_mode(HEPTopTagger::TWO_STEP_FILTER);
//
//     // Requirements to accept a candidate
//     tagger.set_top_minpt(200);
//     tagger.set_top_mass_range(150., 200.);
//     tagger.set_fw(0.15);
//
//     // Run the tagger
//     tagger.run();
//
//     // Look at output if we have a tag:
//     if (tagger.is_tagged()){
//       cout << "Input fatjet: " << ijet << "  pT = " << jets[ijet].perp() << std::endl;
//       cout << "Output: pT = " << tagger.t().perp() << " Mass = " << tagger.t().m() << " f_rec = " << tagger.f_rec() << std::endl;
//     }
//
//   } // end of top tagger
//
//   //*********************
//   return 0;  // end of main
// }

