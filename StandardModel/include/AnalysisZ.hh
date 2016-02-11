#pragma once

#include "AnalysisStandardModel.hh"
#include "ZHadronicTagger.hh"

namespace boca
{

namespace standardmodel
{
/**
 *
 * @brief W tagger ananlysis
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger>
class AnalysisZ : public AnalysisStandardModel<Tagger>
{

public:


    AnalysisZ() {
        this->PreCuts().PtLowerCut().Set(Id::Z, this->LowerPtCut());
        this->PreCuts().PtUpperCut().Set(Id::Z, this->UpperPtCut());
//         this->PreCuts().MassUpperCut().Set(Id::Z, 200_GeV);
        this->PreCuts().TrackerMaxEta().Set(Id::Z, DetectorGeometry::TrackerEtaMax());
    }

private:

    std::string AnalysisName() const override {
        return Name(this->Collider()) + "-" + boca::Name(this->LowerPtCut()) + "-large-2";
    }


    void SetFiles(Tag tag, Stage stage)override {
        switch (tag) {
        case Tag::signal :
            if (!this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::zz);
            if (this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::bb);
            if (this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_had);
            if (this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_lep);
            if (this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::hh);
            break;
        case Tag::background :
            if(stage == Stage::reader)
          this->NewFile(tag, Process::ww);
            this->NewFile(tag, Process::qq);
            this->NewFile(tag, Process::gg);
            this->NewFile(tag, Process::cc);
            if (!this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_had);
            if (!this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::hh_bb);
            if (!this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::bb);
            if (!this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_lep);
            break;
        }
    }
    int PassPreCut(Event const& , Tag) const override {
        return 1;
//        std::vector<Jet> particles = SortedByPt(event.Partons().GenParticles());
//         if ((particles.at(0).Pt() > this->LowerQuarkCut() && particles.at(0).Pt() < this->UpperQuarkCut()) && (particles.at(1).Pt() > this->LowerQuarkCut() &&  particles.at(1).Pt() < this->UpperQuarkCut())) return 1;
//         return 0;
    }

};

}

}
