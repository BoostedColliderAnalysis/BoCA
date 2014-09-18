# include "HAnalysis.hh"

HAnalysis::HAnalysis()
{

    Print(0, "Constructor");

    ProjectName = "HeavyHiggsParton";

    EventNumberMax = 10000;

    ClonesArrays = new HClonesArrayParton();

    Cut = 0;

}

void HAnalysis::SetFileVector()
{

    Print(0, "Fill Analysis Vector", AnalysisName);

    FileVector.push_back(new HFileFolder("Background/4f_10k"));
    FileVector.push_back(new HFileFolder("Signal/Signal_5f"));

    FileVector.front()->BasePath = "~/Projects/HeavyHiggs/Mass/";
    FileVector.front()->FileSuffix = "_MG5.root";
    FileVector.front()->TreeString = "LHEF";

    Print(0, "Files prepared", FileVector.size());

}

void HAnalysis::NewFile()
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

void HAnalysis::CloseFile()
{
    Print(0, "Close File");

    Print(0, "EventCounter", EventCounter);
    Print(0, "JetCounter", JetCounter);
    Print(0, "DeltaEtaCounter", DeltaEtaCounter);
    Print(0, "BMassCounter", BMassCounter);
    Print(0, "Jet2Counter", Jet2Counter);
    Print(0, "TMassCounter", TMassCounter);

}



bool HAnalysis::Analysis()
{

    Print(1, "Analysis", AnalysisName);

    HHeavyHiggsBranch *HeavyHiggs = static_cast<HHeavyHiggsBranch *>(HeavyHiggsBranch->NewEntry());

    ++EventCounter;

    Event->GetParticles();

    vector<PseudoJet> BottomVector = Event->Particle->BottomJetVector;

    int BottomSum = BottomVector.size();
    HeavyHiggs->JetNumber = BottomSum;

    if (BottomSum != 2) {

        Print(0, "BottomSum", BottomSum);
        return 0;

    }

    sort(BottomVector.begin(), BottomVector.end(), SortJetByEta());

    PseudoJet FrontJet = BottomVector.front();
    double FrontPt = FrontJet.pt();
    double FrontEta = FrontJet.eta();

    PseudoJet BackJet = BottomVector.back();
    double BackEta = BackJet.eta();
    double BackPt = BackJet.pt();

    PseudoJet CombinedJet = FrontJet + BackJet;
    double CombinedMass = CombinedJet.m();
    double CombinedEta = FrontEta - BackEta;


    HeavyHiggs->MaxPt = FrontEta;
    HeavyHiggs->MinPt = BackEta;
    HeavyHiggs->DeltaEta = CombinedEta;
    HeavyHiggs->BMass = CombinedMass;



    return 1;

}
