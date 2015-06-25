# include "TopLeptonicTagger.hh"

namespace analysis {

TopLeptonicTagger::TopLeptonicTagger()
{
    //     debug_level_ = kDebug;
    Print(kNotification, "Constructor");
    set_tagger_name("TopLeptonic");
    bottom_reader_.SetTagger(bottom_tagger_);
    top_mass_window = std::abs(Mass(TopId) - Mass(HiggsId))/2;
    DefineVariables();
}

int TopLeptonicTagger::Train(Event &event, PreCuts &pre_cuts, const Object::Tag tag)
{
    Print(kInformation, "Train");
    std::size_t number_of_tops = 2;
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    Print(kInformation, "Jet Number", jets.size());

    Jets leptons = event.Leptons().leptons();
    Print(kInformation, "Lepton Number", leptons.size());
    std::vector<Doublet> doublets;
    if(leptons.size()==0&&tag==kBackground){
      for(const auto & jet :jets){
	const float Lepton_fake_pt=1;
      fastjet::PseudoJet lepton_fake=fastjet::PseudoJet(jet.px(), jet.py(), jet.pz(), jet.e()) / jet.pt()*Lepton_fake_pt;
      Doublet doublet(jet, lepton_fake);
      doublets.emplace_back(doublet);
      }
    }
    for (const auto & lepton : leptons)
        for (const auto & jet : jets) {
            Doublet doublet(jet, lepton);
 //           if (tag == kSignal && std::abs(doublet.Jet().m() - Mass(TopId)) > top_mass_window) continue;
            if (tag == kSignal && doublet.Jet().m()<20) continue;
 //	    if (tag == kSignal && lepton.pt()<50) continue;
	    if (tag == kSignal && lepton.delta_R(jet)>1.0) continue;
            doublets.emplace_back(doublet);
        }
    Print(kInformation, "Number JetPairs", doublets.size());
    std::vector<Doublet> final_doublets=Clean_Doublets(doublets, pre_cuts);

    
    Jets particles = event.Partons().GenParticles();
    Jets tops = copy_if_abs_particle(particles, TopId);
    switch (tag) {
    case kSignal :
        final_doublets = BestMatch(final_doublets, tops);
        break;
    case kBackground  :
        final_doublets = RemoveBestMatch(final_doublets, tops);
        break;
    }
    
    
    return SaveEntries(final_doublets);
}

std::vector<Doublet> TopLeptonicTagger::Clean_Doublets(const std::vector< Doublet > &Doublets, PreCuts &pre_cuts)
{
    
    std::vector<Doublet> clean_doublets;
    for(const auto &doublet : Doublets){
    if(pre_cuts.PtLowerCut(TopId) > 0 && doublet.Jet().pt() < pre_cuts.PtLowerCut(TopId)) continue;
    if(pre_cuts.PtUpperCut(TopId) > 0 && doublet.Jet().pt() > pre_cuts.PtUpperCut(TopId)) continue;
    clean_doublets.emplace_back(doublet);
    }
    return clean_doublets;
}

std::vector<Doublet> TopLeptonicTagger::Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    Jets leptons = event.Leptons().leptons();
    //Print(kError, "lepton number", leptons.size());
    std::vector<Doublet> doublets;
    
    if(leptons.size()==0){ 
      for(const auto & jet :jets){
	const int Lepton_fake_pt=1;
      fastjet::PseudoJet lepton_fake=fastjet::PseudoJet(jet.px(), jet.py(), jet.pz(), jet.e())/jet.pt()*Lepton_fake_pt;
      Doublet doublet(jet, lepton_fake);
      doublet.SetBdt(Bdt(doublet,reader));
      doublets.emplace_back(doublet);
      }
    }
    for (const auto & lepton : leptons) {
        for (const auto & jet : jets) {
            Doublet doublet(jet, lepton);
            doublet.SetBdt(Bdt(doublet,reader));
            doublets.emplace_back(doublet);
        }
    }
    std::vector<Doublet> final_doublets=Clean_Doublets(doublets, pre_cuts);
   // if(final_doublets.size()>0)Print(kError, "doublet_pt", final_doublets.at(0).Jet().pt());
    return ReduceResult(final_doublets);
}

}