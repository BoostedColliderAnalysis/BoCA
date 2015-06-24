# include "AnalysisHiggsTagger.hh"

namespace analysis
{

namespace higgstagger
{

Analysis::Analysis(Tagger &tagger) : analysis::Analysis::Analysis(tagger)
{
//   DebugLevel = Object::kDebug;
    Print(kNotification, "Constructor");
    this->tagger().set_analysis_name(ProjectName());
    pre_cuts().SetPtLowerCut(HiggsId, LowerPtCut());
    pre_cuts().SetPtUpperCut(HiggsId, UpperPtCut());
    pre_cuts().SetMassUpperCut(HiggsId, 250);
//     DetectorGeometry detector_geometry;
    //     pre_cuts().SetTrackerMaxEta(HiggsId, detector_geometry.TrackerEtaMax);
}

std::string Analysis::ProcessName(const Process process) const
{
    switch (process) {
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
    case hh:
        return "hh";
    case ww:
        return "ww";
    case zz:
        return "zz";
    default:
        Print(kError, "process name", "unhandled case", process);
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
        Print(kError, "collider name", "unhandled case");
        return "";
    }
}

void Analysis::SetFiles(const Object::Tag tag)
{
    Print(kNotification, "Set File Vector", tag);
    switch (tag) {
    case kSignal :
        NewSignalFile(hh);
        break;
    case kBackground :
        NewBackgroundFile(tthad);
        NewBackgroundFile(zz);
        NewBackgroundFile(ww);
        NewBackgroundFile(bb);
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
    default:
        Print(kError, "name", "unhandled case", process);
        return "";
    }
}


int Analysis::PassPreCut(Event &event)
{
    Print(kInformation, "pass pre cut");

    Jets jets = fastjet::sorted_by_pt(event.Hadrons().Jets());
    if (jets.empty()) return 0;
    if (jets.front().pt() < LowerPtCut()) return 0;

//     Jets leptons = fastjet::sorted_by_pt(event.Leptons().leptons());
//     if (leptons.empty()) return 1;
//     if (leptons.front().pt() < 80) return 1;
//     return 0;

    Jets particles = fastjet::sorted_by_pt(event.Partons().GenParticles());
//     particles = fastjet::sorted_by_pt(copy_if_abs_particle(particles, HiggsId));
//     if (particles.empty()) return 1;
//     if (particles.size() == 1) return 0;
    if ((particles.at(0).pt() > LowerPtCut() && particles.at(0).pt() < UpperPtCut()) && (particles.at(1).pt() > LowerPtCut() &&  particles.at(1).pt() < UpperPtCut())) return 1;

    return 1;
}

}

}
