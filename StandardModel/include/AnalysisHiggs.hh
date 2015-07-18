#pragma once

#include "AnalysisStandardModel.hh"

namespace analysis {

namespace standardmodel {
/**
 *
 * @brief Higgs tagger analysis
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger>
class AnalysisHiggs : public AnalysisStandardModel<Tagger> {

public:

    AnalysisHiggs()
    {
        this->tagger().set_analysis_name(ProjectName());
        this->pre_cuts().SetPtLowerCut(Id::higgs, this->LowerPtCut());
        this->pre_cuts().SetPtUpperCut(Id::higgs, this->UpperPtCut());
        this->pre_cuts().SetPtLowerCut(Id::bottom, this->LowerPtCut() / 5);
        this->pre_cuts().SetPtUpperCut(Id::bottom, this->UpperPtCut() / 5);
        this->pre_cuts().SetMassUpperCut(Id::higgs, 250);
        this->pre_cuts().SetTrackerMaxEta(Id::higgs, DetectorGeometry::TrackerEtaMax());
        this->pre_cuts().SetTrackerMaxEta(Id::bottom, DetectorGeometry::TrackerEtaMax());
    }

private:

    void SetFiles(const Tag tag) final {
        switch (tag)
        {
        case Tag::signal :
            this->NewFile(tag, Process::hh_bb);
            if (this->tagger().Name() == "Bottom")
                this->NewFile(tag, Process::bb);
            if (this->tagger().Name() == "Bottom")
                this->NewFile(tag, Process::tt_had);
            if (this->tagger().Name() == "Bottom")
                this->NewFile(tag, Process::tt_lep);
            break;
        case Tag::background :
            if (this->tagger().Name() != "Bottom")
                this->NewFile(tag, Process::tt_had);
            if (this->tagger().Name() != "Bottom")
                this->NewFile(tag, Process::tt_lep);
            this->NewFile(tag, Process::zz);
            this->NewFile(tag, Process::ww);
            if (this->tagger().Name() != "Bottom")
                this->NewFile(tag, Process::bb);
            this->NewFile(tag, Process::cc);
            this->NewFile(tag, Process::qq);
            this->NewFile(tag, Process::gg);
            break;
        }

    }

    std::string ProjectName() const final
    {
        return  "HiggsTagger-" + Name(this->collider_type()) + "-" + std::to_string(this->LowerPtCut()) + "GeV-bb";
    }


    int PassPreCut(const Event& event) const final
    {
        Jets jets = fastjet::sorted_by_pt(event.Hadrons().Jets());
        if (jets.empty())
            return 0;
        if (jets.front().pt() < this->LowerPtCut())
            return 0;
        Jets particles = fastjet::sorted_by_pt(event.Partons().GenParticles());
        if ((particles.at(0).pt() > this->LowerQuarkCut() && particles.at(0).pt() < this->UpperQuarkCut()) && (particles.at(1).pt() > this->LowerQuarkCut() &&  particles.at(1).pt() < this->UpperQuarkCut()))
            return 1;
        return 0;
    }

};

}

}
