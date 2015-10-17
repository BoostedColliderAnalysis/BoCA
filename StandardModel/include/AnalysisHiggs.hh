#pragma once

#include "AnalysisStandardModel.hh"
#include "BottomTagger.hh"

namespace boca
{

namespace standardmodel
{
/**
 *
 * @brief Higgs tagger analysis
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger>
class AnalysisHiggs : public AnalysisStandardModel<Tagger>
{

public:

    AnalysisHiggs() {
        this->set_tagger_analysis_name(ProjectName());
        this->pre_cuts().SetPtLowerCut(Id::higgs, this->LowerPtCut());
        this->pre_cuts().SetPtUpperCut(Id::higgs, this->UpperPtCut());
//         this->pre_cuts().SetPtLowerCut(Id::bottom, this->LowerPtCut() / 5.);
//         this->pre_cuts().SetPtUpperCut(Id::bottom, this->UpperPtCut() / 5.);
//         this->pre_cuts().SetMassUpperCut(Id::higgs, 250. * GeV);
        this->pre_cuts().SetTrackerMaxEta(Id::higgs, DetectorGeometry::TrackerEtaMax());
        this->pre_cuts().SetTrackerMaxEta(Id::bottom, DetectorGeometry::TrackerEtaMax());
    }

private:

    std::string ProjectName() const final {
        return Name(this->collider_type()) + "-" + boca::Name(this->LowerPtCut()) + "-large-remove-cuts";
    }

    void SetFiles(Tag tag, Stage) final {
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag, Process::hh_bb);
            if (this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::bb);
            if (this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_had);
            if (this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_lep);
            break;
        case Tag::background :
            if (!this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::bb);
            if (!this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_had);
            if (!this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_lep);
            this->NewFile(tag, Process::zz);
            this->NewFile(tag, Process::ww);
            this->NewFile(tag, Process::cc);
            this->NewFile(tag, Process::qq);
            this->NewFile(tag, Process::gg);
            break;
        }
    }

    int PassPreCut(Event const& event, Tag) const final {
//         Jets jets = fastjet::sorted_by_pt(event.Hadrons().Jets());
//         if (jets.size() < 2) return 0;
//         if ((jets.at(0).pt() > this->LowerPtCut() / GeV && jets.at(0).pt() < this->UpperPtCut() / GeV) &&
//           (jets.at(1).pt() > this->LowerPtCut() / GeV && jets.at(1).pt() < this->UpperPtCut() / GeV))
          return 1;
        return 0;
    }

};

}

}
