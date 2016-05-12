/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include <sys/stat.h>
// #include <fstream>
// #include <boost/lexical_cast.hpp>

#include "boca/generic/Types.hh"
#include "boca/io/Io.hh"
#include "boca/File.hh"
#include "boca/AnalysisBase.hh"
#include "boca/Event.hh"
#include "boca/multivariant/Trainer.hh"
// #define INFORMATION
#include "boca/generic/DEBUG.hh"

namespace boca
{

std::string Name(Output output)
{
    std::string name;
    FlagSwitch(output, [&](Output out) {
        switch (out) {
        case Output::none : name += "None";
            break;
        case Output::fast : name += "Fast";
            break;
        case Output::normal : name += "Normal";
            break;
        case Output::significance : name += "Significance";
            break;
        case Output::efficiency : name += "Efficiency";
            break;
        case Output::plot : name += "Plot";
            break;
        case Output::cut : name += "Cut";
            break;
            DEFAULT(to_int(out));
        }
    });
    return name;
}

AnalysisBase::AnalysisBase()
{
    INFO0;
}

std::string _analysis_name_;

void AnalysisBase::Initialize()
{
    ERROR(Tagger().Name());
//     working_path_ = WorkingPath();
//     if (AnalysisName() != AnalysisBase::AnalysisName())
//     INFO(working_path_, AnalysisName());
    mkdir(AnalysisName().c_str(), 0700);
//     else ERROR(AnalysisName());
    Tagger().Initialize(AnalysisName());
    _analysis_name_ = AnalysisName();
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

void AnalysisBase::NewFile(Tag tag, const std::vector<std::string>& names, Crosssection const& crosssection, latex::String const& latex_name, Mass const& mass)
{
    INFO0;
    files_.emplace_back(File(names, crosssection, latex_name, mass));
    Tagger().AddTreeName(TreeName(names.front()), tag);
}

void AnalysisBase::NewFile(Tag tag, std::vector<std::string> const& names, latex::String const& latex_name)
{
    INFO0;
    files_.emplace_back(File(names, latex_name));
    Tagger().AddTreeName(TreeName(names.front()), tag);
}

void AnalysisBase::NewFile(Tag tag, std::vector<std::string> const& names, Crosssection const& crosssection, Names const& latex_name, Mass const& mass)
{
    INFO0;
    files_.emplace_back(File(names, latex_name, crosssection, mass));
    Tagger().AddTreeName(TreeName(names.front()), tag);
}

void AnalysisBase::NewFile(Tag tag, std::string const& name, Crosssection const& crosssection, latex::String const& latex_name, Mass const& mass)
{
    INFO0;
    files_.emplace_back(File( {name}, crosssection, latex_name, mass));
    Tagger().AddTreeName(TreeName(name), tag);
}

void AnalysisBase::NewFile(Tag tag, std::string const& name, Crosssection const& crosssection, Names const& latex_name, Mass const& mass)
{
    INFO0;
    files_.emplace_back(File( {name}, latex_name, crosssection, mass));
    Tagger().AddTreeName(TreeName(name), tag);
}

void AnalysisBase::NewFile(Tag tag, std::string const& name, latex::String const& latex_name)
{
    INFO0;
    files_.emplace_back(File( {name}, latex_name));
    Tagger().AddTreeName(TreeName(name), tag);
}

File AnalysisBase::File(std::vector<std::string> const& names, Names const& latex_name, Crosssection const& crosssection, Mass const& mass) const
{
    INFO0;
    return boca::File(names, FilePath(), FileSuffix(), latex_name, crosssection, mass);
}

File AnalysisBase::File(std::vector<std::string> const& names, latex::String const& latex_name) const
{
    INFO0;
    return boca::File(names, FilePath(), FileSuffix(), latex_name);
}

File AnalysisBase::File(std::vector<std::string> const& names, Crosssection const& crosssection, latex::String const& latex_name, Mass const& mass) const
{
    INFO0;
    return boca::File(names, FilePath(), FileSuffix(), latex_name, crosssection, mass);
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
    auto cout = std::cout.rdbuf();
    std::cout.rdbuf(cout_file.rdbuf());
    Trainer trainer(Tagger());
    std::cout.rdbuf(cout);
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
    INFO(Name(output));
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
        case Output::plot_hist : RunPlotHist();
            break;
            DEFAULT(Name(output_2));
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

int AnalysisBase::PassPreCut(const Event&, Tag) const
{
    return 1;
}

void AnalysisBase::AnalysisLoop(Stage stage)
{
    for (auto const & tag : std::array<Tag, 2>{{Tag::signal, Tag::background}}) TagLoop( {stage, tag});
}

}

