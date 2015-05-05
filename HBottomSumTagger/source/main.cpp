#include "HAnalysisBottomSumTagger.hh"
#include "HJetPairTagger.hh"

void RunTagger(hanalysis::Tagger &tagger, hanalysis::Tagger::Stage stage)
{
    hbottomsumtagger::HAnalysis Analysis(tagger);
    const std::string Name = tagger.tagger_name();
    Analysis.Print(Analysis.HError, "Tagger", Name);

    std::string FileName = Analysis.ProjectName() + "/" + Name + ".root";
    if (gSystem->AccessPathName(FileName.c_str())) Analysis.AnalysisLoop(stage);

    FileName = Analysis.ProjectName() + "/Mva" + Name + ".root";
    if (gSystem->AccessPathName(FileName.c_str())) {
//         switch (tagger) {
//         case hanalysis::HAnalysis::HBottomTagger:
            hanalysis::HFactory factory(tagger);
//             break;
//         case hanalysis::HAnalysis::HJetPairTagger:
//           hanalysis::HFactory(Analysis.EventBottomSumTagger);
//           break;
//         default:
//             std::cout << "Unhandled case" << std::endl;
//         }
    }

    FileName = Analysis.ProjectName() + "/" + Name + "Bdt.root";
    if (gSystem->AccessPathName(FileName.c_str())) {
//         switch (tagger) {
//           case hanalysis::HAnalysis::HJetPairReader: {
//             Analysis.SetTrees(hanalysis::HAnalysis::HJetPairReader, hanalysis::HObject::kBackground);
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

  hanalysis::HJetPairTagger jet_pair_tagger;
  RunTagger(jet_pair_tagger, hanalysis::Tagger::kTrainer);
  RunTagger(jet_pair_tagger, hanalysis::Tagger::kReader);

    return 0;

}
