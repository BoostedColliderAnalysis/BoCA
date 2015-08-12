#pragma once

#include "AnalysisStandardModel.hh"

namespace analysis {

namespace standardmodel {

enum class Decay {
    leptonic, hadronic
};

std::string WName(const Decay decay);

/**
 *
 * @brief HAnalysis subclass defining the W Tagger ananlysis
 *
 * @author Jan Hajer
 *
 */
template <typename Tagger>
class AnalysisW : public AnalysisStandardModel<Tagger> {

public:

    AnalysisW()
    {
        this->set_tagger_analysis_name(ProjectName());
        this->pre_cuts().SetPtLowerCut(Id::W, this->LowerPtCut());
        this->pre_cuts().SetPtUpperCut(Id::W, this->UpperPtCut());
        this->pre_cuts().SetMassUpperCut(Id::W, 200);
        //     pre_cuts().SetTrackerMaxEta(Id::top, DetectorGeometry::TrackerEtaMax);
    }

    Decay WDecay() const
    {
        return Decay::hadronic;
        //         return Decay::leptonic;
    }

private:

    std::string ProjectName() const final
    {
        return  "WTagger-" + Name(this->collider_type()) + "-" + std::to_string(this->LowerPtCut()) + "GeV-" + Name(Process::tt) + "-jan";
    }


    void SetFiles(Tag tag) final {
        switch (tag)
        {
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
    int PassPreCut(Event const& event, Tag) const final
    {
      Jets particles = fastjet::sorted_by_pt(event.Partons().GenParticles());
      if ((particles.at(0).pt() > this->LowerQuarkCut() && particles.at(0).pt() < this->UpperQuarkCut()) && (particles.at(1).pt() > this->LowerQuarkCut() &&  particles.at(1).pt() < this->UpperQuarkCut())) return 1;
        return 0;
    }

};

}

}
