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

  fastjet::ClusterSequence * const FatJetClusterSequence = new fastjet::ClusterSequence(EFlowJetVector, FatJetDefinition);

  // FatJetPtMin = Jing: 40; fastjet: 0
  const float FatJetPtMin = 0;
  FatJetVector = FatJetClusterSequence->inclusive_jets(FatJetPtMin);

  Print(3, "Number of Fat Jets", FatJetVector.size());

  if (!FatJetVector.empty()) FatJetClusterSequence->delete_self_when_unused();

}


void HReconstruction::GetMassDropVector()
{

    Print(2, "Get Mass Drop Jet Vector");

    for (auto& FatJet : FatJetVector) {

        FatJet = GetMassDropJet(FatJet);

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



PseudoJet HReconstruction::GetMassDropJet(const PseudoJet& FatJet, const float MassDropMin, const float AsymmetryCut)
{

    Print(3, "Get Mass Drop Jet");

    const fastjet::MassDropTagger FatJetMassDroppTagger(MassDropMin, AsymmetryCut);
    const PseudoJet MassDropJet = FatJetMassDroppTagger(FatJet);

    return MassDropJet;

}

bool HReconstruction::JetIsBad(const PseudoJet &Jet)
{

    HObject Object;

    if (fabs(Jet.m()) <= 0) {

        Object.Print(2, "Fat Jet Mass", Jet.m());
        return 1;

    }


    if (Jet.pieces().size() != 2) {

        Object.Print(2, "Pieces Sum", Jet.pieces().size());
        return 1;

    }

    if (!Jet.has_structure()) {

        Object.Print(2, "PseudoJet has no structure");
        return 1;

    }

    return 0;

}



void HReconstruction::GetFatJetTag()
{

    Print(2, "Get Fat Jet Tag");


    for (auto& FatJet : FatJetVector) {

        const vector<PseudoJet> ConstituentsVector = FatJet.constituents();
        HJetInfo JetInfo;

        for (auto& Constituent : ConstituentsVector) {

            JetInfo.AddConstituent(Constituent.user_index(), Constituent.pt());

        }

        FatJet.set_user_info(new HJetInfo(JetInfo));
        FatJet.set_user_index(FatJet.user_info<HJetInfo>().GetMaximalId());
        //         FatJetVector[FatJetNumber].user_info<HJetInfo>().PrintAllInfos();

        Print(4, "Tag", FatJet.user_info<HJetInfo>().GetMaximalId(), FatJet.user_info<HJetInfo>().GetMaximalFraction());

    }

}
