#pragma once

#include "boca/branch/Bdt.hh"
#include "boca/units/Prefixes.hh"

namespace toppartner
{

using namespace boca;

namespace branch
{

/**
 *
 * @brief Top tagger root tree structure
 *
 */
class Truth : public boca::branch::Bdt
{
public:
    Truth();
    float top_pt;
    float lepton_pt;
    float boson_number;
    float hard_boson_number;
    float softest_boson_pt;
    float hardest_boson_pt;
    float detectable_boson_number;
    float boson_delta_r_min;
    float missing_et;
    float scalar_ht;
    float jet_pt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        top_pt = multiplet.TopPt(0) / GeV;
        lepton_pt = multiplet.LeptonPt(0) / GeV;
        boson_number = multiplet.BosonNumber();
        hard_boson_number = multiplet.HardBosonNumber();
        softest_boson_pt = multiplet.SoftBosonPt() / GeV;
        hardest_boson_pt = multiplet.HardBosonPt() / GeV;
        detectable_boson_number = multiplet.DetectableBosonNumber();
        boson_delta_r_min = multiplet.BosonDeltaRMin() / rad;
        missing_et = multiplet.MissingEt() / GeV;
        scalar_ht = multiplet.ScalarHt() / GeV;
        jet_pt = multiplet.JetPt(0) / GeV;
    }
    virtual boca::Observables Variables();
private:
    ClassDef(Truth, 1)
};

}

}
