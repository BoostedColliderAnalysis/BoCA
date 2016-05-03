/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/generic/Exception.hh"
#include "boca/multiplets/Particles.hh"
#include "boca/standardmodel/TopLeptonicTagger.hh"
#include "boca/Event.hh"
// #define DEBUGGING
#include "boca/generic/DEBUG.hh"

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

std::vector<Lepton> Leptons(Event const& event, std::vector<Jet> const& jets)
{
    INFO0;
    auto do_fake_leptons = true;
    auto leptons = RemoveIfSoft(event.Leptons().leptons(), DetectorGeometry::LeptonMinPt());
    if (do_fake_leptons && leptons.empty() && !jets.empty()) leptons.emplace_back(FakeLepton(jets.front()));
    DEBUG(jets.size(), leptons.size());
    return leptons;
}

}

TopLeptonicTagger::TopLeptonicTagger(Id id) :
    id_(id),
    use_w_(false),
    w_leptonic_reader_(InitializeLeptonicReader())
{
    INFO0;
    if (id_ == Id::top)  top_mass_window_ = 80_GeV;
    top_mass_shift_ = use_w_ ? 0_GeV : 40_GeV;
}

int TopLeptonicTagger::Train(Event const& event, boca::PreCuts const& pre_cuts, Tag tag)
{
    INFO0;
    return SaveEntries(Triplets(event, [&](Triplet & triplet) {
        if (Problematic(triplet, pre_cuts, tag)) throw boca::Problematic();
        triplet.SetTag(tag);
        return triplet;
    }), Particles(event), tag);
}

std::vector<Particle> TopLeptonicTagger::Particles(Event const& event) const
{
    INFO0;
    auto particles = event.Partons().GenParticles();
    auto leptons = CopyIfGrandMother(CopyIfLepton(particles), id_);
    return CopyIfGrandDaughter(particles, leptons);
}

bool TopLeptonicTagger::Problematic(boca::Triplet const& triplet, boca::PreCuts const& pre_cuts, Tag tag) const
{
    INFO0;
    if (Problematic(triplet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal :
        if (id_ == Id::top && boost::units::abs(triplet.Mass() - MassOf(id_) + top_mass_shift_) > top_mass_window_) return true;
        if (pre_cuts.NotParticleRho(triplet)) return true;
        break;
    case Tag::background : break;
    }
    return false;
}

bool TopLeptonicTagger::Problematic(Triplet const& triplet, PreCuts const& pre_cuts) const
{
    INFO0;
    if (pre_cuts.ApplyCuts(id_, triplet)) return true;
    return false;
}

std::vector<Triplet> TopLeptonicTagger::Triplets(Event const& event, std::function<Triplet(Triplet&)> const& function)
{
    INFO0;
    auto jets = SortedByPt(bottom_reader_.Jets(event));
    auto leptons = Leptons(event, jets);
    DEBUG(jets.size(), leptons.size());
    std::vector<Doublet> doublets;
    if (use_w_) doublets = w_leptonic_reader_.Multiplets(event);
    else for (auto const & lepton : leptons) {
            Doublet doublet;
            doublet.Enforce(lepton);
            doublets.emplace_back(doublet);
        }
    auto triplets = Pairs(doublets, jets, [&](Doublet const & doublet, Jet const & jet) {
        DEBUG(doublet.Rap(), jet.rap());
        Triplet triplet(doublet, jet);
        CHECK(triplet.Mass() == triplet.Mass(), triplet.Mass());
        return function(triplet);
    });
    return triplets;
}

std::vector<Triplet> TopLeptonicTagger::Multiplets(Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader)
{
    INFO0;
    return Triplets(event, [&](Triplet & triplet) {
        if (Problematic(triplet, pre_cuts)) throw boca::Problematic();
        triplet.SetBdt(Bdt(triplet, reader));
        return triplet;
    });
}

Stage TopLeptonicTagger::InitializeLeptonicReader()
{
    INFO0;
    return use_w_ ? Stage::reader : Stage::trainer;
}

std::string TopLeptonicTagger::Name() const
{
    return "TopLeptonic";
}

latex::String TopLeptonicTagger::LatexName() const
{
    return {"t_{l}", true};
}

boca::Filter TopLeptonicTagger::Filter() const
{
    boca::Filter filter("Pull1");
    if (!use_w_) filter.Add("BDT1");
    return filter;
}

}

}
