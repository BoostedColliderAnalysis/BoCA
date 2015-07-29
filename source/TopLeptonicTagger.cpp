#include "TopLeptonicTagger.hh"
#include "Event.hh"
#include "WLeptonicTagger.hh"
#include "Debug.hh"

namespace analysis {

TopLeptonicTagger::TopLeptonicTagger()
{
  Info();
    top_mass_window = 80;
    DefineVariables();
}

int TopLeptonicTagger::Train(const Event& event, const analysis::PreCuts& pre_cuts, Tag tag) const
{
    Info();
    bool do_fake_leptons = false;
    Jets jets = fastjet::sorted_by_pt(bottom_reader_.Multiplets(event));
    if (jets.empty()) return 0;
    Info(jets.size());
    Jets leptons = event.Leptons().leptons();
    if (do_fake_leptons && leptons.empty()) leptons.emplace_back(FakeLepton(jets.front()));
    Info(leptons.size());
    std::vector<Doublet> doublets;
    if (use_w_) doublets = w_leptonic_reader_.Multiplets(event);
    else {
        Jets leptons = event.Leptons().leptons();
        for (const auto& lepton : leptons) doublets.emplace_back(Doublet(lepton));
    }
    std::vector<Triplet> triplets;
    for (const auto& jet : jets) {
        for (const auto& doublet : doublets) {
            Triplet triplet(doublet, jet);
            if (Problematic(triplet, pre_cuts, tag)) continue;
            triplets.emplace_back(triplet);
        }
    }
    Info(triplets.size());
    Jets tops = Particles(event);
    return SaveEntries(BestMatches(triplets, tops, tag));
}

fastjet::PseudoJet TopLeptonicTagger::FakeLepton(const fastjet::PseudoJet& jet) const
{
    return fastjet::PseudoJet(jet.px(), jet.py(), jet.pz(), jet.e()) / jet.pt() * DetectorGeometry::LeptonMinPt();
}

bool TopLeptonicTagger::Problematic(const Triplet& triplet, const PreCuts& pre_cuts) const
{
    if (pre_cuts.PtLowerCut(Id::top) > 0 && triplet.Jet().pt() < pre_cuts.PtLowerCut(Id::top)) return true;
    if (pre_cuts.PtUpperCut(Id::top) > 0 && triplet.Jet().pt() > pre_cuts.PtUpperCut(Id::top)) return true;
    if (pre_cuts.MassUpperCut(Id::top) > 0 && triplet.Jet().m() > pre_cuts.MassUpperCut(Id::top)) return true;
    return false;
}

Jets TopLeptonicTagger::Particles(const Event& event) const
{
    Jets particles = event.Partons().GenParticles();
    Jets leptons = fastjet::sorted_by_pt(event.Leptons().leptons());
    int lepton_charge = 1;
    if (!leptons.empty()) {
        lepton_charge = leptons.at(0).user_info<JetInfo>().Charge();
        Info(lepton_charge);
    }
    Jets tops = CopyIfExactParticle(particles, to_int(Id::top) * lepton_charge);
    return tops;
//         int w_leptonic_id = WLeptonicTagger().WLeptonicId(event);
//     int top_leptonic_id = sgn(w_leptonic_id) * to_int(Id::top);
//     return CopyIfExactParticle(particles, top_leptonic_id);
}

bool TopLeptonicTagger::Problematic(const analysis::Triplet& triplet, const analysis::PreCuts& pre_cuts, Tag tag) const
{
    if (Problematic(triplet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal :
        if (use_w_ && triplet.Doublet().Singlet1().Jet().pt() <= DetectorGeometry::LeptonMinPt()) return true;
        if (!use_w_ && triplet.Doublet().Jet().pt() <= DetectorGeometry::LeptonMinPt()) return true;
        if (std::abs(triplet.Jet().m() - Mass(Id::top) + 40) > top_mass_window) return true;
        break;
    case Tag::background :
        break;
    }
    return false;
}

std::vector<Triplet> TopLeptonicTagger::Multiplets(const Event& event, const analysis::PreCuts& pre_cuts, const TMVA::Reader& reader) const
{
    Info();
    bool do_fake_leptons = false;
    std::vector<Triplet> triplets;
    Jets jets = fastjet::sorted_by_pt(bottom_reader_.Multiplets(event));
    if (jets.empty()) return triplets;
    Jets leptons = event.Leptons().leptons();
    Debug(jets.size(), leptons.size());
    if (do_fake_leptons && leptons.empty()) leptons.emplace_back(FakeLepton(jets.front()));
    std::vector<Doublet> doublets;
    if (use_w_) doublets = w_leptonic_reader_.Multiplets(event);
    else {
        Jets leptons = event.Leptons().leptons();
        for (const auto& lepton : leptons)
            doublets.emplace_back(Doublet(lepton));
    }
    for (const auto& jet : jets) {
        for (const auto& doublet : doublets) {
            Triplet triplet(doublet, jet);
            if (Problematic(triplet, pre_cuts)) continue;
            triplet.SetBdt(Bdt(triplet, reader));
            triplets.emplace_back(triplet);
        }
    }
//     Error(triplets.size());
    return ReduceResult(triplets);
}

}
