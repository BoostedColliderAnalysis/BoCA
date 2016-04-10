#pragma once

#include "fastjet/contrib/Njettiness.hh"

namespace hep
{

enum Mode {EARLY_MASSRATIO_SORT_MASS,
           LATE_MASSRATIO_SORT_MASS,
           EARLY_MASSRATIO_SORT_MODDJADE,
           LATE_MASSRATIO_SORT_MODDJADE,
           TWO_STEP_FILTER
          };

class TopTaggerFixedR
{
public:
    TopTaggerFixedR();

    TopTaggerFixedR(fastjet::PseudoJet jet);

    TopTaggerFixedR(fastjet::PseudoJet jet, double mtmass, double mwmass);

    //run tagger
    void run();

    //settings
    void do_qjets(bool qjets);

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

    void set_pruning_zcut(double zcut);
    void set_pruning_rcut_factor(double rcut_factor);

    void set_debug(bool debug);
    void set_qjets(double q_zcut, double q_dcut_fctr, double q_exp_min, double q_exp_max, double q_rigidity, double q_truncation_fctr);

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
    fastjet::PseudoJet const& t() const;
    fastjet::PseudoJet const& b() const;
    fastjet::PseudoJet const& W() const;
    fastjet::PseudoJet const& W1() const;
    fastjet::PseudoJet const& W2() const;
    std::vector<fastjet::PseudoJet> const& top_subjets() const;
    fastjet::PseudoJet const& j1() const;
    fastjet::PseudoJet const& j2() const;
    fastjet::PseudoJet const& j3() const;
    std::vector<fastjet::PseudoJet> const& top_hadrons() const;
    std::vector<fastjet::PseudoJet> const& hardparts() const;
    fastjet::PseudoJet const& fat_initial();

    void get_setting() const;
    void get_info() const;

    double nsub(fastjet::PseudoJet jet, int order, fastjet::contrib::Njettiness::AxesMode axes = fastjet::contrib::Njettiness::kt_axes, double beta = 1., double R0 = 1.);
    double q_weight();

private:
    bool _do_qjets;

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

    double _q_zcut, _q_dcut_fctr, _q_exp_min, _q_exp_max, _q_rigidity, _q_truncation_fctr;
    fastjet::JetDefinition _qjet_def;

    fastjet::PseudoJet _fat;
    bool _debug;

    bool _is_masscut_passed;
    bool _is_ptmincut_passed;
    bool _is_maybe_top;

    double _delta_top;
    double _djsum;

    double _pruned_mass;
    double _unfiltered_mass;

    double _fw;
    unsigned _parts_size;

    fastjet::PseudoJet _top_candidate;
    fastjet::PseudoJet _W;
    std::vector<fastjet::PseudoJet> _top_subs;
    std::vector<fastjet::PseudoJet> _top_subjets;
    std::vector<fastjet::PseudoJet> _top_hadrons;
    std::vector<fastjet::PseudoJet> _top_parts;

    static bool _first_time;
    double _qweight;

    //internal functions
    void FindHardSubst(fastjet::PseudoJet const& jet, std::vector<fastjet::PseudoJet>& t_parts);
    std::vector<fastjet::PseudoJet> Filtering(const std::vector <fastjet::PseudoJet>& top_constits, const fastjet::JetDefinition& filtering_def);
    void store_topsubjets(std::vector<fastjet::PseudoJet> const& top_subs);
    bool check_mass_criteria(std::vector<fastjet::PseudoJet> const& top_subs) const;
    double perp(fastjet::PseudoJet const& vec, fastjet::PseudoJet const& ref);
    double djademod(fastjet::PseudoJet const& subjet_i, fastjet::PseudoJet const& subjet_j, fastjet::PseudoJet const& ref);

    void print_banner();

};

}
