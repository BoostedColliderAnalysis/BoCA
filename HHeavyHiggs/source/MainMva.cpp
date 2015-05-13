#include "HAnalysisHeavyHiggsMva.hh"

#include "fastjet/LimitedWarning.hh"

# include "HConfig.hh"
# include "TSystem.h"
# include "Factory.hh"
# include "Tagger.hh"

void RunTagger(hanalysis::Tagger &tagger, hanalysis::Tagger::Stage stage, const HConfig &config)
{
    hheavyhiggs::HAnalysisMva Analysis(tagger);
    const std::string name = tagger.tagger_name();
    Analysis.Print(Analysis.kError, "Tagger", name);
    Analysis.SetConfig(config);

    std::string file_name = Analysis.ProjectName() + "/" + name + ".root";
    if (gSystem->AccessPathName(file_name.c_str())) Analysis.AnalysisLoop(stage);

    file_name = Analysis.ProjectName() + "/Mva" + name + ".root";
    if (gSystem->AccessPathName(file_name.c_str())) {
//         switch (Tagger) {
//         case hanalysis::HAnalysis::HBottomTagger:
            hanalysis::Factory factory(tagger);
//             break;
//         case hanalysis::HAnalysis::HJetPairTagger:
//             hanalysis::Factory(Analysis.JetPairTagger);
//             break;
//         case hanalysis::HAnalysis::WHadronicTagger:
//             hanalysis::Factory(Analysis.w_hadronic_tagger);
//             break;
//         case hanalysis::HAnalysis::HWSemiTagger:
//             hanalysis::Factory(Analysis.WSemiTagger);
//             break;
//         case hanalysis::HAnalysis::HTopLeptonicTagger:
// //             hanalysis::Factory(Analysis.TopLeptonicTagger);
//             break;
//         case hanalysis::HAnalysis::TopHadronicTagger:
//             hanalysis::Factory(Analysis.top_hadronic_tagger);
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
//             hanalysis::Factory(Analysis.HeavyHiggsSemiTagger);
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
//         case hanalysis::HAnalysis::HSignatureSemiTagger:
//             hanalysis::Factory(Analysis.SignatureSemiTagger);
//             break;
// //         case hanalysis::HAnalysis::HChargedHiggsSemiTagger:
// //           hanalysis::Factory(Analysis.ChargedHiggsSemiTagger);
// //           break;
//         default:
//             std::cout << "Unhandled case" << std::endl;
//         }
    }

//     FileName = Analysis.GetProjectName() + "/Mva" + Name + ".root";
//     if(!gSystem->AccessPathName(FileName.c_str())){
//             Analysis.PrepareReader(Tagger);
//     }


    file_name = Analysis.ProjectName() + "/" + name + "Bdt.root";
    if (gSystem->AccessPathName(file_name.c_str())) {
//         switch (Tagger) {
//         case hanalysis::HAnalysis::HEventLeptonicReader: {
//             hanalysis::Reader Reader(Analysis.EventLeptonicTagger);
//             Reader.SimpleMVALoop();
//             break;
//         }
//         case hanalysis::HAnalysis::HEventSemiReader: {
//             Analysis.SetTrees(hanalysis::HAnalysis::HEventSemiReader, hanalysis::HObject::kBackground);
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

    HConfig config("Neutral");

    hanalysis::BottomTagger bottom_tagger;
    RunTagger(bottom_tagger, hanalysis::Tagger::kTrainer, config);
    RunTagger(bottom_tagger, hanalysis::Tagger::kReader, config);

    hanalysis::HJetPairTagger jet_pair_tagger;
    RunTagger(jet_pair_tagger, hanalysis::Tagger::kTrainer, config);
    RunTagger(jet_pair_tagger, hanalysis::Tagger::kReader, config);

    hanalysis::WHadronicTagger w_hadronic_tagger;
    RunTagger(w_hadronic_tagger, hanalysis::Tagger::kTrainer, config);
    RunTagger(w_hadronic_tagger, hanalysis::Tagger::kReader, config);

    hanalysis::HWSemiTagger w_semi_tagger;
    RunTagger(w_semi_tagger, hanalysis::Tagger::kTrainer, config);
    RunTagger(w_semi_tagger, hanalysis::Tagger::kReader, config);

    hanalysis::TopHadronicTagger top_hadronic_tagger;
    RunTagger(top_hadronic_tagger, hanalysis::Tagger::kTrainer, config);
    RunTagger(top_hadronic_tagger, hanalysis::Tagger::kReader, config);

    hanalysis::HTopSemiTagger tops_semi_tagger;
    RunTagger(tops_semi_tagger, hanalysis::Tagger::kTrainer, config);
    RunTagger(tops_semi_tagger, hanalysis::Tagger::kReader, config);

    hanalysis::HHeavyHiggsSemiTagger heavy_higgs_semi_tagger;
    RunTagger(heavy_higgs_semi_tagger, hanalysis::Tagger::kTrainer, config);
    RunTagger(heavy_higgs_semi_tagger, hanalysis::Tagger::kReader, config);

    hheavyhiggs::HSignatureSemiTagger signature_semi_tagger;
    RunTagger(signature_semi_tagger, hanalysis::Tagger::kTrainer, config);
    RunTagger(signature_semi_tagger, hanalysis::Tagger::kReader, config);

    hheavyhiggs::HEventSemiTagger event_semi_tagger;
    RunTagger(event_semi_tagger, hanalysis::Tagger::kTrainer, config);
    RunTagger(event_semi_tagger, hanalysis::Tagger::kReader, config);

    std::cout << fastjet::LimitedWarning::summary() << std::endl;

    return 0;

}

