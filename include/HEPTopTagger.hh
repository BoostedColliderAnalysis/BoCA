#ifndef __HEPTOPTAGGER_HH__
#define __HEPTOPTAGGER_HH__

// using namespace std;
// using namespace fastjet;

# include "fastjet/JetDefinition.hh"
# include "fastjet/ClusterSequence.hh"

using std::vector;
using std::max;
using std::swap;
using std::cout;
using std::endl;
using std::min;

using fastjet::JetAlgorithm;
using fastjet::ClusterSequence;
using fastjet::JetDefinition;
using fastjet::PseudoJet;
using fastjet::cambridge_algorithm;

class HEPTopTagger
{
public:

    HEPTopTagger(const fastjet::ClusterSequence &cs,
                 const fastjet::PseudoJet &jet);

    HEPTopTagger(const fastjet::ClusterSequence &cs,
                 const fastjet::PseudoJet &jet,
                 double mtmass, double mwmass);

    void run_tagger();
    bool is_maybe_top() const {
        return _is_maybe_top;
    }
    bool is_masscut_passed() const {
        return _is_masscut_passed;
    }
    const PseudoJet &top_candidate() const {
        return _top_candidate;
    }
    const vector<PseudoJet> &top_subjets() const {
        return _top_subjets;
    }
    const vector<PseudoJet> &top_hadrons() const {
        return _top_hadrons;
    }
    unsigned top_count() const {
        return _top_count;
    }
    const vector<PseudoJet> &hardparts() const {
        return _top_parts;
    }
    unsigned parts_size() const {
        return _parts_size;
    }
    double delta_top() const {
        return _delta_top;
    }
    const vector<vector<PseudoJet> > &candjets() const {
        return _candjets;
    }
    void get_setting() const;
    void get_info() const;
    // for setting parameters
    void set_max_subjet_mass(double x) {
        _max_subjet_mass = x;
    }
    void set_mass_drop_threshold(double x) {
        _mass_drop_threshold = x;
    }
    void set_top_range(double xmin, double xmax) {
        _mtmin = xmin;
        _mtmax = xmax;
    }
    void set_mass_ratio_range(double rmin, double rmax) {
        _rmin = rmin;
        _rmax = rmax;
    }
    void set_mass_ratio_cut(double m23cut, double m13cutmin, double m13cutmax) {
        _m23cut = m23cut;
        _m13cutmin = m13cutmin;
        _m13cutmax = m13cutmax;
    }
    void set_nfilt(unsigned nfilt) {
        _nfilt = nfilt;
    }
    void set_filtering_jetalgorithm(JetAlgorithm jet_algorithm) {
        _jet_algorithm = jet_algorithm;
    }
    void set_reclustering_jetalgorithm(JetAlgorithm jet_algorithm) {
        _jet_algorithm_recluster = jet_algorithm;
    }
    //
    double cos_theta_h() const;
    double dr_bjj() const;
    vector<double> dr_values() const;

private:
    const ClusterSequence *_cs;
    const PseudoJet _jet;
    const double _mtmass, _mwmass;
    double _mass_drop_threshold;
    double _max_subjet_mass; // stop when subjet mass < 30 GeV
    double _mtmin, _mtmax;
    double _rmin, _rmax;
    double _m23cut, _m13cutmin, _m13cutmax;
    size_t _nfilt;
    // filtering algorithm
    JetAlgorithm _jet_algorithm;
    JetAlgorithm _jet_algorithm_recluster;
    bool debugg;

    bool _is_masscut_passed;
    bool _is_maybe_top;
    double _delta_top;
    unsigned _top_count;
    unsigned _parts_size;
    PseudoJet _top_candidate;
    vector<PseudoJet> _top_subjets;
    vector<PseudoJet> _top_hadrons;
    vector<PseudoJet> _top_parts;
    vector<vector<PseudoJet> > _candjets;

    void FindHardSubst(const PseudoJet &jet, vector<fastjet::PseudoJet> &t_parts);
    vector<PseudoJet> Filtering(const vector <PseudoJet> &top_constits, const JetDefinition &filtering_def);
    void store_topsubjets(const vector<PseudoJet> &top_subs);
    bool check_mass_criteria(const vector<fastjet::PseudoJet> &top_subs) const;
    double check_cos_theta(const PseudoJet &jet, const PseudoJet &subj1, const PseudoJet &subj2) const;
    PseudoJet Sum(const vector<PseudoJet> &);
    double r_max_3jets(const fastjet::PseudoJet &jet1, const fastjet::PseudoJet &jet2,
                       const fastjet::PseudoJet &jet3) const;
};

#endif
