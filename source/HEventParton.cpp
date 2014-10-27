# include "HEventParton.hh"


hanalysis::hparton::HEvent::HEvent()
{

    Print(1, "Constructor");

    Particles = new HParticle();

    HasParticles = 0;

}

hanalysis::hparton::HEvent::~HEvent()
{

    Print(1, "Destructor");

    delete Particles;

}

void hanalysis::hparton::HEvent::NewEvent(const hanalysis::HClonesArray * const ClonesArrays)
{

    Print(2, "New Event");

    Particles->NewEvent(ClonesArrays);

}


void hanalysis::hparton::HEvent::GetParticles()
{

    Print(2, "Get Particles");

    HasParticles = Particles->GetParticles();

}






