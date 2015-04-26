# include "HTriplet.hh"
// # include "HTagPrivate.hh"

// class hanalysis::HTripletPrivate : public HTagPrivate
// {
//
// public:
//
// //     HTripletPrivate() {}
//
//     void SetSinglet(const fastjet::PseudoJet &NewSinglet);
//
//     void SetDoublet(const HDoublet &NewDoublet);
//
//     HDoublet Doublet;
//
//     fastjet::PseudoJet Singlet;
//
// };

// void hanalysis::HTripletPrivate::SetSinglet(const fastjet::PseudoJet &NewSinglet)
// {
//     Singlet = NewSinglet;
// }
//
// void hanalysis::HTripletPrivate::SetDoublet(const hanalysis::HDoublet &NewDoublet)
// {
//     Doublet = NewDoublet;
// }

void hanalysis::HTriplet::SetSinglet(const fastjet::PseudoJet &NewSinglet)
{
  singlet_ = NewSinglet;
}

void hanalysis::HTriplet::SetDoublet(const hanalysis::HDoublet &NewDoublet)
{
  doublet_ = NewDoublet;
}

hanalysis::HTriplet::HTriplet()
// : hanalysis::HTag(*new HTripletPrivate)
{
    Print(HInformation, "Constructor");
}


// hanalysis::HTriplet::HTriplet(HTripletPrivate &NewTripletPrivate) : HTag(NewTripletPrivate)
// {
//     Print(HInformation, "Constructor");
// }

fastjet::PseudoJet hanalysis::HTriplet::Singlet() const
{
//     return static_cast<HTripletPrivate *>(TagPrivate.get())->Singlet;
    return singlet_;
}

hanalysis::HDoublet hanalysis::HTriplet::Doublet() const
{
//     return dynamic_cast<HTripletPrivate *>(TagPrivate.get())->Doublet;
    return doublet_;
}

hanalysis::HTriplet::HTriplet(const hanalysis::HDoublet &NewDoublet, const fastjet::PseudoJet &NewSinglet)
// : hanalysis::HTag(*new HTripletPrivate)
{

    Print(HInformation, "Constructor");

//     static_cast<HTripletPrivate *>(TagPrivate.get())->SetSinglet(NewSinglet);
//     static_cast<HTripletPrivate *>(TagPrivate.get())->SetDoublet(NewDoublet);
    SetSinglet(NewSinglet);
    SetDoublet(NewDoublet);
//     if (NewSinglet.has_user_info<HJetInfo>()) if (NewSinglet.user_info<HJetInfo>().Bdt() != TagPrivate.get()->InitialValue) TagPrivate.get()->Bdt = (NewSinglet.user_info<HJetInfo>().Bdt() + NewDoublet.Bdt()) / 2;
    if (NewSinglet.has_user_info<HJetInfo>() && NewSinglet.user_info<HJetInfo>().Bdt() != initial_value()) SetBdt(NewSinglet.user_info<HJetInfo>().Bdt(),NewDoublet.Bdt());
    SetFlag(NewDoublet.Flag());
}

hanalysis::HTriplet::HTriplet(const fastjet::PseudoJet &NewSinglet)
// : hanalysis::HTag(*new HTripletPrivate)
{

    Print(HInformation, "Constructor");

//     static_cast<HTripletPrivate *>(TagPrivate.get())->SetSinglet(NewSinglet / 2);
//     static_cast<HTripletPrivate *>(TagPrivate.get())->SetDoublet(HDoublet(NewSinglet / 2));
//     if (NewSinglet.has_user_info<HJetInfo>()) if (NewSinglet.user_info<HJetInfo>().Bdt() != TagPrivate.get()->InitialValue) TagPrivate.get()->Bdt = NewSinglet.user_info<HJetInfo>().Bdt();

    SetSinglet(NewSinglet / 2);
    SetDoublet(HDoublet(NewSinglet / 2));
    SetDegenerate();
    if (NewSinglet.has_user_info<HJetInfo>() && NewSinglet.user_info<HJetInfo>().Bdt() != initial_value()) SetBdt(NewSinglet.user_info<HJetInfo>().Bdt());
    else SetBdt(0);
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
