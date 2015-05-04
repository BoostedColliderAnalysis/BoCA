#include "HAnalysisTopTagger.hh"
#include <exception>

#include "fastjet/LimitedWarning.hh"

void RunTagger(const hanalysis::HAnalysis::HTagger Tagger)
{
    htoptagger::HAnalysis Analysis;
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
//             hanalysis::HFactory(Analysis.WSemiTagger);
            break;
        case hanalysis::HAnalysis::HTopHadronicTagger:
            hanalysis::HFactory(Analysis.TopHadronicTagger);
            break;
        case hanalysis::HAnalysis::HTopSemiTagger:
            hanalysis::HFactory(Analysis.TopLeptonTagger);
            break;
        default:
            std::cout << "Unhandled case" << std::endl;
        }
    }

    FileName = Analysis.ProjectName() + "/" + Name + "Bdt.root";
    if (gSystem->AccessPathName(FileName.c_str())) {
        switch (Tagger) {
        case hanalysis::HAnalysis::HTopSemiReader: {
            Analysis.SetTrees(hanalysis::HAnalysis::HTopSemiTagger, hanalysis::HObject::kBackground);
            hanalysis::HReader Reader(Analysis.TopLeptonTagger);
            Reader.SimpleMVALoop();
            break;
        }
        case hanalysis::HAnalysis::HTopHadronicReader: {
            Analysis.SetTrees(hanalysis::HAnalysis::HTopHadronicTagger, hanalysis::HObject::kBackground);
            hanalysis::HReader Reader(Analysis.TopHadronicTagger);
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

    try {

        htoptagger::HAnalysis Analysis;

        RunTagger(hanalysis::HAnalysis::HBottomTagger);
//         RunTagger(hanalysis::HAnalysis::HBottomReader);

        if (Analysis.TopDecay() == htoptagger::HAnalysis::Hadronic) {
            RunTagger(hanalysis::HAnalysis::HWHadronicTagger);
//        RunTagger(hanalysis::HAnalysis::HWHadronicReader);
            RunTagger(hanalysis::HAnalysis::HTopHadronicTagger);
            RunTagger(hanalysis::HAnalysis::HTopHadronicReader);
        }

        if (Analysis.TopDecay() == htoptagger::HAnalysis::Leptonic) {
//         RunTagger(hanalysis::HAnalysis::HWSemiTagger);
//         RunTagger(hanalysis::HAnalysis::HWSemiReader);
            RunTagger(hanalysis::HAnalysis::HTopSemiTagger);
            RunTagger(hanalysis::HAnalysis::HTopSemiReader);
        }
    } catch (const std::exception &exception) {
        std::cout << "Standard exception: " << exception.what() << std::endl;
    }

    std::cout << fastjet::LimitedWarning::summary() << std::endl;

    return EXIT_SUCCESS;

}

