# include "HSubStructure.hh"

HSubStructure::HSubStructure()
{

    Print(1, "Constructor");

//   Shift = 1;


}

HSubStructure::~HSubStructure()
{

    Print(1, "Destructor");

}

void HSubStructure::NewEvent()
{

    SubJets = 0;

}

bool HSubStructure::GetSubJets(const PseudoJet &CandidateJet)
{

    SubJets = 1;

    Global.Mass = CandidateJet.m();
    Global.Pt = CandidateJet.pt();

    vector<PseudoJet> PieceJets = CandidateJet.pieces();
    std::sort(PieceJets.begin(), PieceJets.end(), SortJetByMass());

    if (PieceJets.size() != 2) {

        Print(4, "Wrong Number of SubJets", PieceJets.size()); // TODO reenable in smarter way
        return 0;

    }
    
    if (PieceJets[0] == PieceJets[1]) {
        
        Print(1, "Just one Piece Jet");
        return 0;
        
    }

    // SubJets

    SubJet1.Mass = PieceJets[0].m();
    SubJet2.Mass = PieceJets[1].m();

    if (SubJet1.Mass <= 0 || SubJet2.Mass <= 0) {

        Print(2, "No SubJet Mass");
        return 0;

    }

    SubJet1.Pt = PieceJets[0].pt();
    SubJet2.Pt = PieceJets[1].pt();

    if (SubJet1.Pt <= 0 || SubJet2.Pt <= 0) {

        Print(1, "No SubJet Pt");
        return 0;

    }


    Global.DeltaR = PieceJets[0].delta_R(PieceJets[1]);

    SubJet1.DeltaR = PieceJets[0].delta_R(CandidateJet);
    SubJet2.DeltaR = PieceJets[1].delta_R(CandidateJet);

    //         float Asymmetry = SubJet2Pt * SubJetDeltaR / CandidateMass;

    // Get SubJet coordinates in Higgs Jet coordinates

    SubJet1.Eta = PieceJets[0].eta() - CandidateJet.eta();
    SubJet2.Eta = PieceJets[1].eta() - CandidateJet.eta();

    SubJet1.Phi = PieceJets[0].delta_phi_to(CandidateJet);
    SubJet2.Phi = PieceJets[1].delta_phi_to(CandidateJet);

    // move subjet1 together with subjet2 to origin

    SubJet2.Eta -= SubJet1.Eta;
    SubJet2.Phi -= SubJet1.Phi;

    // scale subjet distance to reference value

    const float SubJetDistance = GetDistance(SubJet2.Eta, SubJet2.Phi);

    if (SubJetDistance <= 0) {

        Print(1, "No SubJet Distance", SubJetDistance);
        return 0;
    }
    
    SubJetRatio =  GetPosDistance() / SubJetDistance;


    return 1;

}

bool HSubStructure::GetConstituents(const PseudoJet &CandidateJet, ExRootTreeBranch *const ConstituentBranch)
{

    if (CandidateJet.constituents().size() < 1) {

        Print(1, "Not enough Constituents", CandidateJet.constituents().size());
        return 0;

    }

    if (!SubJets) GetSubJets(CandidateJet);
    const float Theta = atan2(SubJet2.Phi, SubJet2.Eta);

    float SumInverseEta = 0;
    float SumInversePhi = 0;
    float SubJet1Pt = 0;
    float SubJet2Pt = 0;
    DeltaR = 0;

    for (const auto & ConstituentJet : CandidateJet.constituents()) {

        const float Distance = ConstituentJet.delta_R(CandidateJet);

        if (Distance > DeltaR) DeltaR = Distance;

        const float Distance1 = ConstituentJet.delta_R(CandidateJet.pieces()[0]);
        const float Distance2 = ConstituentJet.delta_R(CandidateJet.pieces()[1]);

        if (Distance1 < Distance2) {
            SubJet1Pt += ConstituentJet.pt();
        } else if (Distance2 < Distance1) {
            SubJet2Pt += ConstituentJet.pt();
        } else {
            Print(0, "Constituent is exactly in the middle");
        }


        // Get Constituent coordinates in Higgs Jet coordinates

        float ConstEta = ConstituentJet.eta() - CandidateJet.eta();
        float ConstPhi = ConstituentJet.delta_phi_to(CandidateJet);

        // move subjet1 together with constituent to origin

        ConstEta -= SubJet1.Eta;
        ConstPhi = GetDeltaPhi(ConstPhi, SubJet1.Phi);

        // scale distance to reference value

        ConstEta = ConstEta * SubJetRatio;
        ConstPhi = ConstPhi * SubJetRatio;

        // rotate Constituent according to subjet2

        float ObservableEta = ConstEta * cos(Theta) + ConstPhi * sin(Theta);
        const float ObservablePhi = ConstEta * sin(Theta) - ConstPhi * cos(Theta);

        // move subjet2 to (1,0)
        ObservableEta -= Shift;


        HParticleBranch *Constituent = static_cast<HParticleBranch *>(ConstituentBranch->NewEntry());
        Constituent->Eta = ObservableEta;
        Constituent->Phi = ObservablePhi;
        Constituent->Pt = ConstituentJet.pt();


        SumInverseEta += ConstituentJet.pt() / fabs(ObservableEta);
        SumInversePhi += ConstituentJet.pt() / fabs(ObservablePhi);

    }

    Global.Eta = CandidateJet.pt() / SumInverseEta;
    Global.Phi = CandidateJet.pt() / SumInversePhi;
    Asymmetry = SubJet2Pt / SubJet1Pt;

    return 1;

}

bool HSubStructure::GetIsolation(const PseudoJet &CandidateJet, const vector<PseudoJet> &LeptonJets)
{

    // Get Position of SubJets

    vector<PseudoJet> PieceJets = CandidateJet.pieces();
    std::sort(PieceJets.begin(), PieceJets.end(), SortJetByMass());

    if (!(PieceJets.size() == 2)) {

        Print(1, "Wrong Number of SubJets", PieceJets.size());
        return 0;

    }


    // Isolation

    float IsolationDeltaR = LargeNumber;

    PseudoJet ClosestLepton;
    PseudoJet ClosestPiece;

    for (const auto & PieceJet : PieceJets) {

        for (const auto & LeptonJet : LeptonJets) {

            const float Distance = LeptonJet.delta_R(PieceJet);
            Print(4, "DeltaR", Distance);

            if (Distance < IsolationDeltaR) {

                IsolationDeltaR = Distance;
                ClosestLepton = LeptonJet;
                ClosestPiece = PieceJet;

            }

        }

    }

    if (IsolationDeltaR != LargeNumber) {

        Isolation.Eta = ClosestLepton.eta() - ClosestPiece.eta();
        Isolation.Phi = ClosestLepton.delta_phi_to(ClosestPiece);
        Isolation.Pt = ClosestLepton.pt() / ClosestPiece.pt();
        Isolation.DeltaR = ClosestLepton.delta_R(ClosestPiece);

    }

    return 1;

}



float HSubStructure::GetDiPolarity(const PseudoJet &CandidateJet) const
{

    Print(2, "Jing Dipolarity");

//     vector<PseudoJet> SubJetVector = CandidateJet.pieces();
//     if (SubJetVector.size() != 2) Print(0, "not two subjets");
//
//     // Filtering
//     float ParentCylinderDistance = SubJetVector[0].delta_R(SubJetVector[1]);
//     // MinimalCylinderDistance = Jing: 0.35; fastjet: 0.3; paper: 0.3; somewhat arbitrary choice
//     float MinimalCylinderDistance = 0.35;
//     float FilterCylinderDistance = min(ParentCylinderDistance / 2, MinimalCylinderDistance);
//     JetDefinition MassDropJetDefinition(fastjet::antikt_algorithm, FilterCylinderDistance);
//
//     // number of pieces we'll take in the filtering = Jing: 3; fastjet: 3
//     int NumberHardestPieces = 3;
//     Selector ThreeHardest = SelectorNHardest(NumberHardestPieces);
//     Filter FatJetFilter(MassDropJetDefinition, ThreeHardest);
//     PseudoJet FilterJet = FatJetFilter(CandidateJet);

    const vector<PseudoJet> SubJetVector = CandidateJet.pieces();
    if (SubJetVector.size() != 2) Print(0, "not two subjets");


    float Eta1, Eta2, Phi1, Phi2;

    if (SubJetVector[0].eta() < SubJetVector[1].eta()) {

        Eta1 = SubJetVector[0].eta();
        Phi1 = SubJetVector[0].phi_std();
        Eta2 = SubJetVector[1].eta();
        Phi2 = SubJetVector[1].phi_std();

    } else {

        Eta1 = SubJetVector[1].eta();
        Phi1 = SubJetVector[1].phi_std();
        Eta2 = SubJetVector[0].eta();
        Phi2 = SubJetVector[0].phi_std();

    }

    float DeltaR12 = SubJetVector[0].delta_R(SubJetVector[1]);

    float DiPolarity = 0;

    for (const auto & Constituent : CandidateJet.constituents()) {

        const float ConstituentEta = Constituent.eta();
        float ConstituentPhi = Constituent.phi_std();

        const float DeltaPhi = Phi2 - Phi1;
        const float DeltaEta = -(Eta2 - Eta1);
        const float EtaPhi = Eta2 * Phi1 - Eta1 * Phi2;

        const float ConstituentDeltaR1 = Constituent.delta_R(SubJetVector[0]);
        const float ConstituentDeltaR2 = Constituent.delta_R(SubJetVector[1]);
        const float ConstituentDeltaR3 = fabs(DeltaPhi * ConstituentEta + DeltaEta * ConstituentPhi + EtaPhi) / sqrt(pow(DeltaPhi, 2) + pow(DeltaEta, 2));
        float Eta3 = - (DeltaPhi * EtaPhi - DeltaEta * DeltaEta * ConstituentEta + DeltaPhi * DeltaEta * ConstituentPhi) / (DeltaPhi * DeltaPhi + DeltaEta * DeltaEta);
        float Phi3 = - (DeltaEta * EtaPhi + DeltaPhi * DeltaEta * ConstituentEta - DeltaPhi * DeltaPhi * ConstituentPhi) / (DeltaPhi * DeltaPhi + DeltaEta * DeltaEta);

        float DeltaR1;
        if ((Eta3 >= Eta1 && Eta3 <= Eta2 && Phi3 >= Phi1 && Phi3 <= Phi2)
                || (Eta3 >= Eta1 && Eta3 <= Eta2 && Phi3 >= Phi2 && Phi3 <= Phi1)) {
            DeltaR1 = ConstituentDeltaR3;
        } else {
            DeltaR1 = std::min(ConstituentDeltaR1, ConstituentDeltaR2);
        }

        if (ConstituentPhi < 0) {
            ConstituentPhi = ConstituentPhi + 2 * TMath::Pi();
        } else {
            ConstituentPhi = ConstituentPhi - 2 * TMath::Pi();
        }

        Eta3 = - (DeltaPhi * EtaPhi - DeltaEta * DeltaEta * ConstituentEta + DeltaPhi * DeltaEta * ConstituentPhi) / (DeltaPhi * DeltaPhi + DeltaEta * DeltaEta);
        Phi3 = - (DeltaEta * EtaPhi + DeltaPhi * DeltaEta * ConstituentEta - DeltaPhi * DeltaPhi * ConstituentPhi) / (DeltaPhi * DeltaPhi + DeltaEta * DeltaEta);

        const float ConstituntDeltaR4 = fabs(DeltaPhi * ConstituentEta + DeltaEta * ConstituentPhi + EtaPhi) / sqrt(pow(DeltaPhi, 2) + pow(DeltaEta, 2));

        float DeltaR2;
        if ((Eta3 >= Eta1 && Eta3 <= Eta2 && Phi3 >= Phi1 && Phi3 <= Phi2)
                || (Eta3 >= Eta1 && Eta3 <= Eta2 && Phi3 >= Phi2 && Phi3 <= Phi1)) {
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


