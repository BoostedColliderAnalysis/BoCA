# include "HTriplePair.hh"

hanalysis::HTriplePair::HTriplePair(const HTriple& NewTriple1, const HTriple& NewPair2) {
    Print(HInformation, "Constructor");
    Triple1 = NewTriple1;
    Triple2 = NewPair2;
    Error=0;
    Bdt=Triple1.GetBdt() * Triple2.GetBdt();
}

hanalysis::HTriplePair::HTriplePair(const HPairJetPair& NewTriple1, const HPairJetPair& NewPair2) {
    Print(HInformation, "Constructor");
//     Triple1 = (NewTriple1.Get);
//     Triple2 = NewPair2;
//     Error=0;
//     Bdt=Triple1.GetBdt() * Triple2.GetBdt();
}

hanalysis::HTriplePair::~HTriplePair()
{
    Print(HInformation, "Destructor");
    Error =0;
}

