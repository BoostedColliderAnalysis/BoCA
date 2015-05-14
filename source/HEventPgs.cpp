# include "HEventPgs.hh"


hanalysis::hpgs::Event::Event()
{
    Print(kNotification, "Constructor");

    Lepton = new HLepton();
    jets = new HJet();
}

hanalysis::hpgs::Event::~Event()
{
    Print(kNotification, "Destructor");

    delete Lepton;
    delete jets;

}

void hanalysis::hpgs::Event::Newevent(const hanalysis::ClonesArrays &ClonesArrays)
{

    Print(kInformation, "New event");

    Lepton->Newevent(ClonesArrays);
    jets->Newevent(ClonesArrays);

}
