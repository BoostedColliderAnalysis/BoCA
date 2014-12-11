# include "HDoublet.hh"

hanalysis::HDoublet::HDoublet()
{
    Print(HInformation, "Constructor");
}

hanalysis::HDoublet::HDoublet(const fastjet::PseudoJet &NewJet1, const fastjet::PseudoJet &NewJet2)
{
    Print(HInformation, "Constructor");
    Jet1 = NewJet1;
    Jet2 = NewJet2;
    Bdt =1;
    if(Jet1.has_user_info<HJetInfo>()) if(Jet1.user_info<HJetInfo>().GetBdt() != InitialValue) Bdt *= Jet1.user_info<HJetInfo>().GetBdt();
    if(Jet2.has_user_info<HJetInfo>()) if(Jet2.user_info<HJetInfo>().GetBdt() != InitialValue) Bdt *= Jet2.user_info<HJetInfo>().GetBdt();
}

// // hanalysis::HDoublet::HDoublet(const fastjet::PseudoJet &Jet, const fastjet::PseudoJet &Lepton)
// {
//     Print(HInformation, "Constructor");
//     Jet1 = Jet;
//     Jet2 = Lepton;
//     Bdt = Jet1.user_info<HJetInfo>().GetBdt();
// }

hanalysis::HDoublet::~HDoublet()
{
    Print(HInformation, "Destructor");
}


float hanalysis::HDoublet::GetReferenceAngle(const fastjet::PseudoJet &Jet, const fastjet::PseudoJet &ReferenceJet) const
{

  Print(HInformation, "Get ReferenceAngle");

  const float Rap = Jet.rap() - ReferenceJet.rap();
  const float Phi = Jet.delta_phi_to(ReferenceJet);

  return (std::atan2(-Phi, -Rap));

}


float hanalysis::HDoublet::GetPullAngle1() const
{

  Print(HInformation, "GetPullAngle1");

  const float Pull = GetPull(Jet1);
  const float ReferenceAngle = GetReferenceAngle(Jet1, Jet2);
  //     Print(HDebug, "Pull", Pull, ReferenceAngle, GetDeltaPhi(Pull, ReferenceAngle));

  //     if (std::abs(GetDeltaPhi(Pull, ReferenceAngle) > 3)) {
  //         Print(HError, "extrema", Pull, ReferenceAngle);
  //         Print(HError, "extrema", Jet1.rap(), Jet1.phi_std());
  //         Print(HError, "extrema", Jet2.rap(), Jet2.phi_std());
  //         Print(HError, " ");
  //     }

  return GetDeltaPhi(Pull, ReferenceAngle);

}

float hanalysis::HDoublet::GetPullAngle2() const
{

  Print(HInformation, "GetPullAngle2");

  const float Pull = GetPull(Jet2);
  const float ReferenceAngle = GetReferenceAngle(Jet2, Jet1);
  Print(HDebug, "Pull", Pull, ReferenceAngle, GetDeltaPhi(Pull, ReferenceAngle));

  return GetDeltaPhi(Pull, ReferenceAngle);

}


float hanalysis::HDoublet::GetPull(const fastjet::PseudoJet &CandidateJet) const
{

  Print(HInformation, "GetPull");

  float Rap = 0;
  float Phi = 0;

  for (const auto & Constituent : CandidateJet.constituents()) {

    const float DeltaY = Constituent.rap() - CandidateJet.rap();
    const float DeltaPhi = GetDeltaPhi(Constituent.phi_std(), CandidateJet.phi_std());
    const float DeltaR = std::sqrt(std::pow(DeltaY, 2) + std::pow(DeltaPhi, 2));
    const float PullFactor = Constituent.pt() / CandidateJet.pt() * DeltaR;
    //         const float PullFactor = Constituent.pt() / CandidateJet.pt() * Constituent.delta_R(CandidateJet);

    Rap += (PullFactor * DeltaY);
    Phi += (PullFactor * DeltaPhi);

  }

  return std::atan2(Phi, Rap);

}


std::vector<HKinematics> hanalysis::HDoublet::GetConstituents() const
{

  Print(HInformation, "GetConstituents");

  if (Jet1.constituents().size() < 1 || Jet2.constituents().size() < 1) {

    Print(HNotification, "Not enough Constituents", Jet1.constituents().size(), Jet2.constituents().size());
    //         return 0;

  }

  const float Shift = 1;

  const float CenterRap = (Jet1.rap() + Jet2.rap()) / 2;
  //     const float CenterPhi = (Jet1.phi_std() + Jet2.phi_std()) / 2;
  const float CenterPhi = GetDeltaPhi(Jet1.phi_std(), -Jet2.phi_std()) / 2;

  const float Theta = atan2(GetDeltaPhi(Jet1.phi_std(), CenterPhi), Jet1.rap() - CenterRap);

  const float Distance = Jet1.delta_R(Jet2);
  const float SubJetRatio = 2. * Shift / Distance;

  std::vector<HKinematics> ConstituentVectors1 = GetConstituents(Jet1, SubJetRatio, Theta, -Shift);
  std::vector<HKinematics> ConstituentVectors2 = GetConstituents(Jet2, SubJetRatio, -Theta, Shift);

  ConstituentVectors1.insert(ConstituentVectors1.end(), ConstituentVectors2.begin(), ConstituentVectors2.end());

  return ConstituentVectors1;

}


std::vector<HKinematics> hanalysis::HDoublet::GetConstituents(const fastjet::PseudoJet &Jet, const float JetRatio, const float Theta, const float Shift) const
{

  Print(HInformation, "GetConstituents", JetRatio, Theta);

  const float Cut = 2. / JetRatio;
  const float Cut1 = 1. / JetRatio;

  std::vector<HKinematics> ConstituentVectors;

  for (const auto & ConstituentJet : Jet.constituents()) {

    if (Jet.delta_R(ConstituentJet) > Cut) continue;
    if (Jet.delta_R(ConstituentJet) < Cut1) continue;

    // Get Constituent coordinates in Jet coordinates
    const float ConstRap = ConstituentJet.rap() - Jet.rap();
    const float ConstPhi = GetDeltaPhi(ConstituentJet.phi_std(), Jet.phi_std());

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

    ConstituentVectors.push_back(Constituent);

  }

  return ConstituentVectors;

}




