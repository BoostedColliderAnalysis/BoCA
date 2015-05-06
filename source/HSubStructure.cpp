# include "HSubStructure.hh"

hanalysis::HSubStructure::HSubStructure()
{

    Print(HNotification, "Constructor");

//   Shift = 1;


}

hanalysis::HSubStructure::~HSubStructure()
{

    Print(HNotification, "Destructor");

}

void hanalysis::HSubStructure::NewEvent()
{

    SubJets = 0;

}

bool hanalysis::HSubStructure::GetSubJets(const fastjet::PseudoJet &CandidateJet)
{

    SubJets = 1;

    Global.Mass = CandidateJet.m();
    Global.Pt = CandidateJet.pt();

    HJets PieceJets = CandidateJet.pieces();
    std::sort(PieceJets.begin(), PieceJets.end(), SortJetByMass());

    if (PieceJets.size() != 2) {

        Print(HNotification, "Wrong Number of SubJets", PieceJets.size()); // TODO reenable in smarter way
        return 0;

    }

    if (PieceJets.at(0) == PieceJets.at(1)) {

        Print(HNotification, "Just one Piece Jet");
        return 0;

    }

    // SubJets

    SubJet1.Mass = PieceJets.at(0).m();

    if (SubJet1.Mass <= 0) {

        Print(HNotification, "No SubJet 1 Mass", SubJet1.Mass);
        return 0;

    }

    SubJet2.Mass = PieceJets.at(1).m();
    if (SubJet2.Mass <= 0) SubJet2.Mass = 0;

    SubJet1.Pt = PieceJets.at(0).pt();
    SubJet2.Pt = PieceJets.at(1).pt();

    if (SubJet1.Pt <= 0 || SubJet2.Pt <= 0) {

        Print(HNotification, "No SubJet Pt");
        return 0;

    }


    Global.DeltaR = PieceJets.at(0).delta_R(PieceJets.at(1));

    SubJet1.DeltaR = PieceJets.at(0).delta_R(CandidateJet);
    SubJet2.DeltaR = PieceJets.at(1).delta_R(CandidateJet);

    //         float Asymmetry = SubJet2Pt * SubJetDeltaR / CandidateMass;

    // Get SubJet coordinates in Higgs Jet coordinates

    SubJet1.Rap = PieceJets.at(0).rap() - CandidateJet.rap();
    SubJet2.Rap = PieceJets.at(1).rap() - CandidateJet.rap();

    SubJet1.Phi = PieceJets.at(0).delta_phi_to(CandidateJet);
    SubJet2.Phi = PieceJets.at(1).delta_phi_to(CandidateJet);

    // move subjet1 together with subjet2 to origin

    SubJet2.Rap -= SubJet1.Rap;
    SubJet2.Phi -= SubJet1.Phi;

    // scale subjet distance to reference value

    const float SubJetDistance = GetDistance(SubJet2.Rap, SubJet2.Phi);

    if (SubJetDistance <= 0) {

        Print(HNotification, "No SubJet Distance", SubJetDistance);
        return 0;
    }

    SubJetRatio =  GetPosDistance() / SubJetDistance;

    return 1;

}

HVectors hanalysis::HSubStructure::GetConstituents(const fastjet::PseudoJet &CandidateJet)
{

    if (CandidateJet.constituents().empty()) {

        Print(HNotification, "Not enough Constituents", CandidateJet.constituents().size());
//         return 0;

    }

    if (!SubJets) GetSubJets(CandidateJet);
    const float Theta = atan2(SubJet2.Phi, SubJet2.Rap);

    float SumInverseRap = 0;
    float SumInversePhi = 0;
    float SubJet1Pt = 0;
    float SubJet2Pt = 0;
    DeltaR = 0;

    std::vector <TLorentzVector> ConstituentVectors;

    for (const auto & ConstituentJet : CandidateJet.constituents()) {

        if (ConstituentJet.user_index() != IsrId &&
                ConstituentJet.user_index() != CpvHiggsId &&
                std::abs(ConstituentJet.user_index()) != TopId &&
                ConstituentJet.user_index() != HiggsId
           )
            Print(HError, "Wrong UserId", ConstituentJet.user_index());

            const float Distance = ConstituentJet.delta_R(CandidateJet);

        if (Distance > DeltaR) DeltaR = Distance;

        const float Distance1 = ConstituentJet.delta_R(CandidateJet.pieces().at(0));
        const float Distance2 = ConstituentJet.delta_R(CandidateJet.pieces().at(1));

        if (Distance1 < Distance2) {
            SubJet1Pt += ConstituentJet.pt();
        } else if (Distance2 < Distance1) {
            SubJet2Pt += ConstituentJet.pt();
        } else {
            Print(HError, "Constituent is exactly in the middle");
        }


        // Get Constituent coordinates in Higgs Jet coordinates

        float ConstRap = ConstituentJet.rap() - CandidateJet.rap();
        float ConstPhi = ConstituentJet.delta_phi_to(CandidateJet);

        // move subjet1 together with constituent to origin

        ConstRap -= SubJet1.Rap;
        ConstPhi = GetDeltaPhi(ConstPhi, SubJet1.Phi);

        // scale distance to reference value

        ConstRap *= SubJetRatio;
        ConstPhi *= SubJetRatio;

        // rotate Constituent according to subjet2

        float ObservableRap = ConstRap * cos(Theta) + ConstPhi * sin(Theta);
        const float ObservablePhi = ConstRap * sin(Theta) - ConstPhi * cos(Theta);

        // move subjet2 to (1,0)
        ObservableRap -= Shift;

        const TLorentzVector ConstituentVector(ConstituentJet.pt(),ObservableRap,ObservablePhi,ConstituentJet.e());
        ConstituentVectors.emplace_back(ConstituentVector);

//         HParticleBranch *Constituent = static_cast<HParticleBranch *>(ConstituentBranch->NewEntry());
//         Constituent->Rap = ObservableRap;
//         Constituent->Phi = ObservablePhi;
//         Constituent->Pt = ConstituentJet.pt();

        SumInverseRap += ConstituentJet.pt() / std::abs(ObservableRap);
        SumInversePhi += ConstituentJet.pt() / std::abs(ObservablePhi);

    }

    Global.Rap = CandidateJet.pt() / SumInverseRap;
    Global.Phi = CandidateJet.pt() / SumInversePhi;
    Asymmetry = SubJet2Pt / SubJet1Pt;

    return ConstituentVectors;

}

bool hanalysis::HSubStructure::GetIsolation(const fastjet::PseudoJet &CandidateJet, const HJets &LeptonJets)
{

    // Get Position of SubJets

    HJets PieceJets = CandidateJet.pieces();
    std::sort(PieceJets.begin(), PieceJets.end(), SortJetByMass());

    if (PieceJets.size() != 2) {

        Print(HNotification, "Wrong Number of SubJets", PieceJets.size());
        return 0;

    }

    // Isolation

    float IsolationDeltaR = LargeNumber;

    fastjet::PseudoJet ClosestLepton;
    fastjet::PseudoJet ClosestPiece;

    for (const auto & PieceJet : PieceJets) {

        for (const auto & LeptonJet : LeptonJets) {

            const float Distance = LeptonJet.delta_R(PieceJet);
            Print(HDetailed, "DeltaR", Distance);

            if (Distance < IsolationDeltaR) {

                IsolationDeltaR = Distance;
                ClosestLepton = LeptonJet;
                ClosestPiece = PieceJet;

            }

        }

    }

    if (IsolationDeltaR != LargeNumber) {

        Isolation.Rap = ClosestLepton.rap() - ClosestPiece.rap();
        Isolation.Phi = ClosestLepton.delta_phi_to(ClosestPiece);
        Isolation.Pt = ClosestLepton.pt() / ClosestPiece.pt();
        Isolation.DeltaR = ClosestLepton.delta_R(ClosestPiece);

    }

    return 1;

}



float hanalysis::HSubStructure::GetDiPolarity(const fastjet::PseudoJet &CandidateJet) const
{

    Print(HInformation, "Jing Dipolarity");

//     HJets SubJetVector = CandidateJet.pieces();
//     if (SubJetVector.size() != 2) Print(HError, "not two subjets");
//
//     // Filtering
//     float ParentCylinderDistance = SubJetVector.at(0).delta_R(SubJetVector.at(1));
//     // MinimalCylinderDistance = Jing: 0.35; fastjet: 0.3; paper: 0.3; somewhat arbitrary choice
//     float MinimalCylinderDistance = 0.35;
//     float FilterCylinderDistance = min(ParentCylinderDistance / 2, MinimalCylinderDistance);
//     JetDefinition MassDropJetDefinition(fastjet::antikt_algorithm, FilterCylinderDistance);
//
//     // number of pieces we'll take in the filtering = Jing: 3; fastjet: 3
//     int NumberHardestPieces = 3;
//     Selector ThreeHardest = SelectorNHardest(NumberHardestPieces);
//     Filter FatJetFilter(MassDropJetDefinition, ThreeHardest);
//     fastjet::PseudoJet FilterJet = FatJetFilter(CandidateJet);

    const HJets SubJetVector = CandidateJet.pieces();
    if (SubJetVector.size() != 2) Print(HError, "not two subjets");


    float Rap1, Rap2, Phi1, Phi2;

    if (SubJetVector.at(0).rap() < SubJetVector.at(1).rap()) {

        Rap1 = SubJetVector.at(0).rap();
        Phi1 = SubJetVector.at(0).phi_std();
        Rap2 = SubJetVector.at(1).rap();
        Phi2 = SubJetVector.at(1).phi_std();

    } else {

        Rap1 = SubJetVector.at(1).rap();
        Phi1 = SubJetVector.at(1).phi_std();
        Rap2 = SubJetVector.at(0).rap();
        Phi2 = SubJetVector.at(0).phi_std();

    }

    float DeltaR12 = SubJetVector.at(0).delta_R(SubJetVector.at(1));

    float DiPolarity = 0;

    for (const auto & Constituent : CandidateJet.constituents()) {

        const float ConstituentRap = Constituent.rap();
        float ConstituentPhi = Constituent.phi_std();

        const float DeltaPhi = Phi2 - Phi1;
        const float DeltaRap = -(Rap2 - Rap1);
        const float RapPhi = Rap2 * Phi1 - Rap1 * Phi2;

        const float ConstituentDeltaR1 = Constituent.delta_R(SubJetVector.at(0));
        const float ConstituentDeltaR2 = Constituent.delta_R(SubJetVector.at(1));
        const float ConstituentDeltaR3 = std::abs(DeltaPhi * ConstituentRap + DeltaRap * ConstituentPhi + RapPhi) / sqrt(pow(DeltaPhi, 2) + pow(DeltaRap, 2));
        float Rap3 = - (DeltaPhi * RapPhi - DeltaRap * DeltaRap * ConstituentRap + DeltaPhi * DeltaRap * ConstituentPhi) / (DeltaPhi * DeltaPhi + DeltaRap * DeltaRap);
        float Phi3 = - (DeltaRap * RapPhi + DeltaPhi * DeltaRap * ConstituentRap - DeltaPhi * DeltaPhi * ConstituentPhi) / (DeltaPhi * DeltaPhi + DeltaRap * DeltaRap);

        float DeltaR1;
        if ((Rap3 >= Rap1 && Rap3 <= Rap2 && Phi3 >= Phi1 && Phi3 <= Phi2)
                || (Rap3 >= Rap1 && Rap3 <= Rap2 && Phi3 >= Phi2 && Phi3 <= Phi1)) {
            DeltaR1 = ConstituentDeltaR3;
        } else {
            DeltaR1 = std::min(ConstituentDeltaR1, ConstituentDeltaR2);
        }

        if (ConstituentPhi < 0) {
            ConstituentPhi = ConstituentPhi + 2 * TMath::Pi();
        } else {
            ConstituentPhi = ConstituentPhi - 2 * TMath::Pi();
        }

        Rap3 = - (DeltaPhi * RapPhi - DeltaRap * DeltaRap * ConstituentRap + DeltaPhi * DeltaRap * ConstituentPhi) / (DeltaPhi * DeltaPhi + DeltaRap * DeltaRap);
        Phi3 = - (DeltaRap * RapPhi + DeltaPhi * DeltaRap * ConstituentRap - DeltaPhi * DeltaPhi * ConstituentPhi) / (DeltaPhi * DeltaPhi + DeltaRap * DeltaRap);

        const float ConstituntDeltaR4 = std::abs(DeltaPhi * ConstituentRap + DeltaRap * ConstituentPhi + RapPhi) / sqrt(pow(DeltaPhi, 2) + pow(DeltaRap, 2));

        float DeltaR2;
        if ((Rap3 >= Rap1 && Rap3 <= Rap2 && Phi3 >= Phi1 && Phi3 <= Phi2)
                || (Rap3 >= Rap1 && Rap3 <= Rap2 && Phi3 >= Phi2 && Phi3 <= Phi1)) {
            DeltaR2 = ConstituntDeltaR4;
        } else {
            DeltaR2 = std::min(ConstituentDeltaR1, ConstituentDeltaR2);
        }

        const float Distance = std::min(DeltaR1, DeltaR2);

        const float ConeSize = sqrt(2);

        if (ConstituentDeltaR1 < DeltaR12 / ConeSize || ConstituentDeltaR2 < DeltaR12 / ConeSize) {

            const float deltar = Distance / DeltaR12;
            //         float ConstDelR1 = ConstituentDeltaR1 / DeltaR12;
            //         float ConstDelR2 = ConstituentDeltaR2 / DeltaR12;
            //         float PtRatio =  Constituent.perp() / HiggsJet.perp();
            const float PtRatio =  Constituent.pt() / CandidateJet.pt();

            DiPolarity += PtRatio * pow(deltar, 2);

        }

    }

    return DiPolarity;
    //     return (DiPolarity / ConstituentSum * 10000);

}


