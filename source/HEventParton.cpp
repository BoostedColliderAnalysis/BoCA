# include "HEventParton.hh"
# include "HParticleParton.hh"


hanalysis::hparton::HEvent::HEvent()
{

    Print(kNotification, "Constructor");

    Particles = new HParticle();

}

hanalysis::hparton::HEvent::~HEvent()
{

    Print(kNotification, "Destructor");

    delete Particles;

}

void hanalysis::hparton::HEvent::NewEvent(const hanalysis::ClonesArrays &ClonesArrays)
{

    Print(kInformation, "New Event");

    Particles->NewEvent(ClonesArrays);

}
