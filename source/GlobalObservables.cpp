/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
// #include <numeric>
#include <boost/range/numeric.hpp>
#include <boost/range/algorithm/count_if.hpp>

#include "GlobalObservables.hh"
#include "Event.hh"
#include "Sort.hh"
#include "DEBUG.hh"

namespace boca
{

GlobalObservables::GlobalObservables() {}

GlobalObservables::GlobalObservables(const Event& event)
{
    SetEvent(event);
}

GlobalObservables::GlobalObservables(const Event& event, const std::vector<boca::Jet>& jets)
{
    SetEvent(event, jets);
}

void GlobalObservables::SetEvent(boca::Event const& event, const std::vector<boca::Jet>& jets)
{
    SetJets(jets);
    SetLeptons(event.Leptons().leptons());
    scalar_ht_ = event.Hadrons().ScalarHt();
    missing_et_ = event.Hadrons().MissingEt().Pt();
}

void GlobalObservables::SetEvent(boca::Event const& event)
{
    SetJets(event.Hadrons().Jets());
    SetLeptons(event.Leptons().leptons());
    scalar_ht_ = event.Hadrons().ScalarHt();
    missing_et_ = event.Hadrons().MissingEt().Pt();
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

double GlobalObservables::BottomBdt() const
{
    INFO0;
    if (Jets().empty()) return -1;
    return boost::accumulate(jets_, 0., [](double bdt, boca::Jet const & jet) {
        return bdt + jet.Info().Bdt();
    }) / JetNumber();
}

double GlobalObservables::BottomBdt(int number) const
{
    INFO0;
    if (number > JetNumber()) return -1;
    return Jets().at(number - 1).Info().Bdt();
}

double GlobalObservables::BottomBdt(int number_1, int number_2) const
{
    INFO0;
    if (number_1 > JetNumber()) return 0;
    if (number_2 > JetNumber()) return 0;
    return (Jets().at(number_1 - 1).Info().Bdt() + Jets().at(number_2 - 1).Info().Bdt()) / 2;
}

Momentum GlobalObservables::ScalarHt() const
{
    INFO0;
    return scalar_ht_;
}

Momentum GlobalObservables::LeptonHt() const
{
    INFO0;
    return boost::accumulate(leptons_, 0_eV, [](Momentum ht, boca::Jet const & lepton) {
        return ht + lepton.Pt();
    });
}

Momentum GlobalObservables::JetHt() const
{
    INFO0;
    return boost::accumulate(jets_, 0_eV, [](Momentum ht, boca::Jet const & jet) {
        return ht + jet.Pt();
    });
}

Energy GlobalObservables::MissingEt() const
{
    INFO0;
    return missing_et_;
}

Singlet GlobalObservables::Singlet() const
{
    INFO0;
    boca::Jet jet = Join(Jets());
    jet.Info().SetBdt(BottomBdt());
    return boca::Singlet(jet);
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

Momentum GlobalObservables::JetPt(int number) const
{
    return jets_.size() >= number ? jets_.at(number - 1).Pt() : at_rest;
}

Momentum GlobalObservables::LeptonPt(int number) const
{
    return leptons_.size() >= number ? leptons_.at(number - 1).Pt() : at_rest;
}
Momentum GlobalObservables::Ht() const
{
    return ScalarHt();
}

int GlobalObservables::Charge() const
{
    return 0; // FIXME implement this
}

Jet GlobalObservables::Jet() const
{
    return Join(Jets());
}

const Singlet& GlobalObservables::ConstituentJet() const
{
    if (!has_singlet_) {
        singlet_ = Join(Jets());
        has_singlet_ = true;
    }
    return singlet_;
}

Mass GlobalObservables::Mass() const
{
    return Jet().Mass();
}
Angle GlobalObservables::DeltaRTo(const PseudoJet& jet) const
{
    return Jet().DeltaRTo(jet);
}

}
