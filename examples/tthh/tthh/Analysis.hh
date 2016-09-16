#pragma once

#include <boost/range/algorithm/count_if.hpp>

#include "boca/analysis/Analysis.hh"

namespace tthh
{

using namespace boca::units;

template<typename Tagger_>
class Analysis : public boca::Analysis<Tagger_>
{

public:

    void SetFiles(boca::Tag tag, boca::Stage) override
    {
        switch (tag) {
        case boca::Tag::signal :
            // put your signal file here
            boca::analysis::Base::NewFile(tag, "hh_14TeV-500GeV", "h");
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
        return "SimpleAnalysis";
    }

    bool PassPreCut(boca::Event const &event) const override
    {
        auto jets = event.Jets();
        auto number_hard_jets = boost::range::count_if(jets, [](boca::Jet const & jet) {
            return jet.Pt() > 50_GeV;
        });
        return number_hard_jets >= 2  ?  true : false;
    }

};

}
