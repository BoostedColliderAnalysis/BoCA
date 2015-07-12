# include "TopLeptonicTagger.hh"

namespace analysis
{

TopLeptonicTagger::TopLeptonicTagger()
{
//         debug_level_ = Severity::debug;
    Print(Severity::notification, "Constructor");
    set_tagger_name("TopLeptonic");
    bottom_reader_.SetTagger(bottom_tagger_);
    top_mass_window = 80;
    DefineVariables();
}

int TopLeptonicTagger::Train(Event &event, PreCuts &pre_cuts, const Tag tag)
{
    Print(Severity::information, "Train");
    Jets jets = fastjet::sorted_by_pt(bottom_reader_.Multiplets<BottomTagger>(event));
    if (jets.empty()) return 0;
    Print(Severity::information, "Jet Number", jets.size());

    Jets leptons = event.Leptons().leptons();
    
    std::vector<Doublet> doublets;
    for (const auto & lepton : leptons) {
 //     if(lepton.pt()<50)continue;
    for (const auto & jet : jets) {
        
            Doublet doublet(jet, lepton);
            if (tag == Tag::signal && doublet.Jet().m()<0) continue;
 	    if (tag == Tag::signal && lepton.delta_R(jet)>0.5) continue;
	    if (tag == Tag::signal && doublet.Jet().m() > pre_cuts.MassUpperCut(Id::top)) continue;
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
    std::vector<Doublet> final_doublets=Clean_Doublets(doublets, pre_cuts);
    Jets tops = Particles(event);
    return SaveEntries(BestMatches(final_doublets, tops, tag));
}

Jets TopLeptonicTagger::Particles(Event &event) const
{
    Jets particles = event.Partons().GenParticles();
    Jets leptons=fastjet::sorted_by_pt(event.Leptons().leptons());
    int lepton_charge;
    if(leptons.size()==0) lepton_charge=1;
    else
    {
      lepton_charge=leptons.at(0).user_info<JetInfo>().Charge(); 
      Print(Severity::information, "lepton_charge", lepton_charge);
    }    
//     return copy_if_particle(particles, static_cast<int>(Id::top)*lepton_charge);
    return copy_if_abs_particle(particles, Id::top);
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

std::vector<Doublet> TopLeptonicTagger::Multiplets(analysis::Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Print(Severity::information, "Bdt");
    std::vector<Doublet> doublets;
    Jets jets = fastjet::sorted_by_pt(bottom_reader_.Multiplets<BottomTagger>(event));
    
    if (jets.empty()) return doublets;
    
    Jets leptons = event.Leptons().leptons();
    
    for (const auto & lepton : leptons) {
//          if(lepton.pt()<50)continue;
    for (const auto & jet : jets) {
      if(jet.delta_R(lepton)>0.5) continue;
            Doublet doublet(jet, lepton);
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
