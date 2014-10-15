# include "HEventPgs.hh"


HEventPgs::HEventPgs()
{

    Print(1, "Constructor");

    Lepton = new HLeptonPgs();
    Jets = new HJetPgs();

    HasLeptons = 0;
    HasJets = 0;

}

HEventPgs::~HEventPgs()
{

    Print(1, "Destructor");

    delete Lepton;
    delete Jets;

}

void HEventPgs::NewEvent(const HClonesArray * const ClonesArrays)
{

    Print(2, "New Event");

    Lepton->NewEvent(ClonesArrays);
    Jets->NewEvent(ClonesArrays);
    
    HasLeptons = 0;
    HasJets = 0;

}


vector<TLorentzVector> HEventPgs::GetLeptons()
{
    
    Print(2, "Get Leptons");
    
    vector<TLorentzVector> LeptonVector = Lepton->GetLeptonLorentzVectors();
    
    
    return LeptonVector;
    
}

void HEventPgs::GetJets()
{
    Print(2, "Get Jets");
    
    if (!HasJets) HasJets = Jets->GetJets(HJet::Plain);
    
}






