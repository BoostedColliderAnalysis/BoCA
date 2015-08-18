/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "TopLeptonicTagger.hh"
#include "Event.hh"
#include "WLeptonicTagger.hh"
#include "Debug.hh"

namespace analysis
{

TopLeptonicTagger::TopLeptonicTagger() : w_leptonic_reader_(InitializeLeptonicReader())
{
    Info();
    top_mass_window = 80;
    DefineVariables();
}

int TopLeptonicTagger::Train(Event const& event, analysis::PreCuts const& pre_cuts, Tag tag) const
{
    Info();
    Jets jets = fastjet::sorted_by_pt(bottom_reader_.Multiplets(event));
    Info(jets.size());
    Jets leptons = Leptons(event, jets);
    std::vector<Doublet> doublets;
    if (use_w_) doublets = w_leptonic_reader_.Multiplets(event);
    else for (auto const & lepton : leptons) doublets.emplace_back(Doublet(lepton));

    Debug(jets.size(), doublets.size());
    std::vector<Triplet> triplets = pairs(doublets, jets, [&](Doublet const & doublet, fastjet::PseudoJet const & jet) {
        Triplet triplet(doublet, jet);
        if (Problematic(triplet, pre_cuts, tag)) throw "problematic";
        triplet.SetTag(tag);
        return triplet;
    });
    Jets tops = Particles(event, pre_cuts);
    Error(triplets.size(), tops.size(), leptons.size());
    return SaveEntries(triplets, tops, tag);
}

Jets TopLeptonicTagger::Leptons(Event const& event, Jets const& jets) const
{
    bool do_fake_leptons = false;
    Jets leptons = event.Leptons().leptons();
    leptons = RemoveIfSoft(leptons, DetectorGeometry::LeptonMinPt());
    if (do_fake_leptons && leptons.empty()) leptons.emplace_back(FakeLepton(jets.front()));
    Debug(jets.size(), leptons.size());
    return leptons;
}

fastjet::PseudoJet TopLeptonicTagger::FakeLepton(fastjet::PseudoJet const& jet) const
{
    return fastjet::PseudoJet(jet.px(), jet.py(), jet.pz(), jet.e()) / jet.pt() * DetectorGeometry::LeptonMinPt();
}

Jets TopLeptonicTagger::Particles(Event const& event, PreCuts const& pre_cuts) const
{
    Jets particles = event.Partons().GenParticles();
    if (!pre_cuts.SemiLeptonic()) return CopyIfParticle(particles, Id::top);
    Jets leptons = fastjet::sorted_by_pt(event.Leptons().leptons());
    leptons = RemoveIfSoft(leptons, DetectorGeometry::LeptonMinPt());
    int lepton_charge = 1;
    if (!leptons.empty()) lepton_charge = leptons.front().user_info<JetInfo>().Charge();
    return CopyIfExactParticle(particles, to_int(Id::top) * lepton_charge);
}

bool TopLeptonicTagger::Problematic(analysis::Triplet const& triplet, analysis::PreCuts const& pre_cuts, Tag tag) const
{
    if (Problematic(triplet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal :
        if (std::abs(triplet.Jet().m() - Mass(Id::top) + 40) > top_mass_window) return true;
        if (triplet.Singlet().Bdt() < 0) return true;
        if ((triplet.Rho() < 0.5 || triplet.Rho() > 2) && triplet.Rho() > 0) return true;
        break;
    case Tag::background :
        break;
    }
    return false;
}

bool TopLeptonicTagger::Problematic(Triplet const& triplet, PreCuts const& pre_cuts) const
{
    if (pre_cuts.PtLowerCut(Id::top) > 0 && triplet.Jet().pt() < pre_cuts.PtLowerCut(Id::top)) return true;
    if (pre_cuts.PtUpperCut(Id::top) > 0 && triplet.Jet().pt() > pre_cuts.PtUpperCut(Id::top)) return true;
    if (pre_cuts.MassUpperCut(Id::top) > 0 && triplet.Jet().m() > pre_cuts.MassUpperCut(Id::top)) return true;
    return false;
}

std::vector<Triplet> TopLeptonicTagger::Multiplets(Event const& event, analysis::PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info();
    Jets jets = fastjet::sorted_by_pt(bottom_reader_.Multiplets(event));
    Jets leptons = Leptons(event, jets);
    std::vector<Doublet> doublets;
    if (use_w_) doublets = w_leptonic_reader_.Multiplets(event);
    else for (auto const & lepton : leptons) doublets.emplace_back(Doublet(lepton));
    std::vector<Triplet> triplets = pairs(doublets, jets, [&](Doublet const & doublet, fastjet::PseudoJet const & jet) {
        Triplet triplet(doublet, jet);
        if (Problematic(triplet, pre_cuts)) throw "problematic";
        triplet.SetBdt(Bdt(triplet, reader));
        return triplet;
    });
    return ReduceResult(triplets);
}

int TopLeptonicTagger::TopLeptonicId(Event const& event) const
{
    return sgn(w_leptonic_reader_.Tagger().WLeptonicId(event)) * to_int(Id::top);
}

Stage TopLeptonicTagger::InitializeLeptonicReader()
{
    if (use_w_) return Stage::reader;
    else return Stage::trainer;
}

}
