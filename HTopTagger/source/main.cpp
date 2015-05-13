#include "HAnalysisTopTagger.hh"
#include "TopHadronicTagger.hh"
#include "HTopSemiTagger.hh"
#include "HWSemiTagger.hh"
#include "TSystem.h"
# include "Factory.hh"
#include <exception>

#include "fastjet/LimitedWarning.hh"

void RunTagger(hanalysis::Tagger &tagger, hanalysis::Tagger::Stage stage)
{
  htoptagger::HAnalysis analysis(tagger);
  const std::string name = tagger.name(stage);
  analysis.Print(analysis.kError, "Tagger", name);

  std::string file_name = analysis.ProjectName() + "/" + name + ".root";
  if (gSystem->AccessPathName(file_name.c_str())) analysis.AnalysisLoop(stage);
}

void RunFactory(hanalysis::Tagger &tagger)
{
  htoptagger::HAnalysis analysis(tagger);
  const std::string name = tagger.name(hanalysis::Tagger::kTrainer);
  analysis.Print(analysis.kError, "Tagger", name);
  std::string file_name = analysis.ProjectName() + "/Mva" + name + ".root";
  if (gSystem->AccessPathName(file_name.c_str())) hanalysis::Factory factory(tagger);
}

void RunReader(hanalysis::Tagger &tagger)
{
  htoptagger::HAnalysis analysis(tagger);
  const std::string file_name = analysis.ProjectName() + "/" + tagger.tagger_name() + "Bdt.root";
  if (gSystem->AccessPathName(file_name.c_str())) {
    hanalysis::Reader reader(tagger);
    reader.OptimalSignificance();
  }
}

int main(const int argc, const char **argv)
{
    const std::vector<std::string> Arguments(argv, argv + argc);
    for (const auto & Argument : Arguments) std::cout << Argument << std::endl;
    fastjet::Error::set_print_errors(true);
    fastjet::Error::set_print_backtrace(true);
    try {

        hanalysis::BottomTagger bottom_tagger;
        RunTagger(bottom_tagger, hanalysis::Tagger::kTrainer);
        RunFactory(bottom_tagger);
        RunTagger(bottom_tagger, hanalysis::Tagger::kReader);

        htoptagger::HAnalysis analysis(bottom_tagger);
        if (analysis.TopDecay() == htoptagger::HAnalysis::kHadronic) {

            hanalysis::WHadronicTagger w_hadronic_tagger;
            RunTagger(w_hadronic_tagger, hanalysis::Tagger::kTrainer);
            RunFactory(w_hadronic_tagger);
            RunTagger(w_hadronic_tagger, hanalysis::Tagger::kReader);

            hanalysis::TopHadronicTagger top_hadronic_tagger;
            RunTagger(top_hadronic_tagger, hanalysis::Tagger::kTrainer);
            RunFactory(top_hadronic_tagger);
            RunTagger(top_hadronic_tagger, hanalysis::Tagger::kReader);
            RunReader(top_hadronic_tagger);

        }

        if (analysis.TopDecay() == htoptagger::HAnalysis::kLeptonic) {

            hanalysis::HWSemiTagger w_semi_tagger;
            RunTagger(w_semi_tagger, hanalysis::Tagger::kTrainer);
            RunFactory(w_semi_tagger);
            RunTagger(w_semi_tagger, hanalysis::Tagger::kReader);

            hanalysis::HTopSemiTagger tops_semi_tagger;
            RunTagger(tops_semi_tagger, hanalysis::Tagger::kTrainer);
            RunFactory(tops_semi_tagger);
            RunTagger(tops_semi_tagger, hanalysis::Tagger::kReader);
            RunReader(tops_semi_tagger);
        }
    } catch (const std::exception &exception) {
      std::cout << "Standard exception: " << exception.what() << std::endl;
    }
    std::cout << fastjet::LimitedWarning::summary() << std::endl;
    return EXIT_SUCCESS;
}

