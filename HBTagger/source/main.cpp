#include "HAnalysisBTagger.hh"
#include "HBottomTaggerSimple.hh"
# include "Factory.hh"
#include "TSystem.h"

void RunTagger(hanalysis::Tagger &tagger, hanalysis::Tagger::Stage stage)
{
    hbtagger::HAnalysis analysis(tagger);
    const std::string name = tagger.name(stage);
    analysis.Print(analysis.HError, "Tagger", name);

    std::string file_name = analysis.ProjectName() + "/" + name + ".root";
    if (gSystem->AccessPathName(file_name.c_str())) analysis.AnalysisLoop(stage);
}

void RunFactory(hanalysis::Tagger &tagger)
{
  hbtagger::HAnalysis analysis(tagger);
  const std::string name = tagger.name(hanalysis::Tagger::kTrainer);
  analysis.Print(analysis.HError, "Tagger", name);
  std::string file_name = analysis.ProjectName() + "/Mva" + name + ".root";
  if (gSystem->AccessPathName(file_name.c_str())) hanalysis::Factory factory(tagger);
}

void RunReader(hanalysis::Tagger &tagger)
{
    hbtagger::HAnalysis analysis(tagger);
    const std::string file_name = analysis.ProjectName() + "/" + tagger.tagger_name() + "Bdt.root";
    if (gSystem->AccessPathName(file_name.c_str())) {
        hanalysis::Reader reader(tagger);
        reader.OptimalSignificance();
    }
}

int main(const int argc, const char **argv)
{
    const std::vector<std::string> Arguments(argv, argv + argc);
    for (const auto & Argument : Arguments) std::cout << Argument << std::endl;
    hbtagger::HBottomTaggerSimple bottom_tagger;
    RunTagger(bottom_tagger, hanalysis::Tagger::kTrainer);
    RunFactory(bottom_tagger);
    RunTagger(bottom_tagger, hanalysis::Tagger::kReader);
    RunReader(bottom_tagger);
    return EXIT_SUCCESS;
}
