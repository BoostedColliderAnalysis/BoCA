# include "HEventPgs.hh"


HPgs::HEvent::HEvent()
{

    Print(1, "Constructor");

    Lepton = new HLepton();
    Jets = new HJet();

    HasLeptons = 0;
    HasJets = 0;

}

HPgs::HEvent::~HEvent()
{

    Print(1, "Destructor");

    delete Lepton;
    delete Jets;

}

void HPgs::HEvent::NewEvent(const Analysis::HClonesArray*const ClonesArrays)
{

    Print(2, "New Event");

    Lepton->NewEvent(ClonesArrays);
    Jets->NewEvent(ClonesArrays);

    HasLeptons = 0;
    HasJets = 0;

}


vector<TLorentzVector> HPgs::HEvent::GetLeptons()
{

    Print(2, "Get Leptons");

    vector<TLorentzVector> LeptonVector = Lepton->GetLeptonLorentzVectors();


    return LeptonVector;

}

void HPgs::HEvent::GetJets()
{
    Print(2, "Get Jets");

    if (!HasJets) HasJets = Jets->GetJets(Analysis::HJet::Plain);

}






