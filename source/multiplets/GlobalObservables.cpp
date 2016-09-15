/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include <boost/range/numeric.hpp>
#include <boost/range/algorithm/count_if.hpp>

#include "boca/multiplets/GlobalObservables.hh"
#include "boca/Event.hh"
#include "boca/multiplets/Sort.hh"
#include "boca/generic/Vector.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

GlobalObservables::GlobalObservables() {}

GlobalObservables::GlobalObservables(Event const& event)
{
    SetEvent(event);
}

GlobalObservables::GlobalObservables(Event const& event, const std::vector<boca::Jet>& jets)
{
    SetEvent(event, jets);
}

void GlobalObservables::SetEvent(boca::Event const& event, const std::vector<boca::Jet>& jets)
{
    SetJets(jets);
    SetLeptons(event.Leptons());
    scalar_ht_ = event.ScalarHt();
    missing_et_ = event.MissingEt().Pt();
}

void GlobalObservables::SetEvent(boca::Event const& event)
{
    SetJets(event.Jets());
    SetLeptons(event.Leptons());
    scalar_ht_ = event.ScalarHt();
    missing_et_ = event.MissingEt().Pt();
}

int GlobalObservables::LeptonNumber() const
{
    INFO0;
    return leptons_.size();
}

int GlobalObservables::JetNumber() const
{
    INFO0;
    return Jets().size();
}

int GlobalObservables::BottomNumber() const
{
    INFO0;
    return boost::range::count_if(Jets(), [](boca::Jet const & jet) {
        return jet.Info().Bdt() > 0.05;
    });
}

Momentum GlobalObservables::ScalarHt() const
{
    INFO0;
    return scalar_ht_;
}

Momentum GlobalObservables::LeptonHt() const
{
    INFO0;
    return boost::accumulate(leptons_, 0_eV, [](Momentum const& ht, boca::Jet const & lepton) {
        return ht + lepton.Pt();
    });
}

Momentum GlobalObservables::JetHt() const
{
    INFO0;
    return boost::accumulate(jets_, 0_eV, [](Momentum const& ht, boca::Jet const & jet) {
        return ht + jet.Pt();
    });
}

Energy GlobalObservables::MissingEt() const
{
    INFO0;
    return missing_et_;
}

std::vector<Jet> GlobalObservables::Jets() const
{
    INFO0;
    return jets_;
}

void GlobalObservables::SetJets(std::vector<boca::Jet> const& jets)
{
    INFO0;
    jets_ = SortedByPt(jets);
}

void GlobalObservables::SetLeptons(std::vector<Lepton> const& leptons)
{
    INFO0;
    leptons_ = SortedByPt(leptons);
}

Momentum GlobalObservables::JetPt(std::size_t number) const
{
    return jets_.size() > number ? jets_.at(number).Pt() : at_rest;
}

Momentum GlobalObservables::LeptonPt(std::size_t number) const
{
    return leptons_.size() > number ? leptons_.at(number).Pt() : at_rest;
}

Momentum GlobalObservables::Ht() const
{
    return ScalarHt();
}

int GlobalObservables::Charge() const
{
    return boost::accumulate(Jets(), 0, [](int sum, boca::Jet const & jet) {
        return sum + jet.Info().Charge();
    });
}

Jet GlobalObservables::Jet() const
{
    return jet_.Get([this]() {
        return Join(Jets());
    });
}

Singlet GlobalObservables::ConstituentJet() const
{
    return constituent_jet_.Get([this]() {
      return Join(boost::accumulate(Jets(), std::vector<boca::Jet>{}, [](std::vector<boca::Jet>& sum, boca::Jet const & jet) {
            return Combine(sum, jet.Constituents());
        }));
    });
}

Mass GlobalObservables::Mass() const
{
    return Jet().Mass();
}
Angle GlobalObservables::DeltaRTo(PseudoJet const& jet) const
{
    return Jet().DeltaRTo(jet);
}

std::vector< Jet > GlobalObservables::Constituents() const
{
    return ConstituentJet().Constituents();
}
std::vector< LorentzVector< Momentum > > GlobalObservables::LorentzVectors() const
{
    return {};
}


}
