#include "AnalysisTopPartner.hh"
#include "Debug.hh"

namespace analysis
{

namespace toppartner
{

// Analysis::Analysis(Tagger &tagger) : analysis::Analysis::Analysis(tagger)
// {
//     Note();
//     this->tagger().set_analysis_name(ProjectName());
// }
//
// std::string Analysis::ProcessName()
// {
//     return "toppartner";
// }
//
// std::string Analysis::ProjectName() const
// {
//     return  "TopPartner_" + std::to_string(PreCut()) + "GeV";
// }
//
// int toppartner::Analysis::PreCut() const
// {
//     return 100;
// }
//
//
// void Analysis::SetFiles(const Tag tag)
// {
//     Note();
//     switch (tag) {
//     case Tag::signal :
// //         NewFile(tag,"pp-Tth-bbbbjjjjlv");
// //         NewFile(tag,"pp-TThh-bbbbbbjjlv");
//         NewFile(tag, "pp-TT-tthh-bbbbbbjjlv", 0.001971);
// //         if(tagger().name() == "Bottom") NewFile(tag,"pp-ttbbj-bbbbjjlv");
//         break;
//     case Tag::background :
// //         NewFile(tag,"pp-ttbb-bbbbjjlv");
// //       NewFile(tag,"pp-tthjj-bbbbjjjjlv);
//         NewFile(tag, "pp-tthjj-bbbbjjjjlv_" + std::to_string(PreCut()) + "GeV");
// //         NewFile(tag,"tt_inc-LE-0GeV_0");
//         break;
//     }
// }
//
// int Analysis::PassPreCut(const Event &event)
// {
//     Info();
//     Jets particles = event.Partons().GenParticles();
//     particles = RemoveIfSoft(particles, PreCut());
//     Jets tops = copy_if_abs_particle(particles, Id::top);
//     Jets higgs = copy_if_abs_particle(particles, Id::higgs);
//     if (tops.size() < 2 || higgs.size() < 1) return 0;
//     return 1;
// }
//
// int Analysis::EventNumberMax() const
// {
//     return 1000;
// }
//
// std::string Analysis::FilePath() const
// {
//     return "~/Projects/TopPartner/Analysis/";
// }

}

}
