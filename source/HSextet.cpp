# include "HSextet.hh"

hanalysis::HSextet::HSextet(const HTriplet &NewTriple1, const HTriplet &NewPair2)
{
    Print(HInformation, "Constructor");
    Triple1 = NewTriple1;
    Triple2 = NewPair2;
    Error = 0;
    Bdt = Triple1.GetBdt() * Triple2.GetBdt();
}

// hanalysis::HTriplePair::HTriplePair(const HPairJetPair &NewTriple1, const HPairJetPair &NewTriple2)
// {
//     Print(HInformation, "Constructor");
//     Triple1.SetJets(NewTriple1.GetPairJet1(), NewTriple1.GetPairJet2(),NewTriple1.GetJet());
//     Triple1.SetBdt(NewTriple1.GetBdt());
//     Triple2.SetJets(NewTriple2.GetPairJet1(), NewTriple2.GetPairJet2(),NewTriple2.GetJet());
//     Triple2.SetBdt(NewTriple2.GetBdt());
// //     Triple2 = NewPair2;
// //     Error=0;
// //     Bdt=Triple1.GetBdt() * Triple2.GetBdt();
// }

// hanalysis::HTriplePair::HTriplePair(const HTriplet &NewTriple1, const HPairJetPair &NewTriple2)
// {
//     Print(HInformation, "Constructor");
//     Triple1 = NewTriple1;
//     Triple2.SetJets(NewTriple2.GetPairJet1(), NewTriple2.GetPairJet2(),NewTriple2.GetJet());
//     Triple2.SetBdt(NewTriple2.GetBdt());
// }

hanalysis::HSextet::~HSextet()
{
    Print(HInformation, "Destructor");
    Error = 0;
}

