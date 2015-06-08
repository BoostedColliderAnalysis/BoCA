# include "AnalysisCharged.hh"

heavyhiggs::AnalysisCharged::AnalysisCharged(analysis::Tagger &tagger) : analysis::Analysis::Analysis(tagger)
{
  Print(kNotification, "Constructor");
  tagger_.set_analysis_name(ProjectName());
}


std::vector<analysis::File> heavyhiggs::AnalysisCharged::Files(const analysis::Object::Tag tag)
{
    Print(kNotification, "Set File Vector", tag);

    std::vector<analysis::File> SignalLeptonicFiles;

    std::vector<analysis::File> BackgroundLeptonicFiles;

    std::vector<analysis::File> SignalSemiFiles;
    std::vector<analysis::File> BackgroundSemiFiles;

    std::string SignalName = ProcessName(Htb) + "-" + ColliderName(collider_type()) + "-" + std::to_string(Mass()) + "GeV";
    SignalSemiFiles.emplace_back(analysis::File(SignalName, SignalCrosssection(), Mass()));

//     BackgroundSemiFiles.emplace_back(BackgroundFile(ttbb));
//     BackgroundSemiFiles.emplace_back(BackgroundFile(ttcc));
//     BackgroundSemiFiles.emplace_back(BackgroundFile(ttjj));
    BackgroundSemiFiles.emplace_back(BackgroundFile(tt));

    std::vector<analysis::File> SignalHadronicFiles;

    std::vector<analysis::File> BackgroundHadronicFiles;

    std::vector<analysis::File> LeptonicFiles = JoinFiles(SignalLeptonicFiles, BackgroundLeptonicFiles);
    std::vector<analysis::File> HadronicFiles = JoinFiles(SignalHadronicFiles, BackgroundHadronicFiles);
    std::vector<analysis::File> SemiFiles = JoinFiles(SignalSemiFiles, BackgroundSemiFiles);

    std::vector<analysis::File> NotLeptonicFiles = JoinFiles(HadronicFiles, SemiFiles);
    std::vector<analysis::File> CombinedFiles = JoinFiles(NotLeptonicFiles, LeptonicFiles);


    std::vector<analysis::File> NonLeptonicSignalFiles = JoinFiles(SignalLeptonicFiles, SignalSemiFiles);
    std::vector<analysis::File> CombinedSignalFiles = JoinFiles(SignalHadronicFiles, NonLeptonicSignalFiles);

    std::vector<analysis::File> NewFiles;

    switch (tag) {
      case Object::kSignal :
        NewFiles = SignalSemiFiles;
        break;
      case Object::kBackground :
        NewFiles = BackgroundSemiFiles;
        break;
    }

    SetTrees();
//     PrepareReader(Tagger, tag);
    return NewFiles;
}

void heavyhiggs::AnalysisCharged::SetTrees()
{

  analysis::Strings SignalLeptonicTrees {};
  analysis::Strings BackgroundLeptonicTrees {};

    std::string SignalTree = ProcessName(Htb) + "-" + ColliderName(collider_type()) + "-" + std::to_string(Mass()) + "GeV-run_01";

    analysis::Strings SignalSemiTrees {SignalTree};

    analysis::Strings BackgroundSemiTrees {
//       BackgroundTree(ttbb),
//       BackgroundTree(ttcc),
//       BackgroundTree(ttjj)
        BackgroundTree(tt)
    };

    analysis::Strings SignalHadronicTree {};
    analysis::Strings BackgroundHadronicTrees {};

    analysis::Strings LeptonicTrees = JoinStrings(SignalLeptonicTrees, BackgroundLeptonicTrees);
    analysis::Strings HadronicTrees = JoinStrings(SignalHadronicTree, BackgroundHadronicTrees);
    analysis::Strings SemiTrees = JoinStrings(SignalSemiTrees, BackgroundSemiTrees);

    analysis::Strings NotLeptonicTrees = JoinStrings(HadronicTrees, SemiTrees);
    analysis::Strings CombinedTrees = JoinStrings(NotLeptonicTrees, LeptonicTrees);

}

int heavyhiggs::AnalysisCharged::PassPreCut(analysis::Event &event)
{
  Print(kInformation, "pass pre cut");
  analysis::Jets Particles = event.partons().GenParticles();
  analysis::Jets Quarks = fastjet::sorted_by_pt(analysis::RemoveIfNot5Quarks(Particles));
  Quarks = fastjet::sorted_by_pt(RemoveIfAbsMother(Quarks, TopId));
  if (Quarks.empty()) {
    //       if (Tag == kSignal && PreCut() > 0 && !(Tagger == BottomTagger || Tagger == HBottomReader))
    //       if (PreCut() > 0)
    Print(kError, "Not enough bottom quarks", Quarks.size());
    return 0;
  } else if (Quarks.front().pt() < PreCut()) return 0;


  analysis::Jets TopQuarks = fastjet::sorted_by_pt(RemoveIfWrongAbsParticle(Particles, TopId));
  if (TopQuarks.size() != 2) {
    Print(kError, "Not enough top quarks", TopQuarks.size());
    return 0;
  } else if (TopQuarks.front().pt() < PreCut()) return 0;


  if (event.hadrons().MissingEt().pt() < MissingEt()) return 0;
  analysis::Jets Leptons = fastjet::sorted_by_pt(event.leptons().leptons());
  if (Leptons.empty()) return 0;
  if (Leptons.front().pt() < LeptonPt()) return 0;
  analysis::Jets jets = event.hadrons().Jets();
  if (jets.size() < 4) return 0;
  return 1;
}
