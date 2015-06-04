# include "HReconstruction.hh"

analysis::HReconstruction::HReconstruction()
{
    Print(kNotification, "Constructor");
//     DebugLevel = 4;
}

analysis::HReconstruction::~HReconstruction()
{
    Print(kNotification, "Destructor");
}

void analysis::HReconstruction::NewEvent()
{
    Print(kInformation, "New event");
//     FatJetVector.clear();
}

analysis::Jets analysis::HReconstruction::GetFatJets(const Jets &EFlowJets) const
{
    // FatJetCylinderDistanceMax = Jing: 1.4; fastjet: 1.2; paper: 1.2
    const float DeltaR = 1.2;
    const fastjet::JetAlgorithm FatJetAlgorithm = fastjet::cambridge_algorithm;
    const fastjet::JetDefinition FatJetDefinition(FatJetAlgorithm, DeltaR);
    return GetFatJets(EFlowJets, FatJetDefinition);
}

analysis::Jets analysis::HReconstruction::GetFatJets(const Jets &EFlowJets, const fastjet::JetDefinition &FatJetDefinition) const
{
    Print(kInformation, "Fat Jet Vector", FatJetDefinition.R());
    fastjet::ClusterSequence *const FatJetClusterSequence = new fastjet::ClusterSequence(EFlowJets, FatJetDefinition);
    // FatJetPtMin = Jing: 40; fastjet: 0
    const float FatJetPtMin = 0;
    const Jets FatJets = FatJetClusterSequence->inclusive_jets(FatJetPtMin);
    if (!FatJets.empty()) FatJetClusterSequence->delete_self_when_unused();
    return FatJets;
}


analysis::Jets analysis::HReconstruction::GetMassDropJets(const Jets &FatJets) const
{
    Print(kInformation, "Mass Drop Jets", FatJets.size());
    Jets MassDropJets;
    for (auto & FatJet : FatJets) {
        MassDropJets.emplace_back(GetMassDropJet(FatJet));
    }
    return MassDropJets;
}

fastjet::PseudoJet analysis::HReconstruction::GetMassDropJet(const fastjet::PseudoJet &FatJet) const
{
//     Print(kDebug, "Mass Drop Jet");
    //     MassDropMin = Jing: 0.667; fastjet: 0.67; Paper: 0.67
    const float MassDropMin = 0.67;
    //     AsymmetryCut = Jing: 0.09; fastjet: 0.09; paper: 0.09
    const float AsymmetryCut = 0.09;
    return GetMassDropJet(FatJet, MassDropMin, AsymmetryCut);
}



fastjet::PseudoJet analysis::HReconstruction::GetMassDropJet(const fastjet::PseudoJet &FatJet, const float MassDropMin, const float AsymmetryCut) const
{
    Print(kDebug, "Mass Drop Jet");
    const fastjet::MassDropTagger FatJetMassDroppTagger(MassDropMin, AsymmetryCut);
    const fastjet::PseudoJet MassDropJet = FatJetMassDroppTagger(FatJet);
    return MassDropJet;
}




analysis::Jets analysis::HReconstruction::GetSubjet_taggedJets(const Jets &FatJets) const
{
    Print(kInformation, "Sub Jet Tagged Jets", FatJets.size());
    Jets Subjet_taggedJets;
    for (auto & FatJet : FatJets) {
        Subjet_taggedJets.emplace_back(GetSubjet_taggedJet(FatJet));
    }
    return Subjet_taggedJets;
}

fastjet::PseudoJet analysis::HReconstruction::GetSubjet_taggedJet(const fastjet::PseudoJet &FatJet) const
{
    Print(kDebug, "Mass Drop Jet");
    const fastjet::CASubJetTagger Subjet_tagger;
    const fastjet::PseudoJet MassDropJet = Subjet_tagger.result(FatJet);
    return MassDropJet;
}


bool analysis::HReconstruction::JetIsBad(const fastjet::PseudoJet &Jet)
{
    Object Object;
    if (std::abs(Jet.m()) <= 40) {
        Object.Print(kInformation, "Fat Jet Mass", Jet.m());
        return 1;
    }
    if (Jet.pieces().size() != 2) {
        Object.Print(kNotification, "Pieces Sum", Jet.pieces().size());
        return 1;
    }
    if (!Jet.has_structure()) {
        Object.Print(kNotification, "fastjet::PseudoJet has no structure");
        return 1;
    }
    return 0;
}



analysis::Jets analysis::HReconstruction::GetFatjet_tag(Jets &FatJets)
{
    Print(kInformation, "Fat Jet Tag", FatJets.size());
    for (auto & FatJet : FatJets) {
        analysis::JetInfo jet_info;
        for (const auto & constituent : FatJet.constituents()) {
            if (constituent.has_user_info()) {
                jet_info.Addconstituents(constituent.user_info<analysis::JetInfo>().constituents());
//               std::map<int, float> JetFractions = constituent.user_info<analysis::JetInfo>().GetJetFractions();
//               for (std::map<int, float>::const_iterator Pair = JetFractions.begin(); Pair != JetFractions.end(); ++Pair) {
//                     jet_info.Addconstituent((*Pair).first, (*Pair).second * constituent.pt());
//                 }
//                 constituent.user_info<analysis::JetInfo>().PrintAllInfos(kDetailed);
            } else {
                Print(kError,"No info in constituent jet");
//             jet_info.Addconstituent(constituent.user_index(), constituent.pt());
            }
        }
        FatJet.set_user_info(new analysis::JetInfo(jet_info));
//         FatJet.set_user_index(FatJet.user_info<analysis::JetInfo>().MaximalId());
//         FatJet.user_info<analysis::JetInfo>().PrintAllInfos(kDetailed);
//         Print(kDetailed, "Tag", FatJet.user_info<analysis::JetInfo>().MaximalId(), FatJet.user_info<analysis::JetInfo>().MaximalFraction(), FatJet.m());
    }
    return FatJets;
}
