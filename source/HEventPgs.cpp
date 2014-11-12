# include "HEventPgs.hh"


hpgs::HEvent::HEvent()
{

    Print(1, "Constructor");

    Lepton = new HLepton();
    Jets = new HJet();

//     HasLeptons = 0;
//     HasJets = 0;

}

hpgs::HEvent::~HEvent()
{

    Print(1, "Destructor");

    delete Lepton;
    delete Jets;

}

void hpgs::HEvent::NewEvent(const hanalysis::HClonesArray*const ClonesArrays)
{

    Print(2, "New Event");

    Lepton->NewEvent(ClonesArrays);
    Jets->NewEvent(ClonesArrays);

//     HasLeptons = 0;
//     HasJets = 0;

}


// HVectors hpgs::HEvent::GetLeptons()
// {
//
//     Print(2, "Get Leptons");
//
//     HVectors LeptonVector = Lepton->GetLeptonLorentzVectors();
//
//
//     return LeptonVector;
//
// }

// void hpgs::HEvent::GetJets()
// {
//     Print(2, "Get Jets");
//
//     Jets->GetJets();
//
// }






