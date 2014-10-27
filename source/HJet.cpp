# include "HJet.hh"

hanalysis::HJet::HJet()
{

    Print(1, "Constructor");

}

hanalysis::HJet::~HJet()
{

    Print(1, "Destructor");

}

void hanalysis::HJet::NewEvent(const HClonesArray *const NewClonesArrays)
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

bool hanalysis::HJet::GetJets(const HJetDetails JetDetails)
{

    Print(1, "Get Jets", "No Jets", JetDetails);

    return 0;

}

bool hanalysis::HJet::ReadEFlow(const HJetDetails JetDetails)
{

    Print(1, "Get EFlow", "No EFlow", JetDetails);

    return 0;

}

void hanalysis::HJet::GetGenJet()
{

    Print(1, "Get Gen Jets", "No Gen Jets");

}

float hanalysis::HJet::GetScalarHt()
{

    Print(1, "Get Scalar Ht", "No Scalar Ht");

    return 0;

}
