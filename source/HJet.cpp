# include "HJet.hh"

hanalysis::HJet::HJet()
{
// DebugLevel=HDebug;
    Print(HNotification, "Constructor");
}

hanalysis::HJet::~HJet()
{

    Print(HNotification, "Destructor");

}

void hanalysis::HJet::NewEvent(const HClonesArray *const NewClonesArrays)
{

    Print(HInformation, "New Event");

    hanalysis::HFourVector::NewEvent(NewClonesArrays);
    
    GotJets = 0;

    GotEFlow = 0;

    JetLorentzVectors.clear();

    TauLorentzVectors.clear();

    AntiTauLorentzVectors.clear();

    BottomLorentzVectors.clear();

    EFlowJets.clear();

    BottomJets.clear();

    CharmJets.clear();

    GenJets.clear();

    Jets.clear();

}

bool hanalysis::HJet::GetJets(const hanalysis::HJet::HJetDetails JetDetails)
{

    Print(HError, "Get Jets", "No Jets", JetDetails);

    return 0;

}

bool hanalysis::HJet::GetEFlow(const hanalysis::HJet::HJetDetails JetDetails)
{

    Print(HError, "Get EFlow", "No EFlow", JetDetails);

    return 0;

}

void hanalysis::HJet::GetGenJet()
{

    Print(HError, "Get Gen Jets", "No Gen Jets");

}

float hanalysis::HJet::GetScalarHt()
{

    Print(HError, "Get Scalar Ht", "No Scalar Ht");

    return 0;

}

fastjet::PseudoJet hanalysis::HJet::GetMissingEt()
{
  
  Print(HError, "Get Missing Et", "No Mising Et");
  
  fastjet::PseudoJet Jet;
  return Jet;
  
}
