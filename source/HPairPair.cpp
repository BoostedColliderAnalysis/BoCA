# include "HPairPair.hh"

hanalysis::HPairPair::HPairPair(const HJetLeptonPair &NewPair1, const HJetLeptonPair &NewPair2) {
    Print(HInformation, "Constructor");
    Pair1 = NewPair1;
    Pair2 = NewPair2;
}

hanalysis::HPairPair::HPairPair(const HJetLeptonPair &NewPair1, const HJetLeptonPair &NewPair2, const float NewMet) {
    Print(HInformation, "Constructor");
    Pair1 = NewPair1;
    Pair2 = NewPair2;
    Met = NewMet;
}

hanalysis::HPairPair::~HPairPair()
{

    Print(HInformation, "Destructor");

}
