/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "JetInfo.hh"

#include <boost/range/algorithm/max_element.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/algorithm_ext/erase.hpp>

#include "delphes/Delphes.hh"
#include "Vector.hh"
#include "Math.hh"
#include "Types.hh"

// #define DEBUG
#include "Debug.hh"

namespace boca
{

JetInfo::JetInfo()
{
    Debug();
}

JetInfo::JetInfo(float bdt)
{
    Debug();
    SetBdt(bdt);
}

void JetInfo::SetDelphesTags(::delphes::Jet const& jet)
{
    Debug();
    SetBTag(jet.BTag);
    SetTauTag(jet.TauTag);
    SetCharge(jet.Charge);
}

JetInfo::JetInfo(::delphes::Jet const& jet)
{
    Debug();
    SetDelphesTags(jet);
}

JetInfo::JetInfo(int charge)
{
    Debug();
    SetCharge(charge);
}

JetInfo::JetInfo(Constituent const& constituent)
{
    Debug();
    SetConstituent(constituent);
}

JetInfo::JetInfo(Constituent const& constituent, int charge)
{
    Debug();
    SetConstituent(constituent);
    SetCharge(charge);
}

JetInfo::JetInfo(std::vector<Constituent> const& constituents)
{
    Debug();
    SetConstituents(constituents);
}

JetInfo::JetInfo(std::vector<Constituent> const& constituents, std::vector<Constituent> const& displaced_constituents)
{
    Debug();
    constituents_ = constituents;
    displaced_constituents_ = displaced_constituents;
}

JetInfo JetInfo::operator+(JetInfo const& jet_info)
{
    Debug();
    JetInfo result(Join(this->constituents(), jet_info.constituents()), Join(this->displaced_constituents(), jet_info.displaced_constituents()));
    result.SetBTag(this->BTag() + jet_info.BTag());
    result.SetTauTag(this->TauTag() + jet_info.TauTag());
    result.SetCharge(this->Charge() + jet_info.Charge());
    return result;
}

JetInfo& JetInfo::operator+=(JetInfo const& jet_info)
{
    Debug();
    this->AddConstituents(jet_info.constituents(), jet_info.displaced_constituents());
    this->b_tag_ += jet_info.BTag();
    this->tau_tag_ += jet_info.TauTag();
    this->charge_ += jet_info.Charge();
    return *this;
}


void JetInfo::SetConstituent(Constituent const& constituent)
{
    Debug();
    constituents_.emplace_back(constituent);
    if (VertexResultion(constituent)) displaced_constituents_.emplace_back(constituent);
}

void JetInfo::SetConstituents(std::vector<Constituent> const& constituents)
{
    Debug();
    constituents_ = constituents;
    displaced_constituents_ = ApplyVertexResolution(constituents);
}

void JetInfo::AddConstituent(Constituent const& constituent)
{
    Debug();
    constituents_.emplace_back(constituent);
    if (VertexResultion(constituent)) displaced_constituents_.emplace_back(constituent);
}

void JetInfo::AddConstituents(std::vector<Constituent> const& constituents)
{
    Debug();
    constituents_ = Join(constituents_, constituents);
    displaced_constituents_ = Join(displaced_constituents_, ApplyVertexResolution(constituents));
}

void JetInfo::AddConstituents(std::vector<Constituent> const& constituents, std::vector<Constituent> const& displaced_constituents)
{
    Debug();
    constituents_ = Join(constituents_, constituents);
    displaced_constituents_ = Join(displaced_constituents_, displaced_constituents);
}

std::vector<Constituent> JetInfo::constituents() const
{
    Debug();
    return constituents_;
}

std::vector<Constituent> JetInfo::displaced_constituents() const
{
    Debug();
    return displaced_constituents_;
}

int JetInfo::VertexNumber() const
{
    Debug();
    return displaced_constituents_.size();
}

fastjet::PseudoJet JetInfo::VertexJet() const
{
    Debug();
    Jets jets;
    for (auto const & consituent : displaced_constituents_) jets.emplace_back(PseudoJet(consituent.Momentum()));
    return fastjet::join(jets);
}

Length JetInfo::SumDisplacement() const
{
    Debug();
    if (displaced_constituents_.empty()) return 0. * mm;
    return boost::accumulate(displaced_constituents_, 0. * mm, [](Length result, Constituent const & constituent) {
        return (result + 1. * constituent.Position().Vect().Perp() * mm);
    });
}

Length JetInfo::MeanDisplacement() const
{
    Debug();
    if (displaced_constituents_.empty()) return 0. * mm;
    return SumDisplacement() / double(displaced_constituents_.size());
}

Length JetInfo::MaxDisplacement() const
{
    Debug();
    if(displaced_constituents_.empty()) return 0. * mm;
    return 1. * (*boost::max_element(displaced_constituents_, [](Constituent const & constituent_1, Constituent const & constituent_2) {
        return constituent_1.Position().Vect().Perp() > constituent_2.Position().Vect().Perp();
    })).Position().Vect().Perp() * mm;
}

Mass JetInfo::VertexMass() const
{
    Debug();
    Mass vertex_mass = 1. * boost::accumulate(displaced_constituents_, LorentzVector(), [](LorentzVector const & momentum, Constituent const & constituent) {
        return momentum + constituent.Momentum();
    }).M() * GeV;
    Debug(vertex_mass);
    if (vertex_mass < DetectorGeometry::VertexMassMin()) return massless;
    return vertex_mass;
}

Energy JetInfo::VertexEnergy() const
{
    Debug();
    return 1. * boost::accumulate(displaced_constituents_, Constituent()).Momentum().E() * GeV;
}

std::vector<Constituent> JetInfo::ApplyVertexResolution(std::vector<Constituent> constituents) const
{
    Debug(constituents.size());
    if (constituents.empty()) return constituents;
    std::vector <Constituent> displaced_constituents;
    for (auto const & constituent : constituents) if (VertexResultion(constituent)) displaced_constituents.emplace_back(constituent);
    Debug(displaced_constituents.size());
    return displaced_constituents;
}

bool JetInfo::VertexResultion(Constituent const& constituent) const
{
    Debug(constituent.Position().Perp());
    return (1. * constituent.Position().Vect().Perp() * mm > DetectorGeometry::TrackerDistanceMin() & 1. * constituent.Position().Vect().Perp() * mm < DetectorGeometry::TrackerDistanceMax() & boost::units::abs(1. * constituent.Momentum().Rapidity() * rad) < DetectorGeometry::TrackerEtaMax());
}

float JetInfo::ElectroMagneticRadius(fastjet::PseudoJet const& jet) const
{
    Debug();
    float energy = 0;
    float weight = 0;
    for (auto const & constituent : constituents()) if (constituent.sub_detector() == SubDetector::photon) {
            energy += constituent.Momentum().Et();
            weight += constituent.Momentum().Et() * jet.delta_R(fastjet::PseudoJet(constituent.Momentum()));
        }
    if (energy == 0) return 0;
    else return weight / energy;
}

float JetInfo::TrackRadius(fastjet::PseudoJet const& jet) const
{
    Debug();
    float energy = 0;
    float weight = 0;
    for (auto const & constituent : constituents()) if (constituent.sub_detector() == SubDetector::track) {
            energy += constituent.Momentum().Et();
            weight += constituent.Momentum().Et() * jet.delta_R(fastjet::PseudoJet(constituent.Momentum()));
        }
    if (energy == 0) return 0;
    else return weight / energy;
}

struct IsDetector {
    IsDetector(SubDetector sub_detector) {
        sub_detector_ = sub_detector;
    }
    bool operator()(Constituent const& constituent) {
        return constituent.sub_detector() != sub_detector_;
    }
    SubDetector sub_detector_;
};

float JetInfo::LeadingTrackMomentumFraction() const
{
    Debug();
    std::vector<Constituent> consts = constituents();
    consts = boost::range::remove_erase_if(consts, IsDetector(SubDetector::track));
    std::sort(consts.begin(), consts.end(), [](Constituent const & constituent_1, Constituent const & constituent_2) {
        return (constituent_1.Momentum().Pt() > constituent_2.Momentum().Pt());
    });
    float sum = boost::accumulate(consts, 0, [](float result, Constituent const & constituent) {
        return (result + constituent.Momentum().Pt());
    });
    return consts.front().Momentum().Pt() / sum;
}

float JetInfo::CoreEnergyFraction(fastjet::PseudoJet const& jet) const
{
    Debug();
    float energy = 0;
    float core_energy = 0;
    for (auto const & constituent : constituents()) if (constituent.sub_detector() == SubDetector::photon) {
            energy += constituent.Momentum().Et();
            if (jet.delta_R(fastjet::PseudoJet(constituent.Momentum())) < 0.2) core_energy += constituent.Momentum().Et();
        }
    if (energy == 0) return 0;
    else
        return core_energy / energy;
}

float JetInfo::ElectroMagneticFraction() const
{
    Debug();
    float em_energy = 0;
    float energy = 0;
    for (auto const & constituent : constituents()) {
        energy += constituent.Momentum().Et();
        if (constituent.sub_detector() == SubDetector::photon)
            em_energy += constituent.Momentum().Et();
    }
    if (energy == 0)
        return 0;
    else
        return em_energy / energy;
}

float JetInfo::ClusterMass() const
{
    Debug();
    fastjet::PseudoJet jet;
    for (auto const & constituent : constituents()) if (constituent.sub_detector() == SubDetector::photon)
            jet += constituent.Momentum();
    return jet.m();
}

float JetInfo::TrackMass() const
{
    Debug();
    fastjet::PseudoJet jet;
    for (auto const & constituent : constituents()) if (constituent.sub_detector() == SubDetector::track)
            jet += constituent.Momentum();
    return jet.m();
}

int JetInfo::Charge() const
{
    Debug();
    if (charge_ != LargeNumber()) return charge_;
    int charge = boost::accumulate(constituents_, 0, [](int charge, Constituent const & constituent) {
        return charge + constituent.charge();
    });
    return charge;
}
void JetInfo::SetCharge(int charge)
{
    Debug();
    charge_ = charge;
}
bool JetInfo::TauTag() const
{
    Debug();
    return tau_tag_;
}
void JetInfo::SetTauTag(bool tau_tag)
{
    Debug();
    tau_tag_ = tau_tag;
}
bool JetInfo::BTag() const
{
    Debug();
    return b_tag_;
}
void JetInfo::SetBTag(bool b_tag)
{
    Debug();
    b_tag_ = b_tag;
}
// Family JetInfo::Family() const
// {
//     return constituents().front().family();
// }

void JetInfo::SecondayVertex() const
{
    Debug();
    auto leading = boost::range::max_element(constituents_, [](Constituent const & consituent_1, Constituent const & constituent_2) {
        return consituent_1.Momentum().Pt() < constituent_2.Momentum().Pt();
    });
    float x = (*leading).Position().X();
    float y = (*leading).Position().Y();
    float radius = (*leading).Position().Perp() / 2;
    std::vector<Constituent> constituents;
    auto constituent = std::copy_if(constituents_.begin(), constituents_.end(), constituents.begin(), [&](Constituent const & constituent) {
        return (constituent.Position().X() < x + radius && constituent.Position().X() > x - radius && constituent.Position().Y() < y + radius && constituent.Position().Y() > y - radius);
    });
    constituents.resize(std::distance(constituents.begin(), constituent));
}

}
