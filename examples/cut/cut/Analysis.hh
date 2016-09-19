#pragma once

// Include the cut analysis base class
#include "boca/analysis/Cut.hh"

/**
* @ingroup Examples
* @brief Cut Example
*
*/
namespace cut
{

// The analysis inherits from the boca cut analysis base class
class Analysis : public boca::analysis::Cut
{

public:

    // Set files for signal and background
    // it is assumed that all files are in the same folder
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
        return "CutAnalysis";
    }

    // Define the cuts
    bool PassPreCut(boca::Event const& event) const override{
        // The event class contains all relevant physical objects
        auto jets = event.Jets();
        //  this cut is obviously not enough
        if (jets.size() < 2) return false;
        return true;
    }

};

}
