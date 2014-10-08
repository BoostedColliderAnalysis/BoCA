# include "HReconstruction.hh"

HReconstruction::HReconstruction()
{

  Print(1, "Constructor");

}

HReconstruction::~HReconstruction()
{

  Print(1, "Destructor");

}

void HReconstruction::NewEvent()
{

  Print(2, "New Event");

  FatJetVector.clear();

}

void HReconstruction::GetFatJetVector(const vector<PseudoJet>& EFlowJetVector)
{

  // FatJetCylinderDistanceMax = Jing: 1.4; fastjet: 1.2; paper: 1.2
  const float DeltaR = 1.2;
  const fastjet::JetAlgorithm FatJetAlgorithm = fastjet::cambridge_algorithm;

  const fastjet::JetDefinition FatJetDefinition(FatJetAlgorithm, DeltaR);

  GetFatJetVector(EFlowJetVector, FatJetDefinition);

}

void HReconstruction::GetFatJetVector(const vector<PseudoJet>& EFlowJetVector, const fastjet::JetDefinition& FatJetDefinition)
{

  Print(2, "Get Fat Jet Vector");

  fastjet::ClusterSequence *FatJetClusterSequence = new fastjet::ClusterSequence(EFlowJetVector, FatJetDefinition);

  // FatJetPtMin = Jing: 40; fastjet: 0
  const float FatJetPtMin = 0;
  FatJetVector = FatJetClusterSequence->inclusive_jets(FatJetPtMin);

  Print(3, "Number of Fat Jets", FatJetVector.size());

  if (FatJetVector.size() > 0) FatJetClusterSequence->delete_self_when_unused();

}


void HReconstruction::GetMassDropVector()
{

    Print(2, "Get Mass Drop Jet Vector");

    for (unsigned FatJetNumber = 0; FatJetNumber < FatJetVector.size(); ++FatJetNumber) {

        FatJetVector[FatJetNumber] = GetMassDropJet(FatJetVector[FatJetNumber]);

    }

    FatJetVector.erase(std::remove_if(FatJetVector.begin(), FatJetVector.end(), JetIsBad), FatJetVector.end());


}

PseudoJet HReconstruction::GetMassDropJet(const PseudoJet& FatJet)
{

    Print(3, "Get Mass Drop Jet");

    //     MassDropMin = Jing: 0.667; fastjet: 0.667; Paper: 0.67
    const float MassDropMin = 0.667;
    //     AsymmetryCut = Jing: 0.09; fastjet: 0.09; paper: 0.09
    const float AsymmetryCut = 0.09;

    return GetMassDropJet(FatJet, MassDropMin, AsymmetryCut);

}



PseudoJet HReconstruction::GetMassDropJet(const PseudoJet& FatJet, float MassDropMin, float AsymmetryCut)
{

    Print(3, "Get Mass Drop Jet");

    fastjet::MassDropTagger FatJetMassDroppTagger(MassDropMin, AsymmetryCut);
    PseudoJet MassDropJet = FatJetMassDroppTagger(FatJet);

    return MassDropJet;

}

bool HReconstruction::JetIsBad(const PseudoJet &Jet)
{

    if (fabs(Jet.m()) <= 0) {

//         Print(2, "Fat Jet Mass", Jet.m());
        return 1;

    }


    if (Jet.pieces().size() != 2) {

//         Print(2, "Pieces Sum", Jet.pieces().size());
        return 1;

    }

    if (!Jet.has_structure()) {

//         Print(2, "PseudoJet has no structure");
        return 1;

    }

    return 0;

}



void HReconstruction::GetFatJetTag()
{

    Print(2, "Get Fat Jet Tag");

    HJetInfo JetInfo;

    for (unsigned FatJetNumber = 0; FatJetNumber < FatJetVector.size(); ++FatJetNumber) {

        Print(2, "Fat Jet", FatJetNumber);

        const vector<PseudoJet> ConstituentsVector = FatJetVector[FatJetNumber].constituents();

        for (unsigned ConstituentsNumber = 0; ConstituentsNumber < ConstituentsVector.size(); ++ConstituentsNumber) {

            const int ConstituentId = ConstituentsVector[ConstituentsNumber].user_index();
            const float ConstituentPt = ConstituentsVector[ConstituentsNumber].pt();

            JetInfo.AddConstituent(ConstituentId, ConstituentPt);

        }

        FatJetVector[FatJetNumber].set_user_info(new HJetInfo(JetInfo));

        FatJetVector[FatJetNumber].set_user_index(FatJetVector[FatJetNumber].user_info<HJetInfo>().GetMaximalId());

        //         FatJetVector[FatJetNumber].user_info<HJetInfo>().PrintAllInfos();

        Print(4, "Tag", FatJetVector[FatJetNumber].user_info<HJetInfo>().GetMaximalId(), FatJetVector[FatJetNumber].user_info<HJetInfo>().GetMaximalFraction());

        JetInfo.Clear();

    }

    //     Print(0, "");


}
