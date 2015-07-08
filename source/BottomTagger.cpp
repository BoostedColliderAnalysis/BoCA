#include "BottomTagger.hh"
#include "Event.hh"
#include "Predicate.hh"
#include "PreCuts.hh"
#include "Debug.hh"

namespace analysis
{

BottomTagger::BottomTagger()
{
    Info();
    DefineVariables();
}

int BottomTagger::Train(const Event &event, analysis::PreCuts &pre_cuts, const analysis::Tag tag) const
{
    Info(Name(tag));

    Jets jets = event.Hadrons().Jets();
    Info(jets.size());
    if (jets.empty()) return 0;

    Jets final_jets = CleanJets(jets, pre_cuts, tag);
    if (pre_cuts.DoSubJets()) {
        final_jets = Join(final_jets, TrainOnSubJets(jets, pre_cuts, tag, 2));
        final_jets = Join(final_jets, TrainOnSubJets(jets, pre_cuts, tag, 3));
    }

    Jets particles = event.Partons().Particles();
    Jets bottoms = CopyIfAbsParticle(particles, Id::bottom);
//     Jets tops = CopyIfAbsParticle(particles, Id::top);
//     Jets higgs = CopyIfAbsParticle(particles, Id::higgs);
    bottoms = RemoveIfSoft(bottoms, DetectorGeometry().JetMinPt());
    Info(bottoms.size());
    return SaveEntries(BestMatches(final_jets, bottoms, tag));
}

bool BottomTagger::Problematic(const fastjet::PseudoJet &jet, PreCuts &pre_cuts, const Tag tag) const
{
    if (Problematic(jet, pre_cuts)) return true;
//     if (tag == Tag::signal && jet.user_info<JetInfo>().SumDisplacement() == 0) return true;
//     if (jet.user_info<JetInfo>().Tag() != tag) return true;
    return false;
}

bool BottomTagger::Problematic(const fastjet::PseudoJet &jet, PreCuts &pre_cuts) const
{
    if (!jet.has_user_info<JetInfo>())return true;
    if (pre_cuts.PtLowerCut(Id::bottom) > 0 && jet.pt() < pre_cuts.PtLowerCut(Id::bottom)) return true;
    if (pre_cuts.PtUpperCut(Id::bottom) > 0 && jet.pt() > pre_cuts.PtUpperCut(Id::bottom)) return true;
    if (pre_cuts.TrackerMaxEta(Id::bottom) > 0 && std::abs(jet.rap()) > pre_cuts.TrackerMaxEta(Id::bottom)) return true;
    if (jet.m() < 0) return true;
    return false;
}

Jets BottomTagger::CleanJets(analysis::Jets &jets, analysis::PreCuts &pre_cuts, const analysis::Tag tag) const
{
    Info(jets.size());

    if (jets.empty()) return jets;
    Jets clean_jets;
    for (const auto & jet : jets) {
        if (Problematic(jet, pre_cuts, tag)) continue;
        clean_jets.emplace_back(jet);
    }
    Info(clean_jets.size());
    return clean_jets;
}

Jets BottomTagger::TrainOnSubJets(const analysis::Jets &jets, analysis::PreCuts &pre_cuts, const analysis::Tag tag, const int sub_jet_number) const
{
    Debug(sub_jet_number);
    Jets sub_jets = SubJets(jets, sub_jet_number);
    return CleanJets(sub_jets, pre_cuts, tag);
}

Jets BottomTagger::SubJets(const analysis::Jets &jets, const int sub_jet_number) const
{
    Jets subjets;
    for (const auto & jet : jets) subjets = Join(subjets, Tagger::SubJets(jet, sub_jet_number));
    return subjets;
}

Jets BottomTagger::Multiplets(const Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader) const
{
    Info();
    return Multiplets(event.Hadrons().Jets(), pre_cuts, reader);
}

Jets BottomTagger::Multiplets(const analysis::Jets &jets, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader) const
{
    Jets final_jets;
    for (const auto &jet : jets) {
        if (Problematic(jet, pre_cuts)) continue;
        final_jets.emplace_back(Multiplet(jet, reader));
    }
    return final_jets;
}

Jets BottomTagger::SubMultiplets(const Jets &jets, PreCuts &pre_cuts, const TMVA::Reader &reader, const std::size_t sub_jet_number) const
{
    Jets final_jets;
    for (const auto &sub_jet : SubJets(jets, sub_jet_number)) {
        if (Problematic(sub_jet, pre_cuts)) continue;
        final_jets.emplace_back(Multiplet(sub_jet, reader));
    }
    return final_jets;
}

fastjet::PseudoJet BottomTagger::Multiplet(const fastjet::PseudoJet &jet, const TMVA::Reader &reader) const
{
    static_cast<JetInfo &>(*jet.user_info_shared_ptr().get()).SetBdt(Bdt(jet, reader));
    return jet;
}

Jets BottomTagger::SubMultiplet(const fastjet::PseudoJet &jet, const TMVA::Reader &reader, const int sub_jet_number) const
{
    Jets jets;
    for (const auto &sub_jet : Tagger::SubJets(jet, sub_jet_number)) {
        if (!sub_jet.has_user_info<JetInfo>()) continue;
        if (sub_jet.m() <= 0) continue;
        jets.emplace_back(Multiplet(sub_jet, reader));
    }
    return jets;
}

int BottomTagger::GetBdt(const Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader) const
{
    Jets jets = event.Hadrons().Jets();
    Jets bottoms = Multiplets(jets, pre_cuts, reader);
    bottoms = Join(bottoms, SubMultiplets(jets, pre_cuts, reader, 2));
    bottoms = Join(bottoms, SubMultiplets(jets, pre_cuts, reader, 3));
//     return SaveEntries(ReduceResult(bottoms),2);
    return SaveEntries(bottoms);
}

Jets BottomTagger::Multiplets(const analysis::Jets &jets, const TMVA::Reader &reader) const
{
    PreCuts pre_cuts;
    return Multiplets(jets, pre_cuts, reader);
}

}

