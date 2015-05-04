#include "HAnalysisHeavyHiggsMva.hh"

#include "fastjet/LimitedWarning.hh"

# include "HConfig.hh"
# include "TSystem.h"
# include "HFactory.hh"
# include "Tagger.hh"

void RunTagger(const hanalysis::Tagger &tagger, hanalysis::Tagger::Stage stage, const HConfig &config)
{
    hheavyhiggs::HAnalysisMva Analysis(tagger);
    const std::string name = tagger.tagger_name();
    Analysis.Print(Analysis.HError, "Tagger", name);
    Analysis.SetConfig(config);

    std::string file_name = Analysis.ProjectName() + "/" + name + ".root";
    if (gSystem->AccessPathName(file_name.c_str())) Analysis.AnalysisLoop(stage);

    file_name = Analysis.ProjectName() + "/Mva" + name + ".root";
    if (gSystem->AccessPathName(file_name.c_str())) {
        switch (Tagger) {
        case hanalysis::HAnalysis::HBottomTagger:
            hanalysis::HFactory(Analysis.BottomTagger);
            break;
        case hanalysis::HAnalysis::HJetPairTagger:
            hanalysis::HFactory(Analysis.JetPairTagger);
            break;
        case hanalysis::HAnalysis::HWHadronicTagger:
            hanalysis::HFactory(Analysis.WHadronicTagger);
            break;
        case hanalysis::HAnalysis::HWSemiTagger:
            hanalysis::HFactory(Analysis.WSemiTagger);
            break;
        case hanalysis::HAnalysis::HTopLeptonicTagger:
//             hanalysis::HFactory(Analysis.TopLeptonicTagger);
            break;
        case hanalysis::HAnalysis::HTopHadronicTagger:
            hanalysis::HFactory(Analysis.TopHadronicTagger);
            break;
        case hanalysis::HAnalysis::HTopSemiTagger:
            hanalysis::HFactory(Analysis.TopSemiTagger);
            break;
        case hanalysis::HAnalysis::HHeavyHiggsLeptonicTagger:
//             hanalysis::HFactory(Analysis.HeavyHiggsLeptonicTagger);
            break;
        case hanalysis::HAnalysis::HHeavyHiggsHadronicTagger:
//             hanalysis::HFactory(Analysis.HeavyHiggsHadronicTagger);
            break;
        case hanalysis::HAnalysis::HHeavyHiggsSemiTagger:
            hanalysis::HFactory(Analysis.HeavyHiggsSemiTagger);
            break;
        case hanalysis::HAnalysis::HEventLeptonicTagger:
//             hanalysis::HFactory(Analysis.EventLeptonicTagger);
            break;
        case hanalysis::HAnalysis::HEventHadronicTagger:
//             hanalysis::HFactory(Analysis.EventHadronicTagger);
            break;
        case hanalysis::HAnalysis::HEventSemiTagger:
            hanalysis::HFactory(Analysis.EventSemiTagger);
            break;
        case hanalysis::HAnalysis::HSignatureSemiTagger:
            hanalysis::HFactory(Analysis.SignatureSemiTagger);
            break;
//         case hanalysis::HAnalysis::HChargedHiggsSemiTagger:
//           hanalysis::HFactory(Analysis.ChargedHiggsSemiTagger);
//           break;
        default:
            std::cout << "Unhandled case" << std::endl;
        }
    }

//     FileName = Analysis.GetProjectName() + "/Mva" + Name + ".root";
//     if(!gSystem->AccessPathName(FileName.c_str())){
//             Analysis.PrepareReader(Tagger);
//     }


    file_name = Analysis.ProjectName() + "/" + name + "Bdt.root";
    if (gSystem->AccessPathName(file_name.c_str())) {
        switch (Tagger) {
        case hanalysis::HAnalysis::HEventLeptonicReader: {
//             hanalysis::HReader Reader(Analysis.EventLeptonicTagger);
//             Reader.SimpleMVALoop();
            break;
        }
        case hanalysis::HAnalysis::HEventSemiReader: {
            Analysis.SetTrees(hanalysis::HAnalysis::HEventSemiReader, hanalysis::HObject::kBackground);
            hanalysis::HReader Reader(Analysis.EventSemiTagger);
            Reader.SimpleMVALoop();
            break;
        }
        default:
            std::cout << "Unhandled case" << std::endl;
        }
    }
}

int main()
{
    fastjet::Error::set_print_errors(true);
    fastjet::Error::set_print_backtrace(true);

    HConfig config("Neutral");

    HBottomTagger bottom_tagger;
    RunTagger(bottom_tagger, hanalysis::Tagger::kTrainer, config);
    RunTagger(bottom_tagger, hanalysis::Tagger::kReader, config);

    HJetPairTagger jet_pair_tagger;
    RunTagger(jet_pair_tagger, hanalysis::Tagger::kTrainer, config);
    RunTagger(jet_pair_tagger, hanalysis::Tagger::kReader, config);

    HWHadronicTagger w_hadronic_tagger;
    RunTagger(w_hadronic_tagger, hanalysis::Tagger::kTrainer, config);
    RunTagger(w_hadronic_tagger, hanalysis::Tagger::kReader, config);

    HWSemiTagger w_semi_tagger;
    RunTagger(w_semi_tagger, hanalysis::Tagger::kTrainer, config);
    RunTagger(w_semi_tagger, hanalysis::Tagger::kReader, config);

    HTopHadronicTagger top_hadronic_tagger;
    RunTagger(top_hadronic_tagger, hanalysis::Tagger::kTrainer, config);
    RunTagger(top_hadronic_tagger, hanalysis::Tagger::kReader, config);

    HTopSemiTagger tops_semi_tagger;
    RunTagger(tops_semi_tagger, hanalysis::Tagger::kTrainer, config);
    RunTagger(tops_semi_tagger, hanalysis::Tagger::kReader, config);

    HHeavyHiggsSemiTagger heavy_higgs_semi_tagger;
    RunTagger(heavy_higgs_semi_tagger, hanalysis::Tagger::kTrainer, config);
    RunTagger(heavy_higgs_semi_tagger, hanalysis::Tagger::kReader, config);

    HSignatureSemiTagger signature_semi_tagger;
    RunTagger(signature_semi_tagger, hanalysis::Tagger::kTrainer, config);
    RunTagger(signature_semi_tagger, hanalysis::Tagger::kReader, config);

    HEventSemiTagger event_semi_tagger;
    RunTagger(event_semi_tagger, hanalysis::Tagger::kTrainer, config);
    RunTagger(event_semi_tagger, hanalysis::Tagger::kReader, config);

    std::cout << fastjet::LimitedWarning::summary() << std::endl;

    return 0;

}

