# include "HFactory.hh"

hanalysis::HFactory::HFactory(HMva &NewMva)
{
    DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification , "Constructor");
    Mva = &NewMva;
    NewFactory();
    AddVariables();
    PrepareTrainingAndTestTree(GetTrees());
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
//     delete Mva; // TODO do I need this?
}

void hanalysis::HFactory::NewFactory()
{
    Print(HNotification , "New Factory");
    const std::string FactoryOutputName = "Mva" + Mva->GetTaggerName();
    const std::string OutputFileName = Mva->GetAnalysisName() + "/" + FactoryOutputName + ".root";
    OutputFile = TFile::Open(OutputFileName.c_str(), "Recreate");
    const std::string FactoryOptions = "!Color:!Silent:V";
//     const std::string FactoryOptions = "";
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

int hanalysis::HFactory::GetTrees()
{
    Print(HNotification , "Get Trees");

    int SignalNumber = 0;
    for (const auto & SignalName : Mva->GetSignalNames()) {

        std::string SignalFileName = Mva->GetAnalysisName() + "/" + SignalName + ".root";
        if (gSystem->AccessPathName(SignalFileName.c_str())) Print(HError, "File not found", SignalFileName);
        TFile *SignalFile = TFile::Open(SignalFileName.c_str());
        Print(HNotification , "Signal File", SignalFile->GetName(),Mva->GetSignalTreeNames().size());

        for (int TreeNumber : HRange(Mva->GetSignalTreeNames().size())) {
            Print(HNotification , "signal Tree Name", Mva->GetSignalTreeNames()[TreeNumber]);
            SignalNumber += AddTree(SignalFile, Mva->GetSignalTreeNames()[TreeNumber], 1);
        }

    }

    int BackgroundNumber = 0;
    for (const auto & BackgroundName : Mva->GetBackgroundNames()) {

        std::string BackgroundFileName = Mva->GetAnalysisName() + "/" + BackgroundName + ".root";
        if (gSystem->AccessPathName(BackgroundFileName.c_str())) Print(HError, "File not found", BackgroundFileName);
        TFile *BackgroundFile = TFile::Open(BackgroundFileName.c_str());
        Print(HNotification , "Background File", BackgroundFile->GetName(),Mva->GetBackgroundTreeNames().size());

        for (const auto & BackgroundTreeName : Mva->GetBackgroundTreeNames()) {
            Print(HNotification , "Background Tree Name", BackgroundTreeName);
            BackgroundNumber += AddTree(BackgroundFile, BackgroundTreeName, 0);
        }

    }

    Print(HError, "Event Numbers", SignalNumber, BackgroundNumber);

    return (std::min(SignalNumber, BackgroundNumber) / 2);
}

int hanalysis::HFactory::AddTree(const TFile *const File, const std::string &TreeName, const bool Signal)
{

    Print(HError , "Add Tree", TreeName);

    if (!File->GetListOfKeys()->Contains(TreeName.c_str()))return 0;

//     if (gSystem->Acces(FileName.c_str()))

// //     for (int TreeNumber = 0; TreeNumber < const_cast<TFile *>(File)->GetListOfFree()->GetEntriesFast(); ++TreeNumber) D{
//         if (static_cast<TBranch *>(const_cast<TTree *>(Tree)->GetListOfBranches()->At(TreeNumber))->GetName() != Mva->GetBranchName()) return 0;
//     }

    const TTree *const Tree = (TTree *)(const_cast<TFile *>(File)->Get(TreeName.c_str()));

    Print(HError, "Branch Name", Mva->GetBranchName().c_str());
    const_cast<TTree *>(Tree)->GetBranch(Mva->GetBranchName().c_str());
    const ExRootTreeReader *const TreeReader = new ExRootTreeReader(const_cast<TTree *>(Tree));

    const int Entries = TreeReader->GetEntries();

    const TClonesArray *const ClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(Mva->GetWeightBranchName().c_str());
    const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(0);
    HInfoBranch *Info = (HInfoBranch *) ClonesArray->First();

    const float Crosssection = Info->Crosssection;
//     const float Crosssection = Info->Crosssection *  Info->EventNumber / TreeReader->GetEntries();
//     delete TreeReader; // FIXME why

//     const float Crosssection = 1.; //FIXME we dont use the crosssection

    Print(HNotification , "Weight", Crosssection);

    if (Signal) Factory->AddSignalTree(const_cast<TTree *>(Tree), Crosssection);
    else Factory->AddBackgroundTree(const_cast<TTree *>(Tree), Crosssection);

    return Entries;
}

void hanalysis::HFactory::PrepareTrainingAndTestTree(const int EventNumber)
{
    Print(HError , "PrepareTrainingAndTestTree");

    std::string NumberOptions = "nTrain_Background=" + std::to_string(EventNumber) + ":nTest_Background=" + std::to_string(EventNumber) + ":nTrain_Signal=" + std::to_string(EventNumber) + ":nTest_Signal=" + std::to_string(EventNumber);

//     std::string NumberOptions = "nTrain_Background=" + std::to_string(2*EventNumber)
//     + ":nTest_Background=" + std::to_string(EventNumber)
//     + ":nTrain_Signal=" + std::to_string(2*EventNumber)
//     + ":nTest_Signal=" + std::to_string(EventNumber)
    ;

//     Print(HError, "NumberOptions", NumberOptions);

//     std::string TrainingAndTestOptions = "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V";
    const std::string TrainingAndTestOptions = NumberOptions + ":V";
//     "nTrain_Background=100000:nTest_Background=100000";

    Factory->PrepareTrainingAndTestTree(Mva->GetCut(), Mva->GetCut(), TrainingAndTestOptions);

}

void hanalysis::HFactory::BookMethods()
{

    Print(HNotification , "Book Methods");

//     const std::string CutOptions = "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart";
//     std::string CutOptions = "VarProp=FSmart:VarTransform=PCA";
//     const std::string CutOptions = "";

//     const std::string CutMethodName = Mva->CutMethodName + "_" + Mva->BackgroundName;

    //     Factory->BookMethod(TMVA::Types::kCuts, Mva->GetCutMethodName(), CutOptions);

//     const std::string BdtOptions = "!H:!V:NTrees=1000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=2";
    const std::string BdtOptions =
//     "";
        "H:V:NTrees=1000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20";//:CreateMVAPdfs:DoBoostMonitor";
//     const std::string BdtOptions = "";

//     const std::string BdtMethodName = Mva->BdtMethodName + "_" + Mva->BackgroundName;

    Factory->BookMethod(TMVA::Types::kBDT, Mva->GetBdtMethodName(), BdtOptions);

}
