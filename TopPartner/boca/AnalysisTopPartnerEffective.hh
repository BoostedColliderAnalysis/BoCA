/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#pragma once

#include "boca/AnalysisTopPartner.hh"

namespace boca
{

namespace naturalness
{

/**
 *
 * @brief Top partner analysis
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger>
class AnalysisEffective : public AnalysisNaturalness<Tagger>
{

protected:

    std::string AnalysisName() const override {
        return "Naturalness-Effective-" + Name(DetectorGeometry::DetectorType()) + "-" + boca::Name(this->Mass()) + "-latex";
    }

    void SetFiles(Tag tag, Stage)override {
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag, Process::TThh);
            break;
        case Tag::background :
            this->NewFile(tag, Process::ttWWWW);
            this->NewFile(tag, Process::ttWWWB);
            this->NewFile(tag, Process::ttWWBB);
            this->NewFile(tag, Process::ttWBBB);
            this->NewFile(tag, Process::ttBBBB);
            break;
        }
    }

private:

    int PassPreCut(Event const&, Tag) const override {
//         if (event.Hadrons().Jets().size() < 5) return 0;
//         if (event.Leptons().leptons().empty()) return 0;
        return 1;
    }

};

}

}
