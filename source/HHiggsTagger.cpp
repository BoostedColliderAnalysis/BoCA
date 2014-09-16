# include "HHiggsTagger.hh"

HHiggsTagger::HHiggsTagger()
{
       
    Print(0, "Constructor");
    
    BottomUserIndex = 2000;

    CharmUserIndex = 1000;

    InitialValue = -100;

    DiPolarity = InitialValue;
    
    NewEvent();

}

HHiggsTagger::~HHiggsTagger()
{

    
    Print(0, "Destructor");

}

void HHiggsTagger::NewEvent(){
    
    Print(1, "New Event");
    
    DiPolarity=0;
    
    HiggsJet.reset(0,0,0,0);
    
    FatJet.reset(0,0,0,0);
    
}


PseudoJet HHiggsTagger::GetHiggsJet(vector<PseudoJet> InputJetVector, vector<PseudoJet> BottomVector, vector<PseudoJet> CharmVector)
{
    Print(1, "GetHiggsJet");

    vector<PseudoJet> FatJetVector = GetFatJetVector(InputJetVector);

    int FatJetSum = FatJetVector.size();
    for (int FatJetNumber = 0; FatJetNumber < FatJetSum; ++FatJetNumber) {

        FatJet = FatJetVector[FatJetNumber];

        PseudoJet MassDropJet = GetMassDropJet(FatJet);

        if (MassDropJet == 0) {

            if (Debug > 2) cout << "No substructure found" << endl;
            continue;

        }

        // fastjet: 3, paper: 3, Jing: 3
        const int NumberHardestPieces = 3; // FIXME 
        PseudoJet FilteredJet = GetFilteredJet(MassDropJet, cambridge_algorithm, NumberHardestPieces);

        FilteredJetPieceVector = sorted_by_E(FilteredJet.pieces());

//         int FilteredJetPieceSum = FilteredJetPieceVector.size();

        GetSubJetSource(CharmVector, CharmUserIndex);
        GetSubJetSource(BottomVector, BottomUserIndex);

        int BTagCounter = BTagger();

        float FilteredJetEta = fabs(FilteredJet.eta());
        // Jing eta < 2.5
        const float FilteredJetEtaMax = 2.5;
        const int BTagRequired = 2;

        if (BTagCounter == BTagRequired && FilteredJetEta < FilteredJetEtaMax) {

            HiggsJet = FilteredJet;
            DiPolarity = GetDipolarity(FatJet);
            break;

        }

    }                                                   // loop over fat jets

    return (HiggsJet);

}

vector<PseudoJet> HHiggsTagger::GetFatJetVector(vector<PseudoJet> InputJetVector)
{
    
    Print(1, "GetFatJetVector");
    
    // FatJetCylinderDistanceMax = Jing: 1.4; fastjet: 1.2; paper: 1.2
    const float FatJetCylinderDistanceMax = 1.2;
    JetDefinition *FatJetDefinition = new JetDefinition(cambridge_algorithm, FatJetCylinderDistanceMax);
    ClusterSequence *FatJetClusterSequence = new ClusterSequence(InputJetVector, *FatJetDefinition);
    // FatJetPtMin = Jing: 40; fastjet: 0
    const float FatJetPtMin = 0.;
    vector<PseudoJet> InclusiveJetVector = FatJetClusterSequence->inclusive_jets(FatJetPtMin);
    vector<PseudoJet> FatJetVector = sorted_by_E(InclusiveJetVector);
    if (Debug > 1) cout << "Number of Fat Jets: " << FatJetVector.size() << endl;
    
    FatJetClusterSequence->delete_self_when_unused();
    delete FatJetDefinition;

    return (FatJetVector);

}

PseudoJet HHiggsTagger::GetMassDropJet(PseudoJet FatJet)
{
    
    Print(1, "GetMassDropJet");
    
    // MassDropMin = Jing: 0.667; fastjet: 0.667; Paper: 0.67
    const float MassDropMin = 0.667;
    // AsymmetryCut = Jing: 0.09; fastjet: 0.09; paper: 0.09
    const float AsymmetryCut = 0.09;
    MassDropTagger FatJetMassDroppTagger(MassDropMin, AsymmetryCut);
    PseudoJet MassDropJet = FatJetMassDroppTagger(FatJet);

    if (Debug > 2) cout << "Mass Drop applied" << endl;

    return (MassDropJet);

}

PseudoJet HHiggsTagger::GetFilteredJet(PseudoJet MassDropJet, JetAlgorithm FilterJetAlgorithm, int NumberHardestPieces)
{
    
    Print(1, "GetFilteredJet");
    
    vector<PseudoJet> MassDropPieces = sorted_by_E(MassDropJet.pieces());
    if (MassDropPieces.size() != 2) cout << "Number of Subjets: " << MassDropPieces.size() << endl;

    PseudoJet Parent1 = MassDropPieces[0];
    PseudoJet Parent2 = MassDropPieces[1];
    float ParentCylinderDistance = Parent1.delta_R(Parent2);

    // MinimalCylinderDistance = Jing: 0.35; fastjet: 0.3; paper: 0.3; somewhat arbitrary choice
    const float MinimalCylinderDistance = 0.35;
    float FilterCylinderDistance = min(ParentCylinderDistance / 2, MinimalCylinderDistance);
    JetDefinition FilterJetDefinition(FilterJetAlgorithm, FilterCylinderDistance);

    // number of pieces we'll take in the filtering = Jing: 3; fastjet: 3
//     const int NumberHardestPieces = 3;
    Selector SelectorHardest = SelectorNHardest(NumberHardestPieces);
    Filter HiggsFilter(FilterJetDefinition, SelectorHardest);
    PseudoJet FilteredJet = HiggsFilter(MassDropJet);

    if (Debug > 2) cout << "SubJets filtered" << endl;

    return (FilteredJet);

}

void HHiggsTagger::GetSubJetSource(vector<PseudoJet> ParticleVector, int UserIndex)
{
    
    Print(1, "GetSubJetSource");
    
    const float CylinderDistanceMax = 0.3;                          // Jing: 0.2

    int ParticleSum = ParticleVector.size();
    for (int ParticleNumber = 0; ParticleNumber < ParticleSum; ++ParticleNumber) {


        PseudoJet ParticleJet = ParticleVector[ParticleNumber];

        const int PieceSum = 2;
//         int PieceSum = FatJetPieceVector.size();
        for (int PieceNumber = 0; PieceNumber < PieceSum; ++PieceNumber) {

            float CylinderDistance = FilteredJetPieceVector[PieceNumber].delta_R(ParticleJet);
            if (CylinderDistance < CylinderDistanceMax) {

                FilteredJetPieceVector[PieceNumber].set_user_index(UserIndex);
                break;


            }

        }

    }

}

int HHiggsTagger::BTagger()
{
    Print(1, "BTagger");
    
    // Jing: 700
    const int BottomPerMil = 750;   
    // Jing: 200
    const int CharmPerMil = 100;                  
    // Jing: 10
    const int LightJetPerMil = 5;
    
    // Jing: 2.5
    const float SubJetEtaMax = 2.5;        
    // Jing: 30
    const float SubJetPtMin = 20;

    int BTagCounter = 0;
//     const int PieceSum = 2;
    int PieceSum = FilteredJetPieceVector.size();
    for (int PieceNumber = 0; PieceNumber < PieceSum; ++PieceNumber) {

        PseudoJet Piece = FilteredJetPieceVector[PieceNumber];
        float PiecePt = Piece.perp();
        float PieceEta = fabs(Piece.eta());

        if (PieceEta < SubJetEtaMax && PiecePt > SubJetPtMin) {

            if (Debug > 2) cout << "SubJet kinematics are fine" << endl;

            float RandomPerMil = rand() % 1000;
            int PieceUserIndex = Piece.user_index();
            if ((PieceUserIndex == BottomUserIndex && RandomPerMil < BottomPerMil) ||
                    (PieceUserIndex == CharmUserIndex && RandomPerMil < CharmPerMil)  ||
                    (PieceUserIndex != BottomUserIndex && PieceUserIndex != CharmUserIndex  && RandomPerMil < LightJetPerMil)) {

                ++BTagCounter;

                if (Debug > 2) cout << "Subjet tagged" << endl;

            } else {

                if (Debug > 2) cout << "SubJet not tagged" << endl;

            }
        } else {

            if (Debug > 2) cout << "SubJet has bad kinematics" << endl;

        }

    }

    return (BTagCounter);

}


float HHiggsTagger::GetDipolarity(PseudoJet FatJet)
{
    Print(1, "GetDipolarity");
    
    DiPolarity = 0;

//     const int NumberHardestPieces = 2;
    // not from Jing
    PseudoJet FilterJet = //GetFilteredJet(FatJet, antikt_algorithm, NumberHardestPieces);
        FatJet;

    vector<PseudoJet> SubJetVector = sorted_by_E(FilterJet.pieces());
    if (SubJetVector.size() != 2) cout << "Number of SubJets: " << SubJetVector.size() << endl;
    PseudoJet SubJet1 = SubJetVector[0];
    PseudoJet SubJet2 = SubJetVector[1];

    if (SubJet1.eta() < SubJet2.eta()) {

        SetEtaPhi(SubJet1, SubJet2);

    } else {

        SetEtaPhi(SubJet2, SubJet1);

    }

    DeltaR12 = SubJet1.delta_R(SubJet2);

    vector<PseudoJet> Constituents = FilterJet.constituents();
    int ConstituentSum = Constituents.size();
    if (Debug > 2) cout << "Number of Constituents: " << ConstituentSum << endl;
    for (int ConstituentNumber = 0; ConstituentNumber < ConstituentSum; ConstituentNumber++) {

        PseudoJet Constituent = Constituents[ConstituentNumber];

        Eta0 = Constituent.eta();
        Phi0 = Constituent.phi_std();

        DeltaR01 = Constituent.delta_R(SubJet1);
        DeltaR02 = Constituent.delta_R(SubJet2);

        float DeltaR1 = GetSubDeltaR();

        if (Phi0 < 0) {

            Phi0 = Phi0 + 2 * Pi();

        } else {

            Phi0 = Phi0 - 2 * Pi();

        }

        float DeltaR2 = GetSubDeltaR();

        float ConeSize = sqrt(2);

        if (DeltaR1 < DeltaR12 / ConeSize || DeltaR2 < DeltaR12 / ConeSize) {

            float DeltaR = min(DeltaR1, DeltaR2);
            float DeltaRRatio = DeltaR / DeltaR12;
            float PtRatio =  Constituent.perp() / FatJet.perp();

            DiPolarity += PtRatio * pow(DeltaRRatio, 2);
        }

//         if (DeltaR1 < DeltaR12 / ConeSize && DeltaR2 > DeltaR12 / ConeSize) {
//
//             float DeltaR = DeltaR1;
//             float DeltaRRatio = DeltaR / DeltaR12;
//             float PtRatio =  Constituent.perp() / FatJet.perp();
//
//             DiPolarity += PtRatio * pow(DeltaRRatio, 2);
//         }
//
//         if (DeltaR2 < DeltaR12 / ConeSize && DeltaR1 > DeltaR12 / ConeSize) {
//
//             float DeltaR = DeltaR2;
//             float DeltaRRatio = DeltaR / DeltaR12;
//             float PtRatio =  Constituent.perp() / FatJet.perp();
//
//             DiPolarity += PtRatio * pow(DeltaRRatio, 2);
//         }


    }

    return (DiPolarity);

}

void HHiggsTagger::SetEtaPhi(PseudoJet SubJet1, PseudoJet SubJet2)
{
    Print(1, "SetEtaPhi");
    
    Eta1 = SubJet1.eta();
    Phi1 = SubJet1.phi_std();
    Eta2 = SubJet2.eta();
    Phi2 = SubJet2.phi_std();

}

float HHiggsTagger::GetSubDeltaR()
{
    
    Print(1, "GetSubDeltaR");
    
    float SubDeltaR;

    float DeltaR = fabs(DeltaPhiEta0() + DeltaEtaPhi0() + EtaPhi()) / DeltaR12;
    float Eta = - (DeltaPhi() * EtaPhi() - DeltaEtaSqr() * Eta0 + DeltaPhi() * DeltaEtaPhi0()) / DeltaR12Sqr();
    float Phi = - (DeltaEta() * EtaPhi() + DeltaEta() * DeltaPhiEta0() - DeltaPhiSqr() * Phi0) / DeltaR12Sqr();

    if ((Eta >= Eta1 && Eta <= Eta2 && Phi >= Phi1 && Phi <= Phi2)
            || (Eta >= Eta1 && Eta <= Eta2 && Phi >= Phi2 && Phi <= Phi1)) {

        SubDeltaR = DeltaR;

    } else {

        SubDeltaR = min(DeltaR01, DeltaR02);

    }


    return (SubDeltaR);
}
