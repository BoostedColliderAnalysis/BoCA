# include "AnalysisHiggs.hh"

# include "TSystem.h"
# include "Factory.hh"
# include "../include/EventTagger.hh"

void RunTagger(analysis::Tagger &tagger, analysis::Tagger::Stage stage)
{
  analysis::higgscpv::Analysis analysis(tagger);
  const std::string name = tagger.name(stage);
  analysis.Print(analysis::Severity::error, "Tagger", name);

  std::string file_name = analysis.ProjectName() + "/" + name + ".root";
  if (gSystem->AccessPathName(file_name.c_str())) analysis.AnalysisLoop(stage);
}

void RunFactory(analysis::Tagger &tagger)
{
  analysis::higgscpv::Analysis analysis(tagger);
  const std::string name = tagger.name(analysis::Tagger::kTrainer);
  analysis.Print(analysis::Severity::error, "Tagger", name);
  std::string file_name = analysis.ProjectName() + "/Mva" + name + ".root";
  if (gSystem->AccessPathName(file_name.c_str())) analysis::Factory factory(tagger);
}

void RunReader(analysis::Tagger &tagger)
{
  analysis::higgscpv::Analysis analysis(tagger);
  const std::string file_name = analysis.ProjectName() + "/" + tagger.tagger_name() + "Bdt.root";
  if (gSystem->AccessPathName(file_name.c_str())) {
    analysis::Reader reader(tagger);
    reader.OptimalSignificance();
  }
}

int main()
{
  analysis::BottomTagger bottom_tagger;
  RunTagger(bottom_tagger, analysis::Tagger::kTrainer);
  RunFactory(bottom_tagger);
  RunTagger(bottom_tagger, analysis::Tagger::kReader);

  analysis::TopLeptonicTagger top_leptonic_tagger;
  RunTagger(top_leptonic_tagger, analysis::Tagger::kTrainer);
  RunFactory(top_leptonic_tagger);
  RunTagger(top_leptonic_tagger, analysis::Tagger::kReader);

  analysis::HiggsTagger higgs_tagger;
  RunTagger(higgs_tagger, analysis::Tagger::kTrainer);
  RunFactory(higgs_tagger);
  RunTagger(higgs_tagger, analysis::Tagger::kReader);

  analysis::higgscpv::TopLeptonicPairTagger jet_pair_tagger;
  RunTagger(jet_pair_tagger, analysis::Tagger::kTrainer);
  RunFactory(jet_pair_tagger);
  RunTagger(jet_pair_tagger, analysis::Tagger::kReader);

  analysis::higgscpv::SignatureTagger signature_semi_tagger;
  RunTagger(signature_semi_tagger, analysis::Tagger::kTrainer);
  RunFactory(signature_semi_tagger);
  RunTagger(signature_semi_tagger, analysis::Tagger::kReader);

  analysis::higgscpv::EventTagger event_semi_tagger;
  RunTagger(event_semi_tagger, analysis::Tagger::kTrainer);
  RunFactory(event_semi_tagger);
  RunTagger(event_semi_tagger, analysis::Tagger::kReader);
  RunReader(event_semi_tagger);

}

