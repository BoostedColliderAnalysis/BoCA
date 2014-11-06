# include "HLepton.hh"

hanalysis::HLepton::HLepton()
{

    Print(1,"Constructor");

//     Debug = 5;

}

hanalysis::HLepton::~HLepton()
{

    Print(1,"Destructor");

}

void hanalysis::HLepton::NewEvent(const HClonesArray * const NewClonesArray)
{

    Print(2,"New Event");

    ClonesArray = NewClonesArray;

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

vector<TLorentzVector> hanalysis::HLepton::GetLeptonLorentzVectors()
{

  Print(2,"Get Leptons");

  if(!GotElectrons) GotElectrons = GetElectrons();
  if(!GotMuons) GotMuons = GetMuons();

    LeptonLorentzVectors = ElectronLorentzVectors;
    LeptonLorentzVectors.insert(LeptonLorentzVectors.end(), MuonLorentzVectors.begin(), MuonLorentzVectors.end());
//     LeptonVector.insert(LeptonVector.end(), TauVector.begin(), TauVector.end());
    sort(LeptonLorentzVectors.begin(), LeptonLorentzVectors.end(), SortByPt());

    Print(3,"Number of Leptons",LeptonLorentzVectors.size());

    AntiLeptonLorentzVectors = AntiElectronLorentzVectors;
    AntiLeptonLorentzVectors.insert(AntiLeptonLorentzVectors.end(), AntiMuonLorentzVectors.begin(), AntiMuonLorentzVectors.end());
//     AntiLeptonVector.insert(AntiLeptonVector.end(), AntiTauVector.begin(), AntiTauVector.end());
    sort(AntiLeptonLorentzVectors.begin(), AntiLeptonLorentzVectors.end(), SortByPt());


    Print(3,"Number of Anti Leptons",AntiLeptonLorentzVectors.size());

    vector<TLorentzVector> CompleteVector = LeptonLorentzVectors;
    CompleteVector.insert(CompleteVector.end(), AntiLeptonLorentzVectors.begin(), AntiLeptonLorentzVectors.end());
    sort(CompleteVector.begin(), CompleteVector.end(), SortByPt());

    return CompleteVector;

}



vector<PseudoJet> hanalysis::HLepton::GetLeptonJets()
{

    Print(2,"Get Lepton Jets");

    if(!GotElectrons) GotElectrons = GetElectrons();
    if(!GotMuons) GotMuons = GetMuons();

    LeptonJets = ElectronJets;
    LeptonJets.insert(LeptonJets.end(), MuonJets.begin(), MuonJets.end());
//     LeptonJetVector.insert(LeptonJetVector.end(), TauJetVector.begin(), TauJetVector.end());
//     sort(LeptonJetVector.begin(), LeptonJetVector.end(), SortJetByPt());

    Print(3,"Number of Lepton Jets",LeptonJets.size());

    AntiLeptonJets = AntiElectronJets;
    AntiLeptonJets.insert(AntiLeptonJets.end(), AntiMuonJets.begin(), AntiMuonJets.end());
//     AntiLeptonJetVector.insert(AntiLeptonJetVector.end(), AntiTauJetVector.begin(), AntiTauJetVector.end());
//     sort(AntiLeptonJetVector.begin(), AntiLeptonJetVector.end(), SortJetByPt());
    Print(3,"Number of Anti Lepton Jets",AntiLeptonJets.size());

    vector<PseudoJet> CompleteJetVector = LeptonJets;
    CompleteJetVector.insert(CompleteJetVector.end(), AntiLeptonJets.begin(), AntiLeptonJets.end());
//     sort(CompleteJetVector.begin(), CompleteJetVector.end(), SortJetByPt());

    return CompleteJetVector;

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
    const float LeptonUpperEtaCut = 2.5;

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
        float ElectronEta = electron->Eta;
        float ElectronPhi = electron->Phi;

        if (ElectronPt > LeptonLowerPtCut && Abs(ElectronEta) < LeptonUpperEtaCut) {

            ElectronCounter++;
            PseudoJet lepton = PseudoJet(ElectronPt * Cos(ElectronPhi), ElectronPt * Sin(ElectronPhi), ElectronPt * SinH(ElectronEta), ElectronPt * CosH(ElectronEta));

        }

    }

    int MuonSum = ClonesArrayClass->MuonClonesArray->GetEntriesFast();

    for (int MuonNumber = 0; MuonNumber < MuonSum; MuonNumber++) {

        Muon *muon = (Muon *) ClonesArrayClass->MuonClonesArray->At(MuonNumber);
        float MuonPt = muon->PT;
        float MuonEta = muon->Eta;
        float MuonPhi = muon->Phi;

        if (MuonPt > LeptonLowerPtCut && Abs(MuonEta) < LeptonUpperEtaCut) {

            MuonCounter++;
            PseudoJet lepton = PseudoJet(MuonPt * Cos(MuonPhi), MuonPt * Sin(MuonPhi), MuonPt * SinH(MuonEta), MuonPt * CosH(MuonEta));

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
