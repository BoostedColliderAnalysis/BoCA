# include "HHiggsTagger.hh"

hdelphes::HHiggsTagger::HHiggsTagger()
{

    Print(HNotification, "Constructor");

    BottomUserIndex = 2000;

    CharmUserIndex = 1000;

    InitialValue = -100;

//     DiPolarity = InitialValue;

    NewEvent();

}

hdelphes::HHiggsTagger::~HHiggsTagger()
{

    Print(HNotification, "Destructor");

}

void hdelphes::HHiggsTagger::NewEvent()
{

    Print(HInformation, "New Event");

//     DiPolarity=0;

    HiggsJet.reset(0, 0, 0, 0);

//     FatJet.reset(0,0,0,0);

}


fastjet::PseudoJet hdelphes::HHiggsTagger::GetHiggsJet(const HJets &EFlowJets, const HJets &BottomJets, const HJets &CharmJets)
{
    Print(HInformation, "GetHiggsJet");

    for (auto & FatJet : GetFatJets(EFlowJets)) {

        fastjet::PseudoJet MassDropJet = GetMassDropJet(FatJet);

        if (MassDropJet == 0) {

            Print(HDebug, "No substructure found");
            continue;

        }

        // fastjet: 3, paper: 3, Jing: 3
        const int NumberHardestPieces = 3; // FIXME
        fastjet::PseudoJet FilteredJet = GetFilteredJet(MassDropJet, fastjet::cambridge_algorithm, NumberHardestPieces);

        FilteredJetPieces = sorted_by_E(FilteredJet.pieces());

//         int FilteredJetPieceSum = FilteredJetPieceVector.size();

        GetSubJetSource(CharmJets, CharmUserIndex);
        GetSubJetSource(BottomJets, BottomUserIndex);

        int BTagCounter = BTagger();

        float FilteredJetRap = std::abs(FilteredJet.rap());
        // Jing eta < 2.5
        const float FilteredJetRapMax = 2.5;
        const int BTagRequired = 2;

        if (BTagCounter == BTagRequired && FilteredJetRap < FilteredJetRapMax) {

            HiggsJet = FilteredJet;
//             DiPolarity = GetDipolarity(FatJet);
            break;

        }

    }                                                   // loop over fat jets

    return HiggsJet;

}

// HJets Analysis::HHiggsTagger::GetFatJetVector(HJets InputJetVector)
// {
//
//     Print(HInformation, "GetFatJetVector");
//
//     const float FatJetCylinderDistanceMax = 1.2;
//     JetDefinition *FatJetDefinition = new JetDefinition(fastjet::cambridge_algorithm, FatJetCylinderDistanceMax);
//     ClusterSequence *FatJetClusterSequence = new ClusterSequence(InputJetVector, *FatJetDefinition);
//
//     const float FatJetPtMin = 0.;
//     HJets InclusiveJetVector = FatJetClusterSequence->inclusive_jets(FatJetPtMin);
//     HJets FatJetVector = sorted_by_E(InclusiveJetVector);
//     Print(HInformation,"Number of Fat Jets",FatJetVector.size());
//
//     FatJetClusterSequence->delete_self_when_unused();
//     delete FatJetDefinition;
//
//     return (FatJetVector);
//
// }



fastjet::PseudoJet hdelphes::HHiggsTagger::GetFilteredJet(const fastjet::PseudoJet &MassDropJet, const fastjet::JetAlgorithm &FilterJetAlgorithm, const int NumberHardestPieces)
{

    Print(HInformation, "GetFilteredJet");

    HJets MassDropPieces = sorted_by_E(MassDropJet.pieces());
    if (MassDropPieces.size() != 2) Print(HError, "Number of Subjets", MassDropPieces.size());

    fastjet::PseudoJet Parent1 = MassDropPieces.at(0);
    fastjet::PseudoJet Parent2 = MassDropPieces.at(1);
    float ParentCylinderDistance = Parent1.delta_R(Parent2);

    // MinimalCylinderDistance = Jing: 0.35; fastjet: 0.3; paper: 0.3; somewhat arbitrary choice
    const float MinimalCylinderDistance = 0.3;
    float FilterCylinderDistance = std::min(ParentCylinderDistance / 2, MinimalCylinderDistance);
    fastjet::JetDefinition FilterJetDefinition(FilterJetAlgorithm, FilterCylinderDistance);

    // number of pieces we'll take in the filtering = Jing: 3; fastjet: 3
//     const int NumberHardestPieces = 3;
    fastjet::Selector SelectorHardest = fastjet::SelectorNHardest(NumberHardestPieces);
    fastjet::Filter HiggsFilter(FilterJetDefinition, SelectorHardest);
    fastjet::PseudoJet FilteredJet = HiggsFilter(MassDropJet);

    Print(HDebug, "SubJets filtered");

    return FilteredJet;

}

void hdelphes::HHiggsTagger::GetSubJetSource(const HJets &Particles, const int UserIndex)
{

    Print(HInformation, "GetSubJetSource");

    const float CylinderDistanceMax = 0.3;                          // Jing: 0.2

    for (unsigned ParticleNumber = 0; ParticleNumber < Particles.size(); ++ParticleNumber) {

        fastjet::PseudoJet ParticleJet = Particles[ParticleNumber];

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

int hdelphes::HHiggsTagger::BTagger()
{
    Print(HInformation, "BTagger");

    // Jing: 700
    const int BottomPerMil = 750;
    // Jing: 200
    const int CharmPerMil = 100;
    // Jing: 10
    const int LightJetPerMil = 5;

    // Jing: 2.5
    const float SubJetRapMax = 2.5;
    // Jing: 30
    const float SubJetPtMin = 20;

    int BTagCounter = 0;
//     const int PieceSum = 2;
    for (unsigned PieceNumber = 0; PieceNumber < FilteredJetPieces.size(); ++PieceNumber) {

        fastjet::PseudoJet Piece = FilteredJetPieces[PieceNumber];
        float PiecePt = Piece.perp();
        float PieceRap = std::abs(Piece.rap());

        if (PieceRap < SubJetRapMax && PiecePt > SubJetPtMin) {

            Print(HDebug, "SubJet kinematics are fine");

            float RandomPerMil = rand() % 1000;
            int PieceUserIndex = Piece.user_index();
            if ((PieceUserIndex == BottomUserIndex && RandomPerMil < BottomPerMil) ||
                    (PieceUserIndex == CharmUserIndex && RandomPerMil < CharmPerMil)  ||
                    (PieceUserIndex != BottomUserIndex && PieceUserIndex != CharmUserIndex  && RandomPerMil < LightJetPerMil)) {

                ++BTagCounter;

                Print(HDebug, "Subjet tagged");

            } else {

                Print(HDebug, "SubJet not tagged");

            }
        } else {

            Print(HDebug, "SubJet has bad kinematics");

        }

    }

    return BTagCounter;

}


float hdelphes::HHiggsTagger::GetDipolarity(const fastjet::PseudoJet &FatJet)
{
    Print(HInformation, "GetDipolarity");

    float DiPolarity = 0;

//     const int NumberHardestPieces = 2;
    // not from Jing
    fastjet::PseudoJet FilterJet = //GetFilteredJet(FatJet, antikt_algorithm, NumberHardestPieces);
        FatJet;

    HJets SubJets = sorted_by_E(FilterJet.pieces());
    if (SubJets.size() != 2) Print(HError, "Number of SubJets", SubJets.size());
    fastjet::PseudoJet SubJet1 = SubJets[0];
    fastjet::PseudoJet SubJet2 = SubJets[1];

    if (SubJet1.rap() < SubJet2.rap()) {

        SetRapPhi(SubJet1, SubJet2);

    } else {

        SetRapPhi(SubJet2, SubJet1);

    }

    DeltaR12 = SubJet1.delta_R(SubJet2);

    HJets Constituents = FilterJet.constituents();
    Print(HDebug, "Number of Constituents", Constituents.size());
    for (unsigned ConstituentNumber = 0; ConstituentNumber < Constituents.size(); ConstituentNumber++) {

        fastjet::PseudoJet Constituent = Constituents[ConstituentNumber];

        Rap0 = Constituent.rap();
        Phi0 = Constituent.phi_std();

        DeltaR01 = Constituent.delta_R(SubJet1);
        DeltaR02 = Constituent.delta_R(SubJet2);

        float DeltaR1 = GetSubDeltaR();

        if (Phi0 < 0) {

            Phi0 = Phi0 + 2 * TMath::Pi();

        } else {

            Phi0 = Phi0 - 2 * TMath::Pi();

        }

        float DeltaR2 = GetSubDeltaR();

        float ConeSize = sqrt(2);

        if (DeltaR1 < DeltaR12 / ConeSize || DeltaR2 < DeltaR12 / ConeSize) {

            float DeltaR = std::min(DeltaR1, DeltaR2);
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

    return DiPolarity;

}

void hdelphes::HHiggsTagger::SetRapPhi(fastjet::PseudoJet &SubJet1, fastjet::PseudoJet &SubJet2)
{
    Print(HInformation, "SetRapPhi");

    Rap1 = SubJet1.rap();
    Phi1 = SubJet1.phi_std();
    Rap2 = SubJet2.rap();
    Phi2 = SubJet2.phi_std();

}

float hdelphes::HHiggsTagger::GetSubDeltaR()
{

    Print(HInformation, "GetSubDeltaR");

    float SubDeltaR;

    float DeltaR = std::abs(DeltaPhiRap0() + DeltaRapPhi0() + RapPhi()) / DeltaR12;
    float Rap = - (DeltaPhi() * RapPhi() - DeltaRapSqr() * Rap0 + DeltaPhi() * DeltaRapPhi0()) / DeltaR12Sqr();
    float Phi = - (DeltaRap() * RapPhi() + DeltaRap() * DeltaPhiRap0() - DeltaPhiSqr() * Phi0) / DeltaR12Sqr();

    if ((Rap >= Rap1 && Rap <= Rap2 && Phi >= Phi1 && Phi <= Phi2)
            || (Rap >= Rap1 && Rap <= Rap2 && Phi >= Phi2 && Phi <= Phi1)) {

        SubDeltaR = DeltaR;

    } else {

        SubDeltaR = std::min(DeltaR01, DeltaR02);

    }


    return SubDeltaR;
}
