#include "HAnalysisHeavyHiggsTt.hh"

#include "fastjet/LimitedWarning.hh"

void RunTagger(analysis::Tagger &tagger, analysis::Tagger::Stage stage)
{
    hheavyhiggs::HAnalysisTt analysis(tagger);
    const std::string Name = tagger.tagger_name();
    analysis.Print(analysis.kError, "Tagger", Name);

    std::string FileName = analysis.ProjectName() + "/" + Name + ".root";
    if (gSystem->AccessPathName(FileName.c_str())) analysis.AnalysisLoop(stage);

    FileName = analysis.ProjectName() + "/Mva" + Name + ".root";
    if (gSystem->AccessPathName(FileName.c_str())) {
//         switch (Tagger) {
//         case analysis::HAnalysis::HBottomTagger:
            analysis::Factory factory(tagger);
//             break;
//         case analysis::HAnalysis::WHadronicTagger:
//             analysis::Factory(Analysis.w_hadronic_tagger);
//             break;
//         case analysis::HAnalysis::HWSemiTagger:
//             analysis::Factory(Analysis.w_semi_tagger);
//             break;
//         case analysis::HAnalysis::TopHadronicTagger:
//             analysis::Factory(Analysis.top_hadronic_tagger);
//             break;
//         case analysis::HAnalysis::HTopSemiTagger:
//             analysis::Factory(Analysis.top_semi_tagger);
//             break;
//         case analysis::HAnalysis::HHeavyHiggsSemiTagger:
//             analysis::Factory(Analysis.HeavyHiggsSemiTagger);
//             break;
//         case analysis::HAnalysis::EventSemiTagger:
//             analysis::Factory(Analysis.eventSemiTagger);
//             break;
//         default:
//             std::cout << "Unhandled case" << std::endl;
//         }
    }

    FileName = analysis.ProjectName() + "/" + Name + "Bdt.root";
    if (gSystem->AccessPathName(FileName.c_str())) {
//         switch (Tagger) {
//         case analysis::HAnalysis::EventSemiReader: {
            analysis::Reader Reader(tagger);
            Reader.OptimalSignificance();
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

    analysis::HHeavyHiggsSemiTagger heavy_higgs_semi_tagger;
    RunTagger(heavy_higgs_semi_tagger, analysis::Tagger::kTrainer);
    RunTagger(heavy_higgs_semi_tagger, analysis::Tagger::kReader);


    hheavyhiggs::EventTtSemiTagger event_semi_tagger;
    RunTagger(event_semi_tagger, analysis::Tagger::kTrainer);
    RunTagger(event_semi_tagger, analysis::Tagger::kReader);


    std::cout << fastjet::LimitedWarning::summary() << std::endl;



    return 0;

}

