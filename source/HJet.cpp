# include "HJet.hh"

hanalysis::HJet::HJet()
{
//     DebugLevel = kDebug;
    Print(kNotification, "Constructor");
}

void hanalysis::HJet::Newevent(const hanalysis::ClonesArrays &NewClonesArrays)
{

    Print(kInformation, "New event");

    hanalysis::HFourVector::Newevent(NewClonesArrays);

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

bool hanalysis::HJet::GetJets(const hanalysis::HJet::HJetDetails JetDetails)
{
    Print(kError, "Get Jets", "No Jets", JetDetails);
    return 0;
}

bool hanalysis::HJet::GetEFlow(const hanalysis::HJet::HJetDetails JetDetails)
{

    Print(kError, "Get EFlow", "No EFlow", JetDetails);

    return 0;

}

void hanalysis::HJet::GetGenJet()
{

    Print(kError, "Get Gen Jets", "No Gen Jets");

}

float hanalysis::HJet::GetScalarHt()
{

    Print(kError, "Get Scalar Ht", "No Scalar Ht");

    return 0;

}

fastjet::PseudoJet hanalysis::HJet::GetMissingEt()
{

    Print(kError, "Get Missing Et", "No Mising Et");

    fastjet::PseudoJet Jet;
    return Jet;

}
