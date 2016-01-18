/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "AnalysisTopPartner.hh"
#include "Debug.hh"

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

    std::string AnalysisName() const final {
        Info0;
        return "Naturalness-Pair-" + boca::Name(this->PreCut()) + "-" + Name(DetectorGeometry::detector_type()) + "-" + boca::Name(this->Mass()) + "-full";
    }

//     std::string ProcessName() const final {
//         Info0;
//         return "Naturalness-Pair";
//     }

    void SetFiles(Tag tag, Stage) final {
        Info0;
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

    int PassPreCut(Event const&, Tag) const final {
        Info0;
        return 1;
    }

};

}

}
