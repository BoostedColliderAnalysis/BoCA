# include "HFactory.hh"



hanalysis::HFactory::HFactory(HMva *const NewMva)
{
//     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification , "Constructor");
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
}

hanalysis::HFactory::~HFactory()
{
    Print(HNotification , "Destructor");
    delete Factory;
}

void hanalysis::HFactory::NewFactory()
{
    Print(HNotification , "New Factory");
    const std::string FactoryOutputName = "Mva" + Mva->GetTaggerName();
    const std::string OutputFileName = Mva->GetAnalysisName() + "/" + FactoryOutputName + ".root";
    OutputFile = TFile::Open(OutputFileName.c_str(), "Recreate");
    const std::string FactoryOptions = "";
    Factory = new TMVA::Factory(Mva->GetTaggerName(), OutputFile, FactoryOptions);
}

void hanalysis::HFactory::AddVariables()
{
    Print(HNotification , "Add Variables");
    (TMVA::gConfig().GetIONames()).fWeightFileDir = Mva->GetAnalysisName();
    for (const auto & Observable : Mva->GetObservables())
        Factory->AddVariable(Observable.Expression, Observable.Title, Observable.Unit, Observable.Type);
    for (const auto & Spectator : Mva->GetSpectators())
        Factory->AddSpectator(Spectator.Expression, Spectator.Title, Spectator.Unit, Spectator.Type);
}

void hanalysis::HFactory::GetTrees()
{
    Print(HNotification , "Get Trees");
    for (const auto & SignalName : Mva->GetSignalNames()) {

        std::string SignalFileName = Mva->GetAnalysisName() + "/" + SignalName + ".root";
        if (gSystem->AccessPathName(SignalFileName.c_str())) Print(HError, "File not found", SignalFileName);
        TFile *SignalFile = TFile::Open(SignalFileName.c_str());
        Print(HNotification , "Signal File", SignalFile->GetName());

        for (int TreeNumber : HRange(Mva->GetSignalTreeNames().size())) AddTree(SignalFile, Mva->GetSignalTreeNames()[TreeNumber], 1);

    }

    for (const auto & BackgroundName : Mva->GetBackgroundNames()) {

        std::string BackgroundFileName = Mva->GetAnalysisName() + "/" + BackgroundName + ".root";
        if (gSystem->AccessPathName(BackgroundFileName.c_str())) Print(HError, "File not found", BackgroundFileName);
        TFile *BackgroundFile = TFile::Open(BackgroundFileName.c_str());
        Print(HNotification , "Background File", BackgroundFile->GetName());

        for (const auto & BackgroundTreeName : Mva->GetBackgroundTreeNames()) AddTree(BackgroundFile, BackgroundTreeName, 0);

    }

}

void hanalysis::HFactory::AddTree(const TFile *const File, const std::string &TreeName, const bool Signal)
{

    Print(HNotification , "Add Tree", TreeName);

    const TTree *const Tree = (TTree *)(const_cast<TFile *>(File)->Get(TreeName.c_str()));

//     Print(HError,"Branch Name",Mva->CandidateBranchName.c_str());
//     const_cast<TTree *>(Tree)->GetBranch(Mva->CandidateBranchName.c_str());
//     const ExRootTreeReader *const TreeReader = new ExRootTreeReader(const_cast<TTree *>(Tree));

//     const TClonesArray *const ClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(Mva->WeightBranchName.c_str());
//     const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(0);
//     HInfoBranch *Info = (HInfoBranch *) ClonesArray->First();

//     const float Crosssection = Info->Crosssection;
//     const float Crosssection = Info->Crosssection *  Info->EventNumber / TreeReader->GetEntries();
//     delete TreeReader; // FixMe why

    const float Crosssection = 1.; //FIXME we dont use the crosssection

    Print(HNotification , "Weight", Crosssection);

    if (Signal) {

        Factory->AddSignalTree(const_cast<TTree *>(Tree), Crosssection);

    } else {

        Factory->AddBackgroundTree(const_cast<TTree *>(Tree), Crosssection);

    }


}

void hanalysis::HFactory::PrepareTrainingAndTestTree()
{

    Print(HNotification , "PrepareTrainingAndTestTree");

//     std::string TrainingAndTestOptions = "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V";
    const std::string TrainingAndTestOptions ="";
//     "nTrain_Background=1000000:nTest_Background=1000000";

    Factory->PrepareTrainingAndTestTree(Mva->GetCut(), Mva->GetCut(), TrainingAndTestOptions);

}

void hanalysis::HFactory::BookMethods()
{

    Print(HNotification , "Book Methods");

    const std::string CutOptions = "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart";
//     std::string CutOptions = "VarProp=FSmart:VarTransform=PCA";
//     const std::string CutOptions = "";

//     const std::string CutMethodName = Mva->CutMethodName + "_" + Mva->BackgroundName;
    const std::string CutMethodName = Mva->GetCutMethodName();

//     Factory->BookMethod(TMVA::Types::kCuts, CutMethodName, CutOptions);

//     const std::string BdtOptions = "!H:!V:NTrees=1000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=2";
    const std::string BdtOptions = "!H:!V:NTrees=1000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20";
//     const std::string BdtOptions = "";

//     const std::string BdtMethodName = Mva->BdtMethodName + "_" + Mva->BackgroundName;
    const std::string BdtMethodName = Mva->GetBdtMethodName();

    Factory->BookMethod(TMVA::Types::kBDT, BdtMethodName, BdtOptions);

}
