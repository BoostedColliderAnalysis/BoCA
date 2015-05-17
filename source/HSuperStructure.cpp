// # include "HSuperStructure.hh"
//
// analysis::HSuperStructure::HSuperStructure()
// {
//     Print(kInformation, "Constructor");
//
// //     Position1 = EmptyPosition;
// //     Position2 = EmptyPosition;
//
// }
//
// analysis::HSuperStructure::HSuperStructure(const fastjet::PseudoJet &NewJet1, const fastjet::PseudoJet &NewJet2)
// {
//
//     Print(kInformation, "Constructor");
//
//     Jet1 = NewJet1;
//     Jet2 = NewJet2;
//
// //     Position1 = EmptyPosition;
// //     Position2 = EmptyPosition;
//
// }
//
// analysis::HSuperStructure::~HSuperStructure()
// {
//
//     Print(kInformation, "Destructor");
//
// }
//
// float analysis::HSuperStructure::GetReferenceAngle(const fastjet::PseudoJet &Jet, const fastjet::PseudoJet &ReferenceJet) const
// {
//
//     Print(kInformation, "Get ReferenceAngle");
//
//     const float Rap = Jet.rap() - ReferenceJet.rap();
//     const float Phi = Jet.delta_phi_to(ReferenceJet);
//
//     return (std::atan2(-Phi, -Rap));
//
// }
//
//
// float analysis::HSuperStructure::GetPullAngle1() const
// {
//
//     Print(kInformation, "GetPullAngle1");
//
//     const float Pull = GetPull(Jet1);
//     const float ReferenceAngle = GetReferenceAngle(Jet1, Jet2);
// //     Print(kDebug, "Pull", Pull, ReferenceAngle, GetDeltaPhi(Pull, ReferenceAngle));
//
// //     if (std::abs(GetDeltaPhi(Pull, ReferenceAngle) > 3)) {
// //         Print(kError, "extrema", Pull, ReferenceAngle);
// //         Print(kError, "extrema", Jet1.rap(), Jet1.phi_std());
// //         Print(kError, "extrema", Jet2.rap(), Jet2.phi_std());
// //         Print(kError, " ");
// //     }
//
//     return GetDeltaPhi(Pull, ReferenceAngle);
//
// }
//
// float analysis::HSuperStructure::GetPullAngle2() const
// {
//
//     Print(kInformation, "GetPullAngle2");
//
//     const float Pull = GetPull(Jet2);
//     const float ReferenceAngle = GetReferenceAngle(Jet2, Jet1);
//     Print(kDebug, "Pull", Pull, ReferenceAngle, GetDeltaPhi(Pull, ReferenceAngle));
//
//     return GetDeltaPhi(Pull, ReferenceAngle);
//
// }
//
//
// float analysis::HSuperStructure::GetPull(const fastjet::PseudoJet &CandidateJet) const
// {
//
//     Print(kInformation, "GetPull");
//
//     float Rap = 0;
//     float Phi = 0;
//
//     for (const auto & constituent : CandidateJet.constituents()) {
//
//         const float DeltaY = constituent.rap() - CandidateJet.rap();
//         const float DeltaPhi = GetDeltaPhi(constituent.phi_std(), CandidateJet.phi_std());
//         const float DeltaR = std::sqrt(std::pow(DeltaY, 2) + std::pow(DeltaPhi, 2));
//         const float PullFactor = constituent.pt() / CandidateJet.pt() * DeltaR;
// //         const float PullFactor = constituent.pt() / CandidateJet.pt() * constituent.delta_R(CandidateJet);
//
//         Rap += (PullFactor * DeltaY);
//         Phi += (PullFactor * DeltaPhi);
//
//     }
//
//     return std::atan2(Phi, Rap);
//
// }
//
//
// std::vector<Kinematics> analysis::HSuperStructure::Getconstituents() const
// {
//
//     Print(kInformation, "Getconstituents");
//
//     if (Jet1.constituents().empty() || Jet2.constituents().empty()) {
//
//         Print(kNotification, "Not enough constituents", Jet1.constituents().size(), Jet2.constituents().size());
// //         return 0;
//
//     }
//
//     const float Shift = 1;
//
//     const float CenterRap = (Jet1.rap() + Jet2.rap()) / 2;
// //     const float CenterPhi = (Jet1.phi_std() + Jet2.phi_std()) / 2;
//     const float CenterPhi = GetDeltaPhi(Jet1.phi_std(), -Jet2.phi_std()) / 2;
//
//     const float Theta = atan2(GetDeltaPhi(Jet1.phi_std(), CenterPhi), Jet1.rap() - CenterRap);
//
//     const float Distance = Jet1.delta_R(Jet2);
//     const float SubJetRatio = 2. * Shift / Distance;
//
//     std::vector<Kinematics> constituentVectors1 = Getconstituents(Jet1, SubJetRatio, Theta, -Shift);
//     std::vector<Kinematics> constituentVectors2 = Getconstituents(Jet2, SubJetRatio, -Theta, Shift);
//
//     constituentVectors1.insert(constituentVectors1.end(), constituentVectors2.begin(), constituentVectors2.end());
//
//     return constituentVectors1;
//
// }
//
//
// std::vector<Kinematics> analysis::HSuperStructure::Getconstituents(const fastjet::PseudoJet &Jet, const float JetRatio, const float Theta, const float Shift) const
// {
//
//     Print(kInformation, "Getconstituents", JetRatio, Theta);
//
//     const float Cut = 2. / JetRatio;
//     const float Cut1 = 1. / JetRatio;
//
//     std::vector<Kinematics> constituentVectors;
//
//     for (const auto & constituentJet : Jet.constituents()) {
//
//         if (Jet.delta_R(constituentJet) > Cut) continue;
//         if (Jet.delta_R(constituentJet) < Cut1) continue;
//
//         // Get constituent coordinates in Jet coordinates
//         const float ConstRap = constituentJet.rap() - Jet.rap();
//         const float ConstPhi = GetDeltaPhi(constituentJet.phi_std(), Jet.phi_std());
//
//         if (ConstPhi > Cut) Print(kError, "phi", "too big");
//         if (ConstRap > Cut) Print(kError, "eta", "too big");
//
//         // rotate constituent according to other jet
//         float ObservableRap = ConstRap * cos(Theta) + ConstPhi * sin(Theta);
//         float ObservablePhi = ConstRap * sin(Theta) - ConstPhi * cos(Theta);
//
//         // Scale according to Jet distance
//         ObservableRap *= JetRatio;
//         ObservablePhi *= JetRatio;
//
//         // move jet to (+-1,0)
//         ObservableRap -= Shift;
//         Print(kDebug, "eta", ObservableRap);
//
//         Kinematics constituent(constituentJet.pt(), ObservableRap, ObservablePhi);
//
//         constituentVectors.emplace_back(constituent);
//
//     }
//
//     return constituentVectors;
//
// }
//
//
//
//
//
//
//
//
//
//
//
//
//
//
// //
// // hdelphes::HPull::HPull()
// // {
// //     Print(kInformation, "Constructor");
// //
// //     InitialValue = -1000;
// //     PullPhi = 0;
// //     PullRap = 0;
// // //     DiPolarity = 0;
// //
// // }
// //
// // hdelphes::HPull::~HPull()
// // {
// //
// //     Print(kInformation, "Destructor");
// //
// // }
// //
// //
// // void hdelphes::HPull::BTagCalculation(const Jet& JetClone)
// // {
// //
// //     Print(kInformation, "BTagCalculation");
// //
// //     fastjet::PseudoJet CandidateJet = GetPseudoJet(const_cast<Jet*>(&JetClone)->P4());
// //
// // //     if (Jet.pt() > 0) {
// //
// //         int ValidconstituentsSum = 0;
// //         int constituentsSum = JetClone.constituents.GetEntriesFast();
// //         Print(kInformation, "Number of b Jet constituents", constituentsSum);
// //
// //
// //         for (int constituentsNumber = 0; constituentsNumber < constituentsSum; ++constituentsNumber) {
// //
// //             const TObject * const constituentObject = JetClone.constituents.At(constituentsNumber);
// //             if (constituentObject == 0) continue;
// //             Print(kDebug, "Entering b Jet constituent", constituentsNumber);
// //             ValidconstituentsSum++;
// //
// //             const fastjet::PseudoJet constituentJet = GetconstituentJet(constituentObject);
// //
// //             const float PullFactor = constituentJet.pt() * constituentJet.delta_R(CandidateJet) / CandidateJet.pt();
// //             PullRap += PullFactor * constituentJet.rap();
// //             PullPhi += PullFactor * constituentJet.phi_std();
// //
// //         }
// //
// //         if (ValidconstituentsSum != constituentsSum) Print(kDebug, "Number of valid Jet constituents", ValidconstituentsSum);
// //         Print(kInformation, "PullPhi", PullPhi);
// //         Print(kInformation, "PullY", PullRap);
// //
// // //     }
// //
// // }
// //
// // float hdelphes::HPull::PullAngle(float Rap, float Phi)
// // {
// //
// //     Print(kInformation, "Pull Angle");
// //
// //     float Theta = InitialValue;
// //     if (Rap != 0) {
// //         Theta = atan(Phi / Rap);
// //     }
// //
// //     if (Rap < 0) {
// //         if (Phi > 0) {
// //             Theta += Pi();
// //         }
// //         if (Phi < 0) {
// //             Theta -= Pi();
// //         }
// //     }
// //
// //     if (fabs(Theta) > Pi()  && Theta !=  InitialValue) {
// //         Print(kError, "Error in Theta Calculation");
// //     }
// //
// //     return (Theta);
// //
// // }
// //
// //
// // float hdelphes::HPull::ConfineAngle(float Angle)
// // {
// //
// //     Print(kInformation, "Confine Angle");
// //
// //     if (Angle > Pi()) {
// //         Angle -= 2 * Pi();
// //     }
// //     if (Angle < -Pi()) {
// //         Angle += 2 * Pi();
// //     }
// //     if (fabs(Angle) > Pi()) {
// //         Print(kError, "Error in Angle Confinment", Angle);
// //     }
// //
// //     return (Angle);
// //
// // }
// //
// //
// // float hdelphes::HPull::SubPull(const fastjet::PseudoJet& SubJet, const fastjet::PseudoJet& RefJet, const fastjet::PseudoJet& CandidateJet)
// // {
// //
// //     Print(kInformation, "Sub Pull");
// //
// //     Print(kDetailed, "Mass", CandidateJet.m());
// //
// //     float SubJetPt = SubJet.pt();
// //
// //     float SubJetPhi = SubJet.phi_std();
// //     float SubJetRap = SubJet.rap();
// //
// //     float RefJetPhi = RefJet.phi_std();
// //     float RefJetRap = RefJet.rap();
// //
// //     float DeltaRSubJetRefJet = RefJet.delta_R(SubJet);
// //     float DeltaPhi = ConfineAngle(RefJetPhi - SubJetPhi);
// //     Print(kInformation, "DeltaPhi", DeltaPhi);
// //
// //     float DeltaRap = RefJetRap - SubJetRap;
// //     Print(kInformation, "DeltaRap", DeltaRap);
// //
// //     float RefTheta = PullAngle(DeltaRap, DeltaPhi);
// //     Print(kInformation, "RefTheta", RefTheta);
// //
// //     float SubPullRap = 0;
// //     float SubPullPhi = 0;
// //     int Validconstituents = 0;
// //
// //     Jets ConstVector = CandidateJet.constituents();
// // //     Jets ConstVector = SubJet.constituents();
// //     int ConstSum = ConstVector.size();
// //     Print(kInformation, "Number of constituents", ConstSum);
// //
// //     for (int ConstNumber = 0; ConstNumber < ConstSum; ConstNumber++) {
// //
// //         fastjet::PseudoJet ConstJet = ConstVector[ConstNumber];
// //
// //         float DeltaRConstSubJet = ConstJet.delta_R(SubJet);
// //         float DeltaRConstRefJet = ConstJet.delta_R(RefJet);
// // //         if (DeltaRConstRefJet > DeltaRSubJetRefJet / 2 /*/ sqrt(2)*/ && DeltaRConstSubJet < DeltaRSubJetRefJet / sqrt(2) /*/ 2*/) {
// // //         if (DeltaRConstSubJet < DeltaRSubJetRefJet /*/ sqrt(2)*/ /2) {
// //
// //         if (
// //             DeltaRConstRefJet > DeltaRSubJetRefJet / 2 /*/ sqrt(2)*/  &&
// //             pow(DeltaRConstSubJet, 2) + pow(DeltaRConstRefJet, 2) < 2 * pow(DeltaRSubJetRefJet, 2)
// //             &&
// //             DeltaRConstSubJet < DeltaRSubJetRefJet /*/ sqrt(2)*/
// //         ) {
// //
// //             float ConstPhi = ConstJet.phi_std();
// //             float DeltaPhiConstSubJet = ConfineAngle(ConstPhi - SubJetPhi);
// //
// //             float ConstRap = ConstJet.rap();
// //             float DeltaRapConstSubJet = ConstRap - SubJetRap;
// //
// //             float DeltaRConstSubJetCalc = sqrt(pow(DeltaPhiConstSubJet, 2) + pow(DeltaRapConstSubJet, 2));
// //             float ConstPt = ConstJet.pt();
// //             float PullFactor = ConstPt / SubJetPt * DeltaRConstSubJetCalc;
// //
// //             SubPullRap += PullFactor * DeltaRapConstSubJet;
// //             SubPullPhi += PullFactor * DeltaPhiConstSubJet;
// //
// //             ++Validconstituents;
// //
// //         }
// //
// //     }
// //     Print(kInformation, "Number of Valid constituents", Validconstituents);
// //     Print(kInformation, "SubPullRap", SubPullRap);
// //     Print(kInformation, "SubPullPhi", SubPullPhi);
// //
// //     float PullTheta = PullAngle(SubPullRap, SubPullPhi);
// //     Print(kInformation, "PullTheta", PullTheta);
// //
// //     float Result = InitialValue;
// //     if (Validconstituents > ConstSum / 5) {
// //
// //         if (PullTheta != InitialValue && RefTheta != InitialValue) {
// //             Result = ConfineAngle(PullTheta - RefTheta);
// //         }
// //
// //         if (fabs(Result) > Pi() && Result != InitialValue) {
// //             Print(kError, "Error in Result Calculation");
// //         }
// //
// //     }
// //
// //     Print(kInformation, "Result", Result);
// //
// //     return (Result);
// //
// // }
// //
// //
// //
// // float hdelphes::HPull::CalculateDiPolarity(const fastjet::PseudoJet& FatJet, const fastjet::PseudoJet& FatJetPiece1, const fastjet::PseudoJet& FatJetPiece2)
// // {
// //
// //     Print(kInformation, "Calculate DiPolarity");
// //
// //     // Filtering
// // //     fastjet::PseudoJet Parent1 = MassDropJet.pieces()[0];
// // //     fastjet::PseudoJet Parent2 = MassDropJet.pieces()[1];
// // //     float ParentCylinderDistance = Parent1.delta_R(Parent2);
// // //     // MinimalCylinderDistance = Jing: 0.35; fastjet: 0.3; paper: 0.3; somewhat arbitrary choice
// // //     float MinimalCylinderDistance = .3;
// // //     float FilterCylinderDistance = min(ParentCylinderDistance / 2, MinimalCylinderDistance);
// // //     JetDefinition MassDropJetDefinition(cambridge_algorithm, FilterCylinderDistance);
// // //
// // //     // number of pieces we'll take in the filtering = Jing: 3; fastjet: 3
// // //     int NumberHardestPieces = 2;
// // //     Selector ThreeHardest = SelectorNHardest(NumberHardestPieces);
// // //     Filter FatJetFilter(MassDropJetDefinition, ThreeHardest);
// // //     fastjet::PseudoJet FatJet = FatJetFilter(MassDropJet);
// // //
// // //
// // //
// //
// //
// //
// //     float FatJetPt = FatJet.pt();
// //     Print(kInformation, "FatJet Pt", FatJetPt);
// //
// //     Jets FatJetPieceVector = FatJet.pieces();
// //     int PieceSum = FatJetPieceVector.size();
// //     if (PieceSum != 2) Print(kError, "Number of Fat Jet Pieces", PieceSum);
// // //     fastjet::PseudoJet FatJetPiece1 = FatJetPieceVector[0];
// // //     fastjet::PseudoJet FatJetPiece2 = FatJetPieceVector[1];
// //
// //     float Piece1Rap = FatJetPiece1.rap();
// //     float Piece1Phi = FatJetPiece1.phi();
// //     float Piece2Rap = FatJetPiece2.rap();
// //     float Piece2Phi = FatJetPiece2.phi();
// //
// //     float DeltaRap = Piece2Rap - Piece1Rap;
// //     float DeltaPhi = Piece2Phi - Piece1Phi;
// //
// //     float PieceDistanceSqr = DeltaRap * DeltaRap + DeltaPhi * DeltaPhi;
// //     Print(kInformation, "Piece Distance sqr", PieceDistanceSqr);
// //     float DiPolaritySum = 0;
// //     float constituentPtSum = 0;
// //     float constituentRSqrSum = 0;
// //     float constituentNumSqrSum = 0;
// //     int Validconstituents = 0;
// //
// //     float DiPolarity;
// //
// //     if (PieceDistanceSqr < 100000000) {
// //
// //
// //         Jets constituentsVector = FatJet.constituents();
// //         int constituentsSum = constituentsVector.size();
// //         Print(kInformation, "Number of Fat Jet constituents", constituentsSum);
// //
// //         for (int constituentsNumber = 0; constituentsNumber < constituentsSum; constituentsNumber++) {
// //
// //             Print(kDebug, "Entering Fat Jet constituent", constituentsNumber);
// //             fastjet::PseudoJet constituentJet = constituentsVector[constituentsNumber];
// //
// //             float constituentPhi = constituentJet.phi();
// //             Print(kDebug, "constituent Phi", constituentPhi);
// //
// //             float constituentRap = constituentJet.rap();
// //             Print(kDebug, "constituent Rap", constituentRap);
// //
// //             float constituentDeltaRap = Piece1Rap - constituentRap;
// //             float constituentDeltaPhi = Piece1Phi - constituentPhi;
// //
// //             float DeltaRap1Sqr = pow(constituentDeltaRap, 2);
// //             float DeltaPhi1Sqr = pow(constituentDeltaPhi, 2);
// //             float DeltaRap2Sqr = pow(Piece2Rap - constituentRap, 2);
// //             float DeltaPhi2Sqr = pow(Piece2Phi - constituentPhi, 2);
// //             float constituentDistance1Sqr = DeltaRap1Sqr + DeltaPhi1Sqr;
// //             float constituentDistance2Sqr = DeltaRap2Sqr + DeltaPhi2Sqr;
// //
// //             if (constituentDistance1Sqr > (PieceDistanceSqr / 2) && constituentDistance2Sqr > (PieceDistanceSqr / 2)) {
// //
// //                 Print(kDebug, "out of cones");
// //                 continue;
// //
// //             }
// //             Validconstituents++;
// //
// //             float constituentPt = constituentJet.pt();
// //             Print(kDebug, "constituent Pt", constituentPt);
// //
// //             float constituentNumSqr = pow(DeltaRap * constituentDeltaPhi - DeltaPhi * constituentDeltaRap, 2);
// //
// //             Print(kDebug, "constituentNumSqr", constituentNumSqr);
// //             float constituentRSqr = constituentNumSqr / PieceDistanceSqr;
// //
// //             DiPolaritySum += constituentRSqr * constituentPt / FatJetPt ;
// //             Print(kDebug, "DiPolarity Sum", DiPolaritySum);
// //
// //             constituentPtSum += constituentPt;
// //
// //             constituentRSqrSum += constituentRSqr;
// //
// //             constituentNumSqrSum += constituentNumSqr;
// //
// //         }
// //
// //         Print(kDebug, "Fraction of valid Constitueants", 1 - (constituentsSum - Validconstituents) / constituentsSum);
// //
// //         DiPolarity = DiPolaritySum / PieceDistanceSqr;
// //
// //     }
// //
// //     if (DiPolarity < 0.01 && DiPolarity > 0) {
// //
// //         Print(kInformation, "Pt Ratio", constituentPtSum / FatJetPt);
// //         Print(kInformation, "RSqr Ratio", constituentRSqrSum / PieceDistanceSqr);
// //         Print(kInformation, "PieceDistanceSqr", PieceDistanceSqr);
// //         Print(kInformation, "constituentNumSqrSum", constituentNumSqrSum);
// //         Print(kInformation, "DiPolaritySum", DiPolaritySum);
// //         Print(kInformation, "DiPolarity", DiPolarity);
// //
// //     }
// //
// //     return DiPolarity;
// //
// // }
// //
// //
// //
// // float hdelphes::HPull::JingDipolarity(const fastjet::PseudoJet &CandidateJet)
// // {
// //
// //     Print(kInformation, "Jing Dipolarity");
// //
// //     Jets SubJetVector = CandidateJet.pieces();
// //     if (SubJetVector.size() != 2) Print(kError, "not two subjets");
// //
// //     // Filtering
// //     float ParentCylinderDistance = SubJetVector[0].delta_R(SubJetVector[1]);
// //     // MinimalCylinderDistance = Jing: 0.35; fastjet: 0.3; paper: 0.3; somewhat arbitrary choice
// //     float MinimalCylinderDistance = 0.35;
// //     float FilterCylinderDistance = min(ParentCylinderDistance / 2, MinimalCylinderDistance);
// //     JetDefinition MassDropJetDefinition(antikt_algorithm, FilterCylinderDistance);
// //
// //     // number of pieces we'll take in the filtering = Jing: 3; fastjet: 3
// //     int NumberHardestPieces = 3;
// //     Selector ThreeHardest = SelectorNHardest(NumberHardestPieces);
// //     Filter FatJetFilter(MassDropJetDefinition, ThreeHardest);
// //     fastjet::PseudoJet FilterJet = FatJetFilter(CandidateJet);
// //
// //     SubJetVector = FilterJet.pieces();
// //     if (SubJetVector.size() != 2) Print(kError, "not two subjets");
// //
// //
// //     float Rap1, Rap2, Phi1, Phi2;
// //
// //     if (SubJetVector[0].rap() < SubJetVector[1].rap()) {
// //
// //         Rap1 = SubJetVector[0].rap();
// //         Phi1 = SubJetVector[0].phi_std();
// //         Rap2 = SubJetVector[1].rap();
// //         Phi2 = SubJetVector[1].phi_std();
// //
// //     } else {
// //
// //         Rap1 = SubJetVector[1].rap();
// //         Phi1 = SubJetVector[1].phi_std();
// //         Rap2 = SubJetVector[0].rap();
// //         Phi2 = SubJetVector[0].phi_std();
// //
// //     }
// //
// //     float DeltaR12 = SubJetVector[0].delta_R(SubJetVector[1]);
// //
// //     float DiPolarity=0;
// //
// //     for (const auto & constituent : FilterJet.constituents()){
// //
// //         const float constituentRap = constituent.rap();
// //         float constituentPhi = constituent.phi_std();
// //
// //         const float DeltaPhi = Phi2 - Phi1;
// //         const float DeltaRap = -(Rap2 - Rap1);
// //         const float RapPhi = Rap2 * Phi1 - Rap1 * Phi2;
// //
// //         const float constituentDeltaR1 = constituent.delta_R(SubJetVector[0]);
// //         const float constituentDeltaR2 = constituent.delta_R(SubJetVector[1]);
// //         const float constituentDeltaR3 = fabs(DeltaPhi * constituentRap + DeltaRap * constituentPhi + RapPhi) / sqrt(pow(DeltaPhi, 2) + pow(DeltaRap, 2));
// //         float Rap3 = - (DeltaPhi * RapPhi - DeltaRap * DeltaRap * constituentRap + DeltaPhi * DeltaRap * constituentPhi) / (DeltaPhi * DeltaPhi + DeltaRap * DeltaRap);
// //         float Phi3 = - (DeltaRap * RapPhi + DeltaPhi * DeltaRap * constituentRap - DeltaPhi * DeltaPhi * constituentPhi) / (DeltaPhi * DeltaPhi + DeltaRap * DeltaRap);
// //
// //         float DeltaR1;
// //         if ((Rap3 >= Rap1 && Rap3 <= Rap2 && Phi3 >= Phi1 && Phi3 <= Phi2)
// //                 || (Rap3 >= Rap1 && Rap3 <= Rap2 && Phi3 >= Phi2 && Phi3 <= Phi1)) {
// //             DeltaR1 = constituentDeltaR3;
// //         } else {
// //             DeltaR1 = min(constituentDeltaR1, constituentDeltaR2);
// //         }
// //
// //         if (constituentPhi < 0) {
// //             constituentPhi = constituentPhi + 2 * Pi();
// //         } else {
// //             constituentPhi = constituentPhi - 2 * Pi();
// //         }
// //
// //         Rap3 = - (DeltaPhi * RapPhi - DeltaRap * DeltaRap * constituentRap + DeltaPhi * DeltaRap * constituentPhi) / (DeltaPhi * DeltaPhi + DeltaRap * DeltaRap);
// //         Phi3 = - (DeltaRap * RapPhi + DeltaPhi * DeltaRap * constituentRap - DeltaPhi * DeltaPhi * constituentPhi) / (DeltaPhi * DeltaPhi + DeltaRap * DeltaRap);
// //
// //         const float ConstituntDeltaR4 = fabs(DeltaPhi * constituentRap + DeltaRap * constituentPhi + RapPhi) / sqrt(pow(DeltaPhi, 2) + pow(DeltaRap, 2));
// //
// //         float DeltaR2;
// //         if ((Rap3 >= Rap1 && Rap3 <= Rap2 && Phi3 >= Phi1 && Phi3 <= Phi2)
// //                 || (Rap3 >= Rap1 && Rap3 <= Rap2 && Phi3 >= Phi2 && Phi3 <= Phi1)) {
// //             DeltaR2 = ConstituntDeltaR4;
// //         } else {
// //             DeltaR2 = min(constituentDeltaR1, constituentDeltaR2);
// //         }
// //
// //         const float DeltaR = min(DeltaR1, DeltaR2);
// //
// //         const float ConeSize = sqrt(2);
// //
// //         if (constituentDeltaR1 < DeltaR12 / ConeSize || constituentDeltaR2 < DeltaR12 / ConeSize) {
// //
// //         const float deltar = DeltaR / DeltaR12;
// // //         float ConstDelR1 = constituentDeltaR1 / DeltaR12;
// // //         float ConstDelR2 = constituentDeltaR2 / DeltaR12;
// // //         float PtRatio =  constituent.perp() / HiggsJet.perp();
// //         const float PtRatio =  constituent.perp() / FilterJet.perp();
// //
// //         DiPolarity += PtRatio * pow(deltar,2);
// //
// //         }
// //
// //     }
// //
// //     return DiPolarity;
// // //     return (DiPolarity / constituentSum * 10000);
// //
// // }
