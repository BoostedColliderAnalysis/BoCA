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

    GotJets = 0;

    GotEFlow = 0;

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

bool hanalysis::HJet::GetJets(const hanalysis::HJet::HJetDetails JetDetails)
{

    Print(0, "Get Jets", "No Jets", JetDetails);

    return 0;

}

bool hanalysis::HJet::GetEFlow(const hanalysis::HJet::HJetDetails JetDetails)
{

    Print(0, "Get EFlow", "No EFlow", JetDetails);

    return 0;

}

void hanalysis::HJet::GetGenJet()
{

    Print(0, "Get Gen Jets", "No Gen Jets");

}

float hanalysis::HJet::GetScalarHt()
{

    Print(0, "Get Scalar Ht", "No Scalar Ht");

    return 0;

}
