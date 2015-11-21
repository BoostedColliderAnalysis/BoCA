/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "WLeptonicTagger.hh"

#include "Event.hh"
#include "ParticleInfo.hh"
#include "Debug.hh"

namespace boca
{

namespace standardmodel
{

WLeptonicTagger::WLeptonicTagger()
{
    Info0;
    w_mass_window_ = 20. * GeV;
}

int WLeptonicTagger::Train(Event const& event, boca::PreCuts const&, Tag tag) const
{
    Info0;
    std::vector<Jet> leptons = event.Leptons().leptons();
    Jet missing_et = event.Hadrons().MissingEt();
    std::vector<Doublet> doublets;
    for (auto const & lepton : leptons) {
        Doublet pre_doublet(lepton, missing_et);
        std::vector<Doublet> post_doublets = ReconstructNeutrino(pre_doublet);
        for (auto & doublet : post_doublets) {
            if (Problematic(doublet, tag)) continue;
            doublet.SetTag(tag);
            doublets.emplace_back(doublet);
        }
    }
    Error(doublets.size());
    std::vector<Particle>w_bosons = Particles(event);
    return SaveEntries(BestMatches(doublets, w_bosons, tag));
}

bool WLeptonicTagger::Problematic(Doublet const& doublet, Tag tag) const
{
    switch (tag) {
    case Tag::signal : if (boost::units::abs(doublet.Mass() - MassOf(Id::W)) > w_mass_window_) return true;
        break;
    case Tag::background : break;
    }
    return false;
}

std::vector<Particle> WLeptonicTagger::Particles(Event const& event) const
{
    std::vector<Particle> particles = event.Partons().GenParticles();
    std::vector<Particle> leptons = CopyIfMother(CopyIfLepton(particles), Id::W);
    particles = CopyIfDaughter(particles, leptons);
    return particles;
}

std::vector<Doublet>  WLeptonicTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    Info0;
    std::vector<Jet> leptons = SortedByPt(event.Leptons().leptons());
    std::vector<Doublet> doublets;
    for (auto const & lepton : leptons) {
        Doublet pre_doublet(lepton, event.Hadrons().MissingEt());
        std::vector<Doublet> post_doublets = ReconstructNeutrino(pre_doublet);
        for (auto & doublet : post_doublets) {
            if (boost::units::abs(doublet.Mass() - MassOf(Id::W)) > w_mass_window_) continue;
            doublet.SetBdt(Bdt(doublet, reader));
            doublets.emplace_back(doublet);
        }
    }
    return ReduceResult(doublets);
}

std::vector<Doublet> WLeptonicTagger::ReconstructNeutrino(Doublet const& doublet) const
{
    Info0;
    std::vector<Doublet> doublets;
    Jet lepton = doublet.Singlet1().Jet();
    Jet missing_et = doublet.Singlet2().Jet();
    float linear_term = (sqr(MassOf(Id::W) / GeV) - lepton.m2()) / 2 + missing_et.px() * lepton.px() + missing_et.py() * lepton.py();
    float lepton_square = sqr(lepton.e()) - sqr(lepton.pz());
    float missing_et_square = sqr(missing_et.px()) + sqr(missing_et.py());
    double radicant = sqr(lepton.pz()) * (sqr(linear_term) -  lepton_square * missing_et_square);
    if (radicant < 0) {
        INFO("Imaginary root", "move missing et towards lepton");
        Doublet mod_doublet(lepton, missing_et + 0.1 * (lepton - missing_et));
//         mod_doublet.SetFlag(true);
        mod_doublet.SetTag(doublet.Tag());
        return ReconstructNeutrino(mod_doublet);
    }
    Check(radicant != 0, "Radicant exactly zero", "implement this case!");
    float sqrt = std::sqrt(radicant);
    float neutrino_1_e = (lepton.e() * linear_term - sqrt) / lepton_square;
    float neutrino_1_pz = (sqr(lepton.pz()) * linear_term - lepton.e() * sqrt) / lepton.pz() / lepton_square;
    Jet neutrino_1(missing_et.px(), missing_et.py(), neutrino_1_pz, neutrino_1_e);
    Debug(neutrino_1);
    Doublet doublet1(lepton, neutrino_1);
    doublet1.SetTag(doublet.Tag());
    doublets.emplace_back(doublet1);

    float neutrino_2_e = (lepton.e() * linear_term + sqrt) / lepton_square;
    float neutrino_2_pz = (sqr(lepton.pz()) * linear_term + lepton.e() * sqrt) / lepton.pz() / lepton_square;
    Jet neutrino_2(missing_et.px(), missing_et.py(), neutrino_2_pz, neutrino_2_e);
    Debug(neutrino_2);
    Doublet doublet2(lepton, neutrino_2);
    doublet2.SetTag(doublet.Tag());
    doublets.emplace_back(doublet2);

    return doublets;
}

std::string WLeptonicTagger::Name() const
{
    return "WLeptonic";
}

std::string WLeptonicTagger::NiceName() const
{
    return "W_{l}";
}

}

}
