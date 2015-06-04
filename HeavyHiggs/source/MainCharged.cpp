#include "AnalysisCharged.hh"

#include "fastjet/LimitedWarning.hh"

void RunTagger(analysis::Tagger &tagger, analysis::Tagger::Stage stage)
{
    heavyhiggs::AnalysisCharged analysis(tagger);
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
//         case analysis::HAnalysis::JetPairTagger:
//             analysis::Factory(Analysis.jet_pair_tagger);
//             break;
//         case analysis::HAnalysis::WHadronicTagger:
//             analysis::Factory(Analysis.w_hadronic_tagger);
//             break;
//         case analysis::HAnalysis::HWSemiTagger:
//             analysis::Factory(Analysis.w_semi_tagger);
//             break;
//         case analysis::HAnalysis::TopLeptonicTagger:
// //             analysis::Factory(Analysis.top_leptonic_tagger);
//             break;
//         case analysis::HAnalysis::TopHadronicTagger:
//             analysis::Factory(Analysis.top_hadronic_tagger);
//             break;
//         case analysis::HAnalysis::HTopSemiTagger:
//             analysis::Factory(Analysis.top_semi_tagger);
//             break;
//         case analysis::HAnalysis::HeavyHiggsLeptonicTagger:
// //             analysis::Factory(Analysis.heavy_higgs_leptonic_tagger);
//             break;
//         case analysis::HAnalysis::HHeavyHiggsHadronicTagger:
// //             analysis::Factory(Analysis.HeavyHiggsHadronicTagger);
//             break;
//         case analysis::HAnalysis::HeavyHiggsSemiTagger:
//             analysis::Factory(Analysis.charged_higgs_semi_tagger);
//             break;
//         case analysis::HAnalysis::EventLeptonicTagger:
// //             analysis::Factory(Analysis.eventLeptonicTagger);
//             break;
//         case analysis::HAnalysis::EventHadronicTagger:
// //             analysis::Factory(Analysis.eventHadronicTagger);
//           break;
//         case analysis::HAnalysis::SignatureNeutralTagger:
//           analysis::Factory(Analysis.SignatureSemiTagger);
//           break;
//         case analysis::HAnalysis::EventNeutralTagger:
//             analysis::Factory(Analysis.eventSemiTagger);
//             break;
// //         case analysis::HAnalysis::ChargedHiggsSemiTagger:
// //           analysis::Factory(Analysis.charged_higgs_semi_tagger);
// //           break;
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
            analysis::Reader Reader(tagger);
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

    analysis::ChargedHiggsSemiTagger heavy_higgs_semi_tagger;
    RunTagger(heavy_higgs_semi_tagger, analysis::Tagger::kTrainer);
    RunTagger(heavy_higgs_semi_tagger, analysis::Tagger::kReader);

    analysis::TripletJetPairTagger jet_pair_tagger;
    RunTagger(jet_pair_tagger, analysis::Tagger::kTrainer);
    RunTagger(jet_pair_tagger, analysis::Tagger::kReader);

    heavyhiggs::SignatureChargedTagger signature_semi_tagger;
    RunTagger(signature_semi_tagger, analysis::Tagger::kTrainer);
    RunTagger(signature_semi_tagger, analysis::Tagger::kReader);

    heavyhiggs::EventChargedTagger event_semi_tagger;
    RunTagger(event_semi_tagger, analysis::Tagger::kTrainer);
    RunTagger(event_semi_tagger, analysis::Tagger::kReader);

    std::cout << fastjet::LimitedWarning::summary() << std::endl;

    return 0;
}
