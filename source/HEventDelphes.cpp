# include "HEventDelphes.hh"

hdelphes::HEvent::HEvent()
{

    Print(1, "Constructor");

    Particles = new HParticle();
    Jets = new HJet();
    Lepton = new HLepton();
    TopTagger = new HTopTagger();
    HiggsTagger = new HHiggsTagger();
    Discriminator = new HDiscriminator();

//     HasParticles = 0;
//     HasEFlow = 0;
//     HasJets = 0;

//     Debug = 5;

}

hdelphes::HEvent::~HEvent()
{

    Print(1, "Destructor");

    delete Particles;
    delete Jets;
    delete Lepton;
    delete TopTagger;
    delete HiggsTagger;
    delete Discriminator;

}

void hdelphes::HEvent::NewEvent(const hanalysis::HClonesArray *const ClonesArrays)
{

    Print(2, "New Event");

    Particles->NewEvent(ClonesArrays);
    Jets->NewEvent(ClonesArrays);
    Lepton->NewEvent(ClonesArrays);

//     TopTagger->NewEvent();
    HiggsTagger->NewEvent();
    Discriminator->NewEvent();

//     HasParticles = 0;
//     HasEFlow = 0;
//     HasJets = 0;

}


// void hdelphes::HEvent::GetParticles()
// {
//
//     Print(2, "Get Particles");
//
//     if (!HasParticles) HasParticles = Particles->GetParticles();
//
// }


// HVectors hdelphes::HEvent::GetLeptons()
// {
//     Print(2, "Get Leptons");
//
// //     Lepton->GetElectrons();
// //     Lepton->GetMuons();
//     std::vector<TLorentzVector > LeptonVector = Lepton->GetLeptonLorentzVectors();
//     HJets LeptonJetVector = Lepton->GetLeptonJets();
//
//     return LeptonVector;
// }

// void hdelphes::HEvent::GetJets()
// {
//     Print(2, "Get Jets");
//
//     if (!HasJets) HasJets = Jets->GetJets(HJet::Plain);
//
// }

// void hdelphes::HEvent::GetStructuredJets()
// {
//   Print(2, "Get Jets");
//
//   Jets->GetStructuredJets();
//
// }

// void hdelphes::HEvent::GetTaggedJets(HJetTag *const JetTag)
// {
//     Print(2, "Get Tagged Jets");
//
// //     GetJets();
// //     GetParticles();
// //     Jets->JetVector = Particles->TagJets(Jets->JetVector);
//
//
//     if (!HasJets) {
//
//         Jets->SetJetTag(JetTag);
//         HasJets = Jets->GetTaggedJets();
//
//     }
//
// }


// void hdelphes::HEvent::GetEFlow()
// {
//
//     Print(2, "Get EFlow");
//
//     if (!HasEFlow) HasEFlow = Jets->ReadEFlow(HJet::Plain);
//
// }


// void hdelphes::HEvent::GetTaggedEFlow(HJetTag *const JetTag)
// {
//
//     Print(2, "Get EFlow");
//
//     if (!HasEFlow) {
//
//         Jets->SetJetTag(JetTag);
//
//         HasEFlow = Jets->ReadEFlow(HJet::Tagging);
//
//     }
//
// }


// void hdelphes::HEvent::GetIsolatedEFlow()
// {
//
//     Print(2, "Get EFlow");
//
//     if (!HasEFlow) HasEFlow = Jets->ReadEFlow(HJet::Isolation);
//
// }


// void hdelphes::HEvent::GetIsoaltedTaggedEFlow(HJetTag *const JetTag)
// {
//
//     Print(2, "Get EFlow");
//
//     if (!HasEFlow) {
//
//         Jets->SetJetTag(JetTag);
//
//         HasEFlow = Jets->ReadEFlow(HJet::TaggingIsolation);
//
//     }
//
// }


PseudoJet hdelphes::HEvent::GetHiggs()
{

    Print(2, "Get Higgs");

//     GetEFlow();
//     GetParticlesM()->GetParticles();

    PseudoJet HiggsJet = HiggsTagger->GetHiggsJet(Jets->GetEFlowJets(),Particles->GetBottomJets(),Particles->GetCharmJets());

    return (HiggsJet);

}

HJets hdelphes::HEvent::GetTops(hanalysis::HJetTag *const JetTag)
{

    Print(2, "Get Tops", JetTag->GetBranchId(0,0));

//     GetEFlow();

    HJets EFlowJets = Jets->GetEFlowJets();

//     HJets TopJetVector = TopTagger->GetTops(Jets->GetEFlowJets());
    HJets TopJetVector = TopTagger->GetTops(EFlowJets);

//     return (TopTagger->GetTops(Jets->GetEFlowJets()));

    return(TopJetVector);

}


// HJets HDelphes::HEvent::GetHiggsTopCandidates(bool Higgs, bool Tops, bool Candidates)
// {
//     Print(2,"GetHiggsTopCandidates");
//
//     HJets CandidateJets;
//
//     if (!EFlow) EFlow = Jets->AnalyseEFlow(ClonesArrays);
//     if (Higgs || Tops) Particle->GetParticles(ClonesArrays);
//
//     if (Particle->TopJetVector.size() > 0 && Tops && !Candidates) {
//
//         CandidateJets = HDelphes->GetTopJets(Jets->EFlowJetVector, Particle->HiggsJetVector, Particle->TopJetVector);
//
//     }
//
//     if (Particle->HiggsJetVector.size() > 0 && Higgs && !Candidates) {
//
//        PseudoJet HiggsJet = HDelphes->GetHiggsJet(Jets->EFlowJetVector, Particle->HiggsJetVector, Particle->TopJetVector);
//        CandidateJets.push_back(HiggsJet);
//
//     }
//
//     if (Candidates && !(Higgs || Tops) ) {
//
//         CandidateJets = HDelphes->GetCandidateJets(Jets->EFlowJetVector);
//
//     }
//
//     if (Higgs && Tops && Candidates) {
//
//         CandidateJets = HDelphes->GetTaggedCandidateJets(Jets->EFlowJetVector, Particle->HiggsJetVector, Particle->TopJetVector);
//
//     }
//
//     return (CandidateJets);
//
// }


HJets hdelphes::HEvent::GetCandidates(hanalysis::HJetTag * const JetTag) // FIXME why does this not work
{
    Print(2, "GetHiggsTopCandidates");

//     for(auto HeavyParticle : JetTag->HeavyParticles) {
//         Print(0,"HeavyParticle",HeavyParticle);
//     }

//     GetIsoaltedTaggedEFlow(JetTag);
//     GetParticles();

//     CandidateJets = HDelphes->GetTaggedCandidateJets(Jets->EFlowJetVector, Particles->HiggsJetVector, Particles->TopJetVector);
//     return HDelphes->GetCandidateJetsForced(Jets->GetEFlowJets(),Jets->GetScalarHt());
    return Discriminator->GetCandidateJets(Jets->GetIsolatedTaggedEFlowJets(JetTag), Jets->GetScalarHt());

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



