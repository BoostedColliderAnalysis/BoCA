/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "AnalysisStandardModel.hh"
#include "Vector.hh"

namespace boca
{

namespace standardmodel
{

enum class Production
{
    DYP,
    VBF,
    Associated
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
class AnalysisBottom : public AnalysisStandardModel<Tagger>
{

public:

    AnalysisBottom() {
        this->pre_cuts().PtLowerCut().Set(Id::bottom, this->LowerPtCut());
        this->pre_cuts().PtUpperCut().Set(Id::bottom, this->UpperPtCut());
        this->pre_cuts().TrackerMaxEta().Set(Id::bottom, DetectorGeometry::TrackerEtaMax());
        this->pre_cuts().SetSubJets(false);
    }

private:

    std::string AnalysisName() const final {
      return  Name(production_channel()) + Name(this->collider_type()) + "_" + boca::Name(this->MadGraphCut()) + "-large";
    }

    Production production_channel() const {
        return Production::DYP;
        //         return Production::VBF;
        //         return Production::Associated;
    }

    void SetFiles(Tag tag, Stage) final {
        switch (tag) {
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
//             this->NewFile(tag, Process::hh);
            this->NewFile(tag, Process::ww);
            break;
        }

    }

    int PassPreCut(Event const& event, Tag) const final {
        Jets jets = event.Hadrons().Jets();
        jets = RemoveIfOutsidePtWindow(jets, this->LowerPtCut(), this->UpperPtCut());
        return jets.size();
    }

};

}

}
