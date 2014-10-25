# include "HEventDelphes.hh"

Analysis::HDelphes::HEvent::HEvent()
{

    Print(1, "Constructor");

    Particles = new HParticle();
    Jets = new HJet();
    Lepton = new HLepton();
    TopTagger = new Analysis::HTopTagger();
    HiggsTagger = new Analysis::HHiggsTagger();
    Discriminator = new Analysis::HDiscriminator();

    HasParticles = 0;
    HasEFlow = 0;
    HasJets = 0;

//     Debug = 5;

}

Analysis::HDelphes::HEvent::~HEvent()
{

    Print(1, "Destructor");

    delete Particles;
    delete Jets;
    delete Lepton;
    delete TopTagger;
    delete HiggsTagger;
    delete Discriminator;

}

// void HDelphes::HEvent::NewFile()
// {
//
//     Print(2, "New Analysis");
//
//     Discriminator->NewFile();
//
// }

// void HDelphes::HEvent::CloseFile()
// {
//
//     Print(2, "Close File");
//
//     Discriminator->CloseFile();
//
// }

void Analysis::HDelphes::HEvent::NewEvent(const Analysis::HClonesArray *const ClonesArrays)
{

    Print(2, "New Event");

    Particles->NewEvent(ClonesArrays);
    Jets->NewEvent(ClonesArrays);
    Lepton->NewEvent(ClonesArrays);

//     TopTagger->NewEvent();
    HiggsTagger->NewEvent();
    Discriminator->NewEvent();

    HasParticles = 0;
    HasEFlow = 0;
    HasJets = 0;

}


void Analysis::HDelphes::HEvent::GetParticles()
{

    Print(2, "Get Particles");

    if (!HasParticles) HasParticles = Particles->GetParticles();

}


vector<TLorentzVector> Analysis::HDelphes::HEvent::GetLeptons()
{
    Print(2, "Get Leptons");

    Lepton->GetElectrons();
    Lepton->GetMuons();
    vector<TLorentzVector > LeptonVector = Lepton->GetLeptonLorentzVectors();
    vector<PseudoJet> LeptonJetVector = Lepton->GetLeptonJets();

    return LeptonVector;
}

void Analysis::HDelphes::HEvent::GetJets()
{
    Print(2, "Get Jets");

    if (!HasJets) HasJets = Jets->GetJets(Analysis::HJet::Plain);

}

void Analysis::HDelphes::HEvent::GetTaggedJets(Analysis::HJetTag*const JetTag)
{
    Print(2, "Get Tagged Jets");

//     GetJets();
//     GetParticles();
//     Jets->JetVector = Particles->TagJets(Jets->JetVector);


    if (!HasJets) {

        Jets->JetTag = JetTag;
        HasJets = Jets->GetJets(Analysis::HJet::Tagging);

    }

}


void Analysis::HDelphes::HEvent::GetEFlow()
{

    Print(2, "Get EFlow");

    if (!HasEFlow) HasEFlow = Jets->ReadEFlow(Analysis::HJet::Plain);

}


void Analysis::HDelphes::HEvent::GetTaggedEFlow(Analysis::HJetTag*const JetTag)
{

    Print(2, "Get EFlow");

    if (!HasEFlow) {

        Jets->JetTag = JetTag;

        HasEFlow = Jets->ReadEFlow(Analysis::HJet::HJet::Tagging);

    }

}


void Analysis::HDelphes::HEvent::GetIsolatedEFlow()
{

    Print(2, "Get EFlow");

    if (!HasEFlow) HasEFlow = Jets->ReadEFlow(Analysis::HJet::Isolation);

}


void Analysis::HDelphes::HEvent::GetIsoaltedTaggedEFlow(Analysis::HJetTag*const JetTag)
{

    Print(2, "Get EFlow");

    if (!HasEFlow) {

        Jets->JetTag = JetTag;

        HasEFlow = Jets->ReadEFlow(Analysis::HJet::TaggingIsolation);

    }

}


PseudoJet Analysis::HDelphes::HEvent::GetHiggs()
{

    Print(2, "Get Higgs");

    GetEFlow();
    GetParticles();

    PseudoJet HiggsJet = HiggsTagger->GetHiggsJet(
                             Jets->EFlowJets,
                             Particles->BottomJetVector,
                             Particles->CharmJetVector);

    return (HiggsJet);

}

vector<PseudoJet> Analysis::HDelphes::HEvent::GetTops(const Analysis::HJetTag*const JetTag)
{

    Print(2, "Get Tops");

    GetEFlow();

    vector<PseudoJet> TopJetVector = TopTagger->GetTops(Jets->GetEFlowJets());

    return (TopJetVector);

}


// vector<PseudoJet> HDelphes::HEvent::GetHiggsTopCandidates(bool Higgs, bool Tops, bool Candidates)
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


vector<PseudoJet> Analysis::HDelphes::HEvent::GetHiggsTopCandidates(Analysis::HJetTag*const JetTag)
{
    Print(2, "GetHiggsTopCandidates");

    GetIsoaltedTaggedEFlow(JetTag);
//     GetParticles();

//     CandidateJets = Discriminator->GetTaggedCandidateJets(Jets->EFlowJetVector, Particles->HiggsJetVector, Particles->TopJetVector);
//     return Discriminator->GetCandidateJetsForced(Jets->GetEFlowJets(),Jets->GetScalarHt());
    return Discriminator->GetCandidateJets(Jets->GetEFlowJets(),Jets->GetScalarHt());

}

// HDelphes::HEvent::GetPhotons()
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



