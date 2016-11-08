#pragma once

#include "boca/fastjet/Vector.hh"
#include "boca/analysis/Analysis.hh"
#include "boca/generic/DEBUG_MACROS.hh"

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
        return "SimpleAnalysis-Cut2";
    }

    bool PassPreCut(boca::Event const &event) const override
    {
        return true;
        auto number_hard_leptons = CountIfHard(event.Leptons(), 20_GeV);
        static auto ievent = 0;
        ++ievent;
        static auto two_leptons = 0;
        if (number_hard_leptons >= 1) {
            ++two_leptons;
            auto fraction = static_cast<double>(two_leptons) / ievent;
            ERROR(two_leptons, ievent,  fraction);
            return true;
        };
        return false;

        return number_hard_leptons >= 2 ?  true : false;

        auto number_hard_jets = CountIfHard(event.Jets(), 20_GeV);
        auto number_hard_photons = CountIfHard(event.Photons(), 20_GeV);
        return number_hard_jets >= 2 && number_hard_photons >= 2 ?  true : false;
    }

};

}
