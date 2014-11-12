# include "HAnalysisHeavyHiggsParton.hh"

#include <iostream>

hheavyhiggs::HAnalysisHeavyHiggsParton::HAnalysisHeavyHiggsParton()
{
    Print(1, "Constructor");

}

std::vector<hanalysis::HFile*> hheavyhiggs::HAnalysisHeavyHiggsParton::GetFiles(const std::string &StudyName) const
{

    Print(1, "Fill Analysis Vector", StudyName);

    std::vector<hanalysis::HFile*> Files;

    Files.push_back(new hanalysis::HFile("Background/4f_10k"));
    Files.push_back(new hanalysis::HFile("Signal/Signal_5f"));

    Files.front()->SetBasePath("~/Projects/HeavyHiggs/Mass/");
    Files.front()->SetFileSuffix("_MG5.root");
    Files.front()->SetTreeName("LHEF");

    Print(1, "Files prepared", Files.size());

    return Files;

}

void hheavyhiggs::HAnalysisHeavyHiggsParton::NewBranches(ExRootTreeWriter *TreeWriter)
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

void hheavyhiggs::HAnalysisHeavyHiggsParton::CloseFile()
{
    Print(1, "Close File");

    Print(1, "EventCounter", EventCounter);
    Print(1, "JetCounter", JetCounter);
    Print(1, "DeltaEtaCounter", DeltaEtaCounter);
    Print(1, "BMassCounter", BMassCounter);
    Print(1, "Jet2Counter", Jet2Counter);
    Print(1, "TMassCounter", TMassCounter);

}



bool hheavyhiggs::HAnalysisHeavyHiggsParton::Analysis(hanalysis::HEvent *Event, const std::string &StudyName)
{

    Print(2, "Analysis",StudyName);

    HHeavyHiggsBranch *HeavyHiggs = static_cast<HHeavyHiggsBranch *>(HeavyHiggsBranch->NewEntry());

    ++EventCounter;

//     Event->GetParticlesM()->GetParticles();

    HJets BottomVector = Event->GetParticles()->GetBottomJets();

    int BottomSum = BottomVector.size();

    if (BottomSum != 2) {

        Print(1, "BottomSum", BottomSum);
        return 0;

    }

    for (int BottomNumber = 0; BottomNumber < BottomSum; ++BottomNumber) {

        BottomVector[BottomNumber].set_user_index(10);

    }

    HeavyHiggs->JetNumber = BottomSum;

    std::sort(BottomVector.begin(), BottomVector.end(), SortJetByEta());

    PseudoJet FrontJet = BottomVector.front();
//     double FrontPt = FrontJet.pt();
    double FrontEta = FrontJet.rap();

    PseudoJet BackJet = BottomVector.back();
    double BackEta = BackJet.rap();
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

    HJets TopVector = Event->GetParticles()->GetTopJets();

    int TopSum = TopVector.size();

    if (TopSum != 2) {

        Print(1, "TopSum", TopSum);
        return 0;

    }

    for (int TopNumber = 0; TopNumber < TopSum; ++TopNumber) {

        TopVector[TopNumber].set_user_index(100);

    }


    HeavyHiggs->JetNumber += TopSum;

    std::sort(TopVector.begin(), TopVector.end(), SortJetByEta());

    FrontJet = TopVector.front();
    FrontEta = FrontJet.rap();

    BackJet = TopVector.back();
    BackEta = BackJet.rap();

    CombinedJet = FrontJet + BackJet;
    CombinedMass = CombinedJet.m();
    CombinedEta = FrontEta - BackEta;


//     HeavyHiggs->TopDeltaEta = CombinedEta;
//     HeavyHiggs->TopInvMass = CombinedMass;


    HJets JetVector = BottomVector;

    JetVector.insert(JetVector.end(), TopVector.begin(), TopVector.end());

    std::sort(JetVector.begin(), JetVector.end(), SortJetByEta());

    FrontJet = JetVector.front();
    FrontEta = FrontJet.rap();

    BackJet = JetVector.back();
    BackEta = BackJet.rap();

//     HeavyHiggs->TopEta1 = FrontEta;
//     HeavyHiggs->TopEta2 = BackEta;

    CombinedJet = FrontJet + BackJet;
    CombinedMass = CombinedJet.m();
    CombinedEta = FrontEta - BackEta;

//     HeavyHiggs->TopDeltaEta = CombinedEta;
//     HeavyHiggs->TopInvMass = CombinedMass;

    std::sort(JetVector.begin(), JetVector.end(), SortJetByPt());

    Print (0, "Userindex" ,JetVector[0].user_index());
//     Print (0, "Pt" , JetVector[0].pt());

    return 1;

}
