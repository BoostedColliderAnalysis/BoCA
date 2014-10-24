# include "HJet.hh"

Analysis::HJet::HJet()
{

    Print(1, "Constructor");

}

Analysis::HJet::~HJet()
{

    Print(1, "Destructor");

}

void Analysis::HJet::NewEvent(const HClonesArray *const NewClonesArrays)
{

    Print(2, "New Event");

    ClonesArrays = NewClonesArrays;

    JetLorentzVectors.clear();

    TauLorentzVectors.clear();

    AntiTauLorentzVectors.clear();

    BottomLorentzVectors.clear();

    EFlowJets.clear();

    BottomJets.clear();

    CharmJets.clear();

    GenJets.clear();

    Jets.clear();

}

bool Analysis::HJet::GetJets(const HJetDetails JetDetails)
{

    Print(1, "Get Jets", "No Jets", JetDetails);

    return 0;

}

bool Analysis::HJet::ReadEFlow(const HJetDetails JetDetails)
{

    Print(1, "Get EFlow", "No EFlow", JetDetails);

    return 0;

}

void Analysis::HJet::GetGenJet()
{

    Print(1, "Get Gen Jets", "No Gen Jets");

}

float Analysis::HJet::GetScalarHt()
{

    Print(1, "Get Scalar Ht", "No Scalar Ht");

    return 0;

}
