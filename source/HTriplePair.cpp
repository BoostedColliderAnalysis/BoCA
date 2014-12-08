# include "HTriplePair.hh"

hanalysis::HTriplePair::HTriplePair(const hanalysis::HTriple& NewTriple1, const hanalysis::HTriple& NewPair2) {
    Print(HInformation, "Constructor");
    Triple1 = NewTriple1;
    Triple2 = NewPair2;
    Error=0;
    Bdt=Triple1.GetBdt() * Triple2.GetBdt();
}

hanalysis::HTriplePair::~HTriplePair()
{
    Print(HInformation, "Destructor");
    Error =0;
}

