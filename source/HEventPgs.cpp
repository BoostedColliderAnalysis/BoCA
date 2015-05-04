# include "HEventPgs.hh"


hanalysis::hpgs::HEvent::HEvent()
{
    Print(HNotification, "Constructor");

    Lepton = new HLepton();
    Jets = new HJet();
}

hanalysis::hpgs::HEvent::~HEvent()
{
    Print(HNotification, "Destructor");

    delete Lepton;
    delete Jets;

}

void hanalysis::hpgs::HEvent::NewEvent(const hanalysis::ClonesArrays &ClonesArrays)
{

    Print(HInformation, "New Event");

    Lepton->NewEvent(ClonesArrays);
    Jets->NewEvent(ClonesArrays);

}
