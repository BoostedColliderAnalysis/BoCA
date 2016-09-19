#pragma once

#include "boca/analysis/Analysis.hh"

#include <boost/range/algorithm/count_if.hpp>

namespace tthh {

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
            boca::analysis::Base::NewFile(tag, "hhbbaa_sig", "hh");
            break;
        case boca::Tag::background :
            // put your background file here
            boca::analysis::Base::NewFile(tag, "bbaa_bkg", "bbaa");
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
    
    std::string FilePath() const override{
    return this->WorkingPath() + "../events/";
    }
    
    
    int PassPreCut(boca::Event const &event, boca::Tag) const override
    {
        auto jets = event.Jets();
        auto number_hard_jets = boost::range::count_if(jets, [](boca::Jet const & jet) {
            return jet.Pt() > 10_GeV;
        });
//        return number_hard_jets >= 2  ?  1 : 0;
        auto photons = event.Photons();
        auto number_hard_photons = boost::range::count_if(photons, [](boca::Lepton const & photon) {
            return photon.Pt() > 10_GeV;
        });
        return number_hard_jets >= 2 && number_hard_photons >= 2 ?  1 : 0;
    }


};

}
