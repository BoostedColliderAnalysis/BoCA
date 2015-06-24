# include "AnalysisTopTagger.hh"

namespace analysis
{

namespace top
{

Analysis::Analysis(Tagger &tagger) : analysis::Analysis::Analysis(tagger)
{
//   DebugLevel = Object::kDebug;
    Print(kNotification, "Constructor");
    this->tagger().set_analysis_name(ProjectName());
    pre_cuts().SetPtLowerCut(TopId, LowerPtCut());
    pre_cuts().SetPtUpperCut(TopId, UpperPtCut());
    pre_cuts().SetMassUpperCut(TopId, 400);
    pre_cuts().SetTrackerMaxEta(TopId, DetectorGeometry().TrackerEtaMax);
    pre_cuts().SetPtLowerCut(BottomId, LowerPtCut() / 5);
    pre_cuts().SetPtLowerCut(WId, LowerPtCut() / 5);
}

std::string Analysis::ProcessName(const Process process) const
{
    switch (process) {
    case Hbb:
        return "H0bb-ljbbbb";
    case ttbb :
        return "ttbb-ljbbbb";
    case ttcc:
        return "ttcc-ljbbcc";
    case ttjj:
        return "ttjj-ljbbjj";
    case bbjj:
        return "bbjj";
    case tt:
        switch (TopDecay()) {
        case kHadronic :
            //                 return "tt_hadronic_1TeV";
            return "tt_hadronic";
        case  kLeptonic :
            //                 return "tt_leptonic_1TeV";
            return "tt_leptonic";
        case kSemi :
            return "tt_semi_nopre";
        }
    case ttlep:
        return "tt_leptonic";
    case tthad:
        return "tt_hadronic";
    case bb:
        return "bb";
    case cc:
        return "cc";
    case qq:
        return "qq";
    case gg:
        return "gg";
    case wg:
        return "wgg";
    case wq:
        return "wq";
    case wc:
        return "wc";
    case wcb:
        return "wc_b_pre";
    case wb:
        return "wb_u_pre";
    case wu:
        return "wu_b_pre";
    case wbu:
        return "wbu_nopre";
    case hh:
        return "hh";
    case ww:
        return "ww";
    case zz:
        return "zz";
    default:
        Print(kError, "unhandled case");
        return "";
    }
}

std::string Analysis::ColliderName(const Collider collider) const
{
    switch (collider) {
    case LHC :
        return "14TeV";
    case FHC:
        return "100TeV";
    case LE:
        return "LE";
    default:
        Print(kError, "unhandled case");
        return "";
    }
}

void Analysis::SetFiles(const Object::Tag tag)
{
    Print(kNotification, "Set File Vector", tag);
    switch (tag) {
    case kSignal :
        if (TopDecay() == kHadronic || tagger().tagger_name() == "Bottom") NewSignalFile(tthad);
        if (TopDecay() == kLeptonic || tagger().tagger_name() == "Bottom") NewSignalFile(ttlep);
        if (tagger().tagger_name() == "Bottom") NewSignalFile(hh);
        if (tagger().tagger_name() == "Bottom") NewSignalFile(bb);
        if (tagger().tagger_name() == "WHadronic") NewSignalFile(ww);
        break;
    case kBackground :
        if (TopDecay() == kHadronic && tagger().tagger_name() != "Bottom") NewBackgroundFile(ttlep);
        if (TopDecay() == kLeptonic && tagger().tagger_name() != "Bottom") NewBackgroundFile(tthad);
        if (tagger().tagger_name() != "Bottom") NewBackgroundFile(hh);
        NewBackgroundFile(zz);
        if (tagger().tagger_name() != "WHadronic") NewBackgroundFile(ww);
        if (tagger().tagger_name() != "Bottom") NewBackgroundFile(bb);
        NewBackgroundFile(cc);
        NewBackgroundFile(qq);
        NewBackgroundFile(gg);
        break;
    }

}

std::string Analysis::NiceName(const Process process) const
{
    switch (process) {
    case bb:
        return "b";
    case cc:
        return "c";
    case qq:
        return "q";
    case gg:
        return "g";
    case hh:
        return "h";
    case ww:
        return "W";
    case zz:
        return "Z";
    case tthad:
        return "t_{had}";
    case ttlep:
        return "t_{lep}";
    default:
        Print(kError, "name", "unhandled case", process);
        return "";
    }
}


int Analysis::PassPreCut(Event &event)
{
    Print(kInformation, "pass pre cut");
    Jets particles = fastjet::sorted_by_pt(event.Partons().GenParticles());
//     particles = fastjet::sorted_by_pt(copy_if_abs_particle(particles, TopId));
//     if (particles.empty()) return 1;
//     if (particles.size() == 1) Print(kError, "just one top");
    if ((particles.at(0).pt() > LowerQuarkCut() && particles.at(0).pt() < UpperQuarkCut()) && (particles.at(1).pt() > LowerQuarkCut() &&  particles.at(1).pt() < UpperQuarkCut())) return 1;
    return 0;
}
std::string Analysis::ProjectName() const
{
    return  "TopTagger-" + ColliderName(collider_type()) + "-" + std::to_string(LowerPtCut()) + "GeV-" + ProcessName(tt) + "-1-sj";
}
top::Analysis::Decay Analysis::TopDecay() const
{
    return kHadronic;
//         return kLeptonic;
//         return kSemi;
}
std::string Analysis::FilePath() const
{
    return "~/Projects/Tagger/";
}
std::string Analysis::NameSpaceName() const
{
    return "top";
}
void Analysis::NewSignalFile(const top::Analysis::Process process)
{
    analysis::Analysis::NewSignalFile(FileName(process), NiceName(process));
}
void Analysis::NewBackgroundFile(const top::Analysis::Process process)
{
    analysis::Analysis::NewBackgroundFile(FileName(process), NiceName(process));
}
std::string Analysis::FileName(const top::Analysis::Process process) const
{
    return ProcessName(process) + "_" + std::to_string(MadGraphCut()) + "GeV";
}
int Analysis::LowerPtCut() const
{
//         return 350;
//         return 700;
//         return 800;
    return 1000;
}
int Analysis::UpperPtCut() const
{
    switch (LowerPtCut()) {
    case 700 :
        return 1000;
    case 1000 :
        return 1500;
    }
}
int Analysis::MadGraphCut() const
{
    switch (LowerPtCut()) {
    case 700 :
        return 700;
    case 1000 :
        return 1000;
    }
}
int Analysis::LowerQuarkCut() const
{
    return LowerPtCut() * 0.9;
}
int Analysis::UpperQuarkCut() const
{
    return UpperPtCut() * 1.1;
}
int Analysis::EventNumberMax() const
{
    //         return 1000000;
    //         return 100000;
//         return 10000;
    return 5000;
//         return 1000;
//         return 100;
//         return 10;
}
top::Analysis::Collider Analysis::collider_type() const
{
    //       return LHC;
    //       return FHC;
    return LE;
}
int Analysis::BackgroundFileNumber() const
{
    return 1;
    //         return 2;
    //       return 4;
    //       return 5;
    //       return 10;
}
File Analysis::BackgroundFile(const top::Analysis::Process process) const
{
    return BackgroundFile(process, BackgroundFileNumber());
}
File Analysis::BackgroundFile(const top::Analysis::Process process, const int file_sum) const
{
    Strings FileNames;
    for (int file_number = 0; file_number < file_sum; ++file_number) {
        FileNames.emplace_back(FileName(process));
    }
    return File(FileNames);
}
std::string Analysis::BackgroundTree(const top::Analysis::Process Process) const
{
    return ProcessName(Process) + "_" + std::to_string(LowerPtCut()) + "GeV" + "-run_01";
}

}
}
