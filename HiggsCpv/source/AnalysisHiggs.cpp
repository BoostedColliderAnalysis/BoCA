# include "AnalysisHiggs.hh"

namespace higgscpv {

Analysis::Analysis(analysis::Tagger &tagger) : analysis::Analysis::Analysis(tagger)
{
    Print(kNotification, "Constructor");
    tagger_.set_analysis_name(ProjectName());
}

std::string Analysis::ProcessName()
{
    return "higgscpv";
}

void Analysis::SetFiles(const Tag tag)
{
    Print(kNotification, "Set Files");
    switch (tag) {
    case kSignal :
        NewSignalFile("pp-ttx0-bbbbllnunu-1");
        NewSignalFile("pp-ttx0-bbbbllnunu-0");
        NewSignalFile("pp-ttx0-bbbbllnunu-0.5");
        break;
    case kBackground :
        NewBackgroundFile("pp-ttbb-bbbbllnunu");
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

int Analysis::RunAnalysis(analysis::Event &event, const analysis::Tagger::Stage stage, const analysis::Object::Tag tag)
{
    Print(kInformation, "Analysis");
    switch (stage) {
    case analysis::Tagger::kTrainer :
        return tagger_.Train(event, pre_cuts_, tag);
    case analysis::Tagger::kReader :
        return reader_.GetBdt(event, pre_cuts_);
    default :
        return 0;
    }
}

}
