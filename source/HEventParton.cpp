# include "HEventParton.hh"


hanalysis::hparton::HEvent::HEvent()
{

    Print(HNotification, "Constructor");

    Particles = new HParticle();

}

hanalysis::hparton::HEvent::~HEvent()
{

    Print(HNotification, "Destructor");

    delete Particles;

}

void hanalysis::hparton::HEvent::NewEvent(const hanalysis::HClonesArray * const ClonesArrays)
{

    Print(HInformation, "New Event");

    Particles->NewEvent(ClonesArrays);

}


// void hparton::HEvent::GetParticles()
// {
// //
//     Print(HInformation, "Get Particles");
//
//     HasParticles = Particles->GetParticles();
//
// }






