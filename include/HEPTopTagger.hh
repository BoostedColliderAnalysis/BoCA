#ifndef __HEPTOPTAGGER_HH__
#define __HEPTOPTAGGER_HH__

# include "fastjet/JetDefinition.hh"
# include "fastjet/ClusterSequence.hh"

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
    const fastjet::PseudoJet &top_candidate() const {
        return _top_candidate;
    }
    const std::vector<fastjet::PseudoJet> &top_subjets() const {
        return _top_subjets;
    }
    const std::vector<fastjet::PseudoJet> &top_hadrons() const {
        return _top_hadrons;
    }
    unsigned top_count() const {
        return _top_count;
    }
    const std::vector<fastjet::PseudoJet> &hardparts() const {
        return _top_parts;
    }
    unsigned parts_size() const {
        return _parts_size;
    }
    double delta_top() const {
        return _delta_top;
    }
    const std::vector<std::vector<fastjet::PseudoJet> > &candjets() const {
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
    void set_filtering_jetalgorithm(fastjet::JetAlgorithm jet_algorithm) {
        _jet_algorithm = jet_algorithm;
    }
    void set_reclustering_jetalgorithm(fastjet::JetAlgorithm jet_algorithm) {
        _jet_algorithm_recluster = jet_algorithm;
    }
    //
    double cos_theta_h() const;
    double dr_bjj() const;
    std::vector<double> dr_values() const;

private:
    const fastjet::ClusterSequence *_cs;
    const fastjet::PseudoJet _jet;
    const double _mtmass, _mwmass;
    double _mass_drop_threshold;
    double _max_subjet_mass; ///> stop when subjet mass < 30 GeV
    double _mtmin, _mtmax;
    double _rmin, _rmax;
    double _m23cut, _m13cutmin, _m13cutmax;
    size_t _nfilt;
    // filtering algorithm
    fastjet::JetAlgorithm _jet_algorithm;
    fastjet::JetAlgorithm _jet_algorithm_recluster;
    bool debugg;

    bool _is_masscut_passed;
    bool _is_maybe_top;
    double _delta_top;
    unsigned _top_count;
    unsigned _parts_size;
    fastjet::PseudoJet _top_candidate;
    std::vector<fastjet::PseudoJet> _top_subjets;
    std::vector<fastjet::PseudoJet> _top_hadrons;
    std::vector<fastjet::PseudoJet> _top_parts;
    std::vector<std::vector<fastjet::PseudoJet> > _candjets;

    void FindHardSubst(const fastjet::PseudoJet &jet, std::vector<fastjet::PseudoJet> &t_parts);
    std::vector<fastjet::PseudoJet> Filtering(const std::vector <fastjet::PseudoJet> &top_constits, const fastjet::JetDefinition &filtering_def);
    void store_topsubjets(const std::vector<fastjet::PseudoJet> &top_subs);
    bool check_mass_criteria(const std::vector<fastjet::PseudoJet> &top_subs) const;
    double check_cos_theta(const fastjet::PseudoJet &jet, const fastjet::PseudoJet &subj1, const fastjet::PseudoJet &subj2) const;
    fastjet::PseudoJet Sum(const std::vector<fastjet::PseudoJet> &);
    double r_max_3jets(const fastjet::PseudoJet &jet1, const fastjet::PseudoJet &jet2,
                       const fastjet::PseudoJet &jet3) const;
};

#endif
