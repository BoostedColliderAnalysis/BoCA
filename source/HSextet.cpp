# include "HSextet.hh"
// # include "HTagPrivate.hh"
//
// class analysis::HSextetPrivate : public HTagPrivate {
//
// public:
//
//     HSextetPrivate() {}
//
//     void Settriplet1(const Triplet &Newtriplet1);
//
//     void Settriplet2(const Triplet &Newtriplet2);
//
//     Triplet triplet1;
//
//     Triplet triplet2;
//
// };


void analysis::HSextet::Settriplet1(const Triplet &Newtriplet1) {
    triplet1M = Newtriplet1;
}

void analysis::HSextet::Settriplet2(const Triplet &Newtriplet2) {
    triplet2M = Newtriplet2;
}


// analysis::HSextet::HSextet(HSextetPrivate& NewSextetPrivate) : HTag(NewSextetPrivate)
// {
//     Print(kInformation, "Constructor");
// }

analysis::HSextet::HSextet() {
  Print(kInformation, "Default Constructor");
}

analysis::HSextet::HSextet(const Triplet &Newtriplet1, const Triplet &Newtriplet2)
// : analysis::HTag(*new HSextetPrivate)
{
    Print(kInformation, "Constructor");
//     static_cast<HSextetPrivate *>(TagPrivate.get())->Settriplet1(Newtriplet1);
//     static_cast<HSextetPrivate *>(TagPrivate.get())->Settriplet2(Newtriplet2);
//     TagPrivate->Bdt = (Newtriplet1.Bdt() + Newtriplet2.Bdt()) / 2;
    Settriplet1(Newtriplet1);
    Settriplet2(Newtriplet2);
    SetBdt(Newtriplet1.Bdt(), Newtriplet2.Bdt());
    SetTag(Newtriplet1.Tag(), Newtriplet2.Tag());
}

analysis::HSextet::~HSextet()
{
    Print(kInformation, "Destructor");
}

analysis::Triplet analysis::HSextet::triplet1() const {
//     return static_cast<HSextetPrivate *>(TagPrivate.get())->triplet1;
    return triplet1M;
}

analysis::Triplet analysis::HSextet::triplet2() const {
//     return static_cast<HSextetPrivate *>(TagPrivate.get())->triplet2;
    return triplet2M;
}

