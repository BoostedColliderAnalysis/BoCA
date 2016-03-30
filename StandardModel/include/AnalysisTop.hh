#pragma once

#include "AnalysisStandardModel.hh"
#include "WHadronicTagger.hh"
#include "WLeptonicTagger.hh"
#include "Particles.hh"

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
        this->PreCuts().PtLowerCut().Set(Id::top, this->LowerPtCut());
        this->PreCuts().PtUpperCut().Set(Id::top, this->UpperPtCut());
        this->PreCuts().TrackerMaxEta().Set(Id::top, DetectorGeometry::TrackerEtaMax());
    }

    static Decay TopDecay() {
        return Decay::hadronic;
        return Decay::other;
        return Decay::leptonic;
    }

private:

    std::string AnalysisName() const override {
        return Name(this->Collider()) + "-" + boca::Name(this->LowerPtCut()) + "-" + Name(TopDecay()) + "-revised";
    }

    void SetFiles(Tag tag, Stage)override {
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
            if (!this->template TaggerIs<WLeptonicTagger>()) this->NewFile(tag, Process::qq);
            if ((TopDecay() == Decay::hadronic || TopDecay() == Decay::other) && !this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_lep);
            this->NewFile(tag, Process::zz);
            if (!this->template TaggerIs<WHadronicTagger>() && !this->template TaggerIs<WLeptonicTagger>()) this->NewFile(tag, Process::ww);
            break;
        }
    }

    int PassPreCut(Event const& event, Tag) const override {
        std::vector<Particle> particles = SortedByPt(event.Partons().GenParticles());
        particles = CopyIfDrellYan(particles);
        particles = RemoveIfOutsidePtWindow(particles, this->LowerPtCut(), this->UpperPtCut());
//         std::cout << "pre cut " << particles.size() << std::endl;
        return particles.size() == 1 ? 1 : 0;
    }

};

}

}
