# include "HFactory.hh"


HFactory::HFactory()
{

    if (Debug > 0)Print("HFactory", "Constructor");

    Mva = new HMva;

    NewFactory();

    AddVariables();

    GetTrees();

    PrepareTrainingAndTestTree();

    BookMethods();

    Factory->TrainAllMethods();

    Factory->TestAllMethods();

    Factory->EvaluateAllMethods();

    OutputFile->Close();


}

HFactory::~HFactory()
{

    if (Debug > 0)Print("HFactory", "Destructor");

    delete Factory;

}

void HFactory::NewFactory()
{

    if (Debug > 0)Print("HFactory", "New Factory");

    TString FactoryOutputName = "Mva" + Mva->BackgroundName;
    TString OutputFileName(Mva->AnalysisName + "/" + FactoryOutputName + ".root");
    OutputFile = TFile::Open(OutputFileName, "Recreate");

//     TString FactoryOptions = "Transformations=I;D;P;G,D:AnalysisType=Classification";
    TString FactoryOptions = "";

    Factory = new TMVA::Factory(Mva->AnalysisName, OutputFile, FactoryOptions);

}


void HFactory::AddVariables()
{

    if (Debug > 0)Print("HFactory", "Add Variables");

    (TMVA::gConfig().GetIONames()).fWeightFileDir = Mva->AnalysisName;

    int ObservableSum = Mva->ObservableVector.size();

    for (int ObservableNumber = 0; ObservableNumber < ObservableSum; ++ObservableNumber) {

        Factory->AddVariable(Mva->ObservableVector[ObservableNumber].Expression, Mva->ObservableVector[ObservableNumber].Title, Mva->ObservableVector[ObservableNumber].Unit, 'F');

    }

    int SpectatorSum = Mva->SpectatorVector.size();
    for (int SpectatorNumber = 0; SpectatorNumber < SpectatorSum; ++SpectatorNumber) {

        Factory->AddSpectator(Mva->SpectatorVector[SpectatorNumber].Expression, Mva->SpectatorVector[SpectatorNumber].Title, Mva->SpectatorVector[SpectatorNumber].Unit, 'F');

    }

}



// void HFactory::GetTrees()
// {
//
//     if (Debug > 0)PrintFunction("HFactory", "Get Trees");
//
//     // Signal
//     TString SignalFileName = Mva->AnalysisName + "/" + Mva->SignalName + TString(".root");
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
//         TString InputBackgroundName = Mva->BackgroundVector[BackgroundNumber];
//
//         TString BackgroundFileName = Mva->AnalysisName + "/" + InputBackgroundName + TString(".root");
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

    if (Debug > 0)Print("HFactory", "Get Trees");

// Signal
    int SignalSum = Mva->SignalVector.size();
    for (int SignalNumber = 0; SignalNumber < SignalSum; ++SignalNumber) {

        TString SignalName = Mva->SignalVector[SignalNumber];

        TString SignalFileName = Mva->AnalysisName + "/" + Mva->SignalVector[SignalNumber] + TString(".root");
        if (gSystem->AccessPathName(SignalFileName)) cout << "File " << SignalFileName << " not found" << endl;
        TFile *SignalFile = TFile::Open(SignalFileName);
        if (Debug > 0)Print("HFactory", "Signal File", SignalFile->GetName());

        int TreeSum = Mva->SignalTreeVector.size();

        for (int TreeNumber = 0; TreeNumber < TreeSum; ++TreeNumber) {

            AddTree(SignalFile, Mva->SignalTreeVector[TreeNumber], 1);

        }

    }

// Background
    int BackgroundSum = Mva->BackgroundVector.size();
    for (int BackgroundNumber = 0; BackgroundNumber < BackgroundSum; ++BackgroundNumber) {

        TString InputBackgroundName = Mva->BackgroundVector[BackgroundNumber];

        TString BackgroundFileName = Mva->AnalysisName + "/" + InputBackgroundName + TString(".root");
        if (gSystem->AccessPathName(BackgroundFileName)) cout << "File " << BackgroundFileName << " not found" << endl;
        TFile *BackgroundFile = TFile::Open(BackgroundFileName);
        if (Debug > 0)Print("HFactory", "Background File", BackgroundFile->GetName());

        int TreeSum = Mva->BackgroundTreeVector.size();
        for (int TreeNumber = 0; TreeNumber < TreeSum; ++TreeNumber) {

            AddTree(BackgroundFile, Mva->BackgroundTreeVector[TreeNumber], 0);

        }

    }

}

void HFactory::AddTree(TFile *File, TString TreeName, bool Signal)
{

    if (Debug > 0)Print("HFactory", "Add Tree", TreeName);

    TTree *Tree = (TTree *)File->Get(TreeName);

    Tree->GetBranch(Mva->CandidateBranchName);
    ExRootTreeReader *TreeReader = new ExRootTreeReader(Tree);

    TClonesArray *ClonesArray = TreeReader->UseBranch(Mva->WeightBranchName);
    TreeReader->ReadEntry(0);
    HInfoBranch *Info = (HInfoBranch *) ClonesArray->At(0);

//     float Crosssection = Info->Crosssection;
    float Crosssection = Info->Crosssection *  Info->EventNumber / TreeReader->GetEntries();
    delete TreeReader;

//     Crosssection = 1; //FIXME we dont use the crosssection

    if (Debug > 0)Print("HFactory", "Weight", Crosssection);

    if (Signal) {

        Factory->AddSignalTree(Tree, Crosssection);

    } else {

        Factory->AddBackgroundTree(Tree, Crosssection);

    }


}

void HFactory::PrepareTrainingAndTestTree()
{

    if (Debug > 0)Print("HFactory", "PrepareTrainingAndTestTree");

    TCut SignalCut = Mva->Cut;
    TCut BackgroundCut = Mva->Cut;

//     TString TrainingAndTestOptions = "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V";
    TString TrainingAndTestOptions = "";

    Factory->PrepareTrainingAndTestTree(SignalCut, BackgroundCut, TrainingAndTestOptions);

}

void HFactory::BookMethods()
{

    if (Debug > 0) Print("HFactory", "Book Methods");

//     TString CutOptions = "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart";
//     TString CutOptions = "VarProp=FSmart:VarTransform=PCA";
    TString CutOptions = "";

    TString MethodName = Mva->CutMethodName + "_" + Mva->BackgroundName;

    Factory->BookMethod(Types::kCuts, MethodName, CutOptions);

//     TString BDTOptions = "!H:!V:NTrees=1000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20";
    TString BDTOptions = "";

    MethodName = Mva->BdtMethodName + "_" + Mva->BackgroundName;

    Factory->BookMethod(Types::kBDT, MethodName, BDTOptions);

}
