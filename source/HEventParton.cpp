# include "HEventParton.hh"


HEventParton::HEventParton()
{

    Print(1, "Constructor");

    Particles = new HParticleParton();

    HasParticles = 0;

}

HEventParton::~HEventParton()
{

    Print(1, "Destructor");

    delete Particles;

}

void HEventParton::NewEvent(HClonesArray *ClonesArrays)
{

    Print(2, "New Event");

    Particles->NewEvent(ClonesArrays);

}


void HEventParton::GetParticles()
{
    
    Print(2, "Get Particles");
    
    HasParticles = Particles->GetParticles();
    
}






