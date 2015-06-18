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
    pre_cuts().SetPtLowerCut(HiggsId, PreCut());
    pre_cuts().SetPtUpperCut(HiggsId, UpperCut());
//     pre_cuts().SetMassUpperCut(HiggsId, 200);
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
    Jets leptons = fastjet::sorted_by_pt(event.Leptons().leptons());
    if(leptons.empty()) return 1;
    if(leptons.front().pt()<80) return 1;
   return 0;
}

}

}
