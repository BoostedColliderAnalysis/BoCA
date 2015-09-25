/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "BottomTagger.hh"

#include "Event.hh"
#include "Vector.hh"
#include "PreCuts.hh"
#include "Debug.hh"

namespace boca {

BottomTagger::BottomTagger()
{
    Info();
    DefineVariables();
}

int BottomTagger::Train(Event const& event, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Info(boca::Name(tag));
    Jets jets = event.Hadrons().Jets();
    Info(jets.size());
    if (jets.empty()) return 0;
    Jets final_jets = CleanJets(jets, pre_cuts, tag);
    if (pre_cuts.DoSubJets()) {
        final_jets = Join(final_jets, TrainOnSubJets(jets, pre_cuts, tag, 2));
        final_jets = Join(final_jets, TrainOnSubJets(jets, pre_cuts, tag, 3));
    }
    Jets particles = event.Partons().Particles();
    Jets bottoms = CopyIfParticle(particles, Id::bottom);
    bottoms = RemoveIfSoft(bottoms, DetectorGeometry::JetMinPt());
    Info(bottoms.size());
    return SaveEntries(final_jets, bottoms, tag);
}

bool BottomTagger::Problematic(fastjet::PseudoJet const& jet, PreCuts const& pre_cuts, const Tag) const
{
    if (Problematic(jet, pre_cuts)) return true;
//     if (tag == Tag::signal && jet.user_info<JetInfo>().SumDisplacement() == 0) return true;
    //     if (jet.user_info<JetInfo>().Tag() != tag) return true;
    return false;
}

bool BottomTagger::Problematic(fastjet::PseudoJet const& jet, PreCuts const& pre_cuts) const
{
    if (!jet.has_user_info<JetInfo>()) return true;
    if (pre_cuts.PtLowerCut(Id::bottom) > at_rest && jet.pt() < pre_cuts.PtLowerCut(Id::bottom) / GeV) return true;
    if (pre_cuts.PtUpperCut(Id::bottom) > at_rest && jet.pt() > pre_cuts.PtUpperCut(Id::bottom) / GeV) return true;
    if (std::abs(jet.rap()) > DetectorGeometry::TrackerEtaMax()) return true;
    if (jet.m() < 0) return true;
    return false;
}

Jets BottomTagger::CleanJets(boca::Jets& jets, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Info(jets.size());
    if (jets.empty()) return jets;
    Jets clean_jets;
    for (auto const& jet : jets) {
        if (Problematic(jet, pre_cuts, tag)) continue;
        clean_jets.emplace_back(jet);
    }
    Info(clean_jets.size());
    return clean_jets;
}

Jets BottomTagger::TrainOnSubJets(boca::Jets const& jets, boca::PreCuts const& pre_cuts, Tag tag, int sub_jet_number) const
{
    Debug(sub_jet_number);
    Jets sub_jets = SubJets(jets, sub_jet_number);
    return CleanJets(sub_jets, pre_cuts, tag);
}

Jets BottomTagger::SubJets(boca::Jets const& jets, int sub_jet_number) const
{
    Jets subjets;
    for (auto const& jet : jets) subjets = Join(subjets, Tagger::SubJets(jet, sub_jet_number));
    return subjets;
}

Jets BottomTagger::Multiplets(Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info();
    return Multiplets(event.Hadrons().Jets(), pre_cuts, reader);
}

Jets BottomTagger::Multiplets(boca::Jets const& jets, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Jets final_jets;
    for (auto const& jet : jets) {
        if (Problematic(jet, pre_cuts))
            continue;
        final_jets.emplace_back(Multiplet(jet, reader));
    }
    return final_jets;
}

Jets BottomTagger::SubMultiplets(Jets const& jets, PreCuts const& pre_cuts, TMVA::Reader const& reader, size_t sub_jet_number) const
{
    Jets final_jets;
    for (auto const& sub_jet : SubJets(jets, sub_jet_number)) {
        if (Problematic(sub_jet, pre_cuts)) continue;
        final_jets.emplace_back(Multiplet(sub_jet, reader));
    }
    return final_jets;
}

fastjet::PseudoJet BottomTagger::Multiplet(fastjet::PseudoJet const& jet, TMVA::Reader const& reader) const
{
    static_cast<JetInfo&>(*jet.user_info_shared_ptr().get()).SetBdt(Bdt(jet, reader));
    return jet;
}

Jets BottomTagger::SubMultiplet(fastjet::PseudoJet const& jet, TMVA::Reader const& reader, int sub_jet_number) const
{
    Jets jets;
    for (auto const& sub_jet : Tagger::SubJets(jet, sub_jet_number)) {
        if (!sub_jet.has_user_info<JetInfo>()) continue;
        if (sub_jet.m() <= 0) continue;
        jets.emplace_back(Multiplet(sub_jet, reader));
    }
    return jets;
}

int BottomTagger::SaveBdt(Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Jets jets = event.Hadrons().Jets();
    Jets bottoms = Multiplets(jets, pre_cuts, reader);
    bottoms = Join(bottoms, SubMultiplets(jets, pre_cuts, reader, 2));
    bottoms = Join(bottoms, SubMultiplets(jets, pre_cuts, reader, 3));
    return SaveEntries(bottoms,2);
}

Jets BottomTagger::Multiplets(boca::Jets const& jets, TMVA::Reader const& reader) const
{
    PreCuts pre_cuts;
    return Multiplets(jets, pre_cuts, reader);
}

}

