/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "AnalysisTopPartner.hh"
#include "DEBUG.hh"

namespace boca
{

namespace naturalness
{

/**
 *
 * @brief Top partner analysis
 *
 * \author Jan Hajer
 *
 */
template<typename Tagger>
class AnalysisNewPair : public AnalysisNaturalness<Tagger>
{

protected:

    std::string AnalysisName() const override {
        INFO0;
        return "Naturalness-Pair-" + boca::Name(this->PreCut()) + "-" + Name(DetectorGeometry::DetectorType()) + "-" + boca::Name(this->Mass()) + "-full";
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

    int PassPreCut(Event const&, Tag) const override {
        INFO0;
        return 1;
    }

};

}

}
