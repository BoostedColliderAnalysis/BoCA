#pragma once

#include "AnalysisStandardModel.hh"

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
        this->set_tagger_analysis_name(ProjectName());
        this->pre_cuts().SetPtLowerCut(Id::Z, this->LowerPtCut());
        this->pre_cuts().SetPtUpperCut(Id::Z, this->UpperPtCut());
        this->pre_cuts().SetMassUpperCut(Id::Z, 200. * GeV);
        //     pre_cuts().SetTrackerMaxEta(Id::Z, DetectorGeometry::TrackerEtaMax);
    }

private:

    std::string ProjectName() const final {
        return  "ZTagger-" + Name(this->collider_type()) + "-" + boca::Name(this->PreCut()) + "-jan";
    }


    void SetFiles(Tag tag, Stage) final {
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag, Process::zz);
            break;
        case Tag::background :
            this->NewFile(tag, Process::tt_had);
            this->NewFile(tag, Process::tt_lep);
            this->NewFile(tag, Process::hh);
            this->NewFile(tag, Process::ww);
            this->NewFile(tag, Process::bb);
            this->NewFile(tag, Process::cc);
            this->NewFile(tag, Process::qq);
            this->NewFile(tag, Process::gg);
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
