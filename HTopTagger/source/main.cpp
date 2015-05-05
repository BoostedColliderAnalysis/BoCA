#include "HAnalysisTopTagger.hh"
#include "HTopHadronicTagger.hh"
#include "HTopSemiTagger.hh"
#include "HWSemiTagger.hh"
#include <exception>

#include "fastjet/LimitedWarning.hh"

void RunTagger(hanalysis::Tagger &tagger, hanalysis::Tagger::Stage stage)
{
    htoptagger::HAnalysis Analysis(tagger);
    const std::string Name = tagger.tagger_name();
    Analysis.Print(Analysis.HError, "Tagger", Name);

    std::string FileName = Analysis.ProjectName() + "/" + Name + ".root";
    if (gSystem->AccessPathName(FileName.c_str())) Analysis.AnalysisLoop(stage);

    FileName = Analysis.ProjectName() + "/Mva" + Name + ".root";
    if (gSystem->AccessPathName(FileName.c_str())) {
//         switch (Tagger) {
//         case hanalysis::HAnalysis::HBottomTagger:
            hanalysis::HFactory factory(tagger);
//             break;
//         case hanalysis::HAnalysis::HWHadronicTagger:
//             hanalysis::HFactory(Analysis.WHadronicTagger);
//             break;
//         case hanalysis::HAnalysis::HWSemiTagger:
//             hanalysis::HFactory(Analysis.WSemiTagger);
//             break;
//         case hanalysis::HAnalysis::HTopHadronicTagger:
//             hanalysis::HFactory(Analysis.TopHadronicTagger);
//             break;
//         case hanalysis::HAnalysis::HTopSemiTagger:
//             hanalysis::HFactory(Analysis.TopLeptonTagger);
//             break;
//         default:
//             std::cout << "Unhandled case" << std::endl;
//         }
    }

    FileName = Analysis.ProjectName() + "/" + Name + "Bdt.root";
    if (gSystem->AccessPathName(FileName.c_str())) {
//         switch (Tagger) {
//         case hanalysis::HAnalysis::HTopSemiReader: {
//             Analysis.SetTrees(hanalysis::HAnalysis::HTopSemiTagger, hanalysis::HObject::kBackground);
            hanalysis::HReader Reader(tagger);
            Reader.SimpleMVALoop();
//             break;
//         }
//         case hanalysis::HAnalysis::HTopHadronicReader: {
//             Analysis.SetTrees(hanalysis::HAnalysis::HTopHadronicTagger, hanalysis::HObject::kBackground);
//             hanalysis::HReader Reader(Analysis.TopHadronicTagger);
//             Reader.SimpleMVALoop();
//             break;
//         }
//         default:
//             std::cout << "Unhandled case" << std::endl;
//         }
    }
}

int main()
{
    fastjet::Error::set_print_errors(true);
    fastjet::Error::set_print_backtrace(true);


    try {

        hanalysis::HBottomTagger bottom_tagger;
        RunTagger(bottom_tagger, hanalysis::Tagger::kTrainer);
        RunTagger(bottom_tagger, hanalysis::Tagger::kReader);

        htoptagger::HAnalysis analysis(bottom_tagger);
        if (analysis.TopDecay() == htoptagger::HAnalysis::Hadronic) {

          hanalysis::HWHadronicTagger w_hadronic_tagger;
          RunTagger(w_hadronic_tagger, hanalysis::Tagger::kTrainer);
          RunTagger(w_hadronic_tagger, hanalysis::Tagger::kReader);

          hanalysis::HTopHadronicTagger top_hadronic_tagger;
          RunTagger(top_hadronic_tagger, hanalysis::Tagger::kTrainer);
          RunTagger(top_hadronic_tagger, hanalysis::Tagger::kReader);

        }

        if (analysis.TopDecay() == htoptagger::HAnalysis::Leptonic) {

          hanalysis::HWSemiTagger w_semi_tagger;
          RunTagger(w_semi_tagger, hanalysis::Tagger::kTrainer);
          RunTagger(w_semi_tagger, hanalysis::Tagger::kReader);

          hanalysis::HTopSemiTagger tops_semi_tagger;
          RunTagger(tops_semi_tagger, hanalysis::Tagger::kTrainer);
          RunTagger(tops_semi_tagger, hanalysis::Tagger::kReader);
        }
    } catch (const std::exception &exception) {
        std::cout << "Standard exception: " << exception.what() << std::endl;
    }

    std::cout << fastjet::LimitedWarning::summary() << std::endl;

    return EXIT_SUCCESS;

}

