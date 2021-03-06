/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/generic/Exception.hh"
#include "boca/fastjet/Particles.hh"
#include "standardmodel/tagger/TopLeptonic.hh"
#include "boca/event/Event.hh"
// #define NOTIFICATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace standardmodel
{

namespace tagger
{

namespace
{

Lepton FakeLepton(boca::Jet const& jet)
{
    INFO0;
    return jet * (Settings::LeptonMinPt() / jet.Pt());
}

std::vector<Lepton> Leptons(boca::Event const& event, std::vector<boca::Jet> const& jets)
{
    INFO0;
    auto do_fake_leptons = true;
    auto leptons = RemoveIfSoft(event.Leptons(), Settings::LeptonMinPt());
    if (do_fake_leptons && leptons.empty() && !jets.empty()) leptons.emplace_back(FakeLepton(jets.front()));
    DEBUG(jets.size(), leptons.size());
    return leptons;
}

}

TopLeptonic::TopLeptonic(Id id) :
    id_(id),
    use_w_(true),
    w_leptonic_reader_(InitializeLeptonicReader())
{
    INFO0;
    if (id_ == Id::top) {
        top_mass_window_ = 80_GeV;
        top_mass_shift_ = use_w_ ? 0_GeV : 40_GeV;
    }
}

int TopLeptonic::Train(boca::Event const& event, boca::PreCuts const& pre_cuts, Tag tag)
{
    INFO0;
    return SaveEntries(Triplets(event, [&](Triplet & triplet) {
        if (Problematic(triplet, pre_cuts, tag)) throw boca::Problematic();
        triplet.SetTag(tag);
        return triplet;
    }), Particles(event), tag);
}

std::vector<Particle> TopLeptonic::Particles(boca::Event const& event) const
{
    INFO0;
    auto particles = event.GenParticles();

//     auto TOPs = CopyIfParticle(particles,  Id::top);
//     for (auto const& TOP : TOPs) NOTE(TOP.Info().Family());



    auto leptons = CopyIfLepton(particles);
    NOTE(leptons);
    for (auto const& lepton :  leptons) NOTE(lepton.Info().Family());
    auto test = CopyIfGrandMother(leptons, id_);
    auto test_2 = CopyIfGrandMother(leptons, Id::top_partner);
    Insert(test, test_2);
    NOTE(test,  id_);
    auto tops = CopyIfGrandDaughter(particles, test);
    NOTE(tops);
    return tops;
}

bool TopLeptonic::Problematic(boca::Triplet const& triplet, boca::PreCuts const& pre_cuts, Tag tag) const
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

bool TopLeptonic::Problematic(Triplet const& triplet, PreCuts const& pre_cuts) const
{
    INFO0;
    if (pre_cuts.ApplyCuts(id_, triplet)) return true;
    return false;
}

std::vector<Triplet> TopLeptonic::Triplets(boca::Event const& event, std::function<Triplet(Triplet&)> const& function)
{
    INFO0;
    auto jets = SortedByPt(bottom_reader_.Jets(event));
    auto leptons = Leptons(event, jets);
    DEBUG(jets.size(), leptons.size());
    auto doublets = std::vector<Doublet>{};
    if (use_w_) doublets = w_leptonic_reader_.Multiplets(event);
    else for (auto const & lepton : leptons) {
            auto doublet = Doublet{};
            doublet.Enforce(lepton);
            doublets.emplace_back(doublet);
        }
    auto triplets = Pairs(doublets, jets, [&](Doublet const & doublet, boca::Jet const & jet) {
        DEBUG(doublet.Rap(), jet.Rap());
        auto triplet = Triplet{doublet, jet};
        CHECK(triplet.Mass() == triplet.Mass(), triplet.Mass());
        return function(triplet);
    });
    NOTE(triplets.size());
    return triplets;
}

std::vector<Triplet> TopLeptonic::Multiplets(boca::Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader)
{
    INFO0;
    return Triplets(event, [&](Triplet & triplet) {
        if (Problematic(triplet, pre_cuts)) throw boca::Problematic();
        triplet.SetBdt(Bdt(triplet, reader));
        return triplet;
    });
}

Stage TopLeptonic::InitializeLeptonicReader()
{
    INFO0;
    return use_w_ ? Stage::reader : Stage::trainer;
}

std::string TopLeptonic::Name() const
{
    return "TopLeptonic";
}

latex::String TopLeptonic::LatexName() const
{
    return {"t_{l}", true};
}

boca::Filter TopLeptonic::Filter() const
{
    auto filter = boca::Filter{"Pull1"};
    if (!use_w_) filter.Add("BDT1");
    return filter;
}

}

}
