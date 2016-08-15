#include "fastjet/tools/Filter.hh"

#include "fastjet/contrib/Nsubjettiness.hh"

#include "boca/external/QJetsPlugin.hh"
#include "boca/external/QJetsBaseExtras.hh"
#include "boca/external/TopTagger2.hh"

#include "boca/Settings.hh"

namespace hep
{

namespace
{

//optimal_R fit
double R_opt_calc_funct(double pt_filt)
{
    return 327. / pt_filt;
}

}

//uncluster a fat jet to subjets of given cone size
void TopTagger2::UnclusterFatjets(std::vector<fastjet::PseudoJet> const& big_fatjets, std::vector<fastjet::PseudoJet>& small_fatjets, fastjet::ClusterSequence const& cseq, const double small_radius)
{
    for (unsigned i = 0; i < big_fatjets.size(); i++) {
        auto this_jet = big_fatjets[i];
        fastjet::PseudoJet parent1(0, 0, 0, 0), parent2(0, 0, 0, 0);
        auto test = cseq.has_parents(this_jet, parent1, parent2);
        auto dR = 100.;

        if (test) dR = sqrt(parent1.squared_distance(parent2));

        if (!test || dR < small_radius) {
            small_fatjets.push_back(this_jet);
        } else {
            std::vector<fastjet::PseudoJet> parents;
            parents.push_back(parent1);
            parents.push_back(parent2);
            UnclusterFatjets(parents, small_fatjets, cseq, small_radius);
        }
    }
}

TopTagger2::TopTagger2() :
    _do_optimalR(1),
    _do_qjets(0),
    _mass_drop_threshold(0.8),
    _max_subjet_mass(30.),
    _mode(Mode(0)),
    _mtmass(172.3),
    _mwmass(80.4),
    _mtmin(150.),
    _mtmax(200.),
    _rmin(0.85 * 80.4 / 172.3),
    _rmax(1.15 * 80.4 / 172.3),
    _m23cut(0.35),
    _m13cutmin(0.2),
    _m13cutmax(1.3),
    _minpt_tag(200.),
    _nfilt(5),
    _Rfilt(0.3),
    _jet_algorithm_filter(fastjet::cambridge_algorithm),
    _minpt_subjet(0.),
    _jet_algorithm_recluster(fastjet::cambridge_algorithm),
    _zcut(0.1),
    _rcut_factor(0.5),
    _max_fatjet_R(1.8),
    _min_fatjet_R(0.5),
    _step_R(0.1),
    _optimalR_threshold(0.2),
    _R_filt_optimalR_calc(0.2),
    _N_filt_optimalR_calc(10),
    _r_min_exp_function(&R_opt_calc_funct),
    _optimalR_mmin(150.),
    _optimalR_mmax(200.),
    _optimalR_fw(0.175),
    _R_opt_diff(0.3),
    _R_filt_optimalR_pass(0.2),
    _N_filt_optimalR_pass(5),
    _R_filt_optimalR_fail(0.3),
    _N_filt_optimalR_fail(3),
    _q_zcut(0.1),
    _q_dcut_fctr(0.5),
    _q_exp_min(0.),
    _q_exp_max(0.),
    _q_rigidity(0.1),
    _q_truncation_fctr(0.0),
    _debug(false)
{}

TopTagger2::TopTagger2(fastjet::PseudoJet const& jet) :
    _do_optimalR(1),
    _do_qjets(0),
    _jet(jet),
    _initial_jet(jet),
    _mass_drop_threshold(0.8),
    _max_subjet_mass(30.),
    _mode(Mode(0)),
    _mtmass(172.3),
    _mwmass(80.4),
    _mtmin(150.),
    _mtmax(200.),
    _rmin(0.85 * 80.4 / 172.3),
    _rmax(1.15 * 80.4 / 172.3),
    _m23cut(0.35),
    _m13cutmin(0.2),
    _m13cutmax(1.3),
    _minpt_tag(200.),
    _nfilt(5),
    _Rfilt(0.3),
    _jet_algorithm_filter(fastjet::cambridge_algorithm),
    _minpt_subjet(0.),
    _jet_algorithm_recluster(fastjet::cambridge_algorithm),
    _zcut(0.1),
    _rcut_factor(0.5),
    _max_fatjet_R(jet.validated_cluster_sequence()->jet_def().R()),
    _min_fatjet_R(0.5),
    _step_R(0.1),
    _optimalR_threshold(0.2),
    _R_filt_optimalR_calc(0.2),
    _N_filt_optimalR_calc(10),
    _r_min_exp_function(&R_opt_calc_funct),
    _optimalR_mmin(150.),
    _optimalR_mmax(200.),
    _optimalR_fw(0.175),
    _R_opt_diff(0.3),
    _R_filt_optimalR_pass(0.2),
    _N_filt_optimalR_pass(5),
    _R_filt_optimalR_fail(0.3),
    _N_filt_optimalR_fail(3),
    _q_zcut(0.1),
    _q_dcut_fctr(0.5),
    _q_exp_min(0.),
    _q_exp_max(0.),
    _q_rigidity(0.1),
    _q_truncation_fctr(0.0),
    _fat(jet),
    _debug(false)
{}

TopTagger2::TopTagger2(fastjet::PseudoJet const& jet, double mtmass, double mwmass) :
    _do_optimalR(1),
    _do_qjets(0),
    _jet(jet),
    _initial_jet(jet),
    _mass_drop_threshold(0.8),
    _max_subjet_mass(30.),
    _mode(Mode(0)),
    _mtmass(mtmass),
    _mwmass(mwmass),
    _mtmin(150.),
    _mtmax(200.),
    _rmin(0.85 * 80.4 / 172.3),
    _rmax(1.15 * 80.4 / 172.3),
    _m23cut(0.35),
    _m13cutmin(0.2),
    _m13cutmax(1.3),
    _minpt_tag(200.),
    _nfilt(5),
    _Rfilt(0.3),
    _jet_algorithm_filter(fastjet::cambridge_algorithm),
    _minpt_subjet(0.),
    _jet_algorithm_recluster(fastjet::cambridge_algorithm),
    _zcut(0.1),
    _rcut_factor(0.5),
    _max_fatjet_R(jet.validated_cluster_sequence()->jet_def().R()),
    _min_fatjet_R(0.5),
    _step_R(0.1),
    _optimalR_threshold(0.2),
    _R_filt_optimalR_calc(0.2),
    _N_filt_optimalR_calc(10),
    _r_min_exp_function(&R_opt_calc_funct),
    _optimalR_mmin(150.),
    _optimalR_mmax(200.),
    _optimalR_fw(0.175),
    _R_opt_diff(0.3),
    _R_filt_optimalR_pass(0.2),
    _N_filt_optimalR_pass(5),
    _R_filt_optimalR_fail(0.3),
    _N_filt_optimalR_fail(3),
    _q_zcut(0.1),
    _q_dcut_fctr(0.5),
    _q_exp_min(0.),
    _q_exp_max(0.),
    _q_rigidity(0.1),
    _q_truncation_fctr(0.0),
    _fat(jet),
    _debug(false)
{}

void TopTagger2::run()
{
    qjets::QJetsPlugin _qjet_plugin(_q_zcut, _q_dcut_fctr, _q_exp_min, _q_exp_max, _q_rigidity, _q_truncation_fctr);
    auto maxR = static_cast<int>(_max_fatjet_R * 10);
    auto minR = static_cast<int>(_min_fatjet_R * 10);
    auto stepR = static_cast<int>(_step_R * 10);
    _qweight = -1;

    if (!_do_optimalR) {
        TopTaggerFixedR htt(_jet);
        htt.set_mass_drop_threshold(_mass_drop_threshold);
        htt.set_max_subjet_mass(_max_subjet_mass);
        htt.set_filtering_n(_nfilt);
        htt.set_filtering_R(_Rfilt);
        htt.set_filtering_minpt_subjet(_minpt_subjet);
        htt.set_filtering_jetalgorithm(_jet_algorithm_filter);
        htt.set_reclustering_jetalgorithm(_jet_algorithm_recluster);
        htt.set_mode(_mode);
        htt.set_mt(_mtmass);
        htt.set_mw(_mwmass);
        htt.set_top_mass_range(_mtmin, _mtmax);
        htt.set_mass_ratio_range(_rmin, _rmax);
        htt.set_mass_ratio_cut(_m23cut, _m13cutmin, _m13cutmax);
        htt.set_top_minpt(_minpt_tag);
        htt.set_pruning_zcut(_zcut);
        htt.set_pruning_rcut_factor(_rcut_factor);
        htt.set_debug(_debug);
        htt.set_qjets(_q_zcut, _q_dcut_fctr, _q_exp_min, _q_exp_max, _q_rigidity, _q_truncation_fctr);
        htt.run();

        _TopTagger2[maxR] = htt;
        _Ropt = maxR;
        _qweight = htt.q_weight();
        _TopTagger2_opt = _TopTagger2[_Ropt];
    } else {
        _qjet_def = fastjet::JetDefinition(&_qjet_plugin);
        std::vector<fastjet::PseudoJet> _q_constits;
        fastjet::ClusterSequence* _qjet_seq;
        fastjet::PseudoJet _qjet;
        fastjet::ClusterSequence const* _seq;
        _seq = _initial_jet.validated_cluster_sequence();
        if (_do_qjets) {
            _q_constits = _initial_jet.associated_cluster_sequence()->constituents(_initial_jet);
            _qjet_seq = new fastjet::ClusterSequence(_q_constits, _qjet_def, &boca::Settings::Recombiner());
            _qjet = sorted_by_pt(_qjet_seq->inclusive_jets())[0];
            _qjet_seq->delete_self_when_unused();
            auto ext = dynamic_cast<qjets::QJetsBaseExtras const*>(_qjet_seq->extras());
            _qweight = ext->weight();
            _jet = _qjet;
            _seq = _qjet_seq;
            _fat = _qjet;
        }

        // Do optimalR procedure
        std::vector<fastjet::PseudoJet> big_fatjets;
        std::vector<fastjet::PseudoJet> small_fatjets;

        big_fatjets.push_back(_jet);
        _Ropt = 0;

        for (auto R = maxR; R >= minR; R -= stepR) {
            UnclusterFatjets(big_fatjets, small_fatjets, *_seq, R / 10.);

            if (_debug) {
                std::cout << "R = " << R << " -> n_small_fatjets = " << small_fatjets.size() << std::endl;
            }

            _n_small_fatjets[R] = small_fatjets.size();

            // We are sorting by pt - so start with a negative dummy
            double dummy = -99999;

            for (unsigned i = 0; i < small_fatjets.size(); i++) {
                TopTaggerFixedR htt(small_fatjets[i]);
                htt.set_mass_drop_threshold(_mass_drop_threshold);
                htt.set_max_subjet_mass(_max_subjet_mass);
                htt.set_filtering_n(_nfilt);
                htt.set_filtering_R(_Rfilt);
                htt.set_filtering_minpt_subjet(_minpt_subjet);
                htt.set_filtering_jetalgorithm(_jet_algorithm_filter);
                htt.set_reclustering_jetalgorithm(_jet_algorithm_recluster);
                htt.set_mode(_mode);
                htt.set_mt(_mtmass);
                htt.set_mw(_mwmass);
                htt.set_top_mass_range(_mtmin, _mtmax);
                htt.set_mass_ratio_range(_rmin, _rmax);
                htt.set_mass_ratio_cut(_m23cut, _m13cutmin, _m13cutmax);
                htt.set_top_minpt(_minpt_tag);
                htt.set_pruning_zcut(_zcut);
                htt.set_pruning_rcut_factor(_rcut_factor);
                htt.set_debug(_debug);
                htt.set_qjets(_q_zcut, _q_dcut_fctr, _q_exp_min, _q_exp_max, _q_rigidity, _q_truncation_fctr);

                htt.run();

                if (htt.t().perp() > dummy) {
                    dummy = htt.t().perp();
                    _TopTagger2[R] = htt;
                }
            } //End of loop over small_fatjets

            // Only check if we have not found Ropt yet
            if (_Ropt == 0 && R < maxR) {
                // If the new mass is OUTSIDE the window ..
                if (_TopTagger2[R].t().m() < (1 - _optimalR_threshold)*_TopTagger2[maxR].t().m())
                    // .. set _Ropt to the previous mass
                    _Ropt = R + stepR;
            }

            big_fatjets = small_fatjets;
            small_fatjets.clear();
        }//End of loop over R

        // if we did not find Ropt in the loop, pick the last value
        if (_Ropt == 0 && _TopTagger2[maxR].t().m() > 0) _Ropt = minR;

        //for the case that there is no tag at all (< 3 hard substructures)
        if (_Ropt == 0 && _TopTagger2[maxR].t().m() == 0) _Ropt = maxR;

        _TopTagger2_opt = _TopTagger2[_Ropt];

        fastjet::Filter filter_optimalR_calc(_R_filt_optimalR_calc, fastjet::SelectorNHardest(_N_filt_optimalR_calc));
        _R_opt_calc = _r_min_exp_function(filter_optimalR_calc(_fat).pt());

        fastjet::Filter filter_optimalR_pass(_R_filt_optimalR_pass, fastjet::SelectorNHardest(_N_filt_optimalR_pass));
        fastjet::Filter filter_optimalR_fail(_R_filt_optimalR_fail, fastjet::SelectorNHardest(_N_filt_optimalR_fail));
        if (optimalR_type() == 1) _filt_fat = filter_optimalR_pass(_fat);
        else _filt_fat = filter_optimalR_fail(_fat);
    }
}

//optimal_R type
int TopTagger2::optimalR_type()
{
    if (_TopTagger2_opt.t().m() < _optimalR_mmin || _TopTagger2_opt.t().m() > _optimalR_mmax) {
        return 0;
    }
    if (_TopTagger2_opt.f_rec() > _optimalR_fw) {
        return 0;
    }
    if (_Ropt / 10. - _R_opt_calc > _R_opt_diff) {
        return 0;
    }
    return 1;
}

double TopTagger2::nsub_unfiltered(int order, fastjet::contrib::Njettiness::AxesMode axes, double beta, double R0)
{
    fastjet::contrib::Nsubjettiness nsub(order, axes, beta, R0);
    return nsub.result(_fat);
}

double TopTagger2::nsub_filtered(int order, fastjet::contrib::Njettiness::AxesMode axes, double beta, double R0)
{
    fastjet::contrib::Nsubjettiness nsub(order, axes, beta, R0);
    return nsub.result(_filt_fat);
}

bool TopTagger2::is_maybe_top() const
{
    return _TopTagger2_opt.is_maybe_top();
}
bool TopTagger2::is_masscut_passed() const
{
    return _TopTagger2_opt.is_masscut_passed();
}
bool TopTagger2::is_minptcut_passed() const
{
    return _TopTagger2_opt.is_minptcut_passed();
}
bool TopTagger2::is_tagged() const
{
    return _TopTagger2_opt.is_tagged();
}
double TopTagger2::delta_top() const
{
    return _TopTagger2_opt.delta_top();
}
double TopTagger2::djsum() const
{
    return _TopTagger2_opt.djsum();
}
double TopTagger2::pruned_mass() const
{
    return _TopTagger2_opt.pruned_mass();
}
double TopTagger2::unfiltered_mass() const
{
    return _TopTagger2_opt.unfiltered_mass();
}
double TopTagger2::f_rec()
{
    return _TopTagger2_opt.f_rec();
}
fastjet::PseudoJet const& TopTagger2::t() const
{
    return _TopTagger2_opt.t();
}
fastjet::PseudoJet const& TopTagger2::b() const
{
    return _TopTagger2_opt.b();
}
fastjet::PseudoJet const& TopTagger2::W() const
{
    return _TopTagger2_opt.W();
}
fastjet::PseudoJet const& TopTagger2::W1() const
{
    return _TopTagger2_opt.W1();
}
fastjet::PseudoJet const& TopTagger2::W2() const
{
    return _TopTagger2_opt.W2();
}
std::vector< fastjet::PseudoJet > const& TopTagger2::top_subjets() const
{
    return _TopTagger2_opt.top_subjets();
}
fastjet::PseudoJet const& TopTagger2::j1() const
{
    return _TopTagger2_opt.j1();
}
fastjet::PseudoJet const& TopTagger2::j2() const
{
    return _TopTagger2_opt.j2();
}
fastjet::PseudoJet const& TopTagger2::j3() const
{
    return _TopTagger2_opt.j3();
}
std::vector< fastjet::PseudoJet > const& TopTagger2::top_hadrons() const
{
    return _TopTagger2_opt.top_hadrons();
}
std::vector< fastjet::PseudoJet > const& TopTagger2::hardparts() const
{
    return _TopTagger2_opt.hardparts();
}
fastjet::PseudoJet const& TopTagger2::fat_initial()
{
    return _fat;
}
fastjet::PseudoJet const& TopTagger2::fat_Ropt()
{
    return _TopTagger2_opt.fat_initial();
}
TopTaggerFixedR TopTagger2::TopTagger2agger(int i)
{
    return _TopTagger2[i];
}
double TopTagger2::Ropt() const
{
    return _Ropt / 10.;
}
double TopTagger2::Ropt_calc() const
{
    return _R_opt_calc;
}
void TopTagger2::get_setting() const
{
    return _TopTagger2_opt.get_setting();
}
void TopTagger2::get_info() const
{
    return _TopTagger2_opt.get_info();
}
double TopTagger2::q_weight()
{
    return _qweight;
}
void TopTagger2::do_optimalR(bool optimalR)
{
    _do_optimalR = optimalR;
}
void TopTagger2::set_mass_drop_threshold(double x)
{
    _mass_drop_threshold = x;
}
void TopTagger2::set_max_subjet_mass(double x)
{
    _max_subjet_mass = x;
}
void TopTagger2::set_filtering_n(unsigned nfilt)
{
    _nfilt = nfilt;
}
void TopTagger2::set_filtering_R(double Rfilt)
{
    _Rfilt = Rfilt;
}
void TopTagger2::set_filtering_minpt_subjet(double x)
{
    _minpt_subjet = x;
}
void TopTagger2::set_filtering_jetalgorithm(fastjet::JetAlgorithm jet_algorithm)
{
    _jet_algorithm_filter = jet_algorithm;
}
void TopTagger2::set_reclustering_jetalgorithm(fastjet::JetAlgorithm jet_algorithm)
{
    _jet_algorithm_recluster = jet_algorithm;
}
void TopTagger2::set_mode(Mode mode)
{
    _mode = mode;
}
void TopTagger2::set_mt(double x)
{
    _mtmass = x;
}
void TopTagger2::set_mw(double x)
{
    _mwmass = x;
}
void TopTagger2::set_top_mass_range(double xmin, double xmax)
{
    _mtmin = xmin;
    _mtmax = xmax;
}
void TopTagger2::set_fw(double fw)
{
    _rmin = (1. - fw) * _mwmass / _mtmass;
    _rmax = (1. + fw) * _mwmass / _mtmass;
}
void TopTagger2::set_mass_ratio_range(double rmin, double rmax)
{
    _rmin = rmin;
    _rmax = rmax;
}
void TopTagger2::set_mass_ratio_cut(double m23cut, double m13cutmin, double m13cutmax)
{
    _m23cut = m23cut;
    _m13cutmin = m13cutmin;
    _m13cutmax = m13cutmax;
}
void TopTagger2::set_top_minpt(double x)
{
    _minpt_tag = x;
}
void TopTagger2::set_optimalR_max(double x)
{
    _max_fatjet_R = x;
}
void TopTagger2::set_optimalR_min(double x)
{
    _min_fatjet_R = x;
}
void TopTagger2::set_optimalR_step(double x)
{
    _step_R = x;
}
void TopTagger2::set_optimalR_threshold(double x)
{
    _optimalR_threshold = x;
}
void TopTagger2::set_filtering_optimalR_calc_R(double x)
{
    _R_filt_optimalR_calc = x;
}
void TopTagger2::set_filtering_optimalR_calc_n(unsigned x)
{
    _N_filt_optimalR_calc = x;
}
void TopTagger2::set_optimalR_calc_fun(double(*f)(double))
{
    _r_min_exp_function = f;
}
void TopTagger2::set_optimalR_type_top_mass_range(double x, double y)
{
    _optimalR_mmin = x;
    _optimalR_mmax = y;
}
void TopTagger2::set_optimalR_type_fw(double x)
{
    _optimalR_fw = x;
}
void TopTagger2::set_optimalR_type_max_diff(double x)
{
    _R_opt_diff = x;
}
void TopTagger2::set_filtering_optimalR_pass_R(double x)
{
    _R_filt_optimalR_pass = x;
}
void TopTagger2::set_filtering_optimalR_pass_n(unsigned x)
{
    _N_filt_optimalR_pass = x;
}
void TopTagger2::set_filtering_optimalR_fail_R(double x)
{
    _R_filt_optimalR_fail = x;
}
void TopTagger2::set_filtering_optimalR_fail_n(unsigned x)
{
    _N_filt_optimalR_fail = x;
}
void TopTagger2::set_pruning_zcut(double zcut)
{
    _zcut = zcut;
}
void TopTagger2::set_pruning_rcut_factor(double rcut_factor)
{
    _rcut_factor = rcut_factor;
}
void TopTagger2::set_debug(bool debug)
{
    _debug = debug;
}
void TopTagger2::do_qjets(bool qjets)
{
    _do_qjets = qjets;
}
void TopTagger2::set_qjets(double q_zcut, double q_dcut_fctr, double q_exp_min, double q_exp_max, double q_rigidity, double q_truncation_fctr)
{
    _q_zcut = q_zcut; _q_dcut_fctr = q_dcut_fctr; _q_exp_min = q_exp_min; _q_exp_max = q_exp_max; _q_rigidity =  q_rigidity; _q_truncation_fctr =  q_truncation_fctr;
}
}
