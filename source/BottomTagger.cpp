# include "BottomTagger.hh"

namespace analysis {

BottomTagger::BottomTagger()
{
//     DebugLevel = kDebug;
    Print(kInformation, "Constructor");
    set_tagger_name("Bottom");
    DefineVariables();
}

int BottomTagger::Train(Event &event, PreCuts &pre_cuts, const Object::Tag tag)
{
    Print(kInformation, "Bottom Tag", tag);

    Jets particles = event.Partons().GenParticles();
    Jets bottoms = copy_if_abs_particle(particles, BottomId);
    Print(kInformation, "Particle size", bottoms.size());

    Jets jets = event.Hadrons().Jets();
    Print(kInformation, "Number Jets", jets.size());
    if (jets.empty()) return 0;

    Jets final_jets = CleanJets(jets, bottoms, pre_cuts, tag);

    if (pre_cuts.DoSubJets()) {

        Jets doublet_pieces = TrainOnSubJets(jets, bottoms, pre_cuts, tag, 2);
        final_jets = Join(final_jets, doublet_pieces);

        Jets triplet_pieces = TrainOnSubJets(jets, bottoms, pre_cuts, tag, 3);
        final_jets = Join(final_jets, triplet_pieces);

    }

    return SaveEntries(final_jets);
}

Jets BottomTagger::CleanJets(Jets &jets, const Jets &particles, PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "Clean Jets", jets.size(), particles.size());

    if (jets.empty()) return jets;
    for (const auto & particle : particles) {
        std::sort(jets.begin(), jets.end(), MinDeltaRTo(particle));
        if (jets.front().delta_R(particle) < DetectorGeometry().JetConeSize) static_cast<JetInfo &>(*jets.front().user_info_shared_ptr().get()).SetTag(kSignal);
    }

    Jets clean_jets;
    for (const auto & jet : jets) {
        if (!jet.has_user_info<JetInfo>()) {
            Print(kError, "Clean Jets", "No Jet Info");
            continue;
        }
        if (pre_cuts.PtLowerCut(BottomId) > 0 && jet.pt() < pre_cuts.PtLowerCut(BottomId)) continue;
        if (pre_cuts.PtUpperCut(BottomId) > 0 && jet.pt() > pre_cuts.PtUpperCut(BottomId)) continue;
        if (std::abs(jet.rap()) > DetectorGeometry().TrackerEtaMax) {
            Print(kInformation, "Clean Jets", "too large rap");
            continue;
        }
        if (jet.m() < 0) {
            Print(kInformation, "Clean Jets", "negative mass");
            continue;
        }
        if (tag == kSignal && jet.user_info<JetInfo>().SumDisplacement() == 0) {
            Print(kInformation, "Clean Jets", "no displacment");
            continue;
        }
        if (jet.user_info<JetInfo>().Tag() != tag) {
            Print(kDebug, "Clean Jets", "Not a b quark", jet.user_info<JetInfo>().Tag());
            continue;
        }
        clean_jets.emplace_back(jet);
    }
    Print(kInformation, "Jets", clean_jets.size(), particles.size());
    return clean_jets;
}

Jets BottomTagger::TrainOnSubJets(const Jets &jets, const Jets &particles, PreCuts &pre_cuts, const Tag tag, const int sub_jet_number)
{
    Print(kInformation, "Sub Jets");
    Jets pieces = SubJets(jets, sub_jet_number);
    return CleanJets(pieces, particles, pre_cuts, tag);
}

Jets BottomTagger::SubJets(const Jets &jets, const int sub_jet_number)
{
    Jets subjets;
    for (const auto & jet : jets) {
        Jets jets = Tagger::SubJets(jet, sub_jet_number);
        subjets = Join(subjets, jets);
    }
    return subjets;
}

Jets BottomTagger::Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Print(kInformation, "Jet Bdt");
    return Multiplets(event.Hadrons().Jets(), pre_cuts, reader);
}

Jets BottomTagger::Multiplets(const Jets &jets, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Jets final_jets;
    for (const auto jet : jets) {
        if (!jet.has_user_info<JetInfo>()) continue;
        if (jet.m() <= 0) continue;
        if (pre_cuts.PtLowerCut(BottomId) > 0 && jet.pt() < pre_cuts.PtLowerCut(BottomId)) continue;
        if (pre_cuts.PtUpperCut(BottomId) > 0 && jet.pt() > pre_cuts.PtUpperCut(BottomId)) continue;
        if (pre_cuts.TrackerMaxEta(BottomId) > 0 && std::abs(jet.rap()) > pre_cuts.TrackerMaxEta(BottomId)) continue;
        final_jets.emplace_back(Multiplet(jet, reader));
    }
    return final_jets;
}

fastjet::PseudoJet BottomTagger::Multiplet(const fastjet::PseudoJet &jet, const TMVA::Reader &reader)
{
    static_cast<JetInfo &>(*jet.user_info_shared_ptr().get()).SetBdt(Bdt(jet,reader));
    return jet;
}

Jets BottomTagger::SubMultiplet(const fastjet::PseudoJet &jet, const TMVA::Reader &reader, const int sub_jet_number)
{
    Jets jets;
    for (const auto sub_jet : Tagger::SubJets(jet, sub_jet_number)) {
        if (!sub_jet.has_user_info<JetInfo>()) continue;
        if (sub_jet.m() <= 0) continue;
        jets.emplace_back(Multiplet(sub_jet, reader));
    }
    return jets;
}

}
