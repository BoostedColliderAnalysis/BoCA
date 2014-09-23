# include "HJet.hh"

HJet::HJet()
{

    Print(0, "Constructor");

//     Debug = 4;

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

    bool Bool = 0;
    
    return Bool;


}

bool HJet::GetEFlow()
{
    
    Print(0,"Get EFlow","No EFlow");
    
    bool Bool = 0;
    
    return Bool;
    
    
}

void HJet::GetGenJet()
{
    
    Print(0,"Get Gen Jets","No Gen Jets");

}
