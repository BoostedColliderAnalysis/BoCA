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
    bool do_fake_leptons = false;
    Jets jets = fastjet::sorted_by_pt(bottom_reader_.Multiplets(event));
    if (jets.empty()) return 0;
    Info(jets.size());
    Jets leptons = event.Leptons().leptons();
    leptons = RemoveIfSoft(leptons,DetectorGeometry::LeptonMinPt());
    if (do_fake_leptons && leptons.empty()) leptons.emplace_back(FakeLepton(jets.front()));
    Info(leptons.size());
    std::vector<Doublet> doublets;
    if (use_w_) doublets = w_leptonic_reader_.Multiplets(event);
    else for (auto const& lepton : leptons) doublets.emplace_back(Doublet(lepton));

    Debug(jets.size(), doublets.size());
    std::vector<Triplet> triplets;
    for (auto const& jet : jets) {
        for (auto const& doublet : doublets) {
            Triplet triplet(doublet, jet);
            if (Problematic(triplet, pre_cuts, tag)) continue;
            triplet.SetTag(tag);
            triplets.emplace_back(triplet);
        }
    }
    Jets tops = Particles(event, pre_cuts);
    Debug(triplets.size(), tops.size());
//     std::vector<Triplet> matches = BestMatches(triplets, tops, tag);
//     Debug(matches.size());
//     if(tag == Tag::signal && matches.size() > tops.size()) return 0;
    return SaveEntries(triplets, tops, tag);
}

fastjet::PseudoJet TopLeptonicTagger::FakeLepton(fastjet::PseudoJet const& jet) const
{
    return fastjet::PseudoJet(jet.px(), jet.py(), jet.pz(), jet.e()) / jet.pt() * DetectorGeometry::LeptonMinPt();
}

Jets TopLeptonicTagger::Particles(Event const& event, PreCuts const& pre_cuts) const
{
    Jets particles = event.Partons().GenParticles();
    if (pre_cuts.SemiLeptonic()) {
      Jets leptons = fastjet::sorted_by_pt(event.Leptons().leptons());
      leptons = RemoveIfSoft(leptons,DetectorGeometry::LeptonMinPt());
        int lepton_charge = 1;
        if (!leptons.empty()) lepton_charge = leptons.front().user_info<JetInfo>().Charge();
        return CopyIfExactParticle(particles, to_int(Id::top) * lepton_charge);
    } else return CopyIfParticle(particles, Id::top);
}

bool TopLeptonicTagger::Problematic(Triplet const& triplet, PreCuts const& pre_cuts) const
{
    if (pre_cuts.PtLowerCut(Id::top) > 0 && triplet.Jet().pt() < pre_cuts.PtLowerCut(Id::top)) return true;
    if (pre_cuts.PtUpperCut(Id::top) > 0 && triplet.Jet().pt() > pre_cuts.PtUpperCut(Id::top)) return true;
    if (pre_cuts.MassUpperCut(Id::top) > 0 && triplet.Jet().m() > pre_cuts.MassUpperCut(Id::top)) return true;
    return false;
}

bool TopLeptonicTagger::Problematic(analysis::Triplet const& triplet, analysis::PreCuts const& pre_cuts, Tag tag) const
{
    if (Problematic(triplet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal :
        if (std::abs(triplet.Jet().m() - Mass(Id::top) + 40) > top_mass_window) return true;
        if (triplet.Singlet().Bdt()<0) return true;
        if ((triplet.Rho() < 0.5 || triplet.Rho() > 2) && triplet.Rho() > 0) return true;
        break;
    case Tag::background :
        break;
    }
    return false;
}

std::vector<Triplet> TopLeptonicTagger::Multiplets(Event const& event, analysis::PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info();
    bool do_fake_leptons = false;
    std::vector<Triplet> triplets;
    Jets jets = fastjet::sorted_by_pt(bottom_reader_.Multiplets(event));
    if (jets.empty()) return triplets;
    Jets leptons = event.Leptons().leptons();
    leptons = RemoveIfSoft(leptons,DetectorGeometry::LeptonMinPt());
    Debug(jets.size(), leptons.size());
    if (do_fake_leptons && leptons.empty()) leptons.emplace_back(FakeLepton(jets.front()));
    std::vector<Doublet> doublets;
    if (use_w_) doublets = w_leptonic_reader_.Multiplets(event);
    else for (auto const& lepton : leptons) doublets.emplace_back(Doublet(lepton));
    for (auto const& jet : jets) {
        for (auto const& doublet : doublets) {
            Triplet triplet(doublet, jet);
            if (Problematic(triplet, pre_cuts)) continue;
            triplet.SetBdt(Bdt(triplet, reader));
            triplets.emplace_back(triplet);
        }
    }
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
