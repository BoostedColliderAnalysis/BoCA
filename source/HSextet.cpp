# include "HSextet.hh"

hanalysis::HSextet::HSextet(const HTriplet &NewTriple1, const HTriplet &NewPair2)
{
    Print(HInformation, "Constructor");
    Triplet1 = NewTriple1;
    Triplet2 = NewPair2;
    Bdt = (Triplet1.GetBdt() + Triplet2.GetBdt()) / 2;
}


hanalysis::HSextet::~HSextet()
{
    Print(HInformation, "Destructor");
//     Error = 0;
}

