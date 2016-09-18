/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#pragma once

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
        return "Naturalness-Effective-" + boca::Name(Settings::Collider()) + "-" + boca::units::Name(this->Mass()) + "-latex";
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

    bool PassPreCut(boca::Event const&) const override {
//         if (event.Jets().size() < 5) return false;
//         if (event.Leptons().empty()) return false;
        return true;
    }

};

}

}
