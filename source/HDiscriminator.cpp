# include "HDiscriminator.hh"

analysis::HDiscriminator::HDiscriminator()
{

    Print(kNotification, "Constructor");

//     DebugLevel = 5;

}

analysis::HDiscriminator::~HDiscriminator()
{

    Print(kNotification, "Destructor");

}

Jets analysis::HDiscriminator::GetCandidateJets(const Jets &EFlowJets, const float ScalarHt)
{

    Print(kInformation, "Get Tagged Candidate Jets", EFlowJets.size());

    const Jets jets;

    if (EFlowJets.size() == 0) {

        Print(kInformation, "No EFlow Jets");
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


Jets analysis::HDiscriminator::GetCandidateJetsForced(const Jets &EFlowJets, const float ScalarHt)
{

    Print(kInformation, "Get Tagged Candidate Jets", EFlowJets.size());

    const Jets jets;

    if (EFlowJets.size() == 0) {

        Print(kInformation, "No EFlow Jets");
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


bool analysis::HDiscriminator::JetIsBad(const fastjet::PseudoJet &Jet)
{

    Object Object;

    if (std::abs(Jet.m()) <= 40.) {

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
