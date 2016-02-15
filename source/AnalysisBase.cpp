/**
 * Copyright (C) 2015 Jan Hajer
 */

#include <sys/stat.h>
#include <fstream>
#include <boost/lexical_cast.hpp>
// #include "boost/filesystem.hpp"

#include "File.hh"
#include "AnalysisBase.hh"
#include "plotting/Plotting.hh"
#include "Event.hh"
#include "Trainer.hh"
#include "ParticleInfo.hh"
// #define INFORMATION
#include "Debug.hh"

namespace boca
{

AnalysisBase::AnalysisBase()
{
    INFO0;
}

void AnalysisBase::Initialize()
{
    ERROR(Tagger().Name());
//     working_path_ = WorkingPath();
//     if (AnalysisName() != AnalysisBase::AnalysisName())
//     INFO(working_path_, AnalysisName());
    mkdir(AnalysisName().c_str(), 0700);
//     else ERROR(AnalysisName());
    Tagger().Initialize(AnalysisName());
}


std::vector<File> AnalysisBase::Files(Tag tag)
{
    ERROR(Name(tag));
    return files_;
}

void AnalysisBase::PrepareFiles(Stage stage)
{
    INFO0;
    ClearFiles();
    SetFiles(Tag::signal, stage);
    SetFiles(Tag::background, stage);
}

long AnalysisBase::TrainNumberMax() const
{
    INFO0;
    return 100000;
}

long AnalysisBase::ReadNumberMax() const
{
    INFO0;
    return TrainNumberMax();
}

void AnalysisBase::NewFile(boca::Tag tag, const std::vector<std::string>& names, Crosssection crosssection, std::string const& nice_name, boca::Mass mass)
{
    INFO0;
    files_.emplace_back(File(names, crosssection, nice_name, mass));
    Tagger().AddTreeName(TreeName(names.front()), tag);
}

void AnalysisBase::NewFile(Tag tag, std::vector<std::string> const& names, std::string const& nice_name)
{
    INFO0;
    files_.emplace_back(File(names, nice_name));
    Tagger().AddTreeName(TreeName(names.front()), tag);
}

void AnalysisBase::NewFile(boca::Tag tag, std::string const& name, Crosssection crosssection, std::string const& nice_name, boca::Mass mass)
{
    INFO0;
    files_.emplace_back(File( {name}, crosssection, nice_name, mass));
    Tagger().AddTreeName(TreeName(name), tag);
}

void AnalysisBase::NewFile(Tag tag, std::string const& name, std::string const& nice_name)
{
    INFO0;
    files_.emplace_back(File( {name}, nice_name));
    Tagger().AddTreeName(TreeName(name), tag);
}

File AnalysisBase::File(std::vector<std::string> const& names, std::string const& nice_name) const
{
    INFO0;
    return boca::File(names, FilePath(), FileSuffix(), nice_name);
}

File AnalysisBase::File(std::vector<std::string> const& names, Crosssection crosssection, std::string const& nice_name, boca::Mass mass) const
{
    INFO0;
    return boca::File(names, FilePath(), FileSuffix(), nice_name, crosssection, mass);
}

std::string AnalysisBase::TreeName(std::string const& name) const
{
    INFO0;
    return name + "-run_01";
}

boca::PreCuts const& AnalysisBase::PreCuts() const
{
    INFO0;
    return pre_cuts_;
}

boca::PreCuts& AnalysisBase::PreCuts()
{
    INFO0;
    return pre_cuts_;
}

std::string AnalysisBase::FileSuffix() const
{
    INFO0;
    return ".root";
}

std::string AnalysisBase::FilePath() const
{
    INFO0;
    return WorkingPath();
}

int AnalysisBase::BackgroundFileNumber() const
{
    INFO0;
//     return configuration_.BackgroundFileNumber();
    return 1;
}

void AnalysisBase::RunFast()
{
    INFO0;
    RunTagger(Stage::trainer);
    INFO("Analysis Loop done");
    RunTrainer();
}

void AnalysisBase::RunNormal()
{
    INFO0;
    RunFast();
    RunTagger(Stage::reader);
    INFO("Analysis Loop done");
}

void AnalysisBase::RunFullSignificance()
{
    INFO0;
    RunNormal();
    RunSignificance();
}

void AnalysisBase::ClearFiles()
{
    INFO0;
    files_.clear();
    Tagger().ClearTreeNames();
}

void AnalysisBase::RunFullEfficiency()
{
    INFO0;
    RunNormal();
    RunEfficiency();
}

void AnalysisBase::RunTagger(Stage stage)
{
    INFO0;
    if (Exists(Tagger().FileName(stage, Tag::signal))) return;
    AnalysisLoop(stage);
}

void AnalysisBase::RunTrainer()
{
    INFO0;
    if (Exists(Tagger().WeightFileName())) return;
    PrepareFiles(Stage::trainer);
    std::ofstream cout_file(Tagger().FolderName() + ".txt");
    std::streambuf* cout = std::cout.rdbuf();
    std::cout.rdbuf(cout_file.rdbuf());
    Trainer trainer(Tagger());
    std::cout.rdbuf(cout);
}


void AnalysisBase::RunSignificance()
{
    INFO0;
    if (Exists(Tagger().ExportFileName())) return;
    PrepareFiles(Stage::reader);
    Plotting plotting(Tagger());
    plotting.OptimalCuts();
}

void AnalysisBase::RunEfficiency()
{
    INFO0;
    if (Exists(Tagger().ExportFileName())) return;
    PrepareFiles(Stage::reader);
    Plotting plotting(Tagger());
    plotting.TaggingEfficiency();
}

void AnalysisBase::RunPlots()
{
    INFO0;
    if (Exists(Tagger().ExportFolderName())) return;
    Plotting plotting(Tagger());
    PrepareFiles(Stage::trainer);
    plotting.RunPlots(Stage::trainer);
    PrepareFiles(Stage::reader);
    plotting.RunPlots(Stage::reader);
//     if (Exists(Tagger().ExportFileName())) std::remove(Tagger().ExportFileName().c_str());
}

void AnalysisBase::RunCut()
{
    INFO0;
    RunTagger(Stage::trainer);
    INFO("Analysis Loop done");
    RunTrainer();
    RunTagger(Stage::reader);
    ERROR(Tagger().TreeNames(Tag::signal).size());
    PrepareFiles(Stage::reader);
    Plotting plotting(Tagger());
    plotting.OptimalCuts();
}

std::string AnalysisBase::WorkingPath() const
{
    INFO0;
    return "./";
//     std::string path = boost::filesystem::current_path().string() + "/";
//     ERROR(path);
//     return path;
}

void AnalysisBase::Run(Output output)
{
    INFO0;
    Initialize();
    //   analysis.PreRequisits<analysis.Tagger()::type>(analysis,run);
    FlagSwitch(output, [&](Output output_2) {
        switch (output_2) {
        case Output::fast : RunFast();
            break;
        case Output::normal : RunNormal();
            break;
        case Output::efficiency : RunFullEfficiency();
            break;
        case Output::significance : RunFullSignificance();
            break;
        case Output::plot : RunPlots();
            break;
        case Output::cut : RunCut();
            break;
            DEFAULT(to_int(output));
        }
    });
}

void AnalysisBase::PrintGeneratorLevel(Event const& event, bool signature) const
{
    INFO0;
    auto particles = event.Partons().GenParticles();
    for (auto const & particle : particles) {
        auto family = particle.Info().Family();
        if (signature && family.Member(Relative::step_mother).Id() == 0) continue;
        auto id = Name(family.Member(Relative::particle).Id());
        auto mother = Name(family.Member(Relative::mother).Id());
        auto mother2 = Name(family.Member(Relative::step_mother).Id());
        ERROR(id, mother, mother2);
    }
}

long int AnalysisBase::EventNumberMax(Stage stage) const
{
    switch (stage) {
    case Stage::trainer : return TrainNumberMax();
    case Stage::reader : return ReadNumberMax();
        DEFAULT(Name(stage), 0);
    }
}

}

