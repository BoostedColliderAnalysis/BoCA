#include "HAnalysisTau.hh"

#include "fastjet/LimitedWarning.hh"

void RunTagger(hanalysis::Tagger &tagger, hanalysis::Tagger::Stage stage)
{
    hheavyhiggs::HAnalysisTau Analysis(tagger);
    const std::string Name = tagger.tagger_name();
    Analysis.Print(Analysis.kError, "Tagger", Name);

    std::string FileName = Analysis.ProjectName() + "/" + Name + ".root";
    if (gSystem->AccessPathName(FileName.c_str())) Analysis.AnalysisLoop(stage);

    FileName = Analysis.ProjectName() + "/Mva" + Name + ".root";
    if (gSystem->AccessPathName(FileName.c_str())) {
//         switch (Tagger) {
//         case hanalysis::HAnalysis::HTauTagger:
            hanalysis::Factory factory(tagger);
//             break;
//         case hanalysis::HAnalysis::HJetPairTagger:
//             hanalysis::Factory(Analysis.JetPairTagger);
//             break;
//         case hanalysis::HAnalysis::HWHadronicTagger:
//             hanalysis::Factory(Analysis.WHadronicTagger);
//             break;
//         case hanalysis::HAnalysis::HHeavyHiggsTauTagger:
//             hanalysis::Factory(Analysis.HiggsTauTagger);
//             break;
//         case hanalysis::HAnalysis::HTopLeptonicTagger:
//             hanalysis::Factory(Analysis.TopLeptonicTagger);
//             break;
//         case hanalysis::HAnalysis::HTopHadronicTagger:
//             hanalysis::Factory(Analysis.TopHadronicTagger);
//             break;
//         case hanalysis::HAnalysis::HTopSemiTagger:
//             hanalysis::Factory(Analysis.TopSemiTagger);
//             break;
//         case hanalysis::HAnalysis::HHeavyHiggsLeptonicTagger:
// //             hanalysis::Factory(Analysis.HeavyHiggsLeptonicTagger);
//             break;
//         case hanalysis::HAnalysis::HHeavyHiggsHadronicTagger:
// //             hanalysis::Factory(Analysis.HeavyHiggsHadronicTagger);
//             break;
//         case hanalysis::HAnalysis::HHeavyHiggsSemiTagger:
//             hanalysis::Factory(Analysis.ChargedHiggsSemiTagger);
//             break;
//         case hanalysis::HAnalysis::HEventLeptonicTagger:
// //             hanalysis::Factory(Analysis.EventLeptonicTagger);
//             break;
//         case hanalysis::HAnalysis::HEventHadronicTagger:
// //             hanalysis::Factory(Analysis.EventHadronicTagger);
//             break;
//         case hanalysis::HAnalysis::HEventSemiTagger:
//             hanalysis::Factory(Analysis.EventSemiTagger);
//             break;
//         case hanalysis::HAnalysis::HChargedHiggsSemiTagger:
//           hanalysis::Factory(Analysis.ChargedHiggsSemiTagger);
//           break;
//         default:
//             std::cout << "Unhandled case" << std::endl;
//         }
    }

    FileName = Analysis.ProjectName() + "/" + Name + "Bdt.root";
    if (gSystem->AccessPathName(FileName.c_str())) {
//         switch (Tagger) {
//         case hanalysis::HAnalysis::HEventLeptonicReader: {
//             hanalysis::Reader Reader(Analysis.EventLeptonicTagger);
//             Reader.SimpleMVALoop();
//             break;
//         }
//         case hanalysis::HAnalysis::HEventSemiReader: {
//           Analysis.SetTrees(Tagger,hanalysis::HAnalysis::kSignal);
//             hanalysis::Reader Reader(Analysis.EventSemiTagger);
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

    hanalysis::HTauTagger tau_tagger;
    RunTagger(tau_tagger, hanalysis::Tagger::kTrainer);
    RunTagger(tau_tagger, hanalysis::Tagger::kReader);

    hanalysis::HHeavyHiggsTauTagger heavy_higgs_tau_tagger;
    RunTagger(heavy_higgs_tau_tagger, hanalysis::Tagger::kTrainer);
    RunTagger(heavy_higgs_tau_tagger, hanalysis::Tagger::kReader);

    std::cout << fastjet::LimitedWarning::summary() << std::endl;



    return 0;

}
