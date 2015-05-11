# include "HAnalysisHeavyHiggsParton.hh"

#include <iostream>

// hheavyhiggs::HAnalysisHeavyHiggsParton::HAnalysisHeavyHiggsParton()
// {
//     Print(kNotification, "Constructor");
//
// }

std::vector<hanalysis::RootFile*> hheavyhiggs::HAnalysisHeavyHiggsParton::GetFiles(const std::string &StudyName)
{

    Print(kNotification, "Fill Analysis Vector", StudyName);

    std::vector<hanalysis::RootFile*> Files;

    Files.emplace_back(new hanalysis::RootFile("Background/4f_10k"));
    Files.emplace_back(new hanalysis::RootFile("Signal/Signal_5f"));

    Files.front()->SetBasePath("~/Projects/HeavyHiggs/Mass/");
    Files.front()->set_file_suffix("_MG5.root");
    Files.front()->set_tree_name("LHEF");

    Print(kNotification, "Files prepared", Files.size());

    return Files;

}

void hheavyhiggs::HAnalysisHeavyHiggsParton::NewBranches(ExRootTreeWriter *TreeWriter)
{

    Print(kNotification, "New File");

    HeavyHiggsBranch = TreeWriter->NewBranch("HeavyHiggs", HHeavyHiggsLeptonicBranch::Class());

    EventCounter = 0;
    DeltaRapCounter = 0;
    BMassCounter = 0;
    TMassCounter = 0;
    JetCounter = 0;
    Jet2Counter = 0;

}

void hheavyhiggs::HAnalysisHeavyHiggsParton::CloseFile()
{
    Print(kNotification, "Close File");

    Print(kNotification, "EventCounter", EventCounter);
    Print(kNotification, "JetCounter", JetCounter);
    Print(kNotification, "DeltaRapCounter", DeltaRapCounter);
    Print(kNotification, "BMassCounter", BMassCounter);
    Print(kNotification, "Jet2Counter", Jet2Counter);
    Print(kNotification, "TMassCounter", TMassCounter);

}



int hheavyhiggs::HAnalysisHeavyHiggsParton::Analysis(hanalysis::HEvent &Event, const std::string &StudyName)
{

    Print(kInformation, "Analysis",StudyName);

    HBranchHeavyHiggs *HeavyHiggs = static_cast<HBranchHeavyHiggs *>(HeavyHiggsBranch->NewEntry());

    ++EventCounter;

//     Event.GetParticlesM()->GetParticles();

    Jets BottomVector = Event.GetParticles()->GetBottomJets();

    int BottomSum = BottomVector.size();

    if (BottomSum != 2) {

        Print(kNotification, "BottomSum", BottomSum);
        return 0;

    }

    for (int BottomNumber = 0; BottomNumber < BottomSum; ++BottomNumber) {

        BottomVector[BottomNumber].set_user_index(10);

    }

    HeavyHiggs->JetNumber = BottomSum;

    std::sort(BottomVector.begin(), BottomVector.end(), SortJetByRap());

    fastjet::PseudoJet FrontJet = BottomVector.front();
//     double FrontPt = FrontJet.pt();
    double FrontRap = FrontJet.rap();

    fastjet::PseudoJet BackJet = BottomVector.back();
    double BackRap = BackJet.rap();
//     double BackPt = BackJet.pt();

    fastjet::PseudoJet CombinedJet = FrontJet + BackJet;
    double CombinedMass = CombinedJet.m();
    double CombinedRap = FrontRap - BackRap;


//     HeavyHiggs->MaxPt = FrontRap;
//     HeavyHiggs->MinPt = BackRap;
    HeavyHiggs->BottomRap1 = FrontRap;
    HeavyHiggs->BottomRap2 = BackRap;
    HeavyHiggs->BottomDeltaRap = CombinedRap;
    HeavyHiggs->BottomInvMass = CombinedMass;

    Jets TopVector = Event.GetParticles()->GetTopJets();

    int TopSum = TopVector.size();

    if (TopSum != 2) {

        Print(kNotification, "TopSum", TopSum);
        return 0;

    }

    for (int TopNumber = 0; TopNumber < TopSum; ++TopNumber) {

        TopVector[TopNumber].set_user_index(100);

    }


    HeavyHiggs->JetNumber += TopSum;

    std::sort(TopVector.begin(), TopVector.end(), SortJetByRap());

    FrontJet = TopVector.front();
    FrontRap = FrontJet.rap();

    BackJet = TopVector.back();
    BackRap = BackJet.rap();

    CombinedJet = FrontJet + BackJet;
    CombinedMass = CombinedJet.m();
    CombinedRap = FrontRap - BackRap;


//     HeavyHiggs->TopDeltaRap = CombinedRap;
//     HeavyHiggs->TopInvMass = CombinedMass;


    Jets JetVector = BottomVector;

    JetVector.insert(JetVector.end(), TopVector.begin(), TopVector.end());

    std::sort(JetVector.begin(), JetVector.end(), SortJetByRap());

    FrontJet = JetVector.front();
    FrontRap = FrontJet.rap();

    BackJet = JetVector.back();
    BackRap = BackJet.rap();

//     HeavyHiggs->TopRap1 = FrontRap;
//     HeavyHiggs->TopRap2 = BackRap;

    CombinedJet = FrontJet + BackJet;
    CombinedMass = CombinedJet.m();
    CombinedRap = FrontRap - BackRap;

//     HeavyHiggs->TopDeltaRap = CombinedRap;
//     HeavyHiggs->TopInvMass = CombinedMass;

    std::sort(JetVector.begin(), JetVector.end(), SortJetByPt());

    Print (0, "Userindex" ,JetVector[0].user_index());
//     Print (0, "Pt" , JetVector[0].pt());

    return 1;

}
