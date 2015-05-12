# include "TSystem.h"
# include "AnalysisBottomTagger.hh"
# include "BottomTaggerSimple.hh"
# include "BottomTagger.hh"
# include "Factory.hh"

void RunTagger(hanalysis::Tagger &tagger, hanalysis::Tagger::Stage stage)
{
    hbtagger::HAnalysis analysis(tagger);
    const std::string name = tagger.name(stage);
    analysis.Print(analysis.kError, "Tagger", name);
    std::string file_name = analysis.ExportName(stage,hanalysis::HObject::kSignal);
    if (gSystem->AccessPathName(file_name.c_str())) analysis.AnalysisLoop(stage);
}

void RunFactory(hanalysis::Tagger &tagger)
{
  hbtagger::HAnalysis analysis(tagger);
  const std::string name = tagger.name(hanalysis::Tagger::kTrainer);
  analysis.Print(analysis.kError, "Tagger", name);
  std::string file_name = tagger.factory_name();
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
//     hbtagger::BottomTaggerSimple bottom_tagger;
    hanalysis::BottomTagger bottom_tagger;
    RunTagger(bottom_tagger, hanalysis::Tagger::kTrainer);
    RunFactory(bottom_tagger);
    RunTagger(bottom_tagger, hanalysis::Tagger::kReader);
    RunReader(bottom_tagger);
    return EXIT_SUCCESS;
}
