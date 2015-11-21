/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "TopLeptonicTagger.hh"
#include "Event.hh"
#include "WLeptonicTagger.hh"
#include "ParticleInfo.hh"
#include "Exception.hh"
// #define DEBUG
#include "Debug.hh"

namespace boca
{

namespace standardmodel
{

TopLeptonicTagger::TopLeptonicTagger() : w_leptonic_reader_(InitializeLeptonicReader())
{
    Info0;
    top_mass_window = 80. * GeV;
}

int TopLeptonicTagger::Train(Event const& event, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Info0;
    std::vector<Jet> jets = SortedByPt(bottom_reader_.Jets(event));
    INFO(jets.size());
    std::vector<Jet> leptons = Leptons(event, jets);
    std::vector<Doublet> doublets;
    if (use_w_) doublets = w_leptonic_reader_.Multiplets(event);
    else for (auto const & lepton : leptons) doublets.emplace_back(Doublet(lepton));

    Debug(jets.size(), doublets.size());
    std::vector<Triplet> triplets = pairs(doublets, jets, [&](Doublet const & doublet, Jet const & jet) {
        Triplet triplet(doublet, jet);
        if (Problematic(triplet, pre_cuts, tag)) throw boca::Problematic();
        triplet.SetTag(tag);
        return triplet;
    });
    std::vector<Particle> tops = Particles(event);
    int size = tops.size();
    std::string particle = "";
    if (size > 0) particle = boca::Name(tops.front().Info().Family().Particle().Id());
    Debug(size, particle);
    Debug(triplets.size(), tops.size(), leptons.size());
    return SaveEntries(triplets, tops, tag);
}

std::vector<Jet> TopLeptonicTagger::Leptons(Event const& event, std::vector<Jet> const& jets) const
{
    bool do_fake_leptons = false;
    std::vector<Jet> leptons = event.Leptons().leptons();
    leptons = RemoveIfSoft(leptons, DetectorGeometry::LeptonMinPt());
    if (do_fake_leptons && leptons.empty()) leptons.emplace_back(FakeLepton(jets.front()));
    Debug(jets.size(), leptons.size());
    return leptons;
}

Jet TopLeptonicTagger::FakeLepton(Jet const& jet) const
{
    return Jet(jet) / jet.pt() * (DetectorGeometry::LeptonMinPt() / GeV);
}

std::vector<Particle> TopLeptonicTagger::Particles(Event const& event) const
{
    std::vector<Particle> particles = event.Partons().GenParticles();
    std::vector<Particle> leptons = CopyIfLepton(particles);
    leptons = CopyIfGrandMother(leptons, Id::top);
    return CopyIfGrandDaughter(particles, leptons);
}

bool TopLeptonicTagger::Problematic(boca::Triplet const& triplet, boca::PreCuts const& pre_cuts, Tag tag) const
{
    if (Problematic(triplet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal :
        if (boost::units::abs(triplet.Mass() - MassOf(Id::top) + 40. * GeV) > top_mass_window) return true;
        if (pre_cuts.NotParticleRho(triplet)) return true;
        break;
    case Tag::background : break;
    }
    return false;
}

bool TopLeptonicTagger::Problematic(Triplet const& triplet, PreCuts const& pre_cuts) const
{
    if (pre_cuts.ApplyCuts(Id::top, triplet)) return true;
    return false;
}

std::vector<Triplet> TopLeptonicTagger::Multiplets(Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info0;
    std::vector<Jet> jets = SortedByPt(bottom_reader_.Jets(event));
    std::vector<Jet> leptons = Leptons(event, jets);
    std::vector<Doublet> doublets;
    if (use_w_) doublets = w_leptonic_reader_.Multiplets(event);
    else for (auto const & lepton : leptons) doublets.emplace_back(Doublet(lepton));
    std::vector<Triplet> triplets = pairs(doublets, jets, [&](Doublet const & doublet, Jet const & jet) {
        Triplet triplet(doublet, jet);
        if (Problematic(triplet, pre_cuts)) throw boca::Problematic();
        triplet.SetBdt(Bdt(triplet, reader));
        return triplet;
    });
    return ReduceResult(triplets);
}

Stage TopLeptonicTagger::InitializeLeptonicReader()
{
    if (use_w_) return Stage::reader;
    else return Stage::trainer;
}

std::string TopLeptonicTagger::Name() const
{
    return "TopLeptonic";
}

std::string TopLeptonicTagger::NiceName() const
{
    return "t_{l}";
}

}

}
