#pragma once

#include "boca/analysis/Analysis.hh"

/**
* @ingroup Examples
* @brief Example
*
*/
namespace simple
{

template<typename Tagger_>
class Analysis : public boca::Analysis<Tagger_>
{

public:

    void SetFiles(boca::Tag tag, boca::Stage)
    {
        switch (tag) {
        case boca::Tag::signal :
            // put your signal file here
            boca::AnalysisBase::NewFile(tag, "hh_14TeV-500GeV", "h");
            break;
        case boca::Tag::background :
            // put your background file here
            boca::AnalysisBase::NewFile(tag, "bb_14TeV-500GeV", "bb");
            break;
        }
    }

    long TrainNumberMax() const override
    {
        return 1000;
    }

    std::string AnalysisName() const
    {
        return "SimpleAnalysis";
    }

};

}
