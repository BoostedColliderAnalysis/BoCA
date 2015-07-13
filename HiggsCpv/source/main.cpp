#include "AnalysisHiggsCpv.hh"

#include "TSystem.h"
#include "Factory.hh"
#include "../include/EventTagger.hh"
#include "Debug.hh"

void RunTagger(analysis::Tagger &tagger, analysis::Stage stage)
{
//   analysis::higgscpv::Analysis analysis(tagger);
//   const std::string name = tagger.name(stage);
//   Error("Tagger", name);
//
//   std::string file_name = analysis.ProjectName() + "/" + name + ".root";
//   if (gSystem->AccessPathName(file_name.c_str())) analysis.AnalysisLoop(stage);
}

void RunFactory(analysis::Tagger &tagger)
{
  analysis::higgscpv::Analysis analysis(tagger);
  const std::string name = tagger.Name(analysis::Stage::trainer);
  Error("Tagger", name);
  std::string file_name = analysis.ProjectName() + "/Mva" + name + ".root";
  if (gSystem->AccessPathName(file_name.c_str())) analysis::Factory factory(tagger);
}

void RunReader(analysis::Tagger &tagger)
{
  analysis::higgscpv::Analysis analysis(tagger);
  const std::string file_name = analysis.ProjectName() + "/" + tagger.Name() + "Bdt.root";
  if (gSystem->AccessPathName(file_name.c_str())) {
//     analysis::Reader reader(tagger);
//     reader.OptimalSignificance();
  }
}

int main()
{
  analysis::BottomTagger bottom_tagger;
  RunTagger(bottom_tagger, analysis::Stage::trainer);
  RunFactory(bottom_tagger);
  RunTagger(bottom_tagger, analysis::Stage::reader);

  analysis::TopLeptonicTagger top_leptonic_tagger;
  RunTagger(top_leptonic_tagger, analysis::Stage::trainer);
  RunFactory(top_leptonic_tagger);
  RunTagger(top_leptonic_tagger, analysis::Stage::reader);

  analysis::HiggsTagger higgs_tagger;
  RunTagger(higgs_tagger, analysis::Stage::trainer);
  RunFactory(higgs_tagger);
  RunTagger(higgs_tagger, analysis::Stage::reader);

  analysis::higgscpv::TopLeptonicPairTagger jet_pair_tagger;
  RunTagger(jet_pair_tagger, analysis::Stage::trainer);
  RunFactory(jet_pair_tagger);
  RunTagger(jet_pair_tagger, analysis::Stage::reader);

  analysis::higgscpv::SignatureTagger signature_semi_tagger;
  RunTagger(signature_semi_tagger, analysis::Stage::trainer);
  RunFactory(signature_semi_tagger);
  RunTagger(signature_semi_tagger, analysis::Stage::reader);

  analysis::higgscpv::EventTagger event_semi_tagger;
  RunTagger(event_semi_tagger, analysis::Stage::trainer);
  RunFactory(event_semi_tagger);
  RunTagger(event_semi_tagger, analysis::Stage::reader);
  RunReader(event_semi_tagger);

}

