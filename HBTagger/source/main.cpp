#include "HAnalysisBTagger.hh"

void RunTagger(const hanalysis::HAnalysis::HTagger Tagger)
{
    hbtagger::HAnalysis Analysis;
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
        default:
            std::cout << "Unhandled case" << std::endl;
        }
    }

    FileName = Analysis.ProjectName() + "/" + Name + "Bdt.root";
    if (gSystem->AccessPathName(FileName.c_str())) {
        switch (Tagger) {
        case hanalysis::HAnalysis::HBottomReader: {
            Analysis.SetTrees(hanalysis::HAnalysis::HBottomReader, hanalysis::HObject::HBackground);
            hanalysis::HReader Reader(Analysis.BottomTagger);
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
    RunTagger(hanalysis::HAnalysis::HBottomTagger);
    RunTagger(hanalysis::HAnalysis::HBottomReader);

    return 0;

}
