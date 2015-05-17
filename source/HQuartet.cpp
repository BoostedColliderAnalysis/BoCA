# include "HQuartet.hh"
# include "HTagPrivate.hh"

// class HQuartetPrivate : public analysis::HTagPrivate {
//
// public:
//
//   HQuartetPrivate() {}
//
// };


analysis::HQuartet::HQuartet(const Doublet &Newdoublet1, const Doublet &Newdoublet2)
// : analysis::HTag(*new HQuartetPrivate)
{
    Print(kInformation, "Constructor");
    doublet1 = Newdoublet1;
    doublet2 = Newdoublet2;
//     TagPrivate->Bdt = (doublet1.Bdt() + doublet2.Bdt())/2;
//     TagPrivate->Tag = doublet1.Tag() * doublet2.Tag();
    SetBdt((doublet1.Bdt() + doublet2.Bdt())/2);
    SetTag(doublet1.Tag() * doublet2.Tag());
}

// analysis::HQuartet::HQuartet(const Doublet &Newdoublet1, const Doublet &Newdoublet2, const fastjet::PseudoJet &NewMet)
// {
// //     DebugLevel = Object::kDebug;
//     Print(kInformation, "Constructor");
//     doublet1 = Newdoublet1;
//     doublet2 = Newdoublet2;
//     Met = NewMet;
//     Bdt = doublet1.Bdt() * doublet2.Bdt();
//     Tag = doublet1.Tag() * doublet2.Tag();
// }

analysis::HQuartet::~HQuartet()
{

//     Print(kInformation, "Destructor");

}
