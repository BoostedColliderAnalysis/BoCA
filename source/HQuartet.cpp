# include "HQuartet.hh"

hanalysis::HQuartet::HQuartet(const HDoublet &NewDoublet1, const HDoublet &NewDoublet2)
{
    Print(HInformation, "Constructor");
    Doublet1 = NewDoublet1;
    Doublet2 = NewDoublet2;
    Bdt = Doublet1.GetBdt() * Doublet2.GetBdt();
    Tag = Doublet1.GetTag() * Doublet2.GetTag();
}

// hanalysis::HQuartet::HQuartet(const HDoublet &NewDoublet1, const HDoublet &NewDoublet2, const fastjet::PseudoJet &NewMet)
// {
// //     DebugLevel = HObject::HDebug;
//     Print(HInformation, "Constructor");
//     Doublet1 = NewDoublet1;
//     Doublet2 = NewDoublet2;
//     Met = NewMet;
//     Bdt = Doublet1.GetBdt() * Doublet2.GetBdt();
//     Tag = Doublet1.GetTag() * Doublet2.GetTag();
// }

hanalysis::HQuartet::~HQuartet()
{

//     Print(HInformation, "Destructor");

}
