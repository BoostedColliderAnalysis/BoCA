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
class NewPair : public TopPartner<Tagger_>
{

protected:

    std::string Name() const override {
        INFO0;
        return "Naturalness-Pair-" + boca::units::Name(this->PreCut()) + "-" + boca::Name(Settings::Collider()) + "-" + boca::units::Name(this->Mass()) + "-full";
    }

//     std::string ProcessName() const override {
//         INFO0;
//         return "Naturalness-Pair";
//     }

    void SetFiles(Phase const& phase) override {
        INFO0;
        switch (phase.Tag()) {
        case Tag::signal :
            this->AddSignal(Process::TT);
            break;
        case Tag::background :
            this->AddBackground(Process::ttBjj);
            this->AddBackground(Process::ttBB);
//             this->AddBackground(Process::tthBjj);
            break;
        }
    }

private:

    bool PassPreCut(boca::Event const&) const override {
        INFO0;
        return true;
    }

};

}

}
