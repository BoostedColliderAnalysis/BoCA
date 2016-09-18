#pragma once

// include the Analysis base class
#include "boca/analysis/Analysis.hh"

/**
* @ingroup Examples
* @brief Example
*
*/
namespace simple
{

// all Analyses inherit from the boca::Analysis base class
// the base class expects an Tagger class as template parameter
template<typename Tagger_>
class Analysis : public boca::Analysis<Tagger_>
{

public:

    // Set Files used in the analysis
    void SetFiles(boca::Phase const& phase) override
    {
        switch (phase.Tag()) {
        case boca::Tag::signal :
            // add a signal file by passing its file and process name
            this->AddSignal("hh_14TeV-500GeV", "h");
            break;
        case boca::Tag::background :
            // add a background file by passing its file and process name
            this->AddBackground("bb_14TeV-500GeV", "bb");
            break;
        }
    }

    // define how many events are supposed to beeing used
    long TrainNumberMax() const override
    {
        return 1000;
    }

    // define the analysis name
    std::string Name() const override
    {
        return "SimpleAnalysis";
    }

};

}
