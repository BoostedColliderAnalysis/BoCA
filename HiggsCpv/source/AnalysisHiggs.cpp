# include "AnalysisHiggs.hh"

higgscpv::Analysis::Analysis(analysis::Tagger &tagger) : analysis::Analysis::Analysis(tagger){
  Print(kNotification, "Constructor");
  tagger_.set_analysis_name(ProjectName());
}

std::string higgscpv::Analysis::ProcessName(){
  return "higgscpv";
}

void higgscpv::Analysis::SetFiles(const Tag tag)
{
    Print(kNotification, "Set Files");
    NewBackgroundFile("pp-bbtt-bblvlv");
    NewSignalFile("pp-x0tt-bblvlv-even");
    NewSignalFile("pp-x0tt-bblvlv-mix");
    NewSignalFile("pp-x0tt-bblvlv-odd");
}

int higgscpv::Analysis::PassPreCut(analysis::Event &event)
{
  Print(kInformation, "pass pre cut");
  analysis::Jets particles = event.Partons().GenParticles();
  analysis::Jets tops = fastjet::sorted_by_pt(copy_if_abs_particle(particles, TopId));
//   analysis::remove_if_not_in_pt_window(tops, PreCut(), UpperCut());
  return tops.size();
}

int higgscpv::Analysis::RunAnalysis(analysis::Event &event, const analysis::Tagger::Stage stage, const analysis::Object::Tag tag)
{
  Print(kInformation, "Analysis");
  switch (stage) {
    case analysis::Tagger::kTrainer :
      return tagger_.Train(event, pre_cuts_, tag);
    case analysis::Tagger::kReader :
      return reader_.GetBdt(event, pre_cuts_);
    default : return 0;
  }
}
