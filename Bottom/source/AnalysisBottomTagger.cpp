# include "AnalysisBottomTagger.hh"


bottom::Analysis::Analysis(analysis::Tagger &tagger) : analysis::Analysis::Analysis(tagger)
{
    Print(kNotification, "Constructor");
    tagger_.set_analysis_name(ProjectName());
    pre_cuts_.SetPtLowerCut(BottomId, LowerCut());
    pre_cuts_.SetPtUpperCut(BottomId, UpperCut());
    analysis::DetectorGeometry detector_geometry;
    pre_cuts_.SetTrackerMaxEta(BottomId, detector_geometry.TrackerEtaMax);
    pre_cuts_.SetSubJets(false);
}


void bottom::Analysis::SetFiles(const analysis::Object::Tag tag)
{
    Print(kNotification, "Set File Vector", tag);

    switch (tag) {
    case kSignal :
        NewSignalFile(bb);
//     NewSignalFile(Hbb);
//     NewSignalFile(ttbb);
//     NewSignalFile(ttlep);
//     NewSignalFile(tthad);
//     NewSignalFile(tt);
//     NewBackgroundFile(bb);
        break;
    case kBackground :
        NewBackgroundFile(cc);
//     NewBackgroundFile(jj);
//     NewBackgroundFile(tt);
//     NewBackgroundFile(ttcc);
//     NewBackgroundFile(ttjj);
        NewBackgroundFile(qq);
        NewBackgroundFile(gg);
//     NewBackgroundFile(hh);
//     NewBackgroundFile(ww);
        break;
    }

}

std::string bottom::Analysis::ProcessName(const Process process) const
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


std::string bottom::Analysis::ProductionChannelName(const ProductionChannel production_channel) const
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

int bottom::Analysis::UpperCut() const
{
    switch (LowerCut()) {
    case 500 :
        return 800;
    case 1000 :
        return 1500;
    default :
        Print(kError, "Upper Cut", "No upper cut");
        return 0;
    }
}

std::string bottom::Analysis::DetectorName(const Detector detector) const
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


int bottom::Analysis::PassPreCut(analysis::Event &event)
{
    Print(kInformation, "paas pre cut");
    analysis::Jets jets = event.hadrons().Jets();
    jets = analysis::remove_if_not_in_pt_window(jets, LowerCut(), UpperCut());
    return jets.size();
}


int bottom::Analysis::RunAnalysis(analysis::Event &event, const analysis::Tagger::Stage stage, const Tag tag)
{
    Print(kInformation, "Analysis");
    switch (stage) {
    case analysis::Tagger::kTrainer :
        return tagger_.Train(event, pre_cuts_, tag);
    case analysis::Tagger::kReader :
        return reader_.GetBdt(event, pre_cuts_);
    default :
        return 0;
    }
}

