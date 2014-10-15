# include "HHiggsTagger.hh"

HHiggsTagger::HHiggsTagger()
{

    Print(1, "Constructor");

    BottomUserIndex = 2000;

    CharmUserIndex = 1000;

    InitialValue = -100;

//     DiPolarity = InitialValue;

    NewEvent();

}

HHiggsTagger::~HHiggsTagger()
{

    Print(1, "Destructor");

}

void HHiggsTagger::NewEvent(){

    Print(2, "New Event");

//     DiPolarity=0;

    HiggsJet.reset(0,0,0,0);

    FatJet.reset(0,0,0,0);

}


PseudoJet HHiggsTagger::GetHiggsJet(const vector<PseudoJet>& EFlowJets, const vector<PseudoJet>& BottomJets, const vector<PseudoJet> &CharmJets)
{
    Print(2, "GetHiggsJet");

    for (auto & FatJet : GetFatJets(EFlowJets)) {

        PseudoJet MassDropJet = GetMassDropJet(FatJet);

        if (MassDropJet == 0) {

            Print(3,"No substructure found");
            continue;

        }

        // fastjet: 3, paper: 3, Jing: 3
        const int NumberHardestPieces = 3; // FIXME
        PseudoJet FilteredJet = GetFilteredJet(MassDropJet, fastjet::cambridge_algorithm, NumberHardestPieces);

        FilteredJetPieces = sorted_by_E(FilteredJet.pieces());

//         int FilteredJetPieceSum = FilteredJetPieceVector.size();

        GetSubJetSource(CharmJets, CharmUserIndex);
        GetSubJetSource(BottomJets, BottomUserIndex);

        int BTagCounter = BTagger();

        float FilteredJetEta = fabs(FilteredJet.eta());
        // Jing eta < 2.5
        const float FilteredJetEtaMax = 2.5;
        const int BTagRequired = 2;

        if (BTagCounter == BTagRequired && FilteredJetEta < FilteredJetEtaMax) {

            HiggsJet = FilteredJet;
//             DiPolarity = GetDipolarity(FatJet);
            break;

        }

    }                                                   // loop over fat jets

    return (HiggsJet);

}

// vector<PseudoJet> HHiggsTagger::GetFatJetVector(vector<PseudoJet> InputJetVector)
// {
//
//     Print(2, "GetFatJetVector");
//
//     const float FatJetCylinderDistanceMax = 1.2;
//     JetDefinition *FatJetDefinition = new JetDefinition(fastjet::cambridge_algorithm, FatJetCylinderDistanceMax);
//     ClusterSequence *FatJetClusterSequence = new ClusterSequence(InputJetVector, *FatJetDefinition);
//
//     const float FatJetPtMin = 0.;
//     vector<PseudoJet> InclusiveJetVector = FatJetClusterSequence->inclusive_jets(FatJetPtMin);
//     vector<PseudoJet> FatJetVector = sorted_by_E(InclusiveJetVector);
//     Print(2,"Number of Fat Jets",FatJetVector.size());
//
//     FatJetClusterSequence->delete_self_when_unused();
//     delete FatJetDefinition;
//
//     return (FatJetVector);
//
// }



PseudoJet HHiggsTagger::GetFilteredJet(const PseudoJet &MassDropJet, const fastjet::JetAlgorithm &FilterJetAlgorithm, const int NumberHardestPieces)
{

    Print(2, "GetFilteredJet");

    vector<PseudoJet> MassDropPieces = sorted_by_E(MassDropJet.pieces());
    if (MassDropPieces.size() != 2) Print(0,"Number of Subjets",MassDropPieces.size());

    PseudoJet Parent1 = MassDropPieces[0];
    PseudoJet Parent2 = MassDropPieces[1];
    float ParentCylinderDistance = Parent1.delta_R(Parent2);

    // MinimalCylinderDistance = Jing: 0.35; fastjet: 0.3; paper: 0.3; somewhat arbitrary choice
    const float MinimalCylinderDistance = 0.3;
    float FilterCylinderDistance = min(ParentCylinderDistance / 2, MinimalCylinderDistance);
    fastjet::JetDefinition FilterJetDefinition(FilterJetAlgorithm, FilterCylinderDistance);

    // number of pieces we'll take in the filtering = Jing: 3; fastjet: 3
//     const int NumberHardestPieces = 3;
    fastjet::Selector SelectorHardest = fastjet::SelectorNHardest(NumberHardestPieces);
    fastjet::Filter HiggsFilter(FilterJetDefinition, SelectorHardest);
    PseudoJet FilteredJet = HiggsFilter(MassDropJet);

    Print(3,"SubJets filtered");

    return (FilteredJet);

}

void HHiggsTagger::GetSubJetSource(const vector<PseudoJet>& Particles, const int UserIndex)
{

    Print(2, "GetSubJetSource");

    const float CylinderDistanceMax = 0.3;                          // Jing: 0.2

    for (unsigned ParticleNumber = 0; ParticleNumber < Particles.size(); ++ParticleNumber) {

        PseudoJet ParticleJet = Particles[ParticleNumber];

        const int PieceSum = 2;
//         int PieceSum = FatJetPieceVector.size();
        for (int PieceNumber = 0; PieceNumber < PieceSum; ++PieceNumber) {

            float CylinderDistance = FilteredJetPieces[PieceNumber].delta_R(ParticleJet);
            if (CylinderDistance < CylinderDistanceMax) {

                FilteredJetPieces[PieceNumber].set_user_index(UserIndex);
                break;


            }

        }

    }

}

int HHiggsTagger::BTagger()
{
    Print(2, "BTagger");

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
    for (unsigned PieceNumber = 0; PieceNumber < FilteredJetPieces.size(); ++PieceNumber) {

        PseudoJet Piece = FilteredJetPieces[PieceNumber];
        float PiecePt = Piece.perp();
        float PieceEta = fabs(Piece.eta());

        if (PieceEta < SubJetEtaMax && PiecePt > SubJetPtMin) {

            Print(3,"SubJet kinematics are fine");

            float RandomPerMil = rand() % 1000;
            int PieceUserIndex = Piece.user_index();
            if ((PieceUserIndex == BottomUserIndex && RandomPerMil < BottomPerMil) ||
                    (PieceUserIndex == CharmUserIndex && RandomPerMil < CharmPerMil)  ||
                    (PieceUserIndex != BottomUserIndex && PieceUserIndex != CharmUserIndex  && RandomPerMil < LightJetPerMil)) {

                ++BTagCounter;

                Print(3,"Subjet tagged");

            } else {

                Print(3,"SubJet not tagged");

            }
        } else {

            Print(3,"SubJet has bad kinematics");

        }

    }

    return (BTagCounter);

}


float HHiggsTagger::GetDipolarity(const PseudoJet &FatJet)
{
    Print(2, "GetDipolarity");

    float DiPolarity = 0;

//     const int NumberHardestPieces = 2;
    // not from Jing
    PseudoJet FilterJet = //GetFilteredJet(FatJet, antikt_algorithm, NumberHardestPieces);
        FatJet;

    vector<PseudoJet> SubJets = sorted_by_E(FilterJet.pieces());
    if (SubJets.size() != 2) Print(0,"Number of SubJets",SubJets.size());
    PseudoJet SubJet1 = SubJets[0];
    PseudoJet SubJet2 = SubJets[1];

    if (SubJet1.eta() < SubJet2.eta()) {

        SetEtaPhi(SubJet1, SubJet2);

    } else {

        SetEtaPhi(SubJet2, SubJet1);

    }

    DeltaR12 = SubJet1.delta_R(SubJet2);

    vector<PseudoJet> Constituents = FilterJet.constituents();
    Print(3,"Number of Constituents",Constituents.size());
    for (unsigned ConstituentNumber = 0; ConstituentNumber < Constituents.size(); ConstituentNumber++) {

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
    Print(2, "SetEtaPhi");

    Eta1 = SubJet1.eta();
    Phi1 = SubJet1.phi_std();
    Eta2 = SubJet2.eta();
    Phi2 = SubJet2.phi_std();

}

float HHiggsTagger::GetSubDeltaR()
{

    Print(2, "GetSubDeltaR");

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
