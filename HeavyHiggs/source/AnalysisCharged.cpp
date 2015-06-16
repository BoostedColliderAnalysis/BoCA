# include "AnalysisCharged.hh"

namespace analysis
{

namespace heavyhiggs
{

AnalysisCharged::AnalysisCharged(Tagger &tagger) : Analysis::Analysis(tagger)
{
    Print(kNotification, "Constructor");
    tagger_.set_analysis_name(ProjectName());
}


std::vector<File> AnalysisCharged::Files(const Object::Tag tag)
{
    Print(kNotification, "Set File Vector", tag);

    std::vector<File> SignalLeptonicFiles;

    std::vector<File> BackgroundLeptonicFiles;

    std::vector<File> SignalSemiFiles;
    std::vector<File> BackgroundSemiFiles;

    std::string SignalName = ProcessName(Htb) + "-" + ColliderName(collider_type()) + "-" + std::to_string(Mass()) + "GeV";
    SignalSemiFiles.emplace_back(File(SignalName, SignalCrosssection(), Mass()));

//     BackgroundSemiFiles.emplace_back(BackgroundFile(ttbb));
//     BackgroundSemiFiles.emplace_back(BackgroundFile(ttcc));
//     BackgroundSemiFiles.emplace_back(BackgroundFile(ttjj));
    BackgroundSemiFiles.emplace_back(BackgroundFile(tt));

    std::vector<File> SignalHadronicFiles;

    std::vector<File> BackgroundHadronicFiles;

    std::vector<File> LeptonicFiles = JoinFiles(SignalLeptonicFiles, BackgroundLeptonicFiles);
    std::vector<File> HadronicFiles = JoinFiles(SignalHadronicFiles, BackgroundHadronicFiles);
    std::vector<File> SemiFiles = JoinFiles(SignalSemiFiles, BackgroundSemiFiles);

    std::vector<File> NotLeptonicFiles = JoinFiles(HadronicFiles, SemiFiles);
    std::vector<File> CombinedFiles = JoinFiles(NotLeptonicFiles, LeptonicFiles);


    std::vector<File> NonLeptonicSignalFiles = JoinFiles(SignalLeptonicFiles, SignalSemiFiles);
    std::vector<File> CombinedSignalFiles = JoinFiles(SignalHadronicFiles, NonLeptonicSignalFiles);

    std::vector<File> NewFiles;

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

void AnalysisCharged::SetTrees()
{

    Strings SignalLeptonicTrees {};
    Strings BackgroundLeptonicTrees {};

    std::string SignalTree = ProcessName(Htb) + "-" + ColliderName(collider_type()) + "-" + std::to_string(Mass()) + "GeV-run_01";

    Strings SignalSemiTrees {SignalTree};

    Strings BackgroundSemiTrees {
//       BackgroundTree(ttbb),
//       BackgroundTree(ttcc),
//       BackgroundTree(ttjj)
        BackgroundTree(tt)
    };

    Strings SignalHadronicTree {};
    Strings BackgroundHadronicTrees {};

    Strings LeptonicTrees = JoinStrings(SignalLeptonicTrees, BackgroundLeptonicTrees);
    Strings HadronicTrees = JoinStrings(SignalHadronicTree, BackgroundHadronicTrees);
    Strings SemiTrees = JoinStrings(SignalSemiTrees, BackgroundSemiTrees);

    Strings NotLeptonicTrees = JoinStrings(HadronicTrees, SemiTrees);
    Strings CombinedTrees = JoinStrings(NotLeptonicTrees, LeptonicTrees);

}

int AnalysisCharged::PassPreCut(Event &event)
{
    Print(kInformation, "pass pre cut");
    Jets Particles = event.Partons().GenParticles();
    Jets Quarks = fastjet::sorted_by_pt(RemoveIfNot5Quarks(Particles));
    Quarks = fastjet::sorted_by_pt(RemoveIfAbsMother(Quarks, TopId));
    if (Quarks.empty()) {
        //       if (Tag == kSignal && PreCut() > 0 && !(Tagger == BottomTagger || Tagger == HBottomReader))
        //       if (PreCut() > 0)
        Print(kError, "Not enough bottom quarks", Quarks.size());
        return 0;
    } else if (Quarks.front().pt() < PreCut()) return 0;


    Jets TopQuarks = fastjet::sorted_by_pt(RemoveIfWrongAbsParticle(Particles, TopId));
    if (TopQuarks.size() != 2) {
        Print(kError, "Not enough top quarks", TopQuarks.size());
        return 0;
    } else if (TopQuarks.front().pt() < PreCut()) return 0;


    if (event.Hadrons().MissingEt().pt() < MissingEt()) return 0;
    Jets Leptons = fastjet::sorted_by_pt(event.Leptons().leptons());
    if (Leptons.empty()) return 0;
    if (Leptons.front().pt() < LeptonPt()) return 0;
    Jets jets = event.Hadrons().Jets();
    if (jets.size() < 4) return 0;
    return 1;
}

}

}
