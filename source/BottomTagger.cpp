/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "BottomTagger.hh"

#include "Event.hh"
#include "Vector.hh"
#include "PreCuts.hh"
// #define INFORMATION
#include "Debug.hh"

namespace boca
{

BottomTagger::BottomTagger()
{
    Info();
    bottom_max_mass_ = 75. * GeV;
}

int BottomTagger::Train(Event const& event, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Info();
    boca::Jets jets = event.Hadrons().Jets();
    if (jets.empty()) return 0;
    boca::Jets final_jets = CleanJets(jets, pre_cuts, tag);
    if (pre_cuts.DoSubJets()) {
        final_jets = Join(final_jets, TrainOnSubJets(jets, pre_cuts, tag, 2));
        final_jets = Join(final_jets, TrainOnSubJets(jets, pre_cuts, tag, 3));
    }
    boca::Jets bottoms = Particles(event);
    return SaveEntries(final_jets, bottoms, tag);
}

boca::Jets BottomTagger::Particles(Event const& event) const
{
    Info();
    boca::Jets particles = event.Partons().Particles();
    boca::Jets bottoms = CopyIfParticle(particles, Id::bottom);
    bottoms = RemoveIfSoft(bottoms, DetectorGeometry::JetMinPt());
    Info(bottoms.size());
    return bottoms;
}

bool BottomTagger::Problematic(fastjet::PseudoJet const& jet, PreCuts const& pre_cuts, Tag tag) const
{
    Info();
    if (Problematic(jet, pre_cuts)) return true;
    if (jet.m() * GeV > bottom_max_mass_) return true;
    if (std::abs(jet.rap()) > DetectorGeometry::TrackerEtaMax()) return true;
    switch (tag) {
    case Tag::signal :
        if (jet.user_info<JetInfo>().SumDisplacement() == 0) return true;
        break;
    case Tag::background : break;
    }
    return false;
}

bool BottomTagger::Problematic(fastjet::PseudoJet const& jet, PreCuts const& pre_cuts) const
{
    Info();
    if (pre_cuts.ApplyCuts(Id::bottom, jet)) return true;
    return false;
}

boca::Jets BottomTagger::CleanJets(boca::Jets& jets, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Info(jets.size());
    if (jets.empty()) return jets;
    boca::Jets clean_jets;
    for (auto const & jet : jets) {
        if (Problematic(jet, pre_cuts, tag)) continue;
        clean_jets.emplace_back(jet);
    }
    Info(clean_jets.size());
    return clean_jets;
}

boca::Jets BottomTagger::TrainOnSubJets(boca::Jets const& jets, boca::PreCuts const& pre_cuts, Tag tag, int sub_jet_number) const
{
    Debug(sub_jet_number);
    boca::Jets sub_jets = SubJets(jets, sub_jet_number);
    return CleanJets(sub_jets, pre_cuts, tag);
}

boca::Jets BottomTagger::SubJets(boca::Jets const& jets, int sub_jet_number) const
{
    Info();
    boca::Jets subjets;
    for (auto const & jet : jets) subjets = Join(subjets, Tagger::SubJets(jet, sub_jet_number));
    return subjets;
}

boca::Jets BottomTagger::Multiplets(Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info();
    boca::Jets jets = event.Hadrons().Jets();
    boca::Jets bottoms = Multiplets(jets, pre_cuts, reader);
    bottoms = Join(bottoms, SubMultiplets(jets, pre_cuts, reader, 2));
    bottoms = Join(bottoms, SubMultiplets(jets, pre_cuts, reader, 3));
    return bottoms;
}

boca::Jets BottomTagger::Jets(Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info();
    return Multiplets(event.Hadrons().Jets(), pre_cuts, reader);
}

boca::Jets BottomTagger::Multiplets(boca::Jets const& jets, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info();
    boca::Jets final_jets;
    for (auto const & jet : jets) {
        if (Problematic(jet, pre_cuts)) continue;
        final_jets.emplace_back(Multiplet(jet, reader));
    }
    return final_jets;
}

boca::Jets BottomTagger::SubMultiplets(boca::Jets const& jets, PreCuts const& pre_cuts, TMVA::Reader const& reader, size_t sub_jet_number) const
{
    Info();
    boca::Jets final_jets;
    for (auto const & sub_jet : SubJets(jets, sub_jet_number)) {
        if (Problematic(sub_jet, pre_cuts)) continue;
        final_jets.emplace_back(Multiplet(sub_jet, reader));
    }
    return final_jets;
}

fastjet::PseudoJet BottomTagger::Multiplet(fastjet::PseudoJet const& jet, TMVA::Reader const& reader) const
{
    Info();
    static_cast<JetInfo&>(*jet.user_info_shared_ptr().get()).SetBdt(Bdt(jet, reader));
    return jet;
}

boca::Jets BottomTagger::SubMultiplet(fastjet::PseudoJet const& jet, TMVA::Reader const& reader, int sub_jet_number) const
{
    Info();
    boca::Jets jets;
    for (auto const & sub_jet : Tagger::SubJets(jet, sub_jet_number)) {
        if (!sub_jet.has_user_info<JetInfo>()) continue;
        if (sub_jet.m() <= 0) continue;
        jets.emplace_back(Multiplet(sub_jet, reader));
    }
    return jets;
}

std::string BottomTagger::Name() const
{
    return "Bottom";
}

std::string BottomTagger::NiceName() const
{
    return "b";
}

}

