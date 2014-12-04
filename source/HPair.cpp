# include "HPair.hh"

hanalysis::HPair::HPair()
{
    Print(HInformation, "Constructor");

}

hanalysis::HPair::HPair(const fastjet::PseudoJet &NewJet1, const fastjet::PseudoJet &NewJet2)
{
  
  Print(HInformation, "Constructor");
  
  Jet1 = NewJet1;
  Jet2 = NewJet2;
  
}

hanalysis::HPair::~HPair()
{

    Print(HInformation, "Destructor");

}
