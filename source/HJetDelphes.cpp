# include "HJetDelphes.hh"

HJetDelphes::HJetDelphes()
{

    Print(0, "Constructor");

//     Debug = 4;

}

HJetDelphes::~HJetDelphes()
{

    Print(0, "Destructor");

}

bool HJetDelphes::GetJets()
{

    Print(1, "Analyse Jet");

    TClonesArray *JetClonesArray = ClonesArrays->JetClonesArray;
    int JetSum = JetClonesArray->GetEntriesFast();
    Print(2, "Number of Jets", JetSum);

    /// Loop over all jets
    for (int JetNumber = 0; JetNumber < JetSum; ++JetNumber) {

        Print(3, "Jet Number", JetNumber);
        Jet *JetClone = (Jet *)JetClonesArray->At(JetNumber);

        JetVector.push_back(GetPseudoJet(JetClone));


        
       
        
        
        
        
//         Print(-1,"first",  JetClone->Particles.);



//         TRefArray RefArray = JetClone->Particles;
//         
// //         GenParticle *Clone = (GenParticle*) RefArray.GetObjectRef();
// 
//         int RefSum = RefArray.GetEntriesFast();
// 
// //         Print(-1, "Test",  RefArray.Class_Name());
// 
// //         Print(-1, "RefSum", RefSum);
// 
//         for (int RefNumber = 0; RefNumber < RefSum; ++RefNumber) {
// 
// // Print(-1,"Test",JetClone->Particles.At(RefNumber)->PID);
// 
// // Print(-1,"Test", RefArray.Class()->ClassName());
// // Print(-1,"Test", RefArray.At(RefNumber). );
// 
// //             GenParticle *Clone = (GenParticle*) RefArray.GetObjectRef();
//             GenParticle *Clone = (GenParticle*) RefArray.At(RefNumber);
// // Candidate *Clone = (Candidate*) RefArray.At(RefNumber);
// // Jet *Clone = (Jet*) RefArray.At(RefNumber);            
// // SortableObject *Clone = (SortableObject *) RefArray.At(RefNumber);
//             
// // TObject *Object = RefArray.At(RefNumber);
// // int PID = Clone->Status;
// // float Charge = Clone->Charge;
// 
// // Print(-1,"Test",Object->GetTitle());
// 
//             Print(-1, "Test", Clone->Status);
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
//         }


        if (JetClone->TauTag == 1) {

            Print(3, "Has Tau Tag");

            GetTau(JetClone);

        } else if (JetClone->BTag > 0) {

            Print(3, "Has B Tag");

            BottomLorentzVectorVector.push_back(GetLorentzVector(JetClone));
            BottomJetVector.push_back(GetPseudoJet(JetClone));


        } else {

            JetLorentzVectorVector.push_back(GetLorentzVector(JetClone));

        }

    }

    Print(2, "Untagged jets", JetLorentzVectorVector.size());

    return 1;

}


void HJetDelphes::GetTau(Jet *JetClone)
{

    Print(1, "TauTagCalculations");
    int JetCharge = JetClone->Charge;

    if (JetCharge == - 1) {

        TauLorentzVectorVector.push_back(GetLorentzVector(JetClone));
        Print(2, "Tau Jet");

    } else if (JetCharge == 1) {

        AntiTauLorentzVectorVector.push_back(GetLorentzVector(JetClone));
        Print(2, "Anti Tau Jet");

    } else cout << "Jet Charge: " << JetCharge <<  endl;

}

bool HJetDelphes::GetEFlow()
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
        PseudoJet JetCandidate = GetPseudoJet(EFlowTrackClone);

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

        PseudoJet JetCandidate = GetPseudoJet(EFlowPhotonClone);

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

        EFlowJetVector.push_back(GetPseudoJet(HadronClone));

    }

    // Muon
    if (ClonesArrays->EFlowMuonClonesArray) {

        int MuonSum = ClonesArrays->EFlowMuonClonesArray->GetEntriesFast();
        Print(2, "Number of EF Muon", MuonSum);

        for (int MuonNumber = 0; MuonNumber < MuonSum; ++MuonNumber) {

            Muon *MuonClone = (Muon *) ClonesArrays->EFlowMuonClonesArray->At(MuonNumber);

            EFlowJetVector.push_back(GetPseudoJet(MuonClone));

        }

    }

    Print(2, "Number of EFlow Jet", EFlowJetVector.size());

    return 1;

}


void HJetDelphes::GetGenJet()
{
    Print(1, "GetGenJet");

    int GenJetSum = ClonesArrays->GenJetClonesArray->GetEntriesFast();
    Print(2, "Number of GenJets", GenJetSum);
    for (int GenJetNumber = 0; GenJetNumber < GenJetSum; ++GenJetNumber) {

        Jet *GenJetClone = (Jet *) ClonesArrays->GenJetClonesArray->At(GenJetNumber);

        GenJetVector.push_back(GetPseudoJet(GenJetClone));

    }

}
