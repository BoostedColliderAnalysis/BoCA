# include "HEventDelphes.hh"
# include "HParticleDelphes.hh"
# include "HLeptonDelphes.hh"
# include "HJetDelphes.hh"

hanalysis::hdelphes::Event::Event()
{
// DebugLevel=kDebug;
    Print(kNotification, "Constructor");

    Particles = new hdelphes::HParticle();
    jets = new hdelphes::HJet();
    Lepton = new hdelphes::HLepton();
//     TopTagger = new HTopTagger();
//     HiggsTagger = new HHiggsTagger();
//     Discriminator = new HDiscriminator();

}

hanalysis::hdelphes::Event::~Event()
{

    Print(kNotification, "Destructor");

    delete Particles;
    delete jets;
    delete Lepton;
//     delete TopTagger;
//     delete HiggsTagger;
//     delete Discriminator;

}

void hanalysis::hdelphes::Event::Newevent(const hanalysis::ClonesArrays &ClonesArrays)
{

    Print(kInformation, "New event");

    Particles->Newevent(ClonesArrays);
    jets->Newevent(ClonesArrays);
    Lepton->Newevent(ClonesArrays);

//     HiggsTagger->Newevent();
//     Discriminator->Newevent();

}

// fastjet::PseudoJet hanalysis::hdelphes::Event::GetHiggs()
// {
//
//     Print(kInformation, "Get Higgs");
//
// //     fastjet::PseudoJet HiggsJet = HiggsTagger->GetHiggsJet(Jets->GetEFlowJets(),Particles->GetBottomJets(),Particles->GetCharmJets());
//
//     return (HiggsJet);
//
// }
//
// Jets hanalysis::hdelphes::Event::GetTops(hanalysis::HJetTag &JetTag)
// {
//
//     Print(kInformation, "Get Tops", JetTag.GetBranchId(0,0));
//
//     Jets EFlowJets = Jets->GetEFlowJets();
//
// //     Jets TopJetVector = TopTagger->GetTops(EFlowJets);
//
//     return(TopJetVector);
//
// }
//
// Jets hanalysis::hdelphes::Event::GetCandidates(hanalysis::HJetTag  &JetTag) // FIXME why does this not work
// {
//     Print(kInformation, "GetHiggsTopCandidates");
//
//     return Discriminator->GetCandidateJets(Jets->GetIsolatedTaggedEFlowJets(JetTag), Jets->GetScalarHt());
//
// }


