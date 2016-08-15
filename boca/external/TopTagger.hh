#pragma once

#include "fastjet/JetDefinition.hh"

namespace hep
{

class TopTagger
{

public:

    TopTagger(fastjet::ClusterSequence const& cs, fastjet::PseudoJet const& jet);

    TopTagger(fastjet::ClusterSequence const& cs, fastjet::PseudoJet const& jet, double mtmass, double mwmass);

    void run_tagger();

    bool is_maybe_top() const;
    bool is_masscut_passed() const;
    fastjet::PseudoJet const& top_candidate() const;
    std::vector<fastjet::PseudoJet> const& top_subjets() const;
    std::vector<fastjet::PseudoJet> const& top_hadrons() const;
    unsigned top_count() const;
    std::vector<fastjet::PseudoJet> const& hardparts() const;
    unsigned parts_size() const;
    double delta_top() const;
    const std::vector<std::vector<fastjet::PseudoJet> >& candjets() const;
    void get_setting() const;

    void get_info() const;
    // for setting parameters
    void set_max_subjet_mass(double x);
    void set_mass_drop_threshold(double x);
    void set_top_range(double xmin, double xmax);
    void set_mass_ratio_range(double rmin, double rmax);
    void set_mass_ratio_cut(double m23cut, double m13cutmin, double m13cutmax);
    void set_nfilt(unsigned nfilt);
    void set_filtering_jetalgorithm(fastjet::JetAlgorithm jet_algorithm);
    void set_reclustering_jetalgorithm(fastjet::JetAlgorithm jet_algorithm);
    //
    double cos_theta_h() const;
    double dr_bjj() const;
    std::vector<double> dr_values() const;

private:
    fastjet::ClusterSequence const* _cs;
    const fastjet::PseudoJet _jet;
    const double _mtmass, _mwmass;
    double _mass_drop_threshold;
    double _max_subjet_mass; // stop when subjet mass < 30 GeV
    double _mtmin, _mtmax;
    double _rmin, _rmax;
    double _m23cut, _m13cutmin, _m13cutmax;
    size_t _nfilt;
    // filtering algorithm
    fastjet::JetAlgorithm _jet_algorithm;
    fastjet::JetAlgorithm _jet_algorithm_recluster;

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

    void FindHardSubst(fastjet::PseudoJet const& jet, std::vector<fastjet::PseudoJet>& t_parts);
    std::vector<fastjet::PseudoJet> Filtering(std::vector<fastjet::PseudoJet> const& top_constits, fastjet::JetDefinition const& filtering_def);
    void store_topsubjets(std::vector<fastjet::PseudoJet> const& top_subs);
    bool check_mass_criteria(std::vector<fastjet::PseudoJet> const& top_subs) const;
    double check_cos_theta(fastjet::PseudoJet const& jet, fastjet::PseudoJet const& subj1, fastjet::PseudoJet const& subj2) const;
    fastjet::PseudoJet Sum(std::vector<fastjet::PseudoJet> const&);
    double r_max_3jets(fastjet::PseudoJet const& jet1, fastjet::PseudoJet const& jet2, fastjet::PseudoJet const& jet3) const;
public:
    bool debugg;
};


}
