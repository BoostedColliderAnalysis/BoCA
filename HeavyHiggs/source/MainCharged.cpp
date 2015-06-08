# include "AnalysisCharged.hh"
# include "TSystem.h"
# include "Factory.hh"
# include "EventChargedTagger.hh"

# include "fastjet/LimitedWarning.hh"

void RunTagger(analysis::Tagger &tagger, analysis::Tagger::Stage stage)
{
    heavyhiggs::AnalysisCharged analysis(tagger);
    const std::string Name = tagger.tagger_name();
    analysis.Print(analysis.kError, "Tagger", Name);

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
    RunTagger(bottom_tagger, analysis::Tagger::kTrainer);
    RunTagger(bottom_tagger, analysis::Tagger::kReader);

    analysis::WHadronicTagger w_hadronic_tagger;
    RunTagger(w_hadronic_tagger, analysis::Tagger::kTrainer);
    RunTagger(w_hadronic_tagger, analysis::Tagger::kReader);

    analysis::WSemiTagger w_semi_tagger;
    RunTagger(w_semi_tagger, analysis::Tagger::kTrainer);
    RunTagger(w_semi_tagger, analysis::Tagger::kReader);

    analysis::TopHadronicTagger top_hadronic_tagger;
    RunTagger(top_hadronic_tagger, analysis::Tagger::kTrainer);
    RunTagger(top_hadronic_tagger, analysis::Tagger::kReader);

    analysis::TopSemiTagger tops_semi_tagger;
    RunTagger(tops_semi_tagger, analysis::Tagger::kTrainer);
    RunTagger(tops_semi_tagger, analysis::Tagger::kReader);

    heavyhiggs::ChargedHiggsSemiTagger heavy_higgs_semi_tagger;
    RunTagger(heavy_higgs_semi_tagger, analysis::Tagger::kTrainer);
    RunTagger(heavy_higgs_semi_tagger, analysis::Tagger::kReader);

    analysis::TripletJetPairTagger jet_pair_tagger;
    RunTagger(jet_pair_tagger, analysis::Tagger::kTrainer);
    RunTagger(jet_pair_tagger, analysis::Tagger::kReader);

    heavyhiggs::SignatureChargedTagger signature_semi_tagger;
    RunTagger(signature_semi_tagger, analysis::Tagger::kTrainer);
    RunTagger(signature_semi_tagger, analysis::Tagger::kReader);

    heavyhiggs::EventChargedTagger event_semi_tagger;
    RunTagger(event_semi_tagger, analysis::Tagger::kTrainer);
    RunTagger(event_semi_tagger, analysis::Tagger::kReader);

    std::cout << fastjet::LimitedWarning::summary() << std::endl;

    return 0;
}
