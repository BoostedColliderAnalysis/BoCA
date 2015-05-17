#include "HAnalysisPairTagger.hh"

void RunTagger(analysis::Tagger &tagger, analysis::Tagger::Stage stage)
{
    hpairtagger::HAnalysis Analysis(tagger);
    const std::string Name = tagger.tagger_name();
    Analysis.Print(Analysis.kError, "Tagger", Name);

    std::string FileName = Analysis.ProjectName() + "/" + Name + ".root";
    if (gSystem->AccessPathName(FileName.c_str())) Analysis.AnalysisLoop(stage);

    FileName = Analysis.ProjectName() + "/Mva" + Name + ".root";
    if (gSystem->AccessPathName(FileName.c_str())) {
//         switch (Tagger) {
//         case analysis::HAnalysis::HBottomTagger:
            analysis::Factory factory(tagger);
//             break;
//         case analysis::HAnalysis::HJetPairTagger:
//           analysis::Factory(Analysis.JetPairTagger);
//           break;
//         default:
//             std::cout << "Unhandled case" << std::endl;
//         }
    }

    FileName = Analysis.ProjectName() + "/" + Name + "Bdt.root";
    if (gSystem->AccessPathName(FileName.c_str())) {
//         switch (Tagger) {
//           case analysis::HAnalysis::HJetPairReader: {
//             Analysis.SetTrees(analysis::HAnalysis::HJetPairReader, analysis::Object::kBackground);
            analysis::Reader Reader(tagger);
            Reader.OptimalSignificance();
//             break;
//         }
//         default:
//             std::cout << "Unhandled case" << std::endl;
//         }
    }
}


int main()
{
  analysis::BottomTagger bottom_tagger;
    RunTagger(bottom_tagger, analysis::Tagger::kTrainer);
    RunTagger(bottom_tagger, analysis::Tagger::kReader);

    analysis::HJetPairTagger jet_pair_tagger;
    RunTagger(jet_pair_tagger, analysis::Tagger::kTrainer);
    RunTagger(jet_pair_tagger, analysis::Tagger::kReader);

    return 0;

}
