/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "TopLeptonicTagger.hh"
#include "Event.hh"
#include "ParticleInfo.hh"
#include "Exception.hh"
#include "plotting/Font.hh"
// #define DEBUG
#include "Debug.hh"

namespace boca
{

namespace standardmodel
{

namespace
{

Lepton FakeLepton(Jet const& jet)
{
    Info0;
    return jet * (DetectorGeometry::LeptonMinPt() / jet.Pt());
}

std::vector<Lepton> Leptons(Event const& event, std::vector<Jet> const& jets)
{
    Info0;
    bool do_fake_leptons = true;
    std::vector<Lepton> leptons = RemoveIfSoft(event.Leptons().leptons(), DetectorGeometry::LeptonMinPt());
    if (do_fake_leptons && leptons.empty() && !jets.empty()) leptons.emplace_back(FakeLepton(jets.front()));
    Debug(jets.size(), leptons.size());
    return leptons;
}

}

TopLeptonicTagger::TopLeptonicTagger() :
    use_w_(true),
    w_leptonic_reader_(InitializeLeptonicReader())
{
    Info0;
    top_mass_window_ = 80_GeV;
    top_mass_shift_ = use_w_ ? 0_GeV : 40_GeV;
}

int TopLeptonicTagger::Train(Event const& event, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Info0;
    return SaveEntries(Triplets(event, [&](Triplet & triplet) {
        if (Problematic(triplet, pre_cuts, tag)) throw boca::Problematic();
        triplet.SetTag(tag);
        return triplet;
    }), Particles(event), tag);
}

std::vector<Particle> TopLeptonicTagger::Particles(Event const& event) const
{
    Info0;
    std::vector<Particle> particles = event.Partons().GenParticles();
    std::vector<Particle> leptons = CopyIfGrandMother(CopyIfLepton(particles), Id::top);
    return CopyIfGrandDaughter(particles, leptons);
}

bool TopLeptonicTagger::Problematic(boca::Triplet const& triplet, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Info0;
    if (Problematic(triplet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal :
        if (boost::units::abs(triplet.Mass() - MassOf(Id::top) + top_mass_shift_) > top_mass_window_) return true;
        if (pre_cuts.NotParticleRho(triplet)) return true;
        break;
    case Tag::background : break;
    }
    return false;
}

bool TopLeptonicTagger::Problematic(Triplet const& triplet, PreCuts const& pre_cuts) const
{
    Info0;
    if (pre_cuts.ApplyCuts(Id::top, triplet)) return true;
    return false;
}

std::vector<Triplet> TopLeptonicTagger::Triplets(Event const& event, std::function<Triplet(Triplet&)> const& function) const
{
    Info0;
    std::vector<Jet> jets = SortedByPt(bottom_reader_.Jets(event));
    std::vector<Lepton> leptons = Leptons(event, jets);
    Debug(jets.size(), leptons.size());
    std::vector<Doublet> doublets;
    if (use_w_) doublets = w_leptonic_reader_.Multiplets(event);
    else for (auto const & lepton : leptons) doublets.emplace_back(Doublet(lepton));
    std::vector<Triplet> triplets = pairs(doublets, jets, [&](Doublet const & doublet, Jet const & jet) {
        Debug(doublet.Rap(), jet.rap());
        Triplet triplet(doublet, jet);
        if (triplet.Mass() != triplet.Mass()) Error(triplet.Mass());
        return function(triplet);
    });
    return triplets;
}

std::vector<Triplet> TopLeptonicTagger::Multiplets(Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info0;
    return ReduceResult(Triplets(event, [&](Triplet & triplet) {
        if (Problematic(triplet, pre_cuts)) throw boca::Problematic();
        triplet.SetBdt(Bdt(triplet, reader));
        return triplet;
    }));
}

Stage TopLeptonicTagger::InitializeLeptonicReader()
{
    Info0;
    return use_w_ ? Stage::reader : Stage::trainer;
}

std::string TopLeptonicTagger::Name() const
{
    return "TopLeptonic";
}

std::string TopLeptonicTagger::LatexName() const
{
    return Formula("t_{l}");
}

boca::Filter TopLeptonicTagger::Filter() const
{
    boca::Filter filter("Pull1");
    if(!use_w_) filter.Add("BDT1");
    return filter;
}

}

}
