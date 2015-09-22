/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "WLeptonicTagger.hh"

#include "Event.hh"
#include "ParticleInfo.hh"
#include "Debug.hh"

namespace boca {

WLeptonicTagger::WLeptonicTagger()
{
    Info();
    w_mass_window_ = 20;
    DefineVariables();
}

int WLeptonicTagger::Train(Event const& event, boca::PreCuts const&, Tag tag) const
{
    Info();
    Jets Particles = event.Partons().GenParticles();
    int w_leptonic_id = WLeptonicId(event);
    Jets w_bosons = CopyIfExactParticle(Particles, w_leptonic_id);
    Jets leptons = fastjet::sorted_by_pt(event.Leptons().leptons());
    if (leptons.size() > w_bosons.size())
        leptons.erase(leptons.begin() + w_bosons.size(), leptons.end());
    fastjet::PseudoJet missing_et = event.Hadrons().MissingEt();
    std::vector<Doublet> doublets;
    for (auto const& lepton : leptons) {
        Doublet pre_doublet(lepton, missing_et);
        std::vector<Doublet> post_doublets = ReconstructNeutrino(pre_doublet);
        for (auto& doublet : post_doublets) {
            if (tag == Tag::signal && std::abs(doublet.Jet().m() - MassOf(Id::W)) > w_mass_window_) continue;
            bool in_cone = false;
            for (auto const& w_boson : w_bosons) if (Close(w_boson)(doublet)) in_cone = true;
            switch (tag) {
            case Tag::signal :
                if (!in_cone) continue;
                break;
            case Tag::background :
                if (in_cone) continue;
                break;
            }
            doublet.SetTag(tag);
            doublets.emplace_back(doublet);
        }
    }
    return SaveEntries(doublets);
}

std::vector<Doublet>  WLeptonicTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    Info();
    Jets Particles = event.Partons().GenParticles();
    int w_leptonic_id = WLeptonicId(event);
    Jets w_bosons = CopyIfExactParticle(Particles, w_leptonic_id);
    Jets leptons = fastjet::sorted_by_pt(event.Leptons().leptons());
    if (leptons.size() > w_bosons.size()) leptons.erase(leptons.begin() + w_bosons.size(), leptons.end());
    std::vector<Doublet> doublets;
    for (auto const& lepton : leptons) {
        Doublet pre_doublet(lepton, event.Hadrons().MissingEt());
        std::vector<Doublet> post_doublets = ReconstructNeutrino(pre_doublet);
        for (auto& doublet : post_doublets) {
            if (std::abs(doublet.Jet().m() - MassOf(Id::W)) > w_mass_window_) continue;
            doublet.SetBdt(Bdt(doublet, reader));
            doublets.emplace_back(doublet);
        }
    }
    return ReduceResult(doublets);
}

std::vector<Doublet> WLeptonicTagger::ReconstructNeutrino(Doublet const& doublet) const
{
    Info();
    fastjet::PseudoJet lepton = doublet.Singlet1().Jet();
    fastjet::PseudoJet missing_et = doublet.Singlet2().Jet();
    float linear_term = (sqr(MassOf(Id::W)) - lepton.m2()) / 2 + missing_et.px() * lepton.px() + missing_et.py() * lepton.py();
    float lepton_square = sqr(lepton.e()) - sqr(lepton.pz());
    float missing_et_square = sqr(missing_et.px()) + sqr(missing_et.py());
    double radicant = sqr(lepton.pz()) * (sqr(linear_term) -  lepton_square * missing_et_square);
    if (radicant < 0) {
        Info("Imaginary root", "move missing et towards lepton");
        Doublet mod_doublet(lepton, missing_et + 0.1 * (lepton - missing_et));
//         mod_doublet.SetFlag(true);
        mod_doublet.SetTag(doublet.Tag());
        return ReconstructNeutrino(mod_doublet);
    }
    Check(radicant != 0, "Radicant exactly zero", "implement this case!");
    float sqrt = std::sqrt(radicant);
    float neutrino_1_e = (lepton.e() * linear_term - sqrt) / lepton_square;
    float neutrino_1_pz = (sqr(lepton.pz()) * linear_term - lepton.e() * sqrt) / lepton.pz() / lepton_square;
    fastjet::PseudoJet neutrino_1(missing_et.px(), missing_et.py(), neutrino_1_pz, neutrino_1_e);
    Debug(neutrino_1);
    Doublet doublet1(lepton, neutrino_1);
    doublet1.SetTag(doublet.Tag());
//     doublet1.SetFlag(doublet.Flag());
    float neutrino_2_e = (lepton.e() * linear_term + sqrt) / lepton_square;
    float neutrino_2_pz = (sqr(lepton.pz()) * linear_term + lepton.e() * sqrt) / lepton.pz() / lepton_square;
    fastjet::PseudoJet neutrino_2(missing_et.px(), missing_et.py(), neutrino_2_pz, neutrino_2_e);
    Debug(neutrino_2);
    Doublet doublet2(lepton, neutrino_2);
    doublet2.SetTag(doublet.Tag());
//     doublet2.SetFlag(doublet.Flag());
    std::vector<Doublet> doublets;
    doublets.emplace_back(doublet1);
    doublets.emplace_back(doublet2);
    return doublets;
}

Jets WLeptonicTagger::WLeptonicDaughters(Event const& event) const
{
    Jets w_daughters = event.Partons().GenParticles();
    w_daughters = RemoveIfSoft(w_daughters, DetectorGeometry::JetMinPt());
    w_daughters = CopyIfMother(w_daughters, Id::W);
    w_daughters = RemoveIfQuark(w_daughters);
    return w_daughters;
}

int WLeptonicTagger::WLeptonicId(Jets const& jets) const
{
    if (jets.empty()) return 0;
    int sign;
    bool first = true;
    bool just_one = true;
    for (auto const& jet : jets) {
        int id = jet.user_info<ParticleInfo>().Family().mother_1().id();
        if (first) sign = sgn(id);
        else if (sign != sgn(id)) just_one = false;
        first = false;
    }
    if (just_one) return sign * to_int(Id::W);
    return 0;
}

}
