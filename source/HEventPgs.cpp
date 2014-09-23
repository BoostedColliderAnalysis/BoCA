# include "HEventPgs.hh"


HEventPgs::HEventPgs()
{

    Print(0, "Constructor");

    Lepton = new HLeptonPgs();
    Jets = new HJetPgs();

    HasLeptons = 0;
    HasJets = 0;

}

HEventPgs::~HEventPgs()
{

    Print(0, "Destructor");

    delete Lepton;
    delete Jets;

}

void HEventPgs::NewEvent()
{

    Print(1, "New Event");

    Lepton->NewEvent(ClonesArrays);
    Jets->NewEvent(ClonesArrays);
    
    HasLeptons = 0;
    HasJets = 0;

}


vector<TLorentzVector> HEventPgs::GetLeptons()
{
    
    Print(1, "Get Leptons");
    
    vector<TLorentzVector> LeptonVector = Lepton->GetLeptonVector();
    
    
    return LeptonVector;
    
}

void HEventPgs::GetJets()
{
    Print(1, "Get Jets");
    
    if (!HasJets) HasJets = Jets->GetJets();
    
}






