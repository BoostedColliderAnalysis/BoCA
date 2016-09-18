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

    void SetFiles(boca::Phase const& phase) override
    {
        switch (phase.Tag()) {
        case boca::Tag::signal :
            // put your signal file here
            this->NewFile(phase.Tag(), "hh_14TeV-500GeV", "h");
            break;
        case boca::Tag::background :
            // put your background file here
            this->NewFile(phase.Tag(), "bb_14TeV-500GeV", "bb");
            break;
        }
    }

    long TrainNumberMax() const override
    {
        return 1000;
    }

    std::string Name() const override
    {
        return "SimpleAnalysis";
    }

};

}
