/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include <boost/range/numeric.hpp>
#include <boost/range/algorithm/count_if.hpp>

#include "boca/multiplets/Global.hh"
#include "boca/event/Event.hh"
#include "boca/fastjet/Sort.hh"
#include "boca/generic/Vector.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

Global::Global() {}

Global::Global(Event const& event)
{
    SetEvent(event);
}

Global::Global(Event const& event, const std::vector<boca::Jet>& jets)
{
    SetEvent(event, jets);
}

void Global::SetEvent(boca::Event const& event, const std::vector<boca::Jet>& jets)
{
    SetJets(jets);
    SetLeptons(event.Leptons());
    scalar_ht_ = event.ScalarHt();
    missing_et_ = event.MissingEt().Pt();
}

void Global::SetEvent(boca::Event const& event)
{
    SetJets(event.Jets());
    SetLeptons(event.Leptons());
    scalar_ht_ = event.ScalarHt();
    missing_et_ = event.MissingEt().Pt();
}

int Global::LeptonNumber() const
{
    INFO0;
    return leptons_.size();
}

int Global::JetNumber() const
{
    INFO0;
    return Jets().size();
}

int Global::BottomNumber() const
{
    INFO0;
    return boost::range::count_if(Jets(), [](boca::Jet const & jet) {
        return jet.Info().Bdt() > 0.05;
    });
}

Momentum Global::ScalarHt() const
{
    INFO0;
    return scalar_ht_;
}

Momentum Global::LeptonHt() const
{
    INFO0;
    return boost::accumulate(leptons_, 0_eV, [](Momentum const& ht, boca::Jet const & lepton) {
        return ht + lepton.Pt();
    });
}

Momentum Global::JetHt() const
{
    INFO0;
    return boost::accumulate(jets_, 0_eV, [](Momentum const& ht, boca::Jet const & jet) {
        return ht + jet.Pt();
    });
}

Energy Global::MissingEt() const
{
    INFO0;
    return missing_et_;
}

std::vector<Jet> Global::Jets() const
{
    INFO0;
    return jets_;
}

void Global::SetJets(std::vector<boca::Jet> const& jets)
{
    INFO0;
    jets_ = SortedByPt(jets);
}

void Global::SetLeptons(std::vector<Lepton> const& leptons)
{
    INFO0;
    leptons_ = SortedByPt(leptons);
}

Momentum Global::JetPt(std::size_t number) const
{
    return jets_.size() > number ? jets_.at(number).Pt() : at_rest;
}

Momentum Global::LeptonPt(std::size_t number) const
{
    return leptons_.size() > number ? leptons_.at(number).Pt() : at_rest;
}

Momentum Global::Ht() const
{
    return ScalarHt();
}

int Global::Charge() const
{
    return boost::accumulate(Jets(), 0, [](int sum, boca::Jet const & jet) {
        return sum + jet.Info().Charge();
    });
}

Jet Global::Jet() const
{
    return jet_.Get([this]() {
        return Join(Jets());
    });
}

Singlet Global::ConstituentJet() const
{
    return constituent_jet_.Get([this]() {
      return Join(boost::accumulate(Jets(), std::vector<boca::Jet>{}, [](std::vector<boca::Jet>& sum, boca::Jet const & jet) {
            return Combine(sum, jet.Constituents());
        }));
    });
}

Mass Global::Mass() const
{
    return Jet().Mass();
}
Angle Global::DeltaRTo(PseudoJet const& jet) const
{
    return Jet().DeltaRTo(jet);
}

std::vector< Jet > Global::Constituents() const
{
    return ConstituentJet().Constituents();
}
std::vector< LorentzVector< Momentum > > Global::LorentzVectors() const
{
    return {};
}


}
