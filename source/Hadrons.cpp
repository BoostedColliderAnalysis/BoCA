# include "Hadrons.hh"

analysis::Hadrons::Hadrons()
{
//     DebugLevel = kDebug;
    Print(kNotification, "Constructor");
}

void analysis::Hadrons::NewEvent(const analysis::ClonesArrays &clones_arrays)
{
    Print(kInformation, "New event");
    analysis::FourVector::NewEvent(clones_arrays);
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
    jets_.clear();
}

bool analysis::Hadrons::GetJets(const analysis::Hadrons::JetDetail jet_detail)
{
    Print(kError, "Get Jets", "No Jets", jet_detail);
    return false;
}

bool analysis::Hadrons::GetEFlow(const analysis::Hadrons::JetDetail jet_detail)
{
    Print(kError, "Get EFlow", "No EFlow", jet_detail);
    return false;
}

void analysis::Hadrons::GetGenJet()
{
    Print(kError, "Get Gen Jets", "No Gen Jets");
}

float analysis::Hadrons::GetScalarHt()
{
    Print(kError, "Get Scalar Ht", "No Scalar Ht");
    return 0;
}

fastjet::PseudoJet analysis::Hadrons::GetMissingEt()
{
    Print(kError, "Get Missing Et", "No Mising Et");
    return fastjet::PseudoJet{};
}
