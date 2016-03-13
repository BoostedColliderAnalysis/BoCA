/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "JetInfo.hh"

#include <boost/range/algorithm/max_element.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/algorithm_ext/erase.hpp>

#include "delphes/Delphes.hh"
#include "Vector.hh"
#include "physics/Math.hh"
#include "Types.hh"

// #define DEBUGGING
#include "DEBUG.hh"

namespace boca
{

JetInfo::JetInfo()
{
    DEBUG0;
}

JetInfo::JetInfo(float bdt)
{
    DEBUG0;
    SetBdt(bdt);
}

void JetInfo::SetDelphesTags(::delphes::Jet const& jet)
{
    DEBUG0;
    SetBTag(jet.BTag);
    SetTauTag(jet.TauTag);
    SetCharge(jet.Charge);
}

JetInfo::JetInfo(::delphes::Jet const& jet)
{
    DEBUG0;
    SetDelphesTags(jet);
}

JetInfo::JetInfo(int charge)
{
    DEBUG0;
    SetCharge(charge);
}

JetInfo::JetInfo(Constituent const& constituent)
{
    DEBUG0;
    SetConstituent(constituent);
}

JetInfo::JetInfo(Constituent const& constituent, int charge)
{
    DEBUG0;
    SetConstituent(constituent);
    SetCharge(charge);
}

JetInfo::JetInfo(std::vector<Constituent> const& constituents)
{
    DEBUG0;
    SetConstituents(constituents);
}

JetInfo::JetInfo(std::vector<Constituent> const& constituents, std::vector<Constituent> const& displaced_constituents)
{
    DEBUG0;
    constituents_ = constituents;
    displaced_constituents_ = displaced_constituents;
}

JetInfo JetInfo::operator+(JetInfo const& jet_info)
{
    DEBUG0;
    JetInfo result(Join(this->Constituents(), jet_info.Constituents()), Join(this->DisplacedConstituents(), jet_info.DisplacedConstituents()));
    result.SetBTag(this->BTag() + jet_info.BTag());
    result.SetTauTag(this->TauTag() + jet_info.TauTag());
    result.SetCharge(this->Charge() + jet_info.Charge());
    return result;
}

JetInfo& JetInfo::operator+=(JetInfo const& jet_info)
{
    DEBUG0;
    this->AddConstituents(jet_info.Constituents(), jet_info.DisplacedConstituents());
    this->b_tag_ += jet_info.BTag();
    this->tau_tag_ += jet_info.TauTag();
    this->charge_ += jet_info.Charge();
    return *this;
}


void JetInfo::SetConstituent(Constituent const& constituent)
{
    DEBUG0;
    constituents_.emplace_back(constituent);
    if (VertexResultion(constituent)) displaced_constituents_.emplace_back(constituent);
}

void JetInfo::SetConstituents(std::vector<Constituent> const& constituents)
{
    DEBUG0;
    constituents_ = constituents;
    displaced_constituents_ = ApplyVertexResolution(constituents);
}

void JetInfo::AddConstituent(Constituent const& constituent)
{
    DEBUG0;
    constituents_.emplace_back(constituent);
    if (VertexResultion(constituent)) displaced_constituents_.emplace_back(constituent);
}

void JetInfo::AddConstituents(std::vector<Constituent> const& constituents)
{
    DEBUG0;
    constituents_ = Join(constituents_, constituents);
    displaced_constituents_ = Join(displaced_constituents_, ApplyVertexResolution(constituents));
}

void JetInfo::AddConstituents(std::vector<Constituent> const& constituents, std::vector<Constituent> const& displaced_constituents)
{
    DEBUG0;
    constituents_ = Join(constituents_, constituents);
    displaced_constituents_ = Join(displaced_constituents_, displaced_constituents);
}

std::vector<Constituent> JetInfo::Constituents() const
{
    DEBUG0;
    return constituents_;
}

std::vector<Constituent> JetInfo::DisplacedConstituents() const
{
    DEBUG0;
    return displaced_constituents_;
}

int JetInfo::VertexNumber() const
{
    DEBUG0;
    return displaced_constituents_.size();
}

Jet JetInfo::VertexJet() const
{
    DEBUG0;
   std::vector<Jet> jets;
    for (auto const & consituent : displaced_constituents_) jets.emplace_back(consituent.Momentum());
    return Join(jets);
}

Length JetInfo::SumDisplacement() const
{
    DEBUG0;
    if (displaced_constituents_.empty()) return 0_mm;
    return boost::accumulate(displaced_constituents_, 0_mm, [](Length result, Constituent const & constituent) {
        return (result + constituent.Position().Vect().Perp());
    });
}

Length JetInfo::MeanDisplacement() const
{
    DEBUG0;
    if (displaced_constituents_.empty()) return 0_mm;
    return SumDisplacement() / double(displaced_constituents_.size());
}

Length JetInfo::MaxDisplacement() const
{
    DEBUG0;
    if(displaced_constituents_.empty()) return 0_mm;
    return boost::max_element(displaced_constituents_, [](Constituent const & constituent_1, Constituent const & constituent_2) {
        return constituent_1.Position().Vect().Perp() < constituent_2.Position().Vect().Perp();
    })->Position().Vect().Perp();
}

Mass JetInfo::VertexMass() const
{
    DEBUG0;
    Mass vertex_mass = boost::accumulate(displaced_constituents_, LorentzVector<Momentum>(), [](LorentzVector<Momentum> const & momentum, Constituent const & constituent) {
        return momentum + constituent.Momentum();
    }).M();
    DEBUG(vertex_mass);
    if (vertex_mass < DetectorGeometry::VertexMassMin()) return massless;
    return vertex_mass;
}

Energy JetInfo::VertexEnergy() const
{
    DEBUG0;
    return boost::accumulate(displaced_constituents_, Constituent()).Momentum().E();
}

std::vector<Constituent> JetInfo::ApplyVertexResolution(std::vector<Constituent> constituents) const
{
    DEBUG(constituents.size());
    if (constituents.empty()) return constituents;
    std::vector <Constituent> displaced_constituents;
    for (auto & constituent : constituents) if (VertexResultion(constituent)) displaced_constituents.emplace_back(constituent);
    DEBUG(displaced_constituents.size());
    return displaced_constituents;
}

bool JetInfo::VertexResultion(Constituent constituent) const
{
    DEBUG(constituent.Position().Perp());
    Length x = constituent.Position().X();
    constituent.Smearing();
    DEBUG(x, constituent.Position().X());
    return (constituent.Position().Vect().Perp() > DetectorGeometry::TrackerDistanceMin() && constituent.Position().Vect().Perp() < DetectorGeometry::TrackerDistanceMax() && abs(constituent.Momentum().Rapidity()) < DetectorGeometry::TrackerEtaMax());
}

Angle JetInfo::ElectroMagneticRadius(Jet const& jet) const
{
    DEBUG0;
    Energy energy = 0;
    ValueProduct<Energy,Angle> weight = 0;
    for (auto const & constituent : Constituents()) if (constituent.DetectorPart() == DetectorPart::photon) {
            energy += constituent.Momentum().Et();
            weight += constituent.Momentum().Et() * jet.DeltaRTo(constituent.Momentum());
        }
    if (energy == 0_GeV) return 0_rad;
    else return weight / energy;
}

Angle JetInfo::TrackRadius(Jet const& jet) const
{
    DEBUG0;
    Energy energy = 0;
    ValueProduct<Energy,Angle> weight = 0;
    for (auto const & constituent : Constituents()) if (constituent.DetectorPart() == DetectorPart::track) {
            energy += constituent.Momentum().Et();
            weight += constituent.Momentum().Et() * jet.DeltaRTo(constituent.Momentum());
    }
    if (energy == 0_GeV) return 0_rad;
    else return weight / energy;
}

struct IsDetector {
    IsDetector(DetectorPart detector_part) {
        detector_part_ = detector_part;
    }
    bool operator()(Constituent const& constituent) {
        return constituent.DetectorPart() != detector_part_;
    }
    DetectorPart detector_part_;
};

float JetInfo::LeadingTrackMomentumFraction() const
{
    DEBUG0;
    std::vector<Constituent> constituents = Constituents();
    constituents = boost::range::remove_erase_if(constituents, IsDetector(DetectorPart::track));
    std::sort(constituents.begin(), constituents.end(), [](Constituent const & constituent_1, Constituent const & constituent_2) {
        return (constituent_1.Momentum().Pt() > constituent_2.Momentum().Pt());
    });
    Momentum sum = boost::accumulate(constituents, at_rest, [](Momentum result, Constituent const & constituent) {
        return (result + constituent.Momentum().Pt());
    });
    return constituents.front().Momentum().Pt() / sum;
}

float JetInfo::CoreEnergyFraction(Jet const& jet) const
{
    DEBUG0;
    Energy energy = 0;
    Energy core_energy = 0;
    for (auto const & constituent : Constituents()) if (constituent.DetectorPart() == DetectorPart::photon) {
            energy += constituent.Momentum().Et();
            if (jet.DeltaRTo(constituent.Momentum()) < 0.2_rad) core_energy += constituent.Momentum().Et();
        }
    if (energy == 0_GeV) return 0;
    else return core_energy / energy;
}

float JetInfo::ElectroMagneticFraction() const
{
    DEBUG0;
    Energy em_energy = 0_GeV;
    Energy energy = 0_GeV;
    for (auto const & constituent : Constituents()) {
        energy += constituent.Momentum().Et();
        if (constituent.DetectorPart() == DetectorPart::photon) em_energy += constituent.Momentum().Et();
    }
    if (energy == 0_GeV) return 0;
    else return em_energy / energy;
}

Mass JetInfo::ClusterMass() const
{
    DEBUG0;
    LorentzVector<Momentum> jet;
    for (auto const & constituent : Constituents()) if (constituent.DetectorPart() == DetectorPart::photon) jet += constituent.Momentum();
    return jet.Mass();
}

Mass JetInfo::TrackMass() const
{
    DEBUG0;
    LorentzVector<Momentum> jet;
    for (auto const & constituent : Constituents()) if (constituent.DetectorPart() == DetectorPart::track) jet += constituent.Momentum();
    return jet.Mass();
}

int JetInfo::Charge() const
{
    DEBUG0;
    if (charge_ != std::numeric_limits<int>::max()) return charge_;
    int charge = boost::accumulate(constituents_, 0, [](int charge, Constituent const & constituent) {
        return charge + constituent.Charge();
    });
    return charge;
}
void JetInfo::SetCharge(int charge)
{
    DEBUG0;
    charge_ = charge;
}
bool JetInfo::TauTag() const
{
    DEBUG0;
    return tau_tag_;
}
void JetInfo::SetTauTag(bool tau_tag)
{
    DEBUG0;
    tau_tag_ = tau_tag;
}
bool JetInfo::BTag() const
{
    DEBUG0;
    return b_tag_;
}
void JetInfo::SetBTag(bool b_tag)
{
    DEBUG0;
    b_tag_ = b_tag;
}
// Family JetInfo::Family() const
// {
//     return constituents().front().family();
// }

void JetInfo::SecondayVertex() const
{
    DEBUG0;
    auto leading = boost::range::max_element(constituents_, [](Constituent const & consituent_1, Constituent const & constituent_2) {
        return consituent_1.Momentum().Pt() < constituent_2.Momentum().Pt();
    });
    Length x = (*leading).Position().X();
    Length y = (*leading).Position().Y();
    Length radius = (*leading).Position().Perp() / 2.;
    std::vector<Constituent> constituents;
    auto constituent = std::copy_if(constituents_.begin(), constituents_.end(), constituents.begin(), [&](Constituent const & constituent) {
        return (constituent.Position().X() < x + radius && constituent.Position().X() > x - radius && constituent.Position().Y() < y + radius && constituent.Position().Y() > y - radius);
    });
    constituents.resize(std::distance(constituents.begin(), constituent));
}
bool JetInfo::SubStructure() const
{
    return sub_structure_;
}
void JetInfo::SetSubStructure(bool sub_structure)
{
    sub_structure_ = sub_structure;
}

}
