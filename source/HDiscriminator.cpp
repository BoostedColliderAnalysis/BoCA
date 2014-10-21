# include "HDiscriminator.hh"

HDiscriminator::HDiscriminator()
{

    Print(1, "Constructor");

//     DebugLevel = 5;

}

HDiscriminator::~HDiscriminator()
{

    Print(1, "Destructor");

}

vector<PseudoJet> HDiscriminator::GetCandidateJets(const vector<PseudoJet> &EFlowJets, const float ScalarHt)
{

    Print(2, "Get Tagged Candidate Jets",EFlowJets.size());

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
    
    MassDropJets.erase(std::remove_if(MassDropJets.begin(), MassDropJets.end(), JetIsBad), MassDropJets.end());

    sort(MassDropJets.begin(), MassDropJets.end(), SortJetByMass());
    MassDropJets = GetFatJetTag(MassDropJets);

    return MassDropJets;
    
}
