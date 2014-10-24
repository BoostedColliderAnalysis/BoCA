# include "HAnalysisHeavyHiggsParton.hh"

#include <iostream>

HAnalysisHeavyHiggsParton::HAnalysisHeavyHiggsParton()
{
    Print(1, "Constructor");

}

vector<Analysis::HFile*> HAnalysisHeavyHiggsParton::GetFiles(const string StudyName) const
{

    Print(1, "Fill Analysis Vector", StudyName);

    vector<Analysis::HFile*> Files;

    Files.push_back(new Analysis::HFileFolder("Background/4f_10k"));
    Files.push_back(new Analysis::HFileFolder("Signal/Signal_5f"));

    Files.front()->BasePath = "~/Projects/HeavyHiggs/Mass/";
    Files.front()->FileSuffix = "_MG5.root";
    Files.front()->TreeString = "LHEF";

    Print(1, "Files prepared", Files.size());

    return Files;

}

void HAnalysisHeavyHiggsParton::NewBranches(ExRootTreeWriter *TreeWriter)
{

    Print(1, "New File");

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
    Print(1, "Close File");

    Print(1, "EventCounter", EventCounter);
    Print(1, "JetCounter", JetCounter);
    Print(1, "DeltaEtaCounter", DeltaEtaCounter);
    Print(1, "BMassCounter", BMassCounter);
    Print(1, "Jet2Counter", Jet2Counter);
    Print(1, "TMassCounter", TMassCounter);

}



bool HAnalysisHeavyHiggsParton::Analysis(Analysis::HEvent* Event,string)
{

    Print(2, "Analysis");

    HHeavyHiggsBranch *HeavyHiggs = static_cast<HHeavyHiggsBranch *>(HeavyHiggsBranch->NewEntry());

    ++EventCounter;

    Event->GetParticles();

    vector<PseudoJet> BottomVector = Event->Particles->BottomJetVector;

    int BottomSum = BottomVector.size();

    if (BottomSum != 2) {

        Print(1, "BottomSum", BottomSum);
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

        Print(1, "TopSum", TopSum);
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
