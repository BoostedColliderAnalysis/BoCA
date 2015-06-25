# include "HAnalysisBottomSumTagger.hh"
# include "JetPairTagger.hh"
# include "TSystem.h"

void RunTagger(analysis::Tagger &tagger, analysis::Tagger::Stage stage)
{
    hbottomsumtagger::HAnalysis analysis(tagger);
    const std::string Name = tagger.tagger_name();
    analysis.Print(analysis::Severity::Error, "Tagger", Name);

    std::string FileName = analysis.ProjectName() + "/" + Name + ".root";
    if (gSystem->AccessPathName(FileName.c_str())) analysis.AnalysisLoop(stage);

    FileName = analysis.ProjectName() + "/Mva" + Name + ".root";
    if (gSystem->AccessPathName(FileName.c_str())) {
//         switch (tagger) {
//         case analysis::HAnalysis::HBottomTagger:
            analysis::Factory factory(tagger);
//             break;
//         case analysis::HAnalysis::JetPairTagger:
//           analysis::Factory(Analysis.eventBottomSumTagger);
//           break;
//         default:
//             std::cout << "Unhandled case" << std::endl;
//         }
    }

    FileName = analysis.ProjectName() + "/" + Name + "Bdt.root";
    if (gSystem->AccessPathName(FileName.c_str())) {
//         switch (tagger) {
//           case analysis::HAnalysis::HJetPairReader: {
//             Analysis.SetTrees(analysis::HAnalysis::HJetPairReader, analysis::Tag::Background);
            analysis::Reader Reader(tagger);
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
  analysis::BottomTagger bottom_tagger;
  RunTagger(bottom_tagger, analysis::Tagger::kTrainer);

  analysis::JetPairTagger jet_pair_tagger;
  RunTagger(jet_pair_tagger, analysis::Tagger::kTrainer);
  RunTagger(jet_pair_tagger, analysis::Tagger::kReader);

    return 0;

}
