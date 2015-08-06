#include "JetInfo.hh"

#include "Predicate.hh"
#include "delphes/Delphes.hh"
#include "Debug.hh"

namespace analysis {

JetInfo::JetInfo()
{
    Debug();
}

JetInfo::JetInfo(float bdt)
{
    SetBdt(bdt);
}

void JetInfo::SetDelphesTags(const ::delphes::Jet& jet)
{
    SetBTag(jet.BTag);
    SetTauTag(jet.TauTag);
    SetCharge(jet.Charge);
}

JetInfo::JetInfo(const ::delphes::Jet& jet)
{
    SetDelphesTags(jet);
}

JetInfo::JetInfo(int charge)
{
    SetCharge(charge);
}

JetInfo::JetInfo(const Constituent& constituent)
{
  SetConstituent(constituent);
}

JetInfo::JetInfo(const Constituent& constituent, int charge)
{
    SetConstituent(constituent);
    SetCharge(charge);
}

JetInfo::JetInfo(const std::vector<Constituent>& constituents)
{
    SetConstituents(constituents);
}

JetInfo::JetInfo(const std::vector<Constituent>& constituents, const std::vector<Constituent>& displaced_constituents)
{
    constituents_ = constituents;
    displaced_constituents_ = displaced_constituents;
}

JetInfo JetInfo::operator+(const JetInfo& jet_info)
{
  JetInfo result(Join(this->constituents(),jet_info.constituents()), Join(this->displaced_constituents(),jet_info.displaced_constituents()));
  result.SetBTag(this->BTag() + jet_info.BTag());
  result.SetTauTag(this->TauTag() + jet_info.TauTag());
  result.SetCharge(this->Charge() + jet_info.Charge());
  return result;
}

JetInfo& JetInfo::operator+=(const JetInfo& jet_info)
{
  this->AddConstituents(jet_info.constituents(), jet_info.displaced_constituents());
  this->b_tag_+= jet_info.BTag();
  this->tau_tag_ += jet_info.TauTag();
  this->charge_ += jet_info.Charge();
  return *this;
}


void JetInfo::SetConstituent(const Constituent& constituent)
{
  constituents_.emplace_back(constituent);
  if (VertexResultion(constituent)) displaced_constituents_.emplace_back(constituent);
}

void JetInfo::SetConstituents(const std::vector<Constituent>& constituents)
{
  constituents_ = constituents;
  displaced_constituents_ = ApplyVertexResolution(constituents);
}

void JetInfo::AddConstituent(const Constituent& constituent)
{
    constituents_.emplace_back(constituent);
    if (VertexResultion(constituent)) displaced_constituents_.emplace_back(constituent);
}

void JetInfo::AddConstituents(const std::vector<Constituent>& constituents)
{
    constituents_ = Join(constituents_, constituents);
    displaced_constituents_ = Join(displaced_constituents_, ApplyVertexResolution(constituents));
}

void JetInfo::AddConstituents(const std::vector<Constituent>& constituents, const std::vector<Constituent>& displaced_constituents)
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
    for (const auto& consituent : displaced_constituents_) jets.emplace_back(PseudoJet(consituent.Momentum()));
    return fastjet::join(jets);
}

float JetInfo::SumDisplacement() const
{
    Debug();
    if (displaced_constituents_.empty()) return 0;
    return std::accumulate(displaced_constituents_.rbegin(), displaced_constituents_.rend(), 0, [](float result, const Constituent& constituent){
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
    return (*std::max_element(displaced_constituents_.begin(), displaced_constituents_.end(), [](const Constituent& constituent_1, const Constituent& constituent_2){
      return constituent_1.Position().Vect().Perp() > constituent_2.Position().Vect().Perp();
    } )).Position().Vect().Perp();
}

float JetInfo::VertexMass() const
{
    Debug();
    float vertex_mass = std::accumulate(displaced_constituents_.begin(), displaced_constituents_.end(), LorentzVector(),[](const LorentzVector& momentum,const Constituent &constituent){
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
    for (const auto& constituent : constituents) if (VertexResultion(constituent)) displaced_constituents.emplace_back(constituent);
    Debug(displaced_constituents.size());
    return displaced_constituents;
}

bool JetInfo::VertexResultion(const Constituent& constituent) const
{
    Debug(constituent.Position().Perp());
    return (constituent.Position().Vect().Perp() > DetectorGeometry::TrackerDistanceMin() & constituent.Position().Vect().Perp() < DetectorGeometry::TrackerDistanceMax() & std::abs(constituent.Momentum().Rapidity()) < DetectorGeometry::TrackerEtaMax());
}

float JetInfo::ElectroMagneticRadius(const fastjet::PseudoJet& jet) const
{
    float energy = 0;
    float weight = 0;
    for (const auto& constituent : constituents()) if (constituent.sub_detector() == SubDetector::photon) {
            energy += constituent.Momentum().Et();
            weight += constituent.Momentum().Et() * jet.delta_R(fastjet::PseudoJet(constituent.Momentum()));
        }
    if (energy == 0) return 0;
    else return weight / energy;
}

float JetInfo::TrackRadius(const fastjet::PseudoJet& jet) const
{
    float energy = 0;
    float weight = 0;
    for (const auto& constituent : constituents()) if (constituent.sub_detector() == SubDetector::track) {
            energy += constituent.Momentum().Et();
            weight += constituent.Momentum().Et() * jet.delta_R(fastjet::PseudoJet(constituent.Momentum()));
        }
    if (energy == 0) return 0;
    else return weight / energy;
}

struct IsDetector {
    IsDetector(const SubDetector sub_detector)
    {
        sub_detector_ = sub_detector;
    }
    bool operator()(const Constituent& constituent)
    {
        return constituent.sub_detector() != sub_detector_;
    }
    SubDetector sub_detector_;
};

float JetInfo::LeadingTrackMomentumFraction() const
{
    std::vector<Constituent> consts = constituents();
    consts.erase(std::remove_if(consts.begin(), consts.end(), IsDetector(SubDetector::track)), consts.end());
    std::sort(consts.begin(), consts.end(), [](const Constituent& constituent_1, const Constituent& constituent_2){
      return (constituent_1.Momentum().Pt() > constituent_2.Momentum().Pt());
    });
    float sum = std::accumulate(consts.rbegin(), consts.rend(), 0, [](float result, const Constituent& constituent){
      return (result + constituent.Momentum().Pt());
    });
    return consts.front().Momentum().Pt() / sum;
}

float JetInfo::CoreEnergyFraction(const fastjet::PseudoJet& jet) const
{
    float energy = 0;
    float core_energy = 0;
    for (const auto& constituent : constituents()) if (constituent.sub_detector() == SubDetector::photon) {
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
    for (const auto& constituent : constituents()) {
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
    for (const auto& constituent : constituents()) if (constituent.sub_detector() == SubDetector::photon)
            jet += constituent.Momentum();
    return jet.m();
}

float JetInfo::TrackMass() const
{
    fastjet::PseudoJet jet;
    for (const auto& constituent : constituents()) if (constituent.sub_detector() == SubDetector::track)
            jet += constituent.Momentum();
    return jet.m();
}

int JetInfo::Charge() const
{
    Debug();
    if (charge_ != LargeNumber())
        return charge_;
    int charge = std::accumulate(constituents_.begin(), constituents_.end(), 0, [](int charge, const Constituent & constituent) {
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
    auto leading = std::max_element(constituents_.begin(), constituents_.end(), [](const Constituent& consituent_1, const Constituent& constituent_2) {
        return consituent_1.Momentum().Pt() < constituent_2.Momentum().Pt();
    });
    float x = (*leading).Position().X();
    float y = (*leading).Position().Y();
    float radius = (*leading).Position().Perp() / 2;
    std::vector<Constituent> constituents;
    auto it = std::copy_if(constituents_.begin(), constituents_.end(), constituents.begin(), [&](const Constituent & constituent) {
        return (constituent.Position().X() < x + radius && constituent.Position().X() > x - radius && constituent.Position().Y() < y + radius && constituent.Position().Y() > y - radius);
    });
    constituents.resize(std::distance(constituents.begin(), it));
}

bool SortByBdt::operator()(const fastjet::PseudoJet& jet_1, const fastjet::PseudoJet& jet_2)
{
    return jet_1.user_info<analysis::JetInfo>().Bdt() > jet_2.user_info<analysis::JetInfo>().Bdt();
}

}
