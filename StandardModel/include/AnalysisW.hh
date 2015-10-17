#pragma once

#include "AnalysisStandardModel.hh"

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
        this->set_tagger_analysis_name(ProjectName());
        this->pre_cuts().PtLowerCut().Set(Id::W, this->LowerPtCut());
        this->pre_cuts().PtUpperCut().Set(Id::W, this->UpperPtCut());
        this->pre_cuts().MassUpperCut().Set(Id::W, 200. * GeV);
        //     pre_cuts().TrackerMaxEta().Set(Id::top, DetectorGeometry::TrackerEtaMax);
    }

    Decay WDecay() const {
        return Decay::hadronic;
        return Decay::leptonic;
    }

private:

    std::string ProjectName() const final {
        return  "WTagger-" + Name(this->collider_type()) + "-" + boca::Name(this->LowerPtCut()) + "-" + Name(Process::tt) + "-jan";
    }


    void SetFiles(Tag tag, Stage) final {
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag , Process::ww);
            break;
        case Tag::background :
            this->NewFile(tag , Process::tt_lep);
            this->NewFile(tag , Process::tt_had);
            this->NewFile(tag , Process::hh);
            this->NewFile(tag , Process::zz);
            this->NewFile(tag , Process::bb);
            this->NewFile(tag , Process::cc);
            this->NewFile(tag , Process::qq);
            this->NewFile(tag , Process::gg);
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
