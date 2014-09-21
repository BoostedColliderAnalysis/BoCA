# include "HEventPgs.hh"


HEventPgs::HEventPgs()
{

    Print(0, "Constructor");

    Lepton = new HLeptonPgs();

    Leptons = 0;

}

HEventPgs::~HEventPgs()
{

    Print(0, "Destructor");

    delete Lepton;

}

void HEventPgs::NewEvent()
{

    Print(1, "New Event");

    Lepton->NewEvent(ClonesArrays);

}


vector<TLorentzVector> HEventPgs::GetLeptons()
{
    
    Print(1, "Get Leptons");
    
    vector<TLorentzVector> v = Lepton->GetLeptonVector();
    
    
    return v;
    
}






