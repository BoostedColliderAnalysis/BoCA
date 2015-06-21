# include "AnalysisTopTagger.hh"
# include "TopHadronicTagger.hh"
# include "TopSemiTagger.hh"
# include "TSystem.h"
# include "Factory.hh"

void RunTagger(analysis::Tagger &tagger, analysis::Tagger::Stage stage)
{
    analysis::top::Analysis analysis(tagger);
    const std::string name = tagger.name(stage);
    analysis.Print(analysis.kError, "Tagger", name);

    std::string file_name = analysis.ProjectName() + "/" + name + ".root";
    if (gSystem->AccessPathName(file_name.c_str())) analysis.AnalysisLoop(stage);
}

void RunFactory(analysis::Tagger &tagger)
{
  analysis::top::Analysis analysis(tagger);
  analysis.PrepareFiles();
    const std::string name = tagger.name(analysis::Tagger::kTrainer);
    analysis.Print(analysis.kError, "Tagger", name);
    std::string file_name = analysis.ProjectName() + "/Mva" + name + ".root";
    if (gSystem->AccessPathName(file_name.c_str())) analysis::Factory factory(tagger);
}

void RunReader(analysis::Tagger &tagger)
{
    analysis::top::Analysis analysis(tagger);
    analysis.PrepareFiles();
    const std::string file_name = analysis.ProjectName() + "/" + tagger.tagger_name() + "Bdt.root";
    if (gSystem->AccessPathName(file_name.c_str())) {
        analysis::Reader reader(tagger);
        reader.TaggingEfficiency();
    }
}

void Run(analysis::Tagger &tagger)
{
    RunTagger(tagger, analysis::Tagger::kTrainer);
    RunFactory(tagger);
    RunTagger(tagger, analysis::Tagger::kReader);
}

int main()
{
    analysis::BottomTagger bottom_tagger;
    Run(bottom_tagger);

    analysis::top::Analysis analysis(bottom_tagger);
    if (analysis.TopDecay() == analysis::top::Analysis::kHadronic) {
        analysis::WHadronicTagger w_hadronic_tagger;
        Run(w_hadronic_tagger);

        analysis::TopHadronicTagger top_hadronic_tagger;
        Run(top_hadronic_tagger);
        RunReader(top_hadronic_tagger);
    }

    if (analysis.TopDecay() == analysis::top::Analysis::kLeptonic) {
        analysis::WSemiTagger w_semi_tagger;
        Run(w_semi_tagger);

        analysis::TopSemiTagger tops_semi_tagger;
        Run(tops_semi_tagger);
        RunReader(tops_semi_tagger);
    }
}

