# include "HQuartet.hh"
# include "HTagPrivate.hh"

// class HQuartetPrivate : public hanalysis::HTagPrivate {
//
// public:
//
//   HQuartetPrivate() {}
//
// };


hanalysis::HQuartet::HQuartet(const Doublet &Newdoublet1, const Doublet &Newdoublet2)
// : hanalysis::HTag(*new HQuartetPrivate)
{
    Print(kInformation, "Constructor");
    doublet1 = Newdoublet1;
    doublet2 = Newdoublet2;
//     TagPrivate->Bdt = (doublet1.Bdt() + doublet2.Bdt())/2;
//     TagPrivate->Tag = doublet1.Tag() * doublet2.Tag();
    SetBdt((doublet1.Bdt() + doublet2.Bdt())/2);
    SetTag(doublet1.Tag() * doublet2.Tag());
}

// hanalysis::HQuartet::HQuartet(const Doublet &Newdoublet1, const Doublet &Newdoublet2, const fastjet::PseudoJet &NewMet)
// {
// //     DebugLevel = HObject::kDebug;
//     Print(kInformation, "Constructor");
//     doublet1 = Newdoublet1;
//     doublet2 = Newdoublet2;
//     Met = NewMet;
//     Bdt = doublet1.Bdt() * doublet2.Bdt();
//     Tag = doublet1.Tag() * doublet2.Tag();
// }

hanalysis::HQuartet::~HQuartet()
{

//     Print(kInformation, "Destructor");

}
