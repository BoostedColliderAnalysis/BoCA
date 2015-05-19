#include "HAnalysisTau.hh"

#include "fastjet/LimitedWarning.hh"

void RunTagger(analysis::Tagger &tagger, analysis::Tagger::Stage stage)
{
    hheavyhiggs::HAnalysisTau analysis(tagger);
    const std::string Name = tagger.tagger_name();
    analysis.Print(analysis.kError, "Tagger", Name);

    std::string FileName = analysis.ProjectName() + "/" + Name + ".root";
    if (gSystem->AccessPathName(FileName.c_str())) analysis.AnalysisLoop(stage);

    FileName = analysis.ProjectName() + "/Mva" + Name + ".root";
    if (gSystem->AccessPathName(FileName.c_str())) {
//         switch (Tagger) {
//         case analysis::HAnalysis::HTauTagger:
            analysis::Factory factory(tagger);
//             break;
//         case analysis::HAnalysis::HJetPairTagger:
//             analysis::Factory(Analysis.JetPairTagger);
//             break;
//         case analysis::HAnalysis::WHadronicTagger:
//             analysis::Factory(Analysis.w_hadronic_tagger);
//             break;
//         case analysis::HAnalysis::HHeavyHiggsTauTagger:
//             analysis::Factory(Analysis.Higgstau_tagger);
//             break;
//         case analysis::HAnalysis::HTopLeptonicTagger:
//             analysis::Factory(Analysis.TopLeptonicTagger);
//             break;
//         case analysis::HAnalysis::TopHadronicTagger:
//             analysis::Factory(Analysis.top_hadronic_tagger);
//             break;
//         case analysis::HAnalysis::HTopSemiTagger:
//             analysis::Factory(Analysis.top_semi_tagger);
//             break;
//         case analysis::HAnalysis::HHeavyHiggsLeptonicTagger:
// //             analysis::Factory(Analysis.HeavyHiggsLeptonicTagger);
//             break;
//         case analysis::HAnalysis::HHeavyHiggsHadronicTagger:
// //             analysis::Factory(Analysis.HeavyHiggsHadronicTagger);
//             break;
//         case analysis::HAnalysis::HHeavyHiggsSemiTagger:
//             analysis::Factory(Analysis.ChargedHiggsSemiTagger);
//             break;
//         case analysis::HAnalysis::EventLeptonicTagger:
// //             analysis::Factory(Analysis.eventLeptonicTagger);
//             break;
//         case analysis::HAnalysis::EventHadronicTagger:
// //             analysis::Factory(Analysis.eventHadronicTagger);
//             break;
//         case analysis::HAnalysis::EventSemiTagger:
//             analysis::Factory(Analysis.eventSemiTagger);
//             break;
//         case analysis::HAnalysis::HChargedHiggsSemiTagger:
//           analysis::Factory(Analysis.ChargedHiggsSemiTagger);
//           break;
//         default:
//             std::cout << "Unhandled case" << std::endl;
//         }
    }

    FileName = analysis.ProjectName() + "/" + Name + "Bdt.root";
    if (gSystem->AccessPathName(FileName.c_str())) {
//         switch (Tagger) {
//         case analysis::HAnalysis::EventLeptonicReader: {
//             analysis::Reader Reader(Analysis.eventLeptonicTagger);
//             Reader.SimpleMVALoop();
//             break;
//         }
//         case analysis::HAnalysis::EventSemiReader: {
//           Analysis.SetTrees(Tagger,analysis::HAnalysis::kSignal);
//             analysis::Reader Reader(Analysis.eventSemiTagger);
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

    analysis::TauTagger tau_tagger;
    RunTagger(tau_tagger, analysis::Tagger::kTrainer);
    RunTagger(tau_tagger, analysis::Tagger::kReader);

    analysis::HHeavyHiggsTauTagger heavy_higgs_tau_tagger;
    RunTagger(heavy_higgs_tau_tagger, analysis::Tagger::kTrainer);
    RunTagger(heavy_higgs_tau_tagger, analysis::Tagger::kReader);

    std::cout << fastjet::LimitedWarning::summary() << std::endl;



    return 0;

}
