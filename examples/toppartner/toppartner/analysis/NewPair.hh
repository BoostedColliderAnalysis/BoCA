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

    std::string AnalysisName() const override {
        INFO0;
        return "Naturalness-Pair-" + boca::units::Name(this->PreCut()) + "-" + Name(Settings::Collider()) + "-" + boca::units::Name(this->Mass()) + "-full";
    }

//     std::string ProcessName() const override {
//         INFO0;
//         return "Naturalness-Pair";
//     }

    void SetFiles(Tag tag, Stage)override {
        INFO0;
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag, Process::TT);
            break;
        case Tag::background :
            this->NewFile(tag, Process::ttBjj);
            this->NewFile(tag, Process::ttBB);
//             this->NewFile(tag, Process::tthBjj);
            break;
        }
    }

private:

    int PassPreCut(boca::Event const&, Tag) const override {
        INFO0;
        return 1;
    }

};

}

}
