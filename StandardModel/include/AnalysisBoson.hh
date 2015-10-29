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
class AnalysisBoson : public AnalysisStandardModel<Tagger>
{

public:

    AnalysisBoson() {
        this->pre_cuts().PtLowerCut().Set(Id::neutral_boson, this->LowerPtCut());
        this->pre_cuts().PtUpperCut().Set(Id::neutral_boson, this->UpperPtCut());
//         this->pre_cuts().PtLowerCut().Set(Id::bottom, this->LowerPtCut() / 5.);
//         this->pre_cuts().PtUpperCut().Set(Id::bottom, this->UpperPtCut() / 5.);
//         this->pre_cuts().MassUpperCut().Set(Id::neutral_boson, 250. * GeV);
        this->pre_cuts().TrackerMaxEta().Set(Id::neutral_boson, DetectorGeometry::TrackerEtaMax());
        this->pre_cuts().TrackerMaxEta().Set(Id::bottom, DetectorGeometry::TrackerEtaMax());
    }

private:

    std::string AnalysisName() const final {
        return  Name(this->collider_type()) + "-" + boca::Name(this->LowerPtCut()) + "-pt-switch";
    }

    void SetFiles(Tag tag, Stage stage) final {
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag, Process::hh_bb);
            if (!this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::zz);
//             if (!this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::ww);
            if (this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::bb);
            if (this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_had);
            if (this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_lep);
            break;
        case Tag::background :
            if (!this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_lep);
            if (!this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_had);
            if (!this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::bb);
            this->NewFile(tag, Process::gg);
            this->NewFile(tag, Process::cc);
            this->NewFile(tag, Process::qq);
            if(stage == Stage::reader) this->NewFile(tag, Process::ww);
            break;
        }

    }

    int PassPreCut(Event const& event, Tag) const final {
          return 1;
//         Jets jets = fastjet::sorted_by_pt(event.Hadrons().Jets());
//         if (jets.empty()) return 0;
//         if (jets.front().pt() < this->LowerPtCut() / GeV) return 0;
//         Jets particles = fastjet::sorted_by_pt(event.Partons().GenParticles());
//         if ((particles.at(0).pt() > this->LowerQuarkCut() / GeV && particles.at(0).pt() < this->UpperQuarkCut() / GeV) && (particles.at(1).pt() > this->LowerQuarkCut() / GeV &&  particles.at(1).pt() < this->UpperQuarkCut() / GeV)) return 1;
        return 0;
    }

};

}

}
