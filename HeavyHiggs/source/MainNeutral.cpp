#include "AnalysisNeutral.hh"

#include "fastjet/LimitedWarning.hh"

#include "Configuration.hh"
#include "TSystem.h"
#include "Factory.hh"
#include "EventNeutralTagger.hh"
#include "Debug.hh"

void RunTagger(analysis::Tagger &tagger, analysis::Stage stage, const analysis::Configuration &config)
{
    analysis::heavyhiggs::AnalysisNeutral analysis(tagger);
    const std::string name = tagger.name();
    Error("Tagger", name);
    analysis.SetConfig(config);

    std::string file_name = analysis.ProjectName() + "/" + name + ".root";
    if (gSystem->AccessPathName(file_name.c_str())) analysis.AnalysisLoop(stage);

    file_name = analysis.ProjectName() + "/Mva" + name + ".root";
    if (gSystem->AccessPathName(file_name.c_str())) analysis::Factory factory(tagger);

    file_name = analysis.ProjectName() + "/" + name + "Bdt.root";
    if (gSystem->AccessPathName(file_name.c_str())) {
//       analysis::Reader Reader(tagger);
//       Reader.OptimalSignificance();
    }
}

int main()
{
    fastjet::Error::set_print_errors(true);
    fastjet::Error::set_print_backtrace(true);

    analysis::Configuration config("Neutral");

    analysis::BottomTagger bottom_tagger;
    RunTagger(bottom_tagger, analysis::Stage::trainer, config);
    RunTagger(bottom_tagger, analysis::Stage::reader, config);

    analysis::JetPairTagger jet_pair_tagger;
    RunTagger(jet_pair_tagger, analysis::Stage::trainer, config);
    RunTagger(jet_pair_tagger, analysis::Stage::reader, config);

    analysis::WHadronicTagger w_hadronic_tagger;
    RunTagger(w_hadronic_tagger, analysis::Stage::trainer, config);
    RunTagger(w_hadronic_tagger, analysis::Stage::reader, config);

    analysis::WSemiTagger w_semi_tagger;
    RunTagger(w_semi_tagger, analysis::Stage::trainer, config);
    RunTagger(w_semi_tagger, analysis::Stage::reader, config);

    analysis::TopHadronicTagger top_hadronic_tagger;
    RunTagger(top_hadronic_tagger, analysis::Stage::trainer, config);
    RunTagger(top_hadronic_tagger, analysis::Stage::reader, config);

    analysis::TopSemiTagger tops_semi_tagger;
    RunTagger(tops_semi_tagger, analysis::Stage::trainer, config);
    RunTagger(tops_semi_tagger, analysis::Stage::reader, config);

    analysis::heavyhiggs::HeavyHiggsSemiTagger heavy_higgs_semi_tagger;
    RunTagger(heavy_higgs_semi_tagger, analysis::Stage::trainer, config);
    RunTagger(heavy_higgs_semi_tagger, analysis::Stage::reader, config);

    analysis::heavyhiggs::SignatureNeutralTagger signature_semi_tagger;
    RunTagger(signature_semi_tagger, analysis::Stage::trainer, config);
    RunTagger(signature_semi_tagger, analysis::Stage::reader, config);

    analysis::heavyhiggs::EventNeutralTagger event_semi_tagger;
    RunTagger(event_semi_tagger, analysis::Stage::trainer, config);
    RunTagger(event_semi_tagger, analysis::Stage::reader, config);

    std::cout << fastjet::LimitedWarning::summary() << std::endl;

    return 0;

}

