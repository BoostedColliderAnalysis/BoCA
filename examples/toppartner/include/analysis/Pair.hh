/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "include/analysis/TopPartner.hh"
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

    std::string AnalysisName() const override {
        INFO0;
        return "Naturalness-Pair-" + Name(Settings::Collider()) + "-" + boca::Name(this->Mass()) + "-latex";
    }

    void SetFiles(Tag tag, Stage)override {
        INFO0;
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag, Process::TT);
            break;
        case Tag::background :
            this->NewFile(tag, Process::ttBjj);
            this->NewFile(tag, Process::ttBB);
            break;
        }
    }

};

}

}
