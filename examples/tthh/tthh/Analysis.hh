#pragma once

#include <boost/range/algorithm/count_if.hpp>

#include "boca/analysis/Analysis.hh"

/**
* @brief Higgs coupling
* @ingroup Examples
*
*/
namespace tthh
{

using namespace boca::units;

template<typename Tagger_>
class Analysis : public boca::Analysis<Tagger_>
{

public:

    void SetFiles(boca::Phase const &phase) override
    {
        switch (phase.Tag()) {
        case boca::Tag::signal :
            this->AddSignal("lambda0-n1", "\\lambda_{0} n_{1}");
            break;
        case boca::Tag::background :
            this->AddBackground("tt_inc-100TeV", "tt_{inc}");
            this->AddBackground("tttt_100TeV", "tttt");
            this->AddBackground("tttwb_100TeV", "tttW^{\\pm}b");
            this->AddBackground("ttwbb_100TeV", "ttW^{\\pm}bb");
            break;
        }
    }

    long TrainNumberMax() const override
    {
        return 1000;
    }

    std::string Name() const override
    {
        return "SimpleAnalysis-Cut1";
    }

    bool PassPreCut(boca::Event const &event) const override
    {
        return true;
        auto hard = [](auto const & object) {
            return object.Pt() > 10_GeV;
        };
        auto number_hard_jets = boost::range::count_if(event.Jets(), hard);
        auto number_hard_photons = boost::range::count_if(event.Photons(), hard);
        return number_hard_jets >= 2 && number_hard_photons >= 2 ?  true : false;
    }

};

}
