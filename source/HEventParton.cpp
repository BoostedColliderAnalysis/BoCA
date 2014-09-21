# include "HEventParton.hh"


HEventParton::HEventParton()
{

    Print(0, "Constructor");

    Particles = new HParticleParton();

    HasParticles = 0;

}

HEventParton::~HEventParton()
{

    Print(0, "Destructor");

    delete Particles;

}

void HEventParton::NewEvent()
{

    Print(1, "New Event");

    Particles->NewEvent(ClonesArrays);

}


void HEventParton::GetParticles()
{
    
    Print(1, "Get Particles");
    
    HasParticles = Particles->GetParticles();
    
}






