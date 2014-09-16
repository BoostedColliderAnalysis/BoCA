# include "HPull.hh"

HPull::HPull(int debug)
{

    InitialValue = -1000;
    Debug = debug;
    PullPhi = 0;
    PullRap = 0;
    DiPolarity = 0;
    if (Debug > 1) cout << "Pull created" << endl;

}

HPull::~HPull()
{

    if (Debug > 1) cout << "Pull deleted" << endl;

}


void HPull::BTagCalculation(Jet *JetClone)
{

    float BottomPt = JetClone->PT;
    float BottomPhi = JetClone->Phi;
    float BottomEta = JetClone->Eta;
    float BottomMass = JetClone->Mass;
    BottomLorentzVector.SetPtEtaPhiM(BottomPt, BottomEta, BottomPhi, BottomMass);
    float BottomY = BottomLorentzVector.Rapidity();

    BottomJet = PseudoJet(BottomPt * cos(BottomPhi), BottomPt * sin(BottomPhi), BottomPt * sinh(BottomEta), BottomPt * cosh(BottomEta));

    if (BottomPt > 0) {

        TLorentzVector ConstituentLorentzVector;
        int ValidConstituentsSum = 0;
        int ConstituentsSum = JetClone->Constituents.GetEntriesFast();
        if (Debug > 1) cout << "Number of b Jet Constituents: " << ConstituentsSum << endl;
        for (int ConstituentsNumber = 0; ConstituentsNumber < ConstituentsSum; ConstituentsNumber++) {

            TObject *ConstituentObject = JetClone->Constituents.At(ConstituentsNumber);
            if (ConstituentObject == 0) continue;
            if (Debug > 2) cout << "Entering b Jet Constituent: " << ConstituentsNumber << endl;
            ValidConstituentsSum++;
            TClass *ConstituentClass = ConstituentObject->IsA();

            if (ConstituentClass == GenParticle::Class()) {
                ConstituentLorentzVector = ((GenParticle *) ConstituentObject)->P4();
            } else if (ConstituentClass == Track::Class()) {
                ConstituentLorentzVector += ((Track *) ConstituentObject)->P4();
            } else if (ConstituentClass == Tower::Class()) {
                ConstituentLorentzVector += ((Tower *) ConstituentObject)->P4();
            } else if (ConstituentClass == Muon::Class()) {
                ConstituentLorentzVector += ((Muon *) ConstituentObject)->P4();
            } else {
                cout << "Strange b jet constituent!" << endl;
            }

            float ConstituentPhi = ConstituentLorentzVector.Phi();
            float ConstituentDeltaPhi = ConstituentPhi - BottomPhi;

            float ConstituentY = ConstituentLorentzVector.Rapidity();
            float ConstituentDeltaY = ConstituentY - BottomY;

            float ConstituentR = sqrt(pow(ConstituentDeltaPhi, 2.) + pow(ConstituentDeltaY, 2.));
            float ConstituentPt = ConstituentLorentzVector.Pt();

            float PullFactor = ConstituentPt * ConstituentR / BottomPt;
            PullRap += PullFactor * ConstituentY;
            PullPhi += PullFactor * ConstituentPhi;

        }                                                       //  Constituent Loop


        if (Debug > 1 && ValidConstituentsSum != ConstituentsSum) cout << "Number of valid Jet Constituents: " << ValidConstituentsSum << endl;
        if (Debug > 1) cout << "PullPhi: " << PullPhi << endl;
        if (Debug > 1) cout << "PullY: " << PullRap << endl;

    }

}





float HPull::PullAngle(float Rap, float Phi)
{

    float Theta = InitialValue;
    if (Rap != 0) {
        Theta = atan(Phi / Rap);
    }

    if (Rap < 0) {
        if (Phi > 0) {
            Theta += Pi();
        }
        if (Phi < 0) {
            Theta -= Pi();
        }
    }

    if (fabs(Theta) > Pi()  && Theta !=  InitialValue) {
        cout << "Error in Theta Calculation" <<  endl;
    }

    return (Theta);

}




float HPull::ConfineAngle(float Angle)
{

    if (Angle > Pi()) {
        Angle -= 2 * Pi();
    }
    if (Angle < -Pi()) {
        Angle += 2 * Pi();
    }
    if (fabs(Angle) > Pi()) {
        cout << "Error in Angle Confinment: " << Angle << endl;
    }

    return (Angle);

}





float HPull::SubPull(PseudoJet SubJet,  PseudoJet RefJet,  PseudoJet CandidateJet)
{

//     Debug = 2;

    if (Debug > 3) cout << CandidateJet.m() << endl;

    float SubJetPt = SubJet.pt();

    float SubJetPhi = SubJet.phi_std();
    float SubJetRap = SubJet.rap();

    float RefJetPhi = RefJet.phi_std();
    float RefJetRap = RefJet.rap();

    float DeltaRSubJetRefJet = RefJet.delta_R(SubJet);
    float DeltaPhi = ConfineAngle(RefJetPhi - SubJetPhi);
    if (Debug > 1) {
        cout << "DeltaPhi: " << DeltaPhi << endl;
    }

    float DeltaRap = RefJetRap - SubJetRap;
    if (Debug > 1) {
        cout << "DeltaRap: " << DeltaRap << endl;
    }

    float RefTheta = PullAngle(DeltaRap, DeltaPhi);
    if (Debug > 1) {
        cout << "RefTheta: " << RefTheta << endl;
    }

    float SubPullRap = 0;
    float SubPullPhi = 0;
    int ValidConstituents = 0;

    vector<PseudoJet> ConstVector = CandidateJet.constituents();
//     vector<PseudoJet> ConstVector = SubJet.constituents();
    int ConstSum = ConstVector.size();
    if (Debug > 1) {
        cout << "Number of Constituents: " << ConstSum << endl;
    }

    for (int ConstNumber = 0; ConstNumber < ConstSum; ConstNumber++) {

        PseudoJet ConstJet = ConstVector[ConstNumber];

        float DeltaRConstSubJet = ConstJet.delta_R(SubJet);
        float DeltaRConstRefJet = ConstJet.delta_R(RefJet);
//         if (DeltaRConstRefJet > DeltaRSubJetRefJet / 2 /*/ sqrt(2)*/ && DeltaRConstSubJet < DeltaRSubJetRefJet / sqrt(2) /*/ 2*/) {
//         if (DeltaRConstSubJet < DeltaRSubJetRefJet /*/ sqrt(2)*/ /2) {

        if (
            DeltaRConstRefJet > DeltaRSubJetRefJet / 2 /*/ sqrt(2)*/  &&
            pow(DeltaRConstSubJet, 2) + pow(DeltaRConstRefJet, 2) < 2 * pow(DeltaRSubJetRefJet, 2)
            &&
            DeltaRConstSubJet < DeltaRSubJetRefJet /*/ sqrt(2)*/
        ) {

            float ConstPhi = ConstJet.phi_std();
            float DeltaPhiConstSubJet = ConfineAngle(ConstPhi - SubJetPhi);

            float ConstRap = ConstJet.rap();
            float DeltaRapConstSubJet = ConstRap - SubJetRap;

            float DeltaRConstSubJetCalc = sqrt(pow(DeltaPhiConstSubJet, 2) + pow(DeltaRapConstSubJet, 2));
            float ConstPt = ConstJet.pt();
            float PullFactor = ConstPt / SubJetPt * DeltaRConstSubJetCalc;

            SubPullRap += PullFactor * DeltaRapConstSubJet;
            SubPullPhi += PullFactor * DeltaPhiConstSubJet;

            ++ValidConstituents;

        }

    }
    if (Debug > 1) {
        cout << "Number of Valid Constituents: " << ValidConstituents << endl;
        cout << "SubPullRap: " << SubPullRap << endl;
        cout << "SubPullPhi: " << SubPullPhi << endl;
    }

    float PullTheta = PullAngle(SubPullRap, SubPullPhi);
    if (Debug > 1) {
        cout << "PullTheta: " << PullTheta << endl;
    }

    float Result = InitialValue;
    if (ValidConstituents > ConstSum / 5) {

        if (PullTheta != InitialValue && RefTheta != InitialValue) {
            Result = ConfineAngle(PullTheta - RefTheta);
        }

        if (fabs(Result) > Pi() && Result != InitialValue) {
            cout << "Error in Result Calculation" <<  endl;
        }

    }

    if (Debug > 1) {
        cout << "Result: " << Result << endl << endl;
    }

    return (Result);

}














float HPull::CalculateDiPolarity(PseudoJet FatJet, PseudoJet FatJetPiece1, PseudoJet FatJetPiece2)
{
    // Filtering
//     PseudoJet Parent1 = MassDropJet.pieces()[0];
//     PseudoJet Parent2 = MassDropJet.pieces()[1];
//     float ParentCylinderDistance = Parent1.delta_R(Parent2);
//     // MinimalCylinderDistance = Jing: 0.35; fastjet: 0.3; paper: 0.3; somewhat arbitrary choice
//     float MinimalCylinderDistance = .3;
//     float FilterCylinderDistance = min(ParentCylinderDistance / 2, MinimalCylinderDistance);
//     JetDefinition MassDropJetDefinition(cambridge_algorithm, FilterCylinderDistance);
//
//     // number of pieces we'll take in the filtering = Jing: 3; fastjet: 3
//     int NumberHardestPieces = 2;
//     Selector ThreeHardest = SelectorNHardest(NumberHardestPieces);
//     Filter FatJetFilter(MassDropJetDefinition, ThreeHardest);
//     PseudoJet FatJet = FatJetFilter(MassDropJet);
//
//
//



    float FatJetPt = FatJet.pt();
    if (Debug > 1) cout << "FatJet Pt: " <<  FatJetPt << endl;

    vector<PseudoJet> FatJetPieceVector = FatJet.pieces();
    int PieceSum = FatJetPieceVector.size();
    if (PieceSum != 2) cout << "Number of Fat Jet Pieces: " << PieceSum << endl;
//     PseudoJet FatJetPiece1 = FatJetPieceVector[0];
//     PseudoJet FatJetPiece2 = FatJetPieceVector[1];

    float Piece1Eta = FatJetPiece1.eta();
    float Piece1Phi = FatJetPiece1.phi();
    float Piece2Eta = FatJetPiece2.eta();
    float Piece2Phi = FatJetPiece2.phi();

    float DeltaEta = Piece2Eta - Piece1Eta;
    float DeltaPhi = Piece2Phi - Piece1Phi;

    float PieceDistanceSqr = DeltaEta * DeltaEta + DeltaPhi * DeltaPhi;
    if (Debug > 1) cout << "Piece Distance sqr: " <<  PieceDistanceSqr << endl;
    float DiPolaritySum = 0;
    float ConstituentPtSum = 0;
    float ConstituentRSqrSum = 0;
    float ConstituentNumSqrSum = 0;
    int ValidConstituents = 0;

    if (PieceDistanceSqr < 100000000) {


        vector<PseudoJet> ConstituentsVector = FatJet.constituents();
        int ConstituentsSum = ConstituentsVector.size();
        if (Debug > 1) cout << "Number of Fat Jet Constituents: " << ConstituentsSum << endl;

        for (int ConstituentsNumber = 0; ConstituentsNumber < ConstituentsSum; ConstituentsNumber++) {

            if (Debug > 2) cout << "Entering Fat Jet Constituent: " << ConstituentsNumber << endl;
            PseudoJet ConstituentJet = ConstituentsVector[ConstituentsNumber];

            float ConstituentPhi = ConstituentJet.phi();
            if (Debug > 2) cout << "Constituent Phi: " << ConstituentPhi << endl;

            float ConstituentEta = ConstituentJet.eta();
            if (Debug > 2) cout << "Constituent Eta: " << ConstituentEta << endl;

            float ConstituentDeltaEta = Piece1Eta - ConstituentEta;
            float ConstituentDeltaPhi = Piece1Phi - ConstituentPhi;

            float DeltaEta1Sqr = pow(ConstituentDeltaEta, 2);
            float DeltaPhi1Sqr = pow(ConstituentDeltaPhi, 2);
            float DeltaEta2Sqr = pow(Piece2Eta - ConstituentEta, 2);
            float DeltaPhi2Sqr = pow(Piece2Phi - ConstituentPhi, 2);
            float ConstituentDistance1Sqr = DeltaEta1Sqr + DeltaPhi1Sqr;
            float ConstituentDistance2Sqr = DeltaEta2Sqr + DeltaPhi2Sqr;

            if (ConstituentDistance1Sqr > (PieceDistanceSqr / 2) && ConstituentDistance2Sqr > (PieceDistanceSqr / 2)) {

                if (Debug > 2) cout << "out of cones" << endl;
                if (Debug > 2) cout << endl;
                continue;

            }
            ValidConstituents++;

            float ConstituentPt = ConstituentJet.pt();
            if (Debug > 2) cout << "Constituent Pt: " << ConstituentPt << endl;

            float ConstituentNumSqr = pow(DeltaEta * ConstituentDeltaPhi - DeltaPhi * ConstituentDeltaEta, 2);

            if (Debug > 2) cout << ConstituentNumSqr << endl;
            float ConstituentRSqr = ConstituentNumSqr / PieceDistanceSqr;

            DiPolaritySum += ConstituentRSqr * ConstituentPt / FatJetPt ;
            if (Debug > 2) cout << "DiPolarity Sum: " << DiPolaritySum << endl;

            ConstituentPtSum += ConstituentPt;

            ConstituentRSqrSum += ConstituentRSqr;

            ConstituentNumSqrSum += ConstituentNumSqr;

        }                                                   //  Constituent Loop

        if (Debug > 2) cout << "Fraction of valid Constitueants: " <<  1 - (ConstituentsSum - ValidConstituents) / ConstituentsSum << endl;

        DiPolarity = DiPolaritySum / PieceDistanceSqr;

    }

    if (DiPolarity < 0.01 && DiPolarity > 0) {
//         Debug = 2;



        if (Debug > 1) cout << "Pt Ratio: " << ConstituentPtSum / FatJetPt << endl;

        if (Debug > 1) cout << "RSqr Ratio: " << ConstituentRSqrSum / PieceDistanceSqr << endl;

        if (Debug > 1) cout << "PieceDistanceSqr: " << PieceDistanceSqr << endl;

        if (Debug > 1) cout << "ConstituentNumSqrSum: " << ConstituentNumSqrSum << endl;

        if (Debug > 1) cout << "DiPolaritySum: " << DiPolaritySum  << endl;

        if (Debug > 1) cout << "DiPolarity: " << DiPolarity << endl;

        if (Debug > 1) cout <<  endl;

    }

    return (DiPolarity);

}



float HPull::JingDipolarity(PseudoJet CandidateJet, PseudoJet HiggsJet)
{

    vector<PseudoJet> SubJetVector = CandidateJet.pieces();
    if (SubJetVector.size() != 2) cout << "not two subjets" << endl;

    PseudoJet SubJet1 = SubJetVector[0];
    PseudoJet SubJet2 = SubJetVector[1];

    // Filtering
    float ParentCylinderDistance = SubJet1.delta_R(SubJet2);
    // MinimalCylinderDistance = Jing: 0.35; fastjet: 0.3; paper: 0.3; somewhat arbitrary choice
    float MinimalCylinderDistance = 0.35;
    float FilterCylinderDistance = min(ParentCylinderDistance / 2, MinimalCylinderDistance);
    JetDefinition MassDropJetDefinition(antikt_algorithm, FilterCylinderDistance);

    // number of pieces we'll take in the filtering = Jing: 3; fastjet: 3
    int NumberHardestPieces = 3;
    Selector ThreeHardest = SelectorNHardest(NumberHardestPieces);
    Filter FatJetFilter(MassDropJetDefinition, ThreeHardest);
    PseudoJet FilterJet = FatJetFilter(CandidateJet);

    vector<PseudoJet> CandidateConstituents = FilterJet.constituents();

    SubJetVector = FilterJet.pieces();
    if (SubJetVector.size() != 2) cout << "not two subjets" << endl;
    SubJet1 = SubJetVector[0];
    SubJet2 = SubJetVector[1];


    float Eta1, Eta2, Phi1, Phi2;

    if (SubJet1.eta() < SubJet2.eta()) {

        Eta1 = SubJet1.eta();
        Phi1 = SubJet1.phi_std();
        Eta2 = SubJet2.eta();
        Phi2 = SubJet2.phi_std();

    } else {

        Eta1 = SubJet2.eta();
        Phi1 = SubJet2.phi_std();
        Eta2 = SubJet1.eta();
        Phi2 = SubJet1.phi_std();

    }

    float DeltaR12 = SubJet1.delta_R(SubJet2);

    int ConstituentSum = CandidateConstituents.size();
    for (int ConstituentNumber = 0; ConstituentNumber < ConstituentSum; ConstituentNumber++) {

        PseudoJet Constituent = CandidateConstituents[ConstituentNumber];

        float ConstituentEta = Constituent.eta();
        float ConstituentPhi = Constituent.phi_std();

        float DeltaPhi = Phi2 - Phi1;
        float DeltaEta = -(Eta2 - Eta1);
        float EtaPhi = Eta2 * Phi1 - Eta1 * Phi2;

        float ConstituentDeltaR1 = Constituent.delta_R(SubJet1);
        float ConstituentDeltaR2 = Constituent.delta_R(SubJet2);
        float ConstituentDeltaR3 = fabs(DeltaPhi * ConstituentEta + DeltaEta * ConstituentPhi + EtaPhi) / sqrt(pow(DeltaPhi, 2) + pow(DeltaEta, 2));
        float Eta3 = - (DeltaPhi * EtaPhi - DeltaEta * DeltaEta * ConstituentEta + DeltaPhi * DeltaEta * ConstituentPhi) / (DeltaPhi * DeltaPhi + DeltaEta * DeltaEta);
        float Phi3 = - (DeltaEta * EtaPhi + DeltaPhi * DeltaEta * ConstituentEta - DeltaPhi * DeltaPhi * ConstituentPhi) / (DeltaPhi * DeltaPhi + DeltaEta * DeltaEta);

        float DeltaR1;
        if ((Eta3 >= Eta1 && Eta3 <= Eta2 && Phi3 >= Phi1 && Phi3 <= Phi2)
                || (Eta3 >= Eta1 && Eta3 <= Eta2 && Phi3 >= Phi2 && Phi3 <= Phi1)) {
            DeltaR1 = ConstituentDeltaR3;
        } else {
            DeltaR1 = min(ConstituentDeltaR1, ConstituentDeltaR2);
        }

        if (ConstituentPhi < 0) {
            ConstituentPhi = ConstituentPhi + 2 * Pi();
        } else {
            ConstituentPhi = ConstituentPhi - 2 * Pi();
        }

        Eta3 = - (DeltaPhi * EtaPhi - DeltaEta * DeltaEta * ConstituentEta + DeltaPhi * DeltaEta * ConstituentPhi) / (DeltaPhi * DeltaPhi + DeltaEta * DeltaEta);
        Phi3 = - (DeltaEta * EtaPhi + DeltaPhi * DeltaEta * ConstituentEta - DeltaPhi * DeltaPhi * ConstituentPhi) / (DeltaPhi * DeltaPhi + DeltaEta * DeltaEta);

        float ConstituntDeltaR4 = fabs(DeltaPhi * ConstituentEta + DeltaEta * ConstituentPhi + EtaPhi) / sqrt(pow(DeltaPhi, 2) + pow(DeltaEta, 2));

        float DeltaR2;
        if ((Eta3 >= Eta1 && Eta3 <= Eta2 && Phi3 >= Phi1 && Phi3 <= Phi2)
                || (Eta3 >= Eta1 && Eta3 <= Eta2 && Phi3 >= Phi2 && Phi3 <= Phi1)) {
            DeltaR2 = ConstituntDeltaR4;
        } else {
            DeltaR2 = min(ConstituentDeltaR1, ConstituentDeltaR2);
        }

        float DeltaR = min(DeltaR1, DeltaR2);

//         float ConeSize = sqrt(2);

//         if (ConstituentDeltaR1 < DeltaR12 / ConeSize || ConstituentDeltaR2 < DeltaR12 / ConeSize) {

        float deltar = DeltaR / DeltaR12;
        float ConstDelR1 = ConstituentDeltaR1 / DeltaR12;
        float ConstDelR2 = ConstituentDeltaR2 / DeltaR12;
//         float PtRatio =  Constituent.perp() / HiggsJet.perp();
        float PtRatio =  Constituent.perp() / FilterJet.perp();

        DiPolarity += PtRatio * deltar * ConstDelR1 * ConstDelR2;

// 	}
    }

    return (DiPolarity);
//     return (DiPolarity / ConstituentSum * 10000);

}
