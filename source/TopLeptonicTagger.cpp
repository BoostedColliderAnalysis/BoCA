# include "TopLeptonicTagger.hh"

namespace analysis {

TopLeptonicTagger::TopLeptonicTagger()
{
    //     debug_level_ = Severity::debug;
    Print(Severity::notification, "Constructor");
    set_tagger_name("TopLeptonic");
    bottom_reader_.SetTagger(bottom_tagger_);

    top_mass_window = std::abs(Mass(Id::top) - Mass(Id::higgs))/2;

    DefineVariables();
}

int TopLeptonicTagger::Train(Event &event, PreCuts &pre_cuts, const Tag tag)
{
    Print(Severity::information, "Train");
    std::size_t number_of_tops = 2;
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    Print(Severity::information, "Jet Number", jets.size());

    Jets leptons = event.Leptons().leptons();

    Print(Severity::information, "Lepton Number", leptons.size());


    std::vector<Doublet> doublets;
    for (const auto & lepton : leptons){
 	if (lepton.pt()<50) continue;
        for (const auto & jet : jets) {
            Doublet doublet(jet, lepton);
 //           if (tag == kSignal && std::abs(doublet.Jet().m() - Mass(Id::top)) > top_mass_window) continue;
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

    Print(Severity::information, "Number JetPairs", doublets.size());
    std::vector<Doublet> final_doublets=Clean_Doublets(doublets, pre_cuts);


    
    Jets particles = event.Partons().GenParticles();
    Jets tops = copy_if_abs_particle(particles, Id::top);
    switch (tag) {
    case Tag::signal :
        final_doublets = BestMatch(final_doublets, tops);
        break;
    case Tag::background  :
        final_doublets = RemoveBestMatch(final_doublets, tops);
        break;
    }
    
    
    return SaveEntries(final_doublets);
}

std::vector<Doublet> TopLeptonicTagger::Clean_Doublets(const std::vector< Doublet > &Doublets, PreCuts &pre_cuts)
{
    
    std::vector<Doublet> clean_doublets;
    for(const auto &doublet : Doublets){
    if(pre_cuts.PtLowerCut(Id::top) > 0 && doublet.Jet().pt() < pre_cuts.PtLowerCut(Id::top)) continue;
    if(pre_cuts.PtUpperCut(Id::top) > 0 && doublet.Jet().pt() > pre_cuts.PtUpperCut(Id::top)) continue;
    clean_doublets.emplace_back(doublet);
    }
    return clean_doublets;
}

std::vector<Doublet> TopLeptonicTagger::Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    Jets leptons = event.Leptons().leptons();
    Print(Severity::information, "Bdt");
    std::vector<Doublet> doublets;
    for (const auto & lepton : leptons) {
        if (lepton.pt()<50) continue;
        for (const auto & jet : jets) {
            Doublet doublet(jet, lepton);
            doublet.SetBdt(Bdt(doublet,reader));
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
   // if(final_doublets.size()>0)Print(kError, "doublet_pt", final_doublets.at(0).Jet().pt());
    return ReduceResult(final_doublets);
}

}
