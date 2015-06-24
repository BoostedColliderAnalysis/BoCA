# include "BottomTagger.hh"

namespace analysis
{

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

    Jets jets = event.Hadrons().Jets();
    Print(kInformation, "Number Jets", jets.size());
    if (jets.empty()) return 0;

    Jets final_jets = CleanJets(jets, pre_cuts, tag);
    if (pre_cuts.DoSubJets()) {
        final_jets = Join(final_jets, TrainOnSubJets(jets, pre_cuts, tag, 2));
        final_jets = Join(final_jets, TrainOnSubJets(jets, pre_cuts, tag, 3));
    }

    Jets particles = event.Partons().Particles();
    Jets bottoms = copy_if_abs_particle(particles, BottomId);
    bottoms = RemoveIfSoft(bottoms, DetectorGeometry().JetMinPt);
    Print(kInformation, "Particle size", bottoms.size());
    return SaveEntries(BestMatches(final_jets, bottoms, tag));
}

bool BottomTagger::Problematic(const fastjet::PseudoJet &jet, PreCuts &pre_cuts, const Tag tag) const
{
    if (Problematic(jet, pre_cuts)) return true;
    if (tag == kSignal && jet.user_info<JetInfo>().SumDisplacement() == 0) return true;
//     if (jet.user_info<JetInfo>().Tag() != tag) return true;
    return false;
}

bool BottomTagger::Problematic(const fastjet::PseudoJet &jet, PreCuts &pre_cuts) const
{
    if (!jet.has_user_info<JetInfo>())return true;
    if (pre_cuts.PtLowerCut(BottomId) > 0 && jet.pt() < pre_cuts.PtLowerCut(BottomId)) return true;
    if (pre_cuts.PtUpperCut(BottomId) > 0 && jet.pt() > pre_cuts.PtUpperCut(BottomId)) return true;
    if (pre_cuts.TrackerMaxEta(BottomId) > 0 && std::abs(jet.rap()) > pre_cuts.TrackerMaxEta(BottomId)) return true;
    if (jet.m() < 0) return true;
    return false;
}

Jets BottomTagger::CleanJets(Jets &jets, PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "Clean Jets", jets.size());

    if (jets.empty()) return jets;
    Jets clean_jets;
    for (const auto & jet : jets) {
        if (Problematic(jet, pre_cuts, tag)) continue;
        clean_jets.emplace_back(jet);
    }
    Print(kInformation, "Jets", clean_jets.size());
    return clean_jets;
}

Jets BottomTagger::TrainOnSubJets(const Jets &jets, PreCuts &pre_cuts, const Tag tag, const int sub_jet_number)
{
    Print(kDebug, "Sub Jets", sub_jet_number);
    Jets sub_jets = SubJets(jets, sub_jet_number);
    return CleanJets(sub_jets, pre_cuts, tag);
}

Jets BottomTagger::SubJets(const Jets &jets, const int sub_jet_number)
{
    Jets subjets;
    for (const auto & jet : jets) subjets = Join(subjets, Tagger::SubJets(jet, sub_jet_number));
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
        if (Problematic(jet, pre_cuts)) continue;
        final_jets.emplace_back(Multiplet(jet, reader));
    }
    return final_jets;
}

Jets BottomTagger::SubMultiplets(const Jets &jets, PreCuts &pre_cuts, const TMVA::Reader &reader, const std::size_t sub_jet_number)
{
    Jets final_jets;
    for (const auto sub_jet : SubJets(jets, sub_jet_number)) {
        if (Problematic(sub_jet, pre_cuts)) continue;
        final_jets.emplace_back(Multiplet(sub_jet, reader));
    }
    return final_jets;
}

fastjet::PseudoJet BottomTagger::Multiplet(const fastjet::PseudoJet &jet, const TMVA::Reader &reader)
{
    static_cast<JetInfo &>(*jet.user_info_shared_ptr().get()).SetBdt(Bdt(jet, reader));
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

int BottomTagger::GetBdt(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Jets jets = event.Hadrons().Jets();
    Jets bottoms = Multiplets(jets, pre_cuts, reader);
    bottoms = Join(bottoms, SubMultiplets(jets, pre_cuts, reader, 2));
    bottoms = Join(bottoms, SubMultiplets(jets, pre_cuts, reader, 3));
//     return SaveEntries(ReduceResult(bottoms),2);
    return SaveEntries(bottoms);
}

Jets BottomTagger::Multiplets(const Jets &jets, const TMVA::Reader &reader)
{
    PreCuts pre_cuts;
    return Multiplets(jets, pre_cuts, reader);
}

}

