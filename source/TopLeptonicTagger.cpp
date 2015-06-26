# include "TopLeptonicTagger.hh"

namespace analysis
{

TopLeptonicTagger::TopLeptonicTagger()
{
    //     debug_level_ = Severity::debug;
    Print(Severity::notification, "Constructor");
    set_tagger_name("TopLeptonic");
    bottom_reader_.SetTagger(bottom_tagger_);
    top_mass_window = 80;
    DefineVariables();
}

int TopLeptonicTagger::Train(Event &event, PreCuts &pre_cuts, const Tag tag)
{
    Print(Severity::information, "Train");
    do_fake_leptons = true;
    Jets jets = fastjet::sorted_by_pt(bottom_reader_.Multiplets<BottomTagger>(event));
    if (jets.empty()) return 0;
    Print(Severity::information, "Jet Number", jets.size());

    Jets leptons = event.Leptons().leptons();
    if (leptons.empty()) leptons.emplace_back(FakeLepton(jets.front()));
    Print(Severity::information, "Lepton Number", leptons.size());

    std::vector<Doublet> doublets;
    for (const auto & jet : jets) {
        for (const auto & lepton : leptons) {
            Doublet doublet(jet, lepton);
            if (tag == Tag::signal && doublet.Jet().m()<20) continue;
 	    if (tag == Tag::signal && lepton.delta_R(jet)>1.0) continue;
            doublets.emplace_back(doublet);
        }
   }
    
    for(const auto & jet :jets){
      if(doublets.size() >= 0) break;
      const float Lepton_fake_pt=1;    
      fastjet::PseudoJet lepton_fake=fastjet::PseudoJet(jet.px(), jet.py(), jet.pz(), jet.e()) / jet.pt()*Lepton_fake_pt;
      Doublet doublet(jet, lepton_fake);
      doublets.emplace_back(doublet);
    }

    Print(Severity::information, "Number doublets", doublets.size());
    Jets tops = Particles(event);
    return SaveEntries(BestMatches(doublets, tops, tag));
}

fastjet::PseudoJet TopLeptonicTagger::FakeLepton(const fastjet::PseudoJet &jet) const
{
    return fastjet::PseudoJet(jet.px(), jet.py(), jet.pz(), jet.e()) / jet.pt() * DetectorGeometry().LeptonMinPt;
}

bool TopLeptonicTagger::Problematic(const Doublet &doublet, PreCuts &pre_cuts) const
{
    if (pre_cuts.PtLowerCut(Id::top) > 0 && doublet.Jet().pt() < pre_cuts.PtLowerCut(Id::top)) return true;
    if (pre_cuts.PtUpperCut(Id::top) > 0 && doublet.Jet().pt() > pre_cuts.PtUpperCut(Id::top)) return true;
    if (pre_cuts.MassUpperCut(Id::top) > 0 && doublet.Jet().m() > pre_cuts.MassUpperCut(Id::top)) return true;
    return false;
}

Jets TopLeptonicTagger::Particles(Event &event) const
{
    Jets particles = event.Partons().GenParticles();
    return copy_if_abs_particle(particles, Id::top);
}

bool TopLeptonicTagger::Problematic(const analysis::Doublet &doublet, analysis::PreCuts &pre_cuts, const analysis::Tag tag) const
{
    if (Problematic(doublet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal :
        if (doublet.Singlet1().Jet().pt() <= DetectorGeometry().LeptonMinPt) return true;
        if (std::abs(doublet.Jet().m() - Mass(Id::top) + 40) > top_mass_window) return true;
        break;
    case Tag::background :
        break;
    }

std::vector<Doublet> TopLeptonicTagger::Clean_Doublets(const std::vector< Doublet > &Doublets, PreCuts &pre_cuts)
{
    
    std::vector<Doublet> clean_doublets;
    for(const auto &doublet : Doublets){
    if(pre_cuts.PtLowerCut(Id::top) > 0 && doublet.Jet().pt() < pre_cuts.PtLowerCut(Id::top)) continue;
    if(pre_cuts.PtUpperCut(Id::top) > 0 && doublet.Jet().pt() > pre_cuts.PtUpperCut(Id::top)) continue;
    if(pre_cuts.MassUpperCut(Id::top) > 0 && doublet.Jet().m()> pre_cuts.MassUpperCut(Id::top)) continue;
    clean_doublets.emplace_back(doublet);
    }
    return clean_doublets;

}

std::vector<Doublet> TopLeptonicTagger::Multiplets(analysis::Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Print(Severity::information, "Bdt");
    std::vector<Doublet> doublets;
    Jets jets = fastjet::sorted_by_pt(bottom_reader_.Multiplets<BottomTagger>(event));
    if (jets.empty()) return doublets;
    Jets leptons = event.Leptons().leptons();
    if (leptons.empty()) leptons.emplace_back(FakeLepton(jets.front()));

    for (const auto & jet : jets) {
        for (const auto & lepton : leptons) {
            Doublet doublet(jet, lepton);
            if (Problematic(doublet, pre_cuts)) continue;
            doublet.SetBdt(Bdt(doublet, reader));
            doublets.emplace_back(doublet);
        }
    }
    
    for(const auto & jet :jets){
      if(doublets.size() > 0) break;
      const int Lepton_fake_pt=1;
      fastjet::PseudoJet lepton_fake=fastjet::PseudoJet(jet.px(), jet.py(), jet.pz(), jet.e())/jet.pt()*Lepton_fake_pt;
      Doublet doublet(jet, lepton_fake);
      doublet.SetBdt(Bdt(doublet,reader));
      doublets.emplace_back(doublet);
    }
    
    std::vector<Doublet> final_doublets=Clean_Doublets(doublets, pre_cuts);
    return ReduceResult(final_doublets);

}

}
