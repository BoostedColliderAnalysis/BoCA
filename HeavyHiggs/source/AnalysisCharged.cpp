# include "AnalysisCharged.hh"

namespace analysis
{

namespace heavyhiggs
{

AnalysisCharged::AnalysisCharged(Tagger &tagger) : Analysis::Analysis(tagger)
{
    Print(Severity::notification, "Constructor");
    this->tagger().set_analysis_name(ProjectName());
}


std::vector<File> AnalysisCharged::Files(const Tag tag)
{
    Print(Severity::notification, "Set File Vector", Name(tag));

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

    std::vector<File> LeptonicFiles = analysis::Join(SignalLeptonicFiles, BackgroundLeptonicFiles);
    std::vector<File> HadronicFiles = analysis::Join(SignalHadronicFiles, BackgroundHadronicFiles);
    std::vector<File> SemiFiles = analysis::Join(SignalSemiFiles, BackgroundSemiFiles);

    std::vector<File> NotLeptonicFiles = analysis::Join(HadronicFiles, SemiFiles);
    std::vector<File> CombinedFiles = analysis::Join(NotLeptonicFiles, LeptonicFiles);


    std::vector<File> NonLeptonicSignalFiles = analysis::Join(SignalLeptonicFiles, SignalSemiFiles);
    std::vector<File> CombinedSignalFiles = analysis::Join(SignalHadronicFiles, NonLeptonicSignalFiles);

    std::vector<File> NewFiles;

    switch (tag) {
    case Tag::signal :
        NewFiles = SignalSemiFiles;
        break;
    case Tag::background :
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

    Strings LeptonicTrees = analysis::Join(SignalLeptonicTrees, BackgroundLeptonicTrees);
    Strings HadronicTrees = analysis::Join(SignalHadronicTree, BackgroundHadronicTrees);
    Strings SemiTrees = analysis::Join(SignalSemiTrees, BackgroundSemiTrees);

    Strings NotLeptonicTrees = analysis::Join(HadronicTrees, SemiTrees);
    Strings CombinedTrees = analysis::Join(NotLeptonicTrees, LeptonicTrees);

}

int AnalysisCharged::PassPreCut(Event &event)
{
    Print(Severity::information, "pass pre cut");
    Jets Particles = event.Partons().GenParticles();
    Jets Quarks = fastjet::sorted_by_pt(RemoveIfNot5Quarks(Particles));
    Quarks = fastjet::sorted_by_pt(RemoveIfAbsMother(Quarks, Id::top));
    if (Quarks.empty()) {
        //       if (Tag == Tag::signal && PreCut() > 0 && !(Tagger == BottomTagger || Tagger == HBottomReader))
        //       if (PreCut() > 0)
        Print(Severity::error, "Not enough bottom quarks", Quarks.size());
        return 0;
    } else if (Quarks.front().pt() < PreCut()) return 0;


    Jets TopQuarks = fastjet::sorted_by_pt(RemoveIfWrongAbsParticle(Particles, Id::top));
    if (TopQuarks.size() != 2) {
        Print(Severity::error, "Not enough top quarks", TopQuarks.size());
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
