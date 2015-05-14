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
}

hanalysis::hdelphes::Event::~Event()
{

    Print(kNotification, "Destructor");

    delete Particles;
    delete jets;
    delete Lepton;
}

void hanalysis::hdelphes::Event::Newevent(const hanalysis::ClonesArrays &ClonesArrays)
{

    Print(kInformation, "New event");

    Particles->Newevent(ClonesArrays);
    jets->Newevent(ClonesArrays);
    Lepton->Newevent(ClonesArrays);

}
