# include "HJet.hh"

HJet::HJet()
{

    Print(0, "Constructor");

}

HJet::~HJet()
{

    Print(0, "Destructor");

}

void HJet::NewEvent(HClonesArray *NewClonesArrays)
{

    Print(1, "New Event");

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
    
    Print(0,"Get Jets","No Jets");
    
    return 0;

}

bool HJet::GetTaggedJets()
{
    
    Print(0,"Get Tagged Jets","No Jets");
    
    return 0;
    
}

bool HJet::GetStructuredJets()
{
    
    Print(0,"Get Structured Jets","No Jets");
    
    return 0;
    
}

bool HJet::GetEFlow(bool Tagging)
{
    
    Print(0,"Get EFlow","No EFlow");
        
    return 0;
        
}

bool HJet::GetEFlow()
{
    
    Print(0,"Get EFlow","No EFlow");
    
    return 0;
    
}

bool HJet::GetTaggedEFlow()
{
    
    Print(0,"Get Tagged EFlow","No EFlow");
    
    return 0;
    
}

void HJet::GetGenJet()
{
    
    Print(0,"Get Gen Jets","No Gen Jets");

}
