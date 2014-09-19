# include "HEventParton.hh"


HEventParton::HEventParton()
{

    Print(0, "Constructor");

    Particle = new HParticleParton();

    Particles = 0;

}

HEventParton::~HEventParton()
{

    Print(0, "Destructor");

    delete Particle;

}

void HEventParton::NewEvent()
{

    Print(1, "New Event");

    Particle->NewEvent(ClonesArrays);

}


void HEventParton::GetParticles()
{
    
    Print(1, "Get Particles");
    
    Particles = Particle->GetParticles();
    
}






