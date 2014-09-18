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

void HJet::NewEvent()
{

    Print(1, "New Event");

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


void HJet::AnalyseJet(HClonesArrayBase *ImportClonesArrays)
{

    Print(1, "Analyse Jet");

    ClonesArrays = ImportClonesArrays;
    TClonesArray *JetClonesArray = ClonesArrays->JetClonesArray;
    int JetSum = JetClonesArray->GetEntriesFast();
    Print(2, "Number of Jets", JetSum);

    /// Loop over all jets
    for (int JetNumber = 0; JetNumber < JetSum; JetNumber++) {

        Print(3, "Jet Number", JetNumber);
        Jet *JetClone = (Jet *)JetClonesArray->At(JetNumber);

        PseudoJet Jet = FillPtJet(JetClone->PT, JetClone->Eta, JetClone->Phi);
        JetVector.push_back(Jet);


        if (JetClone->TauTag == 1) {

            Print(3, "Has Tau Tag");

            TauTagCalculations(JetClone);

        } else if (JetClone->BTag > 0) {

            Print(3, "Has B Tag");
            TLorentzVector BJetLorentzVector;
            BJetLorentzVector.SetPtEtaPhiM(JetClone->PT, JetClone->Eta, JetClone->Phi, JetClone->Mass);
            BottomLorentzVectorVector.push_back(BJetLorentzVector);

            PseudoJet BottomJet = FillPtJet(JetClone->PT, JetClone->Eta, JetClone->Phi);
            BottomJetVector.push_back(BottomJet);

            //             HBottom *Bottom = new HBottom(Debug);
//             Bottom->BTagCalculation(JetClone);
//             BottomVector.push_back(Bottom);

        } else {

            TLorentzVector JetLorentzVector;
            JetLorentzVector.SetPtEtaPhiM(JetClone->PT, JetClone->Eta, JetClone->Phi, JetClone->Mass);
            JetLorentzVectorVector.push_back(JetLorentzVector);

        }

    }

    Print(2, "Untagged jets", JetLorentzVectorVector.size());

}


void HJet::TauTagCalculations(Jet *JetClone)
{

    Print(1, "TauTagCalculations");
    int JetCharge = JetClone->Charge;

    if (JetCharge == - 1) {

        TLorentzVector TauLorentzVector;
        TauLorentzVector.SetPtEtaPhiM(JetClone->PT, JetClone->Eta, JetClone->Phi, JetClone->Mass);
        TauLorentzVectorVector.push_back(TauLorentzVector);
        Print(2, "Tau Jet");

    } else if (JetCharge == 1) {

        TLorentzVector AntiTauLorentzVector;
        AntiTauLorentzVector.SetPtEtaPhiM(JetClone->PT, JetClone->Eta, JetClone->Phi, JetClone->Mass);
        AntiTauLorentzVectorVector.push_back(AntiTauLorentzVector);
        Print(2, "Anti Tau Jet");

    } else cout << "Jet Charge: " << JetCharge <<  endl;

}

bool HJet::AnalyseEFlow(HClonesArrayBase *ImportClonesArrays)
{
    Print(1, "AnalyseEFlow");

    ClonesArrays = ImportClonesArrays;

    // Tracks
    int EFLowTrackSum = ClonesArrays->EFlowTrackClonesArray->GetEntriesFast();
    Print(2, "Number of E Flow Tracks", EFLowTrackSum);
    int ElectronSum = ClonesArrays->ElectronClonesArray->GetEntriesFast();
    if (ElectronSum > 0) Print(3, "Number of Electons", ElectronSum);
    int MuonSum = ClonesArrays->MuonClonesArray->GetEntriesFast();
    if (MuonSum > 0) Print(3, "Number of Muons", MuonSum);
    for (int EFlowTrackNumber = 0; EFlowTrackNumber < EFLowTrackSum ; ++EFlowTrackNumber) {

        Track *EFlowTrackClone = (Track *) ClonesArrays->EFlowTrackClonesArray->At(EFlowTrackNumber);
        float EFlowTrackPt = EFlowTrackClone->PT;
        float EFlowTrackEta = EFlowTrackClone->Eta;
        float EFlowTrackPhi = EFlowTrackClone->Phi;
        PseudoJet JetCandidate = FillPtJet(EFlowTrackPt, EFlowTrackEta, EFlowTrackPhi);

        // Make sure this is not an electron
        bool Isolated = true;
        for (int ElectronNumber = 0; ElectronNumber < ElectronSum; ++ElectronNumber) {

            Electron *ElectronClone = (Electron *) ClonesArrays->ElectronClonesArray->At(ElectronNumber);
            float ElectronPhi = ElectronClone->Phi;
            float ElectronEta = ElectronClone->Eta;

            Isolated = CheckIsolation(EFlowTrackEta, ElectronEta, EFlowTrackPhi, ElectronPhi);

        }

        // make sure this is not a muon
        for (int MuonNumber = 0; MuonNumber < MuonSum; ++MuonNumber) {
            Muon *MuonClone = (Muon *) ClonesArrays->MuonClonesArray->At(MuonNumber);
            float MuonPhi = MuonClone->Phi;
            float MuonEta = MuonClone->Eta;
            Isolated = CheckIsolation(EFlowTrackEta, MuonEta, EFlowTrackPhi, MuonPhi);

        }

        if (Isolated) EFlowJetVector.push_back(JetCandidate);

    }


    // Photons
    int EFLowPhotonSum = ClonesArrays->EFlowPhotonClonesArray->GetEntriesFast();
    Print(2, "Number of E Flow Photons", EFLowPhotonSum);
    for (int EFlowPhotonNumber = 0; EFlowPhotonNumber < EFLowPhotonSum ; ++EFlowPhotonNumber) {

        // Using Tower for ET
        Tower *EFlowPhotonClone = (Tower *) ClonesArrays->EFlowPhotonClonesArray->At(EFlowPhotonNumber);
        float EFlowPhotonE = EFlowPhotonClone->E;
        float EFlowPhotonEta = EFlowPhotonClone->Eta;
        float EFlowPhotonPhi = EFlowPhotonClone->Phi;
        PseudoJet JetCandidate = FillEJet(EFlowPhotonE, EFlowPhotonEta, EFlowPhotonPhi);

        // Make sure this is not a photon
        bool Isolated = true;
        int PhotonSum = ClonesArrays->PhotonClonesArray->GetEntriesFast();
        if (PhotonSum > 0) Print(2, "Number of Photons", PhotonSum);
        for (int PhotonNumber = 0; PhotonNumber < PhotonSum; ++PhotonNumber) {

            Photon *PhotonClone = (Photon *) ClonesArrays->PhotonClonesArray->At(PhotonNumber);
            float PhotonPhi = PhotonClone->Phi;
            float PhotonEta = PhotonClone->Eta;
            Isolated = CheckIsolation(EFlowPhotonEta, PhotonEta, EFlowPhotonPhi, PhotonPhi);

        }

        if (Isolated) EFlowJetVector.push_back(JetCandidate);

    }

    // Neutral Hadrons
    int HadronSum = ClonesArrays->EFlowNeutralHadronClonesArray->GetEntriesFast();
    Print(2, "Number of EF Neut Had", HadronSum);
    for (int HadronNumber = 0; HadronNumber < HadronSum; ++HadronNumber) {

        // Using Tower for ET
        Tower *HadronClone = (Tower *) ClonesArrays->EFlowNeutralHadronClonesArray->At(HadronNumber);
        float HadronE = HadronClone->E;
        float HadronEta = HadronClone->Eta;
        float HadronPhi = HadronClone->Phi;
        PseudoJet JetCandidate = FillEJet(HadronE, HadronEta, HadronPhi);
        EFlowJetVector.push_back(JetCandidate);

    }

    // Muon
    if (ClonesArrays->EFlowMuonClonesArray) {
        int MuonSum = ClonesArrays->EFlowMuonClonesArray->GetEntriesFast();
        Print(2, "Number of EF Muon", MuonSum);
        for (int MuonNumber = 0; MuonNumber < MuonSum; ++MuonNumber) {

            // Using Tower for ET
            Muon *MuonClone = (Muon *) ClonesArrays->EFlowMuonClonesArray->At(MuonNumber);
            float MuonPt = MuonClone->PT;
            float MuonEta = MuonClone->Eta;
            float MuonPhi = MuonClone->Phi;
            PseudoJet JetCandidate = FillPtJet(MuonPt, MuonEta, MuonPhi);
            EFlowJetVector.push_back(JetCandidate);

        }
    }

    Print(2, "Number of EFlow Jet", EFlowJetVector.size());
    
    return 1;

}

// bool HJet::CheckIsolation(float Eta1, float Eta2, float Phi1, float Phi2)
// {
//
//     const float DeltaRIsolationMax = 0.1;
//     bool Isolated = true;
//
//     if (fabs(Eta1 - Eta2) < DeltaRIsolationMax && fabs(Phi1 - Phi2) < DeltaRIsolationMax) {
//
//         Isolated = false;
//
//     }
//
//     return (Isolated);
//
// }

bool HJet::CheckIsolation(float Eta1, float Eta2, float Phi1, float Phi2)
{

    const float DeltaRIsolationMax = 0.01; // TODO decide on best value
    bool Isolated = true;

    if (GetDistance(Eta1, Phi1, Eta2, Phi2) < DeltaRIsolationMax) {

        Isolated = false;

    }


    Isolated = true; // FIXME this destroys the isolation check (right now on purpose to get harder top jets)

    return (Isolated);

}

PseudoJet HJet::FillPtJet(float Pt, float Eta, float Phi)
{

    PseudoJet JetCandidate;
    JetCandidate = PseudoJet(Pt * cos(Phi), Pt * sin(Phi), Pt * sinh(Eta), Pt * cosh(Eta));

    return (JetCandidate);

}

PseudoJet HJet::FillEJet(float E, float Eta, float Phi)
{

    float Pt = E / cosh(Eta);
    PseudoJet JetCandidate = FillPtJet(Pt, Eta, Phi);

    return (JetCandidate);

}


void HJet::GetGenJet(HClonesArrayBase *ImportClonesArrays)
{
    Print(1, "GetGenJet");

    ClonesArrays = ImportClonesArrays;
    int GenJetSum = ClonesArrays->GenJetClonesArray->GetEntriesFast();
    Print(2, "Number of GenJets", GenJetSum);
    for (int GenJetNumber = 0; GenJetNumber < GenJetSum; ++GenJetNumber) {

        Jet *GenJetClone = (Jet *) ClonesArrays->GenJetClonesArray->At(GenJetNumber);
        float GenJetPt = GenJetClone->PT;
        float GenJetEta = GenJetClone->Eta;
        float GenJetPhi = GenJetClone->Phi;
        PseudoJet JetCandidate = FillPtJet(GenJetPt, GenJetEta, GenJetPhi);

        GenJetVector.push_back(JetCandidate);

    }

}
