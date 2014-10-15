# include "HReconstruction.hh"

HReconstruction::HReconstruction()
{

    Print(1, "Constructor");
    
//     DebugLevel = 4;

}

HReconstruction::~HReconstruction()
{

    Print(1, "Destructor");

}

void HReconstruction::NewEvent()
{

    Print(2, "New Event");

//     FatJetVector.clear();

}

vector<PseudoJet> HReconstruction::GetFatJets(const vector<PseudoJet> &EFlowJetVector) const
{

    // FatJetCylinderDistanceMax = Jing: 1.4; fastjet: 1.2; paper: 1.2
    const float DeltaR = 1.2;
    const fastjet::JetAlgorithm FatJetAlgorithm = fastjet::cambridge_algorithm;

    const fastjet::JetDefinition FatJetDefinition(FatJetAlgorithm, DeltaR);

    return GetFatJets(EFlowJetVector, FatJetDefinition);

}

vector<PseudoJet> HReconstruction::GetFatJets(const vector<PseudoJet> &EFlowJetVector, const fastjet::JetDefinition &FatJetDefinition) const
{

    Print(2, "Get Fat Jet Vector",FatJetDefinition.R());
       

    fastjet::ClusterSequence *const FatJetClusterSequence = new fastjet::ClusterSequence(EFlowJetVector, FatJetDefinition);

    // FatJetPtMin = Jing: 40; fastjet: 0
    const float FatJetPtMin = 0;
    const vector<PseudoJet> FatJetVector = FatJetClusterSequence->inclusive_jets(FatJetPtMin);

    if (!FatJetVector.empty()) FatJetClusterSequence->delete_self_when_unused();

    return FatJetVector;
    
}


vector<PseudoJet> HReconstruction::GetMassDropJets(const vector<PseudoJet> &FatJetVector) const
{

    Print(2, "Get Mass Drop Jet Vector", FatJetVector.size());
    
    vector<PseudoJet> MassDropVector;

    for (auto & FatJet : FatJetVector) {

        MassDropVector.push_back(GetMassDropJet(FatJet));

    }
    
    return MassDropVector;
    
}

PseudoJet HReconstruction::GetMassDropJet(const PseudoJet &FatJet) const
{

//     Print(3, "Get Mass Drop Jet");

    //     MassDropMin = Jing: 0.667; fastjet: 0.67; Paper: 0.67
    const float MassDropMin = 0.67;
    //     AsymmetryCut = Jing: 0.09; fastjet: 0.09; paper: 0.09
    const float AsymmetryCut = 0.09;

    return GetMassDropJet(FatJet, MassDropMin, AsymmetryCut);

}



PseudoJet HReconstruction::GetMassDropJet(const PseudoJet &FatJet, const float MassDropMin, const float AsymmetryCut) const
{

    Print(3, "Get Mass Drop Jet");

    const fastjet::MassDropTagger FatJetMassDroppTagger(MassDropMin, AsymmetryCut);
    const PseudoJet MassDropJet = FatJetMassDroppTagger(FatJet);
     

    
    return MassDropJet;

}

bool HReconstruction::JetIsBad(const PseudoJet &Jet)
{

    HObject Object;

    if (fabs(Jet.m()) <= 10) {

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



vector<PseudoJet> HReconstruction::GetFatJetTag(vector<PseudoJet>& FatJetVector)
{

    Print(2, "Get Fat Jet Tag",FatJetVector.size());

    for (auto & FatJet : FatJetVector) {

        HJetInfo JetInfo;

        for (const auto & Constituent : FatJet.constituents()) {

            JetInfo.AddConstituent(Constituent.user_index(), Constituent.pt());

        }

        FatJet.set_user_info(new HJetInfo(JetInfo));
        FatJet.set_user_index(FatJet.user_info<HJetInfo>().GetMaximalId());
        if(DebugLevel>=4) FatJet.user_info<HJetInfo>().PrintAllInfos();

        Print(4, "Tag", FatJet.user_info<HJetInfo>().GetMaximalId(), FatJet.user_info<HJetInfo>().GetMaximalFraction(),FatJet.m());

    }
    
    return FatJetVector;

}
