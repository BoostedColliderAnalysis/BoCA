# include "HQuartet.hh"
# include "HTagPrivate.hh"

// class HQuartetPrivate : public hanalysis::HTagPrivate {
//
// public:
//
//   HQuartetPrivate() {}
//
// };


hanalysis::HQuartet::HQuartet(const HDoublet &NewDoublet1, const HDoublet &NewDoublet2)
// : hanalysis::HTag(*new HQuartetPrivate)
{
    Print(HInformation, "Constructor");
    Doublet1 = NewDoublet1;
    Doublet2 = NewDoublet2;
//     TagPrivate->Bdt = (Doublet1.Bdt() + Doublet2.Bdt())/2;
//     TagPrivate->Tag = Doublet1.Tag() * Doublet2.Tag();
    SetBdt((Doublet1.Bdt() + Doublet2.Bdt())/2);
    SetTag(Doublet1.Tag() * Doublet2.Tag());
}

// hanalysis::HQuartet::HQuartet(const HDoublet &NewDoublet1, const HDoublet &NewDoublet2, const fastjet::PseudoJet &NewMet)
// {
// //     DebugLevel = HObject::HDebug;
//     Print(HInformation, "Constructor");
//     Doublet1 = NewDoublet1;
//     Doublet2 = NewDoublet2;
//     Met = NewMet;
//     Bdt = Doublet1.Bdt() * Doublet2.Bdt();
//     Tag = Doublet1.Tag() * Doublet2.Tag();
// }

hanalysis::HQuartet::~HQuartet()
{

//     Print(HInformation, "Destructor");

}
