# include "AnalysisNeutral.hh"

namespace analysis
{

namespace heavyhiggs
{

AnalysisNeutral::AnalysisNeutral(Tagger &tagger) : Analysis::Analysis(tagger)
{
    Print(kNotification, "Constructor");
    tagger_.set_analysis_name(ProjectName());
}

std::vector<File> AnalysisNeutral::Files(const Object::Tag tag)
{
    Print(kNotification, "Set File Vector", tag);

    std::vector<File> SignalLeptonicFiles;
    std::vector<File> BackgroundLeptonicFiles;
    std::vector<File> SignalSemiFiles;
    std::vector<File> BackgroundSemiFiles;

    std::string SignalName = ProcessName(Hbb) + "-" + ColliderName(collider_type()) + "-" + std::to_string(Mass()) + "GeV";
    SignalSemiFiles.emplace_back(File(SignalName, SignalCrosssection(), Mass()));
//     SignalSemiFiles.emplace_back(BackgroundFile(ttbb));

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
    return NewFiles;

}


void AnalysisNeutral::SetTrees()
{

    Strings SignalLeptonicTrees {};
    Strings BackgroundLeptonicTrees {};

    std::string SignalTree = ProcessName(Hbb) + "-" + ColliderName(collider_type()) + "-" + std::to_string(Mass()) + "GeV-run_01";

    Strings SignalSemiTrees {
        SignalTree
//         BackgroundTree(ttbb)
    };

    Strings BackgroundSemiTrees {
//         BackgroundTree(ttbb),
//         BackgroundTree(ttcc),
//         BackgroundTree(ttjj)
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

int AnalysisNeutral::PassPreCut(Event &event)
{
    Print(kInformation, "pass pre cut");
    Jets Particles = event.Partons().GenParticles();
    Jets Tops = RemoveIfWrongAbsParticle(Particles, TopId);
    if (Tops.size() != 2) {
        Print(kError, "Not enough top quarks", Tops.size());
        return 0;
    } else {
        if (Tops.at(0).pt() < PreCut()) return 0;
        if (Tops.at(1).pt() < PreCut()) return 0;
    }

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
