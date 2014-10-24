# include "HFactory.hh"

# include "TObjArray.h"


HFactory::HFactory(HMva *NewMva)
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

    DebugLevel = 4;

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
    
    const string OutputFileName = Mva->AnalysisName + "/" + FactoryOutputName + ".root";
    
    OutputFile = TFile::Open(OutputFileName.c_str(), "Recreate");

//     string FactoryOptions = "Transformations=I;D;P;G,D:AnalysisType=Classification";
    const string FactoryOptions = "";

    Factory = new TMVA::Factory(Mva->AnalysisName, OutputFile, FactoryOptions);

}


void HFactory::AddVariables()
{

    Print(1 , "Add Variables");

    (TMVA::gConfig().GetIONames()).fWeightFileDir = Mva->AnalysisName;

    for (const auto & Observable : Mva->Observables) {

        Factory->AddVariable(Observable.Expression, Observable.Title, Observable.Unit, 'F');

    }

    for (const auto & Spectator : Mva->Spectators) {

        Factory->AddSpectator(Spectator.Expression, Spectator.Title, Spectator.Unit, 'F');

    }

}


void HFactory::GetTrees()
{

    Print(1 , "Get Trees");

    for (const auto & SignalName : Mva->SignalNames) {

        string SignalFileName = Mva->AnalysisName + "/" + SignalName + ".root";
        if (gSystem->AccessPathName(SignalFileName.c_str())) Print(0, "File not found", SignalFileName);
        TFile *SignalFile = TFile::Open(SignalFileName.c_str());
        Print(1 , "Signal File", SignalFile->GetName());

        int TreeSum = Mva->SignalTreeNames.size();

        for (int TreeNumber = 0; TreeNumber < TreeSum; ++TreeNumber) {

            AddTree(SignalFile, Mva->SignalTreeNames[TreeNumber], 1);

        }

    }

    for (const auto & BackgroundName : Mva->BackgroundNames) {

        string BackgroundFileName = Mva->AnalysisName + "/" + BackgroundName + ".root";
        if (gSystem->AccessPathName(BackgroundFileName.c_str())) Print(0, "File not found", BackgroundFileName);
        TFile *BackgroundFile = TFile::Open(BackgroundFileName.c_str());
        Print(1 , "Background File", BackgroundFile->GetName());

        for (const auto & BackgroundTreeName : Mva->BackgroundTreeNames) {

            AddTree(BackgroundFile, BackgroundTreeName, 0);

        }

    }

}

void HFactory::AddTree(const TFile *const File, const string TreeName, const bool Signal)
{

    Print(1 , "Add Tree", TreeName);

    const TTree *const Tree = (TTree *)(const_cast<TFile *>(File)->Get(TreeName.c_str()));

    const_cast<TTree *>(Tree)->GetBranch(Mva->CandidateBranchName.c_str());
    const ExRootTreeReader *const TreeReader = new ExRootTreeReader(const_cast<TTree *>(Tree));

    const TClonesArray *const ClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(Mva->WeightBranchName.c_str());
    const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(0);
    HInfoBranch *Info = (HInfoBranch *) ClonesArray->First();

//     const float Crosssection = Info->Crosssection;
//     cosnt float Crosssection = Info->Crosssection *  Info->EventNumber / TreeReader->GetEntries();
    delete TreeReader;

    const float Crosssection = 1; //FIXME we dont use the crosssection

    Print(1 , "Weight", Crosssection);

    if (Signal) {

        Factory->AddSignalTree(const_cast<TTree *>(Tree), Crosssection);

    } else {

        Factory->AddBackgroundTree(const_cast<TTree *>(Tree), Crosssection);

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

    const string CutOptions = "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart";
//     string CutOptions = "VarProp=FSmart:VarTransform=PCA";
//     const string CutOptions = "";

    const string CutMethodName = Mva->CutMethodName + "_" + Mva->BackgroundName;

    Factory->BookMethod(Types::kCuts, CutMethodName, CutOptions);

//     const string BdtOptions = "!H:!V:NTrees=1000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=2";
    const string BdtOptions = "!H:!V:NTrees=1000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20";
//     const string BdtOptions = "";

    const string BdtMethodName = Mva->BdtMethodName + "_" + Mva->BackgroundName;

    Factory->BookMethod(Types::kBDT, BdtMethodName, BdtOptions);

}
