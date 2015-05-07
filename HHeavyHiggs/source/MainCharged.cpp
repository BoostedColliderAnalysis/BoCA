#include "HAnalysisChargedHiggsMva.hh"

#include "fastjet/LimitedWarning.hh"

void RunTagger(hanalysis::Tagger &tagger, hanalysis::Tagger::Stage stage)
{
    hheavyhiggs::HAnalysisCharged Analysis(tagger);
    const std::string Name = tagger.tagger_name();
    Analysis.Print(Analysis.HError, "Tagger", Name);

    std::string FileName = Analysis.ProjectName() + "/" + Name + ".root";
    if (gSystem->AccessPathName(FileName.c_str())) Analysis.AnalysisLoop(stage);

    FileName = Analysis.ProjectName() + "/Mva" + Name + ".root";
    if (gSystem->AccessPathName(FileName.c_str())) {
//         switch (Tagger) {
//         case hanalysis::HAnalysis::HBottomTagger:
            hanalysis::Factory factory(tagger);
//             break;
//         case hanalysis::HAnalysis::HJetPairTagger:
//             hanalysis::Factory(Analysis.JetPairTagger);
//             break;
//         case hanalysis::HAnalysis::HWHadronicTagger:
//             hanalysis::Factory(Analysis.WHadronicTagger);
//             break;
//         case hanalysis::HAnalysis::HWSemiTagger:
//             hanalysis::Factory(Analysis.WSemiTagger);
//             break;
//         case hanalysis::HAnalysis::HTopLeptonicTagger:
// //             hanalysis::Factory(Analysis.TopLeptonicTagger);
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
//           break;
//         case hanalysis::HAnalysis::HSignatureSemiTagger:
//           hanalysis::Factory(Analysis.SignatureSemiTagger);
//           break;
//         case hanalysis::HAnalysis::HEventSemiTagger:
//             hanalysis::Factory(Analysis.EventSemiTagger);
//             break;
// //         case hanalysis::HAnalysis::HChargedHiggsSemiTagger:
// //           hanalysis::Factory(Analysis.ChargedHiggsSemiTagger);
// //           break;
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
            hanalysis::Reader Reader(tagger);
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


    hanalysis::BottomTagger bottom_tagger;
    RunTagger(bottom_tagger, hanalysis::Tagger::kTrainer);
    RunTagger(bottom_tagger, hanalysis::Tagger::kReader);

    hanalysis::HWHadronicTagger w_hadronic_tagger;
    RunTagger(w_hadronic_tagger, hanalysis::Tagger::kTrainer);
    RunTagger(w_hadronic_tagger, hanalysis::Tagger::kReader);

    hanalysis::HWSemiTagger w_semi_tagger;
    RunTagger(w_semi_tagger, hanalysis::Tagger::kTrainer);
    RunTagger(w_semi_tagger, hanalysis::Tagger::kReader);

    hanalysis::HTopHadronicTagger top_hadronic_tagger;
    RunTagger(top_hadronic_tagger, hanalysis::Tagger::kTrainer);
    RunTagger(top_hadronic_tagger, hanalysis::Tagger::kReader);

    hanalysis::HTopSemiTagger tops_semi_tagger;
    RunTagger(tops_semi_tagger, hanalysis::Tagger::kTrainer);
    RunTagger(tops_semi_tagger, hanalysis::Tagger::kReader);

    hanalysis::HChargedHiggsSemiTagger heavy_higgs_semi_tagger;
    RunTagger(heavy_higgs_semi_tagger, hanalysis::Tagger::kTrainer);
    RunTagger(heavy_higgs_semi_tagger, hanalysis::Tagger::kReader);

    hanalysis::HChargedJetPairTagger jet_pair_tagger;
    RunTagger(jet_pair_tagger, hanalysis::Tagger::kTrainer);
    RunTagger(jet_pair_tagger, hanalysis::Tagger::kReader);

    hheavyhiggs::HChargedSignatureSemiTagger signature_semi_tagger;
    RunTagger(signature_semi_tagger, hanalysis::Tagger::kTrainer);
    RunTagger(signature_semi_tagger, hanalysis::Tagger::kReader);

    hheavyhiggs::HChargedEventSemiTagger event_semi_tagger;
    RunTagger(event_semi_tagger, hanalysis::Tagger::kTrainer);
    RunTagger(event_semi_tagger, hanalysis::Tagger::kReader);

    std::cout << fastjet::LimitedWarning::summary() << std::endl;

    return 0;
}
