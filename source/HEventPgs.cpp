# include "HEventPgs.hh"


hanalysis::hpgs::HEvent::HEvent()
{

    Print(1, "Constructor");

    Lepton = new HLepton();
    Jets = new HJet();

//     HasLeptons = 0;
//     HasJets = 0;

}

hanalysis::hpgs::HEvent::~HEvent()
{

    Print(1, "Destructor");

    delete Lepton;
    delete Jets;

}

void hanalysis::hpgs::HEvent::NewEvent(const hanalysis::HClonesArray*const ClonesArrays)
{

    Print(2, "New Event");

    Lepton->NewEvent(ClonesArrays);
    Jets->NewEvent(ClonesArrays);

//     HasLeptons = 0;
//     HasJets = 0;

}


// vector<TLorentzVector> hanalysis::hpgs::HEvent::GetLeptons()
// {
//
//     Print(2, "Get Leptons");
//
//     vector<TLorentzVector> LeptonVector = Lepton->GetLeptonLorentzVectors();
//
//
//     return LeptonVector;
//
// }

// void hanalysis::hpgs::HEvent::GetJets()
// {
//     Print(2, "Get Jets");
//
//     Jets->GetJets();
//
// }






