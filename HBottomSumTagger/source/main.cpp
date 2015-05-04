#include "HAnalysisBottomSumTagger.hh"

void RunTagger(const hanalysis::HAnalysis::HTagger Tagger)
{
    hbottomsumtagger::HAnalysis Analysis;
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
        case hanalysis::HAnalysis::HJetPairTagger:
          hanalysis::HFactory(Analysis.EventBottomSumTagger);
          break;
        default:
            std::cout << "Unhandled case" << std::endl;
        }
    }

    FileName = Analysis.ProjectName() + "/" + Name + "Bdt.root";
    if (gSystem->AccessPathName(FileName.c_str())) {
        switch (Tagger) {
          case hanalysis::HAnalysis::HJetPairReader: {
            Analysis.SetTrees(hanalysis::HAnalysis::HJetPairReader, hanalysis::HObject::kBackground);
            hanalysis::HReader Reader(Analysis.EventBottomSumTagger);
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
    RunTagger(hanalysis::HAnalysis::HJetPairTagger);
    RunTagger(hanalysis::HAnalysis::HJetPairReader);

    return 0;

}
