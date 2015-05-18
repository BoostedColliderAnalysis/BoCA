# include "AnalysisWTagger.hh"


hwtagger::HAnalysis::HAnalysis(analysis::Tagger &tagger) : analysis::Analysis::Analysis(tagger)
{
//   DebugLevel = analysis::Object::kDebug;
  Print(kNotification, "Constructor");
    tagger_.set_analysis_name(ProjectName());
//     pre_cuts_.SetPtLowerCut(WId, PreCut());
//     pre_cuts_.SetPtUpperCut(WId, UpperCut());
//     DetectorGeometry detector_geometry;
//     pre_cuts_.SetTrackerMaxEta(TopId, detector_geometry.TrackerEtaMax);
}

std::string hwtagger::HAnalysis::ProcessName(const Process process) const {
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

std::string hwtagger::HAnalysis::ColliderName(const Collider collider) const {
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

void hwtagger::HAnalysis::SetFiles(const analysis::Object::Tag tag)
{
    Print(kNotification, "Set File Vector", tag);
    switch (tag) {
    case kSignal :
//         if (WDecay() == kHadronic) NewSignalFile(tthad);
//         else if (WDecay() == kLeptonic) NewSignalFile(ttlep);

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
        NewSignalFile(ww);
//         NewBackgroundFile(zz);
        break;
    case kBackground :
//         if (WDecay() == kHadronic) NewBackgroundFile(ttlep);
//         else if (WDecay() == kLeptonic) NewBackgroundFile(tthad);
    NewBackgroundFile(bb);
//     NewBackgroundFile(wc);
//     NewBackgroundFile(wq);
//     NewBackgroundFile(wg);
//     NewBackgroundFile(wu);
//     NewBackgroundFile(wcb);
//     NewBackgroundFile(wbu);
        break;
    }

}


int hwtagger::HAnalysis::PassPreCut(analysis::Event &event)
{
    Print(kInformation, "paas pre cut");
    Jets particles = event.partons().Generator();
    Jets w = fastjet::sorted_by_pt(copy_if_abs_particle(particles, WId));
//     remove_if_not_in_pt_window(w, PreCut(), UpperCut());
    return w.size();
}

int hwtagger::HAnalysis::RunAnalysis(analysis::Event &event, const analysis::Tagger::Stage stage, const analysis::Object::Tag tag)
{
    Print(kInformation, "Analysis");
    switch (stage) {
      case analysis::Tagger::kTrainer :
        return tagger_.Train(event, pre_cuts_, tag);
      case analysis::Tagger::kReader :
        return reader_.GetBdt(event, pre_cuts_);
    }
}
