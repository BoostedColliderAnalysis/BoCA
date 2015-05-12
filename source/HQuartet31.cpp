# include "HQuartet31.hh"
// # include "HTagPrivate.hh"
//
// class hanalysis::HQuartet31Private : public HTagPrivate
// {
//
// public:
//
// //     HQuartet31Private() {}
//
//     void Settriplet(const Triplet &Newtriplet);
//
//     void SetSinglet(const fastjet::PseudoJet &NewSinglet);
//
//     Triplet triplet;
//
//     fastjet::PseudoJet Singlet;
//
// };

void hanalysis::HQuartet31::Settriplet(const Triplet &Newtriplet)
{
    tripletM = Newtriplet;
}

void hanalysis::HQuartet31::SetSinglet(const fastjet::PseudoJet &NewSinglet)
{
    SingletM = NewSinglet;
}

// hanalysis::HQuartet31::HQuartet31(HQuartet31Private &NewQuartet31Private) : HTag(NewQuartet31Private)
// {
//     Print(kInformation, "Constructor");
// }

hanalysis::HQuartet31::HQuartet31()
// : hanalysis::HTag(*new HQuartet31Private)
{
    Print(kInformation, "Constructor");
}

hanalysis::HQuartet31::HQuartet31(const Triplet &Newtriplet, const fastjet::PseudoJet &NewSinglet)
// : hanalysis::HTag(*new HQuartet31Private)
{
    Print(kInformation, "Constructor");
//     static_cast<HQuartet31Private *>(TagPrivate.get())->Settriplet(Newtriplet);
//     static_cast<HQuartet31Private *>(TagPrivate.get())->SetSinglet(NewSinglet);
    Settriplet(Newtriplet);
    SetSinglet(NewSinglet);
    if (singlet().has_user_info<JetInfo>()) {
//         TagPrivate->Bdt = (triplet().Bdt() + singlet().user_info<JetInfo>().Bdt()) / 2;
//         TagPrivate->Tag = triplet().Tag() * singlet().user_info<JetInfo>().Tag();
        SetBdt(triplet().Bdt(),singlet().user_info<JetInfo>().Bdt());
        SetTag(triplet().Tag(),singlet().user_info<JetInfo>().Tag());
    }
    SetFlag(Newtriplet.Flag());
}

hanalysis::HQuartet31::~HQuartet31()
{
    Print(kInformation, "Destructor");
}

hanalysis::Triplet hanalysis::HQuartet31::triplet() const
{
//     return static_cast<HQuartet31Private *>(TagPrivate.get())->triplet;
    return tripletM;
}

fastjet::PseudoJet hanalysis::HQuartet31::singlet()const
{
//     return static_cast<HQuartet31Private *>(TagPrivate.get())->Singlet;
    return SingletM;
}
