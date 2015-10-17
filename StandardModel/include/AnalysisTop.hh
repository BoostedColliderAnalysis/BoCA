#pragma once

#include "AnalysisStandardModel.hh"
#include "WHadronicTagger.hh"

namespace boca
{

namespace standardmodel
{

/**
 *
 * @brief Top Tagger ananlysis
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger>
class TopAnalysis : public AnalysisStandardModel<Tagger>
{

public:

    TopAnalysis() {
        this->set_tagger_analysis_name(ProjectName());
        this->pre_cuts().SetPtLowerCut(Id::top, this->LowerPtCut());
        this->pre_cuts().SetPtUpperCut(Id::top, this->UpperPtCut());
//         this->pre_cuts().SetMassUpperCut(Id::top, 500);
        this->pre_cuts().SetTrackerMaxEta(Id::top, DetectorGeometry::TrackerEtaMax());
        this->pre_cuts().SetPtLowerCut(Id::bottom, this->LowerPtCut() / 5.);
        this->pre_cuts().SetPtLowerCut(Id::W, this->LowerPtCut() / 5.);
    }

    Decay TopDecay() const {
        return Decay::hadronic;
        return Decay::leptonic;
    }

private:

    std::string ProjectName() const final {
        return  Name(this->collider_type()) + "-" + boca::Name(this->LowerPtCut()) + "-" + Name(Process::tt) + "-" + Name(TopDecay()) + "-test3";
    }

    void SetFiles(Tag tag, Stage) final {
        switch (tag) {
        case Tag::signal :
            if (TopDecay() == Decay::hadronic || this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_had);
            if (this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::hh);
            if (this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::bb);
            if (TopDecay() == Decay::leptonic || this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_lep);
            if (this->template TaggerIs<WHadronicTagger>()) this->NewFile(tag, Process::ww);
            break;
        case Tag::background :
            if (TopDecay() == Decay::leptonic && !this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_had);
            if (!this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::hh);
            if (!this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::bb);
            this->NewFile(tag, Process::cc);
            this->NewFile(tag, Process::gg);
            this->NewFile(tag, Process::qq);
            if (TopDecay() == Decay::hadronic && !this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_lep);
            this->NewFile(tag, Process::zz);
            if (!this->template TaggerIs<WHadronicTagger>()) this->NewFile(tag, Process::ww);
            break;
        }
    }

    int PassPreCut(Event const& event, Tag) const final {
        Jets particles = fastjet::sorted_by_pt(event.Partons().GenParticles());
        if ((particles.at(0).pt() > this->LowerQuarkCut() / GeV && particles.at(0).pt() < this->UpperQuarkCut() / GeV) && (particles.at(1).pt() > this->LowerQuarkCut() / GeV &&  particles.at(1).pt() < this->UpperQuarkCut() / GeV)) return 1;
        return 0;
    }

};

}

}
