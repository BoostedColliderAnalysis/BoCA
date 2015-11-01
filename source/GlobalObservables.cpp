/**
 * Copyright (C) 2015 Jan Hajer
 */
// #include <numeric>
#include <boost/range/numeric.hpp>

#include "GlobalObservables.hh"
#include "InfoRecombiner.hh"
#include "Event.hh"
#include "Debug.hh"

namespace boca {

void GlobalObservables::SetEvent(boca::Event const& event, const boca::Jets&)
{
    leptons_ = event.Leptons().leptons();
    scalar_ht_ = event.Hadrons().ScalarHt();
    missing_et_ = event.Hadrons().MissingEt().pt();
}

void GlobalObservables::SetEvent(boca::Event const& event)
{
  leptons_ = event.Leptons().leptons();
  scalar_ht_ = event.Hadrons().ScalarHt();
  missing_et_ = event.Hadrons().MissingEt().pt();
}

int GlobalObservables::LeptonNumber() const
{
    Info0;
    return leptons_.size();
}

int GlobalObservables::JetNumber() const
{
    Info0;
    return Jets().size();
}

int GlobalObservables::BottomNumber() const
{
    Info0;
    boca::Jets bottoms;
    for (auto const& jet : Jets()) if (jet.user_info<JetInfo>().Bdt() > 0)
            bottoms.emplace_back(jet);
    return bottoms.size();
}

float GlobalObservables::BottomBdt() const
{
    Info0;
    return boost::accumulate(jets_, 0., [](float bdt, fastjet::PseudoJet const& jet) {
        return bdt + jet.user_info<JetInfo>().Bdt();
    }) / JetNumber();
}

float GlobalObservables::BottomBdt(int number) const
{
    Info0;
    if (number > JetNumber())
        return 0;
    return Jets().at(number - 1).user_info<JetInfo>().Bdt();
}

float GlobalObservables::BottomBdt(int number_1, int number_2) const
{
    Info0;
    if (number_1 > JetNumber())
        return 0;
    if (number_2 > JetNumber())
        return 0;
    return (Jets().at(number_1 - 1).user_info<JetInfo>().Bdt() + Jets().at(number_2 - 1).user_info<JetInfo>().Bdt()) / 2;
}

float GlobalObservables::ScalarHt() const
{
    Info0;
    return scalar_ht_;
}

float GlobalObservables::LeptonHt() const
{
    Info0;
    return boost::accumulate(leptons_, 0., [](float ht, fastjet::PseudoJet const& lepton) {
        return ht + lepton.pt();
    });
}

float GlobalObservables::JetHt() const
{
    Info0;
    return boost::accumulate(jets_, 0., [](float ht, fastjet::PseudoJet const& jet) {
        return ht + jet.pt();
    });
}

float GlobalObservables::MissingEt() const
{
    Info0;
    return missing_et_;
}

Singlet GlobalObservables::Singlet() const
{
    Info0;
    fastjet::PseudoJet jet(fastjet::join(Jets(),InfoRecombiner()));
    jet.set_user_info(new JetInfo(BottomBdt()));
    return boca::Singlet(jet);
}

Jets GlobalObservables::Jets() const
{
    Info0;
    return jets_;
}

void GlobalObservables::SetJets(const boca::Jets jets)
{
    Info0;
    jets_ = jets;
}

}
