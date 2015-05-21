#include "HAnalysisHeavyHiggsMva.hh"

#include "fastjet/LimitedWarning.hh"

# include "Configuration.hh"
# include "TSystem.h"
# include "Factory.hh"
# include "Tagger.hh"

void RunTagger(analysis::Tagger &tagger, analysis::Tagger::Stage stage, const analysis::Configuration &config)
{
    hheavyhiggs::HAnalysisMva analysis(tagger);
    const std::string name = tagger.tagger_name();
    analysis.Print(analysis.kError, "Tagger", name);
    analysis.SetConfig(config);

    std::string file_name = analysis.ProjectName() + "/" + name + ".root";
    if (gSystem->AccessPathName(file_name.c_str())) analysis.AnalysisLoop(stage);

    file_name = analysis.ProjectName() + "/Mva" + name + ".root";
    if (gSystem->AccessPathName(file_name.c_str())) {
//         switch (Tagger) {
//         case analysis::HAnalysis::HBottomTagger:
            analysis::Factory factory(tagger);
//             break;
//         case analysis::HAnalysis::HJetPairTagger:
//             analysis::Factory(Analysis.JetPairTagger);
//             break;
//         case analysis::HAnalysis::WHadronicTagger:
//             analysis::Factory(Analysis.w_hadronic_tagger);
//             break;
//         case analysis::HAnalysis::HWSemiTagger:
//             analysis::Factory(Analysis.w_semi_tagger);
//             break;
//         case analysis::HAnalysis::HTopLeptonicTagger:
// //             analysis::Factory(Analysis.TopLeptonicTagger);
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
//             analysis::Factory(Analysis.HeavyHiggsSemiTagger);
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
//         case analysis::HAnalysis::HSignatureSemiTagger:
//             analysis::Factory(Analysis.SignatureSemiTagger);
//             break;
// //         case analysis::HAnalysis::HChargedHiggsSemiTagger:
// //           analysis::Factory(Analysis.ChargedHiggsSemiTagger);
// //           break;
//         default:
//             std::cout << "Unhandled case" << std::endl;
//         }
    }

//     FileName = Analysis.GetProjectName() + "/Mva" + Name + ".root";
//     if(!gSystem->AccessPathName(FileName.c_str())){
//             Analysis.PrepareReader(Tagger);
//     }


    file_name = analysis.ProjectName() + "/" + name + "Bdt.root";
    if (gSystem->AccessPathName(file_name.c_str())) {
//         switch (Tagger) {
//         case analysis::HAnalysis::EventLeptonicReader: {
//             analysis::Reader Reader(Analysis.eventLeptonicTagger);
//             Reader.SimpleMVALoop();
//             break;
//         }
//         case analysis::HAnalysis::EventSemiReader: {
//             Analysis.SetTrees(analysis::HAnalysis::EventSemiReader, analysis::Object::kBackground);
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

    analysis::Configuration config("Neutral");

    analysis::BottomTagger bottom_tagger;
    RunTagger(bottom_tagger, analysis::Tagger::kTrainer, config);
    RunTagger(bottom_tagger, analysis::Tagger::kReader, config);

    analysis::HJetPairTagger jet_pair_tagger;
    RunTagger(jet_pair_tagger, analysis::Tagger::kTrainer, config);
    RunTagger(jet_pair_tagger, analysis::Tagger::kReader, config);

    analysis::WHadronicTagger w_hadronic_tagger;
    RunTagger(w_hadronic_tagger, analysis::Tagger::kTrainer, config);
    RunTagger(w_hadronic_tagger, analysis::Tagger::kReader, config);

    analysis::WSemiTagger w_semi_tagger;
    RunTagger(w_semi_tagger, analysis::Tagger::kTrainer, config);
    RunTagger(w_semi_tagger, analysis::Tagger::kReader, config);

    analysis::TopHadronicTagger top_hadronic_tagger;
    RunTagger(top_hadronic_tagger, analysis::Tagger::kTrainer, config);
    RunTagger(top_hadronic_tagger, analysis::Tagger::kReader, config);

    analysis::TopSemiTagger tops_semi_tagger;
    RunTagger(tops_semi_tagger, analysis::Tagger::kTrainer, config);
    RunTagger(tops_semi_tagger, analysis::Tagger::kReader, config);

    analysis::HHeavyHiggsSemiTagger heavy_higgs_semi_tagger;
    RunTagger(heavy_higgs_semi_tagger, analysis::Tagger::kTrainer, config);
    RunTagger(heavy_higgs_semi_tagger, analysis::Tagger::kReader, config);

    hheavyhiggs::HSignatureSemiTagger signature_semi_tagger;
    RunTagger(signature_semi_tagger, analysis::Tagger::kTrainer, config);
    RunTagger(signature_semi_tagger, analysis::Tagger::kReader, config);

    hheavyhiggs::EventSemiTagger event_semi_tagger;
    RunTagger(event_semi_tagger, analysis::Tagger::kTrainer, config);
    RunTagger(event_semi_tagger, analysis::Tagger::kReader, config);

    std::cout << fastjet::LimitedWarning::summary() << std::endl;

    return 0;

}

