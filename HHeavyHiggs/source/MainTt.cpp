#include "HAnalysisHeavyHiggsTt.hh"

#include "fastjet/LimitedWarning.hh"

void RunTagger(const hanalysis::HAnalysis::HTagger Tagger)
{
    hheavyhiggs::HAnalysisTt Analysis;
    const std::string Name = Analysis.StudyName(Tagger);
    Analysis.Print(Analysis.HError, "Tagger", Tagger, Name);

    std::string FileName = Analysis.ProjectName() + "/" + Name + ".root";
    if (gSystem->AccessPathName(FileName.c_str())) Analysis.AnalysisLoop(Tagger);

    FileName = Analysis.ProjectName() + "/Mva" + Name + ".root";
    if (gSystem->AccessPathName(FileName.c_str())) {
        switch (Tagger) {
        case hanalysis::HAnalysis::HBottomTagger:
            hanalysis::HFactory(Analysis.BottomTagger);
            break;
        case hanalysis::HAnalysis::HWHadronicTagger:
            hanalysis::HFactory(Analysis.WHadronicTagger);
            break;
        case hanalysis::HAnalysis::HWSemiTagger:
            hanalysis::HFactory(Analysis.WSemiTagger);
            break;
        case hanalysis::HAnalysis::HTopHadronicTagger:
            hanalysis::HFactory(Analysis.TopHadronicTagger);
            break;
        case hanalysis::HAnalysis::HTopSemiTagger:
            hanalysis::HFactory(Analysis.TopSemiTagger);
            break;
        case hanalysis::HAnalysis::HHeavyHiggsSemiTagger:
            hanalysis::HFactory(Analysis.HeavyHiggsSemiTagger);
            break;
        case hanalysis::HAnalysis::HEventSemiTagger:
            hanalysis::HFactory(Analysis.EventSemiTagger);
            break;
        default:
            std::cout << "Unhandled case" << std::endl;
        }
    }

    FileName = Analysis.ProjectName() + "/" + Name + "Bdt.root";
    if (gSystem->AccessPathName(FileName.c_str())) {
        switch (Tagger) {
        case hanalysis::HAnalysis::HEventSemiReader: {
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

    RunTagger(hanalysis::HAnalysis::HBottomTagger);
//     RunTagger(hanalysis::HAnalysis::HBottomReader);

    RunTagger(hanalysis::HAnalysis::HWHadronicTagger);
//     RunTagger(hanalysis::HAnalysis::HWHadronicReader);

    RunTagger(hanalysis::HAnalysis::HWSemiTagger);
//     RunTagger(hanalysis::HAnalysis::HWSemiReader);


    RunTagger(hanalysis::HAnalysis::HTopHadronicTagger);
//     RunTagger(hanalysis::HAnalysis::HTopHadronicReader);

    RunTagger(hanalysis::HAnalysis::HTopSemiTagger);
//     RunTagger(hanalysis::HAnalysis::HTopSemiReader);
//
    RunTagger(hanalysis::HAnalysis::HHeavyHiggsSemiTagger);
//     RunTagger(hanalysis::HAnalysis::HHeavyHiggsSemiReader);

    RunTagger(hanalysis::HAnalysis::HEventSemiTagger);
    RunTagger(hanalysis::HAnalysis::HEventSemiReader);


    std::cout << fastjet::LimitedWarning::summary() << std::endl;



    return 0;

}

