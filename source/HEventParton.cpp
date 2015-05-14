# include "HEventParton.hh"
# include "HParticleParton.hh"


hanalysis::hparton::Event::Event()
{

    Print(kNotification, "Constructor");

    Particles = new HParticle();

}

hanalysis::hparton::Event::~Event()
{

    Print(kNotification, "Destructor");

    delete Particles;

}

void hanalysis::hparton::Event::Newevent(const hanalysis::ClonesArrays &ClonesArrays)
{

    Print(kInformation, "New event");

    Particles->Newevent(ClonesArrays);

}
