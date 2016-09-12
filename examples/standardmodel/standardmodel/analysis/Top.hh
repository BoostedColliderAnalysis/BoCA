#pragma once

#include "boca/multiplets/Particles.hh"

#include "standardmodel/analysis/StandardModel.hh"
#include "standardmodel/tagger/WHadronic.hh"
#include "standardmodel/tagger/WLeptonic.hh"

namespace standardmodel
{

enum class TopTagger
{
    boca,
    hep,
    hep2
};

std::string Name(TopTagger top_tagger);

namespace analysis
{

/**
 *
 * @brief Top Tagger ananlysis
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger_>
class Top : public StandardModel<Tagger_>
{

public:

    Top() {
        this->PreCuts().PtLowerCut().Set(Id::top, this->LowerPtCut());
        this->PreCuts().PtUpperCut().Set(Id::top, this->UpperPtCut());
        this->PreCuts().TrackerMaxEta().Set(Id::top, Settings::TrackerEtaMax());
    }

    static Decay TopDecay() {
        return Decay::hadronic;
        return Decay::leptonic;
    }

    static standardmodel::TopTagger TopTagger() {
        return standardmodel::TopTagger::hep;
        return standardmodel::TopTagger::boca;
        return standardmodel::TopTagger::hep2;
    }

private:

    std::string AnalysisName() const override {
      return Name(this->Collider()) + "-" + boca::units::Name(this->LowerPtCut()) + "-" + Name(TopDecay()) + (TopDecay() == Decay::hadronic ? "-" + Name(TopTagger()) : "") + "";
    }

    void SetFiles(Tag tag, Stage)override {
        switch (tag) {
        case Tag::signal :
            if (TopDecay() == Decay::hadronic || this->template TaggerIs<tagger::Bottom>()) this->NewFile(tag, Process::tt_had);
            if (this->template TaggerIs<tagger::Bottom>()) this->NewFile(tag, Process::hh);
            if (this->template TaggerIs<tagger::Bottom>()) this->NewFile(tag, Process::bb);
            if (TopDecay() == Decay::leptonic || this->template TaggerIs<tagger::Bottom>()) this->NewFile(tag, Process::tt_lep);
            if (this->template TaggerIs<tagger::WHadronic>() || this->template TaggerIs<tagger::WLeptonic>()) this->NewFile(tag, Process::ww);
            break;
        case Tag::background :
            if (TopDecay() == Decay::leptonic && !this->template TaggerIs<tagger::Bottom>()) this->NewFile(tag, Process::tt_had);
            if (!this->template TaggerIs<tagger::Bottom>()) this->NewFile(tag, Process::hh);
            if (!this->template TaggerIs<tagger::Bottom>()) this->NewFile(tag, Process::bb);
            this->NewFile(tag, Process::cc);
            this->NewFile(tag, Process::gg);
            if (!this->template TaggerIs<tagger::WLeptonic>()) this->NewFile(tag, Process::qq);
            if ((TopDecay() == Decay::hadronic) && !this->template TaggerIs<tagger::Bottom>()) this->NewFile(tag, Process::tt_lep);
            this->NewFile(tag, Process::zz);
            if (!this->template TaggerIs<tagger::WHadronic>() && !this->template TaggerIs<tagger::WLeptonic>()) this->NewFile(tag, Process::ww);
            break;
        }
    }

    int PassPreCut(boca::Event const& event, Tag) const override {
        auto particles = SortedByPt(event.GenParticles());
        particles = CopyIfDrellYan(particles);
        particles = RemoveIfOutsidePtWindow(particles, this->LowerPtCut(), this->UpperPtCut());
//         std::cout << "pre cut " << particles.size() << std::endl;
        return particles.size() == 1 ? 1 : 0;
    }

};

}

}
