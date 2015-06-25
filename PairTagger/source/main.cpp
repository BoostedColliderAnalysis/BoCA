# include "AnalysisPair.hh"
# include "TSystem.h"
# include "JetPairTagger.hh"
# include "Factory.hh"

void RunTagger(analysis::Tagger &tagger, analysis::Tagger::Stage stage)
{
    fusionpair::Analysis analysis(tagger);
    const std::string Name = tagger.tagger_name();
    analysis.Print(analysis::Severity::Error, "Tagger", Name);

    std::string FileName = analysis.ProjectName() + "/" + Name + ".root";
    if (gSystem->AccessPathName(FileName.c_str())) analysis.AnalysisLoop(stage);

    FileName = analysis.ProjectName() + "/Mva" + Name + ".root";
    if (gSystem->AccessPathName(FileName.c_str())) {
//         switch (Tagger) {
//         case analysis::Analysis::HBottomTagger:
            analysis::Factory factory(tagger);
//             break;
//         case analysis::Analysis::JetPairTagger:
//           analysis::Factory(Analysis.jet_pair_tagger);
//           break;
//         default:
//             std::cout << "Unhandled case" << std::endl;
//         }
    }

    FileName = analysis.ProjectName() + "/" + Name + "Bdt.root";
    if (gSystem->AccessPathName(FileName.c_str())) {
//         switch (Tagger) {
//           case analysis::Analysis::HJetPairReader: {
//             Analysis.SetTrees(analysis::Analysis::HJetPairReader, analysis::Tag::Background);
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

    analysis::JetPairTagger jet_pair_tagger;
    RunTagger(jet_pair_tagger, analysis::Tagger::kTrainer);
    RunTagger(jet_pair_tagger, analysis::Tagger::kReader);

    return 0;

}
