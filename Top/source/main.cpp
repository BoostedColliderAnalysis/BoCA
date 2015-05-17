#include "AnalysisTopTagger.hh"
#include "TopHadronicTagger.hh"
#include "HTopSemiTagger.hh"
#include "TSystem.h"
# include "Factory.hh"
#include <exception>

#include "fastjet/LimitedWarning.hh"

void RunTagger(analysis::Tagger &tagger, analysis::Tagger::Stage stage)
{
  htoptagger::HAnalysis analysis(tagger);
  const std::string name = tagger.name(stage);
  analysis.Print(analysis.kError, "Tagger", name);

  std::string file_name = analysis.ProjectName() + "/" + name + ".root";
  if (gSystem->AccessPathName(file_name.c_str())) analysis.AnalysisLoop(stage);
}

void RunFactory(analysis::Tagger &tagger)
{
  htoptagger::HAnalysis analysis(tagger);
  const std::string name = tagger.name(analysis::Tagger::kTrainer);
  analysis.Print(analysis.kError, "Tagger", name);
  std::string file_name = analysis.ProjectName() + "/Mva" + name + ".root";
  if (gSystem->AccessPathName(file_name.c_str())) analysis::Factory factory(tagger);
}

void RunReader(analysis::Tagger &tagger)
{
  htoptagger::HAnalysis analysis(tagger);
  const std::string file_name = analysis.ProjectName() + "/" + tagger.tagger_name() + "Bdt.root";
  if (gSystem->AccessPathName(file_name.c_str())) {
    analysis::Reader reader(tagger);
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

        analysis::BottomTagger bottom_tagger;
        RunTagger(bottom_tagger, analysis::Tagger::kTrainer);
        RunFactory(bottom_tagger);
        RunTagger(bottom_tagger, analysis::Tagger::kReader);

        htoptagger::HAnalysis analysis(bottom_tagger);
        if (analysis.TopDecay() == htoptagger::HAnalysis::kHadronic) {

            analysis::WHadronicTagger w_hadronic_tagger;
            RunTagger(w_hadronic_tagger, analysis::Tagger::kTrainer);
            RunFactory(w_hadronic_tagger);
            RunTagger(w_hadronic_tagger, analysis::Tagger::kReader);

            analysis::TopHadronicTagger top_hadronic_tagger;
            RunTagger(top_hadronic_tagger, analysis::Tagger::kTrainer);
            RunFactory(top_hadronic_tagger);
            RunTagger(top_hadronic_tagger, analysis::Tagger::kReader);
            RunReader(top_hadronic_tagger);

        }

        if (analysis.TopDecay() == htoptagger::HAnalysis::kLeptonic) {

            analysis::HWSemiTagger w_semi_tagger;
            RunTagger(w_semi_tagger, analysis::Tagger::kTrainer);
            RunFactory(w_semi_tagger);
            RunTagger(w_semi_tagger, analysis::Tagger::kReader);

            analysis::HTopSemiTagger tops_semi_tagger;
            RunTagger(tops_semi_tagger, analysis::Tagger::kTrainer);
            RunFactory(tops_semi_tagger);
            RunTagger(tops_semi_tagger, analysis::Tagger::kReader);
            RunReader(tops_semi_tagger);
        }
    } catch (const std::exception &exception) {
      std::cout << "Standard exception: " << exception.what() << std::endl;
    }
    std::cout << fastjet::LimitedWarning::summary() << std::endl;
    return EXIT_SUCCESS;
}

