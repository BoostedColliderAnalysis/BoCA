# include "AnalysisHiggs.hh"

# include "Configuration.hh"
# include "TSystem.h"
# include "Factory.hh"
# include "EventTagger.hh"

void RunTagger(analysis::Tagger &tagger, analysis::Tagger::Stage stage, const analysis::Configuration &config)
{
  higgscpv::Analysis analysis(tagger);
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
  analysis::Configuration config("HiggsCpv");

  analysis::BottomTagger bottom_tagger;
  RunTagger(bottom_tagger, analysis::Tagger::kTrainer, config);
  RunTagger(bottom_tagger, analysis::Tagger::kReader, config);

  analysis::TopLeptonicTagger top_hadronic_tagger;
  RunTagger(top_hadronic_tagger, analysis::Tagger::kTrainer, config);
  RunTagger(top_hadronic_tagger, analysis::Tagger::kReader, config);

  analysis::HiggsTagger heavy_higgs_semi_tagger;
  RunTagger(heavy_higgs_semi_tagger, analysis::Tagger::kTrainer, config);
  RunTagger(heavy_higgs_semi_tagger, analysis::Tagger::kReader, config);

  higgscpv::TopLeptonicPairTagger jet_pair_tagger;
  RunTagger(jet_pair_tagger, analysis::Tagger::kTrainer, config);
  RunTagger(jet_pair_tagger, analysis::Tagger::kReader, config);

  higgscpv::SignatureTagger signature_semi_tagger;
  RunTagger(signature_semi_tagger, analysis::Tagger::kTrainer, config);
  RunTagger(signature_semi_tagger, analysis::Tagger::kReader, config);

  higgscpv::EventTagger event_semi_tagger;
  RunTagger(event_semi_tagger, analysis::Tagger::kTrainer, config);
  RunTagger(event_semi_tagger, analysis::Tagger::kReader, config);

}

