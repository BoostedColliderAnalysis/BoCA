# include "HEventBase.hh"

HEventBase::HEventBase()
{

    Print(0, "Constructor");

}

HEventBase::~HEventBase()
{

    Print(0, "Destructor");

}


void HEventBase::NewEvent(HClonesArrayBase *ImportClonesArrays)
{

    Print(1, "New Event");

    ClonesArrays = ImportClonesArrays;
    
    NewEvent();

}
