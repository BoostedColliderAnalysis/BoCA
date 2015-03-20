#include "HAnalysisHeavyHiggsMva.hh"

#include "fastjet/LimitedWarning.hh"

#include "HConfig.hh"

void RunTagger(const hanalysis::HAnalysis::HTagger Tagger, const HConfig &config)
{
    hheavyhiggs::HAnalysisMva Analysis;
    const std::string Name = Analysis.StudyName(Tagger);
    Analysis.Print(Analysis.HError, "Tagger", Tagger, Name);
    Analysis.SetConfig(config);

    std::string FileName = Analysis.ProjectName() + "/" + Name + ".root";
    if (gSystem->AccessPathName(FileName.c_str())) Analysis.AnalysisLoop(Tagger);

    FileName = Analysis.ProjectName() + "/Mva" + Name + ".root";
    if (gSystem->AccessPathName(FileName.c_str())) {
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
            hanalysis::HFactory(Analysis.TopLeptonicTagger);
            break;
        case hanalysis::HAnalysis::HTopHadronicTagger:
            hanalysis::HFactory(Analysis.TopHadronicTagger);
            break;
        case hanalysis::HAnalysis::HTopSemiTagger:
            hanalysis::HFactory(Analysis.TopSemiTagger);
            break;
        case hanalysis::HAnalysis::HHeavyHiggsLeptonicTagger:
            hanalysis::HFactory(Analysis.HeavyHiggsLeptonicTagger);
            break;
        case hanalysis::HAnalysis::HHeavyHiggsHadronicTagger:
            hanalysis::HFactory(Analysis.HeavyHiggsHadronicTagger);
            break;
        case hanalysis::HAnalysis::HHeavyHiggsSemiTagger:
            hanalysis::HFactory(Analysis.HeavyHiggsSemiTagger);
            break;
        case hanalysis::HAnalysis::HEventLeptonicTagger:
            hanalysis::HFactory(Analysis.EventLeptonicTagger);
            break;
        case hanalysis::HAnalysis::HEventHadronicTagger:
            hanalysis::HFactory(Analysis.EventHadronicTagger);
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


    FileName = Analysis.ProjectName() + "/" + Name + "Bdt.root";
    if (gSystem->AccessPathName(FileName.c_str())) {
        switch (Tagger) {
        case hanalysis::HAnalysis::HEventLeptonicReader: {
            hanalysis::HReader Reader(Analysis.EventLeptonicTagger);
            Reader.SimpleMVALoop();
            break;
        }
        case hanalysis::HAnalysis::HEventSemiReader: {
          Analysis.SetTrees(hanalysis::HAnalysis::HEventSemiReader,hanalysis::HObject::HBackground);
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

    RunTagger(hanalysis::HAnalysis::HBottomTagger,config);
        RunTagger(hanalysis::HAnalysis::HBottomReader,config);

    RunTagger(hanalysis::HAnalysis::HJetPairTagger,config);
        RunTagger(hanalysis::HAnalysis::HJetPairReader,config);

    RunTagger(hanalysis::HAnalysis::HWHadronicTagger,config);
        RunTagger(hanalysis::HAnalysis::HWHadronicReader,config);

    RunTagger(hanalysis::HAnalysis::HWSemiTagger,config);
        RunTagger(hanalysis::HAnalysis::HWSemiReader,config);

    RunTagger(hanalysis::HAnalysis::HTopHadronicTagger,config);
        RunTagger(hanalysis::HAnalysis::HTopHadronicReader,config);

    RunTagger(hanalysis::HAnalysis::HTopSemiTagger,config);
        RunTagger(hanalysis::HAnalysis::HTopSemiReader,config);

    RunTagger(hanalysis::HAnalysis::HHeavyHiggsSemiTagger,config);
        RunTagger(hanalysis::HAnalysis::HHeavyHiggsSemiReader,config);

    RunTagger(hanalysis::HAnalysis::HSignatureSemiTagger,config);
        RunTagger(hanalysis::HAnalysis::HSignatureSemiReader,config);

    RunTagger(hanalysis::HAnalysis::HEventSemiTagger,config);
    RunTagger(hanalysis::HAnalysis::HEventSemiReader,config);

    std::cout << fastjet::LimitedWarning::summary() << std::endl;

    return 0;

}

