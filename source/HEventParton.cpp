# include "HEventParton.hh"


hparton::HEvent::HEvent()
{

    Print(1, "Constructor");

    Particles = new HParticle();

}

hparton::HEvent::~HEvent()
{

    Print(1, "Destructor");

    delete Particles;

}

void hparton::HEvent::NewEvent(const hanalysis::HClonesArray * const ClonesArrays)
{

    Print(2, "New Event");

    Particles->NewEvent(ClonesArrays);

}


// void hparton::HEvent::GetParticles()
// {
// //
//     Print(2, "Get Particles");
//
//     HasParticles = Particles->GetParticles();
//
// }






