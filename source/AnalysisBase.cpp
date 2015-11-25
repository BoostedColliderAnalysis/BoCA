#include "AnalysisBase.hh"

#include <sys/stat.h>
#include <fstream>

#include "TTree.h"

#include "exroot/ExRootAnalysis.hh"

#include "Branches.hh"
#include "File.hh"
#include "Plotting.hh"
#include "Event.hh"
#include "Trainer.hh"
// #define DEBUG
#include "Debug.hh"

namespace analysis
{

void AnalysisBase::Initialize()
{
  Error(tagger().Name());
  mkdir(ProjectName().c_str(), 0700);
  tagger().ClearTreeNames();
}

exroot::TreeWriter AnalysisBase::TreeWriter(TFile& export_file, const std::string& export_tree_name, Stage)
{
    Note(export_tree_name.c_str());
    exroot::TreeWriter tree_writer(&export_file, export_tree_name.c_str());
    return tree_writer;
}

std::vector<File> AnalysisBase::files(Tag tag)
{
    Error(TagName(tag));
    return files_;
}

void AnalysisBase::PrepareFiles()
{
    files_.clear();
    tagger().ClearTreeNames();
    SetFiles(Tag::signal);
    SetFiles(Tag::background);
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

void AnalysisBase::NewFile(Tag tag, const Strings& names, float crosssection, const std::string& nice_name, int mass)
{
    files_.emplace_back(File(names, crosssection, nice_name, mass));
    tagger().AddTreeName(TreeName(names.front()), tag);
}

void AnalysisBase::NewFile(Tag tag, const Strings& names, const std::string& nice_name)
{
    files_.emplace_back(File(names, nice_name));
    tagger().AddTreeName(TreeName(names.front()), tag);
}

void AnalysisBase::NewFile(Tag tag, const std::string& name, float crosssection, const std::string& nice_name, int mass)
{
  files_.emplace_back(File({name}, crosssection, nice_name, mass));
  tagger().AddTreeName(TreeName(name), tag);
}

void AnalysisBase::NewFile(Tag tag, const std::string& name, const std::string& nice_name)
{
  files_.emplace_back(File({name}, nice_name));
  tagger().AddTreeName(TreeName(name), tag);
}

File AnalysisBase::File(const Strings& names, const std::string& nice_name) const
{
    return analysis::File(names, FilePath(), FileSuffix(), nice_name);
}

File AnalysisBase::File(const Strings& names, float crosssection, const std::string& nice_name, int mass) const
{
    return analysis::File(names, FilePath(), FileSuffix(), nice_name, crosssection, mass);
}

std::string AnalysisBase::FileName(const std::string&) const
{
    return ProcessName() + "_" + std::to_string(PreCut()) + "GeV";
}

std::string AnalysisBase::TreeName(const std::string& name) const
{
    return name + "-run_01";
}

const PreCuts& AnalysisBase::pre_cuts() const
{
    return pre_cuts_;
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
//   return "/media/toodles/Hajer/jan_old/final_sources/";
  
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
    RunTagger(Stage::trainer);
    RunTrainer();
}

void AnalysisBase::RunNormal()
{
    RunFast();
    RunTagger(Stage::reader);
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
    if (!Exists(tagger().FileName(stage, Tag::signal))) AnalysisLoop(stage);
}

void AnalysisBase::RunTrainer()
{
    PrepareFiles();
    TMVA::Types::EMVA mva = TMVA::Types::EMVA::kBDT;
    if (!Exists(tagger().WeightFileName(mva))){
      std::ofstream cout_file(tagger().FolderName() + ".txt");
      std::streambuf* cout = std::cout.rdbuf();
      std::cout.rdbuf(cout_file.rdbuf());
      Trainer trainer(tagger(), mva);
      std::cout.rdbuf(cout);
    }
}


void AnalysisBase::RunSignificance()
{
    PrepareFiles();
    if (!Exists(tagger().ExportFileName())) {
        Plotting plot(tagger());
        plot.OptimalSignificance();
    }
}

void AnalysisBase::RunEfficiency()
{
    PrepareFiles();
    if (!Exists(tagger().ExportFileName())) {
        Plotting plot(tagger());
        plot.TaggingEfficiency();
    }
}

void AnalysisBase::RunPlots()
{
    PrepareFiles();
    if (!Exists(tagger().ExportFolderName())) {
        Plotting plot(tagger());
        plot.RunPlots();
    }
}

}
