# include "HPairJetPair.hh"


hanalysis::HPairJetPair::HPairJetPair(const HPair &NewPair, const fastjet::PseudoJet &NewJet) {
    Print(HInformation, "Constructor");
    Pair = NewPair;
    Jet = NewJet;
}

hanalysis::HPairJetPair::~HPairJetPair()
{

    Print(HInformation, "Destructor");

}
