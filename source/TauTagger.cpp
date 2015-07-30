#include "TauTagger.hh"

#include "fastjet/ClusterSequence.hh"
#include "Singlet.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis {

TauTagger::TauTagger()
{
    Info();
    DefineVariables();
}

int TauTagger::Train(const Event& event, const PreCuts&, Tag tag) const
{
    Info(analysis::Name(tag));
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
    for (const auto& final_jet : final_jets)
        singlets.emplace_back(Singlet(final_jet));
    return SaveEntries(singlets);
}


Jets TauTagger::CleanJets(analysis::Jets& jets, const analysis::Jets& Particles, Tag tag) const
{
    Info("Clean Jets");
    for (const auto& Particle : Particles) {
        std::sort(jets.begin(), jets.end(), MinDeltaRTo(Particle));
        if (jets.front().delta_R(Particle) < 0.4)
            static_cast<JetInfo*>(jets.front().user_info_shared_ptr().get())->SetTag(Tag::signal);
    }
    Jets NewCleanJets;
    for (const auto& Jet : jets) {
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

Jets TauTagger::Multiplets(const Event& event, const analysis::PreCuts&, const TMVA::Reader& reader) const
{
    Jets final_jets;
    Info("Jet Bdt");
    Jets jets = event.Hadrons().Jets();
    for (const auto& jet : jets) {
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
