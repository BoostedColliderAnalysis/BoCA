# include "AnalysisTopPartner.hh"

namespace analysis {

namespace toppartner
{

Analysis::Analysis(Tagger &tagger) : analysis::Analysis::Analysis(tagger)
{
    Print(kNotification, "Constructor");
    this->tagger().set_analysis_name(ProjectName());
}

std::string Analysis::ProcessName()
{
    return "toppartner";
}

void Analysis::SetFiles(const Tag tag)
{
    Print(kNotification, "Set Files");
    switch (tag) {
    case kSignal :
      NewSignalFile("pp-Tth-bbbbjjjjlv");
//         NewSignalFile("pp-ttx0-bbbbllnunu-0", 0.008937);
//         NewSignalFile("pp-ttx0-bbbbllnunu-0.5", 0.01193);
        break;
    case kBackground :
      NewBackgroundFile("pp-Tth-bbbbjjjjlv");
        break;
    }
}

int Analysis::PassPreCut(Event &event)
{
    Print(kInformation, "pass pre cut");
//   Jets particles = event.Partons().GenParticles();
//   Jets tops = fastjet::sorted_by_pt(copy_if_abs_particle(particles, TopId));
//   remove_if_not_in_pt_window(tops, PreCut(), UpperCut());
    return 1;
}

}

}
