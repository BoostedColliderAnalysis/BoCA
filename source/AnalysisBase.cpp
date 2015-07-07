#include "AnalysisBase.hh"

#include <sys/stat.h>

#include "TTree.h"

#include "exroot/ExRootAnalysis.hh"

#include "Branches.hh"
#include "Plot.hh"
#include "Event.hh"
#include "Factory.hh"

#define DEBUG

#include "Debug.hh"

namespace analysis
{

InfoBranch AnalysisBase::FillInfoBranch(const exroot::TreeReader &tree_reader, const File &file)
{
    InfoBranch info_branch;
    info_branch.Crosssection = file.crosssection();
    info_branch.CrosssectionError = file.crosssection_error();
    info_branch.Mass = file.mass();
    info_branch.EventNumber = std::min((int)tree_reader.GetEntries(), EventNumberMax());
    info_branch.Name = file.nice_name();
    return info_branch;
}

std::string AnalysisBase::ExportName(const Stage stage, const Tag tag) const
{
    Note(tagger().name(stage, tag));
    return ProjectName() + "/" + tagger().name(stage, tag) + FileSuffix();
}

exroot::TreeWriter AnalysisBase::TreeWriter(TFile &export_file, const std::string &export_tree_name, Stage stage)
{
    Note(export_tree_name.c_str());
    exroot::TreeWriter tree_writer(&export_file, export_tree_name.c_str());
//     tagger().SetTreeBranch(tree_writer, stage);
    return tree_writer;
}

bool AnalysisBase::Missing(const std::string &name) const
{
    Error(name);
    struct stat buffer;
    return (stat(name.c_str(), &buffer) != 0);
}

std::vector< File > AnalysisBase::Files(const Tag tag)
{
    Error(Name(tag));
    return files_;
}

void AnalysisBase::SetFiles(const Tag tag)
{
    Error("should be subclassed", Name(tag));
}

int AnalysisBase::PassPreCut(const Event &)
{
    Error("no pre cut applied");
    return 1;
}

// void AnalysisBase::SetConfig(const Configuration &configuration)
// {
//     configuration_ = configuration;
// }

void AnalysisBase::PrepareFiles()
{
    files_.clear();
    tagger().clear_tree_names();
    SetFiles(analysis::Tag::signal);
    SetFiles(analysis::Tag::background);
}

std::string AnalysisBase::ProjectName() const
{
    return "ProjectName";
}

int AnalysisBase::EventNumberMax() const
{
    return 100000;
}

std::string AnalysisBase::ProcessName() const
{
    return "Process";
}

void AnalysisBase::NewFile(const Tag tag, const std::string &name, const float crosssection, const std::string &nice_name)
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

void AnalysisBase::NewFile(const Tag tag, const std::string &name, const std::string &nice_name)
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

void AnalysisBase::NewSignalFile(const std::string &name, const std::string &nice_name)
{
    files_.emplace_back(get_file(name, nice_name));
    tagger().AddSignalTreeName(TreeName(name));
}

void AnalysisBase::NewBackgroundFile(const std::string &name, const std::string &nice_name)
{
    files_.emplace_back(get_file(name, nice_name));
    tagger().AddBackgroundTreeName(TreeName(name));
}

void AnalysisBase::NewSignalFile(const std::string &name, const float crosssection, const std::string &nice_name)
{
  files_.emplace_back(get_file(name, crosssection, nice_name));
  tagger().AddSignalTreeName(TreeName(name));
}

void AnalysisBase::NewBackgroundFile(const std::string &name, const float crosssection, const std::string &nice_name)
{
  files_.emplace_back(get_file(name, crosssection, nice_name));
  tagger().AddBackgroundTreeName(TreeName(name));
}

// void AnalysisBase::NewFile(const Tag tag, const std::string &name, const float crosssection)
// {
//     switch (tag) {
//     case Tag::signal :
//         NewSignalFile(name, crosssection);
//         break;
//     case Tag::background :
//         NewBackgroundFile(name, crosssection);
//         break;
//     }
// }

// void AnalysisBase::NewSignalFile(const std::string &name, const float crosssection)
// {
//     files_.emplace_back(get_file(name, crosssection));
//     tagger().AddSignalTreeName(TreeName(name));
// }

// void AnalysisBase::NewBackgroundFile(const std::string &name, const float crosssection)
// {
//     files_.emplace_back(get_file(name, crosssection));
//     tagger().AddBackgroundTreeName(TreeName(name));
// }

File AnalysisBase::get_file(const std::string &name, const std::string &nice_name) const
{
    return File(name, FilePath(), FileSuffix(), nice_name);
}

File AnalysisBase::get_file(const std::string &name, const float crosssection, const std::string &nice_name) const
{
  return File(name, FilePath(), FileSuffix(), crosssection, nice_name);
}

File AnalysisBase::get_file(const std::string &name, const float crosssection) const
{
    return File(name, FilePath(), FileSuffix(), crosssection);
}

std::string AnalysisBase::FileName(const std::string &name) const
{
    return ProcessName() + "_" + std::to_string(PreCut()) + "GeV";
}

std::string AnalysisBase::TreeName(const std::string &name) const
{
    return name + "-run_01";
}

PreCuts &AnalysisBase::pre_cuts()
{
    return pre_cuts_;
}

//   Tagger &AnalysisBase::tagger()
//   {
//     return tagger_;
//   }

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
}

int AnalysisBase::PreCut() const
{
//     return configuration_.PreCut();
}

int AnalysisBase::Mass() const
{
//     return configuration_.Mass();
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

std::string AnalysisBase::PathName(const std::string &file_name) const
{
    Error(file_name);
    return ProjectName() + "/" + file_name + ".root";
}

void AnalysisBase::RunTagger(Stage stage)
{
    if (Missing(PathName(tagger().name(stage)))) AnalysisLoop(stage);
}

void AnalysisBase::RunFactory()
{
    PrepareFiles();
    if (Missing(PathName(tagger().factory_name()))) analysis::Factory factory(tagger());
}

void AnalysisBase::RunSignificance()
{
    PrepareFiles();
    if (Missing(PathName(tagger().export_name()))) {
        analysis::Plot plot(tagger());
        plot.OptimalSignificance();
    }
}

void AnalysisBase::RunEfficiency()
{
    PrepareFiles();
    if (Missing(PathName(tagger().export_name()))) {
        analysis::Plot plot(tagger());
        plot.TaggingEfficiency();
    }
}

}


