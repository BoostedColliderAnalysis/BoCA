#include "AnalysisPair.hh"
#include "TSystem.h"
#include "JetPairTagger.hh"
#include "Factory.hh"
#include "Debug.hh"

void RunTagger(analysis::Tagger& tagger, analysis::Stage stage)
{
//     fusionpair::Analysis analysis(tagger);
//     const std::string Name = tagger.name();
//     Error("Tagger", Name);
//
//     std::string FileName = analysis.ProjectName() + "/" + Name + ".root";
//     if (gSystem->AccessPathName(FileName.c_str())) analysis.AnalysisLoop(stage);
//
//     FileName = analysis.ProjectName() + "/Mva" + Name + ".root";
//     if (gSystem->AccessPathName(FileName.c_str())) {
// //         switch (Tagger) {
// //         case analysis::Analysis::HBottomTagger:
//             analysis::Factory factory(tagger);
// //             break;
// //         case analysis::Analysis::JetPairTagger:
// //           analysis::Factory(Analysis.jet_pair_tagger);
// //           break;
// //         default:
// //             std::cout << "Unhandled case" << std::endl;
// //         }
//     }
//
//     FileName = analysis.ProjectName() + "/" + Name + "Bdt.root";
//     if (gSystem->AccessPathName(FileName.c_str())) {
// //         switch (Tagger) {
// //           case analysis::Analysis::HJetPairReader: {
// //             Analysis.SetTrees(analysis::Analysis::HJetPairReader, analysis::Tag::background);
// //             analysis::Reader Reader(tagger);
// //             Reader.OptimalSignificance();
// //             break;
// //         }
// //         default:
// //             std::cout << "Unhandled case" << std::endl;
// //         }
//     }
}


int main()
{
    analysis::BottomTagger bottom_tagger;
    RunTagger(bottom_tagger, analysis::Stage::trainer);
    RunTagger(bottom_tagger, analysis::Stage::reader);
    analysis::JetPairTagger jet_pair_tagger;
    RunTagger(jet_pair_tagger, analysis::Stage::trainer);
    RunTagger(jet_pair_tagger, analysis::Stage::reader);
    return 0;
}
