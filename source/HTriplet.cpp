# include "HTriplet.hh"
# include "HTagPrivate.hh"

class hanalysis::HTripletPrivate : public HTagPrivate {

public:

    HTripletPrivate() {}

    void SetSinglet(const fastjet::PseudoJet &NewSinglet);

    void SetDoublet(const HDoublet &NewDoublet);

    HDoublet Doublet;

    fastjet::PseudoJet Singlet;

};

void hanalysis::HTripletPrivate::SetSinglet(const fastjet::PseudoJet& NewSinglet) {
    Singlet = NewSinglet;
}

void hanalysis::HTripletPrivate::SetDoublet(const hanalysis::HDoublet& NewDoublet) {
    Doublet = NewDoublet;
}

hanalysis::HTriplet::HTriplet() : hanalysis::HTag(*new HTripletPrivate)
{
    Print(HInformation, "Constructor");
}


hanalysis::HTriplet::HTriplet(HTripletPrivate& NewTripletPrivate) : HTag(NewTripletPrivate)
{
    Print(HInformation, "Constructor");
}

fastjet::PseudoJet hanalysis::HTriplet::Singlet() const {
    return static_cast<HTripletPrivate *>(TagPrivate)->Singlet;
}

hanalysis::HDoublet hanalysis::HTriplet::Doublet() const {
    return static_cast<HTripletPrivate *>(TagPrivate)->Doublet;
}

hanalysis::HTriplet::HTriplet(const hanalysis::HDoublet& NewDoublet, const fastjet::PseudoJet& NewSinglet)  : hanalysis::HTag(*new HTripletPrivate)
{

    Print(HInformation, "Constructor");

    static_cast<HTripletPrivate *>(TagPrivate)->SetSinglet(NewSinglet);
    static_cast<HTripletPrivate *>(TagPrivate)->SetDoublet(NewDoublet);
//     Triplet->Singlet = NewSinglet;
//     Triplet->Doublet = NewDoublet;
    if(NewSinglet.has_user_info<HJetInfo>()) if(NewSinglet.user_info<HJetInfo>().Bdt() != TagPrivate->InitialValue) TagPrivate->Bdt = (NewSinglet.user_info<HJetInfo>().Bdt() + NewDoublet.Bdt()) / 2;
}

hanalysis::HTriplet::HTriplet(const fastjet::PseudoJet& NewSinglet) : hanalysis::HTag(*new HTripletPrivate)
{

    Print(HInformation, "Constructor");

    static_cast<HTripletPrivate *>(TagPrivate)->SetSinglet(NewSinglet);
//     Triplet->Singlet = NewSinglet;
    HDoublet NewDoublet(NewSinglet);
//     Triplet->Doublet = NewDoublet;
    static_cast<HTripletPrivate *>(TagPrivate)->SetDoublet(NewDoublet);
    if(NewSinglet.has_user_info<HJetInfo>()) if(NewSinglet.user_info<HJetInfo>().Bdt() != TagPrivate->InitialValue) TagPrivate->Bdt = NewSinglet.user_info<HJetInfo>().Bdt();
}

hanalysis::HTriplet::~HTriplet()
{
    Print(HInformation, "Destructor");
//     delete Triplet;
}

// hanalysis::HDoublet hanalysis::HTriplet::Doublet()const {
//   return Triplet->Doublet;
// }
//
// fastjet::PseudoJet hanalysis::HTriplet::Singlet()const {
//   return Triplet->Singlet;
// }
