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

    void SetFiles(boca::Phase const& phase) override
    {
        switch (phase.Tag()) {
        case boca::Tag::signal :
            // put your signal file here
            this->AddSignal("hhbbaa_sig", "hh", 0_b,  0_eV, "../events/");
            break;
        case boca::Tag::background :
            // put your background file here
            this->AddBackground("bbaa_bkg", "bbaa", 0_b,  0_eV, "../events/");
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
        auto jets = event.Jets();
        auto number_hard_jets = boost::range::count_if(jets, [](boca::Jet const & jet) {
            return jet.Pt() > 10_GeV;
        });
//        return number_hard_jets >= 2  ?  1 : 0;
        auto photons = event.Photons();
        auto number_hard_photons = boost::range::count_if(photons, [](boca::Photon const & photon) {
            return photon.Pt() > 10_GeV;
        });
        return number_hard_jets >= 2 && number_hard_photons >= 2 ?  1 : 0;
    }

};

}
