# include "HEvent.hh"

HEvent::HEvent()
{

    Print(0, "Constructor");

}

HEvent::~HEvent()
{

    Print(0, "Destructor");

}


void HEvent::NewEvent(HClonesArray *NewClonesArrays)
{

    Print(1, "New Event");

    ClonesArrays = NewClonesArrays;
    
    NewEvent();

}
