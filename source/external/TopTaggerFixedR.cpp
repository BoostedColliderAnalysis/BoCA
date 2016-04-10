#include "fastjet/tools/Pruner.hh"
#include "fastjet/tools/Filter.hh"

#include "fastjet/contrib/Nsubjettiness.hh"

#include "external/QJetsPlugin.hh"
#include "external/QJetsBaseExtras.hh"
#include "external/TopTaggerFixedR.hh"

namespace hep
{

bool TopTaggerFixedR::_first_time = true;

void TopTaggerFixedR::print_banner()
{
    if (!_first_time) return;
    _first_time = false;

    std::cout << "#--------------------------------------------------------------------------\n";
    std::cout << "#                           HEPTopTagger 2.0                               \n";
    std::cout << "#                                                                          \n";
    std::cout << "# Please cite JHEP 1506 (2015) 203 [arXiv:1503.05921 [hep-ph]]             \n";
    std::cout << "# and JHEP 1010 (2010) 078 [arXiv:1006.2833 [hep-ph]].                     \n";
    std::cout << "# This code is provided without warranty.                                  \n";
    std::cout << "#--------------------------------------------------------------------------\n";
}

//pt wrt a reference std::vector
double TopTaggerFixedR::perp(fastjet::PseudoJet const& vec, fastjet::PseudoJet const& ref)
{
    double ref_ref = ref.px() * ref.px() + ref.py() * ref.py() + ref.pz() * ref.pz();
    double vec_ref = vec.px() * ref.px() + vec.py() * ref.py() + vec.pz() * ref.pz();
    double per_per = vec.px() * vec.px() + vec.py() * vec.py() + vec.pz() * vec.pz();
    if (ref_ref > 0.)
        per_per -= vec_ref * vec_ref / ref_ref;
    if (per_per < 0.)
        per_per = 0.;
    return sqrt(per_per);
}

//modified Jade distance
double TopTaggerFixedR::djademod(fastjet::PseudoJet const& subjet_i, fastjet::PseudoJet const& subjet_j, fastjet::PseudoJet const& ref)
{
    double dj = -1.0;
    double delta_phi = subjet_i.delta_phi_to(subjet_j);
    double delta_eta = subjet_i.eta() - subjet_j.eta();
    double delta_R = sqrt(delta_eta * delta_eta + delta_phi * delta_phi);
    dj = perp(subjet_i, ref) * perp(subjet_j, ref) * pow(delta_R, 4.);
    return dj;
}

//minimal |(m_ij / m_123) / (m_w/ m_t) - 1|
double TopTaggerFixedR::f_rec()
{
    double m12 = (_top_subs[0] + _top_subs[1]).m();
    double m13 = (_top_subs[0] + _top_subs[2]).m();
    double m23 = (_top_subs[1] + _top_subs[2]).m();
    double m123 = (_top_subs[0] + _top_subs[1] + _top_subs[2]).m();

    double fw12 = fabs((m12 / m123) / (_mwmass / _mtmass) - 1);
    double fw13 = fabs((m13 / m123) / (_mwmass / _mtmass) - 1);
    double fw23 = fabs((m23 / m123) / (_mwmass / _mtmass) - 1);

    return std::min(fw12, std::min(fw13, fw23));
}

//find hard substructures
void TopTaggerFixedR::FindHardSubst(fastjet::PseudoJet const& this_jet, std::vector<fastjet::PseudoJet>& t_parts)
{
    fastjet::PseudoJet parent1(0, 0, 0, 0), parent2(0, 0, 0, 0);
    if (this_jet.m() < _max_subjet_mass || !this_jet.validated_cs()->has_parents(this_jet, parent1, parent2)) {
        t_parts.push_back(this_jet);
    } else {
        if (parent1.m() < parent2.m())
            std::swap(parent1, parent2);
        FindHardSubst(parent1, t_parts);
        if (parent1.m() < _mass_drop_threshold * this_jet.m())
            FindHardSubst(parent2, t_parts);
    }
}

//store subjets as std::vector<fastjet::PseudoJet> with [0]->b [1]->W-jet 1 [2]->W-jet 2
void TopTaggerFixedR::store_topsubjets(std::vector<fastjet::PseudoJet> const& top_subs)
{
    _top_subjets.resize(0);
    double m12 = (top_subs[0] + top_subs[1]).m();
    double m13 = (top_subs[0] + top_subs[2]).m();
    double m23 = (top_subs[1] + top_subs[2]).m();
    double dm12 = fabs(m12 - _mwmass);
    double dm13 = fabs(m13 - _mwmass);
    double dm23 = fabs(m23 - _mwmass);

    if (dm23 <= dm12 && dm23 <= dm13) {
        _top_subjets.push_back(top_subs[0]);
        _top_subjets.push_back(top_subs[1]);
        _top_subjets.push_back(top_subs[2]);
    } else if (dm13 <= dm12 && dm13 < dm23) {
        _top_subjets.push_back(top_subs[1]);
        _top_subjets.push_back(top_subs[0]);
        _top_subjets.push_back(top_subs[2]);
    } else if (dm12 < dm23 && dm12 < dm13) {
        _top_subjets.push_back(top_subs[2]);
        _top_subjets.push_back(top_subs[0]);
        _top_subjets.push_back(top_subs[1]);
    }
    _W = _top_subjets[1] + _top_subjets[2];
    return;
}

//check mass plane cuts
bool TopTaggerFixedR::check_mass_criteria(std::vector<fastjet::PseudoJet> const& top_subs) const
{
    bool is_passed = false;
    double m12 = (top_subs[0] + top_subs[1]).m();
    double m13 = (top_subs[0] + top_subs[2]).m();
    double m23 = (top_subs[1] + top_subs[2]).m();
    double m123 = (top_subs[0] + top_subs[1] + top_subs[2]).m();
    if (
        (atan(m13 / m12) > _m13cutmin && _m13cutmax > atan(m13 / m12)
         && (m23 / m123 > _rmin && _rmax > m23 / m123))
        ||
        (((m23 / m123) * (m23 / m123) < 1 - _rmin * _rmin * (1 + (m13 / m12) * (m13 / m12)))
         &&
         ((m23 / m123) * (m23 / m123) > 1 - _rmax * _rmax * (1 + (m13 / m12) * (m13 / m12)))
         &&
         (m23 / m123 > _m23cut))
        ||
        (((m23 / m123) * (m23 / m123) < 1 - _rmin * _rmin * (1 + (m12 / m13) * (m12 / m13)))
         &&
         ((m23 / m123) * (m23 / m123) > 1 - _rmax * _rmax * (1 + (m12 / m13) * (m12 / m13)))
         &&
         (m23 / m123 > _m23cut))
    ) {
        is_passed = true;
    }
    return is_passed;
}

double TopTaggerFixedR::nsub(fastjet::PseudoJet jet, int order, fastjet::contrib::Njettiness::AxesMode axes, double beta, double R0)
{
    fastjet::contrib::Nsubjettiness nsub(order, axes, beta, R0);
    return nsub.result(jet);
}

TopTaggerFixedR::TopTaggerFixedR() : _do_qjets(0),
    _mass_drop_threshold(0.8), _max_subjet_mass(30.),
    _mode(Mode(0)), _mtmass(172.3), _mwmass(80.4), _mtmin(150.), _mtmax(200.), _rmin(0.85 * 80.4 / 172.3), _rmax(1.15 * 80.4 / 172.3),
    _m23cut(0.35), _m13cutmin(0.2), _m13cutmax(1.3), _minpt_tag(200.),
    _nfilt(5), _Rfilt(0.3), _jet_algorithm_filter(fastjet::cambridge_algorithm), _minpt_subjet(0.),
    _jet_algorithm_recluster(fastjet::cambridge_algorithm),
    _zcut(0.1), _rcut_factor(0.5),
    _q_zcut(0.1), _q_dcut_fctr(0.5), _q_exp_min(0.), _q_exp_max(0.), _q_rigidity(0.1), _q_truncation_fctr(0.0),
    _debug(false)
{
    _djsum = 0.;
    _delta_top = 1000000000000.0;
    _pruned_mass = 0.;
    _unfiltered_mass = 0.;
    _top_candidate.reset(0., 0., 0., 0.);
    _parts_size = 0;
    _is_maybe_top = _is_masscut_passed = _is_ptmincut_passed = false;
    _top_subs.clear();
    _top_subjets.clear();
    _top_hadrons.clear();
    _top_parts.clear();
    _qweight = -1.;

}

TopTaggerFixedR::TopTaggerFixedR(const fastjet::PseudoJet jet) : _do_qjets(0),
    _jet(jet), _initial_jet(jet),
    _mass_drop_threshold(0.8), _max_subjet_mass(30.),
    _mode(Mode(0)), _mtmass(172.3), _mwmass(80.4),  _mtmin(150.), _mtmax(200.), _rmin(0.85 * 80.4 / 172.3), _rmax(1.15 * 80.4 / 172.3),
    _m23cut(0.35), _m13cutmin(0.2), _m13cutmax(1.3), _minpt_tag(200.),
    _nfilt(5), _Rfilt(0.3), _jet_algorithm_filter(fastjet::cambridge_algorithm), _minpt_subjet(0.),
    _jet_algorithm_recluster(fastjet::cambridge_algorithm),
    _zcut(0.1), _rcut_factor(0.5),
    _q_zcut(0.1), _q_dcut_fctr(0.5), _q_exp_min(0.), _q_exp_max(0.), _q_rigidity(0.1), _q_truncation_fctr(0.0),
    _fat(jet),
    _debug(false)
{}

TopTaggerFixedR::TopTaggerFixedR(const fastjet::PseudoJet jet,
                                 double mtmass, double mwmass) : _do_qjets(0),
    _jet(jet), _initial_jet(jet),
    _mass_drop_threshold(0.8), _max_subjet_mass(30.),
    _mode(Mode(0)), _mtmass(mtmass), _mwmass(mwmass), _rmin(0.85 * 80.4 / 172.3), _rmax(1.15 * 80.4 / 172.3),
    _m23cut(0.35), _m13cutmin(0.2), _m13cutmax(1.3), _minpt_tag(200.),
    _nfilt(5), _Rfilt(0.3), _jet_algorithm_filter(fastjet::cambridge_algorithm), _minpt_subjet(0.),
    _jet_algorithm_recluster(fastjet::cambridge_algorithm),
    _zcut(0.1), _rcut_factor(0.5),
    _q_zcut(0.1), _q_dcut_fctr(0.5), _q_exp_min(0.), _q_exp_max(0.), _q_rigidity(0.1), _q_truncation_fctr(0.0),
    _fat(jet),
    _debug(false)
{}

void TopTaggerFixedR::run()
{
    print_banner();

    if ((_mode != EARLY_MASSRATIO_SORT_MASS)
            && (_mode != LATE_MASSRATIO_SORT_MASS)
            && (_mode != EARLY_MASSRATIO_SORT_MODDJADE)
            && (_mode != LATE_MASSRATIO_SORT_MODDJADE)
            && (_mode != TWO_STEP_FILTER)) {
        std::cout << "ERROR: UNKNOWN MODE" << std::endl;
        return;
    }

    //Qjets
    qjets::QJetsPlugin _qjet_plugin(_q_zcut, _q_dcut_fctr, _q_exp_min, _q_exp_max, _q_rigidity, _q_truncation_fctr);
    _qjet_def = fastjet::JetDefinition(&_qjet_plugin);
    _qweight = -1;
    std::vector<fastjet::PseudoJet> _q_constits;
    fastjet::ClusterSequence* _qjet_seq;
    fastjet::PseudoJet _qjet;
    if (_do_qjets) {
        _q_constits = _initial_jet.associated_cluster_sequence()->constituents(_initial_jet);
        _qjet_seq = new fastjet::ClusterSequence(_q_constits, _qjet_def);
        _qjet = fastjet::sorted_by_pt(_qjet_seq->inclusive_jets())[0];
        _qjet_seq->delete_self_when_unused();
        qjets::QJetsBaseExtras const* ext = dynamic_cast<qjets::QJetsBaseExtras const*>(_qjet_seq->extras());
        _qweight = ext->weight();
        _jet = _qjet;
        _fat = _qjet;
    }

    //initialization
    _djsum = 0.;
    _delta_top = 1000000000000.0;
    _pruned_mass = 0.;
    _unfiltered_mass = 0.;
    _top_candidate.reset(0., 0., 0., 0.);
    _parts_size = 0;
    _is_maybe_top = _is_masscut_passed = _is_ptmincut_passed = false;
    _top_subs.clear();
    _top_subjets.clear();
    _top_hadrons.clear();
    _top_parts.clear();

    //find hard substructures
    FindHardSubst(_jet, _top_parts);

    if (_top_parts.size() < 3) {
        if (_debug) {
            std::cout << "< 3 hard substructures " << std::endl;
        }
        return; //such events are not interesting
    }

    // Sort subjets-after-unclustering by pT.
    // Necessary so that two-step-filtering can use the leading-three.
    _top_parts = fastjet::sorted_by_pt(_top_parts);

    // loop over triples
    _top_parts = fastjet::sorted_by_pt(_top_parts);
    for (unsigned rr = 0; rr < _top_parts.size(); rr++) {
        for (unsigned ll = rr + 1; ll < _top_parts.size(); ll++) {
            for (unsigned kk = ll + 1; kk < _top_parts.size(); kk++) {

                // two-step filtering
                // This means that we only look at the triplet formed by the
                // three leading-in-pT subjets-after-unclustering.
                if ((_mode == TWO_STEP_FILTER) && rr > 0)
                    continue;
                if ((_mode == TWO_STEP_FILTER) && ll > 1)
                    continue;
                if ((_mode == TWO_STEP_FILTER) && kk > 2)
                    continue;

                //pick triple
                fastjet::PseudoJet triple = fastjet::join(_top_parts[rr], _top_parts[ll], _top_parts[kk]);

                //filtering
                double filt_top_R
                    = std::min(_Rfilt, 0.5 * sqrt(std::min(_top_parts[kk].squared_distance(_top_parts[ll]),
                                                  std::min(_top_parts[rr].squared_distance(_top_parts[ll]),
                                                          _top_parts[kk].squared_distance(_top_parts[rr])))));
                fastjet::JetDefinition filtering_def(_jet_algorithm_filter, filt_top_R);
                fastjet::Filter filter(filtering_def, fastjet::SelectorNHardest(_nfilt) * fastjet::SelectorPtMin(_minpt_subjet));
                fastjet::PseudoJet topcandidate = filter(triple);

                //mass window cut
                if (topcandidate.m() < _mtmin || _mtmax < topcandidate.m()) continue;

                // Sanity cut: can't recluster less than 3 objects into three subjets
                if (topcandidate.pieces().size() < 3)
                    continue;

                // Recluster to 3 subjets and apply mass plane cuts
                fastjet::JetDefinition reclustering(_jet_algorithm_recluster, 3.14);
                fastjet::ClusterSequence*   cs_top_sub = new fastjet::ClusterSequence(topcandidate.pieces(), reclustering);
                std::vector <fastjet::PseudoJet> top_subs = fastjet::sorted_by_pt(cs_top_sub->exclusive_jets(3));
                cs_top_sub->delete_self_when_unused();

                // Require the third subjet to be above the pT threshold
                if (top_subs[2].perp() < _minpt_subjet)
                    continue;

                // Modes with early 2d-massplane cuts
                if (_mode == EARLY_MASSRATIO_SORT_MASS      && !check_mass_criteria(top_subs)) {
                    continue;
                }
                if (_mode == EARLY_MASSRATIO_SORT_MODDJADE  && !check_mass_criteria(top_subs)) {
                    continue;
                }

                //is this candidate better than the other? -> update
                double deltatop = fabs(topcandidate.m() - _mtmass);
                double djsum = djademod(top_subs[0], top_subs[1], topcandidate)
                               + djademod(top_subs[0], top_subs[2], topcandidate)
                               + djademod(top_subs[1], top_subs[2], topcandidate);
                bool better = false;

                // Modes 0 and 1 sort by top mass
                if ((_mode == EARLY_MASSRATIO_SORT_MASS)
                        || (_mode == LATE_MASSRATIO_SORT_MASS)) {
                    if (deltatop < _delta_top)
                        better = true;
                }
                // Modes 2 and 3 sort by modified jade distance
                else if ((_mode == EARLY_MASSRATIO_SORT_MODDJADE)
                         || (_mode == LATE_MASSRATIO_SORT_MODDJADE)) {
                    if (djsum > _djsum)
                        better = true;
                }
                // Mode 4 is the two-step filtering. No sorting necessary as
                // we just look at the triplet of highest pT objects after
                // unclustering
                else if (_mode == TWO_STEP_FILTER) {
                    better = true;
                } else {
                    std::cout << "ERROR: UNKNOWN MODE (IN DISTANCE MEASURE SELECTION)" << std::endl;
                    return;
                }

                if (better) {
                    _djsum = djsum;
                    _delta_top = deltatop;
                    _is_maybe_top = true;
                    _top_candidate = topcandidate;
                    _top_subs = top_subs;
                    store_topsubjets(top_subs);
                    _top_hadrons = topcandidate.constituents();
                    // Pruning
                    double _Rprun = _initial_jet.validated_cluster_sequence()->jet_def().R();
                    fastjet::JetDefinition jet_def_prune(fastjet::cambridge_algorithm, _Rprun);
                    fastjet::Pruner pruner(jet_def_prune, _zcut, _rcut_factor);
                    fastjet::PseudoJet prunedjet = pruner(triple);
                    _pruned_mass = prunedjet.m();
                    _unfiltered_mass = triple.m();

                    //are all criteria fulfilled?
                    _is_masscut_passed = false;
                    if (check_mass_criteria(top_subs)) {
                        _is_masscut_passed = true;
                    }
                    _is_ptmincut_passed = false;
                    if (_top_candidate.pt() > _minpt_tag) {
                        _is_ptmincut_passed = true;
                    }
                }//end better
            }//end kk
        }//end ll
    }//end rr

    return;
}

void TopTaggerFixedR::get_info() const
{
    std::cout << "#--------------------------------------------------------------------------\n";
    std::cout << "#                          TopTagger2 Result" << std::endl;
    std::cout << "#" << std::endl;
    std::cout << "# is top candidate: " << _is_maybe_top << std::endl;
    std::cout << "# mass plane cuts passed: " << _is_masscut_passed << std::endl;
    std::cout << "# top candidate mass: " << _top_candidate.m() << std::endl;
    std::cout << "# top candidate (pt, eta, phi): ("
              << _top_candidate.perp() << ", "
              << _top_candidate.eta() << ", "
              << _top_candidate.phi_std() << ")" << std::endl;
    std::cout << "# top hadrons: " << _top_hadrons.size() << std::endl;
    std::cout << "# hard substructures: " << _parts_size << std::endl;
    std::cout << "# |m - mtop| : " << _delta_top << std::endl;
    std::cout << "# djsum : " << _djsum << std::endl;
    std::cout << "# is consistency cut passed: " << _is_ptmincut_passed << std::endl;
    std::cout << "#--------------------------------------------------------------------------\n";
    return;
}

void TopTaggerFixedR::get_setting() const
{
    std::cout << "#--------------------------------------------------------------------------\n";
    std::cout << "#                         TopTagger2 Settings" << std::endl;
    std::cout << "#" << std::endl;
    std::cout << "# mode: " << _mode << " (0 = EARLY_MASSRATIO_SORT_MASS) " << std::endl;
    std::cout << "#        "         << " (1 = LATE_MASSRATIO_SORT_MASS)  " << std::endl;
    std::cout << "#        "         << " (2 = EARLY_MASSRATIO_SORT_MODDJADE)  " << std::endl;
    std::cout << "#        "         << " (3 = LATE_MASSRATIO_SORT_MODDJADE)  " << std::endl;
    std::cout << "#        "         << " (4 = TWO_STEP_FILTER)  " << std::endl;
    std::cout << "# top mass: " << _mtmass << "    ";
    std::cout << "W mass: " << _mwmass << std::endl;
    std::cout << "# top mass window: [" << _mtmin << ", " << _mtmax << "]" << std::endl;
    std::cout << "# W mass ratio: [" << _rmin << ", " << _rmax << "] (["
              << _rmin* _mtmass / _mwmass << "%, " << _rmax* _mtmass / _mwmass << "%])" << std::endl;
    std::cout << "# mass plane cuts: (m23cut, m13min, m13max) = ("
              << _m23cut << ", " << _m13cutmin << ", " << _m13cutmax << ")" << std::endl;
    std::cout << "# mass_drop_threshold: " << _mass_drop_threshold << "    ";
    std::cout << "max_subjet_mass: " << _max_subjet_mass << std::endl;
    std::cout << "# R_filt: " << _Rfilt << "    ";
    std::cout << "n_filt: " << _nfilt << std::endl;
    std::cout << "# minimal subjet pt: " << _minpt_subjet << std::endl;
    std::cout << "# minimal reconstructed pt: " << _minpt_tag << std::endl;
    std::cout << "# internal jet algorithms (0 = kt, 1 = C/A, 2 = anti-kt): " << std::endl;
    std::cout << "#   filtering: " << _jet_algorithm_filter << std::endl;
    std::cout << "#   reclustering: " << _jet_algorithm_recluster << std::endl;
    std::cout << "#--------------------------------------------------------------------------\n";

    return;
}
double TopTaggerFixedR::q_weight()
{
    return _qweight;
}
fastjet::PseudoJet const& TopTaggerFixedR::fat_initial()
{
    return _fat;
}
std::vector< fastjet::PseudoJet > const& TopTaggerFixedR::hardparts() const
{
    return _top_parts;
}
std::vector< fastjet::PseudoJet > const& TopTaggerFixedR::top_hadrons() const
{
    return _top_hadrons;
}
fastjet::PseudoJet const& TopTaggerFixedR::j3() const
{
    return _top_subs[2];
}
fastjet::PseudoJet const& TopTaggerFixedR::j2() const
{
    return _top_subs[1];
}
fastjet::PseudoJet const& TopTaggerFixedR::j1() const
{
    return _top_subs[0];
}
std::vector< fastjet::PseudoJet > const& TopTaggerFixedR::top_subjets() const
{
    return _top_subjets;
}
fastjet::PseudoJet const& TopTaggerFixedR::W2() const
{
    return _top_subjets[2];
}
fastjet::PseudoJet const& TopTaggerFixedR::W1() const
{
    return _top_subjets[1];
}
fastjet::PseudoJet const& TopTaggerFixedR::W() const
{
    return _W;
}
fastjet::PseudoJet const& TopTaggerFixedR::b() const
{
    return _top_subjets[0];
}
fastjet::PseudoJet const& TopTaggerFixedR::t() const
{
    return _top_candidate;
}
double TopTaggerFixedR::unfiltered_mass() const
{
    return _unfiltered_mass;
}
double TopTaggerFixedR::pruned_mass() const
{
    return _pruned_mass;
}
double TopTaggerFixedR::djsum() const
{
    return _djsum;
}
double TopTaggerFixedR::delta_top() const
{
    return _delta_top;
}
bool TopTaggerFixedR::is_tagged() const
{
    return (_is_masscut_passed && _is_ptmincut_passed);
}
bool TopTaggerFixedR::is_minptcut_passed() const
{
    return _is_ptmincut_passed;
}
bool TopTaggerFixedR::is_masscut_passed() const
{
    return _is_masscut_passed;
}
bool TopTaggerFixedR::is_maybe_top() const
{
    return _is_maybe_top;
}
void TopTaggerFixedR::set_qjets(double q_zcut, double q_dcut_fctr, double q_exp_min, double q_exp_max, double q_rigidity, double q_truncation_fctr)
{
    _q_zcut = q_zcut; _q_dcut_fctr = q_dcut_fctr; _q_exp_min = q_exp_min; _q_exp_max = q_exp_max; _q_rigidity =  q_rigidity; _q_truncation_fctr =  q_truncation_fctr;
}
void TopTaggerFixedR::set_debug(bool debug)
{
    _debug = debug;
}
void TopTaggerFixedR::set_pruning_rcut_factor(double rcut_factor)
{
    _rcut_factor = rcut_factor;
}
void TopTaggerFixedR::set_pruning_zcut(double zcut)
{
    _zcut = zcut;
}
void TopTaggerFixedR::set_top_minpt(double x)
{
    _minpt_tag = x;
}
void TopTaggerFixedR::set_mass_ratio_cut(double m23cut, double m13cutmin, double m13cutmax)
{
    _m23cut = m23cut;
    _m13cutmin = m13cutmin;
    _m13cutmax = m13cutmax;
}
void TopTaggerFixedR::set_mass_ratio_range(double rmin, double rmax)
{
    _rmin = rmin;
    _rmax = rmax;
}
void TopTaggerFixedR::set_fw(double fw)
{
    _rmin = (1. - fw) * _mwmass / _mtmass;
    _rmax = (1. + fw) * _mwmass / _mtmass;
}
void TopTaggerFixedR::set_top_mass_range(double xmin, double xmax)
{
    _mtmin = xmin;
    _mtmax = xmax;
}
void TopTaggerFixedR::set_mw(double x)
{
    _mwmass = x;
}
void TopTaggerFixedR::set_mt(double x)
{
    _mtmass = x;
}
void TopTaggerFixedR::set_mode(Mode mode)
{
    _mode = mode;
}
void TopTaggerFixedR::set_reclustering_jetalgorithm(fastjet::JetAlgorithm jet_algorithm)
{
    _jet_algorithm_recluster = jet_algorithm;
}
void TopTaggerFixedR::set_filtering_jetalgorithm(fastjet::JetAlgorithm jet_algorithm)
{
    _jet_algorithm_filter = jet_algorithm;
}
void TopTaggerFixedR::set_filtering_minpt_subjet(double x)
{
    _minpt_subjet = x;
}
void TopTaggerFixedR::set_filtering_R(double Rfilt)
{
    _Rfilt = Rfilt;
}
void TopTaggerFixedR::set_filtering_n(unsigned int nfilt)
{
    _nfilt = nfilt;
}
void TopTaggerFixedR::set_max_subjet_mass(double x)
{
    _max_subjet_mass = x;
}
void TopTaggerFixedR::set_mass_drop_threshold(double x)
{
    _mass_drop_threshold = x;
}
void TopTaggerFixedR::do_qjets(bool qjets)
{
    _do_qjets = qjets;
}

}
