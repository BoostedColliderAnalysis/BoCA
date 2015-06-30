#include "AnalysisCharged.hh"
#include "Debug.hh"

namespace analysis
{

namespace heavyhiggs
{

AnalysisCharged::AnalysisCharged(Tagger &tagger) : Analysis::Analysis(tagger)
{
    Note("Constructor");
    this->tagger().set_analysis_name(ProjectName());
}


std::vector<File> AnalysisCharged::Files(const Tag tag)
{
    Note("Set File Vector", Name(tag));

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
    Info("pass pre cut");
    Jets Particles = event.Partons().GenParticles();
    Jets Quarks = fastjet::sorted_by_pt(RemoveIfNot5Quarks(Particles));
    Quarks = fastjet::sorted_by_pt(RemoveIfAbsMother(Quarks, Id::top));
    if (Quarks.empty()) {
        //       if (Tag == Tag::signal && PreCut() > 0 && !(Tagger == BottomTagger || Tagger == HBottomReader))
        //       if (PreCut() > 0)
        Error("Not enough bottom quarks", Quarks.size());
        return 0;
    } else if (Quarks.front().pt() < PreCut()) return 0;


    Jets TopQuarks = fastjet::sorted_by_pt(RemoveIfWrongAbsParticle(Particles, Id::top));
    if (TopQuarks.size() != 2) {
        Error("Not enough top quarks", TopQuarks.size());
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
int AnalysisCharged::Mass() const
{
    //     return 400;
//         return 500;
    //     return 600;
//             return 800;
//             return 1000;
//         return 1500;
//         return 2000;
    return 3000;
//             return 4000;
//             return 5000;
//         return 6000;
//             return 7000;
//         return 8000;
    //     return 9000;
//                 return 10000;
//                 return 12000;
//         return 15000;
//        return 20000;
}
int AnalysisCharged::PreCut() const
{
    switch (collider_type()) {
    case LHC :
        switch (Mass()) {
        case 500 :
            return 0;
        case 1000 :
            return 250;
        case 2000 :
            return 250;
        case 3000 :
            return 250;
        default :
            return 0;
        }
    case LE :
        switch (Mass()) {
        case 500 :
            return 0;
        case 1000 :
            return 300;
        case 2000 :
            return 300;
        case 4000 :
            return 1500;
        case 6000 :
            return 2500;
        case 10000 :
            return 2500;
        case 15000 :
            return 2500;
        case 20000 :
            return 2500;
        default :
            return 0;
        }
    default :
        return 0;
    }
//         return 0;
//             return 30;
    //     return 80;
    //     return 150;
//         return 100;
//         return 250;
//         return 300;
//         return 1000;
//         return 1500;
//         return 2000;
//         return 2500;
}
float AnalysisCharged::MissingEt()
{
    switch (collider_type()) {
    case LHC :
        return 30;
    case LE :
        return 60;
    default :
        return 0;
    }
}
float AnalysisCharged::LeptonPt()
{
    switch (collider_type()) {
    case LHC :
        return 50;
    case LE :
        return 100;
    default :
        return 0;
    }
}
int AnalysisCharged::EventNumberMax() const
{
// return 10000000;
//         return 1000000;
//                 return 100000;
    return 10000;
//                 return 1000;
//         return 500;
//         return 100;
}
AnalysisCharged::ColliderType AnalysisCharged::collider_type() const
{
    return LHC;
    //       return FHC;
    // return LE;
}
int AnalysisCharged::BackgroundFileNumber() const
{
    switch (collider_type()) {
    case LHC :
        switch (PreCut()) {
        case 0 :
//                 return 1;
            return 79; // < should be switched on
        case 250 :
            return 58; // < should be switched on
        default :
            return 1;
        }
    case LE :
        switch (PreCut()) {
        case 2500 :
            return 28;
        case 2000 :
            return 16;
        case 1500 :
            return 19;
        case 300 :
            return 61; // < should be switched on
//                 return 1;
        case 0 :
            return 118; // < should be switched on
//                 return 1;
        default :
            return 1;
        }
    default :
        return 1;
    }
}
float AnalysisCharged::SignalCrosssection() const
{
    switch (collider_type()) {
    case LHC:
        switch (Mass()) {
        case 500:
            return 3.0495761279999996;
        case 1000:
            return 0.22623192864;
        case 2000:
            return 0.005720855039999999;
        case 3000:
            return 0.0003035467008;
        case 4000:
            return 0.000020556093312;
        default:
            Error("Signal Crosssection", "unhandled case");
            return 1;
        } ;
    case FHC:
    case LE:
        switch (Mass()) {
        case 500:
            return 247.86995327999998;
        case 700:
            return 109.26120959999999;
        case 1000:
            return 39.81212064;
        case 1500:
            return 10.639675008;
        case 2000:
            return 3.8189750399999998;
        case 3000:
            return 0.7737415487999998;
        case 4000:
            return 0.22421177856;
        case 5000:
            return 0.07985005056;
        case 6000:
            return 0.03297554496;
        case 8000:
            return 0.007364981375999998;
        case 10000:
            return 0.0020553163775999996;
        case 12000:
            return 0.0006632091647999999;
        case 15000:
            return 0.00014951794176;
        case 20000:
            return 0.000016388469792;
        default:
            Error("Signal Crosssection", "unhandled case");
            return 1;
        }
    default:
        Error("Signal Crosssection", "unhandled case");
        return 1;
    }
}
File AnalysisCharged::BackgroundFile(const AnalysisCharged::HProcessType Background) const
{
    return BackgroundFile(Background, BackgroundFileNumber());
}
File AnalysisCharged::BackgroundFile(const AnalysisCharged::HProcessType Background, const int FileSum) const
{
    std::string FileName = ProcessName(Background) + "-" + ColliderName(collider_type()) + "-" + std::to_string(PreCut()) + "GeV";
    Strings FileNames;
    for (int FileNumber = 0; FileNumber < FileSum; ++FileNumber) {
        FileNames.emplace_back(FileName + "_" + std::to_string(FileNumber));
    }
    return File(FileNames , BackgroundCrosssection(Background));
}
std::string AnalysisCharged::BackgroundTree(const AnalysisCharged::HProcessType Background) const
{
    return ProcessName(Background) + "-" + ColliderName(collider_type()) + "-" + std::to_string(PreCut()) + "GeV_0-run_01";
}
float AnalysisCharged::BackgroundCrosssection(const AnalysisCharged::HProcessType Process) const
{
    switch (collider_type()) {
    case LHC :
        switch (PreCut()) {
        case 0 :
            switch (Process) {
            case tt :
                return 97.54 * 2 * 1000;
            default :
                Error("unhandled case");
            };
        case 30 :
            switch (Process) {
            case ttbb :
                return 298.2;
            case ttcc:
                return 264.6;
            case ttjj:
                return 9999999999;
            default :
                Error("unhandled case");
            };
        case 80 :
            switch (Process) {
            case ttbb :
                return 89.32;
            case ttcc:
                return 78.42;
            case ttjj:
                return 9999999999;
            default :
                Error("unhandled case");
                return 1;
            }
        case 250 :
            switch (Process) {
            case tt :
                return 4.206 * 2 * 1000;
            default :
                Error("unhandled case");
                return 1;
            }
        }
    case FHC:
        switch (PreCut()) {
        case 30 :
            switch (Process) {
            case ttbb :
                return 2990;
            case ttcc:
                return 2684;
            case ttjj:
                return 9999999999;
            default :
                Error("unhandled case");
                return 1;
            }
        case 80 :
            switch (Process) {
            case ttbb :
                return 1171.6;
            case ttcc:
                return 1042.0;
            case ttjj:
                return 9999999999;
            default :
                Error("unhandled case");
                return 1;
            }
        case 150 :
            switch (Process) {
            case ttbb :
                return 605.199003171 * 2;
            case ttcc:
                return 468.061778817 * 2;
            case ttjj:
                return 61.9287096863 * 2 * 1000;
            default :
                Error("unhandled case");
                return 1;
            }
        case 300 :
            switch (Process) {
            case ttbb :
                return 242;
            case ttcc:
                return 176;
            case ttjj:
                return 26000;
            default :
                Error("unhandled case");
                return 1;
            }
        }
    case LE: {
        switch (Process) {
        case tt:
            switch (PreCut()) {
            case 0 :
                return 3564 * 2 * 1000;
            case 300 :
                return 187.3 * 2 * 1000;
            case 1500 :
                return 0.447 * 2 * 1000;
            case 2500 :
                return 0.0442 * 2 * 1000;
            }
        case ttbb :
            switch (PreCut()) {
            case 300 :
                return 263;
            }
        case ttcc:
            switch (PreCut()) {
            case 300 :
                return 192.82;
            }
        case ttjj:
            switch (PreCut()) {
            case 300 :
                return 28200;
            }
        default :
            Error("unhandled case");
            return 1;
        }
    }
    default :
        Error("unhandled case");
        return 1;
    }
}
std::string AnalysisCharged::ColliderName(const AnalysisCharged::ColliderType Collider) const
{
    switch (Collider) {
    case LHC :
        return "14TeV";
    case FHC:
        return "100TeV";
    case LE:
        return "LE";
    default :
        Error("unhandled case");
        return "";
    }
}
std::string AnalysisCharged::ProcessName(const AnalysisCharged::HProcessType Process) const
{
    switch (Process) {
    case Htb:
//             return "H+tb-bbbbjjlnu";
        return "H+tb-ljbbbb";
    case ttbb :
        return "ttbb-ljbbbb";
    case ttcc:
        return "ttcc-ljbbcc";
    case ttjj:
        return "ttjj-ljbbjj";
    case tt:
        return "tt_inc+";
    default :
        Error("unhandled case");
        return "";
    }
}
std::string AnalysisCharged::ProjectName() const
{
    return  ProcessName() + "-" + ColliderName(collider_type()) + "-" + std::to_string(PreCut()) + "GeV-" + std::to_string(Mass()) + "GeV";
}

}

}
