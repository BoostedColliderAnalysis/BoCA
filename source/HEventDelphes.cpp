# include "HEventDelphes.hh"
# include "HParticleDelphes.hh"
# include "HLeptonDelphes.hh"
# include "HJetDelphes.hh"

hanalysis::hdelphes::HEvent::HEvent()
{
// DebugLevel=HDebug;
    Print(HNotification, "Constructor");

    Particles = new hdelphes::HParticle();
    jets = new hdelphes::HJet();
    Lepton = new hdelphes::HLepton();
//     TopTagger = new HTopTagger();
//     HiggsTagger = new HHiggsTagger();
//     Discriminator = new HDiscriminator();

}

hanalysis::hdelphes::HEvent::~HEvent()
{

    Print(HNotification, "Destructor");

    delete Particles;
    delete jets;
    delete Lepton;
//     delete TopTagger;
//     delete HiggsTagger;
//     delete Discriminator;

}

void hanalysis::hdelphes::HEvent::NewEvent(const hanalysis::ClonesArrays &ClonesArrays)
{

    Print(HInformation, "New Event");

    Particles->NewEvent(ClonesArrays);
    jets->NewEvent(ClonesArrays);
    Lepton->NewEvent(ClonesArrays);

//     HiggsTagger->NewEvent();
//     Discriminator->NewEvent();

}

// fastjet::PseudoJet hanalysis::hdelphes::HEvent::GetHiggs()
// {
//
//     Print(HInformation, "Get Higgs");
//
// //     fastjet::PseudoJet HiggsJet = HiggsTagger->GetHiggsJet(Jets->GetEFlowJets(),Particles->GetBottomJets(),Particles->GetCharmJets());
//
//     return (HiggsJet);
//
// }
//
// Jets hanalysis::hdelphes::HEvent::GetTops(hanalysis::HJetTag &JetTag)
// {
//
//     Print(HInformation, "Get Tops", JetTag.GetBranchId(0,0));
//
//     Jets EFlowJets = Jets->GetEFlowJets();
//
// //     Jets TopJetVector = TopTagger->GetTops(EFlowJets);
//
//     return(TopJetVector);
//
// }
//
// Jets hanalysis::hdelphes::HEvent::GetCandidates(hanalysis::HJetTag  &JetTag) // FIXME why does this not work
// {
//     Print(HInformation, "GetHiggsTopCandidates");
//
//     return Discriminator->GetCandidateJets(Jets->GetIsolatedTaggedEFlowJets(JetTag), Jets->GetScalarHt());
//
// }


