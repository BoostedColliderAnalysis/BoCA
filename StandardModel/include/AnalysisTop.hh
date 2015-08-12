#pragma once

#include "AnalysisStandardModel.hh"

namespace analysis
{

namespace standardmodel
{

enum class Decay
{
    leptonic,
    hadronic
};

std::string Name(const Decay decay);

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
        this->pre_cuts().SetPtLowerCut(Id::bottom, this->LowerPtCut() / 5);
        this->pre_cuts().SetPtLowerCut(Id::W, this->LowerPtCut() / 5);
    }

    Decay TopDecay() const {
        return Decay::leptonic;
        return Decay::hadronic;
    }

private:

    std::string ProjectName() const final {
        return  Name(this->collider_type()) + "-" + std::to_string(this->LowerPtCut()) + "GeV-" + Name(Process::tt) + "-" + Name(TopDecay()) + "-jan";
    }

    void SetFiles(Tag tag) final {
        switch (tag) {
        case Tag::signal :
            if (TopDecay() == Decay::hadronic || this->tagger().Name() == "Bottom") this->NewFile(tag, Process::tt_had);
            if (this->tagger().Name() == "Bottom") this->NewFile(tag, Process::hh);
            if (this->tagger().Name() == "Bottom") this->NewFile(tag, Process::bb);
            if (TopDecay() == Decay::leptonic || this->tagger().Name() == "Bottom") this->NewFile(tag, Process::tt_lep);
            if (this->tagger().Name() == "WHadronic") this->NewFile(tag, Process::ww);
            break;
        case Tag::background :
            if (TopDecay() == Decay::leptonic && this->tagger().Name() != "Bottom") this->NewFile(tag, Process::tt_had);
            if (this->tagger().Name() != "Bottom") this->NewFile(tag, Process::hh);
            if (this->tagger().Name() != "Bottom") this->NewFile(tag, Process::bb);
            this->NewFile(tag, Process::cc);
            this->NewFile(tag, Process::gg);
            this->NewFile(tag, Process::qq);
            if (TopDecay() == Decay::hadronic && this->tagger().Name() != "Bottom") this->NewFile(tag, Process::tt_lep);
            this->NewFile(tag, Process::zz);
            if (this->tagger().Name() != "WHadronic") this->NewFile(tag, Process::ww);
            break;
        }
    }

    int PassPreCut(Event const& event, Tag) const final {
        Jets particles = fastjet::sorted_by_pt(event.Partons().GenParticles());
        if ((particles.at(0).pt() > this->LowerQuarkCut() && particles.at(0).pt() < this->UpperQuarkCut()) && (particles.at(1).pt() > this->LowerQuarkCut() &&  particles.at(1).pt() < this->UpperQuarkCut())) return 1;
        return 0;
    }

};

}

}
