# include "HFactory.hh"

hanalysis::HFactory::HFactory(HMva &tagger) : tagger_(tagger)
// , factory_(CreateFactory())
{
    DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification , "Constructor");
//     Mva = &NewMva;
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
    const std::string FactoryOutputName = "Mva" + tagger_.GetTaggerName();
    const std::string OutputFileName = tagger_.GetAnalysisName() + "/" + FactoryOutputName + ".root";
    OutputFile = TFile::Open(OutputFileName.c_str(), "Recreate");
    const std::string FactoryOptions = "!Color:!Silent";
//     const std::string FactoryOptions = "";
    Factory = new TMVA::Factory(tagger_.GetTaggerName(), OutputFile, FactoryOptions);
}

TMVA::Factory &hanalysis::HFactory::CreateFactory()
{
  Print(HNotification , "New Factory");
  const std::string FactoryOutputName = "Mva" + tagger_.GetTaggerName();
  const std::string OutputFileName = tagger_.GetAnalysisName() + "/" + FactoryOutputName + ".root";
  OutputFile = TFile::Open(OutputFileName.c_str(), "Recreate");
  const std::string FactoryOptions = "!Color:!Silent";
  //     const std::string FactoryOptions = "";
  TMVA::Factory factory(tagger_.GetTaggerName(), OutputFile, FactoryOptions);
  return factory;
}

void hanalysis::HFactory::AddVariables()
{
    Print(HNotification , "Add Variables");
    (TMVA::gConfig().GetIONames()).fWeightFileDir = tagger_.GetAnalysisName();
    for (const auto & Observable : tagger_.observables())
        Factory->AddVariable(Observable.expression(), Observable.title(), Observable.unit(), Observable.type());
    for (const auto & Spectator : tagger_.spectators())
      Factory->AddSpectator(Spectator.expression(), Spectator.title(), Spectator.unit(), Spectator.type());
}

int hanalysis::HFactory::GetTrees()
{
    Print(HNotification , "Get Trees");

    int SignalNumber = 0;
    for (const auto & SignalName : tagger_.GetSignalNames()) {

        std::string SignalFileName = tagger_.GetAnalysisName() + "/" + SignalName + ".root";
        if (gSystem->AccessPathName(SignalFileName.c_str())) Print(HError, "File not found", SignalFileName);
        TFile &SignalFile = *TFile::Open(SignalFileName.c_str());
        Print(HNotification , "Signal File", SignalFile.GetName(),tagger_.GetSignalTreeNames().size());

        for (int TreeNumber : Range(tagger_.GetSignalTreeNames().size())) {
            Print(HNotification , "signal Tree Name", tagger_.GetSignalTreeNames()[TreeNumber]);
            SignalNumber += AddTree(SignalFile, tagger_.GetSignalTreeNames()[TreeNumber], 1);
        }

    }

    int BackgroundNumber = 0;
    for (const auto & BackgroundName : tagger_.GetBackgroundNames()) {

        std::string BackgroundFileName = tagger_.GetAnalysisName() + "/" + BackgroundName + ".root";
        if (gSystem->AccessPathName(BackgroundFileName.c_str())) Print(HError, "File not found", BackgroundFileName);
        TFile &BackgroundFile = *TFile::Open(BackgroundFileName.c_str());
        Print(HNotification , "Background File", BackgroundFile.GetName(),tagger_.GetBackgroundTreeNames().size());

        for (const auto & BackgroundTreeName : tagger_.GetBackgroundTreeNames()) {
            Print(HNotification , "Background Tree Name", BackgroundTreeName);
            BackgroundNumber += AddTree(BackgroundFile, BackgroundTreeName, 0);
        }

    }

    Print(HError, "Event Numbers", SignalNumber, BackgroundNumber);

    return (std::min(SignalNumber, BackgroundNumber) / 2);
}

int hanalysis::HFactory::AddTree(const TFile &File, const std::string &TreeName, const bool Signal)
{

    Print(HError , "Add Tree", TreeName);

    if (!File.GetListOfKeys()->Contains(TreeName.c_str()))return 0;

//     if (gSystem->Acces(FileName.c_str()))

// //     for (int TreeNumber = 0; TreeNumber < const_cast<TFile *>(File)->GetListOfFree()->GetEntriesFast(); ++TreeNumber) D{
//         if (static_cast<TBranch *>(const_cast<TTree *>(Tree)->GetListOfBranches()->At(TreeNumber))->GetName() != Mva.GetBranchName()) return 0;
//     }

    const TTree *const Tree = (TTree *)(const_cast<TFile &>(File).Get(TreeName.c_str()));

    Print(HError, "Branch Name", tagger_.GetBranchName().c_str());
    const_cast<TTree *>(Tree)->GetBranch(tagger_.GetBranchName().c_str());
    const ExRootTreeReader *const TreeReader = new ExRootTreeReader(const_cast<TTree *>(Tree));


    const TClonesArray *const ClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(tagger_.GetWeightBranchName().c_str());
    const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(0);
    HInfoBranch *Info = (HInfoBranch *) ClonesArray->First();

//     const float Crosssection = Info->Crosssection;
//     const float Crosssection = Info->Crosssection *  Info->EventNumber / TreeReader->GetEntries();
    const float Crosssection = Info->Crosssection / TreeReader->GetEntries(); // this takes care of the multiplicity

//     const float Crosssection = 1.; //FIXME we dont use the crosssection

    Print(HNotification , "Weight", Crosssection);

    if (Signal) Factory->AddSignalTree(const_cast<TTree *>(Tree), Crosssection);
    else Factory->AddBackgroundTree(const_cast<TTree *>(Tree), Crosssection);





    // const int Entries = TreeReader->GetEntries(); // old code

    // NewCode
    int Entries = 0;
    const TClonesArray *const EventClonesArray = const_cast<ExRootTreeReader *>(TreeReader)->UseBranch(tagger_.GetBranchName().c_str());
    for (int Entry = 0; Entry < const_cast<ExRootTreeReader *>(TreeReader)->GetEntries(); ++Entry) {
      const_cast<ExRootTreeReader *>(TreeReader)->ReadEntry(Entry);
      Entries += EventClonesArray->GetEntries();
    }
    // end new code



//     delete TreeReader; // FIXME why
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
    const std::string TrainingAndTestOptions = NumberOptions + "";
//     "nTrain_Background=100000:nTest_Background=100000";

    Factory->PrepareTrainingAndTestTree(tagger_.GetCut(), tagger_.GetCut(), TrainingAndTestOptions);

}

void hanalysis::HFactory::BookMethods()
{

    Print(HNotification , "Book Methods");

//     const std::string CutOptions = "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart";
//     std::string CutOptions = "VarProp=FSmart:VarTransform=PCA";
//     const std::string CutOptions = "";

//     const std::string CutMethodName = Mva.CutMethodName + "_" + Mva.BackgroundName;

    //     Factory->BookMethod(TMVA::Types::kCuts, Mva.GetCutMethodName(), CutOptions);

//     const std::string BdtOptions = "!H:!V:NTrees=1000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=2";
    const std::string BdtOptions =
//     "";
        "NTrees=1000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20";//:CreateMVAPdfs:DoBoostMonitor";
//     const std::string BdtOptions = "";

//     const std::string BdtMethodName = Mva.BdtMethodName + "_" + Mva.BackgroundName;

    Factory->BookMethod(TMVA::Types::kBDT, tagger_.BdtMethodName(), BdtOptions);

}

