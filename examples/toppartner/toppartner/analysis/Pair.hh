/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "toppartner/analysis/TopPartner.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace toppartner{

namespace analysis{

/**
 *
 * @brief Top partner analysis
 *
 * \author Jan Hajer
 *
 */
template<typename Tagger_>
class Pair : public TopPartner<Tagger_>
{

    std::string Name() const override {
        INFO0;
        return "Naturalness-Pair-" + boca::Name(Settings::Collider()) + "-" + boca::units::Name(this->Mass()) + "-latex";
    }

    void SetFiles(Phase const& phase) override {
        INFO0;
        switch (phase.Tag()) {
        case Tag::signal :
            this->AddSignal(Process::TT);
            break;
        case Tag::background :
            this->AddBackground(Process::ttBjj);
            this->AddBackground(Process::ttBB);
            break;
        }
    }

};

}

}
