# include "Factory.hh"
# include "TSystem.h"
# include "TMVA/Config.h"
# include "TClonesArray.h"
# include "Branches.hh"

namespace analysis {

Factory::Factory(Tagger &tagger) : tagger_(tagger) , factory_(tagger.tagger_name(), output_file(), factory_options())
{
//     DebugLevel = Severity::debug;
    Print(Severity::notification , "Constructor");
    AddVariables();
    PrepareTrainingAndTestTree(GetTrees());
    BookMethods();
    factory().TrainAllMethods();
    factory().TestAllMethods();
    factory().EvaluateAllMethods();
}

std::string Factory::factory_options()
{
    return "!Color:!Silent";
}

TFile *Factory::output_file() const
{
    const std::string factory_name = "Mva" + tagger().tagger_name();
    const std::string file_name = tagger().analysis_name() + "/" + factory_name + ".root";
    return TFile::Open(file_name.c_str(), "Recreate");
}

void Factory::AddVariables()
{
    Print(Severity::notification , "Add Variables");
    TMVA::gConfig().GetIONames().fWeightFileDir = tagger().analysis_name();
    for (const auto & observable : tagger().observables())
        factory().AddVariable(observable.expression(), observable.title(), observable.unit(), observable.type());
    for (const auto & spectator : tagger().spectators())
        factory().AddSpectator(spectator.expression(), spectator.title(), spectator.unit(), spectator.type());
}

int Factory::GetTrees()
{
    Print(Severity::notification , "Trees");
    int signal_number = 0;
    for (const auto & signal_name : tagger().signal_file_names()) {
        Print(Severity::notification , "Signal", signal_name);
        std::string signal_file_name = tagger().analysis_name() + "/" + signal_name + ".root";
        if (gSystem->AccessPathName(signal_file_name.c_str())) Print(Severity::error, "File not found", signal_file_name);
        TFile &signal_file = *TFile::Open(signal_file_name.c_str());
        Print(Severity::notification , "Signal File", signal_file.GetName(), tagger().signal_tree_names().size());
        for (int tree_number : Range(tagger().signal_tree_names().size())) {
            Print(Severity::notification , "signal Tree Name", tagger().signal_tree_names()[tree_number]);
            signal_number += AddTree(signal_file, tagger().signal_tree_names()[tree_number], Tag::signal);
        }
    }
    int background_number = 0;
    for (const auto & background_name : tagger().background_file_names()) {
        Print(Severity::notification , "Background", background_name);
        std::string background_file_name = tagger().analysis_name() + "/" + background_name + ".root";
        if (gSystem->AccessPathName(background_file_name.c_str())) Print(Severity::error, "File not found", background_file_name);
        TFile &background_file = *TFile::Open(background_file_name.c_str());
        Print(Severity::notification , "Background File", background_file.GetName(), tagger().background_tree_names().size());
        for (const auto & background_tree_name : tagger().background_tree_names()) {
            Print(Severity::notification , "Background Tree Name", background_tree_name);
            background_number += AddTree(background_file, background_tree_name, Tag::background);
        }
    }
    Print(Severity::error, "event Numbers", signal_number, background_number);
    return std::min(signal_number, background_number) / 2;
}

int Factory::AddTree(TFile &file, const std::string &tree_name, const Tag tag)
{
    Print(Severity::error , "Add Tree", tree_name);
    if (!file.GetListOfKeys()->Contains(tree_name.c_str()))return 0;
    TTree &tree = static_cast<TTree &>(*file.Get(tree_name.c_str()));
    Print(Severity::error, "Branch Name", tagger().branch_name().c_str());
    tree.GetBranch(tagger().branch_name().c_str());
    exroot::TreeReader &tree_reader = *new exroot::TreeReader(&tree); // FIXME nasty hack with memeory leak; necessary because the tree reader destructor closes the file which makes it invisible for tmva; reimplment in a cleaner way!!
    TClonesArray &clones_array = *tree_reader.UseBranch(tagger().weight_branch_name().c_str());
    tree_reader.ReadEntry(0);
//     const float crosssection = static_cast<InfoBranch &>(*clones_array.First()).Crosssection / tree_reader.GetEntries(); // this takes care of the multiplicity
    const float crosssection = dynamic_cast<InfoBranch &>(*clones_array.First()).Crosssection / tree_reader.GetEntries(); // this takes care of the multiplicity
    Print(Severity::notification , "Weight", crosssection);
    switch (tag) {
    case Tag::signal :
        factory().AddSignalTree(&tree, crosssection);
        break;
    case Tag::background :
        factory().AddBackgroundTree(&tree, crosssection);
        break;
    }
    int entries = 0;
    TClonesArray &event_clones_array = *tree_reader.UseBranch(tagger().branch_name().c_str());
    for (int entry = 0; entry < tree_reader.GetEntries(); ++entry) {
        tree_reader.ReadEntry(entry);
        entries += event_clones_array.GetEntries();
    }
    return entries;
}

void Factory::PrepareTrainingAndTestTree(const int event_number)
{
    Print(Severity::error , "PrepareTrainingAndTestTree");
    std::string number_options = "nTrain_Background=" + std::to_string(event_number) + ":nTest_Background=" + std::to_string(event_number) + ":nTrain_Signal=" + std::to_string(event_number) + ":nTest_Signal=" + std::to_string(event_number);
//     std::string TrainingAndTestOptions = "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=Numevents:!V";
    const std::string training_and_test_options = number_options + "";
    factory().PrepareTrainingAndTestTree(tagger().cut(), tagger().cut(), training_and_test_options);
}

void Factory::BookMethods()
{
    Print(Severity::notification , "Book Methods");
    const std::string bdt_options = "NTrees=1000:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20";
    //:CreateMVAPdfs:DoBoostMonitor";
    factory().BookMethod(TMVA::Types::kBDT, tagger().bdt_method_name(), bdt_options);
}

}
