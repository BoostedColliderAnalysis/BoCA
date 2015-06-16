# include "AnalysisTopPartner.hh"

# include "TSystem.h"
# include "Factory.hh"
# include "EventTagger.hh"

void RunTagger(analysis::Tagger &tagger, analysis::Tagger::Stage stage)
{
  analysis::toppartner::Analysis analysis(tagger);
  const std::string name = tagger.name(stage);
  analysis.Print(analysis.kError, "Tagger", name);

  std::string file_name = analysis.ProjectName() + "/" + name + ".root";
  if (gSystem->AccessPathName(file_name.c_str())) analysis.AnalysisLoop(stage);
}

void RunFactory(analysis::Tagger &tagger)
{
  analysis::toppartner::Analysis analysis(tagger);
  const std::string name = tagger.name(analysis::Tagger::kTrainer);
  analysis.Print(analysis.kError, "Tagger", name);
  std::string file_name = analysis.ProjectName() + "/Mva" + name + ".root";
  if (gSystem->AccessPathName(file_name.c_str())) analysis::Factory factory(tagger);
}

void RunReader(analysis::Tagger &tagger)
{
  analysis::toppartner::Analysis analysis(tagger);
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

  analysis::HiggsTagger higgs_tagger;
  RunTagger(higgs_tagger, analysis::Tagger::kTrainer);
  RunFactory(higgs_tagger);
  RunTagger(higgs_tagger, analysis::Tagger::kReader);

  analysis::toppartner::HiggsPairTagger higgs_pair_tagger;
  RunTagger(higgs_pair_tagger, analysis::Tagger::kTrainer);
  RunFactory(higgs_pair_tagger);
  RunTagger(higgs_pair_tagger, analysis::Tagger::kReader);

  analysis::TopHadronicTagger top_hadronic_tagger;
  RunTagger(top_hadronic_tagger, analysis::Tagger::kTrainer);
  RunFactory(top_hadronic_tagger);
  RunTagger(top_hadronic_tagger, analysis::Tagger::kReader);

  analysis::TopSemiTagger top_semi_tagger;
  RunTagger(top_semi_tagger, analysis::Tagger::kTrainer);
  RunFactory(top_semi_tagger);
  RunTagger(top_semi_tagger, analysis::Tagger::kReader);

  analysis::ZHadronicTagger z_hadronic_tagger;
  RunTagger(z_hadronic_tagger, analysis::Tagger::kTrainer);
  RunFactory(z_hadronic_tagger);
  RunTagger(z_hadronic_tagger, analysis::Tagger::kReader);

  analysis::toppartner::TopPartnerHadronicTagger top_partner_hadronic_tagger;
  RunTagger(top_partner_hadronic_tagger, analysis::Tagger::kTrainer);
  RunFactory(top_partner_hadronic_tagger);
  RunTagger(top_partner_hadronic_tagger, analysis::Tagger::kReader);

  analysis::toppartner::TopPartnerSemiTagger top_partner_semi_tagger;
  RunTagger(top_partner_semi_tagger, analysis::Tagger::kTrainer);
  RunFactory(top_partner_semi_tagger);
  RunTagger(top_partner_semi_tagger, analysis::Tagger::kReader);

  analysis::toppartner::TopPartnerPairTagger top_partner_pair_tagger;
  RunTagger(top_partner_pair_tagger, analysis::Tagger::kTrainer);
  RunFactory(top_partner_pair_tagger);
  RunTagger(top_partner_pair_tagger, analysis::Tagger::kReader);

  analysis::toppartner::SignatureTagger signature_tagger;
  RunTagger(signature_tagger, analysis::Tagger::kTrainer);
  RunFactory(signature_tagger);
  RunTagger(signature_tagger, analysis::Tagger::kReader);

  analysis::toppartner::EventTagger event_tagger;
  RunTagger(event_tagger, analysis::Tagger::kTrainer);
  RunFactory(event_tagger);
  RunTagger(event_tagger, analysis::Tagger::kReader);
  RunReader(event_tagger);

}

