#include "AnalysisBottomTagger.hh"
#include "Debug.hh"

namespace analysis
{

  namespace standardmodel
{

AnalysisBottom::AnalysisBottom(Tagger &tagger) : analysis::standardmodel::Analysis::Analysis(tagger)
{
    Note();
    this->tagger().set_analysis_name(ProjectName());
    pre_cuts().SetPtLowerCut(Id::bottom, LowerPtCut());
    pre_cuts().SetPtUpperCut(Id::bottom, UpperPtCut());
    pre_cuts().SetTrackerMaxEta(Id::bottom, DetectorGeometry().TrackerEtaMax());
    pre_cuts().SetSubJets(false);
}

void AnalysisBottom::SetFiles(const Tag tag)
{
    Note(Name(tag));

    switch (tag) {
    case Tag::signal :
      NewFile(tag,Process::bb);
      //     NewFile(tag,Process::tt);
      //     NewFile(tag,Process::bb);
        break;
    case Tag::background :
      NewFile(tag,Process::cc);
      //     NewFile(tag,Process::tt);
      //     NewFile(tag,Process::ttcc);
      //     NewFile(tag,Process::ttjj);
      NewFile(tag,Process::qq);
      NewFile(tag,Process::gg);
      //     NewFile(tag,Process::hh);
      NewFile(tag,Process::ww);
        break;
    }

}

std::string AnalysisBottom::ProductionChannelName(const ProductionChannel production_channel) const
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

int AnalysisBottom::PassPreCut(const Event &event)
{
    Info();
    Jets jets = event.Hadrons().Jets();
    jets = remove_if_not_in_pt_window(jets, LowerPtCut(), UpperPtCut());
    return jets.size();
}
std::string AnalysisBottom::ProjectName() const
{
    return  ProductionChannelName(production_channel()) + ColliderName(collider_type()) + "_" + std::to_string(MadGraphCut()) + "GeV-new";
}
AnalysisBottom::ProductionChannel AnalysisBottom::production_channel() const
{
    return DYP;
    //         return VBF;
//         return Associated;
}

}

}
