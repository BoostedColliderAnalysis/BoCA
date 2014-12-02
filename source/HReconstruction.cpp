# include "HReconstruction.hh"

hanalysis::HReconstruction::HReconstruction()
{

    Print(HNotification, "Constructor");

//     DebugLevel = 4;

}

hanalysis::HReconstruction::~HReconstruction()
{

    Print(HNotification, "Destructor");

}

void hanalysis::HReconstruction::NewEvent()
{

    Print(HInformation, "New Event");

//     FatJetVector.clear();

}

HJets hanalysis::HReconstruction::GetFatJets(const HJets &EFlowJets) const
{

    // FatJetCylinderDistanceMax = Jing: 1.4; fastjet: 1.2; paper: 1.2
    const float DeltaR = 1.2;
    const fastjet::JetAlgorithm FatJetAlgorithm = fastjet::cambridge_algorithm;

    const fastjet::JetDefinition FatJetDefinition(FatJetAlgorithm, DeltaR);

    return GetFatJets(EFlowJets, FatJetDefinition);

}

HJets hanalysis::HReconstruction::GetFatJets(const HJets &EFlowJets, const fastjet::JetDefinition &FatJetDefinition) const
{

    Print(HInformation, "Get Fat Jet Vector", FatJetDefinition.R());


    fastjet::ClusterSequence *const FatJetClusterSequence = new fastjet::ClusterSequence(EFlowJets, FatJetDefinition);

    // FatJetPtMin = Jing: 40; fastjet: 0
    const float FatJetPtMin = 0;
    const HJets FatJets = FatJetClusterSequence->inclusive_jets(FatJetPtMin);

    if (!FatJets.empty()) FatJetClusterSequence->delete_self_when_unused();

    return FatJets;

}


HJets hanalysis::HReconstruction::GetMassDropJets(const HJets &FatJets) const
{

    Print(HInformation, "Get Mass Drop Jets", FatJets.size());

    HJets MassDropJets;

    for (auto & FatJet : FatJets) {

        MassDropJets.push_back(GetMassDropJet(FatJet));

    }

    return MassDropJets;

}

fastjet::PseudoJet hanalysis::HReconstruction::GetMassDropJet(const fastjet::PseudoJet &FatJet) const
{

//     Print(HDebug, "Get Mass Drop Jet");

    //     MassDropMin = Jing: 0.667; fastjet: 0.67; Paper: 0.67
    const float MassDropMin = 0.67;
    //     AsymmetryCut = Jing: 0.09; fastjet: 0.09; paper: 0.09
    const float AsymmetryCut = 0.09;

    return GetMassDropJet(FatJet, MassDropMin, AsymmetryCut);

}



fastjet::PseudoJet hanalysis::HReconstruction::GetMassDropJet(const fastjet::PseudoJet &FatJet, const float MassDropMin, const float AsymmetryCut) const
{

    Print(HDebug, "Get Mass Drop Jet");

    const fastjet::MassDropTagger FatJetMassDroppTagger(MassDropMin, AsymmetryCut);
    const fastjet::PseudoJet MassDropJet = FatJetMassDroppTagger(FatJet);



    return MassDropJet;

}




HJets hanalysis::HReconstruction::GetSubJetTaggedJets(const HJets &FatJets) const
{

    Print(HInformation, "Get Sub Jet Tagged Jets", FatJets.size());

    HJets SubJetTaggedJets;

    for (auto & FatJet : FatJets) {

        SubJetTaggedJets.push_back(GetSubJetTaggedJet(FatJet));

    }

    return SubJetTaggedJets;

}

fastjet::PseudoJet hanalysis::HReconstruction::GetSubJetTaggedJet(const fastjet::PseudoJet &FatJet) const
{

    Print(HDebug, "Get Mass Drop Jet");

    const fastjet::CASubJetTagger SubJetTagger;
    const fastjet::PseudoJet MassDropJet = SubJetTagger.result(FatJet);



    return MassDropJet;

}


bool hanalysis::HReconstruction::JetIsBad(const fastjet::PseudoJet &Jet)
{

    HObject Object;

    if (std::abs(Jet.m()) <= 40) {

        Object.Print(HInformation, "Fat Jet Mass", Jet.m());
        return 1;

    }


    if (Jet.pieces().size() != 2) {

        Object.Print(HNotification, "Pieces Sum", Jet.pieces().size());
        return 1;

    }

    if (!Jet.has_structure()) {

        Object.Print(HNotification, "fastjet::PseudoJet has no structure");
        return 1;

    }

    return 0;

}



HJets hanalysis::HReconstruction::GetFatJetTag(HJets &FatJets)
{

    Print(HInformation, "Get Fat Jet Tag", FatJets.size());

    for (auto & FatJet : FatJets) {

        hanalysis::HJetInfo JetInfo;

        for (const auto & Constituent : FatJet.constituents()) {

            if (Constituent.has_user_info()) {

              std::map<int, float> JetFractions = Constituent.user_info<hanalysis::HJetInfo>().GetJetFractions();

              for (std::map<int, float>::const_iterator Pair = JetFractions.begin(); Pair != JetFractions.end(); ++Pair) {

                    JetInfo.AddConstituent((*Pair).first, (*Pair).second * Constituent.pt());

                }

                Constituent.user_info<hanalysis::HJetInfo>().PrintAllInfos(HDetailed);
            } else {

            Print(HDebug,"Constituent index",Constituent.user_index());

            JetInfo.AddConstituent(Constituent.user_index(), Constituent.pt());

            }

        }

        FatJet.set_user_info(new hanalysis::HJetInfo(JetInfo));

        FatJet.set_user_index(FatJet.user_info<hanalysis::HJetInfo>().GetMaximalId());

        FatJet.user_info<hanalysis::HJetInfo>().PrintAllInfos(HDetailed);

        Print(HDetailed, "Tag", FatJet.user_info<hanalysis::HJetInfo>().GetMaximalId(), FatJet.user_info<hanalysis::HJetInfo>().GetMaximalFraction(), FatJet.m());

    }

    return FatJets;

}
