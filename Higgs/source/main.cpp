# include "AnalysisHiggsTagger.hh"
# include "BranchTagger.hh"
# include "HiggsTagger.hh"
# include "TSystem.h"
# include "Factory.hh"


void RunTagger(analysis::Tagger &tagger, analysis::Tagger::Stage stage)
{
    analysis::higgstagger::Analysis analysis(tagger);
    const std::string name = tagger.name(stage);
    analysis.Print(analysis.kError, "Tagger", name);

    std::string file_name = analysis.ProjectName() + "/" + name + ".root";
    if (gSystem->AccessPathName(file_name.c_str())) analysis.AnalysisLoop(stage);
}

void RunFactory(analysis::Tagger &tagger)
{
    analysis::higgstagger::Analysis analysis(tagger);
    const std::string name = tagger.name(analysis::Tagger::kTrainer);
    analysis.Print(analysis.kError, "Tagger", name);
    std::string file_name = analysis.ProjectName() + "/Mva" + name + ".root";
    if (gSystem->AccessPathName(file_name.c_str())) analysis::Factory factory(tagger);
}

void RunReader(analysis::Tagger &tagger)
{
    analysis::higgstagger::Analysis analysis(tagger);
    analysis.PrepareFiles();
    const std::string file_name = analysis.ProjectName() + "/" + tagger.tagger_name() + "Bdt.root";
    if (gSystem->AccessPathName(file_name.c_str())) {
        analysis::Reader reader(tagger);
        reader.TaggingEfficiency();
    }
}

void RunFast(analysis::Tagger &tagger)
{
    RunTagger(tagger, analysis::Tagger::kTrainer);
    RunFactory(tagger);
    RunTagger(tagger, analysis::Tagger::kReader);
}

int main()
{
    analysis::BottomTagger bottom_tagger;
    RunFast(bottom_tagger);

    analysis::higgstagger::Analysis analysis(bottom_tagger);

    analysis::HiggsTagger higgs_tagger;
    RunFast(higgs_tagger);
    RunReader(higgs_tagger);

}

