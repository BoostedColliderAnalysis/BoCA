
# include "HEvent.hh"

HEvent::HEvent()
{

    Print(0, "Constructor");

    Particle = new HParticle();
    Jets = new HJet();
    Leptons = new HLepton();
    TaggedTopClass = new HTopTagger();
    HiggsTagger = new HHiggsTagger();
    Discriminator = new HDiscriminator();

    Particles = 0;
    EFlow = 0;

}

HEvent::~HEvent()
{

    Print(0, "Destructor");

    delete Particle;
    delete Jets;
    delete Leptons;
    delete TaggedTopClass;
    delete HiggsTagger;
    delete Discriminator;

}

void HEvent::NewFile()
{

    Print(1, "New Analysis");

    Discriminator->NewFile();

}

void HEvent::CloseFile()
{

    Print(1, "Close File");

    Discriminator->CloseFile();

}


void HEvent::NewEvent(HClonesArrayBase *ImportClonesArrays)
{

    Print(1, "New Event");

    ClonesArrays = ImportClonesArrays;
    Particle->NewEvent();
    Jets->NewEvent();
    Leptons->NewEvent();
    TaggedTopClass->NewEvent();
    HiggsTagger->NewEvent();
    Discriminator->NewEvent();

    Particles = 0;
    EFlow = 0;

}


void HEvent::GetParticles()
{

    Print(1, "Get Particles");

    Particles = Particle->GetParticles(ClonesArrays);

}

void HEvent::GetLeptons()
{
    Print(1, "Get Leptons");

    Leptons->GetElectrons(ClonesArrays);
    Leptons->GetMuons(ClonesArrays);
    Leptons->GetLeptonLorentzVectorVector();

}

void HEvent::GetJets()
{
    Print(1, "Get Jets");

    Jets->AnalyseJet(ClonesArrays);

}



PseudoJet HEvent::GetHiggs()
{

    Print(1, "Get Higgs");

    if (!EFlow) EFlow = Jets->AnalyseEFlow(ClonesArrays);
    Particle->GetParticles(ClonesArrays);

    PseudoJet HiggsJet = HiggsTagger->GetHiggsJet(Jets->EFlowJetVector, Particle->BottomJetVector, Particle->CharmJetVector);

    return (HiggsJet);

}

vector<PseudoJet> HEvent::GetTops()
{

    Print(1, "Get Tops");

    if (!EFlow) EFlow =  Jets->AnalyseEFlow(ClonesArrays);
    if (Jets->EFlowJetVector.size() > 0) TaggedTopClass->TaggingTop(Jets->EFlowJetVector);
    vector<PseudoJet> TopJetVector = TaggedTopClass->TopJetVector;

    return (TopJetVector);

}


// vector<PseudoJet> HEvent::GetHiggsTopCandidates(bool Higgs, bool Tops, bool Candidates)
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


vector<PseudoJet> HEvent::GetHiggsTopCandidates()
{
    Print(1, "GetHiggsTopCandidates");

    vector<PseudoJet> CandidateJets;

    if (!EFlow) EFlow = Jets->AnalyseEFlow(ClonesArrays);
    if (!Particles) Particles = Particle->GetParticles(ClonesArrays);

    CandidateJets = Discriminator->GetTaggedCandidateJets(Jets->EFlowJetVector, Particle->HiggsJetVector, Particle->TopJetVector);

    return (CandidateJets);

}

// HEvent::GetPhotons()
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




