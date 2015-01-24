# include "HSextet.hh"
# include "HTagPrivate.hh"

class hanalysis::HSextetPrivate : public HTagPrivate {

public:

    HSextetPrivate() {}

    void SetTriplet1(const HTriplet &NewTriplet1);

    void SetTriplet2(const HTriplet &NewTriplet2);

    HTriplet Triplet1;

    HTriplet Triplet2;

};


void hanalysis::HSextetPrivate::SetTriplet1(const HTriplet &NewTriplet1) {
    Triplet1 = NewTriplet1;
}

void hanalysis::HSextetPrivate::SetTriplet2(const HTriplet &NewTriplet2) {
    Triplet2 = NewTriplet2;
}


hanalysis::HSextet::HSextet(HSextetPrivate& NewSextetPrivate) : HTag(NewSextetPrivate)
{
    Print(HInformation, "Constructor");
}

hanalysis::HTriplet hanalysis::HSextet::Triplet1() const {
    return static_cast<HSextetPrivate *>(TagPrivate)->Triplet1;
}

hanalysis::HTriplet hanalysis::HSextet::Triplet2() const {
    return static_cast<HSextetPrivate *>(TagPrivate)->Triplet2;
}

hanalysis::HSextet::HSextet(const HTriplet &NewTriplet1, const HTriplet &NewTriplet2) : hanalysis::HTag(*new HSextetPrivate)
{
    Print(HInformation, "Constructor");
    static_cast<HSextetPrivate *>(TagPrivate)->SetTriplet1(NewTriplet1);
    static_cast<HSextetPrivate *>(TagPrivate)->SetTriplet2(NewTriplet2);
    TagPrivate->Bdt = (NewTriplet1.Bdt() + NewTriplet2.Bdt()) / 2;
}


hanalysis::HSextet::~HSextet()
{
    Print(HInformation, "Destructor");
//     Error = 0;
}

