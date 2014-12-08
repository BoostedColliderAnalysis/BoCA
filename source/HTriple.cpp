# include "HTriple.hh"

hanalysis::HTriple::HTriple()
{
    Print(HInformation, "Constructor");

}

hanalysis::HTriple::HTriple(const fastjet::PseudoJet &NewJet1, const fastjet::PseudoJet &NewJet2, const fastjet::PseudoJet &NewJet3)
{
  
  Print(HInformation, "Constructor");
  
  Jet1 = NewJet1;
  Jet2 = NewJet2;
  Jet3 = NewJet3;
  
}

hanalysis::HTriple::HTriple(const fastjet::PseudoJet &NewJet1, const HJetLeptonPair &Pair)
{
  
  Print(HInformation, "Constructor");
  
  Jet1 = NewJet1;
  Jet2 = Pair.GetLepton();
  Jet3 = Pair.GetJet();
  Bdt = Pair.GetBdt();
  Tag = Pair.GetTag();
  
}

hanalysis::HTriple::~HTriple()
{

    Print(HInformation, "Destructor");

}
