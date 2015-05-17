# include "TSystem.h"
# include "AnalysisBottomTagger.hh"
# include "BottomTaggerSimple.hh"
# include "BottomTagger.hh"
# include "Factory.hh"

void RunTagger(analysis::Tagger &tagger, analysis::Tagger::Stage stage)
{
    hbtagger::HAnalysis analysis(tagger);
    const std::string name = tagger.name(stage);
    analysis.Print(analysis.kError, "Tagger", name);
    std::string file_name = analysis.ExportName(stage,analysis::Object::kSignal);
    if (gSystem->AccessPathName(file_name.c_str())) analysis.AnalysisLoop(stage);
}

void RunFactory(analysis::Tagger &tagger)
{
  hbtagger::HAnalysis analysis(tagger);
  const std::string name = tagger.name(analysis::Tagger::kTrainer);
  analysis.Print(analysis.kError, "Tagger", name);
  std::string file_name = tagger.factory_name();
  if (gSystem->AccessPathName(file_name.c_str())) analysis::Factory factory(tagger);
}

void RunReader(analysis::Tagger &tagger)
{
    hbtagger::HAnalysis analysis(tagger);
    const std::string file_name = analysis.ProjectName() + "/" + tagger.tagger_name() + "Bdt.root";
    if (gSystem->AccessPathName(file_name.c_str())) {
        analysis::Reader reader(tagger);
        reader.OptimalSignificance();
    }
}

int main(const int argc, const char **argv)
{
    const std::vector<std::string> Arguments(argv, argv + argc);
    for (const auto & Argument : Arguments) std::cout << Argument << std::endl;
//     hbtagger::BottomTaggerSimple bottom_tagger;
    analysis::BottomTagger bottom_tagger;
    RunTagger(bottom_tagger, analysis::Tagger::kTrainer);
    RunFactory(bottom_tagger);
    RunTagger(bottom_tagger, analysis::Tagger::kReader);
    RunReader(bottom_tagger);
    return EXIT_SUCCESS;
}
