# include "AnalysisBottomTagger.hh"

namespace analysis
{

namespace bottom
{


  Analysis::Analysis(Tagger &tagger) : analysis::Analysis::Analysis(tagger)
{
    Print(kNotification, "Constructor");
    this->tagger().set_analysis_name(ProjectName());
    pre_cuts().SetPtLowerCut(BottomId, LowerPtCut());
    pre_cuts().SetPtUpperCut(BottomId, UpperPtCut());
    DetectorGeometry detector_geometry;
    pre_cuts().SetTrackerMaxEta(BottomId, detector_geometry.TrackerEtaMax);
    pre_cuts().SetSubJets(false);
}


void Analysis::SetFiles(const Object::Tag tag)
{
    Print(kNotification, "Set File Vector", tag);

    switch (tag) {
    case kSignal :
        NewSignalFile(bb);
//     NewSignalFile(tt);
//     NewBackgroundFile(bb);
        break;
    case kBackground :
        NewBackgroundFile(cc);
//     NewBackgroundFile(tt);
//     NewBackgroundFile(ttcc);
//     NewBackgroundFile(ttjj);
        NewBackgroundFile(qq);
        NewBackgroundFile(gg);
//     NewBackgroundFile(hh);
    NewBackgroundFile(ww);
        break;
    }

}

std::string Analysis::ProcessName(const Process process) const
{
    switch (process) {
    case cc:
        return "cc";
    case jj:
        return "jj";
    case bb:
        return "bb";
    case Hbb:
        return "Hbb";
    case ttbb:
        return "ttbb";
    case ttcc:
        return "ttcc";
    case ttjj:
        return "ttjj";
    case tt:
        return "tt";
    case ttlep:
        return "tt_leptonic";
    case tthad:
        return "tt_hadronic";
    case hh:
        return "hh";
    case ww:
        return "ww";
    case qq:
        return "qq";
    case gg:
        return "gg";
    default :
        return "";
    }
}


std::string Analysis::ProductionChannelName(const ProductionChannel production_channel) const
{
    switch (production_channel) {
    case Associated :
        return "llbb_";
    case DYP :
        return "pp_z_";
    case VBF :
        return "VBF_";
    default:
        return "";
    }
}

// int Analysis::UpperPtCut() const
// {
//     switch (LowerPtCut()) {
//     case 500 :
//         return 800;
//     case 1000 :
//         return 1500;
//     default :
//         Print(kError, "Upper Cut", "No upper cut");
//         return 0;
//     }
// }

std::string Analysis::DetectorName(const Detector detector) const
{
    switch (detector) {
    case LHC :
        return "14TeV";
    case VBF :
        return "100TeV";
    case LE :
        return "LE";
    default:
        return "";
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
    Jets jets = event.Hadrons().Jets();
    jets = remove_if_not_in_pt_window(jets, LowerPtCut(), UpperPtCut());
    return jets.size();
}

}

}
