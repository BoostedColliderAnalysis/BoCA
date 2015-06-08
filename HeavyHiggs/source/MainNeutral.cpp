#include "AnalysisNeutral.hh"

#include "fastjet/LimitedWarning.hh"

# include "Configuration.hh"
# include "TSystem.h"
# include "Factory.hh"
# include "Tagger.hh"

void RunTagger(analysis::Tagger &tagger, analysis::Tagger::Stage stage, const analysis::Configuration &config)
{
    heavyhiggs::AnalysisNeutral analysis(tagger);
    const std::string name = tagger.tagger_name();
    analysis.Print(analysis.kError, "Tagger", name);
    analysis.SetConfig(config);

    std::string file_name = analysis.ProjectName() + "/" + name + ".root";
    if (gSystem->AccessPathName(file_name.c_str())) analysis.AnalysisLoop(stage);

    file_name = analysis.ProjectName() + "/Mva" + name + ".root";
    if (gSystem->AccessPathName(file_name.c_str())) analysis::Factory factory(tagger);

    file_name = analysis.ProjectName() + "/" + name + "Bdt.root";
    if (gSystem->AccessPathName(file_name.c_str())) {
      analysis::Reader Reader(tagger);
      Reader.OptimalSignificance();
    }
}

int main()
{
    fastjet::Error::set_print_errors(true);
    fastjet::Error::set_print_backtrace(true);

    analysis::Configuration config("Neutral");

    analysis::BottomTagger bottom_tagger;
    RunTagger(bottom_tagger, analysis::Tagger::kTrainer, config);
    RunTagger(bottom_tagger, analysis::Tagger::kReader, config);

    analysis::JetPairTagger jet_pair_tagger;
    RunTagger(jet_pair_tagger, analysis::Tagger::kTrainer, config);
    RunTagger(jet_pair_tagger, analysis::Tagger::kReader, config);

    analysis::WHadronicTagger w_hadronic_tagger;
    RunTagger(w_hadronic_tagger, analysis::Tagger::kTrainer, config);
    RunTagger(w_hadronic_tagger, analysis::Tagger::kReader, config);

    analysis::WSemiTagger w_semi_tagger;
    RunTagger(w_semi_tagger, analysis::Tagger::kTrainer, config);
    RunTagger(w_semi_tagger, analysis::Tagger::kReader, config);

    analysis::TopHadronicTagger top_hadronic_tagger;
    RunTagger(top_hadronic_tagger, analysis::Tagger::kTrainer, config);
    RunTagger(top_hadronic_tagger, analysis::Tagger::kReader, config);

    analysis::TopSemiTagger tops_semi_tagger;
    RunTagger(tops_semi_tagger, analysis::Tagger::kTrainer, config);
    RunTagger(tops_semi_tagger, analysis::Tagger::kReader, config);

    heavyhiggs::HeavyHiggsSemiTagger heavy_higgs_semi_tagger;
    RunTagger(heavy_higgs_semi_tagger, analysis::Tagger::kTrainer, config);
    RunTagger(heavy_higgs_semi_tagger, analysis::Tagger::kReader, config);

    heavyhiggs::SignatureNeutralTagger signature_semi_tagger;
    RunTagger(signature_semi_tagger, analysis::Tagger::kTrainer, config);
    RunTagger(signature_semi_tagger, analysis::Tagger::kReader, config);

    heavyhiggs::EventNeutralTagger event_semi_tagger;
    RunTagger(event_semi_tagger, analysis::Tagger::kTrainer, config);
    RunTagger(event_semi_tagger, analysis::Tagger::kReader, config);

    std::cout << fastjet::LimitedWarning::summary() << std::endl;

    return 0;

}

