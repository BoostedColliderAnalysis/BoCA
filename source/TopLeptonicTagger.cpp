#include "TopLeptonicTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis
{

TopLeptonicTagger::TopLeptonicTagger()
{
    Note();
    top_mass_window = 80;
    DefineVariables();
}

int TopLeptonicTagger::Train(const Event &event, analysis::PreCuts &pre_cuts, const analysis::Tag tag) const
{
    Info("Train");
    bool do_fake_leptons = false;
    Jets jets = fastjet::sorted_by_pt(bottom_reader_.Multiplets(event));
    if (jets.empty()) return 0;
    Info("Jet Number", jets.size());

    Jets leptons = event.Leptons().leptons();
    if (do_fake_leptons && leptons.empty()) leptons.emplace_back(FakeLepton(jets.front()));
    Info("Lepton Number", leptons.size());

    std::vector<Doublet> doublets;
    for (const auto & jet : jets) {
        for (const auto & lepton : leptons) {
            Doublet doublet(jet, lepton);
            if (Problematic(doublet, pre_cuts, tag)) continue;
            doublets.emplace_back(doublet);
        }
    }

    Info("Number doublets", doublets.size());
    Jets tops = Particles(event);
    return SaveEntries(BestMatches(doublets, tops, tag));
}

fastjet::PseudoJet TopLeptonicTagger::FakeLepton(const fastjet::PseudoJet &jet) const
{
    return fastjet::PseudoJet(jet.px(), jet.py(), jet.pz(), jet.e()) / jet.pt() * DetectorGeometry().LeptonMinPt();
}

bool TopLeptonicTagger::Problematic(const Doublet &doublet, PreCuts &pre_cuts) const
{
    if (pre_cuts.PtLowerCut(Id::top) > 0 && doublet.Jet().pt() < pre_cuts.PtLowerCut(Id::top)) return true;
    if (pre_cuts.PtUpperCut(Id::top) > 0 && doublet.Jet().pt() > pre_cuts.PtUpperCut(Id::top)) return true;
    if (pre_cuts.MassUpperCut(Id::top) > 0 && doublet.Jet().m() > pre_cuts.MassUpperCut(Id::top)) return true;
    return false;
}

Jets TopLeptonicTagger::Particles(const Event &event) const
{
    Jets particles = event.Partons().GenParticles();
    return CopyIfAbsParticle(particles, Id::top);
}

bool TopLeptonicTagger::Problematic(const analysis::Doublet &doublet, analysis::PreCuts &pre_cuts, const analysis::Tag tag) const
{
    if (Problematic(doublet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal :
        if (doublet.Singlet1().Jet().pt() <= DetectorGeometry().LeptonMinPt()) return true;
        if (std::abs(doublet.Jet().m() - Mass(Id::top) + 40) > top_mass_window) return true;
        break;
    case Tag::background :
        break;
    }

    return false;
}

std::vector<Doublet> TopLeptonicTagger::Multiplets(const Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader) const
{
    Info();

    bool do_fake_leptons = false;

    std::vector<Doublet> doublets;
    Jets jets = fastjet::sorted_by_pt(bottom_reader_.Multiplets(event));
    if (jets.empty()) return doublets;
    Jets leptons = event.Leptons().leptons();
    Debug(jets.size(), leptons.size());
    if (do_fake_leptons && leptons.empty()) leptons.emplace_back(FakeLepton(jets.front()));

    for (const auto & jet : jets) {
        for (const auto & lepton : leptons) {
            Doublet doublet(jet, lepton);
            if (Problematic(doublet, pre_cuts)) continue;
            doublet.SetBdt(Bdt(doublet, reader));
            doublets.emplace_back(doublet);
        }
    }
    return ReduceResult(doublets);
}

}
