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
//         this->pre_cuts().MassUpperCut().Set(Id::higgs, 250_GeV);
        this->pre_cuts().TrackerMaxEta().Set(Id::higgs, DetectorGeometry::TrackerEtaMax());
        this->pre_cuts().TrackerMaxEta().Set(Id::bottom, DetectorGeometry::TrackerEtaMax());
    }

private:

    std::string AnalysisName() const final {
        return Name(this->Collider()) + "-" + boca::Name(this->LowerPtCut()) + "-jet-1";
    }

    void SetFiles(Tag tag, Stage) final {
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag, Process::hh_bb);
            if (this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_had);
            if (this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::bb);
            if (this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_lep);
            break;
        case Tag::background :
            if (!this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_had);
            if (!this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::bb);
            if (!this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_lep);
            this->NewFile(tag, Process::zz);
            this->NewFile(tag, Process::gg);
            this->NewFile(tag, Process::cc);
            this->NewFile(tag, Process::qq);
            this->NewFile(tag, Process::ww);
            break;
        }
    }

    int PassPreCut(Event const& , Tag) const final {
          return 1;
//        std::vector<Jet> jets = SortedByPt(event.Hadrons().Jets());
//         if (jets.size() < 2) return 0;
//         if ((jets.at(0).Pt() > this->LowerPtCut() && jets.at(0).Pt() < this->UpperPtCut()) &&
//           (jets.at(1).Pt() > this->LowerPtCut() && jets.at(1).Pt() < this->UpperPtCut())) return 1;
        return 0;
    }

};

}

}
