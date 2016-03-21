/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "WLeptonicTagger.hh"

#include "Event.hh"
#include "Particles.hh"
#include "plotting/Font.hh"
// #define DEBUGGING
#include "DEBUG.hh"

namespace boca
{

namespace standardmodel
{

namespace
{

Lepton FakeLepton(Jet const& jet)
{
    INFO0;
    return jet * (DetectorGeometry::LeptonMinPt() / jet.Pt());
}

std::vector<Lepton> Leptons(Event const& event)
{
    INFO0;
    bool do_fake_leptons = true;
    std::vector<Lepton> leptons = RemoveIfSoft(event.Leptons().leptons(), DetectorGeometry::LeptonMinPt());
    std::vector<Jet> jets = SortedByPt(event.Hadrons().Jets());
    if (do_fake_leptons && leptons.empty() && !jets.empty()) leptons.emplace_back(FakeLepton(jets.front()));
    DEBUG(jets.size(), leptons.size());
    return leptons;
}

}

WLeptonicTagger::WLeptonicTagger()
{
    INFO0;
    w_mass_window_ = 20_GeV;
}

int WLeptonicTagger::Train(Event const& event, boca::PreCuts const& pre_cuts, Tag tag) const
{
    INFO0;
    return SaveEntries(Doublets(event, [&](Doublet & doublet) -> boost::optional<Doublet> {
        if (Problematic(doublet, pre_cuts, tag)) return boost::none;
        doublet.SetTag(tag);
        return doublet;
    }), Particles(event), tag);
}

bool WLeptonicTagger::Problematic(Doublet const& doublet, PreCuts const& pre_cuts, Tag tag) const
{
    INFO0;
    if (Problematic(doublet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal :
        if (pre_cuts.OutSideMassWindow(doublet, w_mass_window_, Id::W)) return true;
        if (pre_cuts.NotParticleRho(doublet)) return true;
        break;
    case Tag::background : break;
    }
    return false;
}

bool WLeptonicTagger::Problematic(Doublet const& doublet, PreCuts const& pre_cuts) const
{
    INFO0;
    if (pre_cuts.ApplyCuts(Id::W, doublet)) return true;
    return false;
}

std::vector<Particle> WLeptonicTagger::Particles(Event const& event) const
{
    INFO0;
    std::vector<Particle> particles = event.Partons().GenParticles();
    std::vector<Particle> leptons = CopyIfMother(CopyIfLepton(particles), Id::W);
    return CopyIfDaughter(CopyIfParticle(particles, Id::W), leptons);
}

std::vector<Doublet> WLeptonicTagger::Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    INFO0;
    return Doublets(event, [&](Doublet & doublet) -> boost::optional<Doublet> {
        if (Problematic(doublet, pre_cuts)) return boost::none;
        doublet.SetBdt(Bdt(doublet, reader));
        return doublet;
    });
}

std::vector<Doublet> WLeptonicTagger::Doublets(Event const& event, std::function<boost::optional<Doublet>(Doublet&)> const& function) const
{
    INFO0;
//     std::vector<Lepton> leptons = SortedByPt(event.Leptons().leptons());
    std::vector<Lepton> leptons = Leptons(event);
    MissingEt missing_et = event.Hadrons().MissingEt();
    std::vector<Doublet> doublets;
    for (auto const & lepton : leptons) {
        Doublet pre_doublet(lepton, missing_et);
        std::vector<Doublet> post_doublets = ReconstructNeutrino(pre_doublet);
        for (auto & doublet : post_doublets) if (auto optional = function(doublet)) doublets.emplace_back(*optional);
    }
    return doublets;
}

using EnergyCubed = typename boost::units::multiply_typeof_helper< Energy, EnergySquare>::type;
using EnergySixth = typename boost::units::multiply_typeof_helper< EnergyCubed, EnergyCubed>::type;
static const EnergySixth GeV6 = boost::units::pow<6>(GeV);

std::vector<Doublet> WLeptonicTagger::ReconstructNeutrino(Doublet const& doublet) const
{
    INFO0;
    Lepton lepton = doublet.Singlet1();
    MissingEt missing_et = doublet.Singlet2();
    EnergySquare linear_term = (sqr(MassOf(Id::W)) - lepton.MassSquare()) / 2. + missing_et.Px() * lepton.Px() + missing_et.Py() * lepton.Py();
    MomentumSquare lepton_pz_square = sqr(lepton.Pz());
    EnergySquare lepton_square = sqr(lepton.Energy()) - lepton_pz_square;
    EnergySquare missing_et_square = sqr(missing_et.Px()) + sqr(missing_et.Py());
    EnergySixth radicant = lepton_pz_square * (sqr(linear_term) -  lepton_square * missing_et_square);
    if (radicant < 0. * GeV6) {
        INFO("Imaginary root", "move missing et towards lepton");
        return ReconstructNeutrino(Doublet(lepton, Lepton(missing_et + 0.1 * (lepton - missing_et), missing_et.Info())));
    }
    CHECK(radicant != 0. * GeV6, "Radicant exactly zero", "implement this case!");
    EnergyCubed sqrt = boost::units::sqrt(radicant);
    Energy neutrino_1_e = (lepton.Energy() * linear_term - sqrt) / lepton_square;
    Momentum neutrino_1_pz = (lepton_pz_square * linear_term - lepton.Energy() * sqrt) / lepton.Pz() / lepton_square;
    Lepton neutrino_1(missing_et.Px(), missing_et.Py(), neutrino_1_pz, neutrino_1_e);
    DEBUG(neutrino_1);
    std::vector<Doublet> doublets;
    doublets.emplace_back(Doublet(lepton, neutrino_1));

    Energy neutrino_2_e = (lepton.Energy() * linear_term + sqrt) / lepton_square;
    Momentum neutrino_2_pz = (lepton_pz_square * linear_term + lepton.Energy() * sqrt) / lepton.Pz() / lepton_square;
    Lepton neutrino_2(missing_et.Px(), missing_et.Py(), neutrino_2_pz, neutrino_2_e);
    DEBUG(neutrino_2);
    doublets.emplace_back(Doublet(lepton, neutrino_2));

    return doublets;
}

std::string WLeptonicTagger::Name() const
{
    return "WLeptonic";
}

std::string WLeptonicTagger::LatexName() const
{
    return Formula("W_{l}");
}

}

}
