# include "HJetLeptonPair.hh"


hanalysis::HJetLeptonPair::HJetLeptonPair(const fastjet::PseudoJet &Jet, const fastjet::PseudoJet &Lepton){
        
    Print(HInformation, "Constructor");
    
    Jet1 = Jet;
    Jet2 = Lepton;
    
}

hanalysis::HJetLeptonPair::~HJetLeptonPair()
{

    Print(HInformation, "Destructor");

}
