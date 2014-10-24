# include "HEventParton.hh"


HParton::HEvent::HEvent()
{

    Print(1, "Constructor");

    Particles = new HParticle();

    HasParticles = 0;

}

HParton::HEvent::~HEvent()
{

    Print(1, "Destructor");

    delete Particles;

}

void HParton::HEvent::NewEvent(const Analysis::HClonesArray * const ClonesArrays)
{

    Print(2, "New Event");

    Particles->NewEvent(ClonesArrays);

}


void HParton::HEvent::GetParticles()
{

    Print(2, "Get Particles");

    HasParticles = Particles->GetParticles();

}






