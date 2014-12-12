// # include "HSuperStructure.hh"
// 
// hanalysis::HSuperStructure::HSuperStructure()
// {
//     Print(HInformation, "Constructor");
// 
// //     Position1 = EmptyPosition;
// //     Position2 = EmptyPosition;
// 
// }
// 
// hanalysis::HSuperStructure::HSuperStructure(const fastjet::PseudoJet &NewJet1, const fastjet::PseudoJet &NewJet2)
// {
// 
//     Print(HInformation, "Constructor");
// 
//     Jet1 = NewJet1;
//     Jet2 = NewJet2;
// 
// //     Position1 = EmptyPosition;
// //     Position2 = EmptyPosition;
// 
// }
// 
// hanalysis::HSuperStructure::~HSuperStructure()
// {
// 
//     Print(HInformation, "Destructor");
// 
// }
// 
// float hanalysis::HSuperStructure::GetReferenceAngle(const fastjet::PseudoJet &Jet, const fastjet::PseudoJet &ReferenceJet) const
// {
// 
//     Print(HInformation, "Get ReferenceAngle");
// 
//     const float Rap = Jet.rap() - ReferenceJet.rap();
//     const float Phi = Jet.delta_phi_to(ReferenceJet);
// 
//     return (std::atan2(-Phi, -Rap));
// 
// }
// 
// 
// float hanalysis::HSuperStructure::GetPullAngle1() const
// {
// 
//     Print(HInformation, "GetPullAngle1");
// 
//     const float Pull = GetPull(Jet1);
//     const float ReferenceAngle = GetReferenceAngle(Jet1, Jet2);
// //     Print(HDebug, "Pull", Pull, ReferenceAngle, GetDeltaPhi(Pull, ReferenceAngle));
// 
// //     if (std::abs(GetDeltaPhi(Pull, ReferenceAngle) > 3)) {
// //         Print(HError, "extrema", Pull, ReferenceAngle);
// //         Print(HError, "extrema", Jet1.rap(), Jet1.phi_std());
// //         Print(HError, "extrema", Jet2.rap(), Jet2.phi_std());
// //         Print(HError, " ");
// //     }
// 
//     return GetDeltaPhi(Pull, ReferenceAngle);
// 
// }
// 
// float hanalysis::HSuperStructure::GetPullAngle2() const
// {
// 
//     Print(HInformation, "GetPullAngle2");
// 
//     const float Pull = GetPull(Jet2);
//     const float ReferenceAngle = GetReferenceAngle(Jet2, Jet1);
//     Print(HDebug, "Pull", Pull, ReferenceAngle, GetDeltaPhi(Pull, ReferenceAngle));
// 
//     return GetDeltaPhi(Pull, ReferenceAngle);
// 
// }
// 
// 
// float hanalysis::HSuperStructure::GetPull(const fastjet::PseudoJet &CandidateJet) const
// {
// 
//     Print(HInformation, "GetPull");
// 
//     float Rap = 0;
//     float Phi = 0;
// 
//     for (const auto & Constituent : CandidateJet.constituents()) {
// 
//         const float DeltaY = Constituent.rap() - CandidateJet.rap();
//         const float DeltaPhi = GetDeltaPhi(Constituent.phi_std(), CandidateJet.phi_std());
//         const float DeltaR = std::sqrt(std::pow(DeltaY, 2) + std::pow(DeltaPhi, 2));
//         const float PullFactor = Constituent.pt() / CandidateJet.pt() * DeltaR;
// //         const float PullFactor = Constituent.pt() / CandidateJet.pt() * Constituent.delta_R(CandidateJet);
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
// std::vector<HKinematics> hanalysis::HSuperStructure::GetConstituents() const
// {
// 
//     Print(HInformation, "GetConstituents");
// 
//     if (Jet1.constituents().size() < 1 || Jet2.constituents().size() < 1) {
// 
//         Print(HNotification, "Not enough Constituents", Jet1.constituents().size(), Jet2.constituents().size());
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
//     std::vector<HKinematics> ConstituentVectors1 = GetConstituents(Jet1, SubJetRatio, Theta, -Shift);
//     std::vector<HKinematics> ConstituentVectors2 = GetConstituents(Jet2, SubJetRatio, -Theta, Shift);
// 
//     ConstituentVectors1.insert(ConstituentVectors1.end(), ConstituentVectors2.begin(), ConstituentVectors2.end());
// 
//     return ConstituentVectors1;
// 
// }
// 
// 
// std::vector<HKinematics> hanalysis::HSuperStructure::GetConstituents(const fastjet::PseudoJet &Jet, const float JetRatio, const float Theta, const float Shift) const
// {
// 
//     Print(HInformation, "GetConstituents", JetRatio, Theta);
// 
//     const float Cut = 2. / JetRatio;
//     const float Cut1 = 1. / JetRatio;
// 
//     std::vector<HKinematics> ConstituentVectors;
// 
//     for (const auto & ConstituentJet : Jet.constituents()) {
// 
//         if (Jet.delta_R(ConstituentJet) > Cut) continue;
//         if (Jet.delta_R(ConstituentJet) < Cut1) continue;
// 
//         // Get Constituent coordinates in Jet coordinates
//         const float ConstRap = ConstituentJet.rap() - Jet.rap();
//         const float ConstPhi = GetDeltaPhi(ConstituentJet.phi_std(), Jet.phi_std());
// 
//         if (ConstPhi > Cut) Print(HError, "phi", "too big");
//         if (ConstRap > Cut) Print(HError, "eta", "too big");
// 
//         // rotate Constituent according to other jet
//         float ObservableRap = ConstRap * cos(Theta) + ConstPhi * sin(Theta);
//         float ObservablePhi = ConstRap * sin(Theta) - ConstPhi * cos(Theta);
// 
//         // Scale according to Jet distance
//         ObservableRap *= JetRatio;
//         ObservablePhi *= JetRatio;
// 
//         // move jet to (+-1,0)
//         ObservableRap -= Shift;
//         Print(HDebug, "eta", ObservableRap);
// 
//         HKinematics Constituent(ConstituentJet.pt(), ObservableRap, ObservablePhi);
// 
//         ConstituentVectors.push_back(Constituent);
// 
//     }
// 
//     return ConstituentVectors;
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
// //     Print(HInformation, "Constructor");
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
// //     Print(HInformation, "Destructor");
// //
// // }
// //
// //
// // void hdelphes::HPull::BTagCalculation(const Jet& JetClone)
// // {
// //
// //     Print(HInformation, "BTagCalculation");
// //
// //     fastjet::PseudoJet CandidateJet = GetPseudoJet(const_cast<Jet*>(&JetClone)->P4());
// //
// // //     if (Jet.pt() > 0) {
// //
// //         int ValidConstituentsSum = 0;
// //         int ConstituentsSum = JetClone.Constituents.GetEntriesFast();
// //         Print(HInformation, "Number of b Jet Constituents", ConstituentsSum);
// //
// //
// //         for (int ConstituentsNumber = 0; ConstituentsNumber < ConstituentsSum; ++ConstituentsNumber) {
// //
// //             const TObject * const ConstituentObject = JetClone.Constituents.At(ConstituentsNumber);
// //             if (ConstituentObject == 0) continue;
// //             Print(HDebug, "Entering b Jet Constituent", ConstituentsNumber);
// //             ValidConstituentsSum++;
// //
// //             const fastjet::PseudoJet ConstituentJet = GetConstituentJet(ConstituentObject);
// //
// //             const float PullFactor = ConstituentJet.pt() * ConstituentJet.delta_R(CandidateJet) / CandidateJet.pt();
// //             PullRap += PullFactor * ConstituentJet.rap();
// //             PullPhi += PullFactor * ConstituentJet.phi_std();
// //
// //         }
// //
// //         if (ValidConstituentsSum != ConstituentsSum) Print(HDebug, "Number of valid Jet Constituents", ValidConstituentsSum);
// //         Print(HInformation, "PullPhi", PullPhi);
// //         Print(HInformation, "PullY", PullRap);
// //
// // //     }
// //
// // }
// //
// // float hdelphes::HPull::PullAngle(float Rap, float Phi)
// // {
// //
// //     Print(HInformation, "Pull Angle");
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
// //         Print(HError, "Error in Theta Calculation");
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
// //     Print(HInformation, "Confine Angle");
// //
// //     if (Angle > Pi()) {
// //         Angle -= 2 * Pi();
// //     }
// //     if (Angle < -Pi()) {
// //         Angle += 2 * Pi();
// //     }
// //     if (fabs(Angle) > Pi()) {
// //         Print(HError, "Error in Angle Confinment", Angle);
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
// //     Print(HInformation, "Sub Pull");
// //
// //     Print(HDetailed, "Mass", CandidateJet.m());
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
// //     Print(HInformation, "DeltaPhi", DeltaPhi);
// //
// //     float DeltaRap = RefJetRap - SubJetRap;
// //     Print(HInformation, "DeltaRap", DeltaRap);
// //
// //     float RefTheta = PullAngle(DeltaRap, DeltaPhi);
// //     Print(HInformation, "RefTheta", RefTheta);
// //
// //     float SubPullRap = 0;
// //     float SubPullPhi = 0;
// //     int ValidConstituents = 0;
// //
// //     HJets ConstVector = CandidateJet.constituents();
// // //     HJets ConstVector = SubJet.constituents();
// //     int ConstSum = ConstVector.size();
// //     Print(HInformation, "Number of Constituents", ConstSum);
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
// //             ++ValidConstituents;
// //
// //         }
// //
// //     }
// //     Print(HInformation, "Number of Valid Constituents", ValidConstituents);
// //     Print(HInformation, "SubPullRap", SubPullRap);
// //     Print(HInformation, "SubPullPhi", SubPullPhi);
// //
// //     float PullTheta = PullAngle(SubPullRap, SubPullPhi);
// //     Print(HInformation, "PullTheta", PullTheta);
// //
// //     float Result = InitialValue;
// //     if (ValidConstituents > ConstSum / 5) {
// //
// //         if (PullTheta != InitialValue && RefTheta != InitialValue) {
// //             Result = ConfineAngle(PullTheta - RefTheta);
// //         }
// //
// //         if (fabs(Result) > Pi() && Result != InitialValue) {
// //             Print(HError, "Error in Result Calculation");
// //         }
// //
// //     }
// //
// //     Print(HInformation, "Result", Result);
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
// //     Print(HInformation, "Calculate DiPolarity");
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
// //     Print(HInformation, "FatJet Pt", FatJetPt);
// //
// //     HJets FatJetPieceVector = FatJet.pieces();
// //     int PieceSum = FatJetPieceVector.size();
// //     if (PieceSum != 2) Print(HError, "Number of Fat Jet Pieces", PieceSum);
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
// //     Print(HInformation, "Piece Distance sqr", PieceDistanceSqr);
// //     float DiPolaritySum = 0;
// //     float ConstituentPtSum = 0;
// //     float ConstituentRSqrSum = 0;
// //     float ConstituentNumSqrSum = 0;
// //     int ValidConstituents = 0;
// //
// //     float DiPolarity;
// //
// //     if (PieceDistanceSqr < 100000000) {
// //
// //
// //         HJets ConstituentsVector = FatJet.constituents();
// //         int ConstituentsSum = ConstituentsVector.size();
// //         Print(HInformation, "Number of Fat Jet Constituents", ConstituentsSum);
// //
// //         for (int ConstituentsNumber = 0; ConstituentsNumber < ConstituentsSum; ConstituentsNumber++) {
// //
// //             Print(HDebug, "Entering Fat Jet Constituent", ConstituentsNumber);
// //             fastjet::PseudoJet ConstituentJet = ConstituentsVector[ConstituentsNumber];
// //
// //             float ConstituentPhi = ConstituentJet.phi();
// //             Print(HDebug, "Constituent Phi", ConstituentPhi);
// //
// //             float ConstituentRap = ConstituentJet.rap();
// //             Print(HDebug, "Constituent Rap", ConstituentRap);
// //
// //             float ConstituentDeltaRap = Piece1Rap - ConstituentRap;
// //             float ConstituentDeltaPhi = Piece1Phi - ConstituentPhi;
// //
// //             float DeltaRap1Sqr = pow(ConstituentDeltaRap, 2);
// //             float DeltaPhi1Sqr = pow(ConstituentDeltaPhi, 2);
// //             float DeltaRap2Sqr = pow(Piece2Rap - ConstituentRap, 2);
// //             float DeltaPhi2Sqr = pow(Piece2Phi - ConstituentPhi, 2);
// //             float ConstituentDistance1Sqr = DeltaRap1Sqr + DeltaPhi1Sqr;
// //             float ConstituentDistance2Sqr = DeltaRap2Sqr + DeltaPhi2Sqr;
// //
// //             if (ConstituentDistance1Sqr > (PieceDistanceSqr / 2) && ConstituentDistance2Sqr > (PieceDistanceSqr / 2)) {
// //
// //                 Print(HDebug, "out of cones");
// //                 continue;
// //
// //             }
// //             ValidConstituents++;
// //
// //             float ConstituentPt = ConstituentJet.pt();
// //             Print(HDebug, "Constituent Pt", ConstituentPt);
// //
// //             float ConstituentNumSqr = pow(DeltaRap * ConstituentDeltaPhi - DeltaPhi * ConstituentDeltaRap, 2);
// //
// //             Print(HDebug, "ConstituentNumSqr", ConstituentNumSqr);
// //             float ConstituentRSqr = ConstituentNumSqr / PieceDistanceSqr;
// //
// //             DiPolaritySum += ConstituentRSqr * ConstituentPt / FatJetPt ;
// //             Print(HDebug, "DiPolarity Sum", DiPolaritySum);
// //
// //             ConstituentPtSum += ConstituentPt;
// //
// //             ConstituentRSqrSum += ConstituentRSqr;
// //
// //             ConstituentNumSqrSum += ConstituentNumSqr;
// //
// //         }
// //
// //         Print(HDebug, "Fraction of valid Constitueants", 1 - (ConstituentsSum - ValidConstituents) / ConstituentsSum);
// //
// //         DiPolarity = DiPolaritySum / PieceDistanceSqr;
// //
// //     }
// //
// //     if (DiPolarity < 0.01 && DiPolarity > 0) {
// //
// //         Print(HInformation, "Pt Ratio", ConstituentPtSum / FatJetPt);
// //         Print(HInformation, "RSqr Ratio", ConstituentRSqrSum / PieceDistanceSqr);
// //         Print(HInformation, "PieceDistanceSqr", PieceDistanceSqr);
// //         Print(HInformation, "ConstituentNumSqrSum", ConstituentNumSqrSum);
// //         Print(HInformation, "DiPolaritySum", DiPolaritySum);
// //         Print(HInformation, "DiPolarity", DiPolarity);
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
// //     Print(HInformation, "Jing Dipolarity");
// //
// //     HJets SubJetVector = CandidateJet.pieces();
// //     if (SubJetVector.size() != 2) Print(HError, "not two subjets");
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
// //     if (SubJetVector.size() != 2) Print(HError, "not two subjets");
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
// //     for (const auto & Constituent : FilterJet.constituents()){
// //
// //         const float ConstituentRap = Constituent.rap();
// //         float ConstituentPhi = Constituent.phi_std();
// //
// //         const float DeltaPhi = Phi2 - Phi1;
// //         const float DeltaRap = -(Rap2 - Rap1);
// //         const float RapPhi = Rap2 * Phi1 - Rap1 * Phi2;
// //
// //         const float ConstituentDeltaR1 = Constituent.delta_R(SubJetVector[0]);
// //         const float ConstituentDeltaR2 = Constituent.delta_R(SubJetVector[1]);
// //         const float ConstituentDeltaR3 = fabs(DeltaPhi * ConstituentRap + DeltaRap * ConstituentPhi + RapPhi) / sqrt(pow(DeltaPhi, 2) + pow(DeltaRap, 2));
// //         float Rap3 = - (DeltaPhi * RapPhi - DeltaRap * DeltaRap * ConstituentRap + DeltaPhi * DeltaRap * ConstituentPhi) / (DeltaPhi * DeltaPhi + DeltaRap * DeltaRap);
// //         float Phi3 = - (DeltaRap * RapPhi + DeltaPhi * DeltaRap * ConstituentRap - DeltaPhi * DeltaPhi * ConstituentPhi) / (DeltaPhi * DeltaPhi + DeltaRap * DeltaRap);
// //
// //         float DeltaR1;
// //         if ((Rap3 >= Rap1 && Rap3 <= Rap2 && Phi3 >= Phi1 && Phi3 <= Phi2)
// //                 || (Rap3 >= Rap1 && Rap3 <= Rap2 && Phi3 >= Phi2 && Phi3 <= Phi1)) {
// //             DeltaR1 = ConstituentDeltaR3;
// //         } else {
// //             DeltaR1 = min(ConstituentDeltaR1, ConstituentDeltaR2);
// //         }
// //
// //         if (ConstituentPhi < 0) {
// //             ConstituentPhi = ConstituentPhi + 2 * Pi();
// //         } else {
// //             ConstituentPhi = ConstituentPhi - 2 * Pi();
// //         }
// //
// //         Rap3 = - (DeltaPhi * RapPhi - DeltaRap * DeltaRap * ConstituentRap + DeltaPhi * DeltaRap * ConstituentPhi) / (DeltaPhi * DeltaPhi + DeltaRap * DeltaRap);
// //         Phi3 = - (DeltaRap * RapPhi + DeltaPhi * DeltaRap * ConstituentRap - DeltaPhi * DeltaPhi * ConstituentPhi) / (DeltaPhi * DeltaPhi + DeltaRap * DeltaRap);
// //
// //         const float ConstituntDeltaR4 = fabs(DeltaPhi * ConstituentRap + DeltaRap * ConstituentPhi + RapPhi) / sqrt(pow(DeltaPhi, 2) + pow(DeltaRap, 2));
// //
// //         float DeltaR2;
// //         if ((Rap3 >= Rap1 && Rap3 <= Rap2 && Phi3 >= Phi1 && Phi3 <= Phi2)
// //                 || (Rap3 >= Rap1 && Rap3 <= Rap2 && Phi3 >= Phi2 && Phi3 <= Phi1)) {
// //             DeltaR2 = ConstituntDeltaR4;
// //         } else {
// //             DeltaR2 = min(ConstituentDeltaR1, ConstituentDeltaR2);
// //         }
// //
// //         const float DeltaR = min(DeltaR1, DeltaR2);
// //
// //         const float ConeSize = sqrt(2);
// //
// //         if (ConstituentDeltaR1 < DeltaR12 / ConeSize || ConstituentDeltaR2 < DeltaR12 / ConeSize) {
// //
// //         const float deltar = DeltaR / DeltaR12;
// // //         float ConstDelR1 = ConstituentDeltaR1 / DeltaR12;
// // //         float ConstDelR2 = ConstituentDeltaR2 / DeltaR12;
// // //         float PtRatio =  Constituent.perp() / HiggsJet.perp();
// //         const float PtRatio =  Constituent.perp() / FilterJet.perp();
// //
// //         DiPolarity += PtRatio * pow(deltar,2);
// //
// //         }
// //
// //     }
// //
// //     return DiPolarity;
// // //     return (DiPolarity / ConstituentSum * 10000);
// //
// // }
