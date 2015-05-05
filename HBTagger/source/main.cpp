#include "HAnalysisBTagger.hh"
#include "HBottomTagger.hh"
#include "HFactory.hh"
#include "TSystem.h"

void RunTagger(hanalysis::Tagger &tagger, hanalysis::Tagger::Stage stage)
{
    hbtagger::HAnalysis analysis(tagger);
    const std::string name = tagger.tagger_name();
    analysis.Print(analysis.HError, "Tagger", name);

    std::string file_name = analysis.ProjectName() + "/" + name + ".root";
    if (gSystem->AccessPathName(file_name.c_str())) analysis.AnalysisLoop(stage);

    file_name = analysis.ProjectName() + "/Mva" + name + ".root";
    if (gSystem->AccessPathName(file_name.c_str())) hanalysis::HFactory factory(tagger);
}

void RunReader(hanalysis::Tagger &tagger)
{

    hbtagger::HAnalysis analysis(tagger);
    const std::string file_name = analysis.ProjectName() + "/" + tagger.tagger_name() + "Bdt.root";
    if (gSystem->AccessPathName(file_name.c_str())) {
        hanalysis::HReader reader(tagger);
        reader.SimpleMVALoop();
    }
}


int main()
{
    hanalysis::HBottomTagger bottom_tagger;
    RunTagger(bottom_tagger, hanalysis::Tagger::kTrainer);
    RunTagger(bottom_tagger, hanalysis::Tagger::kReader);
    RunReader(bottom_tagger);
    return EXIT_SUCCESS;
}
