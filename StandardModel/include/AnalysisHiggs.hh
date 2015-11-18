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
        this->pre_cuts().PtLowerCut().Set(Id::higgs, this->LowerPtCut());
        this->pre_cuts().PtUpperCut().Set(Id::higgs, this->UpperPtCut());
//         this->pre_cuts().PtLowerCut().Set(Id::bottom, this->LowerPtCut() / 5.);
//         this->pre_cuts().PtUpperCut().Set(Id::bottom, this->UpperPtCut() / 5.);
//         this->pre_cuts().MassUpperCut().Set(Id::higgs, 250. * GeV);
        this->pre_cuts().TrackerMaxEta().Set(Id::higgs, DetectorGeometry::TrackerEtaMax());
        this->pre_cuts().TrackerMaxEta().Set(Id::bottom, DetectorGeometry::TrackerEtaMax());
    }

private:

    std::string AnalysisName() const final {
        return Name(this->collider_type()) + "-" + boca::Name(this->LowerPtCut()) + "-pull";
    }

    void SetFiles(Tag tag, Stage) final {
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag, Process::hh_bb);
            if (this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::bb);
            if (this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_lep);
            if (this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_had);
            break;
        case Tag::background :
            this->NewFile(tag, Process::zz);
            if (!this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_had);
            this->NewFile(tag, Process::gg);
            if (!this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::bb);
            this->NewFile(tag, Process::cc);
            this->NewFile(tag, Process::qq);
            this->NewFile(tag, Process::ww);
            if (!this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_lep);
            break;
        }
    }

    int PassPreCut(Event const& , Tag) const final {
          return 1;
//         Jets jets = fastjet::sorted_by_pt(event.Hadrons().Jets());
//         if (jets.size() < 2) return 0;
//         if ((jets.at(0).pt() > this->LowerPtCut() / GeV && jets.at(0).pt() < this->UpperPtCut() / GeV) &&
//           (jets.at(1).pt() > this->LowerPtCut() / GeV && jets.at(1).pt() < this->UpperPtCut() / GeV)) return 1;
        return 0;
    }

};

}

}
