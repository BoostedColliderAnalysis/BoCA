/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#pragma once

#include "boca/multiplets/Particles.hh"

#include "toppartner/analysis/TopPartner.hh"

namespace toppartner{

namespace analysis{

/**
 *
 * @brief Top partner analysis
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger_>
class Effective : public TopPartner<Tagger_>
{

protected:

    std::string Name() const override {
        return "Naturalness-Effective-" + boca::Name(Settings::Collider()) + "-" + boca::units::Name(this->Mass()) + "-large-2-new";
    }

    void SetFiles(Phase const& phase) override {
        switch (phase.Tag()) {
        case Tag::signal :
            this->AddSignal(Process::TThh);
            break;
        case Tag::background :
            this->AddBackground(Process::ttWWWW);
            this->AddBackground(Process::ttWWWB);
            this->AddBackground(Process::ttWWBB);
            this->AddBackground(Process::ttWBBB);
            this->AddBackground(Process::ttBBBB);
            break;
        }
    }

private:

    bool PassPreCut(boca::Event const& event) const override {
        if (CopyIfLepton(event.GenParticles()).empty()) return false;
        auto leptons = SortedByPt(event.Leptons());
        if (leptons.empty()) return false;
        if (leptons.front().Pt() < Settings::LeptonMinPt()) return false;
        return true;
    }

};

}

}
