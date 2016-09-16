#pragma once

//  Analysis base class
#include "boca/analysis/Analysis.hh"

/**
* @ingroup Examples
* @brief Cut Example
*
*/
namespace cut
{

// Analysis inherits from the boca::Analysis base class and has to pass a tagger class as template paramter
template<typename Tagger_>
class Analysis : public boca::Analysis<Tagger_>
{

public:

    // Set files for signal and background
    void SetFiles(boca::Tag tag, boca::Stage) override
    {
        switch (tag) {
        case boca::Tag::signal :
            // put your signal file here
            this->NewFile(tag, "hh_14TeV-500GeV", "h");
            break;
        case boca::Tag::background :
            // put your background file here
            boca::analysis::Base::NewFile(tag, "bb_14TeV-500GeV", "bb");
            break;
        }
    }

    long TrainNumberMax() const override
    {
        return 1000;
    }

    std::string Name() const override
    {
        return "CutAnalysis";
    }

    bool PassPreCut(boca::Event const& event) const override{
        auto jets = event.Jets();
        if (jets.size() < 2) return false;
        return true;
    }

};

}
