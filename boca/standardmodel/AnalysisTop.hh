#pragma once

#include "boca/standardmodel/AnalysisStandardModel.hh"
#include "boca/standardmodel/WHadronicTagger.hh"
#include "boca/standardmodel/WLeptonicTagger.hh"
#include "boca/multiplets/Particles.hh"

namespace boca
{

namespace standardmodel
{

enum class TopTagger
{
    boca,
    hep,
    hep2
};

std::string Name(TopTagger top_tagger)
{
    switch (top_tagger) {
    case TopTagger::boca : return "BoCA";
    case TopTagger::hep : return "HEP";
    case TopTagger::hep2 : return "HEP_2";
    }
}

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
        this->PreCuts().TrackerMaxEta().Set(Id::top, Settings::TrackerEtaMax());
    }

    static Decay TopDecay() {
        return Decay::hadronic;
        return Decay::leptonic;
    }

    static boca::standardmodel::TopTagger TopTagger() {
        return boca::standardmodel::TopTagger::boca;
        return boca::standardmodel::TopTagger::hep;
        return boca::standardmodel::TopTagger::hep2;
    }

private:

    std::string AnalysisName() const override {
      return Name(this->Collider()) + "-" + boca::Name(this->LowerPtCut()) + "-" + Name(TopDecay()) + (TopDecay() == Decay::hadronic ? "-" + Name(TopTagger()) : "") + "-revised";
    }

    void SetFiles(Tag tag, Stage)override {
        switch (tag) {
        case Tag::signal :
            if (TopDecay() == Decay::hadronic || this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_had);
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
            if ((TopDecay() == Decay::hadronic) && !this->template TaggerIs<BottomTagger>()) this->NewFile(tag, Process::tt_lep);
            this->NewFile(tag, Process::zz);
            if (!this->template TaggerIs<WHadronicTagger>() && !this->template TaggerIs<WLeptonicTagger>()) this->NewFile(tag, Process::ww);
            break;
        }
    }

    int PassPreCut(Event const& event, Tag) const override {
        auto particles = SortedByPt(event.Partons().GenParticles());
        particles = CopyIfDrellYan(particles);
        particles = RemoveIfOutsidePtWindow(particles, this->LowerPtCut(), this->UpperPtCut());
//         std::cout << "pre cut " << particles.size() << std::endl;
        return particles.size() == 1 ? 1 : 0;
    }

};

}

}
