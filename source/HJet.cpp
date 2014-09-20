# include "HJet.hh"

HJet::HJet()
{

    Print(0, "Constructor");

//     Debug = 4;

}

HJet::~HJet()
{

    Print(0, "Destructor");

}

void HJet::NewEvent(HClonesArrayBase *ImportClonesArrays)
{

    Print(1, "New Event");
    
    ClonesArrays = ImportClonesArrays;

    JetLorentzVectorVector.clear();

    TauLorentzVectorVector.clear();

    AntiTauLorentzVectorVector.clear();

    EFlowJetVector.clear();

    BottomJetVector.clear();

    CharmJetVector.clear();

    GenJetVector.clear();

    BottomLorentzVectorVector.clear();

    JetVector.clear();

}


void HJet::AnalyseJet()
{

    Print(1, "Analyse Jet");

    TClonesArray *JetClonesArray = ClonesArrays->JetClonesArray;
    int JetSum = JetClonesArray->GetEntriesFast();
    Print(2, "Number of Jets", JetSum);

    /// Loop over all jets
    for (int JetNumber = 0; JetNumber < JetSum; ++JetNumber) {

        Print(3, "Jet Number", JetNumber);
        Jet *JetClone = (Jet *)JetClonesArray->At(JetNumber);

        JetVector.push_back(GetPseudoJetPt(JetClone));

        if (JetClone->TauTag == 1) {

            Print(3, "Has Tau Tag");

            TauTagCalculations(JetClone);

        } else if (JetClone->BTag > 0) {

            Print(3, "Has B Tag");

            BottomLorentzVectorVector.push_back(GetLorentzVectorM(JetClone));
            BottomJetVector.push_back(GetPseudoJetPt(JetClone));


        } else {

            JetLorentzVectorVector.push_back(GetLorentzVectorM(JetClone));

        }

    }

    Print(2, "Untagged jets", JetLorentzVectorVector.size());

}


void HJet::TauTagCalculations(Jet *JetClone)
{

    Print(1, "TauTagCalculations");
    int JetCharge = JetClone->Charge;

    if (JetCharge == - 1) {

        TauLorentzVectorVector.push_back(GetLorentzVectorM(JetClone));
        Print(2, "Tau Jet");

    } else if (JetCharge == 1) {

        AntiTauLorentzVectorVector.push_back(GetLorentzVectorM(JetClone));
        Print(2, "Anti Tau Jet");

    } else cout << "Jet Charge: " << JetCharge <<  endl;

}

bool HJet::AnalyseEFlow()
{
    Print(1, "AnalyseEFlow");

    // Tracks
    int EFLowTrackSum = ClonesArrays->EFlowTrackClonesArray->GetEntriesFast();
    Print(2, "Number of E Flow Tracks", EFLowTrackSum);
    
    int ElectronSum = ClonesArrays->ElectronClonesArray->GetEntriesFast();
    if (ElectronSum > 0) Print(3, "Number of Electons", ElectronSum);
    
    int MuonSum = ClonesArrays->MuonClonesArray->GetEntriesFast();
    if (MuonSum > 0) Print(3, "Number of Muons", MuonSum);
    
    for (int EFlowTrackNumber = 0; EFlowTrackNumber < EFLowTrackSum ; ++EFlowTrackNumber) {

        Track *EFlowTrackClone = (Track *) ClonesArrays->EFlowTrackClonesArray->At(EFlowTrackNumber);
        PseudoJet JetCandidate = GetPseudoJetPt(EFlowTrackClone);

        // Make sure this is not an electron
        bool Isolated = true;
        for (int ElectronNumber = 0; ElectronNumber < ElectronSum; ++ElectronNumber) {

            Electron *ElectronClone = (Electron *) ClonesArrays->ElectronClonesArray->At(ElectronNumber);
            Isolated = CheckIsolation(EFlowTrackClone, ElectronClone);

        }

        // make sure this is not a muon
        for (int MuonNumber = 0; MuonNumber < MuonSum; ++MuonNumber) {
            
            Muon *MuonClone = (Muon *) ClonesArrays->MuonClonesArray->At(MuonNumber);
            Isolated = CheckIsolation(EFlowTrackClone, MuonClone);

        }

        if (Isolated) EFlowJetVector.push_back(JetCandidate);

    }


    // Photons
    int EFLowPhotonSum = ClonesArrays->EFlowPhotonClonesArray->GetEntriesFast();
    Print(2, "Number of E Flow Photons", EFLowPhotonSum);
    for (int EFlowPhotonNumber = 0; EFlowPhotonNumber < EFLowPhotonSum ; ++EFlowPhotonNumber) {

        // Using Tower for ET
        Photon *EFlowPhotonClone = (Photon *) ClonesArrays->EFlowPhotonClonesArray->At(EFlowPhotonNumber);

        PseudoJet JetCandidate = GetPseudoJetE(EFlowPhotonClone);

        // Make sure this is not a photon
        bool Isolated = true;
        
        int PhotonSum = ClonesArrays->PhotonClonesArray->GetEntriesFast();
        if (PhotonSum > 0) Print(2, "Number of Photons", PhotonSum);
        for (int PhotonNumber = 0; PhotonNumber < PhotonSum; ++PhotonNumber) {

            Photon *PhotonClone = (Photon *) ClonesArrays->PhotonClonesArray->At(PhotonNumber);

            Isolated = CheckIsolation(EFlowPhotonClone, PhotonClone);

        }

        if (Isolated) EFlowJetVector.push_back(JetCandidate);

    }

    // Neutral Hadrons
    int HadronSum = ClonesArrays->EFlowNeutralHadronClonesArray->GetEntriesFast();
    Print(2, "Number of EF Neut Had", HadronSum);
    for (int HadronNumber = 0; HadronNumber < HadronSum; ++HadronNumber) {

        // Using Tower for ET
        Tower *HadronClone = (Tower *) ClonesArrays->EFlowNeutralHadronClonesArray->At(HadronNumber);

        EFlowJetVector.push_back(GetPseudoJetE(HadronClone));

    }

    // Muon
    if (ClonesArrays->EFlowMuonClonesArray) {
        
        int MuonSum = ClonesArrays->EFlowMuonClonesArray->GetEntriesFast();
        Print(2, "Number of EF Muon", MuonSum);
        
        for (int MuonNumber = 0; MuonNumber < MuonSum; ++MuonNumber) {

            Muon *MuonClone = (Muon *) ClonesArrays->EFlowMuonClonesArray->At(MuonNumber);

            EFlowJetVector.push_back(GetPseudoJetPt(MuonClone));

        }
        
    }

    Print(2, "Number of EFlow Jet", EFlowJetVector.size());
    
    return 1;

}


void HJet::GetGenJet()
{
    Print(1, "GetGenJet");

    int GenJetSum = ClonesArrays->GenJetClonesArray->GetEntriesFast();
    Print(2, "Number of GenJets", GenJetSum);
    for (int GenJetNumber = 0; GenJetNumber < GenJetSum; ++GenJetNumber) {

        Jet *GenJetClone = (Jet *) ClonesArrays->GenJetClonesArray->At(GenJetNumber);

        GenJetVector.push_back(GetPseudoJetPt(GenJetClone));

    }

}
