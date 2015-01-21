# include "HDoublet.hh"
# include "HTagPrivate.hh"

class hanalysis::HDoubletPrivate : public HTagPrivate {

public:

  HDoubletPrivate() {}

  void SetSinglet1(const fastjet::PseudoJet &NewSinglet);

  void SetSinglet2(const fastjet::PseudoJet &NewSinglet);

  std::vector< HKinematics > Constituents(const fastjet::PseudoJet& NewJet, const float JetRatio, const float Theta, const float Shift) const;

  float ReferenceAngle(const fastjet::PseudoJet& NewJet, const fastjet::PseudoJet& ReferenceJet) const;

  float Pull(const fastjet::PseudoJet &Jet) const;

  //   HDoublet(HDoubletPrivate &NewDoubletPrivate);

    fastjet::PseudoJet Singlet1;

    fastjet::PseudoJet Singlet2;

};

hanalysis::HDoublet::HDoublet() : hanalysis::HTag(*new HDoubletPrivate)
{
    Print(HInformation, "Constructor");
}


hanalysis::HDoublet::HDoublet(HDoubletPrivate& NewDoubletPrivate) : HTag(NewDoubletPrivate)
{
    Print(HInformation, "Constructor");
}

hanalysis::HDoublet::HDoublet(const fastjet::PseudoJet &NewSinglet1, const fastjet::PseudoJet &NewSinglet2) : hanalysis::HTag(* new HDoubletPrivate)
{
    Print(HInformation, "Constructor");
    SetSinglets(NewSinglet1,NewSinglet2);
}

hanalysis::HDoublet::HDoublet(const fastjet::PseudoJet &NewSinglet) : HTag(* new HDoubletPrivate)
{
    Print(HInformation, "Constructor");
    SetSinglets(NewSinglet);
}

hanalysis::HDoublet::~HDoublet()
{
    Print(HInformation, "Destructor");
//     delete Doublet;
}

fastjet::PseudoJet hanalysis::HDoublet::Singlet1()const {
    return static_cast<HDoubletPrivate *>(TagPrivate)->Singlet1;
}

fastjet::PseudoJet hanalysis::HDoublet::Singlet2()const {
    return static_cast<HDoubletPrivate *>(TagPrivate)->Singlet2;
}

// void Label::setText(const String &text) {
//   LabelPrivate *d = static_cast<LabelPrivate *>(d_ptr); // cast to our private type
//   d->text = text;
// }

void hanalysis::HDoubletPrivate::SetSinglet1(const fastjet::PseudoJet& NewSinglet) {
//     static_cast<HDoubletPrivate *>(TagPrivate)->
    Singlet1 = NewSinglet;
}

void hanalysis::HDoubletPrivate::SetSinglet2(const fastjet::PseudoJet& NewSinglet) {
//   static_cast<HDoubletPrivate *>(TagPrivate)->
  Singlet2 = NewSinglet;
}

void hanalysis::HDoublet::SetSinglets(const fastjet::PseudoJet& NewSinglet1, const fastjet::PseudoJet& NewSinglet2)
{
    Print(HInformation, "Constructor");
    static_cast<HDoubletPrivate *>(TagPrivate)->SetSinglet1(NewSinglet1);
    static_cast<HDoubletPrivate *>(TagPrivate)->SetSinglet2(NewSinglet2);
    int NumberBdt = 0;
    TagPrivate->Bdt = 0;
    if (Singlet1().has_user_info<HJetInfo>()) if (Singlet1().user_info<HJetInfo>().Bdt() != TagPrivate->InitialValue) {
            TagPrivate->Bdt += Singlet1().user_info<HJetInfo>().Bdt();
            ++NumberBdt;
        }
        if (Singlet2().has_user_info<HJetInfo>()) if (Singlet2().user_info<HJetInfo>().Bdt() != TagPrivate->InitialValue) {
          TagPrivate->Bdt += Singlet2().user_info<HJetInfo>().Bdt();
            ++NumberBdt;
        }
        if (NumberBdt != 0)TagPrivate->Bdt /= NumberBdt;
}

void hanalysis::HDoublet::SetSinglets(const fastjet::PseudoJet& NewSinglet1)
{
    Print(HInformation, "Constructor");
    static_cast<HDoubletPrivate *>(TagPrivate)->SetSinglet1(NewSinglet1/2);
    static_cast<HDoubletPrivate *>(TagPrivate)->SetSinglet2(NewSinglet1/2);
    if (Singlet1().has_user_info<HJetInfo>()) if (Singlet1().user_info<HJetInfo>().Bdt() != TagPrivate->InitialValue) TagPrivate->Bdt = Singlet1().user_info<HJetInfo>().Bdt();
}

float hanalysis::HDoubletPrivate::ReferenceAngle(const fastjet::PseudoJet &NewJet, const fastjet::PseudoJet &ReferenceJet) const
{

    Print(HInformation, "Get ReferenceAngle");

    const float Rap = NewJet.rap() - ReferenceJet.rap();
    const float Phi = NewJet.delta_phi_to(ReferenceJet);

    return std::atan2(-Phi, -Rap);

}


float hanalysis::HDoublet::PullAngle1() const
{

    Print(HInformation, "GetPullAngle1");

    const float NewPull = static_cast<HDoubletPrivate *>(TagPrivate)->Pull(Singlet1());
    const float NewReferenceAngle = static_cast<HDoubletPrivate *>(TagPrivate)->ReferenceAngle(Singlet1(), Singlet2());
    //     Print(HDebug, "Pull", Pull, ReferenceAngle, GetDeltaPhi(Pull, ReferenceAngle));

    //     if (std::abs(GetDeltaPhi(Pull, ReferenceAngle) > 3)) {
    //         Print(HError, "extrema", Pull, ReferenceAngle);
    //         Print(HError, "extrema", Jet1.rap(), Jet1.phi_std());
    //         Print(HError, "extrema", Jet2.rap(), Jet2.phi_std());
    //         Print(HError, " ");
    //     }

    return HObject::GetDeltaPhi(NewPull, NewReferenceAngle);

}

float hanalysis::HDoublet::PullAngle2() const
{

    Print(HInformation, "GetPullAngle2");

    const float NewPull = static_cast<HDoubletPrivate *>(TagPrivate)->Pull(Singlet2());
    const float NewReferenceAngle = static_cast<HDoubletPrivate *>(TagPrivate)->ReferenceAngle(Singlet2(), Singlet1());
    Print(HDebug, "Pull", NewPull, NewReferenceAngle, HObject::GetDeltaPhi(NewPull, NewReferenceAngle));

    return HObject::GetDeltaPhi(NewPull, NewReferenceAngle);

}


float hanalysis::HDoubletPrivate::Pull(const fastjet::PseudoJet &NewJet) const
{

    Print(HInformation, "GetPull");

    float Rap = 0;
    float Phi = 0;

    for (const auto & Constituent : NewJet.constituents()) {

        const float NewDeltaRap = Constituent.rap() - NewJet.rap();
        const float NewDeltaPhi = HObject::GetDeltaPhi(Constituent.phi_std(), NewJet.phi_std());
        const float NewDeltaR = std::sqrt(std::pow(NewDeltaRap, 2) + std::pow(NewDeltaPhi, 2));
        const float PullFactor = Constituent.pt() / NewJet.pt() * NewDeltaR;
        //         const float PullFactor = Constituent.pt() / CandidateJet.pt() * Constituent.delta_R(CandidateJet);

        Rap += (PullFactor * NewDeltaRap);
        Phi += (PullFactor * NewDeltaPhi);

    }

    return std::atan2(Phi, Rap);

}


std::vector<HKinematics> hanalysis::HDoublet::Constituents() const
{

    Print(HInformation, "GetConstituents");

    if (Singlet1().constituents().size() < 1 || Singlet2().constituents().size() < 1) {

        Print(HNotification, "Not enough Constituents", Singlet1().constituents().size(), Singlet2().constituents().size());
        //         return 0;

    }

    const float Shift = 1;

    const float CenterRap = (Singlet1().rap() + Singlet2().rap()) / 2;
    //     const float CenterPhi = (Jet1.phi_std() + Jet2.phi_std()) / 2;
    const float CenterPhi = HObject::GetDeltaPhi(Singlet1().phi_std(), -Singlet2().phi_std()) / 2;

    const float Theta = atan2(HObject::GetDeltaPhi(Singlet1().phi_std(), CenterPhi), Singlet1().rap() - CenterRap);

    const float Distance = Singlet1().delta_R(Singlet2());
    const float SubJetRatio = 2. * Shift / Distance;

    std::vector<HKinematics> ConstituentVectors1 = static_cast<HDoubletPrivate *>(TagPrivate)->Constituents(Singlet1(), SubJetRatio, Theta, -Shift);
    std::vector<HKinematics> ConstituentVectors2 = static_cast<HDoubletPrivate *>(TagPrivate)->Constituents(Singlet2(), SubJetRatio, -Theta, Shift);

    ConstituentVectors1.insert(ConstituentVectors1.end(), ConstituentVectors2.begin(), ConstituentVectors2.end());

    return ConstituentVectors1;

}


std::vector<HKinematics> hanalysis::HDoubletPrivate::Constituents(const fastjet::PseudoJet &NewJet, const float JetRatio, const float Theta, const float Shift) const
{

    Print(HInformation, "GetConstituents", JetRatio, Theta);

    const float Cut = 2. / JetRatio;
    const float Cut1 = 1. / JetRatio;

    std::vector<HKinematics> NewConstituents;

    for (const auto & ConstituentJet : NewJet.constituents()) {

        if (NewJet.delta_R(ConstituentJet) > Cut) continue;
        if (NewJet.delta_R(ConstituentJet) < Cut1) continue;

        // Get Constituent coordinates in Jet coordinates
        const float ConstRap = ConstituentJet.rap() - NewJet.rap();
        const float ConstPhi = HObject::GetDeltaPhi(ConstituentJet.phi_std(), NewJet.phi_std());

        if (ConstPhi > Cut) Print(HError, "phi", "too big");
        if (ConstRap > Cut) Print(HError, "eta", "too big");

        // rotate Constituent according to other jet
        float ObservableRap = ConstRap * cos(Theta) + ConstPhi * sin(Theta);
        float ObservablePhi = ConstRap * sin(Theta) - ConstPhi * cos(Theta);

        // Scale according to Jet distance
        ObservableRap *= JetRatio;
        ObservablePhi *= JetRatio;

        // move jet to (+-1,0)
        ObservableRap -= Shift;
        Print(HDebug, "eta", ObservableRap);

        HKinematics Constituent(ConstituentJet.pt(), ObservableRap, ObservablePhi);

        NewConstituents.push_back(Constituent);

    }

    return NewConstituents;

}




