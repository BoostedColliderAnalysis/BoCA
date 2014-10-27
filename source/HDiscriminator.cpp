# include "HDiscriminator.hh"

hanalysis::HDiscriminator::HDiscriminator()
{

    Print(1, "Constructor");

//     DebugLevel = 5;

}

hanalysis::HDiscriminator::~HDiscriminator()
{

    Print(1, "Destructor");

}

vector<PseudoJet> hanalysis::HDiscriminator::GetCandidateJets(const vector<PseudoJet> &EFlowJets, const float ScalarHt)
{

    Print(2, "Get Tagged Candidate Jets", EFlowJets.size());

    const vector<PseudoJet> Jets;

    if (EFlowJets.size() == 0) {

        Print(2, "No EFlow Jets");
        return Jets;

    }

    const float DeltaR = 1000. / ScalarHt;

    const fastjet::JetAlgorithm FatJetAlgorithm = fastjet::cambridge_algorithm;
    const fastjet::JetDefinition FatJetDefinition(FatJetAlgorithm, DeltaR);
    const vector<PseudoJet> FatJets = GetFatJets(EFlowJets, FatJetDefinition);

    vector<PseudoJet> MassDropJets = GetMassDropJets(FatJets);
//     vector<PseudoJet> MassDropJets = GetSubJetTaggedJets(FatJets);

    MassDropJets.erase(std::remove_if(MassDropJets.begin(), MassDropJets.end(), JetIsBad), MassDropJets.end());

    sort(MassDropJets.begin(), MassDropJets.end(), SortJetByMass());

    MassDropJets = GetFatJetTag(MassDropJets);

    return MassDropJets;

}


vector<PseudoJet> hanalysis::HDiscriminator::GetCandidateJetsForced(const vector<PseudoJet> &EFlowJets, const float ScalarHt)
{

    Print(2, "Get Tagged Candidate Jets", EFlowJets.size());

    const vector<PseudoJet> Jets;

    if (EFlowJets.size() == 0) {

        Print(2, "No EFlow Jets");
        return Jets;

    }

//     float DeltaR = 1000. / ScalarHt;
    float DeltaR = 750. / ScalarHt;
    const fastjet::JetAlgorithm FatJetAlgorithm = fastjet::cambridge_algorithm;
    vector<PseudoJet> MassDropJets;

    while (MassDropJets.size() < 1 && DeltaR < 7) {

        const fastjet::JetDefinition FatJetDefinition(FatJetAlgorithm, DeltaR);
        const vector<PseudoJet> FatJets = GetFatJets(EFlowJets, FatJetDefinition);

        MassDropJets = GetMassDropJets(FatJets);
        MassDropJets.erase(std::remove_if(MassDropJets.begin(), MassDropJets.end(), JetIsBad), MassDropJets.end());

        DeltaR += .25;
    }

    sort(MassDropJets.begin(), MassDropJets.end(), SortJetByMass());

    MassDropJets = GetFatJetTag(MassDropJets);

    return MassDropJets;

}


bool hanalysis::HDiscriminator::JetIsBad(const PseudoJet &Jet)
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
