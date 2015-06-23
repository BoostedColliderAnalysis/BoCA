# include "AnalysisWTagger.hh"

namespace analysis
{

namespace wtagger
{

Analysis::Analysis(Tagger &tagger) : analysis::Analysis::Analysis(tagger)
{
//   DebugLevel = Object::kDebug;
    Print(kNotification, "Constructor");
    this->tagger().set_analysis_name(ProjectName());
    pre_cuts().SetPtLowerCut(WId, LowerPtCut());
    pre_cuts().SetPtUpperCut(WId, UpperPtCut());
    pre_cuts().SetMassUpperCut(WId, 200);
//     DetectorGeometry detector_geometry;
//     pre_cuts().SetTrackerMaxEta(TopId, detector_geometry.TrackerEtaMax);
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
        switch (WDecay()) {
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
        NewSignalFile(ww);
        break;
    case kBackground :
        NewBackgroundFile(ttlep);
        NewBackgroundFile(tthad);
        NewBackgroundFile(hh);
        NewBackgroundFile(zz);
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
//     Jets particles = event.Partons().GenParticles();
//     Jets w = fastjet::sorted_by_pt(copy_if_abs_particle(particles, WId));
//     remove_if_not_in_pt_window(w, PreCut(), UpperCut());
    return 1;
}

}

}
