# include "HMva.hh"

hanalysis::HMva::HMva()
{
    Print(HInformation, "Constructor");
    CutMethodName = "Cut";
    BdtMethodName = "Bdt";
    Cut = "";
    WeightBranchName = "Info";
    MaxCombi = 4;
    MinCellResolution = .1;
}

hanalysis::HMva::~HMva()
{
    Print(HInformation, "Destructor");
}

float hanalysis::HMva::GetBdt(TObject *, const TMVA::Reader &)
{

    Print(HError, "Get Bdt", "should be implemented somewhere else");

    return 0;

}

HJets hanalysis::HMva::GetGranulatedJets(HJets &EFlowJets)
{
    // start of granularization of the hadronic calorimeter to redefine hadrons
    const float CellDeltaRap = 0.1;
    const float CellDeltaPhi = 0.1;
    const float PtCutOff = 0.5;

    HJets GranulatedJets;

    EFlowJets = sorted_by_pt(EFlowJets);
    GranulatedJets.push_back(EFlowJets[0]);

    for (unsigned i = 1; i < EFlowJets.size(); ++i) {
        int NewJet = 0;

        for (unsigned j = 0; j < GranulatedJets.size(); ++j) {

            const float CellDiffRap = std::abs(EFlowJets[i].pseudorapidity() - GranulatedJets[j].pseudorapidity()) / CellDeltaRap;
            float CellDiffPhi = std::abs(EFlowJets[i].phi() - GranulatedJets[j].phi());
            if (CellDiffPhi > Pi) CellDiffPhi = TwoPi - CellDiffPhi;
            CellDiffPhi = CellDiffPhi / CellDeltaPhi;

            if (CellDiffRap < 1 && CellDiffPhi < 1) {

                NewJet = 1;

                const float TotalEnergy  = EFlowJets[i].e() + GranulatedJets[j].e();
                const float RescaleFactor = sqrt(pow(EFlowJets[i].px() + GranulatedJets[j].px(), 2) + pow(EFlowJets[i].py() + GranulatedJets[j].py(), 2) + pow(EFlowJets[i].pz() + GranulatedJets[j].pz(), 2));
                const float RescaledPx = TotalEnergy * (EFlowJets[i].px() + GranulatedJets[j].px()) / RescaleFactor;
                const float RescaledPy = TotalEnergy * (EFlowJets[i].py() + GranulatedJets[j].py()) / RescaleFactor;
                const float RescaledPz = TotalEnergy * (EFlowJets[i].pz() + GranulatedJets[j].pz()) / RescaleFactor;

                fastjet::PseudoJet CombinedJet(RescaledPx, RescaledPy, RescaledPz, TotalEnergy);

//                 CombinedJet.set_user_index(EFlowJets[i].user_index() + GranulatedJets[j].user_index());


                std::vector<HConstituent> Constituents;
                std::vector<HConstituent> NewConstituents = EFlowJets[i].user_info<hanalysis::HJetInfo>().Constituents();
                Constituents.insert(Constituents.end(), NewConstituents.begin(), NewConstituents.end());
                NewConstituents = GranulatedJets[j].user_info<hanalysis::HJetInfo>().Constituents();
                Constituents.insert(Constituents.end(), NewConstituents.begin(), NewConstituents.end());

//                 for (const auto & Constituent : EFlowJets[i].constituents()) {
//                   std::vector<HConstituent> NewConstituents =Constituent .user_info<hanalysis::HJetInfo>().Constituents();
//                   Constituents.insert(Constituents.end(), NewConstituents.begin(), NewConstituents.end());
//                 }
//                 for (const auto & Constituent : GranulatedJets[j].constituents()) {
//                   std::vector<HConstituent> NewConstituents = Constituent.user_info<hanalysis::HJetInfo>().Constituents();
//                   Constituents.insert(Constituents.end(), NewConstituents.begin(), NewConstituents.end());
//                 }
                CombinedJet.set_user_info(new HJetInfo(Constituents));

                GranulatedJets.erase(GranulatedJets.begin() + j);
                GranulatedJets.push_back(CombinedJet);
                break;

            }
        }

        if (NewJet != 1) {
            GranulatedJets.push_back(EFlowJets[i]);
            GranulatedJets = sorted_by_pt(GranulatedJets);
        }
    }


    for (unsigned ii = 0; ii < GranulatedJets.size(); ++ii) {

        if ((GranulatedJets[ii].perp() < PtCutOff)) {
            GranulatedJets.erase(GranulatedJets.begin() + ii);
            --ii;
        }
    }

    return GranulatedJets;

}

HJets hanalysis::HMva::GetJets(hanalysis::HEvent *const Event, HJetTag &JetTag)
{

    HJets EFlowJets = Event->GetJets()->GetStructuredEFlowJets();
    HJets GranulatedJets = GetGranulatedJets(EFlowJets);
    Print(HInformation,"Jets",GranulatedJets.size());
    fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(GranulatedJets, fastjet::JetDefinition(fastjet::cambridge_algorithm, 0.4));
    HJets Jets = fastjet::sorted_by_pt(ClusterSequence->inclusive_jets(40));
    if (Jets.size() < 1) {
        delete ClusterSequence;
        return Jets;
    }
    ClusterSequence->delete_self_when_unused();
    for (auto & Jet : Jets) {
        std::vector<HConstituent> Constituents;
        for (const auto & Constituent : Jet.constituents()) {
            std::vector<HConstituent> NewConstituents = Constituent.user_info<HJetInfo>().Constituents();
            Constituents.insert(Constituents.end(), NewConstituents.begin(), NewConstituents.end());
        }
        Jet.set_user_info(new HJetInfo(Constituents));
    }
    return Jets;
}

HJets hanalysis::HMva::GetJets(hanalysis::HEvent *const Event)
{

  HJets EFlowJets = Event->GetJets()->GetStructuredEFlowJets();
  HJets GranulatedJets = GetGranulatedJets(EFlowJets);
  Print(HInformation,"Jets",GranulatedJets.size());
  fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(GranulatedJets, fastjet::JetDefinition(fastjet::cambridge_algorithm, 0.4));
  HJets Jets = fastjet::sorted_by_pt(ClusterSequence->inclusive_jets(40));
  if (Jets.size() < 1) {
    delete ClusterSequence;
    return Jets;
  }
  ClusterSequence->delete_self_when_unused();
  for (auto & Jet : Jets) {
    std::vector<HConstituent> Constituents;
    for (const auto & Constituent : Jet.constituents()) {
      std::vector<HConstituent> NewConstituents = Constituent.user_info<HJetInfo>().Constituents();
      Constituents.insert(Constituents.end(), NewConstituents.begin(), NewConstituents.end());
    }
    Jet.set_user_info(new HJetInfo(Constituents));
  }
  return Jets;
}

HJets hanalysis::HMva::GetJets(hanalysis::HEvent &Event)
{

  HJets EFlowJets = Event.GetJets()->GetStructuredEFlowJets();
  HJets GranulatedJets = GetGranulatedJets(EFlowJets);
  Print(HInformation,"Jets",GranulatedJets.size());
  fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(GranulatedJets, fastjet::JetDefinition(fastjet::cambridge_algorithm, 0.4));
  HJets Jets = fastjet::sorted_by_pt(ClusterSequence->inclusive_jets(40));
  if (Jets.size() < 1) {
    delete ClusterSequence;
    return Jets;
  }
  ClusterSequence->delete_self_when_unused();
  for (auto & Jet : Jets) {
    std::vector<HConstituent> Constituents;
    for (const auto & Constituent : Jet.constituents()) {
      std::vector<HConstituent> NewConstituents = Constituent.user_info<HJetInfo>().Constituents();
      Constituents.insert(Constituents.end(), NewConstituents.begin(), NewConstituents.end());
    }
    Jet.set_user_info(new HJetInfo(Constituents));
  }
  return Jets;
}
