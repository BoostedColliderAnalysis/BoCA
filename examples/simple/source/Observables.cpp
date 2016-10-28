#include <boost/range/algorithm/count_if.hpp>

#include "boca/fastjet/Sort.hh"

#include "simple/Observables.hh"

namespace simple
{

// Get the basic objects from the event
Observables::Observables(boca::Event const& event)
{
    // store the jets sorted by pt
    jets_ = SortedByPt(event.Jets());
    // store the leptons sorted by pt
    leptons_ = SortedByPt(event.Leptons());
    // store the scalar ht
    scalar_ht_ = event.ScalarHt();
    // store the missing et
    missing_et_ = event.MissingEt().Pt();
}

int Observables::LeptonNumber() const
{
    //  return the number of leptons
    return leptons_.size();
}

int Observables::JetNumber() const
{
    //  return the number of jets
    return jets_.size();
}

int Observables::BottomNumber() const
{
    // return the number of jets with Delphes b-tag
    return boost::range::count_if(jets_, [](boca::Jet const & jet) {
        return jet.Info().BTag();
    });
}

boca::Momentum Observables::ScalarHt() const
{
    // return scalar_ht
    return scalar_ht_;
}

boca::Energy Observables::MissingEt() const
{
    //  return missing et
    return missing_et_;
}

boca::Momentum Observables::JetPt(unsigned number) const
{
    //  return pt of jet at number
    return jets_.size() > number ? jets_.at(number).Pt() : boca::at_rest;
}

boca::Momentum Observables::LeptonPt(unsigned number) const
{
    //  return pt of lepton at number
    return leptons_.size() > number ? leptons_.at(number).Pt() : boca::at_rest;
}

}
