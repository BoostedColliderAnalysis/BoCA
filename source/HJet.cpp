# include "HJet.hh"

analysis::HJet::HJet()
{
//     DebugLevel = kDebug;
    Print(kNotification, "Constructor");
}

void analysis::HJet::Newevent(const analysis::ClonesArrays &NewClonesArrays)
{

    Print(kInformation, "New event");

    analysis::HFourVector::Newevent(NewClonesArrays);

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

bool analysis::HJet::GetJets(const analysis::HJet::HJetDetails JetDetails)
{
    Print(kError, "Get Jets", "No Jets", JetDetails);
    return 0;
}

bool analysis::HJet::GetEFlow(const analysis::HJet::HJetDetails JetDetails)
{

    Print(kError, "Get EFlow", "No EFlow", JetDetails);

    return 0;

}

void analysis::HJet::GetGenJet()
{

    Print(kError, "Get Gen Jets", "No Gen Jets");

}

float analysis::HJet::GetScalarHt()
{

    Print(kError, "Get Scalar Ht", "No Scalar Ht");

    return 0;

}

fastjet::PseudoJet analysis::HJet::GetMissingEt()
{

    Print(kError, "Get Missing Et", "No Mising Et");

    fastjet::PseudoJet Jet;
    return Jet;

}
