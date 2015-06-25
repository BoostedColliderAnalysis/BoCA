# include "AnalysisTopPartner.hh"
# include "Factory.hh"
# include <sys/stat.h>

namespace analysis {

namespace toppartner
{

Analysis::Analysis(Tagger &tagger) : analysis::Analysis::Analysis(tagger)
{
    Print(kNotification, "Constructor");
    this->tagger().set_analysis_name(ProjectName());
}

std::string Analysis::ProcessName()
{
    return "toppartner";
}

void Analysis::SetFiles(const Tag tag)
{
    Print(kNotification, "Set Files");
    switch (tag) {
    case kSignal :
      NewSignalFile("pp-Tth-bbbbjjjjlv");
//         NewSignalFile("pp-ttx0-bbbbllnunu-0", 0.008937);
//         NewSignalFile("pp-ttx0-bbbbllnunu-0.5", 0.01193);
        break;
    case kBackground :
      NewBackgroundFile("pp-Tth-bbbbjjjjlv");
        break;
    }
}

int Analysis::PassPreCut(Event &event)
{
    Print(kInformation, "pass pre cut");
//   Jets particles = event.Partons().GenParticles();
//   Jets tops = fastjet::sorted_by_pt(copy_if_abs_particle(particles, TopId));
//   remove_if_not_in_pt_window(tops, PreCut(), UpperCut());
    return 1;
}

void Analysis::RunFast()
{
  RunTagger(analysis::Tagger::kTrainer);
  RunFactory();
}

void Analysis::RunNormal()
{
  RunFast();
  RunTagger(analysis::Tagger::kReader);
}

void Analysis::RunFull()
{
  RunNormal();
  RunReader();
}

void Analysis::RunTagger(Tagger::Stage stage)
{
  if (Missing(PathName(tagger().name(stage)))) AnalysisLoop(stage);
}

void Analysis::RunFactory()
{
  PrepareFiles();
  if (Missing(PathName(tagger().factory_name()))) analysis::Factory factory(tagger());
}

void Analysis::RunReader()
{
  PrepareFiles();
  if (Missing(PathName(tagger().bdt_weight_name()))) {
    analysis::Reader reader(tagger());
    reader.OptimalSignificance();
  }
}

std::string Analysis::PathName(const std::string &file_name) const
{
  Print(kError, "Path Name", file_name);
  return ProjectName() + "/" + file_name + ".root";
}

bool Analysis::Missing(const std::string &name) const
{
  Print(kError, "Missing", name);
  struct stat buffer;
  return (stat(name.c_str(), &buffer) != 0);
}

}

}
