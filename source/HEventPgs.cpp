# include "HEventPgs.hh"


hanalysis::hpgs::HEvent::HEvent()
{
    Print(kNotification, "Constructor");

    Lepton = new HLepton();
    jets = new HJet();
}

hanalysis::hpgs::HEvent::~HEvent()
{
    Print(kNotification, "Destructor");

    delete Lepton;
    delete jets;

}

void hanalysis::hpgs::HEvent::NewEvent(const hanalysis::ClonesArrays &ClonesArrays)
{

    Print(kInformation, "New Event");

    Lepton->NewEvent(ClonesArrays);
    jets->NewEvent(ClonesArrays);

}
