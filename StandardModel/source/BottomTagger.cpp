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

namespace standardmodel
{

BottomTagger::BottomTagger()
{
    Info0;
    bottom_max_mass_ = 75. * GeV;
}

int BottomTagger::Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const
{
    Info0;
    return SaveEntries(Jets(event, pre_cuts, [&](fastjet::PseudoJet & jet) {
        if (Problematic(jet, pre_cuts, tag)) throw boca::Problematic();
        return jet;
    }), Particles(event), tag);
}

boca::Jets BottomTagger::Particles(Event const& event) const
{
    Info0;
    return RemoveIfSoft(CopyIfParticle(event.Partons().Particles(), Id::bottom), DetectorGeometry::JetMinPt());
}

Jets BottomTagger::Jets(Event const& event, PreCuts const& pre_cuts, std::function<fastjet::PseudoJet(fastjet::PseudoJet&)> const& function) const
{
    Info0;
    boca::Jets jets = event.Hadrons().Jets();
    Info(jets.size());
    boca::Jets bottoms = Multiplets(jets, function);
    if (pre_cuts.DoSubJets(Id::bottom)) {
        bottoms = Join(bottoms, Multiplets(jets, function, 2));
        bottoms = Join(bottoms, Multiplets(jets, function, 3));
    }
    Info(bottoms.size());
    return bottoms;
}

boca::Jets BottomTagger::Multiplets(boca::Jets jets, std::function<fastjet::PseudoJet(fastjet::PseudoJet&)> const& function, unsigned sub_jet_number) const
{
    Info0;
    if (sub_jet_number > 1) jets = SubJets(jets, sub_jet_number);
    boca::Jets final_jets;
    for (auto & jet : jets) try {
            final_jets.emplace_back(function(jet));
        } catch (std::exception&) {
            continue;
        }
    return final_jets;
}

boca::Jets BottomTagger::Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info0;
    return Jets(event, pre_cuts, [&](fastjet::PseudoJet const & jet) {
        if (Problematic(jet, pre_cuts)) throw boca::Problematic();
        return Multiplet(jet, reader);
    });
}

fastjet::PseudoJet BottomTagger::Multiplet(fastjet::PseudoJet const& jet, TMVA::Reader const& reader) const
{
    Info0;
    if(jet.has_user_info<JetInfo>()) static_cast<JetInfo&>(*jet.user_info_shared_ptr().get()).SetBdt(Bdt(jet, reader));
    else{
      Error("no user info");
//       jet.user_info(new JetInfo(Bdt(jet, reader)));
    }
    return jet;
}

bool BottomTagger::Problematic(fastjet::PseudoJet const& jet, PreCuts const& pre_cuts, Tag tag) const
{
    Info0;
    if (Problematic(jet, pre_cuts)) return true;
    if (jet.m() * GeV > bottom_max_mass_) return true;
    if (std::abs(jet.rap()) * rad > DetectorGeometry::TrackerEtaMax()) return true;
    switch (tag) {
    case Tag::signal :
        if (jet.user_info<JetInfo>().SumDisplacement() == 0. * mm) return true;
        break;
    case Tag::background : break;
    }
    return false;
}

bool BottomTagger::Problematic(fastjet::PseudoJet const& jet, PreCuts const& pre_cuts) const
{
    Info0;
    if (pre_cuts.ApplyCuts(Id::bottom, jet)) return true;
    return false;
}

boca::Jets BottomTagger::SubJets(boca::Jets const& jets, int sub_jet_number) const
{
    Info0;
    boca::Jets subjets;
    for (auto const & jet : jets) subjets = Join(subjets, Tagger::SubJets(jet, sub_jet_number));
    return subjets;
}

boca::Jets BottomTagger::Jets(Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info0;
    return Multiplets(event.Hadrons().Jets(), [&](fastjet::PseudoJet & jet) {
        if (Problematic(jet, pre_cuts)) throw boca::Problematic();
        return Multiplet(jet, reader);
    });
}

boca::Jets BottomTagger::SubMultiplet(fastjet::PseudoJet const& jet, TMVA::Reader const& reader, int sub_jet_number) const
{
    Info0;
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

}

