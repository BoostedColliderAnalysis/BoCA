# include "HFactory.hh"

# include "TObjArray.h"


hmva::HFactory::HFactory(HMva * const NewMva)
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

hmva::HFactory::~HFactory()
{

    Print(1 , "Destructor");

    delete Factory;

}

void hmva::HFactory::NewFactory()
{

    Print(1 , "New Factory");

    const std::string FactoryOutputName = "Mva" + Mva->BackgroundName;

    const std::string OutputFileName = Mva->AnalysisName + "/" + FactoryOutputName + ".root";

    OutputFile = TFile::Open(OutputFileName.c_str(), "Recreate");

//     std::string FactoryOptions = "Transformations=I;D;P;G,D:AnalysisType=Classification";
    const std::string FactoryOptions = "";

    Factory = new TMVA::Factory(Mva->AnalysisName, OutputFile, FactoryOptions);

}


void hmva::HFactory::AddVariables()
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


void hmva::HFactory::GetTrees()
{

    Print(1 , "Get Trees");

    for (const auto & SignalName : Mva->SignalNames) {

        std::string SignalFileName = Mva->AnalysisName + "/" + SignalName + ".root";
        if (gSystem->AccessPathName(SignalFileName.c_str())) Print(0, "File not found", SignalFileName);
        TFile *SignalFile = TFile::Open(SignalFileName.c_str());
        Print(1 , "Signal File", SignalFile->GetName());

        for (int TreeNumber : HRange(Mva->SignalTreeNames.size())) {

            AddTree(SignalFile, Mva->SignalTreeNames[TreeNumber], 1);

        }

    }

    for (const auto & BackgroundName : Mva->BackgroundNames) {

        std::string BackgroundFileName = Mva->AnalysisName + "/" + BackgroundName + ".root";
        if (gSystem->AccessPathName(BackgroundFileName.c_str())) Print(0, "File not found", BackgroundFileName);
        TFile *BackgroundFile = TFile::Open(BackgroundFileName.c_str());
        Print(1 , "Background File", BackgroundFile->GetName());

        for (const auto & BackgroundTreeName : Mva->BackgroundTreeNames) {

            AddTree(BackgroundFile, BackgroundTreeName, 0);

        }

    }

}

void hmva::HFactory::AddTree(const TFile *const File, const std::string &TreeName, const bool Signal)
{

    Print(1 , "Add Tree", TreeName);

    const TTree *const Tree = (TTree *)(const_cast<TFile *>(File)->Get(TreeName.c_str()));

    Print(0,"Branch Name",Mva->CandidateBranchName.c_str());
    const_cast<TTree *>(Tree)->GetBranch(Mva->CandidateBranchName.c_str());
    const ExRootTreeReader *const TreeReader = new ExRootTreeReader(const_cast<TTree *>(Tree));

    const TClonesArray *const ClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(Mva->WeightBranchName.c_str());
    const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(0);
    HInfoBranch *Info = (HInfoBranch *) ClonesArray->First();

//     const float Crosssection = Info->Crosssection;
    const float Crosssection = Info->Crosssection *  Info->EventNumber / TreeReader->GetEntries();
//     delete TreeReader; // FixMe why

//     const float Crosssection = 1; //FIXME we dont use the crosssection

    Print(1 , "Weight", Crosssection);

    if (Signal) {

        Factory->AddSignalTree(const_cast<TTree *>(Tree), Crosssection);

    } else {

        Factory->AddBackgroundTree(const_cast<TTree *>(Tree), Crosssection);

    }


}

void hmva::HFactory::PrepareTrainingAndTestTree()
{

    Print(1 , "PrepareTrainingAndTestTree");

//     std::string TrainingAndTestOptions = "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V";
    const std::string TrainingAndTestOptions = "";

    Factory->PrepareTrainingAndTestTree(Mva->Cut, Mva->Cut, TrainingAndTestOptions);

}

void hmva::HFactory::BookMethods()
{

    Print(1 , "Book Methods");

    const std::string CutOptions = "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart";
//     std::string CutOptions = "VarProp=FSmart:VarTransform=PCA";
//     const std::string CutOptions = "";

    const std::string CutMethodName = Mva->CutMethodName + "_" + Mva->BackgroundName;

    Factory->BookMethod(TMVA::Types::kCuts, CutMethodName, CutOptions);

//     const std::string BdtOptions = "!H:!V:NTrees=1000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=2";
    const std::string BdtOptions = "!H:!V:NTrees=1000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20";
//     const std::string BdtOptions = "";

    const std::string BdtMethodName = Mva->BdtMethodName + "_" + Mva->BackgroundName;

    Factory->BookMethod(TMVA::Types::kBDT, BdtMethodName, BdtOptions);

}
