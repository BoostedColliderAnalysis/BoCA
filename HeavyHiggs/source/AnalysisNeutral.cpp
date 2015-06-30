#include "AnalysisNeutral.hh"
#include "Debug.hh"

namespace analysis
{

namespace heavyhiggs
{

AnalysisNeutral::AnalysisNeutral(Tagger &tagger) : Analysis::Analysis(tagger)
{
    Note("Constructor");
    this->tagger().set_analysis_name(ProjectName());
}

std::vector<File> AnalysisNeutral::Files(const Tag tag)
{
    Note("Set File Vector", Name(tag));

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

    std::vector<File> LeptonicFiles = analysis::Join(SignalLeptonicFiles, BackgroundLeptonicFiles);
    std::vector<File> HadronicFiles = analysis::Join(SignalHadronicFiles, BackgroundHadronicFiles);
    std::vector<File> SemiFiles = analysis::Join(SignalSemiFiles, BackgroundSemiFiles);

    std::vector<File> NotLeptonicFiles = analysis::Join(HadronicFiles, SemiFiles);
    std::vector<File> CombinedFiles = analysis::Join(NotLeptonicFiles, LeptonicFiles);

    std::vector<File> NonLeptonicSignalFiles = analysis::Join(SignalLeptonicFiles, SignalSemiFiles);
    std::vector<File> CombinedSignalFiles = analysis::Join(SignalHadronicFiles, NonLeptonicSignalFiles);

    std::vector<File> NewFiles;

    switch (tag) {
      case analysis::Tag::signal :
        NewFiles = SignalSemiFiles;
        break;
    case analysis::Tag::background :
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

    Strings LeptonicTrees = analysis::Join(SignalLeptonicTrees, BackgroundLeptonicTrees);
    Strings HadronicTrees = analysis::Join(SignalHadronicTree, BackgroundHadronicTrees);
    Strings SemiTrees = analysis::Join(SignalSemiTrees, BackgroundSemiTrees);

    Strings NotLeptonicTrees = analysis::Join(HadronicTrees, SemiTrees);
    Strings CombinedTrees = analysis::Join(NotLeptonicTrees, LeptonicTrees);

}

int AnalysisNeutral::PassPreCut(Event &event)
{
    Info("pass pre cut");
    Jets Particles = event.Partons().GenParticles();
    Jets Tops = RemoveIfWrongAbsParticle(Particles, Id::top);
    if (Tops.size() != 2) {
        Error("Not enough top quarks", Tops.size());
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
std::string AnalysisNeutral::ColliderName(const AnalysisNeutral::ColliderType Collider) const
{
    switch (Collider) {
    case LHC :
        return "14TeV";
    case FHC:
        return "100TeV";
    case LE:
        return "LE";
    default:
        Error("unhandled case");
        return "";
    }
}
std::string AnalysisNeutral::ProcessName(const AnalysisNeutral::ProcessType Process) const
{
    switch (Process) {
    case Hbb:
        return "H0bb-ljbbbb";
    case ttbb :
        return "ttbb-ljbbbb";
    case ttcc:
        return "ttcc-ljbbcc";
    case ttjj:
        return "ttjj-ljbbjj";
    case tt:
        return "tt_inc";
    default:
        Error("unhandled case");
        return "";
    }
}
float AnalysisNeutral::BackgroundCrosssection(const AnalysisNeutral::ProcessType Process) const
{
    switch (collider_type()) {
    case LHC :
        switch (PreCut()) {
        case 0 :
            switch (Process) {
            case tt :
                return 97.54 * 2 * 1000;
            default:
                Error("Background Crosssection", "unhandled case");
                return 1;
            };
        case 30 :
            switch (Process) {
            case ttbb :
                return 298.2;
            case ttcc:
                return 264.6;
            case ttjj:
                return 9999999999;
            default:
                Error("Background Crosssection", "unhandled case");
                return 1;
            };
        case 80 :
            switch (Process) {
            case ttbb :
                return 89.32;
            case ttcc:
                return 78.42;
            case ttjj:
                return 9999999999;
            default:
                Error("Background Crosssection", "unhandled case");
                return 1;
            }
        case 250 :
            switch (Process) {
            case tt :
                return 5.698 * 2 * 1000;
            default :
                Error("Background Crosssection", "unhandled case");
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
            default:
                Error("Background Crosssection", "unhandled case");
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
            default:
                Error("Background Crosssection", "unhandled case");
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
            default:
                Error("Background Crosssection", "unhandled case");
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
            default:
                Error("Background Crosssection", "unhandled case");
                return 1;
            }
        }
    case LE:
        switch (PreCut()) {
        case 0 :
            switch (Process) {
            case tt :
                return 3564 * 2 * 1000;
            default:
                Error("Background Crosssection", "unhandled case");
                return 1;
            }
        case 150 :
            switch (Process) {
            case ttbb :
                return 688;
            case ttcc:
                return 534;
            case ttjj:
                return 70289;
            default:
                Error("Background Crosssection", "unhandled case");
                return 1;
            }
        case 300 :
            switch (Process) {
            case ttbb :
                return 263;
            case ttcc:
                return 192.82;
            case ttjj:
                return 28200;
            case tt :
                return 178.1 * 2 * 1000;
            default:
                Error("Background Crosssection", "unhandled case");
                return 1;
            }
        case 1000 :
            switch (Process) {
            case tt :
                return 1.532 * 2 * 1000;
            default:
                Error("Background Crosssection", "unhandled case");
                return 1;
            }
        case 1500 :
            switch (Process) {
            case tt :
                return 0.2524 * 2 * 1000;
            default:
                Error("Background Crosssection", "unhandled case");
                return 1;
            }
        case 2000 :
            switch (Process) {
            case tt :
                return 0.09014 * 2 * 1000;
            default:
                Error("Background Crosssection", "unhandled case");
                return 1;
            }
        case 2500 :
            switch (Process) {
            case tt :
                return 0.0222 * 2 * 1000;
            default:
                Error("Background Crosssection", "unhandled case");
                return 1;
            }
        }
    default:
        Error("Background Crosssection",  "unhandled case");
        return 1;
    }
}
std::string AnalysisNeutral::BackgroundTree(const AnalysisNeutral::ProcessType Process) const
{
    return ProcessName(Process) + "-" + ColliderName(collider_type()) + "-" + std::to_string(PreCut()) + "GeV_0-run_01";
}
File AnalysisNeutral::BackgroundFile(const AnalysisNeutral::ProcessType Background, const int FileSum) const
{
    std::string FileName = ProcessName(Background) + "-" + ColliderName(collider_type()) + "-" + std::to_string(PreCut()) + "GeV";
    Strings FileNames;
    for (int FileNumber = 0; FileNumber < FileSum; ++FileNumber) {
        FileNames.emplace_back(FileName + "_" + std::to_string(FileNumber));
    }
    return File(FileNames , BackgroundCrosssection(Background));
}
File AnalysisNeutral::BackgroundFile(const AnalysisNeutral::ProcessType Background) const
{
    return BackgroundFile(Background, BackgroundFileNumber());
}
float AnalysisNeutral::SignalCrosssection() const
{
    switch (collider_type()) {
    case LHC:
        switch (Mass()) {
        case 500:
            return 25.528929726502543;
        case 1000:
            return 1.2783507034600217;
        case 2000:
            return 0.021907574118663196;
        default:
            Error("Signal Crosssection", "unhandled case");
            return 1;
        } ;
    case FHC:
    case LE:
        switch (Mass()) {
        case 500:
            return 973.5805772514352;
        case 1000:
            return 123.02005671222373;
        case 1500:
            return 28.624904980998327;
        case 2000:
            return 9.485582085140349;
        case 3000:
            return 1.7540841248835577;
        case 4000:
            return 0.4851939478031553;
        case 5000:
            return 0.16696738296715652;
        case 6000:
            return 0.06731697180862359;
        case 7000:
            return 0.029372932414373627;
        case 8000:
            return 0.014255221936825225;
        case 10000:
            return 0.0038428602375120795;
        case 12000:
            return 0.0012219523755405267;
        case 15000:
            return 0.00026507004708327343;
        case 20000:
            return 0.000028218388829563033;
        default:
            Error("Signal Crosssection", "unhandled case");
            return 1;
        }
    default:
        Error("Signal Crosssection", "unhandled case");
        return 1;
    }
}
int AnalysisNeutral::BackgroundFileNumber() const
{
    switch (collider_type()) {
    case LHC :
        switch (PreCut()) {
        case  0 :
            return 127;
        case  250 :
            return 41;
            //                 return 1; // < this must be removed !!
        default :
            return 1;
        }
    case LE :
        switch (PreCut()) {
        case  0 :
            return 118;
//                 return 1; // < this must be removed !!
        case  100 :
            return 15;
        case  250 :
            return 15;
        case  300 :
            return 110;
//                 return 1; // < this must be removed !!
        case  1000 :
            return 32;
        case  1500 :
            return 34;
        case  2000 :
            return 26;
        case  2500 :
            return 11;
        default :
            return 1;
        }
    default :
        return 1;
    }
}
float AnalysisNeutral::MissingEt()
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
float AnalysisNeutral::LeptonPt()
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
int AnalysisNeutral::PreCut() const
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
    //     return 30;
    //     return 80;
// return 100;
    //     return 150;
//         return 250;
//              return 300;
//            return 1000;
//         return 1500;
//        return 2000;
//         return 2500;
}
int AnalysisNeutral::Mass() const
{
    //     return 300;
    //     return 400;
//         return 500;
    //     return 600;
    //     return 700;
//             return 800;
    //     return 900;
//         return 1000;
    return 2000;
//            return 3000;
//         return 4000;
//                 return 5000;
//                return 6000;
//             return 7000;
//         return 8000;
//             return 9000;
//                 return 10000;
//                 return 12000;
//                 return 15000;
//                return 20000;
}

}

}
