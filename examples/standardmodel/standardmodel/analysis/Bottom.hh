/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/fastjet/Sort.hh"
#include "boca/fastjet/Particles.hh"
#include "standardmodel/analysis/StandardModel.hh"
#include "boca/event/Event.hh"

namespace standardmodel
{

namespace analysis
{

/**
 *
 * @brief  Bottom Tagger Analysis
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger_>
class Bottom : public StandardModel<Tagger_>
{

public:

    Bottom()
    {
        this->PreCuts().PtLowerCut().Set(Id::bottom, this->LowerPtCut());
        this->PreCuts().PtUpperCut().Set(Id::bottom, this->UpperPtCut());
        this->PreCuts().TrackerMaxEta().Set(Id::bottom, Settings::TrackerEtaMax());
        this->PreCuts().ConsiderBuildingBlock().Set(Id::bottom, false);
    }

private:

    std::string Name() const override
    {
        return  boca::Name(this->Collider()) + "-" + boca::units::Name(this->LowerPtCut()) + "-delete-2";
//       return  Name(production_channel()) + "_" + boca::Name(this->Collider()) + "_" + boca::units::Name(this->LowerPtCut()) + "-large-new";
    }

//     Production production_channel() const {
//         return Production::DYP;
//         //         return Production::VBF;
//         //         return Production::Associated;
//     }

    void SetFiles(Phase const &phase) override
    {
        switch (phase.Tag()) {
        case Tag::signal :
            this->AddSignal(Process::bb);
            break;
        case Tag::background :
            this->AddBackground(Process::cc);
            this->AddBackground(Process::qq);
            this->AddBackground(Process::gg);
            if (phase.Stage() == Stage::reader) {
                this->AddBackground(Process::tt_had);
                this->AddBackground(Process::tt_lep);
//             this->AddBackground(Process::hh_bb);
            }
            this->AddBackground(Process::ww);
            this->AddBackground(Process::zz);
            break;
        }
    }

    bool PassPreCut(boca::Event const &event) const override
    {
//         Debug("muons: ", event.Muons().size());
        auto particles = SortedByPt(event.GenParticles());
        particles = CopyIfDrellYan(particles);
        particles = RemoveIfOutsidePtWindow(particles, this->LowerPtCut(), this->UpperPtCut());
        if (particles.size() != 1) return false;
        return true;
        auto jets = event.Jets();
        jets = RemoveIfOutsidePtWindow(jets, this->LowerPtCut(), this->UpperPtCut());
        return jets.size() > 0  ? true : false;
    }

};

}

}
