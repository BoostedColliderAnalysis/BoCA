#include "AnalysisHiggs.hh"
#include "Debug.hh"

namespace analysis
{

namespace higgscpv
{

Analysis::Analysis(Tagger &tagger) //: analysis::Analysis::Analysis(tagger)
{
    Note();
    //this->tagger().set_analysis_name(ProjectName());
}

std::string Analysis::ProcessName()
{
    return "higgscpv";
}

void Analysis::SetFiles(const Tag tag)
{
    Note("Set Files");
    switch (tag) {
    case Tag::signal :
//         NewSignalFile("pp-ttx0-bbbbllnunu-1", 0.02071);
//         NewSignalFile("pp-ttx0-bbbbllnunu-0", 0.008937);
//         NewSignalFile("pp-ttx0-bbbbllnunu-0.5", 0.01193);
        break;
    case Tag::background :
//         NewBackgroundFile("pp-ttbb-bbbbllnunu", 3.457);
        break;
    }
}

int Analysis::PassPreCut(const Event &event)
{
    Info("pass pre cut");
//   Jets particles = event.Partons().GenParticles();
//   Jets tops = fastjet::sorted_by_pt(CopyIfAbsParticle(particles, Id::top));
//   remove_if_not_in_pt_window(tops, PreCut(), UpperCut());
    return 1;
}

}

}
