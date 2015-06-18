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
    pre_cuts().SetPtLowerCut(TopId, PreCut());
    pre_cuts().SetPtUpperCut(TopId, UpperCut());
    DetectorGeometry detector_geometry;
    pre_cuts().SetTrackerMaxEta(TopId, detector_geometry.TrackerEtaMax);
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
        if (TopDecay() == kHadronic) NewSignalFile(tthad);
        else if (TopDecay() == kLeptonic) NewSignalFile(ttlep);

        //     NewSignalFile(ttbb);
//     NewSignalFile(ttjj);
//     NewSignalFile(tt);
//     NewSignalFile(bb);
//     NewSignalFile(ttlep);

//   NewBackgroundFile(ttbb);
//   NewBackgroundFile(ttcc);
//   NewBackgroundFile(ttjj);
//     NewBackgroundFile(bbjj);
//     NewBackgroundFile(bb);
//     NewBackgroundFile(hh);

//     NewBackgroundFile(cc);
//         NewBackgroundFile(qq);
//         NewBackgroundFile(gg);
//         NewBackgroundFile(ww);
//         NewBackgroundFile(zz);
        break;
    case kBackground :
        if (TopDecay() == kHadronic) NewBackgroundFile(ttlep);
        else if (TopDecay() == kLeptonic) NewBackgroundFile(tthad);
//     NewBackgroundFile(wb);
//     NewBackgroundFile(wc);
//     NewBackgroundFile(wq);
//     NewBackgroundFile(wg);
//     NewBackgroundFile(wu);
//     NewBackgroundFile(wcb);
//     NewBackgroundFile(wbu);
        break;
    }

}


int Analysis::PassPreCut(Event &event)
{
    Print(kInformation, "pass pre cut");
    Jets particles = event.Partons().GenParticles();
    Jets tops = fastjet::sorted_by_pt(copy_if_abs_particle(particles, TopId));
    remove_if_not_in_pt_window(tops, PreCut(), UpperCut());
    return tops.size();
}

}
}
