/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include <sys/stat.h>

#include "boca/generic/Types.hh"
#include "boca/io/Io.hh"
#include "boca/File.hh"
#include "boca/analysis/Base.hh"
#include "boca/Event.hh"
#include "boca/multivariant/Trainer.hh"
#include "boca/tagger/Base.hh"
// #define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

using namespace std::string_literals;

std::string Name(Output output)
{
    auto name = ""s;
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

namespace analysis
{

Base::Base()
{
    INFO0;
}

std::string _name_;

void Base::Initialize()
{
    ERROR(Tagger().AnalysisName());
//     working_path_ = WorkingPath();
//     if (Name() != analysis::Base::Name())
//     INFO(working_path_, Name());
    mkdir(Name().c_str(), 0700);
//     else ERROR(Name());
    Tagger().Initialize(Name());
    _name_ = Name();
}


std::vector<File> Base::Files(Tag tag)
{
    ERROR(boca::Name(tag));
    return files_;
}

void Base::PrepareFiles(Stage stage)
{
    INFO0;
    ClearFiles();
    SetFiles(Tag::signal, stage);
    SetFiles(Tag::background, stage);
}

long Base::TrainNumberMax() const
{
    INFO0;
    return 100000;
}

long Base::ReadNumberMax() const
{
    INFO0;
    return TrainNumberMax();
}

void Base::NewFile(Tag tag, const std::vector<std::string>& names, Crosssection const& crosssection, latex::String const& latex_name, Mass const& mass)
{
    INFO0;
    files_.emplace_back(File(names, crosssection, latex_name, mass));
    Tagger().AddTreeName(TreeName(names.front()), tag);
}

void Base::NewFile(Tag tag, std::vector<std::string> const& names, latex::String const& latex_name)
{
    INFO0;
    files_.emplace_back(File(names, latex_name));
    Tagger().AddTreeName(TreeName(names.front()), tag);
}

void Base::NewFile(Tag tag, std::vector<std::string> const& names, Crosssection const& crosssection, Names const& latex_name, Mass const& mass)
{
    INFO0;
    files_.emplace_back(File(names, latex_name, crosssection, mass));
    Tagger().AddTreeName(TreeName(names.front()), tag);
}

void Base::NewFile(Tag tag, std::string const& name, Crosssection const& crosssection, latex::String const& latex_name, Mass const& mass)
{
    INFO0;
    files_.emplace_back(File( {name}, crosssection, latex_name, mass));
    Tagger().AddTreeName(TreeName(name), tag);
}

void Base::NewFile(Tag tag, std::string const& name, Crosssection const& crosssection, Names const& latex_name, Mass const& mass)
{
    INFO0;
    files_.emplace_back(File( {name}, latex_name, crosssection, mass));
    Tagger().AddTreeName(TreeName(name), tag);
}

void Base::NewFile(Tag tag, std::string const& name, latex::String const& latex_name)
{
    INFO0;
    files_.emplace_back(File( {name}, latex_name));
    Tagger().AddTreeName(TreeName(name), tag);
}

File Base::File(std::vector<std::string> const& names, Names const& latex_name, Crosssection const& crosssection, Mass const& mass) const
{
    INFO0;
    return boca::File(names, FilePath(), FileSuffix(), latex_name, crosssection, mass);
}

File Base::File(std::vector<std::string> const& names, latex::String const& latex_name) const
{
    INFO0;
    return boca::File(names, FilePath(), FileSuffix(), latex_name);
}

File Base::File(std::vector<std::string> const& names, Crosssection const& crosssection, latex::String const& latex_name, Mass const& mass) const
{
    INFO0;
    return boca::File(names, FilePath(), FileSuffix(), latex_name, crosssection, mass);
}

std::string Base::TreeName(std::string const& name) const
{
    INFO0;
    return name + "-run_01";
}

boca::PreCuts const& Base::PreCuts() const
{
    INFO0;
    return pre_cuts_;
}

boca::PreCuts& Base::PreCuts()
{
    INFO0;
    return pre_cuts_;
}

std::string Base::FileSuffix() const
{
    INFO0;
    return ".root";
}

std::string Base::FilePath() const
{
    INFO0;
    return WorkingPath();
}

int Base::BackgroundFileNumber() const
{
    INFO0;
//     return configuration_.BackgroundFileNumber();
    return 1;
}

void Base::RunFast()
{
    INFO0;
    RunTagger(Stage::trainer);
    INFO("Analysis Loop done");
    RunTrainer();
}

void Base::RunNormal()
{
    INFO0;
    RunFast();
    RunTagger(Stage::reader);
    INFO("Analysis Loop done");
}

void Base::RunFullSignificance()
{
    INFO0;
    RunNormal();
    RunSignificance();
}

void Base::ClearFiles()
{
    INFO0;
    files_.clear();
    Tagger().ClearTreeNames();
}

void Base::RunFullEfficiency()
{
    INFO0;
    RunNormal();
    RunEfficiency();
}

void Base::RunTagger(Stage stage)
{
    INFO0;
    if (Exists(Tagger().FileName(stage, Tag::signal))) return;
    AnalysisLoop(stage);
}

void Base::RunTrainer()
{
    INFO0;
    if (Exists(Tagger().WeightFileName())) return;
    PrepareFiles(Stage::trainer);
    auto cout_file = std::ofstream{Tagger().FolderName() + ".txt"};
    auto cout = std::cout.rdbuf();
    std::cout.rdbuf(cout_file.rdbuf());
    Trainer trainer(Tagger());
    std::cout.rdbuf(cout);
}

std::string Base::WorkingPath() const
{
    INFO0;
    return "./";
//     std::string path = boost::filesystem::current_path().string() + "/";
//     ERROR(path);
//     return path;
}

void Base::Run(Output output)
{
    INFO(boca::Name(output));
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
            DEFAULT(boca::Name(output_2));
        }
    });
}

void Base::PrintGeneratorLevel(Event const& event, bool signature) const
{
    INFO0;
    for (auto const & particle : event.GenParticles()) {
        auto family = particle.Info().Family();
        if (signature && family.Member(Relative::step_mother).Id() == 0) continue;
        auto id = boca::Name(family.Member(Relative::particle).Id());
        auto mother = boca::Name(family.Member(Relative::mother).Id());
        auto mother2 = boca::Name(family.Member(Relative::step_mother).Id());
        ERROR(id, mother, mother2);
    }
}

long Base::EventNumberMax(Stage stage) const
{
    switch (stage) {
    case Stage::trainer : return TrainNumberMax();
    case Stage::reader : return ReadNumberMax();
        DEFAULT(boca::Name(stage), 0);
    }
}

bool Base::PassPreCut(Event const&) const
{
    return true;
}

void Base::AnalysisLoop(Stage stage)
{
    for (auto const & tag : std::array<Tag, 2>{{Tag::signal, Tag::background}}) TagLoop( {stage, tag});
}


std::string Base::Name() const
{
    return "BoCA-Analysis";
}

}

}

