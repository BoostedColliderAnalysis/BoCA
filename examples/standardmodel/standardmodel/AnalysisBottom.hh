/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/multiplets/Sort.hh"
#include "boca/multiplets/Particles.hh"
#include "standardmodel/AnalysisStandardModel.hh"
#include "boca/Event.hh"

namespace standardmodel
{

// enum class Production
// {
//     DYP,
//     VBF,
//     Associated
// };

// std::string Name(const Production production_channel);

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
        this->PreCuts().PtLowerCut().Set(Id::bottom, this->LowerPtCut());
        this->PreCuts().PtUpperCut().Set(Id::bottom, this->UpperPtCut());
        this->PreCuts().TrackerMaxEta().Set(Id::bottom, Settings::TrackerEtaMax());
        this->PreCuts().ConsiderBuildingBlock().Set(Id::bottom, false);
    }

private:

    std::string AnalysisName() const override {
        return  Name(this->Collider()) + "-" + boca::units::Name(this->LowerPtCut()) + "-revised";
//       return  Name(production_channel()) + "_" + Name(this->Collider()) + "_" + boca::units::Name(this->LowerPtCut()) + "-large-new";
    }

//     Production production_channel() const {
//         return Production::DYP;
//         //         return Production::VBF;
//         //         return Production::Associated;
//     }

    void SetFiles(Tag tag, Stage stage)override {
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag, Process::bb);
            break;
        case Tag::background :
            this->NewFile(tag, Process::cc);
            this->NewFile(tag, Process::qq);
            this->NewFile(tag, Process::gg);
            if (stage == Stage::reader) {
                this->NewFile(tag, Process::tt_had);
                this->NewFile(tag, Process::tt_lep);
//             this->NewFile(tag, Process::hh_bb);
            }
            this->NewFile(tag, Process::ww);
            this->NewFile(tag, Process::zz);
            break;
        }
    }

    int PassPreCut(boca::Event const& event, Tag) const override {
//         Debug("muons: ", event.Muons().size());
        auto particles = SortedByPt(event.GenParticles());
        particles = CopyIfDrellYan(particles);
        particles = RemoveIfOutsidePtWindow(particles, this->LowerPtCut(), this->UpperPtCut());
        if (particles.size() != 1) return 0;
        return 1;
        auto jets = event.Jets();
        jets = RemoveIfOutsidePtWindow(jets, this->LowerPtCut(), this->UpperPtCut());
        return jets.size();
    }

};

}
