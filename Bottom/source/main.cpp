# include "TSystem.h"
# include "AnalysisBottomTagger.hh"
// # include "BottomTaggerSimple.hh"
# include "BottomTagger.hh"
# include "Factory.hh"

void RunTagger(analysis::Tagger &tagger, analysis::Tagger::Stage stage)
{
    analysis::bottom::Analysis analysis(tagger);
    const std::string name = tagger.name(stage);
    analysis.Print(analysis.kError, "Tagger", name);
    std::string file_name = analysis.ExportName(stage, analysis::Object::kSignal);
    if (gSystem->AccessPathName(file_name.c_str())) analysis.AnalysisLoop(stage);
}

void RunFactory(analysis::Tagger &tagger)
{
    analysis::bottom::Analysis analysis(tagger);
    const std::string name = tagger.name(analysis::Tagger::kTrainer);
    analysis.Print(analysis.kError, "Tagger", name);
    std::string file_name = tagger.factory_name();
    if (gSystem->AccessPathName(file_name.c_str())) analysis::Factory factory(tagger);
}

void RunReader(analysis::Tagger &tagger)
{
  analysis::bottom::Analysis analysis(tagger);
  analysis.PrepareFiles();
    const std::string file_name = analysis.ProjectName() + "/" + tagger.tagger_name() + "Bdt.root";
    if (gSystem->AccessPathName(file_name.c_str())) {
        analysis::Reader reader(tagger);
        reader.TaggingEfficiency();
    }
}

void RunFull(analysis::Tagger &tagger)
{
  RunTagger(tagger, analysis::Tagger::kTrainer);
  RunFactory(tagger);
  RunTagger(tagger, analysis::Tagger::kReader);
  RunReader(tagger);
}

int main()
{
    //     analysis::bottom::BottomTaggerSimple bottom_tagger;
    analysis::BottomTagger bottom_tagger;
    RunFull(bottom_tagger);
}
