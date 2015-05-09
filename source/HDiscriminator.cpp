# include "HDiscriminator.hh"

hanalysis::HDiscriminator::HDiscriminator()
{

    Print(HNotification, "Constructor");

//     DebugLevel = 5;

}

hanalysis::HDiscriminator::~HDiscriminator()
{

    Print(HNotification, "Destructor");

}

Jets hanalysis::HDiscriminator::GetCandidateJets(const Jets &EFlowJets, const float ScalarHt)
{

    Print(HInformation, "Get Tagged Candidate Jets", EFlowJets.size());

    const Jets jets;

    if (EFlowJets.size() == 0) {

        Print(HInformation, "No EFlow Jets");
        return jets;

    }

    const float DeltaR = 750. / ScalarHt;

    const fastjet::JetAlgorithm FatJetAlgorithm = fastjet::cambridge_algorithm;
    const fastjet::JetDefinition FatJetDefinition(FatJetAlgorithm, DeltaR);
    const Jets FatJets = GetFatJets(EFlowJets, FatJetDefinition);

    Jets MassDropJets = GetMassDropJets(FatJets);
//     Jets MassDropJets = GetSubJetTaggedJets(FatJets);

    MassDropJets.erase(std::remove_if(MassDropJets.begin(), MassDropJets.end(), JetIsBad), MassDropJets.end());

    std::sort(MassDropJets.begin(), MassDropJets.end(), SortJetByMass());

    MassDropJets = GetFatJetTag(MassDropJets);

    return MassDropJets;

}


Jets hanalysis::HDiscriminator::GetCandidateJetsForced(const Jets &EFlowJets, const float ScalarHt)
{

    Print(HInformation, "Get Tagged Candidate Jets", EFlowJets.size());

    const Jets jets;

    if (EFlowJets.size() == 0) {

        Print(HInformation, "No EFlow Jets");
        return jets;

    }

//     float DeltaR = 1000. / ScalarHt;
    float DeltaR = 750. / ScalarHt;
    const fastjet::JetAlgorithm FatJetAlgorithm = fastjet::cambridge_algorithm;
    Jets MassDropJets;

    while (MassDropJets.empty() && DeltaR < 7) {

        const fastjet::JetDefinition FatJetDefinition(FatJetAlgorithm, DeltaR);
        const Jets FatJets = GetFatJets(EFlowJets, FatJetDefinition);

        MassDropJets = GetMassDropJets(FatJets);
        MassDropJets.erase(std::remove_if(MassDropJets.begin(), MassDropJets.end(), JetIsBad), MassDropJets.end());

        DeltaR += .25;
    }

    std::sort(MassDropJets.begin(), MassDropJets.end(), SortJetByMass());

    MassDropJets = GetFatJetTag(MassDropJets);

    return MassDropJets;

}


bool hanalysis::HDiscriminator::JetIsBad(const fastjet::PseudoJet &Jet)
{

    HObject Object;

    if (std::abs(Jet.m()) <= 40.) {

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
