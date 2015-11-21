/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "TauTagger.hh"

#include "Singlet.hh"
#include "Sort.hh"
#include "Vector.hh"
#include "Event.hh"
#include "Debug.hh"

namespace boca
{

namespace standardmodel
{

int TauTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info0;
   std::vector<Jet> jets = event.Hadrons().Jets();
    INFO("Number Jets", jets.size());
   std::vector<Particle> Particles = event.Partons().GenParticles();
    Particles = CopyIfParticle(Particles, Id::tau);
//     Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(Id::tau)), Particles.end());
//     if(Particles.size()!=1)
    INFO("Tau Partilces", Particles.size());
   std::vector<Jet> final_jets = CleanJets(jets, Particles, tag);
//     if(FinalJets.size()!=1)
    INFO("Tau Jets", final_jets.size());
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
    INFO("Clean Jets");
    for (auto const & Particle : Particles) {
        std::sort(jets.begin(), jets.end(), MinDeltaRTo(Particle));
        if (jets.front().delta_R(Particle) < 0.4)
            static_cast<JetInfo&>(*jets.front().user_info_shared_ptr().get()).SetTag(Tag::signal);
    }
   std::vector<Jet>NewCleanJets;
    for (auto const & Jet : jets) {
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

std::vector<Singlet> TauTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    std::vector<Singlet> final_jets;
    INFO("Jet Bdt");
   std::vector<Jet> jets = event.Hadrons().Jets();
    for (auto const & jet : jets) {
        if (!jet.has_user_info<JetInfo>()) {
            Error("Jet Bdt", "No Jet Info");
            continue;
        }
        static_cast<JetInfo&>(*jet.user_info_shared_ptr().get()).SetBdt(Bdt(jet, reader));
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
