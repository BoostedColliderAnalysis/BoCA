# include "HPairJetPair.hh"


hanalysis::HPairJetPair::HPairJetPair(const HDoublet &NewPair, const fastjet::PseudoJet &NewJet) {
    Print(HInformation, "Constructor");
    Pair = NewPair;
    Jet = NewJet;
}

hanalysis::HPairJetPair::~HPairJetPair()
{

    Print(HInformation, "Destructor");

}
