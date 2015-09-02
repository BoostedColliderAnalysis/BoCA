/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "GlobalObservables.hh"
#include "InfoRecombiner.hh"
#include "Event.hh"
#include "Debug.hh"
#include <numeric>

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
    Info();
    return leptons_.size();
}

int GlobalObservables::JetNumber() const
{
    Info();
    return Jets().size();
}

int GlobalObservables::BottomNumber() const
{
    Info();
    boca::Jets bottoms;
    for (auto const& jet : Jets()) if (jet.user_info<JetInfo>().Bdt() > 0)
            bottoms.emplace_back(jet);
    return bottoms.size();
}

float GlobalObservables::BottomBdt() const
{
    Info();
    if (Jets().empty())
        return 0;
    return std::accumulate(jets_.begin(), jets_.end(), 0., [](float bdt, fastjet::PseudoJet const& jet) {
        return bdt + jet.user_info<JetInfo>().Bdt();
    }) / JetNumber();
}

float GlobalObservables::BottomBdt(int number) const
{
    Info();
    if (number > JetNumber())
        return 0;
    return Jets().at(number - 1).user_info<JetInfo>().Bdt();
}

float GlobalObservables::BottomBdt(int number_1, int number_2) const
{
    Info();
    if (number_1 > JetNumber())
        return 0;
    if (number_2 > JetNumber())
        return 0;
    return (Jets().at(number_1 - 1).user_info<JetInfo>().Bdt() + Jets().at(number_2 - 1).user_info<JetInfo>().Bdt()) / 2;
}

float GlobalObservables::ScalarHt() const
{
    Info();
    return scalar_ht_;
}

float GlobalObservables::LeptonHt() const
{
    Info();
    if (leptons_.empty())
        return 0;
    return std::accumulate(leptons_.begin(), leptons_.end(), 0., [](float ht, fastjet::PseudoJet const& lepton) {
        return ht + lepton.pt();
    });
}

float GlobalObservables::JetHt() const
{
    Info();
    if (Jets().empty())
        return 0;
    return std::accumulate(jets_.begin(), jets_.end(), 0., [](float ht, fastjet::PseudoJet const& jet) {
        return ht + jet.pt();
    });
}

float GlobalObservables::MissingEt() const
{
    Info();
    return missing_et_;
}

Singlet GlobalObservables::Singlet() const
{
    Info();
    fastjet::PseudoJet jet(fastjet::join(Jets(),InfoRecombiner()));
    jet.set_user_info(new JetInfo(BottomBdt()));
    return boca::Singlet(jet);
}

Jets GlobalObservables::Jets() const
{
    Info();
    return jets_;
}

void GlobalObservables::SetJets(const boca::Jets jets)
{
    Info();
    jets_ = jets;
}

}
