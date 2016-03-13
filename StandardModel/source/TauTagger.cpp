/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "TauTagger.hh"

#include "Sort.hh"
#include "Vector.hh"
#include "Event.hh"
#include "DEBUG.hh"

namespace boca
{

namespace standardmodel
{

int TauTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    INFO0;
    std::vector<Jet> jets = event.Hadrons().Jets();
    INFO(jets.size());
    std::vector<Particle> Particles = event.Partons().GenParticles();
    Particles = CopyIfParticle(Particles, Id::tau);
//     Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(Id::tau)), Particles.end());
//     if(Particles.size()!=1)
    INFO(Particles.size());
    std::vector<Jet> final_jets = CleanJets(jets, Particles, tag);
//     if(FinalJets.size()!=1)
    INFO(final_jets.size());
//    std::vector<Jet> Pieces = GetSubJets(jets, Particles, Tag, 2);
//     FinalJets.insert(FinalJets.end(), Pieces.begin(), Pieces.end());
//
//    std::vector<Jet> Pieces2 = GetSubJets(jets, Particles, Tag, 3);
//     FinalJets.insert(FinalJets.end(), Pieces2.begin(), Pieces2.end());
    std::vector<Singlet> singlets;
    for (auto const & final_jet : final_jets) singlets.emplace_back(Singlet(final_jet));
    return SaveEntries(singlets);
}


std::vector<Jet> TauTagger::CleanJets(std::vector<Jet>& jets, std::vector<Particle> const& Particles, Tag tag) const
{
    INFO0;
    for (auto const & Particle : Particles) {
        SortedByMinDeltaRTo(jets, Particle);
        if (jets.front().DeltaRTo(Particle) < 0.4_rad) jets.front().Info().SetTag(Tag::signal);
    }
    std::vector<Jet> NewCleanJets;
    for (auto const & Jet : jets) {

//         if (std::abs(Jet.rap()) > 2.5) continue;
// if (Jet.m() < 0){
//   ERROR("Clean Jets", "Massless Jet");
//           continue;
//         }
//         if (Tag == Tag::signal && Jet.Info().SumDisplacement() == 0) continue;
        if (Jet.Info().Tag() != tag) {
//   ERROR("Clean Jets", "Not Tagged Jet");
            continue;
        }
        NewCleanJets.emplace_back(Jet);
    }
    return NewCleanJets;
}

std::vector<Singlet> TauTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    std::vector<Singlet> final_jets;
    INFO0;
    std::vector<Jet> jets = event.Hadrons().Jets();
    for (auto & jet : jets) {
        jet.Info().SetBdt(Bdt(jet, reader));
        final_jets.emplace_back(Singlet(jet));
    }
    return final_jets;
}
std::string TauTagger::Name() const
{
    return "Tau";
}

}

}
