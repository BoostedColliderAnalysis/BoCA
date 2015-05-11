# include "HDoublet.hh"
// # include "HTagPrivate.hh"

// class hanalysis::HDoubletPrivate : public HTagPrivate
// class hanalysis::HDoubletPrivate : public HObject
// {
//
// public:
//     void SetSinglet1(const fastjet::PseudoJet &NewSinglet);
//
//     void SetSinglet2(const fastjet::PseudoJet &NewSinglet);
//
//     std::vector< HKinematics > Constituents(const fastjet::PseudoJet &NewJet, const float JetRatio, const float Theta, const float Shift) const;
//
//     float ReferenceAngle(const fastjet::PseudoJet &NewJet, const fastjet::PseudoJet &ReferenceJet) const;
//
//     float Pull(const fastjet::PseudoJet &Jet) const;
//
//     fastjet::PseudoJet Singlet1;
//
//     fastjet::PseudoJet Singlet2;
//
// };

void hanalysis::HDoublet::SetSinglet1(const fastjet::PseudoJet &NewSinglet)
{
    singlet_ = NewSinglet;
}

void hanalysis::HDoublet::SetSinglet2(const fastjet::PseudoJet &NewSinglet)
{
    Singlet2M = NewSinglet;
}

std::vector<HKinematics> hanalysis::HDoublet::Constituents(const fastjet::PseudoJet &NewJet, const float JetRatio, const float Theta, const float Shift) const
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

        NewConstituents.emplace_back(Constituent);

    }

    return NewConstituents;

}

// hanalysis::HDoublet::HDoublet() : hanalysis::HTag(*new HDoubletPrivate)
// hanalysis::HDoublet::HDoublet() : DoubletPrivate(new HDoubletPrivate)
hanalysis::HDoublet::HDoublet()
{
    Print(HInformation, "Constructor");
}

// hanalysis::HDoublet::HDoublet(HDoubletPrivate &NewDoubletPrivate) : HTag(NewDoubletPrivate)
// hanalysis::HDoublet::HDoublet(HDoubletPrivate &NewDoubletPrivate) : DoubletPrivate(&NewDoubletPrivate)
// {
//     Print(HInformation, "Constructor");
// }

// hanalysis::HDoublet::HDoublet(const HDoublet &NewDoublet) : DoubletPrivate(new HDoubletPrivate(*NewDoublet.DoubletPrivate)) {}

// hanalysis::HDoublet::HDoublet(HDoublet && NewDoublet) : DoubletPrivate(std::move(NewDoublet.DoubletPrivate)) {}

// hanalysis::HDoublet &hanalysis::HDoublet::operator=(HDoublet NewDoublet) //note: pass by value and let compiler do the magics
// {
//   DoubletPrivate = std::move(NewDoublet.DoubletPrivate); //a now nullifyed, but that's ok, it's just a value
//   return *this;
// }

// hanalysis::HDoublet::HDoublet(const fastjet::PseudoJet &NewSinglet1, const fastjet::PseudoJet &NewSinglet2) : hanalysis::HTag(* new HDoubletPrivate)
hanalysis::HDoublet::HDoublet(const fastjet::PseudoJet &NewSinglet1, const fastjet::PseudoJet &NewSinglet2)
// : DoubletPrivate(new HDoubletPrivate)
{
    Print(HInformation, "Constructor");
    SetSinglets(NewSinglet1, NewSinglet2);
}

// hanalysis::HDoublet::HDoublet(const fastjet::PseudoJet &NewSinglet) : HTag(* new HDoubletPrivate)
hanalysis::HDoublet::HDoublet(const fastjet::PseudoJet &NewSinglet)
// : DoubletPrivate(new HDoubletPrivate)
{
    Print(HInformation, "Constructor");
    SetSinglets(NewSinglet);
}

hanalysis::HDoublet::~HDoublet()
{
//     Print(HError, "Destructor");
}

fastjet::PseudoJet hanalysis::HDoublet::Singlet1()const
{
//   Print(HError, "Singlet1");
//     return static_cast<HDoubletPrivate *>(TagPrivate)->Singlet1;
//     return DoubletPrivate->Singlet1;
    return singlet_;
}

fastjet::PseudoJet hanalysis::HDoublet::Singlet2()const
{
//   Print(HError, "Singlet2");
//   return dynamic_cast<HDoubletPrivate *>(TagPrivate.get())->Singlet2;
//   return DoubletPrivate->Singlet2;
    return Singlet2M;

}

void hanalysis::HDoublet::SetSinglets(const fastjet::PseudoJet &NewSinglet1, const fastjet::PseudoJet &NewSinglet2)
{
    Print(HInformation, "Constructor");
//     static_cast<HDoubletPrivate *>(TagPrivate.get())->SetSinglet1(NewSinglet1);
//     static_cast<HDoubletPrivate *>(TagPrivate.get())->SetSinglet2(NewSinglet2);
    SetSinglet1(NewSinglet1);
    SetSinglet2(NewSinglet2);


    if (Singlet1().has_user_info<HJetInfo>() && Singlet2().has_user_info<HJetInfo>()) SetBdt(Singlet1().user_info<HJetInfo>().Bdt(),Singlet2().user_info<HJetInfo>().Bdt());
    else if (Singlet1().has_user_info<HJetInfo>()) SetBdt(Singlet1().user_info<HJetInfo>().Bdt());
    else if (Singlet2().has_user_info<HJetInfo>()) SetBdt(Singlet2().user_info<HJetInfo>().Bdt());

//     int NumberBdt = 0;
//     SetBdt(0);
//     if (Singlet1().has_user_info<HJetInfo>() && Singlet1().user_info<HJetInfo>().Bdt() != InitialValue) {
//         BdtM += Singlet1().user_info<HJetInfo>().Bdt();
//         ++NumberBdt;
//     }
//     if (Singlet2().has_user_info<HJetInfo>() && Singlet2().user_info<HJetInfo>().Bdt() != InitialValue) {
//         BdtM += Singlet2().user_info<HJetInfo>().Bdt();
//         ++NumberBdt;
//     }
//     if (NumberBdt != 0)BdtM /= NumberBdt;









}

void hanalysis::HDoublet::SetSinglets(const fastjet::PseudoJet &NewSinglet1)
{
    Print(HInformation, "Constructor");
//     static_cast<HDoubletPrivate *>(TagPrivate.get())->SetSinglet1(NewSinglet1 / 2);
//     static_cast<HDoubletPrivate *>(TagPrivate.get())->SetSinglet2(NewSinglet1 / 2);
    SetSinglet1(NewSinglet1 / 2);
    SetSinglet2(NewSinglet1 / 2);
    SetDegenerate();
    if (NewSinglet1.has_user_info<HJetInfo>()) if (NewSinglet1.user_info<HJetInfo>().Bdt() != initial_value()) SetBdt(NewSinglet1.user_info<HJetInfo>().Bdt());
    else SetBdt(0);
    if (NewSinglet1.has_user_info<HJetInfo>()) if (NewSinglet1.user_info<HJetInfo>().Tag() != initial_value()) SetTag(NewSinglet1.user_info<HJetInfo>().Tag());
}

float hanalysis::HDoublet::ReferenceAngle(const fastjet::PseudoJet &NewJet, const fastjet::PseudoJet &ReferenceJet) const
{

    Print(HInformation, "Get ReferenceAngle");

    const float Rap = NewJet.rap() - ReferenceJet.rap();
    const float Phi = NewJet.delta_phi_to(ReferenceJet);

    return std::atan2(-Phi, -Rap);

}


float hanalysis::HDoublet::PullAngle1() const
{

    Print(HInformation, "GetPullAngle1");

//     const float NewPull = static_cast<HDoubletPrivate *>(TagPrivate.get())->Pull(Singlet1());
    const float NewPull = Pull(Singlet1());
//     const float NewReferenceAngle = static_cast<HDoubletPrivate *>(TagPrivate.get())->ReferenceAngle(Singlet1(), Singlet2());
    const float NewReferenceAngle = ReferenceAngle(Singlet1(), Singlet2());
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

//     const float NewPull = static_cast<HDoubletPrivate *>(TagPrivate.get())->Pull(Singlet2());
    const float NewPull = Pull(Singlet2());
//     const float NewReferenceAngle = static_cast<HDoubletPrivate *>(TagPrivate.get())->ReferenceAngle(Singlet2(), Singlet1());
    const float NewReferenceAngle = ReferenceAngle(Singlet2(), Singlet1());
    Print(HDebug, "Pull", NewPull, NewReferenceAngle, HObject::GetDeltaPhi(NewPull, NewReferenceAngle));

    return HObject::GetDeltaPhi(NewPull, NewReferenceAngle);

}


float hanalysis::HDoublet::Pull(const fastjet::PseudoJet &NewJet) const
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

    if (Singlet1().constituents().empty() || Singlet2().constituents().empty()) {

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

//     std::vector<HKinematics> ConstituentVectors1 = static_cast<HDoubletPrivate *>(TagPrivate.get())->Constituents(Singlet1(), SubJetRatio, Theta, -Shift);
    std::vector<HKinematics> ConstituentVectors1 = Constituents(Singlet1(), SubJetRatio, Theta, -Shift);
//     std::vector<HKinematics> ConstituentVectors2 = static_cast<HDoubletPrivate *>(TagPrivate.get())->Constituents(Singlet2(), SubJetRatio, -Theta, Shift);
    std::vector<HKinematics> ConstituentVectors2 = Constituents(Singlet2(), SubJetRatio, -Theta, Shift);

    ConstituentVectors1.insert(ConstituentVectors1.end(), ConstituentVectors2.begin(), ConstituentVectors2.end());

    return ConstituentVectors1;

}






