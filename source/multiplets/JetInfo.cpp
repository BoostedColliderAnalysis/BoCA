/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include <boost/range/algorithm/max_element.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/algorithm_ext/erase.hpp>

#include "boca/generic/Vector.hh"
#include "boca/generic/Types.hh"
#include "boca/math/Math.hh"
#include "boca/multiplets/JetInfo.hh"
#include "boca/multiplets/Singlet.hh"
#include "boca/delphes/Classes.hh"

// #define DEBUGGING
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

namespace {

bool VertexResultion(Constituent const& constituent)
{
    DEBUG(constituent.Position().Perp());
    return Settings::TrackerRange().Inside(constituent.Position().Perp()) && abs(constituent.Momentum().Rapidity()) < Settings::TrackerEtaMax();
}

}

JetInfo::JetInfo()
{
    DEBUG0;
}

JetInfo::JetInfo(double bdt)
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
    JetInfo result(Combine(this->Constituents(), jet_info.Constituents()), Combine(this->DisplacedConstituents(), jet_info.DisplacedConstituents()));
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
    Insert(constituents_, constituents);
    Insert(displaced_constituents_, ApplyVertexResolution(constituents));
}

std::vector<Constituent> JetInfo::ApplyVertexResolution(std::vector<Constituent> const& constituents) const
{
    DEBUG(constituents.size());
    auto lambda = [&](Constituent const & constituent) {
      return VertexResultion(constituent);
    }; // http://stackoverflow.com/a/25907302
    return CopyIf(constituents, std::ref(lambda));

}

void JetInfo::AddConstituents(std::vector<Constituent> const& constituents, std::vector<Constituent> const& displaced_constituents)
{
    DEBUG0;
    Insert(constituents_, constituents);
    Insert(displaced_constituents_, displaced_constituents);
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

boca::Singlet JetInfo::VertexJet() const
{
    DEBUG0;
    return Join(Transform(displaced_constituents_, [](Constituent const & consituent) -> Jet {
        return consituent.Momentum();
    }));
}

Length JetInfo::SumDisplacement() const
{
    DEBUG0;
    return displaced_constituents_.empty() ? 0_m : boost::accumulate(displaced_constituents_, 0_m, [](Length const & result, Constituent const & constituent) {
        return result + constituent.Position().Perp();
    });
}

Length JetInfo::MeanDisplacement() const
{
    DEBUG0;
    return displaced_constituents_.empty() ? 0_m  : SumDisplacement() / static_cast<double>(displaced_constituents_.size());
}

Length JetInfo::MaxDisplacement() const
{
    DEBUG0;
    return displaced_constituents_.empty() ? 0_m : boost::max_element(displaced_constituents_, [](Constituent const & constituent_1, Constituent const & constituent_2) {
        return constituent_1.Position().Perp() < constituent_2.Position().Perp();
    })->Position().Perp();
}

Mass JetInfo::VertexMass() const
{
    DEBUG0;
    auto vertex_mass = boost::accumulate(displaced_constituents_, LorentzVector<Momentum>(), [](LorentzVector<Momentum> const & momentum, Constituent const & constituent) {
        return momentum + constituent.Momentum();
    }).Mass();
    DEBUG(vertex_mass);
    return vertex_mass < Settings::VertexMassMin() ? massless : vertex_mass;
}

Energy JetInfo::VertexEnergy() const
{
    DEBUG0;
    return boost::accumulate(displaced_constituents_, Constituent()).Momentum().E();
}

Angle JetInfo::ElectroMagneticRadius(Jet const& jet) const
{
    DEBUG0;
    auto energy = 0_eV;
    auto weight = 0_eV * rad;
    for (auto const & constituent : Constituents()) if (constituent.DetectorPart() == DetectorPart::photon) {
            energy += constituent.Momentum().Et();
            weight += constituent.Momentum().Et() * jet.DeltaRTo(constituent.Momentum());
        }
    return energy == 0_eV ? 0_rad : Angle(weight / energy);
}

Angle JetInfo::TrackRadius(Jet const& jet) const
{
    DEBUG0;
    auto energy = 0_eV;
    auto weight = 0_eV * rad;
    for (auto const & constituent : Constituents()) if (constituent.DetectorPart() == DetectorPart::track) {
            energy += constituent.Momentum().Et();
            weight += constituent.Momentum().Et() * jet.DeltaRTo(constituent.Momentum());
        }
    return energy == 0_eV ? 0_rad : Angle(weight / energy);
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

double JetInfo::LeadingTrackMomentumFraction() const
{
    DEBUG0;
    auto constituents = Constituents();
    constituents = boost::range::remove_erase_if(constituents, IsDetector(DetectorPart::track));
    std::sort(constituents.begin(), constituents.end(), [](Constituent const & constituent_1, Constituent const & constituent_2) {
        return (constituent_1.Momentum().Pt() > constituent_2.Momentum().Pt());
    });
    auto sum = boost::accumulate(constituents, at_rest, [](Momentum const & result, Constituent const & constituent) {
        return (result + constituent.Momentum().Pt());
    });
    return constituents.front().Momentum().Pt() / sum;
}

double JetInfo::CoreEnergyFraction(Jet const& jet) const
{
    DEBUG0;
    auto energy = 0_eV;
    auto core_energy = 0_eV;
    for (auto const & constituent : Constituents()) if (constituent.DetectorPart() == DetectorPart::photon) {
            energy += constituent.Momentum().Et();
            if (jet.DeltaRTo(constituent.Momentum()) < 0.2_rad) core_energy += constituent.Momentum().Et();
        }
    return energy == 0_eV ? 0. : static_cast<double>(core_energy / energy);
}

double JetInfo::ElectroMagneticFraction() const
{
    DEBUG0;
    auto em_energy = 0_eV;
    auto energy = 0_eV;
    for (auto const & constituent : Constituents()) {
        energy += constituent.Momentum().Et();
        if (constituent.DetectorPart() == DetectorPart::photon) em_energy += constituent.Momentum().Et();
    }
    return energy == 0_eV ? 0. : static_cast<double>(em_energy / energy);
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
    return boost::accumulate(constituents_, 0, [](int charge, Constituent const & constituent) {
        return charge + constituent.Charge();
    });
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

void JetInfo::SecondayVertex() const
{
    DEBUG0;
    auto leading = boost::range::max_element(constituents_, [](Constituent const & consituent_1, Constituent const & constituent_2) {
        return consituent_1.Momentum().Pt() < constituent_2.Momentum().Pt();
    });
    auto x = (*leading).Position().X();
    auto y = (*leading).Position().Y();
    auto radius = (*leading).Position().Perp() / 2.;
    std::vector<Constituent> constituents;
    auto position = std::copy_if(constituents_.begin(), constituents_.end(), constituents.begin(), [&](Constituent const & constituent) {
        return (constituent.Position().X() < x + radius && constituent.Position().X() > x - radius && constituent.Position().Y() < y + radius && constituent.Position().Y() > y - radius);
    });
    constituents.resize(std::distance(constituents.begin(), position));
}
bool JetInfo::SubStructure() const
{
    return sub_structure_;
}
void JetInfo::SetSubStructure(bool sub_structure)
{
    sub_structure_ = sub_structure;
}

std::vector< Family > JetInfo::Families() const
{
    std::vector<Family> families;
    for (const auto & constituent : Constituents()) Insert(families, constituent.Families());
    return families;
}
bool JetInfo::ContainsDetectorPart(DetectorPart detector_part) const
{
    for (auto const & constituent : Constituents()) if (constituent.DetectorPart() == detector_part) return true;
    return false;
}
void JetInfo::SetMuBTag(double min_x, double fraction)
{
    min_x_ = min_x;
    fraction_ = fraction;
}
double JetInfo::EnergyRatio() const
{
    return min_x_;
}
double JetInfo::MomentumRatio() const
{
    return fraction_;
}

bool JetInfo::InMuonChamber() const
{
    for (auto const & constituent : Constituents()) {
        ERROR(Name(constituent.DetectorPart()), constituent.Position().Perp(), constituent.Position().Z());
        if (constituent.DetectorPart() == DetectorPart::track && (constituent.Position().Perp() > 2_m || abs(constituent.Position().Z()) > 2_m)) return true;
    }
    return false;
}


}
