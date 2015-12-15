#pragma once

#include "AnalysisStandardModel.hh"
#include "WHadronicTagger.hh"
#include "WLeptonicTagger.hh"
// #define INFORMATION
#include "Debug.hh"

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
        Info0;
        this->pre_cuts().PtLowerCut().Set(Id::top, this->LowerPtCut());
        this->pre_cuts().PtUpperCut().Set(Id::top, this->UpperPtCut());
        this->pre_cuts().TrackerMaxEta().Set(Id::top, DetectorGeometry::TrackerEtaMax());
    }

    static Decay TopDecay() {
        Info0;
        return Decay::hadronic;
        return Decay::other;
        return Decay::leptonic;
    }

private:

    std::string AnalysisName() const final {
        Info0;
        return Name(this->collider_type()) + "-" + boca::Name(this->LowerPtCut()) + "-" + Name(TopDecay()) + "";
    }

    void SetFiles(Tag tag, Stage) final {
        Info0;
        switch (tag) {
        case Tag::signal :
            if (TopDecay() == Decay::hadronic || TopDecay() == Decay::other || this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_had);
            if (this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::hh);
            if (this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::bb);
            if (TopDecay() == Decay::leptonic || this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_lep);
            if (this->template TaggerIs<WHadronicTagger>() || this->template TaggerIs<WLeptonicTagger>()) this->NewFile(tag, Process::ww);
            break;
        case Tag::background :
            if (TopDecay() == Decay::leptonic && !this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_had);
            if (!this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::hh);
            if (!this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::bb);
            this->NewFile(tag, Process::cc);
            this->NewFile(tag, Process::gg);
            this->NewFile(tag, Process::qq);
            if ((TopDecay() == Decay::hadronic || TopDecay() == Decay::other) && !this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_lep);
            this->NewFile(tag, Process::zz);
            if (!this->template TaggerIs<WHadronicTagger>() && !this->template TaggerIs<WLeptonicTagger>()) this->NewFile(tag, Process::ww);
            break;
        }
    }

    int PassPreCut(Event const& event, Tag) const final {
        Info0;
        std::vector<Particle> particles = SortedByPt(event.Partons().GenParticles());
        particles = CopyIfDrellYan(particles);
        particles = RemoveIfOutsidePtWindow(particles, this->LowerPtCut(), this->UpperPtCut());
        if (particles.size() != 1) return 0;
        return 1;
    }

};

}

}
