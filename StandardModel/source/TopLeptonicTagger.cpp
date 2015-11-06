/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "TopLeptonicTagger.hh"
#include "Event.hh"
#include "WLeptonicTagger.hh"
#include "ParticleInfo.hh"
#include "Exception.hh"
// #define DEBUG
#include "Debug.hh"

namespace boca
{

namespace standardmodel
{

TopLeptonicTagger::TopLeptonicTagger() : w_leptonic_reader_(InitializeLeptonicReader())
{
    Info0;
    top_mass_window = 80. * GeV;
}

int TopLeptonicTagger::Train(Event const& event, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Info0;
    Jets jets = fastjet::sorted_by_pt(bottom_reader_.Jets(event));
    Info(jets.size());
    Jets leptons = Leptons(event, jets);
    std::vector<Doublet> doublets;
    if (use_w_) doublets = w_leptonic_reader_.Multiplets(event);
    else for (auto const & lepton : leptons) doublets.emplace_back(Doublet(lepton));

    Debug(jets.size(), doublets.size());
    std::vector<Triplet> triplets = pairs(doublets, jets, [&](Doublet const & doublet, fastjet::PseudoJet const & jet) {
        Triplet triplet(doublet, jet);
        if (Problematic(triplet, pre_cuts, tag)) throw boca::Problematic();
        triplet.SetTag(tag);
        return triplet;
    });
    Jets tops = Particles(event/*, pre_cuts*/);
    int size = tops.size();
    std::string particle = "";
    if (size > 0) particle = boca::Name(tops.front().user_info<ParticleInfo>().Family().particle().id());
    Debug(size, particle);
    Debug(triplets.size(), tops.size(), leptons.size());
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
    return fastjet::PseudoJet(jet) / jet.pt() * (DetectorGeometry::LeptonMinPt() / GeV);
}

Jets TopLeptonicTagger::Particles(Event const& event/*, PreCuts const& pre_cuts*/) const
{
    Jets particles = event.Partons().GenParticles();
    Jets leptons = CopyIfLepton(particles);
    leptons = CopyIfGrandMother(leptons, Id::top);
    if (leptons.empty()) return {};
    Check(leptons.size() == 1, leptons.size());
    int grand_mother = leptons.front().user_info<ParticleInfo>().Family().grand_mother().id();
    Info(grand_mother);
    return CopyIfExactParticle(particles, grand_mother);
//     if (!pre_cuts.SemiLeptonic()) return CopyIfParticle(particles, Id::top);
//     Jets leptons = fastjet::sorted_by_pt(event.Leptons().leptons());
//     leptons = RemoveIfSoft(leptons, DetectorGeometry::LeptonMinPt());
//     int lepton_charge = 1;
//     if (!leptons.empty()) lepton_charge = leptons.front().user_info<JetInfo>().Charge();
//     return CopyIfExactParticle(particles, to_int(Id::top) * lepton_charge);
}

bool TopLeptonicTagger::Problematic(boca::Triplet const& triplet, boca::PreCuts const& pre_cuts, Tag tag) const
{
    if (Problematic(triplet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal :
        if (boost::units::abs(triplet.Mass() - MassOf(Id::top) + 40. * GeV) > top_mass_window) return true;
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
    if (pre_cuts.ApplyCuts(Id::top, triplet)) return true;
    return false;
}

std::vector<Triplet> TopLeptonicTagger::Multiplets(Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info0;
    Jets jets = fastjet::sorted_by_pt(bottom_reader_.Jets(event));
    Jets leptons = Leptons(event, jets);
    std::vector<Doublet> doublets;
    if (use_w_) doublets = w_leptonic_reader_.Multiplets(event);
    else for (auto const & lepton : leptons) doublets.emplace_back(Doublet(lepton));
    std::vector<Triplet> triplets = pairs(doublets, jets, [&](Doublet const & doublet, fastjet::PseudoJet const & jet) {
        Triplet triplet(doublet, jet);
        if (Problematic(triplet, pre_cuts)) throw boca::Problematic();
        triplet.SetBdt(Bdt(triplet, reader));
        return triplet;
    });
    return ReduceResult(triplets);
}

Stage TopLeptonicTagger::InitializeLeptonicReader()
{
    if (use_w_) return Stage::reader;
    else return Stage::trainer;
}

std::string TopLeptonicTagger::Name() const
{
    return "TopLeptonic";
}

std::string TopLeptonicTagger::NiceName() const
{
    return "t_{l}";
}

}

}
