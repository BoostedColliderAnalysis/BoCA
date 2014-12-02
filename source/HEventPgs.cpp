# include "HEventPgs.hh"


hanalysis::hpgs::HEvent::HEvent()
{

    Print(HNotification, "Constructor");

    Lepton = new HLepton();
    Jets = new HJet();

//     HasLeptons = 0;
//     HasJets = 0;

}

hanalysis::hpgs::HEvent::~HEvent()
{

    Print(HNotification, "Destructor");

    delete Lepton;
    delete Jets;

}

void hanalysis::hpgs::HEvent::NewEvent(const hanalysis::HClonesArray*const ClonesArrays)
{

    Print(HInformation, "New Event");

    Lepton->NewEvent(ClonesArrays);
    Jets->NewEvent(ClonesArrays);

//     HasLeptons = 0;
//     HasJets = 0;

}


// HVectors hpgs::HEvent::GetLeptons()
// {
//
//     Print(HInformation, "Get Leptons");
//
//     HVectors LeptonVector = Lepton->GetLeptonLorentzVectors();
//
//
//     return LeptonVector;
//
// }

// void hpgs::HEvent::GetJets()
// {
//     Print(HInformation, "Get Jets");
//
//     Jets->GetJets();
//
// }






