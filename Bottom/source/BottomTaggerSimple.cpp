# include "BottomTaggerSimple.hh"

# include "Event.hh"
# include "Reader.hh"

namespace analysis
{

namespace bottom
{

BottomTaggerSimple::BottomTaggerSimple()
{
//     DebugLevel = kDebug;
    Print(kInformation, "Constructor");
    set_tagger_name("Bottom");
    DefineVariables();
}

int BottomTaggerSimple::Train(Event &event, const Object::Tag tag)
{
    Print(kInformation, "Bottom Tag", tag);
    Jets particles = event.Partons().GenParticles();
    particles = RemoveIfWrongAbsParticle(particles, BottomId);
    Print(kInformation, "Particle size", particles.size());
    Jets jets = event.Hadrons().Jets();
    Print(kInformation, "Number Jets", jets.size());
    if (jets.empty()) return 0;
    jets = CleanJets(jets, particles, tag);
    Print(kDebug, "Number B Jets", jets.size());
    SaveEntries(jets);
    return jets.size();
}

Jets BottomTaggerSimple::CleanJets(Jets &jets, const Jets &particles, const Tag tag)
{
    Print(kInformation, "Clean Jets");
    for (const auto & particle : particles) {
        jets = SortedByMinDeltaRTo(jets, particle);
        if (jets.front().delta_R(particle) < detector_geometry().JetConeSize) static_cast<JetInfo &>(*jets.front().user_info_shared_ptr().get()).SetTag(kSignal);
    }
    Jets clean_jets;
    for (const auto & Jet : jets) {
        if (!Jet.has_user_info<JetInfo>())continue;
        if (std::abs(Jet.rap()) > detector_geometry().TrackerEtaMax) continue;
        if (Jet.m() < 0) continue;
        if (tag == kSignal && Jet.user_info<JetInfo>().SumDisplacement() == 0) continue;
        Print(kDebug, "Jet Tag", Jet.user_info<JetInfo>().Tag());
        clean_jets.emplace_back(Jet);
    }
    return clean_jets;
}

int BottomTaggerSimple::GetBdt(Event &event, const TMVA::Reader &reader)
{
    Jets jets = event.Hadrons().Jets();
    Jets final_jets;
    Print(kInformation, "Jet Bdt");
    for (const auto & jet : jets) {
        if (std::abs(jet.rap()) > detector_geometry().TrackerEtaMax) continue;
        if (!jet.has_user_info<JetInfo>()) continue;
        if (jet.m() <= 0) continue;
        static_cast<JetInfo &>(*jet.user_info_shared_ptr().get()).SetBdt(Bdt(jet,reader));
        final_jets.emplace_back(jet);
    }
    SaveEntries(final_jets);
    return final_jets.size();
}

}

}
