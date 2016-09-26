/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#pragma once

#include "toppartner/analysis/TopPartner.hh"
#include "boca/multiplets/Particles.hh"
#include "boca/Settings.hh"

#include "toppartner/tagger/EventSubDom.hh"

namespace toppartner
{

namespace analysis
{

/**
 *
 * @brief Top partner analysis
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger_>
class SubDom : public TopPartner<Tagger_>
{

protected:

    std::string Name() const override
    {
        return "Naturalness-SubDom-" + boca::Name(Settings::Collider()) + "-" + boca::units::Name(this->Mass()) + "-large";
    }

    void SetFiles(Phase const &phase) override
    {
        switch (phase.Tag()) {
        case Tag::signal :
            this->AddSignal(Process::TTh);
            break;
        case Tag::background :
            this->AddBackground(Process::ttWWW);
            this->AddBackground(Process::ttWWB);
            this->AddBackground(Process::ttWBB);
            this->AddBackground(Process::ttBBB);
            break;
        }
    }

    long ReadNumberMax() const override
    {
        INFO0;
        if (this->template TaggerIs<tagger::SignatureSubDom>() || this->template TaggerIs<standardmodel::tagger::Global>() || this->template TaggerIs<toppartner::tagger::EventSubDom>()) return 100000;
        return this->TrainNumberMax();
    }

private:

    bool PassPreCut(boca::Event const &event) const override
    {
        if (CopyIfLepton(event.GenParticles()).empty()) return false;
        auto leptons = SortedByPt(event.Leptons());
        if (leptons.empty()) return false;
        if (leptons.front().Pt() < Settings::LeptonMinPt()) return false;
        return true;
    }

};

}

}
