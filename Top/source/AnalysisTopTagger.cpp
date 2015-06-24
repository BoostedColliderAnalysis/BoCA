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

}
}
