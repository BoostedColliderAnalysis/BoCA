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
class SubDom : public TopPartner<Tagger_>
{

protected:

    std::string Name() const override {
        return "Naturalness-SubDom-" + boca::Name(Settings::Collider()) + "-" + boca::units::Name(this->Mass()) + "-valgrind";
    }

    void SetFiles(Phase const& phase) override {
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

private:

    bool PassPreCut(boca::Event const&) const override {
//         if (event.Jets().size() < 5) return false;
//         if (event.Leptons().empty()) return false;
        return true;
    }

};

}

}
