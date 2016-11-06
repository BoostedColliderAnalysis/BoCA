/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/fastjet/Sort.hh"
#include "boca/fastjet/Particles.hh"
#include "boca/event/Event.hh"

#include "standardmodel/tagger/Tau.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace standardmodel
{

namespace tagger
{

int Tau::Train(boca::Event const& event, PreCuts const&, Tag tag)
{
    INFO0;
    auto jets = event.Jets();
    INFO(jets.size());
    auto particles = event.GenParticles();
    particles = CopyIfParticle(particles, Id::tau);
//     particles.erase(std::remove_if(particles.begin(), particles.end(), WrongAbsId(Id::tau)), particles.end());
//     if(particles.size()!=1)
    INFO(particles.size());
    auto final_jets = CleanJets(jets, particles, tag);
//     if(FinalJets.size()!=1)
    INFO(final_jets.size());
//    std::vector<Jet> Pieces = GetSubJets(jets, particles, Tag, 2);
//     FinalJets.insert(FinalJets.end(), Pieces.begin(), Pieces.end());
//
//    std::vector<Jet> Pieces2 = GetSubJets(jets, particles, Tag, 3);
//     FinalJets.insert(FinalJets.end(), Pieces2.begin(), Pieces2.end());
    auto singlets = std::vector<Singlet>{};
    for (auto const & final_jet : final_jets) singlets.emplace_back(Singlet(final_jet));
    return SaveEntries(singlets);
}


std::vector<boca::Jet> Tau::CleanJets(std::vector<boca::Jet>& jets, std::vector<Particle> const& particles, Tag tag) const
{
    INFO0;
    for (auto const & particle : particles) {
        SortedByMinDeltaRTo(jets, particle);
        if (jets.front().DeltaRTo(particle) < 0.4_rad) jets.front().Info().SetTag(Tag::signal);
    }
    auto new_clean_jets = std::vector<boca::Jet>{};
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
        new_clean_jets.emplace_back(Jet);
    }
    return new_clean_jets;
}

std::vector<Singlet> Tau::Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    auto jets = event.Jets();
    auto final_jets = std::vector<Singlet>{};
    for (auto & jet : jets) {
        jet.Info().SetBdt(Bdt(jet, reader));
        final_jets.emplace_back(Singlet(jet));
    }
    return final_jets;
}
std::string Tau::Name() const
{
    return "Tau";
}

}

}
