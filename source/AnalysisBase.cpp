/**
 * Copyright (C) 2015 Jan Hajer
 */
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
#include "Debug.hh"

namespace boca
{

void AnalysisBase::Initialize()
{
    Error(tagger().Name());
    working_path_ = WorkingPath();
    mkdir(ProjectName().c_str(), 0700);
    tagger().ClearTreeNames();
}

exroot::TreeWriter AnalysisBase::TreeWriter(TFile& export_file, std::string const& export_tree_name, Stage)
{
    Note(export_tree_name.c_str());
    exroot::TreeWriter tree_writer(&export_file, export_tree_name.c_str());
    return tree_writer;
}

std::vector<File> AnalysisBase::files(Tag tag)
{
    Error(Name(tag));
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

void AnalysisBase::NewFile(Tag tag, Strings const& names, float crosssection, std::string const& nice_name, int mass)
{
    files_.emplace_back(File(names, crosssection, nice_name, mass));
    tagger().AddTreeName(TreeName(names.front()), tag);
}

void AnalysisBase::NewFile(Tag tag, Strings const& names, std::string const& nice_name)
{
    files_.emplace_back(File(names, nice_name));
    tagger().AddTreeName(TreeName(names.front()), tag);
}

void AnalysisBase::NewFile(Tag tag, std::string const& name, float crosssection, std::string const& nice_name, int mass)
{
    files_.emplace_back(File( {name}, crosssection, nice_name, mass));
    tagger().AddTreeName(TreeName(name), tag);
}

void AnalysisBase::NewFile(Tag tag, std::string const& name, std::string const& nice_name)
{
    files_.emplace_back(File( {name}, nice_name));
    tagger().AddTreeName(TreeName(name), tag);
}

File AnalysisBase::File(Strings const& names, std::string const& nice_name) const
{
    return boca::File(names, FilePath(), FileSuffix(), nice_name);
}

File AnalysisBase::File(Strings const& names, float crosssection, std::string const& nice_name, int mass) const
{
    return boca::File(names, FilePath(), FileSuffix(), nice_name, crosssection, mass);
}

std::string AnalysisBase::FileName(const std::string&) const
{
    return ProcessName() + "_" + std::to_string(PreCut()) + "GeV";
}

std::string AnalysisBase::TreeName(std::string const& name) const
{
    return name + "-run_01";
}

PreCuts const& AnalysisBase::pre_cuts() const
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
    return working_path_;
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
    if (!Exists(tagger().WeightFileName(mva))) {
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
        Plotting plotting(tagger());
        plotting.OptimalCuts();
    }
}

void AnalysisBase::RunEfficiency()
{
    PrepareFiles();
    if (!Exists(tagger().ExportFileName())) {
        Plotting plotting(tagger());
        plotting.TaggingEfficiency();
    }
}

void AnalysisBase::RunPlots()
{
    PrepareFiles();
    if (!Exists(tagger().ExportFolderName())) {
        Plotting plotting(tagger());
        plotting.RunPlots();
    }
}

std::string AnalysisBase::WorkingPath()
{
    int path_length_max = 200;
    char temp [ path_length_max ];
    if (getcwd(temp, path_length_max) != 0) return std::string(temp) + "/";
    int error = errno;
    switch (error) {
        // EINVAL can't happen - size argument > 0
        // path_length_max includes the terminating nul,
        // so ERANGE should not be returned
    case EACCES:
        throw std::runtime_error("Access denied");
    case ENOMEM:
        // I'm not sure whether this can happen or not
        throw std::runtime_error("Insufficient storage");
    default: {
        std::ostringstream stream;
        stream << "Unrecognised error" << error;
        throw std::runtime_error(stream.str());
    }
    }
}

}
