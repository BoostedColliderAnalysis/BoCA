#include "hep/TopTagger.hh"
#include "boca/fastjet/ClusterSequence.hh"
#include "fastjet/ClusterSequence.hh"

namespace hep
{

double TopTagger::cos_theta_h() const
{
    return check_cos_theta(_top_candidate, _top_subjets[1], _top_subjets[2]); // m23 is closest to mW
}

double TopTagger::dr_bjj() const
{
    if (_top_subjets.size() != 3) {
        return -1;
    }
    return r_max_3jets(_top_subjets[0], _top_subjets[1], _top_subjets[2]);
}

std::vector<double> TopTagger::dr_values() const
{
    std::vector<double> dr_values;
    dr_values.push_back(sqrt(_top_subjets[1].squared_distance(_top_subjets[2])));
    dr_values.push_back(sqrt(_top_subjets[0].squared_distance(_top_subjets[2])));
    dr_values.push_back(sqrt(_top_subjets[0].squared_distance(_top_subjets[1])));
    return dr_values;
}

double TopTagger::r_max_3jets(fastjet::PseudoJet const& jet1, fastjet::PseudoJet const& jet2, fastjet::PseudoJet const& jet3) const
{
    fastjet::PseudoJet jet12, jet13, jet23;
    jet12 = jet1 + jet2;
    jet13 = jet1 + jet3;
    jet23 = jet2 + jet3;

    auto a = sqrt(jet1.squared_distance(jet2));
    auto b = sqrt(jet2.squared_distance(jet3));
    auto c = sqrt(jet3.squared_distance(jet1));
    auto dR1 = a, dR2 = a;

    if (a <= b && a <= c) {
        dR1 = a;
        dR2 = sqrt(jet12.squared_distance(jet3));
    };
    if (b < a && b <= c) {
        dR1 = b;
        dR2 = sqrt(jet23.squared_distance(jet1));
    };
    if (c < a && c < b) {
        dR1 = c;
        dR2 = sqrt(jet13.squared_distance(jet2));
    };
    return std::max(dR1, dR2);
}

double TopTagger::check_cos_theta(fastjet::PseudoJet const& jet, fastjet::PseudoJet const& subj1, fastjet::PseudoJet const& subj2) const
{
    // the two jets of interest: top and lower-pt prong of W
    fastjet::PseudoJet W2;
    auto top = jet;

    if (subj1.perp2() < subj2.perp2()) {
        W2 = subj1;
    } else {
        W2 = subj2;
    }

    // transform these jets into jets in the rest frame of the W
    W2.unboost(subj1 + subj2);
    top.unboost(subj1 + subj2);

    auto csthet = (W2.px() * top.px() + W2.py() * top.py() + W2.pz() * top.pz()) / sqrt(W2.modp2() * top.modp2());
    return (csthet);
}

void TopTagger::FindHardSubst(fastjet::PseudoJet const& this_jet, std::vector<fastjet::PseudoJet>& t_parts)
{
    fastjet::PseudoJet parent1(0, 0, 0, 0), parent2(0, 0, 0, 0);
    if (this_jet.m() < _max_subjet_mass || !_cs->has_parents(this_jet, parent1, parent2)) {
        t_parts.push_back(this_jet);
    } else {
        if (parent1.m() < parent2.m()) std::swap(parent1, parent2);

        FindHardSubst(parent1, t_parts);

        if (parent1.m() < _mass_drop_threshold * this_jet.m()) {
            FindHardSubst(parent2, t_parts);
        }
    }
}

void TopTagger::store_topsubjets(std::vector<fastjet::PseudoJet> const& top_subs)
{
    _top_subjets.resize(0);
    auto m12 = (top_subs[0] + top_subs[1]).m();
    auto m13 = (top_subs[0] + top_subs[2]).m();
    auto m23 = (top_subs[1] + top_subs[2]).m();
//     double m123 = (top_subs[0] + top_subs[1] + top_subs[2]).m();
    auto dm12 = std::abs(m12 - _mwmass);
    auto dm13 = std::abs(m13 - _mwmass);
    auto dm23 = std::abs(m23 - _mwmass);
    //double dm_min=std::min(dm12,std::min(dm13,dm23));
    if (dm23 <= dm12 && dm23 <= dm13) {
        _top_subjets.push_back(top_subs[0]); //supposed to be b
        _top_subjets.push_back(top_subs[1]); //W-jet 1
        _top_subjets.push_back(top_subs[2]); //W-jet 2
    } else if (dm13 <= dm12 && dm13 < dm23) {
        _top_subjets.push_back(top_subs[1]); //supposed to be b
        _top_subjets.push_back(top_subs[0]); //W-jet 1
        _top_subjets.push_back(top_subs[2]); //W-jet 2
    } else if (dm12 < dm23 && dm12 < dm13) {
        _top_subjets.push_back(top_subs[2]); //supposed to be b
        _top_subjets.push_back(top_subs[0]); //W-jet 1
        _top_subjets.push_back(top_subs[1]); //W-jet 2
    }
    return;
}

bool TopTagger::check_mass_criteria(std::vector<fastjet::PseudoJet> const& top_subs) const
{
    auto is_passed = false;
    auto m12 = (top_subs[0] + top_subs[1]).m();
    auto m13 = (top_subs[0] + top_subs[2]).m();
    auto m23 = (top_subs[1] + top_subs[2]).m();
    auto m123 = (top_subs[0] + top_subs[1] + top_subs[2]).m();
    if (
        (atan(m13 / m12) > _m13cutmin && _m13cutmax > atan(m13 / m12)
         && (m23 / m123 > _rmin && _rmax > m23 / m123))
        ||
        (((m23 / m123) * (m23 / m123) < 1 - _rmin * _rmin * (1 + (m13 / m12) * (m13 / m12))) &&
         ((m23 / m123) * (m23 / m123) > 1 - _rmax * _rmax * (1 + (m13 / m12) * (m13 / m12))) &&
         (m23 / m123 > _m23cut))
        ||
        (((m23 / m123) * (m23 / m123) < 1 - _rmin * _rmin * (1 + (m12 / m13) * (m12 / m13))) &&
         ((m23 / m123) * (m23 / m123) > 1 - _rmax * _rmax * (1 + (m12 / m13) * (m12 / m13))) &&
         (m23 / m123 > _m23cut))
    ) {
        is_passed = true;
    }
    return is_passed;
}

TopTagger::TopTagger(fastjet::ClusterSequence const& cs, fastjet::PseudoJet const& jet) :
    _cs(&cs), _jet(jet), _mtmass(172.3), _mwmass(80.4),
    _mass_drop_threshold(0.8), _max_subjet_mass(30.),
    _mtmin(172.3 - 25.), _mtmax(172.3 + 25.), _rmin(0.85 * 80.4 / 172.3), _rmax(1.15 * 80.4 / 172.3),
    _m23cut(0.35), _m13cutmin(0.2), _m13cutmax(1.3),
    _nfilt(5), _jet_algorithm(fastjet::cambridge_algorithm), _jet_algorithm_recluster(fastjet::cambridge_algorithm),
    debugg(false)
{}

TopTagger::TopTagger(fastjet::ClusterSequence const& cs, fastjet::PseudoJet const& jet, double mtmass, double mwmass) :
    _cs(&cs), _jet(jet), _mtmass(mtmass), _mwmass(mwmass),
    _mass_drop_threshold(0.8), _max_subjet_mass(30.),
    _mtmin(mtmass - 25.), _mtmax(mtmass + 25.), _rmin(0.85 * mwmass / mtmass), _rmax(1.15 * mwmass / mtmass),
    _m23cut(0.35), _m13cutmin(0.2), _m13cutmax(1.3),
    _nfilt(5), _jet_algorithm(fastjet::cambridge_algorithm), _jet_algorithm_recluster(fastjet::cambridge_algorithm),
    debugg(false)
{}

void TopTagger::run_tagger()
{
    _delta_top = 1000000000000.0;
    _top_candidate.reset(0., 0., 0., 0.);
    _top_count = 0;
    _parts_size = 0;
    _is_maybe_top = _is_masscut_passed = false;
    _top_subjets.clear();
    _top_hadrons.clear();
    _top_parts.clear();

    if (debugg) {
        std::cout << "mtmass in top_tagger: " << _mtmass << '\n';
        std::cout << "mwmass in top_tagger: " << _mwmass << '\n';
        std::cout << "jet input HEPTopTagger: " << '\n';
        //printjet(_jet);
    }

    // input this_jet, output _top_parts
    FindHardSubst(_jet, _top_parts);

    // store hard substructure of the top candidate
    _parts_size = _top_parts.size();

    // these events are not interesting
    if (_top_parts.size() < 3) return;

    for (unsigned rr = 0; rr < _top_parts.size(); rr++) {
        for (auto ll = rr + 1; ll < _top_parts.size(); ll++) {
            for (auto kk = ll + 1; kk < _top_parts.size(); kk++) {
                // define top_constituents candidate before filtering
                auto top_constits = _cs->constituents(_top_parts[rr]);
                _cs->add_constituents(_top_parts[ll], top_constits);
                _cs->add_constituents(_top_parts[kk], top_constits);

                // define Filtering: filt_top_R and jetdefinition
                auto filt_top_R
                    = std::min(0.3, 0.5 * sqrt(std::min(_top_parts[kk].squared_distance(_top_parts[ll]),
                                                        std::min(_top_parts[rr].squared_distance(_top_parts[ll]),
                                                                _top_parts[kk].squared_distance(_top_parts[rr])))));
                fastjet::JetDefinition filtering_def(_jet_algorithm, filt_top_R);
                auto top_constits_filtered = Filtering(top_constits, filtering_def);
                auto topcandidate = Sum(top_constits_filtered);
                if (topcandidate.m() < _mtmin || _mtmax < topcandidate.m()) continue;
                _top_count++;
                // obtain 3 subjets
                fastjet::JetDefinition reclustering(_jet_algorithm_recluster, 3.14 / 2);
                boca::ClusterSequence cssubtop(top_constits_filtered, reclustering);
                auto top_subs = sorted_by_pt(PseudoJetVector(cssubtop.ExclusiveJets(3)));
                _candjets.push_back(top_subs); //

                // transfer infos of the positively identified top to the outer world
                auto deltatop = std::abs(topcandidate.m() - _mtmass);
                if (deltatop < _delta_top) {
                    _delta_top = deltatop;
                    _is_maybe_top = true;
                    _top_candidate = topcandidate;
                    store_topsubjets(top_subs);
                    _top_hadrons = top_constits_filtered;
                    /////////////////////// check mass plane cut////////////////////////
                    _is_masscut_passed = check_mass_criteria(top_subs);
                }// end deltatop < _delta_top
            }// end kk
        }// end ll
    }// end rr
    return;
}

std::vector<fastjet::PseudoJet> TopTagger::Filtering(std::vector<fastjet::PseudoJet> const& top_constits, fastjet::JetDefinition const& filtering_def)
{
    // perform filtering
    fastjet::ClusterSequence cstopfilt(top_constits, filtering_def);

    // extract top subjets
    auto filt_top_subjets = sorted_by_pt(cstopfilt.inclusive_jets());

    // take first n_topfilt subjets
    std::vector<fastjet::PseudoJet> top_constits_filtered;
    for (unsigned ii = 0; ii < std::min(_nfilt, filt_top_subjets.size()) ; ii++) {
        cstopfilt.add_constituents(filt_top_subjets[ii], top_constits_filtered);
    }
    return top_constits_filtered;
}

fastjet::PseudoJet TopTagger::Sum(std::vector<fastjet::PseudoJet> const& vec_pjet)
{
    fastjet::PseudoJet sum;
    sum.reset(0., 0., 0., 0.);
    for (unsigned i = 0; i < vec_pjet.size(); i++) {
        sum += vec_pjet.at(i);
    }
    return sum;
}

void TopTagger::get_info() const
{
    std::cout << "maybe_top: " <<  _is_maybe_top << '\n';
    std::cout << "mascut_passed: " <<  _is_masscut_passed << '\n';
    std::cout << "top candidate mass:" <<  _top_candidate.m() << '\n';
    std::cout << "top candidate (pt, eta, phi): ("
              <<  _top_candidate.perp() << ","
              <<  _top_candidate.eta() << ","
              <<  _top_candidate.phi_std() << ")" << '\n';
    std::cout << "hadrons size: " <<  _top_hadrons.size() << '\n';
    std::cout << "topcount: " <<  _top_count << '\n';
    std::cout << "parts size: " <<  _parts_size << '\n';
    std::cout << "delta_top: " <<  _delta_top << '\n';
    return;
}

void TopTagger::get_setting() const
{
    std::cout << "top mass: " <<  _mtmass << '\n';
    std::cout << "W mass: " <<  _mwmass << '\n';
    std::cout << "top mass range: [" << _mtmin << ", " << _mtmax << "]" << '\n';
    std::cout << "W mass ratio range: [" << _rmin << ", " << _rmax << "] (["
              << _rmin* _mtmass / _mwmass << "%, " << _rmax* _mtmass / _mwmass << "%])" << '\n';
    std::cout << "mass ratio cut: (m23cut, m13min, m13max)=("
              << _m23cut << ", " << _m13cutmin << ", " << _m13cutmax << ")" << '\n';
    std::cout << "mass_drop_threshold: " << _mass_drop_threshold << '\n';
    std::cout << "max_subjet_mass: " << _max_subjet_mass << '\n';
    std::cout << "n_filtering: " << _nfilt << '\n';
    std::cout << "JetAlgorithm for filtering: " << _jet_algorithm << '\n';
    std::cout << "JetAlgorithm for reclustering: " << _jet_algorithm_recluster << '\n';
    return;
}
bool TopTagger::is_maybe_top() const
{
    return _is_maybe_top;
}
bool TopTagger::is_masscut_passed() const
{
    return _is_masscut_passed;
}
fastjet::PseudoJet const& TopTagger::top_candidate() const
{
    return _top_candidate;
}
std::vector< fastjet::PseudoJet > const& TopTagger::top_subjets() const
{
    return _top_subjets;
}
std::vector< fastjet::PseudoJet > const& TopTagger::top_hadrons() const
{
    return _top_hadrons;
}
unsigned TopTagger::top_count() const
{
    return _top_count;
}
std::vector< fastjet::PseudoJet > const& TopTagger::hardparts() const
{
    return _top_parts;
}
unsigned TopTagger::parts_size() const
{
    return _parts_size;
}
double TopTagger::delta_top() const
{
    return _delta_top;
}
const std::vector< std::vector< fastjet::PseudoJet > >& TopTagger::candjets() const
{
    return _candjets;
}
void TopTagger::set_max_subjet_mass(double x)
{
    _max_subjet_mass = x;
}
void TopTagger::set_mass_drop_threshold(double x)
{
    _mass_drop_threshold = x;
}
void TopTagger::set_top_range(double xmin, double xmax)
{
    _mtmin = xmin;
    _mtmax = xmax;
}
void TopTagger::set_mass_ratio_range(double rmin, double rmax)
{
    _rmin = rmin;
    _rmax = rmax;
}
void TopTagger::set_mass_ratio_cut(double m23cut, double m13cutmin, double m13cutmax)
{
    _m23cut = m23cut;
    _m13cutmin = m13cutmin;
    _m13cutmax = m13cutmax;
}
void TopTagger::set_nfilt(unsigned nfilt)
{
    _nfilt = nfilt;
}
void TopTagger::set_filtering_jetalgorithm(fastjet::JetAlgorithm jet_algorithm)
{
    _jet_algorithm = jet_algorithm;
}
void TopTagger::set_reclustering_jetalgorithm(fastjet::JetAlgorithm jet_algorithm)
{
    _jet_algorithm_recluster = jet_algorithm;
}

}
