# include "HJetDelphes.hh"
#include <fastjet/ClusterSequence.hh>
// #include <fastjet/PseudoJet.hh>

// using fastjet::PseudoJet;

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

    Print(2, "Number of Jets", ClonesArrays->JetSum());
    Jet *JetClone;

    /// Loop over all jets
    for (int JetNumber = 0; JetNumber < ClonesArrays->JetSum(); ++JetNumber) {

        Print(3, "Jet Number", JetNumber);
        JetClone = (Jet *)ClonesArrays->JetClonesArray->At(JetNumber);

        JetVector.push_back(GetPseudoJet(JetClone->P4()));

        
        
        TObject *Object;
        int PID = 0;
        for (int ParticleNumber = 0; ParticleNumber < JetClone->Particles.GetEntriesFast(); ++ParticleNumber) {
            
            Object = JetClone->Particles.At(ParticleNumber);
            if (Object == 0) continue;

            if (Object->IsA() == GenParticle::Class()) {
                
                PID = ((GenParticle *) Object)->PID;
                if(abs(PID)==6 || abs(PID)==24)  Print(-1, "Particle", PID);

            } else if (Object->IsA() == Track::Class()) {
                
                PID = ((Track *) Object)->PID;
                if(abs(PID)==6 || abs(PID)==24)  Print(-1, "Track", PID);

            } else if (Object->IsA() == Candidate::Class()) {
                
                PID = ((Candidate *) Object)->PID;
                if(abs(PID)==6 || abs(PID)==24)  Print(-1, "Candidate", PID);
                
            } else {

                Print(-1, "it is", Object->IsA());

            }
        }

        Print(-1, " ");

vector<PseudoJet> ConstituentsVector;
        
        // Loop over all jet's constituents
        TString String;
        for (int ConstituentNumber = 0; ConstituentNumber < JetClone->Constituents.GetEntriesFast(); ++ConstituentNumber) {
            
            Object = JetClone->Constituents.At(ConstituentNumber);
            if (Object == 0) continue;

            if (Object->IsA() == GenParticle::Class()) {
                                
                ConstituentsVector.push_back(GetPseudoJet(((GenParticle *) Object)->P4()));
                
            } else if (Object->IsA() == Track::Class()) {
                
                ConstituentsVector.push_back(GetPseudoJet(((Track *) Object)->P4()));
                
            } else if (Object->IsA() == Tower::Class()) {
                
                ConstituentsVector.push_back(GetPseudoJet(((Tower *) Object)->P4()));
                
            } else if (Object->IsA() == Muon::Class()) {
                
                ConstituentsVector.push_back(GetPseudoJet(((Muon *) Object)->P4()));
                
            } else {
                
                String =Object->ClassName();
                Print(0, "something else", String);

            }
        }

        Print(-1, " ");

        
//         fastjet::JetDefinition jetDefinition(fastjet::cambridge_algorithm, 1.);
//         fastjet::ClusterSequence JetClusterSequence(ConstituentsVector, jetDefinition);
        
        
//         fastjet::JetDefinition
//         fastjet::ClusterSequence CS(ConstituentsVector,fastjet::cambridge_algorithm);
// CS->add_constituents(JetVector.back(),ConstituentsVector);


        if (JetClone->TauTag == 1) {

            Print(3, "Has Tau Tag");

            GetTau(JetClone);

        } else if (JetClone->BTag > 0) {

            Print(3, "Has B Tag");

            BottomLorentzVectorVector.push_back(JetClone->P4());
            BottomJetVector.push_back(GetPseudoJet(JetClone->P4()));


        } else {

            JetLorentzVectorVector.push_back(JetClone->P4());

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

        TauLorentzVectorVector.push_back(JetClone->P4());
        Print(2, "Tau Jet");

    } else if (JetCharge == 1) {

        AntiTauLorentzVectorVector.push_back(JetClone->P4());
        Print(2, "Anti Tau Jet");

    } else cout << "Jet Charge: " << JetCharge <<  endl;

}

bool HJetDelphes::GetEFlow()
{
    Print(1, "AnalyseEFlow");

    // Tracks

    Track *EFlowTrackClone;
    Electron *ElectronClone;
    Muon *MuonClone;
    PseudoJet JetCandidate;
    bool Isolated;

    if (ClonesArrays->ElectronSum() > 0) Print(3, "Number of Electons", ClonesArrays->ElectronSum());
    if (ClonesArrays->MuonSum() > 0) Print(3, "Number of Muons", ClonesArrays->MuonSum());
    if (ClonesArrays->EFlowTrackSum() > 0) Print(2, "Number of E Flow Tracks", ClonesArrays->EFlowTrackSum());
    for (int EFlowTrackNumber = 0; EFlowTrackNumber < ClonesArrays->EFlowTrackSum() ; ++EFlowTrackNumber) {

        EFlowTrackClone = (Track *) ClonesArrays->EFlowTrackClonesArray->At(EFlowTrackNumber);
        JetCandidate = GetPseudoJet(EFlowTrackClone->P4());

        // Make sure this is not an electron
        Isolated = true;
        for (int ElectronNumber = 0; ElectronNumber < ClonesArrays->ElectronSum(); ++ElectronNumber) {

            ElectronClone = (Electron *) ClonesArrays->ElectronClonesArray->At(ElectronNumber);
            Isolated = CheckIsolation(EFlowTrackClone, ElectronClone);

        }

        // make sure this is not a muon
        for (int MuonNumber = 0; MuonNumber < ClonesArrays->MuonSum(); ++MuonNumber) {

            MuonClone = (Muon *) ClonesArrays->MuonClonesArray->At(MuonNumber);
            Isolated = CheckIsolation(EFlowTrackClone, MuonClone);

        }

        if (Isolated) EFlowJetVector.push_back(JetCandidate);

    }


    // Photons
    Photon *EFlowPhotonClone, *PhotonClone;

    if (ClonesArrays->EFlowPhotonSum() > 0) Print(2, "Number of E Flow Photons", ClonesArrays->EFlowPhotonSum());
    if (ClonesArrays->PhotonSum() > 0) Print(2, "Number of Photons", ClonesArrays->PhotonSum());
    for (int EFlowPhotonNumber = 0; EFlowPhotonNumber < ClonesArrays->EFlowPhotonSum() ; ++EFlowPhotonNumber) {

        EFlowPhotonClone = (Photon *) ClonesArrays->EFlowPhotonClonesArray->At(EFlowPhotonNumber);
        JetCandidate = GetPseudoJet(EFlowPhotonClone->P4());

        // Make sure this is not a photon
        Isolated = true;

        for (int PhotonNumber = 0; PhotonNumber < ClonesArrays->PhotonSum(); ++PhotonNumber) {

            PhotonClone = (Photon *) ClonesArrays->PhotonClonesArray->At(PhotonNumber);

            Isolated = CheckIsolation(EFlowPhotonClone, PhotonClone);

        }

        if (Isolated) EFlowJetVector.push_back(JetCandidate);

    }

    // Neutral Hadrons
    // Using Tower for ET
    Tower *HadronClone;

    if (ClonesArrays->EFlowNeutralHadronSum() > 0) Print(2, "Number of EF Neut Had", ClonesArrays->EFlowNeutralHadronSum());
    for (int HadronNumber = 0; HadronNumber < ClonesArrays->EFlowNeutralHadronSum(); ++HadronNumber) {

        HadronClone = (Tower *) ClonesArrays->EFlowNeutralHadronClonesArray->At(HadronNumber);

        EFlowJetVector.push_back(GetPseudoJet(HadronClone->P4()));

    }

    // Muon
    if (ClonesArrays->EFlowMuonClonesArray) {

        Muon *EFlowMuonClone;

        Print(2, "Number of EF Muon", ClonesArrays->EFlowMuonSum());

        for (int MuonNumber = 0; MuonNumber < ClonesArrays->EFlowMuonSum(); ++MuonNumber) {

            EFlowMuonClone = (Muon *) ClonesArrays->EFlowMuonClonesArray->At(MuonNumber);

            // make sure this is not a muon
            Isolated = true;
            for (int MuonNumber = 0; MuonNumber < ClonesArrays->MuonSum(); ++MuonNumber) {

                MuonClone = (Muon *) ClonesArrays->MuonClonesArray->At(MuonNumber);
                Isolated = CheckIsolation(EFlowTrackClone, MuonClone);

            }


            if (Isolated) EFlowJetVector.push_back(GetPseudoJet(EFlowMuonClone->P4()));

        }

    }

    Print(2, "Number of EFlow Jet", EFlowJetVector.size());

    return 1;

}


void HJetDelphes::GetGenJet()
{
    Print(1, "GetGenJet");
    Jet *GenJetClone;

    Print(2, "Number of GenJets",  ClonesArrays->GenJetSum());
    for (int GenJetNumber = 0; GenJetNumber <  ClonesArrays->GenJetSum(); ++GenJetNumber) {

        GenJetClone = (Jet *) ClonesArrays->GenJetClonesArray->At(GenJetNumber);

        GenJetVector.push_back(GetPseudoJet(GenJetClone->P4()));

    }

}
