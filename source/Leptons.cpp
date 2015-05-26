# include "Leptons.hh"
# include "Predicate.hh"

analysis::Leptons::Leptons()
{
//   DebugLevel=kDebug;
    Print(kNotification,"Constructor");
}

analysis::Leptons::~Leptons()
{
    Print(kNotification,"Destructor");
}

void analysis::Leptons::NewEvent(const analysis::ClonesArrays &clones_arrays)
{
    Print(kInformation,"New event");
    analysis::FourVector::NewEvent(clones_arrays);
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

Vectors analysis::Leptons::GetLeptonVectors()
{
    Print(kInformation,"Get Leptons");
    if(!GotElectrons) GotElectrons = GetElectrons(kPlain);
    if(!GotMuons) GotMuons = GetMuons(kPlain);
    LeptonLorentzVectors = ElectronLorentzVectors;
    LeptonLorentzVectors.insert(LeptonLorentzVectors.end(), MuonLorentzVectors.begin(), MuonLorentzVectors.end());
//     LeptonVector.insert(LeptonVector.end(), TauVector.begin(), TauVector.end());
    std::sort(LeptonLorentzVectors.begin(), LeptonLorentzVectors.end(), SortByPt());
    Print(kDebug,"Number of Leptons",LeptonLorentzVectors.size());
    AntiLeptonLorentzVectors = AntiElectronLorentzVectors;
    AntiLeptonLorentzVectors.insert(AntiLeptonLorentzVectors.end(), AntiMuonLorentzVectors.begin(), AntiMuonLorentzVectors.end());
//     AntiLeptonVector.insert(AntiLeptonVector.end(), AntiTauVector.begin(), AntiTauVector.end());
    std::sort(AntiLeptonLorentzVectors.begin(), AntiLeptonLorentzVectors.end(), SortByPt());
    Print(kDebug,"Number of Anti Leptons",AntiLeptonLorentzVectors.size());
    Vectors CompleteVector = LeptonLorentzVectors;
    CompleteVector.insert(CompleteVector.end(), AntiLeptonLorentzVectors.begin(), AntiLeptonLorentzVectors.end());
    std::sort(CompleteVector.begin(), CompleteVector.end(), SortByPt());
    return CompleteVector;
}

Jets analysis::Leptons::GetLeptonJets()
{
    Print(kInformation,"Get Lepton Jets");
    return GetLeptonJets(kPlain);
}

Jets analysis::Leptons::GetLeptonJets(analysis::FourVector::JetDetail jet_detail)
{
    Print(kInformation,"Get Lepton Jets");
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
//     if(!GotElectrons)
    GotElectrons = GetElectrons(jet_detail);
//     if(!GotMuons)
    GotMuons = GetMuons(jet_detail);
    LeptonJets = ElectronJets;
    LeptonJets.insert(LeptonJets.end(), MuonJets.begin(), MuonJets.end());
//     LeptonJetVector.insert(LeptonJetVector.end(), TauJetVector.begin(), TauJetVector.end());
//     sort(LeptonJetVector.begin(), LeptonJetVector.end(), SortJetByPt());
    Print(kDebug,"Number of Lepton Jets",LeptonJets.size());
    AntiLeptonJets = AntiElectronJets;
    AntiLeptonJets.insert(AntiLeptonJets.end(), AntiMuonJets.begin(), AntiMuonJets.end());
//     AntiLeptonJetVector.insert(AntiLeptonJetVector.end(), AntiTauJetVector.begin(), AntiTauJetVector.end());
//     sort(AntiLeptonJetVector.begin(), AntiLeptonJetVector.end(), SortJetByPt());
    Print(kDebug,"Number of Anti Lepton Jets",AntiLeptonJets.size());
    Jets AllJets = LeptonJets;
    AllJets.insert(AllJets.end(), AntiLeptonJets.begin(), AntiLeptonJets.end());
    //     sort(CompleteJetVector.begin(), CompleteJetVector.end(), SortJetByPt());
    PrintTruthLevel(kDebug);
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
