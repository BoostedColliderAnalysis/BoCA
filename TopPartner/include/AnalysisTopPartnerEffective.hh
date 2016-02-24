/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#pragma once

#include "AnalysisTopPartner.hh"

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
        return "Naturalness-Effective-" + Name(DetectorGeometry::DetectorType()) + "-" + boca::Name(this->Mass()) + "-neutral-truth";
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

    int PassPreCut(Event const& , Tag) const override {
        return 1;
    }

};

}

}
