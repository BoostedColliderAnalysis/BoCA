#pragma once

#include "AnalysisStandardModel.hh"

namespace analysis {

namespace standardmodel {

enum class Production {
    DYP, VBF, Associated
};

std::string Name(const Production production_channel);

/**
 *
 * @brief  Bottom Tagger Analysis
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger>
class AnalysisBottom : public AnalysisStandardModel<Tagger> {

public:

    AnalysisBottom()
    {
        this->set_tagger_analysis_name(ProjectName());
        this->pre_cuts().SetPtLowerCut(Id::bottom, this->LowerPtCut());
        this->pre_cuts().SetPtUpperCut(Id::bottom, this->UpperPtCut());
        this->pre_cuts().SetTrackerMaxEta(Id::bottom, DetectorGeometry::TrackerEtaMax());
        this->pre_cuts().SetSubJets(false);
    }

private:

    std::string ProjectName() const final
    {
        return  Name(production_channel()) + Name(this->collider_type()) + "_" + std::to_string(this->MadGraphCut()) + "GeV-new";
    }


    Production production_channel() const
    {
        return Production::DYP;
        //         return Production::VBF;
        //         return Production::Associated;
    }

    void SetFiles(const Tag tag) final {
        switch (tag)
        {
        case Tag::signal :
            this->NewFile(tag, Process::bb);
            //     NewFile(tag,Process::tt);
            //     NewFile(tag,Process::bb);
            break;
        case Tag::background :
            this->NewFile(tag, Process::cc);
            //     NewFile(tag,Process::tt);
            //     NewFile(tag,Process::ttcc);
            //     NewFile(tag,Process::ttjj);
            this->NewFile(tag, Process::qq);
            this->NewFile(tag, Process::gg);
            //     NewFile(tag,Process::hh);
            this->NewFile(tag, Process::ww);
            break;
        }

    }

    int PassPreCut(const Event& event) const final
    {
        Jets jets = event.Hadrons().Jets();
        jets = RemoveIfOutsidePtWindow(jets, this->LowerPtCut(), this->UpperPtCut());
        return jets.size();
    }

};

}

}
