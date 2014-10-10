# include "HFactory.hh"


HFactory::HFactory(HMva* NewMva)
{

    Print(1 , "Constructor");

    Mva = NewMva;

    NewFactory();

    AddVariables();

    GetTrees();

    PrepareTrainingAndTestTree();

    BookMethods();

    Factory->TrainAllMethods();

    Factory->TestAllMethods();

    Factory->EvaluateAllMethods();

    OutputFile->Close();

    DebugLevel =4;

}

HFactory::~HFactory()
{

    Print(1 , "Destructor");

    delete Factory;

}

void HFactory::NewFactory()
{

    Print(1 , "New Factory");

    const string FactoryOutputName = "Mva" + Mva->BackgroundName;
    const TString OutputFileName(Mva->AnalysisName + "/" + FactoryOutputName + ".root");
    OutputFile = TFile::Open(OutputFileName, "Recreate");

//     string FactoryOptions = "Transformations=I;D;P;G,D:AnalysisType=Classification";
    const string FactoryOptions = "";

    Factory = new TMVA::Factory(Mva->AnalysisName, OutputFile, FactoryOptions);

}


void HFactory::AddVariables()
{

    Print(1 , "Add Variables");

    (TMVA::gConfig().GetIONames()).fWeightFileDir = Mva->AnalysisName;

    for (auto& Observable : Mva->ObservableVector) {

        Factory->AddVariable(Observable.Expression, Observable.Title, Observable.Unit, 'F');

    }

    for (auto& Spectator : Mva->SpectatorVector) {

        Factory->AddSpectator(Spectator.Expression, Spectator.Title, Spectator.Unit, 'F');

    }

}



// void HFactory::GetTrees()
// {
//
//     if (Debug > 0)PrintFunction("HFactory", "Get Trees");
//
//     // Signal
//     string SignalFileName = Mva->AnalysisName + "/" + Mva->SignalName + string(".root");
//     if (gSystem->AccessPathName(SignalFileName)) cout << "File " << SignalFileName << " not found" << endl;
//     TFile *SignalFile = TFile::Open(SignalFileName);
//     if (Debug > 0)PrintFunction("HFactory", "Signal File", SignalFile->GetName());
//
//     int TreeSum = Mva->SignalTreeVector.size();
//
//
//         TTree *Tree = (TTree *)SignalFile->Get(Mva->SignalTreeVector[0]);
//         Tree->GetBranch(Mva->CandidateBranchName);
//         float Crosssection = 1; //FIXME we dont use the crosssection
//         if (Debug > 0)PrintFunction("HFactory", "Weight", Crosssection);
//         Factory->AddSignalTree(Tree, Crosssection);
//
//
//
//     // Background
//     int BackgroundSum = Mva->BackgroundVector.size();
//     for (int BackgroundNumber = 0; BackgroundNumber < BackgroundSum; ++BackgroundNumber) {
//
//         string InputBackgroundName = Mva->BackgroundVector[BackgroundNumber];
//
//         string BackgroundFileName = Mva->AnalysisName + "/" + InputBackgroundName + string(".root");
//         if (gSystem->AccessPathName(BackgroundFileName)) cout << "File " << BackgroundFileName << " not found" << endl;
//         TFile *BackgroundFile = TFile::Open(BackgroundFileName);
//         if (Debug > 0)PrintFunction("HFactory", "Background File", BackgroundFile->GetName());
//
//
//             TTree *Tree = (TTree *)BackgroundFile->Get(Mva->BackgroundTreeVector[0]);
//             Tree->GetBranch(Mva->CandidateBranchName);
//             float Crosssection = 1; //FIXME we dont use the crosssection
//             if (Debug > 0)PrintFunction("HFactory", "Weight", Crosssection);
//             Factory->AddBackgroundTree(Tree, Crosssection);
//
//
//
//     }
//
// }





void HFactory::GetTrees()
{

    Print(1 , "Get Trees");

// Signal
    for (auto& SignalName : Mva->SignalNameVector) {

        TString SignalFileName = Mva->AnalysisName + "/" + SignalName + string(".root");
        if (gSystem->AccessPathName(SignalFileName)) Print(0, "File not found", SignalFileName);
        TFile *SignalFile = TFile::Open(SignalFileName);
        Print(1 , "Signal File", SignalFile->GetName());

        int TreeSum = Mva->SignalTreeNameVector.size();

        for (int TreeNumber = 0; TreeNumber < TreeSum; ++TreeNumber) {

            AddTree(SignalFile, Mva->SignalTreeNameVector[TreeNumber], 1);

        }

    }

// Background
for (auto& BackgroundName : Mva->BackgroundNameVector){

        TString BackgroundFileName = Mva->AnalysisName + "/" + BackgroundName + string(".root");
        if (gSystem->AccessPathName(BackgroundFileName)) Print(0, "File not found",BackgroundFileName);
        TFile *BackgroundFile = TFile::Open(BackgroundFileName);
        Print(1 , "Background File", BackgroundFile->GetName());

        for (auto& BackgroundTreeName : Mva->BackgroundTreeNameVector){

            AddTree(BackgroundFile, BackgroundTreeName, 0);

        }

    }

}

void HFactory::AddTree(const TFile * const File, const string TreeName, const bool Signal)
{

    Print(1 , "Add Tree", TreeName);

    const TTree * const Tree = (TTree *)(const_cast<TFile*>(File)->Get(TString(TreeName)));

    const_cast<TTree*>(Tree)->GetBranch(TString(Mva->CandidateBranchName));
    const ExRootTreeReader * const TreeReader = new ExRootTreeReader(const_cast<TTree*>(Tree));

    const TClonesArray * const ClonesArray = const_cast<ExRootTreeReader*>(TreeReader)->UseBranch(TString(Mva->WeightBranchName));
    const_cast<ExRootTreeReader*>(TreeReader)->ReadEntry(0);
    HInfoBranch *Info = (HInfoBranch *) ClonesArray->At(0);

//     float Crosssection = Info->Crosssection;
    float Crosssection = Info->Crosssection *  Info->EventNumber / TreeReader->GetEntries();
    delete TreeReader;

//     Crosssection = 1; //FIXME we dont use the crosssection

    Print(1 , "Weight", Crosssection);

    if (Signal) {

        Factory->AddSignalTree(const_cast<TTree*>(Tree), Crosssection);

    } else {

        Factory->AddBackgroundTree(const_cast<TTree*>(Tree), Crosssection);

    }


}

void HFactory::PrepareTrainingAndTestTree()
{

    Print(1 , "PrepareTrainingAndTestTree");

    const TCut SignalCut = Mva->Cut;
    const TCut BackgroundCut = Mva->Cut;

//     string TrainingAndTestOptions = "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V";
    const string TrainingAndTestOptions = "";

    Factory->PrepareTrainingAndTestTree(SignalCut, BackgroundCut, TrainingAndTestOptions);

}

void HFactory::BookMethods()
{

    Print(1 , "Book Methods");

//     string CutOptions = "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart";
//     string CutOptions = "VarProp=FSmart:VarTransform=PCA";
    const string CutOptions = "";

    const string CutMethodName = Mva->CutMethodName + "_" + Mva->BackgroundName;

    Factory->BookMethod(Types::kCuts, CutMethodName, CutOptions);

//     string BdtOptions = "!H:!V:NTrees=1000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20";
    const string BdtOptions = "";

    const string BdtMethodName = Mva->BdtMethodName + "_" + Mva->BackgroundName;

    Factory->BookMethod(Types::kBDT, BdtMethodName, BdtOptions);

}
