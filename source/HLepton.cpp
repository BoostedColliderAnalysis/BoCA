# include "HLepton.hh"

hanalysis::HLepton::HLepton()
{

    Print(HNotification,"Constructor");

//     Debug = 5;

}

hanalysis::HLepton::~HLepton()
{

    Print(HNotification,"Destructor");

}

void hanalysis::HLepton::NewEvent(const HClonesArray * const NewClonesArrays)
{

    Print(HInformation,"New Event");

//     ClonesArrays = NewClonesArray;
    hanalysis::HFourVector::NewEvent(NewClonesArrays);

    GotElectrons = 0;

    GotMuons = 0;

    ElectronLorentzVectors.clear();

    AntiElectronLorentzVectors.clear();

    MuonLorentzVectors.clear();

    AntiMuonLorentzVectors.clear();

    TauLorentzVectors.clear();

    AntiTauLorentzVectors.clear();

    LeptonLorentzVectors.clear();

    AntiLeptonLorentzVectors.clear();

    ElectronJets.clear();

    AntiElectronJets.clear();

    MuonJets.clear();

    AntiMuonJets.clear();

    LeptonJets.clear();

    AntiLeptonJets.clear();

}

HVectors hanalysis::HLepton::GetLeptonVectors()
{

  Print(HInformation,"Get Leptons");

  if(!GotElectrons) GotElectrons = GetElectrons(Plain);
  if(!GotMuons) GotMuons = GetMuons(Plain);

    LeptonLorentzVectors = ElectronLorentzVectors;
    LeptonLorentzVectors.insert(LeptonLorentzVectors.end(), MuonLorentzVectors.begin(), MuonLorentzVectors.end());
//     LeptonVector.insert(LeptonVector.end(), TauVector.begin(), TauVector.end());
    std::sort(LeptonLorentzVectors.begin(), LeptonLorentzVectors.end(), SortByPt());

    Print(HDebug,"Number of Leptons",LeptonLorentzVectors.size());

    AntiLeptonLorentzVectors = AntiElectronLorentzVectors;
    AntiLeptonLorentzVectors.insert(AntiLeptonLorentzVectors.end(), AntiMuonLorentzVectors.begin(), AntiMuonLorentzVectors.end());
//     AntiLeptonVector.insert(AntiLeptonVector.end(), AntiTauVector.begin(), AntiTauVector.end());
    std::sort(AntiLeptonLorentzVectors.begin(), AntiLeptonLorentzVectors.end(), SortByPt());


    Print(HDebug,"Number of Anti Leptons",AntiLeptonLorentzVectors.size());

    HVectors CompleteVector = LeptonLorentzVectors;
    CompleteVector.insert(CompleteVector.end(), AntiLeptonLorentzVectors.begin(), AntiLeptonLorentzVectors.end());
    std::sort(CompleteVector.begin(), CompleteVector.end(), SortByPt());

    return CompleteVector;

}

HJets hanalysis::HLepton::GetLeptonJets()
{
    
    Print(HInformation,"Get Lepton Jets");
    
    return GetLeptonJets(Plain);
    
}

HJets hanalysis::HLepton::GetLeptonJets(HJetDetails JetDetails)
{

    Print(HInformation,"Get Lepton Jets");

    if(!GotElectrons) GotElectrons = (JetDetails);
    if(!GotMuons) GotMuons = GetMuons(JetDetails);

    LeptonJets = ElectronJets;
    LeptonJets.insert(LeptonJets.end(), MuonJets.begin(), MuonJets.end());
//     LeptonJetVector.insert(LeptonJetVector.end(), TauJetVector.begin(), TauJetVector.end());
//     sort(LeptonJetVector.begin(), LeptonJetVector.end(), SortJetByPt());

    Print(HDebug,"Number of Lepton Jets",LeptonJets.size());

    AntiLeptonJets = AntiElectronJets;
    AntiLeptonJets.insert(AntiLeptonJets.end(), AntiMuonJets.begin(), AntiMuonJets.end());
//     AntiLeptonJetVector.insert(AntiLeptonJetVector.end(), AntiTauJetVector.begin(), AntiTauJetVector.end());
//     sort(AntiLeptonJetVector.begin(), AntiLeptonJetVector.end(), SortJetByPt());
    Print(HDebug,"Number of Anti Lepton Jets",AntiLeptonJets.size());

    HJets AllJets = LeptonJets;
    AllJets.insert(AllJets.end(), AntiLeptonJets.begin(), AntiLeptonJets.end());
//     sort(CompleteJetVector.begin(), CompleteJetVector.end(), SortJetByPt());

    return AllJets;

}


// void  leptons::FindLargestLorentzVector()
// {
//
//     TLorentzVector Lepton;
//
//     float ElectronPT = Electron.Pt();
//     float MuonPT = Muon.Pt();
//     float TauPT = Tau.Pt();
//
//     if (ElectronPT > MuonPT && ElectronPT > TauPT) {
//         Lepton =  Electron;
//     } else if (MuonPT > ElectronPT && MuonPT > TauPT) {
//         LeptonLorentzVector = MuonLorentzVector;
//     } else if (TauPT > ElectronPT && TauPT > MuonPT) {
//         LeptonLorentzVector = TauLorentzVector;
//     }
//
//     return (LeptonLorentzVector);
//
// }                                                           // FindLargestLorentzVector

/*

void leptons::LeptonsAndMissingEt()
{

    const float LeptonLowerPtCut = 25.0;
    const float LeptonUpperRapCut = 2.5;

    int MuonCounter = 0, ElectronCounter = 0;                       //initial the varibles Important

    float MissingPx, MissingPy, MissingEt, MissingPhi;
    MissingPx = 0;
    MissingPy = 0;
    MissingEt = 0;
    MissingPhi = 0;

    int ElectronSum = ClonesArrayClass->ElectronClonesArray->GetEntriesFast();

    for (int ElectronNumber = 0; ElectronNumber < ElectronSum; ElectronNumber++) {

        Electron *electron = (Electron *) ClonesArrayClass->ElectronClonesArray->At(ElectronNumber);
        float ElectronPt = electron->PT;
        float ElectronRap = electron->Rap;
        float ElectronPhi = electron->Phi;

        if (ElectronPt > LeptonLowerPtCut && Abs(ElectronRap) < LeptonUpperRapCut) {

            ElectronCounter++;
            fastjet::PseudoJet lepton = fastjet::PseudoJet(ElectronPt * Cos(ElectronPhi), ElectronPt * Sin(ElectronPhi), ElectronPt * SinH(ElectronRap), ElectronPt * CosH(ElectronRap));

        }

    }

    int MuonSum = ClonesArrayClass->MuonClonesArray->GetEntriesFast();

    for (int MuonNumber = 0; MuonNumber < MuonSum; MuonNumber++) {

        Muon *muon = (Muon *) ClonesArrayClass->MuonClonesArray->At(MuonNumber);
        float MuonPt = muon->PT;
        float MuonRap = muon->Rap;
        float MuonPhi = muon->Phi;

        if (MuonPt > LeptonLowerPtCut && Abs(MuonRap) < LeptonUpperRapCut) {

            MuonCounter++;
            fastjet::PseudoJet lepton = fastjet::PseudoJet(MuonPt * Cos(MuonPhi), MuonPt * Sin(MuonPhi), MuonPt * SinH(MuonRap), MuonPt * CosH(MuonRap));

        }

    }

    int MissingEtSum = ClonesArrayClass->MissingEtClonesArray->GetEntriesFast();

    if (MissingEtSum > 0) {

        MissingET *met = (MissingET *) ClonesArrayClass->MissingEtClonesArray->At(0);

        MissingEt = met->MET;
        MissingPhi = met->Phi;

        MissingPx = MissingEt * cos(MissingPhi);
        MissingPy = MissingEt * sin(MissingPhi);

    }


}*/
