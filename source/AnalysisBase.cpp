/**
 * Copyright (C) 2015 Jan Hajer
 */

#include <sys/stat.h>
#include <fstream>
#include <boost/lexical_cast.hpp>

#include "File.hh"
#include "AnalysisBase.hh"
#include "Plotting.hh"
#include "Event.hh"
#include "Trainer.hh"
#include "ParticleInfo.hh"
// #define INFORMATION
#include "Debug.hh"

namespace boca
{

AnalysisBase::AnalysisBase()
{
    Info0;
}

void AnalysisBase::Initialize()
{
    Error(tagger().Name());
    working_path_ = WorkingPath();
//     if (AnalysisName() != AnalysisBase::AnalysisName())
    Info(working_path_,AnalysisName());
      mkdir(AnalysisName().c_str(), 0700);
//     else Error(AnalysisName());
    tagger().SetAnalysisName(AnalysisName());
    tagger().Initialize();
}


std::vector<File> AnalysisBase::Files(Tag tag)
{
    Error(Name(tag));
    return files_;
}

void AnalysisBase::PrepareFiles(Stage stage)
{
    Info0;
    files_.clear();
    tagger().ClearTreeNames();
    SetFiles(Tag::signal, stage);
    SetFiles(Tag::background, stage);
}

long AnalysisBase::EventNumberMax() const
{
    Info0;
    return 100000;
}

void AnalysisBase::NewFile(boca::Tag tag, const boca::Strings& names, Crosssection crosssection, std::string const& nice_name, boca::Mass mass)
{
    Info0;
    files_.emplace_back(File(names, crosssection, nice_name, mass));
    tagger().AddTreeName(TreeName(names.front()), tag);
}

void AnalysisBase::NewFile(Tag tag, Strings const& names, std::string const& nice_name)
{
    Info0;
    files_.emplace_back(File(names, nice_name));
    tagger().AddTreeName(TreeName(names.front()), tag);
}

void AnalysisBase::NewFile(boca::Tag tag, std::string const& name, Crosssection crosssection, std::string const& nice_name, boca::Mass mass)
{
    Info0;
    files_.emplace_back(File( {name}, crosssection, nice_name, mass));
    tagger().AddTreeName(TreeName(name), tag);
}

void AnalysisBase::NewFile(Tag tag, std::string const& name, std::string const& nice_name)
{
    Info0;
    files_.emplace_back(File( {name}, nice_name));
    tagger().AddTreeName(TreeName(name), tag);
}

File AnalysisBase::File(Strings const& names, std::string const& nice_name) const
{
    Info0;
    return boca::File(names, FilePath(), FileSuffix(), nice_name);
}

File AnalysisBase::File(Strings const& names, Crosssection crosssection, std::string const& nice_name, boca::Mass mass) const
{
    Info0;
    return boca::File(names, FilePath(), FileSuffix(), nice_name, crosssection, mass);
}

// std::string AnalysisBase::FileName(std::string const&) const
// {
//   return "Process_" + Name(PreCut());
// }

std::string AnalysisBase::TreeName(std::string const& name) const
{
    Info0;
    return name + "-run_01";
}

PreCuts const& AnalysisBase::pre_cuts() const
{
    Info0;
    return pre_cuts_;
}

PreCuts& AnalysisBase::pre_cuts()
{
    Info0;
    return pre_cuts_;
}

std::string AnalysisBase::FileSuffix() const
{
    Info0;
    return ".root";
}

std::string AnalysisBase::FilePath() const
{
    Info0;
    return working_path_;
}

int AnalysisBase::BackgroundFileNumber() const
{
    Info0;
//     return configuration_.BackgroundFileNumber();
    return 1;
}

Momentum AnalysisBase::PreCut() const
{
    Info0;
//     return configuration_.PreCut();
    return 0;
}

boca::Mass AnalysisBase::Mass() const
{
    Info0;
//     return configuration_.Mass();
    return 1.*GeV;
}

void AnalysisBase::RunFast()
{
    Info0;
    RunTagger(Stage::trainer);
    Info("Analysis Loop done");
    RunTrainer();
}

void AnalysisBase::RunNormal()
{
    Info0;
    RunFast();
    RunTagger(Stage::reader);
    Info("Analysis Loop done");
}

void AnalysisBase::RunFullSignificance()
{
    Info0;
    RunNormal();
    RunSignificance();
}

void AnalysisBase::ClearFiles()
{
    Info0;
    files_.clear();
}

void AnalysisBase::RunFullEfficiency()
{
    Info0;
    RunNormal();
    RunEfficiency();
}

void AnalysisBase::RunTagger(Stage stage)
{
    Info0;
    if (!Exists(tagger().FileName(stage, Tag::signal))) AnalysisLoop(stage);
}

void AnalysisBase::RunTrainer()
{
    Info0;
    PrepareFiles(Stage::trainer);
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
    Info0;
    PrepareFiles(Stage::reader);
    if (!Exists(tagger().ExportFileName())) {
        Plotting plotting(tagger());
        plotting.OptimalCuts();
    }
}

void AnalysisBase::RunEfficiency()
{
    Info0;
    PrepareFiles(Stage::reader);
    if (!Exists(tagger().ExportFileName())) {
        Plotting plotting(tagger());
        plotting.TaggingEfficiency();
    }
}

void AnalysisBase::RunPlots()
{
    Info0;
    PrepareFiles(Stage::reader);
    if (!Exists(tagger().ExportFolderName())) {
        Plotting plotting(tagger());
        plotting.RunPlots();
    }
}

std::string AnalysisBase::WorkingPath()
{
    Info0;
    // FIXME remove this magic number
    const int path_length_max = 200;
    char temp [ path_length_max ];
    if (getcwd(temp, path_length_max) != 0) {
        return std::string(temp) + "/";
    }
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
//         std::ostringstream stream;
//         stream << "Unrecognised error" << error;
//         throw std::runtime_error(stream.str());
        throw std::runtime_error("Unrecognised error" + boost::lexical_cast<std::string>(error));
    }
    }
}


void AnalysisBase::Run(Output run)
{
  Info0;
  Initialize();
  //   analysis.PreRequisits<analysis.tagger()::type>(analysis,run);
  switch (run) {
    case Output::fast :
      RunFast();
      break;
    case Output::normal :
      RunNormal();
      break;
    case Output::efficiency :
      RunFullEfficiency();
      //       RunPlots();
      break;
    case Output::significance :
      RunFullSignificance();
      RunPlots();
      break;
    case Output::plot :
      RunNormal();
      RunPlots();
      break;
  }
  if (is(run, Output::plot)) {
    RunPlots();
  }

}

void Run(AnalysisBase& analysis, Output run)
{
    Info0;
    analysis.Run(run);
//     analysis.Initialize();
// //   analysis.PreRequisits<analysis.tagger()::type>(analysis,run);
//     switch (run) {
//     case Output::fast :
//         analysis.RunFast();
//         break;
//     case Output::normal :
//         analysis.RunNormal();
//         break;
//     case Output::efficiency :
//         analysis.RunFullEfficiency();
// //       analysis.RunPlots();
//         break;
//     case Output::significance :
//         analysis.RunFullSignificance();
//         analysis.RunPlots();
//         break;
//     case Output::plot :
//         analysis.RunNormal();
//         analysis.RunPlots();
//         break;
//     }
//     if (is(run, Output::plot)) {
//         analysis.RunPlots();
//     }

}

void AnalysisBase::PrintGeneratorLevel(Event const& event, bool signature) const
{
    Info0;
    Jets particles = event.Partons().GenParticles();
    for (auto const & particle : particles) {
        Family family = particle.user_info<ParticleInfo>().Family();
        if (signature && family.StepMother().Id() == 0) continue;
        std::string id = Name(family.Particle().Id());
        std::string mother = Name(family.Mother().Id());
        std::string mother2 = Name(family.StepMother().Id());
        Error(id, mother, mother2);
    }
}

}

