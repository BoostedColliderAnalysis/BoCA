# include "AnalysisTopPartner.hh"

namespace toppartner
{

Analysis::Analysis(analysis::Tagger &tagger) : analysis::Analysis::Analysis(tagger)
{
    Print(kNotification, "Constructor");
    tagger_.set_analysis_name(ProjectName());
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
        NewSignalFile("pp-ttx0-bbbbllnunu-1", 0.02071);
//         NewSignalFile("pp-ttx0-bbbbllnunu-0", 0.008937);
//         NewSignalFile("pp-ttx0-bbbbllnunu-0.5", 0.01193);
        break;
    case kBackground :
        NewBackgroundFile("pp-ttbb-bbbbllnunu", 3.457);
        break;
    }
}

int Analysis::PassPreCut(analysis::Event &event)
{
    Print(kInformation, "pass pre cut");
//   analysis::Jets particles = event.Partons().GenParticles();
//   analysis::Jets tops = fastjet::sorted_by_pt(copy_if_abs_particle(particles, TopId));
//   analysis::remove_if_not_in_pt_window(tops, PreCut(), UpperCut());
    return 1;
}

}
