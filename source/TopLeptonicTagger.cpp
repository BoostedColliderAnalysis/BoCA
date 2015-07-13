#include "TopLeptonicTagger.hh"
#include "Event.hh"
#include "WSemiTagger.hh"
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
    Info();
    bool do_fake_leptons = false;
    Jets jets = fastjet::sorted_by_pt(bottom_reader_.Multiplets(event));
    if (jets.empty()) return 0;
    Info(jets.size());

    Jets leptons = event.Leptons().leptons();
    Info(leptons.size());

    std::vector<Doublet> doublets;
    for (const auto & lepton : leptons) {
    for (const auto & jet : jets) {
        
            Doublet doublet(jet, lepton);
	    if(Problematic(doublet,pre_cuts,tag)) continue;
            doublets.emplace_back(doublet);
        }
   }
    
    for(const auto & jet :jets){
      if(doublets.size() >= 0) break;
      const float Lepton_fake_pt=1;    
      fastjet::PseudoJet lepton_fake=fastjet::PseudoJet(jet.px(), jet.py(), jet.pz(), jet.e()) / jet.pt()*Lepton_fake_pt;
      Doublet doublet(jet, lepton_fake);
      if(Problematic(doublet,pre_cuts,tag)) continue;
      doublets.emplace_back(doublet);
    }


    Info(doublets.size());
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
    return false;
}

Jets TopLeptonicTagger::Particles(const Event &event) const
{
    Jets particles = event.Partons().GenParticles();
    Jets leptons=fastjet::sorted_by_pt(event.Leptons().leptons());
    int lepton_charge;
    if(leptons.size()==0) lepton_charge=1;
    else
    {
      lepton_charge=leptons.at(0).user_info<JetInfo>().Charge(); 
      Info(lepton_charge);
    }    
    return CopyIfParticle(particles, to_int(Id::top)*lepton_charge);
//     return CopyIfAbsParticle(particles, Id::top);
    
    int w_semi_id = WSemiTagger().WSemiId(event);
    int top_leptonic_id = sgn(w_semi_id) * to_int(Id::top);
    return CopyIfParticle(particles, top_leptonic_id);
}

bool TopLeptonicTagger::Problematic(const Doublet  &doublet, PreCuts &pre_cuts,const  Tag tag) const
{    
    if (Problematic(doublet, pre_cuts)) return true;
    switch (tag) {
    case Tag::signal :
//          if (doublet.Singlet1().Jet().pt() <= DetectorGeometry().LeptonMinPt()) return true;
            if (doublet.Jet().m()<0) return true;
 	    if (doublet.Singlet2().Jet().delta_R(doublet.Singlet1().Jet())>0.5) return true;
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
    
    for (const auto & lepton : leptons) {
    for (const auto & jet : jets) {
      if(jet.delta_R(lepton)>0.5) continue;
            Doublet doublet(jet, lepton);
	    if(Problematic(doublet,pre_cuts)) continue;
            doublet.SetBdt(Bdt(doublet, reader));
            doublets.emplace_back(doublet);
        }
    }
    
    for(const auto & jet :jets){
      if(doublets.size() > 0) break;
      const int Lepton_fake_pt=1;
      fastjet::PseudoJet lepton_fake=fastjet::PseudoJet(jet.px(), jet.py(), jet.pz(), jet.e())/jet.pt()*Lepton_fake_pt;
      Doublet doublet(jet, lepton_fake);
	    if(Problematic(doublet,pre_cuts)) continue;
      doublet.SetBdt(Bdt(doublet,reader));
      doublets.emplace_back(doublet);
    }
    
    return ReduceResult(doublets);

}

}
