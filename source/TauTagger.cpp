/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "TauTagger.hh"

#include "Singlet.hh"
#include "Sort.hh"
#include "Vector.hh"
#include "Event.hh"
#include "Debug.hh"

namespace boca {

TauTagger::TauTagger()
{
    Info();
    DefineVariables();
}

int TauTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info();
    Jets jets = event.Hadrons().Jets();
    Info("Number Jets", jets.size());
    Jets Particles = event.Partons().GenParticles();
    Particles = CopyIfParticle(Particles, Id::tau);
//     Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(Id::tau)), Particles.end());
//     if(Particles.size()!=1)
    Info("Tau Partilces", Particles.size());
    Jets final_jets = CleanJets(jets, Particles, tag);
//     if(FinalJets.size()!=1)
    Info("Tau Jets", final_jets.size());
//     Jets Pieces = GetSubJets(jets, Particles, Tag, 2);
//     FinalJets.insert(FinalJets.end(), Pieces.begin(), Pieces.end());
//
//     Jets Pieces2 = GetSubJets(jets, Particles, Tag, 3);
//     FinalJets.insert(FinalJets.end(), Pieces2.begin(), Pieces2.end());
    std::vector<Singlet> singlets;
    for (auto const& final_jet : final_jets)
        singlets.emplace_back(Singlet(final_jet));
    return SaveEntries(singlets);
}


Jets TauTagger::CleanJets(boca::Jets& jets, boca::Jets const& Particles, Tag tag) const
{
    Info("Clean Jets");
    for (auto const& Particle : Particles) {
        std::sort(jets.begin(), jets.end(), MinDeltaRTo(Particle));
        if (jets.front().delta_R(Particle) < 0.4)
            static_cast<JetInfo&>(*jets.front().user_info_shared_ptr().get()).SetTag(Tag::signal);
    }
    Jets NewCleanJets;
    for (auto const& Jet : jets) {
        if (!Jet.has_user_info<JetInfo>()) {
            Error("Clean Jets", "No Jet Info");
            continue;
        }
//         if (std::abs(Jet.rap()) > 2.5) continue;
// if (Jet.m() < 0){
//   Error("Clean Jets", "Massless Jet");
//           continue;
//         }
//         if (Tag == Tag::signal && Jet.user_info<JetInfo>().SumDisplacement() == 0) continue;
        if (Jet.user_info<JetInfo>().Tag() != tag) {
//   Error("Clean Jets", "Not Tagged Jet");
            continue;
        }
        NewCleanJets.emplace_back(Jet);
    }
    return NewCleanJets;
}

Jets TauTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    Jets final_jets;
    Info("Jet Bdt");
    Jets jets = event.Hadrons().Jets();
    for (auto const& jet : jets) {
        if (!jet.has_user_info<JetInfo>()) {
            Error("Jet Bdt", "No Jet Info");
            continue;
        }
        static_cast<JetInfo&>(*jet.user_info_shared_ptr().get()).SetBdt(Bdt(jet, reader));
        final_jets.emplace_back(jet);
    }
    return final_jets;
}

}
