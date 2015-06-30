#include "AnalysisFusion.hh"
#include "TSystem.h"
#include "EventFusionTagger.hh"
#include "Factory.hh"

#include "fastjet/LimitedWarning.hh"
#include "Debug.hh"

void RunTagger(analysis::Tagger &tagger, analysis::Stage stage)
{
    analysis::heavyhiggs::AnalysisFusion analysis(tagger);
    const std::string Name = tagger.name();
    Error("Tagger", Name);

    std::string FileName = analysis.ProjectName() + "/" + Name + ".root";
    if (gSystem->AccessPathName(FileName.c_str())) analysis.AnalysisLoop(stage);

    FileName = analysis.ProjectName() + "/Mva" + Name + ".root";
    if (gSystem->AccessPathName(FileName.c_str())) analysis::Factory factory(tagger);

    FileName = analysis.ProjectName() + "/" + Name + "Bdt.root";
    if (gSystem->AccessPathName(FileName.c_str())) {
        analysis::Reader Reader(tagger);
        Reader.OptimalSignificance();
    }
}

int main()
{
    fastjet::Error::set_print_errors(true);
    fastjet::Error::set_print_backtrace(true);

    analysis::BottomTagger bottom_tagger;
    RunTagger(bottom_tagger, analysis::Stage::trainer);
    RunTagger(bottom_tagger, analysis::Stage::reader);

    analysis::WHadronicTagger w_hadronic_tagger;
    RunTagger(w_hadronic_tagger, analysis::Stage::trainer);
    RunTagger(w_hadronic_tagger, analysis::Stage::reader);

    analysis::WSemiTagger w_semi_tagger;
    RunTagger(w_semi_tagger, analysis::Stage::trainer);
    RunTagger(w_semi_tagger, analysis::Stage::reader);

    analysis::TopHadronicTagger top_hadronic_tagger;
    RunTagger(top_hadronic_tagger, analysis::Stage::trainer);
    RunTagger(top_hadronic_tagger, analysis::Stage::reader);

    analysis::TopSemiTagger tops_semi_tagger;
    RunTagger(tops_semi_tagger, analysis::Stage::trainer);
    RunTagger(tops_semi_tagger, analysis::Stage::reader);

    analysis::heavyhiggs::HeavyHiggsSemiTagger heavy_higgs_semi_tagger;
    RunTagger(heavy_higgs_semi_tagger, analysis::Stage::trainer);
    RunTagger(heavy_higgs_semi_tagger, analysis::Stage::reader);


    analysis::heavyhiggs::EventFusionTagger event_semi_tagger;
    RunTagger(event_semi_tagger, analysis::Stage::trainer);
    RunTagger(event_semi_tagger, analysis::Stage::reader);


    std::cout << fastjet::LimitedWarning::summary() << std::endl;

    return EXIT_SUCCESS;
}

