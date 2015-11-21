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
        this->pre_cuts().PtLowerCut().Set(Id::Z, this->LowerPtCut());
        this->pre_cuts().PtUpperCut().Set(Id::Z, this->UpperPtCut());
//         this->pre_cuts().MassUpperCut().Set(Id::Z, 200. * GeV);
        this->pre_cuts().TrackerMaxEta().Set(Id::Z, DetectorGeometry::TrackerEtaMax());
    }

private:

    std::string AnalysisName() const final {
        return Name(this->collider_type()) + "-" + boca::Name(this->LowerPtCut()) + "-large-2";
    }


    void SetFiles(Tag tag, Stage stage) final {
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
    int PassPreCut(Event const& , Tag) const final {
        return 1;
//        std::vector<Jet> particles = fastjet::sorted_by_pt(event.Partons().GenParticles());
//         if ((particles.at(0).pt() > this->LowerQuarkCut() / GeV && particles.at(0).pt() < this->UpperQuarkCut() / GeV) && (particles.at(1).pt() > this->LowerQuarkCut() / GeV &&  particles.at(1).pt() < this->UpperQuarkCut() / GeV)) return 1;
//         return 0;
    }

};

}

}
