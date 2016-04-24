/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include <boost/range/algorithm/unique.hpp>

#include "boca/generic/Exception.hh"
#include "boca/multiplets/Particles.hh"
#include "boca/standardmodel/BottomTagger.hh"
#include "boca/PreCuts.hh"
#include "boca/Event.hh"
// #define DEBUGGING
// #define INFORMATION
#include "boca/generic/DEBUG.hh"

namespace boca
{

namespace standardmodel
{

BottomTagger::BottomTagger()
{
    INFO0;
    bottom_max_mass_ = 75_GeV;
}

int BottomTagger::Train(Event const& event, PreCuts const& pre_cuts, Tag tag)
{
    INFO0;
    auto jets = Jets(event, pre_cuts, [&](Jet & jet) {
        if (Problematic(jet, pre_cuts, tag)) throw boca::Problematic();
        return jet;
    });
    return SaveEntries(jets, Particles(event), tag);
}

std::vector<Particle> BottomTagger::Particles(Event const& event) const
{
    INFO0;
    auto particles = SortedByPhi(RemoveIfSoft(CopyIfParticle(event.Partons().Particles(), Id::bottom), DetectorGeometry::JetMinPt()));

//     ERROR(particles.size());
//     for(auto const& particle : particles) ERROR(particle.Mass(), particle.Pt(), particle.Rap(), particle.Phi());


    boost::erase(particles, boost::unique<boost::return_found_end>(particles,[](Particle const& particle_1, Particle const& particle_2){
      return particle_1.DeltaRTo(particle_2) < DetectorGeometry::IsolationConeSize();
    }));
//     ERROR(particles.size());
//     for(auto const& particle : particles) ERROR(particle.Mass(), particle.Pt(), particle.Rap(), particle.Phi());



    return particles;
}

std::vector<Jet> BottomTagger::Jets(Event const& event, PreCuts const& pre_cuts, std::function<Jet(Jet&)> const& function)
{
    INFO0;
    auto jets = event.Hadrons().Jets();
    INFO(jets.size());
    auto bottoms = Multiplets(jets, function);
    if (pre_cuts.DoSubJets(Id::bottom)) {
        Insert(bottoms, Multiplets(jets, function, 2));
        Insert(bottoms, Multiplets(jets, function, 3));
    }
    INFO(bottoms.size());
    return bottoms;
}

std::vector<Jet> BottomTagger::Multiplets(std::vector<Jet> jets, std::function<Jet(Jet&)> const& function, unsigned sub_jet_number) const
{
    INFO0;
    if (sub_jet_number > 1) jets = SubJets(jets, sub_jet_number);
    std::vector<Jet> final_jets;
    for (auto & jet : jets) try {
            DEBUG(jet.Mass(), jet.Pt(), jet.Rap(), jet.Phi());
            final_jets.emplace_back(function(jet));
        } catch (std::exception&) {
            continue;
        }
    return final_jets;
}

std::vector<Jet> BottomTagger::Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader)
{
    INFO0;
    return Jets(event, pre_cuts, [&](Jet & jet) {
        if (Problematic(jet, pre_cuts)) throw boca::Problematic();
        return Multiplet(jet, reader);
    });
}

Jet BottomTagger::Multiplet(Jet& jet, TMVA::Reader const& reader)
{
    INFO0;
    DEBUG(jet.Mass(), jet.Rap(), jet.Phi(), jet.has_user_info());
    jet.Info().SetBdt(Bdt(jet, reader));
    return jet;
}

bool BottomTagger::Problematic(Jet const& jet, PreCuts const& pre_cuts, Tag tag) const
{
    DEBUG0;
    if (Problematic(jet, pre_cuts)) return true;
    if (jet.Mass() > bottom_max_mass_) return true;
    if (boost::units::abs(jet.Rap()) > DetectorGeometry::TrackerEtaMax()) return true;
    switch (tag) {
    case Tag::signal :
        if (jet.Info().SumDisplacement() == 0_m) return true;
        break;
    case Tag::background : break;
    }
    return false;
}

bool BottomTagger::Problematic(Jet const& jet, PreCuts const& pre_cuts) const
{
    DEBUG0;
    if (pre_cuts.ApplyCuts(Id::bottom, jet)) return true;
    return false;
}

std::vector<Jet> BottomTagger::SubJets(std::vector<Jet> const& jets, int sub_jet_number) const
{
    INFO0;
    std::vector<Jet> subjets;
    for (auto const & jet : jets) Insert(subjets, Tagger::SubJets(jet, sub_jet_number));
    return subjets;
}

std::vector<Jet> BottomTagger::Jets(Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader)
{
    INFO0;
    return Multiplets(event.Hadrons().Jets(), [&](Jet & jet) {
        if (Problematic(jet, pre_cuts)) throw boca::Problematic();
        return Multiplet(jet, reader);
    });
}

std::vector<Jet> BottomTagger::SubMultiplet(Jet const& jet, TMVA::Reader const& reader, int sub_jet_number)
{
    INFO0;
    std::vector<Jet> jets;
    for (auto & sub_jet : Tagger::SubJets(jet, sub_jet_number)) {
//         if (sub_jet.Mass() <= massless) continue;
        jets.emplace_back(Multiplet(sub_jet, reader));
    }
    return jets;
//     boost::push_back(jets, Tagger::SubJets(jet, sub_jet_number) | boost::adaptors::transformed([&](Jet & sub_jet) -> Jet {
//         return Multiplet(sub_jet, reader);
//     }));
}

std::string BottomTagger::Name() const
{
    return "Bottom";
}

std::string BottomTagger::LatexName() const
{
    return "b";
}

}

}
