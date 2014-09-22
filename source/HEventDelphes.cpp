# include "HEventDelphes.hh"

HEventDelphes::HEventDelphes()
{

    Print(0, "Constructor");

    Particles = new HParticleDelphes();
    Jets = new HJet();
    Lepton = new HLeptonDelphes();
    TopTagger = new HTopTagger();
    HiggsTagger = new HHiggsTagger();
    Discriminator = new HDiscriminator();

    HasParticles = 0;
    HasEFlow = 0;
    HasJets = 0;

}

HEventDelphes::~HEventDelphes()
{

    Print(0, "Destructor");

    delete Particles;
    delete Jets;
    delete Lepton;
    delete TopTagger;
    delete HiggsTagger;
    delete Discriminator;

}

void HEventDelphes::NewFile()
{

    Print(1, "New Analysis");

    Discriminator->NewFile();

}

void HEventDelphes::CloseFile()
{

    Print(1, "Close File");

    Discriminator->CloseFile();

}

void HEventDelphes::NewEvent()
{

    Print(1, "New Event");

    Particles->NewEvent(ClonesArrays);
    Jets->NewEvent(ClonesArrays);
    Lepton->NewEvent(ClonesArrays);

    TopTagger->NewEvent();
    HiggsTagger->NewEvent();
    Discriminator->NewEvent();

    HasParticles = 0;
    HasEFlow = 0;
    HasJets = 0;

}


void HEventDelphes::GetParticles()
{

    Print(1, "Get Particles");

    if (!HasParticles) HasParticles = Particles->GetParticles();

}


vector<TLorentzVector> HEventDelphes::GetLeptons()
{
    Print(1, "Get Leptons");

    Lepton->GetElectrons();
    Lepton->GetMuons();
    vector<TLorentzVector > LeptonVector = Lepton->GetLeptonVector();
    vector<PseudoJet> LeptonJetVector = Lepton->GetLeptonJetVector();

    return LeptonVector;
}

void HEventDelphes::GetJets()
{
    Print(1, "Get Jets");

    if (!HasJets) HasJets = Jets->GetJets();

}

void HEventDelphes::GetTaggedJets()
{
    Print(1, "Get Jets");

    GetJets();
    GetParticles();
    Jets->JetVector = Particles->TagJets(Jets->JetVector);


}



PseudoJet HEventDelphes::GetHiggs()
{

    Print(1, "Get Higgs");

    if (!HasEFlow) HasEFlow = Jets->GetEFlow();
    Particles->GetParticles();

    PseudoJet HiggsJet = HiggsTagger->GetHiggsJet(
                             Jets->EFlowJetVector,
                             Particles->BottomJetVector,
                             Particles->CharmJetVector);

    return (HiggsJet);

}

vector<PseudoJet> HEventDelphes::GetTops()
{

    Print(1, "Get Tops");

    if (!HasEFlow) HasEFlow =  Jets->GetEFlow();
    if (Jets->EFlowJetVector.size() > 0) TopTagger->TaggingTop(Jets->EFlowJetVector);
    vector<PseudoJet> TopJetVector = TopTagger->TopJetVector;

    return (TopJetVector);

}


// vector<PseudoJet> HEventDelphes::GetHiggsTopCandidates(bool Higgs, bool Tops, bool Candidates)
// {
//     Print(1,"GetHiggsTopCandidates");
//
//     vector<PseudoJet> CandidateJets;
//
//     if (!EFlow) EFlow = Jets->AnalyseEFlow(ClonesArrays);
//     if (Higgs || Tops) Particle->GetParticles(ClonesArrays);
//
//     if (Particle->TopJetVector.size() > 0 && Tops && !Candidates) {
//
//         CandidateJets = Discriminator->GetTopJets(Jets->EFlowJetVector, Particle->HiggsJetVector, Particle->TopJetVector);
//
//     }
//
//     if (Particle->HiggsJetVector.size() > 0 && Higgs && !Candidates) {
//
//        PseudoJet HiggsJet = Discriminator->GetHiggsJet(Jets->EFlowJetVector, Particle->HiggsJetVector, Particle->TopJetVector);
//        CandidateJets.push_back(HiggsJet);
//
//     }
//
//     if (Candidates && !(Higgs || Tops) ) {
//
//         CandidateJets = Discriminator->GetCandidateJets(Jets->EFlowJetVector);
//
//     }
//
//     if (Higgs && Tops && Candidates) {
//
//         CandidateJets = Discriminator->GetTaggedCandidateJets(Jets->EFlowJetVector, Particle->HiggsJetVector, Particle->TopJetVector);
//
//     }
//
//     return (CandidateJets);
//
// }


vector<PseudoJet> HEventDelphes::GetHiggsTopCandidates()
{
    Print(1, "GetHiggsTopCandidates");

    vector<PseudoJet> CandidateJets;

    if (!HasEFlow) HasEFlow = Jets->GetEFlow();
    if (!HasParticles) HasParticles = Particles->GetParticles();

    CandidateJets = Discriminator->GetTaggedCandidateJets(Jets->EFlowJetVector, Particles->HiggsJetVector, Particles->TopJetVector);

    return (CandidateJets);

}

// HEventDelphes::GetPhotons()
// {
//
//     int PhotonSum = ClonesArrays->PhotonClonesArray->GetEntriesFast();
//     if (Debug > 1) cout <<  "Number of Phoyons: " << PhotonSum <<  endl;
//     for (int PhotonNumber = 0; PhotonNumber < PhotonSum; PhotonNumber++) {
//
//         Photon *PhotonClone = (Photon *) ClonesArrays->GenJetClonesArray->At(PhotonNumber);
//         float GenJetPt = PhotonClone->PT;
//         float GenJetEta = PhotonClone->Eta;
//         float GenJetPhi = PhotonClone->Phi;
//         PseudoJet JetCandidate = FillJet(GenJetPt, GenJetEta, GenJetPhi);
//
//         GenJetVector.push_back(JetCandidate);
//
//     }
//
// }



