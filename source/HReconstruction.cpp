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

vector<PseudoJet> HReconstruction::GetFatJets(const vector<PseudoJet> &EFlowJets) const
{

    // FatJetCylinderDistanceMax = Jing: 1.4; fastjet: 1.2; paper: 1.2
    const float DeltaR = 1.2;
    const fastjet::JetAlgorithm FatJetAlgorithm = fastjet::cambridge_algorithm;

    const fastjet::JetDefinition FatJetDefinition(FatJetAlgorithm, DeltaR);

    return GetFatJets(EFlowJets, FatJetDefinition);

}

vector<PseudoJet> HReconstruction::GetFatJets(const vector<PseudoJet> &EFlowJets, const fastjet::JetDefinition &FatJetDefinition) const
{

    Print(2, "Get Fat Jet Vector", FatJetDefinition.R());


    fastjet::ClusterSequence *const FatJetClusterSequence = new fastjet::ClusterSequence(EFlowJets, FatJetDefinition);

    // FatJetPtMin = Jing: 40; fastjet: 0
    const float FatJetPtMin = 0;
    const vector<PseudoJet> FatJets = FatJetClusterSequence->inclusive_jets(FatJetPtMin);

    if (!FatJets.empty()) FatJetClusterSequence->delete_self_when_unused();

    return FatJets;

}


vector<PseudoJet> HReconstruction::GetMassDropJets(const vector<PseudoJet> &FatJets) const
{

    Print(2, "Get Mass Drop Jets", FatJets.size());

    vector<PseudoJet> MassDropJets;

    for (auto & FatJet : FatJets) {

        MassDropJets.push_back(GetMassDropJet(FatJet));

    }

    return MassDropJets;

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




vector<PseudoJet> HReconstruction::GetSubJetTaggedJets(const vector<PseudoJet> &FatJets) const
{

    Print(2, "Get Sub Jet Tagged Jets", FatJets.size());

    vector<PseudoJet> SubJetTaggedJets;

    for (auto & FatJet : FatJets) {

        SubJetTaggedJets.push_back(GetSubJetTaggedJet(FatJet));

    }

    return SubJetTaggedJets;

}

PseudoJet HReconstruction::GetSubJetTaggedJet(const PseudoJet &FatJet) const
{

    Print(3, "Get Mass Drop Jet");

    const fastjet::CASubJetTagger SubJetTagger;
    const PseudoJet MassDropJet = SubJetTagger.result(FatJet);



    return MassDropJet;

}


bool HReconstruction::JetIsBad(const PseudoJet &Jet)
{

    HObject Object;

    if (fabs(Jet.m()) <= 40) {

        Object.Print(2, "Fat Jet Mass", Jet.m());
        return 1;

    }


    if (Jet.pieces().size() != 2) {

        Object.Print(1, "Pieces Sum", Jet.pieces().size());
        return 1;

    }

    if (!Jet.has_structure()) {

        Object.Print(1, "PseudoJet has no structure");
        return 1;

    }

    return 0;

}



vector<PseudoJet> HReconstruction::GetFatJetTag(vector<PseudoJet> &FatJets)
{

    Print(2, "Get Fat Jet Tag", FatJets.size());

    for (auto & FatJet : FatJets) {

        HJetInfo JetInfo;

        for (const auto & Constituent : FatJet.constituents()) {

            if (Constituent.has_user_info()) {

                map<int, float> JetFractions = Constituent.user_info<HJetInfo>().GetJetFractions();

                for (map<int, float>::const_iterator Pair = JetFractions.begin(); Pair != JetFractions.end(); ++Pair) {

                    JetInfo.AddConstituent((*Pair).first, (*Pair).second * Constituent.pt());

                }

                Constituent.user_info<HJetInfo>().PrintAllInfos(3);
            } else {

            Print(3,"Constituent index",Constituent.user_index());

            JetInfo.AddConstituent(Constituent.user_index(), Constituent.pt());
            
            }

        }

        FatJet.set_user_info(new HJetInfo(JetInfo));

        FatJet.set_user_index(FatJet.user_info<HJetInfo>().GetMaximalId());

        FatJet.user_info<HJetInfo>().PrintAllInfos(4);

        Print(4, "Tag", FatJet.user_info<HJetInfo>().GetMaximalId(), FatJet.user_info<HJetInfo>().GetMaximalFraction(), FatJet.m());

    }

    return FatJets;

}
