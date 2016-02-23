/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
// #include <numeric>
#include <boost/range/numeric.hpp>

#include "GlobalObservables.hh"
#include "Event.hh"
#include "Debug.hh"

namespace boca
{

void GlobalObservables::SetEvent(boca::Event const& event, const std::vector<Jet>&)
{
    leptons_ = event.Leptons().leptons();
    scalar_ht_ = event.Hadrons().ScalarHt();
    missing_et_ = event.Hadrons().MissingEt().Pt();
}

void GlobalObservables::SetEvent(boca::Event const& event)
{
    leptons_ = event.Leptons().leptons();
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
    std::vector<Jet> bottoms;
    for (auto const & jet : Jets()) if (jet.Info().Bdt() > 0) bottoms.emplace_back(jet);
    return bottoms.size();
}

float GlobalObservables::BottomBdt() const
{
    INFO0;
    if(Jets().empty()) return -1;
    return boost::accumulate(jets_, 0., [](float bdt, Jet const & jet) {
        return bdt + jet.Info().Bdt();
    }) / JetNumber();
}

float GlobalObservables::BottomBdt(int number) const
{
    INFO0;
    if (number > JetNumber()) return -1;
    return Jets().at(number - 1).Info().Bdt();
}

float GlobalObservables::BottomBdt(int number_1, int number_2) const
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
    return boost::accumulate(leptons_, 0_eV, [](Momentum ht, Jet const & lepton) {
        return ht + lepton.Pt();
    });
}

Momentum GlobalObservables::JetHt() const
{
    INFO0;
    return boost::accumulate(jets_, 0_eV, [](Momentum ht, Jet const & jet) {
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
    Jet jet = Join(Jets());
    jet.Info().SetBdt(BottomBdt());
    return boca::Singlet(jet);
}

std::vector<Jet> GlobalObservables::Jets() const
{
    INFO0;
    return jets_;
}

void GlobalObservables::SetJets(const std::vector<Jet> jets)
{
    INFO0;
    jets_ = jets;
}

}
