# include "HEventDelphes.hh"

HEventDelphes::HEventDelphes()
{

    Print(1, "Constructor");

    Particles = new HParticleDelphes();
    Jets = new HJetDelphes();
    Lepton = new HLeptonDelphes();
    TopTagger = new HTopTagger();
    HiggsTagger = new HHiggsTagger();
    Discriminator = new HDiscriminator();

    HasParticles = 0;
    HasEFlow = 0;
    HasJets = 0;

//     Debug = 5;

}

HEventDelphes::~HEventDelphes()
{

    Print(1, "Destructor");

    delete Particles;
    delete Jets;
    delete Lepton;
    delete TopTagger;
    delete HiggsTagger;
    delete Discriminator;

}

void HEventDelphes::NewFile()
{

    Print(2, "New Analysis");

    Discriminator->NewFile();

}

void HEventDelphes::CloseFile()
{

    Print(2, "Close File");

    Discriminator->CloseFile();

}

void HEventDelphes::NewEvent(const HClonesArray * const ClonesArrays)
{

    Print(2, "New Event");

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

    Print(2, "Get Particles");

    if (!HasParticles) HasParticles = Particles->GetParticles();

}


vector<TLorentzVector> HEventDelphes::GetLeptons()
{
    Print(2, "Get Leptons");

    Lepton->GetElectrons();
    Lepton->GetMuons();
    vector<TLorentzVector > LeptonVector = Lepton->GetLeptonVector();
    vector<PseudoJet> LeptonJetVector = Lepton->GetLeptonJetVector();

    return LeptonVector;
}

void HEventDelphes::GetJets()
{
    Print(2, "Get Jets");

    if (!HasJets) HasJets = Jets->GetJets();

}

void HEventDelphes::GetTaggedJets()
{
    Print(2, "Get Tagged Jets");

//     GetJets();
//     GetParticles();
//     Jets->JetVector = Particles->TagJets(Jets->JetVector);


    if (!HasJets) HasJets = Jets->GetTaggedJets();



}


void HEventDelphes::GetEFlow()
{

    Print(2, "Get EFlow");

    if (!HasEFlow) HasEFlow = Jets->GetEFlow();

}


void HEventDelphes::GetTaggedEFlow()
{

    Print(2, "Get EFlow");

    if (!HasEFlow) HasEFlow = Jets->GetTaggedEFlow();

}


PseudoJet HEventDelphes::GetHiggs()
{

    Print(2, "Get Higgs");

    GetEFlow();
    GetParticles();

    PseudoJet HiggsJet = HiggsTagger->GetHiggsJet(
                             Jets->EFlowJetVector,
                             Particles->BottomJetVector,
                             Particles->CharmJetVector);

    return (HiggsJet);

}

vector<PseudoJet> HEventDelphes::GetTops()
{

    Print(2, "Get Tops");

    GetEFlow();
    if (Jets->EFlowJetVector.size() > 0) TopTagger->TaggingTop(Jets->EFlowJetVector);
    vector<PseudoJet> TopJetVector = TopTagger->TopJetVector;

    return (TopJetVector);

}


// vector<PseudoJet> HEventDelphes::GetHiggsTopCandidates(bool Higgs, bool Tops, bool Candidates)
// {
//     Print(2,"GetHiggsTopCandidates");
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
    Print(2, "GetHiggsTopCandidates");

    GetTaggedEFlow();
//     GetParticles();

//     CandidateJets = Discriminator->GetTaggedCandidateJets(Jets->EFlowJetVector, Particles->HiggsJetVector, Particles->TopJetVector);
    return Discriminator->GetCandidateJets(Jets->EFlowJetVector);

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



