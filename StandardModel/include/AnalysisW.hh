#pragma once

#include "AnalysisStandardModel.hh"
#include "WHadronicTagger.hh"

namespace boca
{

namespace standardmodel
{

/**
 *
 * @brief HAnalysis subclass defining the W Tagger ananlysis
 *
 * @author Jan Hajer
 *
 */
template <typename Tagger>
class AnalysisW : public AnalysisStandardModel<Tagger>
{

public:

    AnalysisW() {
        this->pre_cuts().PtLowerCut().Set(Id::W, this->LowerPtCut());
        this->pre_cuts().PtUpperCut().Set(Id::W, this->UpperPtCut());
//         this->pre_cuts().MassUpperCut().Set(Id::W, 200. * GeV);
        //     pre_cuts().TrackerMaxEta().Set(Id::top, DetectorGeometry::TrackerEtaMax);
        this->pre_cuts().ConsiderBuildingBlock().Set(Id::W, false);
    }

    static Decay WDecay() {
        return Decay::hadronic;
        return Decay::leptonic;
    }

private:

    std::string AnalysisName() const final {
        return Name(this->collider_type()) + "-" + boca::Name(this->LowerPtCut()) + "-bottom";
    }


    void SetFiles(Tag tag, Stage stage) final {
        switch (tag) {
        case Tag::signal :
            if (!this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::ww);
            if (this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::bb);
            if (this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_had);
            if (this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_lep);
            if (this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::hh);
            break;
        case Tag::background :
            this->NewFile(tag, Process::zz);
            this->NewFile(tag, Process::qq);
            this->NewFile(tag, Process::gg);
            this->NewFile(tag, Process::cc);
            if (this->template TaggerIs<WHadronicTagger>() && stage == Stage::reader) this->NewFile(tag, Process::tt_had);
            if (!this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::hh_bb);
            if (!this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::bb);
            if (!this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_lep);
            break;
        }
    }
    int PassPreCut(Event const& event, Tag) const final {
        return 1;
       std::vector<Particle> particles = SortedByPt(event.Partons().GenParticles());
        if ((particles.at(0).pt() > this->LowerQuarkCut() / GeV && particles.at(0).pt() < this->UpperQuarkCut() / GeV) && (particles.at(1).pt() > this->LowerQuarkCut() / GeV &&  particles.at(1).pt() < this->UpperQuarkCut() / GeV)) return 1;
        return 0;
    }

};

}

}
