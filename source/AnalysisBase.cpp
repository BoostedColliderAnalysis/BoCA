#include "AnalysisBase.hh"

#include <sys/stat.h>

#include "TTree.h"

#include "exroot/ExRootAnalysis.hh"

#include "Branches.hh"
#include "Plot.hh"
#include "Event.hh"
#include "Factory.hh"

#include "Debug.hh"

namespace analysis {

exroot::TreeWriter AnalysisBase::TreeWriter(TFile& export_file, const std::string& export_tree_name, Stage)
{
    Note(export_tree_name.c_str());
    exroot::TreeWriter tree_writer(&export_file, export_tree_name.c_str());
    return tree_writer;
}

bool AnalysisBase::Missing(const std::string& name) const
{
    Error(name);
    struct stat buffer;
    return (stat(name.c_str(), &buffer) != 0);
}

std::vector<analysis::File> AnalysisBase::files(Tag tag)
{
    Error(Name(tag));
    return files_;
}

int AnalysisBase::PassPreCut(const analysis::Event&) const
{
    Error("no pre cut applied");
    return 1;
}

void AnalysisBase::PrepareFiles()
{
    files_.clear();
    tagger().ClearTreeNames();
    SetFiles(analysis::Tag::signal);
    SetFiles(analysis::Tag::background);
}

std::string AnalysisBase::ProjectName() const
{
    return "ProjectName";
}

long AnalysisBase::EventNumberMax() const
{
    return 100000;
}

std::string AnalysisBase::ProcessName() const
{
    return "Process";
}

void AnalysisBase::NewFile(Tag tag, const std::string& name, float crosssection, const std::string& nice_name)
{
    switch (tag) {
    case Tag::signal :
        NewSignalFile(name, crosssection, nice_name);
        break;
    case Tag::background :
        NewBackgroundFile(name, crosssection, nice_name);
        break;
    }
}

void AnalysisBase::NewFile(Tag tag, const std::string& name, const std::string& nice_name)
{
    switch (tag) {
    case Tag::signal :
        NewSignalFile(name, nice_name);
        break;
    case Tag::background :
        NewBackgroundFile(name, nice_name);
        break;
    }
}

void AnalysisBase::NewSignalFile(const std::string& name, const std::string& nice_name)
{
    files_.emplace_back(File(name, nice_name));
    tagger().AddSignalTreeName(TreeName(name));
}

void AnalysisBase::NewBackgroundFile(const std::string& name, const std::string& nice_name)
{
    files_.emplace_back(File(name, nice_name));
    tagger().AddBackgroundTreeName(TreeName(name));
}

void AnalysisBase::NewSignalFile(const std::string& name, float crosssection, const std::string& nice_name)
{
    files_.emplace_back(File(name, crosssection, nice_name));
    tagger().AddSignalTreeName(TreeName(name));
}

void AnalysisBase::NewBackgroundFile(const std::string& name, float crosssection, const std::string& nice_name)
{
    files_.emplace_back(File(name, crosssection, nice_name));
    tagger().AddBackgroundTreeName(TreeName(name));
}

analysis::File AnalysisBase::File(const std::string& name, const std::string& nice_name) const
{
    return analysis::File(name, FilePath(), FileSuffix(), nice_name);
}

analysis::File AnalysisBase::File(const std::string& name, float crosssection, const std::string& nice_name) const
{
    return analysis::File(name, FilePath(), FileSuffix(), crosssection, nice_name);
}

std::string AnalysisBase::FileName(const std::string&) const
{
    return ProcessName() + "_" + std::to_string(PreCut()) + "GeV";
}

std::string AnalysisBase::TreeName(const std::string& name) const
{
    return name + "-run_01";
}

PreCuts& AnalysisBase::pre_cuts()
{
    return pre_cuts_;
}

std::string AnalysisBase::FileSuffix() const
{
    return ".root";
}

std::string AnalysisBase::FilePath() const
{
    return "~/Projects/";
}

int AnalysisBase::BackgroundFileNumber() const
{
//     return configuration_.BackgroundFileNumber();
    return 1;
}

int AnalysisBase::PreCut() const
{
//     return configuration_.PreCut();
    return 0;
}

int AnalysisBase::Mass() const
{
//     return configuration_.Mass();
    return 1;
}

void AnalysisBase::RunFast()
{
    RunTagger(analysis::Stage::trainer);
    RunFactory();
}

void AnalysisBase::RunNormal()
{
    RunFast();
    RunTagger(analysis::Stage::reader);
}

void AnalysisBase::RunFullSignificance()
{
    RunNormal();
    RunSignificance();
}

void AnalysisBase::ClearFiles()
{
    files_.clear();
}

void AnalysisBase::RunFullEfficiency()
{
    RunNormal();
    RunEfficiency();
}

void AnalysisBase::RunTagger(Stage stage)
{
  if (Missing(tagger().SignalFileName(stage))) AnalysisLoop(stage);
}

// void AnalysisBase::RunFactory()
// {
//     PrepareFiles();
//     if (Missing(tagger().FactoryFileName())) analysis::Factory factory(tagger());
// }

void AnalysisBase::RunFactory()
{
    PrepareFiles();
    if (Missing(tagger().WeightFileName(TMVA::Types::EMVA::kBDT))) analysis::Factory factory(tagger());
}


void AnalysisBase::RunSignificance()
{
    PrepareFiles();
    //     if (Missing(tagger().ExportFileName())) {
    analysis::Plot plot(tagger());
    plot.OptimalSignificance();
//     }
}

void AnalysisBase::RunEfficiency()
{
    PrepareFiles();
    //     if (Missing(tagger().ExportFileName())) {
    analysis::Plot plot(tagger());
    plot.TaggingEfficiency();
//     }
}

void AnalysisBase::RunPlots()
{
    PrepareFiles();
    //   if (Missing(tagger().ExportFileName())) {
    analysis::Plot plot(tagger());
    plot.RunPlots();
//   }
}

}
