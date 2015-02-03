# include "HSextet.hh"
// # include "HTagPrivate.hh"
//
// class hanalysis::HSextetPrivate : public HTagPrivate {
//
// public:
//
//     HSextetPrivate() {}
//
//     void SetTriplet1(const HTriplet &NewTriplet1);
//
//     void SetTriplet2(const HTriplet &NewTriplet2);
//
//     HTriplet Triplet1;
//
//     HTriplet Triplet2;
//
// };


void hanalysis::HSextet::SetTriplet1(const HTriplet &NewTriplet1) {
    Triplet1M = NewTriplet1;
}

void hanalysis::HSextet::SetTriplet2(const HTriplet &NewTriplet2) {
    Triplet2M = NewTriplet2;
}


// hanalysis::HSextet::HSextet(HSextetPrivate& NewSextetPrivate) : HTag(NewSextetPrivate)
// {
//     Print(HInformation, "Constructor");
// }

hanalysis::HSextet::HSextet() {
  Print(HInformation, "Default Constructor");
}

hanalysis::HSextet::HSextet(const HTriplet &NewTriplet1, const HTriplet &NewTriplet2)
// : hanalysis::HTag(*new HSextetPrivate)
{
    Print(HInformation, "Constructor");
//     static_cast<HSextetPrivate *>(TagPrivate.get())->SetTriplet1(NewTriplet1);
//     static_cast<HSextetPrivate *>(TagPrivate.get())->SetTriplet2(NewTriplet2);
//     TagPrivate->Bdt = (NewTriplet1.Bdt() + NewTriplet2.Bdt()) / 2;
    SetTriplet1(NewTriplet1);
    SetTriplet2(NewTriplet2);
    SetBdt(NewTriplet1.Bdt(), NewTriplet2.Bdt());
    SetTag(NewTriplet1.Tag(), NewTriplet2.Tag());
}

hanalysis::HSextet::~HSextet()
{
    Print(HInformation, "Destructor");
}

hanalysis::HTriplet hanalysis::HSextet::Triplet1() const {
//     return static_cast<HSextetPrivate *>(TagPrivate.get())->Triplet1;
    return Triplet1M;
}

hanalysis::HTriplet hanalysis::HSextet::Triplet2() const {
//     return static_cast<HSextetPrivate *>(TagPrivate.get())->Triplet2;
    return Triplet2M;
}

