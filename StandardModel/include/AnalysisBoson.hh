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
        this->PreCuts().PtLowerCut().Set(Id::neutral_boson, this->LowerPtCut());
        this->PreCuts().PtUpperCut().Set(Id::neutral_boson, this->UpperPtCut());
//         this->PreCuts().PtLowerCut().Set(Id::bottom, this->LowerPtCut() / 5.);
//         this->PreCuts().PtUpperCut().Set(Id::bottom, this->UpperPtCut() / 5.);
//         this->PreCuts().MassUpperCut().Set(Id::neutral_boson, 250_GeV);
        this->PreCuts().TrackerMaxEta().Set(Id::neutral_boson, DetectorGeometry::TrackerEtaMax());
        this->PreCuts().TrackerMaxEta().Set(Id::bottom, DetectorGeometry::TrackerEtaMax());
    }

private:

    std::string AnalysisName() const override {
        return  Name(this->Collider()) + "-" + boca::Name(this->LowerPtCut()) + "-large";
    }

    void SetFiles(Tag tag, Stage stage)override {
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

    int PassPreCut(Event const& , Tag) const override {
          return 1;
//        std::vector<Jet> jets = SortedByPt(event.Hadrons().Jets());
//         if (jets.empty()) return 0;
//         if (jets.front().Pt() < this->LowerPtCut()) return 0;
//        std::vector<Jet> particles = SortedByPt(event.Partons().GenParticles());
//         if ((particles.at(0).Pt() > this->LowerQuarkCut() && particles.at(0).Pt() < this->UpperQuarkCut()) && (particles.at(1).Pt() > this->LowerQuarkCut() &&  particles.at(1).Pt() < this->UpperQuarkCut())) return 1;
        return 0;
    }

};

}

}
