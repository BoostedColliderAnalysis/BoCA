# include "Triplet.hh"
// # include "HTagPrivate.hh"

// class hanalysis::TripletPrivate : public HTagPrivate
// {
//
// public:
//
// //     TripletPrivate() {}
//
//     void SetSinglet(const fastjet::PseudoJet &NewSinglet);
//
//     void Setdoublet(const Doublet &Newdoublet);
//
//     Doublet doublet;
//
//     fastjet::PseudoJet Singlet;
//
// };

// void hanalysis::TripletPrivate::SetSinglet(const fastjet::PseudoJet &NewSinglet)
// {
//     Singlet = NewSinglet;
// }
//
// void hanalysis::TripletPrivate::Setdoublet(const hanalysis::Doublet &Newdoublet)
// {
//     doublet = Newdoublet;
// }

void hanalysis::Triplet::SetSinglet(const fastjet::PseudoJet &NewSinglet)
{
  singlet_ = NewSinglet;
}

void hanalysis::Triplet::Setdoublet(const hanalysis::Doublet &Newdoublet)
{
  doublet_ = Newdoublet;
}

hanalysis::Triplet::Triplet()
// : hanalysis::HTag(*new TripletPrivate)
{
    Print(kInformation, "Constructor");
}


// hanalysis::Triplet::Triplet(TripletPrivate &NewtripletPrivate) : HTag(NewtripletPrivate)
// {
//     Print(kInformation, "Constructor");
// }

fastjet::PseudoJet hanalysis::Triplet::singlet() const
{
//     return static_cast<TripletPrivate *>(TagPrivate.get())->Singlet;
    return singlet_;
}

hanalysis::Doublet hanalysis::Triplet::doublet() const
{
//     return dynamic_cast<TripletPrivate *>(TagPrivate.get())->doublet;
    return doublet_;
}

hanalysis::Triplet::Triplet(const hanalysis::Doublet &Newdoublet, const fastjet::PseudoJet &NewSinglet)
// : hanalysis::HTag(*new TripletPrivate)
{

    Print(kInformation, "Constructor");

//     static_cast<TripletPrivate *>(TagPrivate.get())->SetSinglet(NewSinglet);
//     static_cast<TripletPrivate *>(TagPrivate.get())->Setdoublet(Newdoublet);
    SetSinglet(NewSinglet);
    Setdoublet(Newdoublet);
//     if (NewSinglet.has_user_info<JetInfo>()) if (NewSinglet.user_info<JetInfo>().Bdt() != TagPrivate.get()->InitialValue) TagPrivate.get()->Bdt = (NewSinglet.user_info<JetInfo>().Bdt() + Newdoublet.Bdt()) / 2;
    if (NewSinglet.has_user_info<JetInfo>() && NewSinglet.user_info<JetInfo>().Bdt() != initial_value()) SetBdt(NewSinglet.user_info<JetInfo>().Bdt(),Newdoublet.Bdt());
    SetFlag(Newdoublet.Flag());
}

hanalysis::Triplet::Triplet(const fastjet::PseudoJet &NewSinglet)
// : hanalysis::HTag(*new TripletPrivate)
{

    Print(kInformation, "Constructor");

//     static_cast<TripletPrivate *>(TagPrivate.get())->SetSinglet(NewSinglet / 2);
//     static_cast<TripletPrivate *>(TagPrivate.get())->Setdoublet(Doublet(NewSinglet / 2));
//     if (NewSinglet.has_user_info<JetInfo>()) if (NewSinglet.user_info<JetInfo>().Bdt() != TagPrivate.get()->InitialValue) TagPrivate.get()->Bdt = NewSinglet.user_info<JetInfo>().Bdt();

    SetSinglet(NewSinglet / 2);
    Setdoublet(Doublet(NewSinglet / 2));
    SetDegenerate();
    if (NewSinglet.has_user_info<JetInfo>() && NewSinglet.user_info<JetInfo>().Bdt() != initial_value()) SetBdt(NewSinglet.user_info<JetInfo>().Bdt());
    else SetBdt(0);
}


// hanalysis::Doublet hanalysis::Triplet::doublet()const {
//   return triplet->doublet;
// }
//
// fastjet::PseudoJet hanalysis::Triplet::singlet()const {
//   return triplet->Singlet;
// }
