#include "WLeptonicTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis {

WLeptonicTagger::WLeptonicTagger()
{
    Info();
    w_mass_window_ = 20;
    DefineVariables();
}

int WLeptonicTagger::Train(const Event& event, const analysis::PreCuts&, Tag tag) const
{
    Info();
    Jets Particles = event.Partons().GenParticles();
    int w_leptonic_id = WLeptonicId(event);
    Jets w_bosons = CopyIfExactParticle(Particles, w_leptonic_id);
    Jets leptons = fastjet::sorted_by_pt(event.Leptons().leptons());
    if (leptons.size() > w_bosons.size())
        leptons.erase(leptons.begin() + w_bosons.size(), leptons.end());
    const fastjet::PseudoJet missing_et = event.Hadrons().MissingEt();
    std::vector<Doublet> doublets;
    for (const auto& lepton : leptons) {
        Doublet pre_doublet(lepton, missing_et);
        std::vector<Doublet> post_doublets = ReconstructNeutrino(pre_doublet);
        for (auto& doublet : post_doublets) {
            if (tag == Tag::signal && std::abs(doublet.Jet().m() - Mass(Id::W)) > w_mass_window_)
                continue;
            bool in_cone = false;
            for (const auto& w_boson : w_bosons) if (doublet.Coincides(w_boson))
                    in_cone = true;
            switch (tag) {
            case Tag::signal :
                if (!in_cone)
                    continue;
                break;
            case Tag::background :
                if (in_cone)
                    continue;
                break;
            }
            doublet.SetTag(tag);
            doublets.emplace_back(doublet);
        }
    }
    return SaveEntries(doublets);
}

std::vector<Doublet>  WLeptonicTagger::Multiplets(const Event& event, const analysis::PreCuts&, const TMVA::Reader& reader) const
{
    Info();
    Jets Particles = event.Partons().GenParticles();
    int w_leptonic_id = WLeptonicId(event);
    Jets w_bosons = CopyIfExactParticle(Particles, w_leptonic_id);
    Jets leptons = fastjet::sorted_by_pt(event.Leptons().leptons());
    if (leptons.size() > w_bosons.size())
        leptons.erase(leptons.begin() + w_bosons.size(), leptons.end());
    std::vector<Doublet> doublets;
    for (const auto& lepton : leptons) {
        Doublet pre_doublet(lepton, event.Hadrons().MissingEt());
        std::vector<Doublet> post_doublets = ReconstructNeutrino(pre_doublet);
        for (auto& doublet : post_doublets) {
            if (std::abs(doublet.Jet().m() - Mass(Id::W)) > w_mass_window_)
                continue;
            doublet.SetBdt(Bdt(doublet, reader));
            doublets.emplace_back(doublet);
        }
    }
    return ReduceResult(doublets);
}

std::vector<Doublet> WLeptonicTagger::ReconstructNeutrino(const Doublet& doublet) const
{
    Info();
    const fastjet::PseudoJet lepton = doublet.Singlet1().Jet();
    const fastjet::PseudoJet missing_et = doublet.Singlet2().Jet();
    float linear_term = (std::pow(Mass(Id::W), 2) - lepton.m2()) / 2 + missing_et.px() * lepton.px() + missing_et.py() * lepton.py();
    float lepton_square = std::pow(lepton.e(), 2) - std::pow(lepton.pz(), 2);
    float missing_et_square = std::pow(missing_et.px(), 2) + std::pow(missing_et.py(), 2);
    double radicant = std::pow(lepton.pz(), 2) * (std::pow(linear_term, 2) -  lepton_square * missing_et_square);
    if (radicant < 0) {
        Info("Imaginary root", "move missing et towards lepton");
        Doublet mod_doublet(lepton, missing_et + 0.1 * (lepton - missing_et));
        mod_doublet.SetFlag(true);
        mod_doublet.SetTag(doublet.Tag());
        return ReconstructNeutrino(mod_doublet);
    }
    Check(radicant != 0, "Radicant exactly zero", "implement this case!");
    float sqrt = std::sqrt(radicant);
    float neutrino_1_e = (lepton.e() * linear_term - sqrt) / lepton_square;
    float neutrino_1_pz = (std::pow(lepton.pz(), 2) * linear_term - lepton.e() * sqrt) / lepton.pz() / lepton_square;
    fastjet::PseudoJet neutrino_1(missing_et.px(), missing_et.py(), neutrino_1_pz, neutrino_1_e);
    Debug("Neutrnio 1", neutrino_1);
    Doublet doublet1(lepton, neutrino_1);
    doublet1.SetTag(doublet.Tag());
    doublet1.SetFlag(doublet.Flag());
    float neutrino_2_e = (lepton.e() * linear_term + sqrt) / lepton_square;
    float neutrino_2_pz = (std::pow(lepton.pz(), 2) * linear_term + lepton.e() * sqrt) / lepton.pz() / lepton_square;
    fastjet::PseudoJet neutrino_2(missing_et.px(), missing_et.py(), neutrino_2_pz, neutrino_2_e);
    Debug("Neutrino 2", neutrino_2);
    Doublet doublet2(lepton, neutrino_2);
    doublet2.SetTag(doublet.Tag());
    doublet2.SetFlag(doublet.Flag());
    std::vector<Doublet> doublets;
    doublets.emplace_back(doublet1);
    doublets.emplace_back(doublet2);
    return doublets;
}

Jets WLeptonicTagger::WLeptonicDaughters(const Event& event) const
{
    Jets w_daughters = event.Partons().GenParticles();
    w_daughters = RemoveIfSoft(w_daughters, DetectorGeometry::JetMinPt());
    w_daughters = CopyIfMother(w_daughters, Id::W);
    w_daughters = RemoveIfQuark(w_daughters);
    return w_daughters;
}

int WLeptonicTagger::WLeptonicId(const Jets& jets) const
{
    if (jets.empty())
        return 0;
    int sign;
    bool first = true;
    bool just_one = true;
    for (const auto jet : jets) {
        int id = jet.user_info<JetInfo>().constituents().front().family().mother_1().id();
        if (first) sign = sgn(id);
        else if (sign != sgn(id)) just_one = false;
        first = false;
    }
    if (just_one) return sign * to_int(Id::W);
    return 0;
}

}
