/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include <boost/range/numeric.hpp>
#include <boost/range/algorithm/count_if.hpp>

#include "boca/Event.hh"
#include "boca/multiplets/Sort.hh"
#include "boca/generic/Vector.hh"
#include "boca/generic/DEBUG_MACROS.hh"

#include "tthh/Observables.hh"

namespace tthh {

using namespace boca::units;

Observables::Observables(boca::Event const& event)
{
    jets_ = SortedByPt(event.Jets());
    leptons_ = SortedByPt(event.Leptons());
    photons_ = SortedByPt(event.Photons());
    scalar_ht_ = event.ScalarHt();
    missing_et_ = event.MissingEt().Pt();
}

int Observables::LeptonNumber() const
{
    INFO0;
    return leptons_.size();
}

int Observables::JetNumber() const
{
    INFO0;
    return Jets().size();
}

int Observables::BottomNumber() const
{
    INFO0;
    return boost::range::count_if(Jets(), [](boca::Jet const & jet) {
        return jet.Info().BTag();
    });
    return boost::range::count_if(Jets(), [](boca::Jet const & jet) {
        return jet.Info().Bdt() > 0.05;
    });
}

boca::Momentum Observables::ScalarHt() const
{
    INFO0;
    return scalar_ht_;
}

boca::Momentum Observables::LeptonHt() const
{
    INFO0;
    return boost::accumulate(leptons_, 0_eV, [](boca::Momentum const& ht, boca::Lepton const & lepton) {
        return ht + lepton.Pt();
    });
}

boca::Momentum Observables::JetHt() const
{
    INFO0;
    return boost::accumulate(jets_, 0_eV, [](boca::Momentum const& ht, boca::Jet const & jet) {
        return ht + jet.Pt();
    });
}

boca::Energy Observables::MissingEt() const
{
    INFO0;
    return missing_et_;
}

std::vector<boca::Jet> Observables::Jets() const
{
    INFO0;
    return jets_;
}

boca::Momentum Observables::JetPt(unsigned number) const
{
    return jets_.size() > number ? jets_.at(number).Pt() : boca::at_rest;
}

boca::Momentum Observables::PhotonPt(unsigned number) const
{
    return photons_.size() > number ? photons_.at(number).Pt() : boca::at_rest;
}

boca::Momentum Observables::LeptonPt(unsigned number) const
{
    return leptons_.size() > number ? leptons_.at(number).Pt() : boca::at_rest;
}

boca::Mass Observables::PhotonPM() const
{
    return photons_.size() > 1 ? (photons_.at(0) + photons_.at(1)).Mass() : boca::at_rest;
}

boca::Momentum Observables::Ht() const
{
    return ScalarHt();
}


}
