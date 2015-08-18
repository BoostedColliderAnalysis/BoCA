/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "JetInfo.hh"

#include "Vector.hh"
#include "Math.hh"
#include "Types.hh"
#include "delphes/Delphes.hh"
#include "Debug.hh"

namespace boca {

JetInfo::JetInfo()
{
    Debug();
}

JetInfo::JetInfo(float bdt)
{
    SetBdt(bdt);
    SetCharge(LargeNumber());
}

void JetInfo::SetDelphesTags(::delphes::Jet const& jet)
{
    SetBTag(jet.BTag);
    SetTauTag(jet.TauTag);
    SetCharge(jet.Charge);
}

JetInfo::JetInfo(::delphes::Jet const& jet)
{
  SetDelphesTags(jet);
  SetCharge(LargeNumber());
}

JetInfo::JetInfo(int charge)
{
    SetCharge(charge);
}

JetInfo::JetInfo(Constituent const& constituent)
{
  SetConstituent(constituent);
}

JetInfo::JetInfo(Constituent const& constituent, int charge)
{
    SetConstituent(constituent);
    SetCharge(charge);
}

JetInfo::JetInfo(std::vector<Constituent> const& constituents)
{
  SetConstituents(constituents);
  SetCharge(LargeNumber());
}

JetInfo::JetInfo(std::vector<Constituent> const& constituents, std::vector<Constituent> const& displaced_constituents)
{
    constituents_ = constituents;
    displaced_constituents_ = displaced_constituents;
    SetCharge(LargeNumber());
}

JetInfo JetInfo::operator+(JetInfo const& jet_info)
{
  JetInfo result(Join(this->constituents(),jet_info.constituents()), Join(this->displaced_constituents(),jet_info.displaced_constituents()));
  result.SetBTag(this->BTag() + jet_info.BTag());
  result.SetTauTag(this->TauTag() + jet_info.TauTag());
  result.SetCharge(this->Charge() + jet_info.Charge());
  return result;
}

JetInfo& JetInfo::operator+=(JetInfo const& jet_info)
{
  this->AddConstituents(jet_info.constituents(), jet_info.displaced_constituents());
  this->b_tag_+= jet_info.BTag();
  this->tau_tag_ += jet_info.TauTag();
  this->charge_ += jet_info.Charge();
  return *this;
}


void JetInfo::SetConstituent(Constituent const& constituent)
{
  constituents_.emplace_back(constituent);
  if (VertexResultion(constituent)) displaced_constituents_.emplace_back(constituent);
}

void JetInfo::SetConstituents(std::vector<Constituent> const& constituents)
{
  constituents_ = constituents;
  displaced_constituents_ = ApplyVertexResolution(constituents);
}

void JetInfo::AddConstituent(Constituent const& constituent)
{
    constituents_.emplace_back(constituent);
    if (VertexResultion(constituent)) displaced_constituents_.emplace_back(constituent);
}

void JetInfo::AddConstituents(std::vector<Constituent> const& constituents)
{
    constituents_ = Join(constituents_, constituents);
    displaced_constituents_ = Join(displaced_constituents_, ApplyVertexResolution(constituents));
}

void JetInfo::AddConstituents(std::vector<Constituent> const& constituents, std::vector<Constituent> const& displaced_constituents)
{
  constituents_ = Join(constituents_, constituents);
  displaced_constituents_ = Join(displaced_constituents_, displaced_constituents);
}

std::vector<Constituent> JetInfo::constituents() const
{
    return constituents_;
}

std::vector<Constituent> JetInfo::displaced_constituents() const
{
    return displaced_constituents_;
}

int JetInfo::VertexNumber() const
{
    return displaced_constituents_.size();
}

fastjet::PseudoJet JetInfo::VertexJet() const
{
    Jets jets;
    for (auto const& consituent : displaced_constituents_) jets.emplace_back(PseudoJet(consituent.Momentum()));
    return fastjet::join(jets);
}

float JetInfo::SumDisplacement() const
{
    Debug();
    if (displaced_constituents_.empty()) return 0;
    return std::accumulate(displaced_constituents_.rbegin(), displaced_constituents_.rend(), 0, [](float result, Constituent const& constituent){
      return (result + constituent.Position().Vect().Perp());
    });
}

float JetInfo::MeanDisplacement() const
{
    Debug();
    if (displaced_constituents_.empty()) return 0;
    return SumDisplacement() / displaced_constituents_.size();
}

float JetInfo::MaxDisplacement() const
{
    Debug();
    if (displaced_constituents_.empty())
        return 0;
    return (*std::max_element(displaced_constituents_.begin(), displaced_constituents_.end(), [](Constituent const& constituent_1, Constituent const& constituent_2){
      return constituent_1.Position().Vect().Perp() > constituent_2.Position().Vect().Perp();
    } )).Position().Vect().Perp();
}

float JetInfo::VertexMass() const
{
    Debug();
    float vertex_mass = std::accumulate(displaced_constituents_.begin(), displaced_constituents_.end(), LorentzVector(),[](LorentzVector const& momentum,Constituent const&constituent){
      return momentum + constituent.Momentum();
    }).M();
    Debug(vertex_mass);
    if (vertex_mass < DetectorGeometry::VertexMassMin())
        return 0;
    return vertex_mass;
}

float JetInfo::VertexEnergy() const
{
    Debug();
    float vertex_energy = std::accumulate(displaced_constituents_.begin(), displaced_constituents_.end(), Constituent()).Momentum().E();
    return vertex_energy;
}

std::vector<Constituent> JetInfo::ApplyVertexResolution(std::vector<Constituent> constituents) const
{
    Debug(constituents.size());
    if (constituents.empty())
        return constituents;
    std::vector <Constituent> displaced_constituents;
    for (auto const& constituent : constituents) if (VertexResultion(constituent)) displaced_constituents.emplace_back(constituent);
    Debug(displaced_constituents.size());
    return displaced_constituents;
}

bool JetInfo::VertexResultion(Constituent const& constituent) const
{
    Debug(constituent.Position().Perp());
    return (constituent.Position().Vect().Perp() > DetectorGeometry::TrackerDistanceMin() & constituent.Position().Vect().Perp() < DetectorGeometry::TrackerDistanceMax() & std::abs(constituent.Momentum().Rapidity()) < DetectorGeometry::TrackerEtaMax());
}

float JetInfo::ElectroMagneticRadius(fastjet::PseudoJet const& jet) const
{
    float energy = 0;
    float weight = 0;
    for (auto const& constituent : constituents()) if (constituent.sub_detector() == SubDetector::photon) {
            energy += constituent.Momentum().Et();
            weight += constituent.Momentum().Et() * jet.delta_R(fastjet::PseudoJet(constituent.Momentum()));
        }
    if (energy == 0) return 0;
    else return weight / energy;
}

float JetInfo::TrackRadius(fastjet::PseudoJet const& jet) const
{
    float energy = 0;
    float weight = 0;
    for (auto const& constituent : constituents()) if (constituent.sub_detector() == SubDetector::track) {
            energy += constituent.Momentum().Et();
            weight += constituent.Momentum().Et() * jet.delta_R(fastjet::PseudoJet(constituent.Momentum()));
        }
    if (energy == 0) return 0;
    else return weight / energy;
}

struct IsDetector {
    IsDetector(SubDetector sub_detector)
    {
        sub_detector_ = sub_detector;
    }
    bool operator()(Constituent const& constituent)
    {
        return constituent.sub_detector() != sub_detector_;
    }
    SubDetector sub_detector_;
};

float JetInfo::LeadingTrackMomentumFraction() const
{
    std::vector<Constituent> consts = constituents();
    consts.erase(std::remove_if(consts.begin(), consts.end(), IsDetector(SubDetector::track)), consts.end());
    std::sort(consts.begin(), consts.end(), [](Constituent const& constituent_1, Constituent const& constituent_2){
      return (constituent_1.Momentum().Pt() > constituent_2.Momentum().Pt());
    });
    float sum = std::accumulate(consts.rbegin(), consts.rend(), 0, [](float result, Constituent const& constituent){
      return (result + constituent.Momentum().Pt());
    });
    return consts.front().Momentum().Pt() / sum;
}

float JetInfo::CoreEnergyFraction(fastjet::PseudoJet const& jet) const
{
    float energy = 0;
    float core_energy = 0;
    for (auto const& constituent : constituents()) if (constituent.sub_detector() == SubDetector::photon) {
            energy += constituent.Momentum().Et();
            if (jet.delta_R(fastjet::PseudoJet(constituent.Momentum())) < 0.2)
                core_energy += constituent.Momentum().Et();
        }
    if (energy == 0)
        return 0;
    else
        return core_energy / energy;
}

float JetInfo::ElectroMagneticFraction() const
{
    float em_energy = 0;
    float energy = 0;
    for (auto const& constituent : constituents()) {
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
    fastjet::PseudoJet jet;
    for (auto const& constituent : constituents()) if (constituent.sub_detector() == SubDetector::photon)
            jet += constituent.Momentum();
    return jet.m();
}

float JetInfo::TrackMass() const
{
    fastjet::PseudoJet jet;
    for (auto const& constituent : constituents()) if (constituent.sub_detector() == SubDetector::track)
            jet += constituent.Momentum();
    return jet.m();
}

int JetInfo::Charge() const
{
    Debug();
    if (charge_ != LargeNumber())
        return charge_;
    int charge = std::accumulate(constituents_.begin(), constituents_.end(), 0, [](int charge, Constituent const& constituent) {
        return charge + constituent.charge();
    });
    return charge;
}
void JetInfo::SetCharge(int charge)
{
  charge_ = charge;
}
bool JetInfo::TauTag() const
{
  return tau_tag_;
}
void JetInfo::SetTauTag(bool tau_tag)
{
  tau_tag_ = tau_tag;
}
bool JetInfo::BTag() const
{
  return b_tag_;
}
void JetInfo::SetBTag(bool b_tag)
{
  b_tag_ = b_tag;
}
Family JetInfo::Family() const
{
    return constituents().front().family();
}

void JetInfo::SecondayVertex() const
{
    auto leading = std::max_element(constituents_.begin(), constituents_.end(), [](Constituent const& consituent_1, Constituent const& constituent_2) {
        return consituent_1.Momentum().Pt() < constituent_2.Momentum().Pt();
    });
    float x = (*leading).Position().X();
    float y = (*leading).Position().Y();
    float radius = (*leading).Position().Perp() / 2;
    std::vector<Constituent> constituents;
    auto it = std::copy_if(constituents_.begin(), constituents_.end(), constituents.begin(), [&](Constituent const& constituent) {
        return (constituent.Position().X() < x + radius && constituent.Position().X() > x - radius && constituent.Position().Y() < y + radius && constituent.Position().Y() > y - radius);
    });
    constituents.resize(std::distance(constituents.begin(), it));
}

}
