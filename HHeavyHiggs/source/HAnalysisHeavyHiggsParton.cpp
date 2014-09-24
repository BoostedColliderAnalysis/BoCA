# include "HAnalysisHeavyHiggsParton.hh"

#include <iostream>

HAnalysisHeavyHiggsParton::HAnalysisHeavyHiggsParton()
{

    Print(0, "Constructor");

    ProjectName = "HeavyHiggsParton";

    EventNumberMax = 10000;

    ClonesArrays = new HClonesArrayParton();

    Event = new HEventParton();

    Cut = 0;

}

void HAnalysisHeavyHiggsParton::SetFileVector()
{

    Print(0, "Fill Analysis Vector", AnalysisName);

    FileVector.push_back(new HFileFolder("Background/4f_10k"));
    FileVector.push_back(new HFileFolder("Signal/Signal_5f"));

    FileVector.front()->BasePath = "~/Projects/HeavyHiggs/Mass/";
    FileVector.front()->FileSuffix = "_MG5.root";
    FileVector.front()->TreeString = "LHEF";

    Print(0, "Files prepared", FileVector.size());

}

void HAnalysisHeavyHiggsParton::NewFile()
{

    Print(0, "New File");

    HeavyHiggsBranch = TreeWriter->NewBranch("HeavyHiggs", HHeavyHiggsBranch::Class());

    EventCounter = 0;
    DeltaEtaCounter = 0;
    BMassCounter = 0;
    TMassCounter = 0;
    JetCounter = 0;
    Jet2Counter = 0;

}

void HAnalysisHeavyHiggsParton::CloseFile()
{
    Print(0, "Close File");

    Print(0, "EventCounter", EventCounter);
    Print(0, "JetCounter", JetCounter);
    Print(0, "DeltaEtaCounter", DeltaEtaCounter);
    Print(0, "BMassCounter", BMassCounter);
    Print(0, "Jet2Counter", Jet2Counter);
    Print(0, "TMassCounter", TMassCounter);

}



bool HAnalysisHeavyHiggsParton::Analysis()
{

    Print(1, "Analysis", AnalysisName);

    HHeavyHiggsBranch *HeavyHiggs = static_cast<HHeavyHiggsBranch *>(HeavyHiggsBranch->NewEntry());

    ++EventCounter;

    Event->GetParticles();

    vector<PseudoJet> BottomVector = Event->Particles->BottomJetVector;

    int BottomSum = BottomVector.size();

    if (BottomSum != 2) {

        Print(0, "BottomSum", BottomSum);
        return 0;

    }

    for (int BottomNumber = 0; BottomNumber < BottomSum; ++BottomNumber) {

        BottomVector[BottomNumber].set_user_index(10);

    }

    HeavyHiggs->JetNumber = BottomSum;

    sort(BottomVector.begin(), BottomVector.end(), SortJetByEta());

    PseudoJet FrontJet = BottomVector.front();
//     double FrontPt = FrontJet.pt();
    double FrontEta = FrontJet.eta();

    PseudoJet BackJet = BottomVector.back();
    double BackEta = BackJet.eta();
//     double BackPt = BackJet.pt();

    PseudoJet CombinedJet = FrontJet + BackJet;
    double CombinedMass = CombinedJet.m();
    double CombinedEta = FrontEta - BackEta;


//     HeavyHiggs->MaxPt = FrontEta;
//     HeavyHiggs->MinPt = BackEta;
    HeavyHiggs->BottomEta1 = FrontEta;
    HeavyHiggs->BottomEta2 = BackEta;
    HeavyHiggs->BottomDeltaEta = CombinedEta;
    HeavyHiggs->BottomInvMass = CombinedMass;

    vector<PseudoJet> TopVector = Event->Particles->TopJetVector;

    int TopSum = TopVector.size();

    if (TopSum != 2) {

        Print(0, "TopSum", TopSum);
        return 0;

    }

    for (int TopNumber = 0; TopNumber < TopSum; ++TopNumber) {

        TopVector[TopNumber].set_user_index(100);

    }


    HeavyHiggs->JetNumber += TopSum;

    sort(TopVector.begin(), TopVector.end(), SortJetByEta());

    FrontJet = TopVector.front();
    FrontEta = FrontJet.eta();

    BackJet = TopVector.back();
    BackEta = BackJet.eta();

    CombinedJet = FrontJet + BackJet;
    CombinedMass = CombinedJet.m();
    CombinedEta = FrontEta - BackEta;


//     HeavyHiggs->TopDeltaEta = CombinedEta;
//     HeavyHiggs->TopInvMass = CombinedMass;


    vector<PseudoJet> JetVector = BottomVector;

    JetVector.insert(JetVector.end(), TopVector.begin(), TopVector.end());

    sort(JetVector.begin(), JetVector.end(), SortJetByEta());

    FrontJet = JetVector.front();
    FrontEta = FrontJet.eta();

    BackJet = JetVector.back();
    BackEta = BackJet.eta();

//     HeavyHiggs->TopEta1 = FrontEta;
//     HeavyHiggs->TopEta2 = BackEta;

    CombinedJet = FrontJet + BackJet;
    CombinedMass = CombinedJet.m();
    CombinedEta = FrontEta - BackEta;

//     HeavyHiggs->TopDeltaEta = CombinedEta;
//     HeavyHiggs->TopInvMass = CombinedMass;

    sort(JetVector.begin(), JetVector.end(), SortJetByPt());

    Print (0, "Userindex" ,JetVector[0].user_index());
//     Print (0, "Pt" , JetVector[0].pt());

    return 1;

}
