#pragma once

#include "AnalysisStandardModel.hh"

namespace analysis {

namespace standardmodel {
/**
 *
 * @brief W tagger ananlysis
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger>
class AnalysisZ : public AnalysisStandardModel<Tagger> {

public:


    AnalysisZ()
    {
        this->set_tagger_analysis_name(ProjectName());
        this->pre_cuts().SetPtLowerCut(Id::Z, this->LowerPtCut());
        this->pre_cuts().SetPtUpperCut(Id::Z, this->UpperPtCut());
        this->pre_cuts().SetMassUpperCut(Id::Z, 200);
        //     pre_cuts().SetTrackerMaxEta(Id::Z, DetectorGeometry::TrackerEtaMax);
    }

private:

    void SetFiles(Tag tag) final {
        switch (tag)
        {
        case Tag::signal :
            this->NewFile(tag, Process::zz);
            break;
        case Tag::background :
            this->NewFile(tag, Process::tt_had);
            this->NewFile(tag, Process::hh);
            this->NewFile(tag, Process::ww);
            this->NewFile(tag, Process::bb);
            this->NewFile(tag, Process::cc);
            this->NewFile(tag, Process::qq);
            this->NewFile(tag, Process::gg);
            break;
        }
    }

    std::string ProjectName() const final
    {
        return  "ZTagger-" + Name(this->collider_type()) + "-" + std::to_string(this->PreCut()) + "GeV-test";
    }

    int PassPreCut(const Event& event, Tag) const final
    {
        Jets leptons = fastjet::sorted_by_pt(event.Leptons().leptons());
        if (leptons.empty())
            return 1;
        if (leptons.front().pt() < 80)
            return 1;
        return 0;
    }

};

}

}
