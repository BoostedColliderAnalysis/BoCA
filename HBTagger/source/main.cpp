#include "HAnalysisBTagger.hh"
#include "HBottomTagger.hh"

void RunTagger(hanalysis::Tagger &tagger, hanalysis::Tagger::Stage stage)
{
    hbtagger::HAnalysis Analysis(tagger);
    const std::string Name = tagger.tagger_name();
    Analysis.Print(Analysis.HError, "Tagger", Name);

    std::string FileName = Analysis.ProjectName() + "/" + Name + ".root";
    if (gSystem->AccessPathName(FileName.c_str())) Analysis.AnalysisLoop(stage);

    FileName = Analysis.ProjectName() + "/Mva" + Name + ".root";
    if (gSystem->AccessPathName(FileName.c_str())) {
//         switch (Tagger) {
//         case hanalysis::HAnalysis::HBottomTagger:
            hanalysis::HFactory factory(tagger);
//             break;
//         default:
//             std::cout << "Unhandled case" << std::endl;
//         }
    }

    FileName = Analysis.ProjectName() + "/" + Name + "Bdt.root";
    if (gSystem->AccessPathName(FileName.c_str())) {
//         switch (Tagger) {
//         case hanalysis::HAnalysis::HBottomReader: {
//             Analysis.SetTrees(hanalysis::HAnalysis::HBottomReader, hanalysis::HObject::kBackground);
            hanalysis::HReader Reader(tagger);
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
  hanalysis::HBottomTagger bottom_tagger;
  RunTagger(bottom_tagger, hanalysis::Tagger::kTrainer);
  RunTagger(bottom_tagger, hanalysis::Tagger::kReader);

    return 0;

}
