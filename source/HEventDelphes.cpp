# include "HEventDelphes.hh"

HEventDelphes::HEventDelphes()
{

    Print(0, "Constructor");

    Particle = new HParticleDelphes();
    Jets = new HJet();
    Leptons = new HLeptonDelphes();
    TopTagger = new HTopTagger();
    HiggsTagger = new HHiggsTagger();
    Discriminator = new HDiscriminator();

    Particles = 0;
    EFlow = 0;

}

HEventDelphes::~HEventDelphes()
{

    Print(0, "Destructor");

    delete Particle;
    delete Jets;
    delete Leptons;
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

    Particle->NewEvent(ClonesArrays);
    Jets->NewEvent(ClonesArrays);
    Leptons->NewEvent(ClonesArrays);
    
    TopTagger->NewEvent();
    HiggsTagger->NewEvent();
    Discriminator->NewEvent();

//     Particles = 0;
    EFlow = 0;

}


void HEventDelphes::GetParticles()
{

    Print(1, "Get Particles");

    Particles = Particle->GetParticles();

}


vector<TLorentzVector> HEventDelphes::GetLeptons()
{
    Print(1, "Get Leptons");

    Leptons->GetElectrons();
    Leptons->GetMuons();
    vector<TLorentzVector > LeptonVector =Leptons->GetLeptonVector();
    vector<PseudoJet> LeptonJetVector =Leptons->GetLeptonJetVector();

    return LeptonVector;
}

void HEventDelphes::GetJets()
{
    Print(1, "Get Jets");

    Jets->AnalyseJet();

}



PseudoJet HEventDelphes::GetHiggs()
{

    Print(1, "Get Higgs");

    if (!EFlow) EFlow = Jets->AnalyseEFlow();
    Particle->GetParticles();

    PseudoJet HiggsJet = HiggsTagger->GetHiggsJet(
                             Jets->EFlowJetVector,
                             Particle->BottomJetVector,
                             Particle->CharmJetVector);

    return (HiggsJet);

}

vector<PseudoJet> HEventDelphes::GetTops()
{

    Print(1, "Get Tops");

    if (!EFlow) EFlow =  Jets->AnalyseEFlow();
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

    if (!EFlow) EFlow = Jets->AnalyseEFlow();
    if (!Particles) Particles = Particle->GetParticles();

    CandidateJets = Discriminator->GetTaggedCandidateJets(Jets->EFlowJetVector, Particle->HiggsJetVector, Particle->TopJetVector);

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



