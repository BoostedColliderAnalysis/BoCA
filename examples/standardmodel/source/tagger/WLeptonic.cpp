/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/fastjet/Particles.hh"
#include "boca/fastjet/Vector.hh"
#include "boca/Event.hh"
#include "standardmodel/tagger/WLeptonic.hh"
// #define DEBUGGING
#include "boca/generic/DEBUG_MACROS.hh"

namespace standardmodel
{

namespace tagger
{

namespace
{

Lepton FakeLepton(boca::Jet const &jet)
{
    INFO0;
    return jet * (Settings::LeptonMinPt() / jet.Pt());
}

std::vector<Lepton> Leptons(boca::Event const &event)
{
    INFO0;
    auto do_fake_leptons = true;
    auto leptons = RemoveIfSoft(event.Leptons(), Settings::LeptonMinPt());
    auto jets = SortedByPt(event.Jets());
    if (do_fake_leptons && leptons.empty() && !jets.empty()) leptons.emplace_back(FakeLepton(jets.front()));
    DEBUG(jets.size(), leptons.size());
    return leptons;
}

}

int WLeptonic::Train(boca::Event const &event, boca::PreCuts const &pre_cuts, Tag tag)
{
    INFO0;
    return SaveEntries(Doublets(event, [&](Doublet & doublet) -> boost::optional<Doublet> {
        if (Problematic(doublet, pre_cuts, tag)) return boost::none;
        doublet.SetTag(tag);
        return doublet;
    }), Particles(event), tag);
}

bool WLeptonic::Problematic(Doublet const &doublet, PreCuts const &pre_cuts, Tag tag) const
{
    INFO0;
    if (Problematic(doublet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal :
        if (pre_cuts.OutSideMassWindow(doublet, w_mass_window_, Id::W)) return true;
        if (pre_cuts.NotParticleRho(doublet)) return true;
        break;
    case Tag::background :
        break;
    }
    return false;
}

bool WLeptonic::Problematic(Doublet const &doublet, PreCuts const &pre_cuts) const
{
    INFO0;
    if (pre_cuts.ApplyCuts(Id::W, doublet)) return true;
    return false;
}

std::vector<Particle> WLeptonic::Particles(boca::Event const &event) const
{
    INFO0;
    auto particles = event.GenParticles();
    return CopyIfDaughter(CopyIfParticle(particles, Id::W), CopyIfMother(CopyIfLepton(particles), Id::W));
}

std::vector<Doublet> WLeptonic::Multiplets(boca::Event const &event, PreCuts const &pre_cuts, TMVA::Reader const &reader)
{
    INFO0;
    return Doublets(event, [&](Doublet & doublet) -> boost::optional<Doublet> {
        if (Problematic(doublet, pre_cuts)) return boost::none;
        doublet.SetBdt(Bdt(doublet, reader));
        return doublet;
    });
}

std::vector<Doublet> WLeptonic::Doublets(boca::Event const &event, std::function<boost::optional<Doublet>(Doublet &)> const &function) const
{
    INFO0;
//     std::vector<Lepton> leptons = SortedByPt(event.Leptons());
    auto leptons = Leptons(event);
    auto missing_et = event.MissingEt();
    auto doublets = std::vector<Doublet> {};
    for (auto const &lepton : leptons) {
        if (reconstruct_neutrino_) {
            auto reconstructed = ReconstructNeutrino(lepton, missing_et.Transverse());
            for (auto &doublet : reconstructed) if (auto optional = function(doublet)) doublets.emplace_back(*optional);
        } else {
            Doublet doublet(lepton, {});
            doublets.emplace_back(doublet);
        }
    }
    return doublets;
}

std::vector<Doublet> WLeptonic::ReconstructNeutrino(Lepton const &lepton, Vector2<Momentum> const &missing_et) const
{
    INFO0;
    auto linear_term = (sqr(MassOf(Id::W)) - lepton.MassSquare()) / 2. + missing_et * lepton.Transverse();
    auto lepton_pz_square = sqr(lepton.Pz());
    auto lepton_square = sqr(lepton.Energy()) - lepton_pz_square;
    auto radicant = lepton_pz_square * (sqr(linear_term) -  lepton_square * sqr(missing_et));
    if (radicant < 0_eV * eV * eV2 * eV2) {
        INFO("Imaginary root", "move missing et towards lepton");
        auto reco = missing_et + 0.1 * (lepton.Transverse() - missing_et);
        return ReconstructNeutrino(lepton, reco);
    }
    CHECK(radicant != 0_eV * eV * eV2 * eV2, "Radicant exactly zero", "implement this case!");
    auto sqrt = boost::units::sqrt(radicant);
    auto neutrino_1_e = (lepton.Energy() * linear_term - sqrt) / lepton_square;
    auto neutrino_1_pz = (lepton_pz_square * linear_term - lepton.Energy() * sqrt) / lepton.Pz() / lepton_square;
    auto neutrino_1 = Lepton {missing_et, neutrino_1_pz, neutrino_1_e};
    auto neutrino_2_e = (lepton.Energy() * linear_term + sqrt) / lepton_square;
    auto neutrino_2_pz = (lepton_pz_square * linear_term + lepton.Energy() * sqrt) / lepton.Pz() / lepton_square;
    auto neutrino_2 = Lepton {missing_et, neutrino_2_pz, neutrino_2_e};
    return {Doublet(lepton, neutrino_1), Doublet(lepton, neutrino_2)};
}

std::string WLeptonic::Name() const
{
    return "WLeptonic";
}

latex::String WLeptonic::LatexName() const
{
    return {"W_{l}", true};
}

void WLeptonic::DoNeutrinoReconstruction(bool do_it)
{
    reconstruct_neutrino_ =  do_it;
}

}

}
