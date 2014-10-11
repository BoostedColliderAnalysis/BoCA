# include "HJet.hh"

HJet::HJet()
{

    Print(1, "Constructor");

}

HJet::~HJet()
{

    Print(1, "Destructor");

}

void HJet::NewEvent(const HClonesArray * const NewClonesArrays)
{

    Print(2, "New Event");

    ClonesArrays = NewClonesArrays;

    JetLorentzVectorVector.clear();

    TauLorentzVectorVector.clear();

    AntiTauLorentzVectorVector.clear();

    EFlowJetVector.clear();

    BottomJetVector.clear();

    CharmJetVector.clear();

    GenJetVector.clear();

    BottomLorentzVectorVector.clear();

    JetVector.clear();

}

bool HJet::GetJets()
{

    Print(1,"Get Jets","No Jets");

    return 0;

}

bool HJet::GetTaggedJets(const HJetTag * const JetTag)
{

    Print(1,"Get Tagged Jets","No Jets");

    return 0;

}

bool HJet::GetStructuredJets()
{

    Print(1,"Get Structured Jets","No Jets");

    return 0;

}

bool HJet::GetEFlow()
{

    Print(1,"Get EFlow","No EFlow");

    return 0;

}

bool HJet::GetTaggedEFlow(const HJetTag * const JetTag)
{

    Print(1,"Get Tagged EFlow","No EFlow");

    return 0;

}

void HJet::GetGenJet()
{

    Print(1,"Get Gen Jets","No Gen Jets");

}
