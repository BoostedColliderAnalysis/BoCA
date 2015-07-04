#include "JetInfo.hh"

#include "Predicate.hh"
#include "Debug.hh"

namespace analysis
{

struct AccuPerpDistance {
    float operator()(float result, const Constituent &constituent) {
        return (result + constituent.Position().Vect().Perp());
    }

};

struct MaxPerpDistance {
     bool operator()(const Constituent &constituent_1, const Constituent &constituent_2) const {
        return constituent_1.Position().Vect().Perp() > constituent_2.Position().Vect().Perp();
    }
};

struct WrongDetector {
    WrongDetector(const SubDetector sub_detector) {
        sub_detector_ = sub_detector;
    }
    bool operator()(const Constituent &constituent) {
        return constituent.sub_detector() != sub_detector_;
    }
    SubDetector sub_detector_;
};

struct MaxConstPt {
    bool operator()(const Constituent &constituent_1, const Constituent &constituent_2) {
        return (constituent_1.Momentum().Pt() > constituent_2.Momentum().Pt());
    }
};

struct AccuPt {
    float operator()(float result, const Constituent &constituent) {
        return (result + constituent.Momentum().Pt());
    }

};

JetInfo::JetInfo()
{
    Debug("Constructor");
}

JetInfo::JetInfo(const float bdt)
{
    SetBdt(bdt);
}

void JetInfo::SetDelphesTags(const ::delphes::Jet &jet)
{
    SetBTag(jet.BTag);
    SetTauTag(jet.TauTag);
}

JetInfo::JetInfo(const ::delphes::Jet &jet)
{
    SetDelphesTags(jet);
}

JetInfo::JetInfo(const bool b_tag)
{
    SetBTag(b_tag);
}

// JetInfo::JetInfo(const bool b_tag, const int charge)
// {
//   SetBTag(b_tag);
//   SetCharge(charge);
// }

JetInfo::JetInfo(const bool b_tag, const bool tau_tag)
{
    SetBTag(b_tag);
    SetTauTag(tau_tag);
}

JetInfo::JetInfo(const int charge)
{
    SetCharge(charge);
}

JetInfo::JetInfo(const Constituent &constituent)
{
    constituents_.emplace_back(constituent);
}

JetInfo::JetInfo(const Constituent &constituent, const int charge)
{
    constituents_.emplace_back(constituent);
    SetCharge(charge);
}

JetInfo::JetInfo(const std::vector<Constituent> &constituents)
{
    constituents_ = constituents;
}

void JetInfo::AddConstituent(const Constituent &constituent)
{
    constituents_.emplace_back(constituent);
}

void JetInfo::AddConstituents(const std::vector<Constituent> &constituents)
{
    constituents_.insert(constituents_.end(), constituents.begin(), constituents.end());
}

void JetInfo::AddDaughter(const int daughter)
{
    if (!constituents().empty()) {
        Error("constituents", constituents().size(), constituents().front().family().particle().Id);
        constituents().front().family().AddDaughter(daughter);
        return;
    }
    Error("No constituent");
}

std::vector<Constituent> JetInfo::constituents() const
{
    return constituents_;
}

std::unordered_map<Family, float> JetInfo::FamilyFractions()
{
    return family_fractions_;
}

int JetInfo::VertexNumber() const
{
    return ApplyVertexResolution().size();
}

void JetInfo::AddFamily(const Family &family, const float weight)
{
    Debug("Add constituent", family.particle().Id, family.mother_1().Id, weight);
    family_fractions_[family] += weight;
}

void JetInfo::ExtractFamilyFraction()
{
    Info("Extract Family Fraction");
    for (const auto & constituent : constituents()) family_fractions_[constituent.family()] += constituent.Momentum().Pt();
}

Family JetInfo::MaximalFamily()
{
    Debug("Maximal Id");
    return std::max_element(family_fractions_.begin(), family_fractions_.end(), SortPairs())->first;
}

void JetInfo::AddParticle(const int constituent_id, const float weight)
{
    Debug("Add constituent", constituent_id, weight);
    id_fractions_[constituent_id] += weight;
    Detail("Saved Weight", id_fractions_[constituent_id]);
}

void JetInfo::AddParticle(const Id constituent_id, const float weight)
{
  Debug("Add constituent", Name(constituent_id), weight);
  id_fractions_[int(constituent_id)] += weight;
  Detail("Saved Weight", id_fractions_[int(constituent_id)]);
}

void JetInfo::ExtractFraction(const int id)
{
    Info("Extract Fraction", id);
    ExtractFamilyFraction();
    for (const auto & pair : family_fractions_) {
        if (pair.first.particle().Id == id || pair.first.mother_1().Id == id) AddParticle(id, pair.second);
        else if (pair.first.particle().Id == -id || pair.first.mother_1().Id == -id) AddParticle(-id, pair.second);
        else AddParticle(pair.first.particle().Id, pair.second);
    }
}

void JetInfo::ExtractFraction(const int id, const int mother_id)
{
    Info("Extract Fraction", id, mother_id);
    for (const auto & pair : family_fractions_) {
        if (std::abs(pair.first.particle().Id) == id && std::abs(pair.first.mother_1().Id) == mother_id) AddParticle(pair.first.particle().Id, pair.second);
        else AddParticle(Id::isr, pair.second);
    }
}

void JetInfo::ExtractAbsFraction(const int id)
{
    Info("Extract Fraction", id);
    ExtractFamilyFraction();
    for (const auto & pair : family_fractions_) {
        if (std::abs(pair.first.particle().Id) == id || std::abs(pair.first.mother_1().Id) == id) AddParticle(id, pair.second);
        else AddParticle(pair.first.particle().Id, pair.second);
    }
}

float JetInfo::GetWeightSum() const
{
    Debug("Weight Sum", id_fractions_.size());
    float weight_sum = std::accumulate(begin(id_fractions_), end(id_fractions_), 0.0, [](const float previous, const std::pair<int, float> &pair) {
        return (previous + pair.second);
    });
    Detail("Weight Sum", weight_sum);
    return weight_sum;
}

float JetInfo::Fraction(const int id) const
{
    Info("Fraction", id);
    if (!id_fractions_.count(id)) return 0;
    if (GetWeightSum() == 0)   return 0;
    return (id_fractions_.at(id) / GetWeightSum());
}

float JetInfo::MaximalFraction() const
{
    Info("Maximal Fraction");
    std::pair<int, float> maximal_weight = *std::max_element(id_fractions_.begin(), id_fractions_.end(), SortPairs());
    if (GetWeightSum() == 0) return 0;
    else return (maximal_weight.second / GetWeightSum());
}

int JetInfo::MaximalId() const
{
    Debug("Maximal Id");
    return std::max_element(id_fractions_.begin(), id_fractions_.end(), SortPairs())->first;
}

void JetInfo::PrintAllInfos(const Severity severity) const
{
    Debug("Print All Infos");
//     for (auto pair = id_fractions_.begin(); pair != id_fractions_.end(); ++pair) {
//         if (GetWeightSum() == 0) Print(severity, "Jet Fraction", Name((*pair).first), 0);
//         else Print(severity, "Jet Fraction", Name((*pair).first), (*pair).second / GetWeightSum());
//     }
}

void JetInfo::PrintAllconstituentInfos(const Severity severity) const
{
    Debug("Print All Family Infos");
//     for (const auto constituent : constituents())
//         Print(severity, "Jet Fraction", Name(constituent.family().particle().Id), Name(constituent.family().mother_1().Id), constituent.family().particle().Momentum.Pt(), constituent.family().mother_1().Momentum.Pt());
}
void JetInfo::PrintAllFamInfos(const Severity severity) const
{
    Debug("Print All Family Infos");
//     for (const auto & family_fraction : family_fractions_)
//         Print(severity, "Family Fraction", Name(family_fraction.first.particle().Id), Name(family_fraction.first.mother_1().Id), family_fraction.first.particle().Momentum.Pt(), family_fraction.first.mother_1().Momentum.Pt());
}

fastjet::PseudoJet JetInfo::VertexJet() const
{
    std::vector <Constituent > vertices = ApplyVertexResolution();
    fastjet::PseudoJet Jet;
    for (const auto & vertex : vertices) Jet = fastjet::join(Jet, PseudoJet(vertex.Momentum()));
    return Jet;
}



float JetInfo::SumDisplacement() const
{
    Debug("Jet Displacement");
    if (constituents_.empty()) return 0;
    std::vector <Constituent > vertices = ApplyVertexResolution();
    return std::accumulate(vertices.rbegin(), vertices.rend(), 0, AccuPerpDistance());
}

float JetInfo::MeanDisplacement() const
{
    Debug("Jet Displacement");
    if (constituents_.empty()) return 0;
    std::vector <Constituent > vertices = ApplyVertexResolution();
    if (vertices.empty()) return 0;
    const float sum = std::accumulate(vertices.rbegin(), vertices.rend(), 0, AccuPerpDistance());
    return sum / vertices.size();
}

float JetInfo::MaxDisplacement() const
{
    Debug("Jet Displacement");
    if (constituents_.empty()) return 0;
    std::vector <Constituent > vertices = ApplyVertexResolution();
    if (vertices.empty()) return 0;
    std::sort(vertices.begin(), vertices.end(), MaxPerpDistance());
    return vertices.front().Position().Vect().Perp();
}

float JetInfo::VertexMass() const
{
    Debug("Vertex Mass");
    std::vector <Constituent > vertices = ApplyVertexResolution();
    const float vertex_mass = std::accumulate(vertices.begin(), vertices.end(), Constituent()).Momentum().M();
    Debug("Vertex Mass", vertex_mass);
    if (vertex_mass < DetectorGeometry().VertexMassMin()) return 0;
    return vertex_mass;
}

float JetInfo::VertexEnergy() const
{
    Debug("Energy Fraction");
    std::vector <Constituent > vertices = ApplyVertexResolution();
    const float vertex_energy = std::accumulate(vertices.begin(), vertices.end(), Constituent()).Momentum().E();
    return vertex_energy;
}

std::vector<Constituent> JetInfo::ApplyVertexResolution() const
{
    Debug("Apply Vertex Resolution");
    std::vector <Constituent > displaced_constituents;
    Debug("Vertex Number", constituents().size());
    if (constituents().empty()) return displaced_constituents;
    for (const auto & constituent : constituents()) if (constituent.Position().Vect().Perp() > DetectorGeometry().TrackerDistanceMin() && constituent.Position().Vect().Perp() < DetectorGeometry().TrackerDistanceMax() && std::abs(constituent.Momentum().Rapidity()) < DetectorGeometry().TrackerEtaMax()) displaced_constituents.emplace_back(constituent);
    Debug("Real Vertex Number", displaced_constituents.size());
    return displaced_constituents;
}

float JetInfo::ElectroMagneticRadius(const fastjet::PseudoJet &jet) const
{
    float energy = 0;
    float weight = 0;
    for (const auto & constituent : constituents()) if (constituent.sub_detector() == SubDetector::photon) {
            energy += constituent.Momentum().Et();
            weight += constituent.Momentum().Et() * jet.delta_R(fastjet::PseudoJet(constituent.Momentum()));
        }
    if (energy == 0) return 0;
    else return weight / energy;
}

float JetInfo::TrackRadius(const fastjet::PseudoJet &jet) const
{
    float energy = 0;
    float weight = 0;
    for (const auto & constituent : constituents()) if (constituent.sub_detector() == SubDetector::track) {
            energy += constituent.Momentum().Et();
            weight += constituent.Momentum().Et() * jet.delta_R(fastjet::PseudoJet(constituent.Momentum()));
        }
    if (energy == 0) return 0;
    else return weight / energy;
}

float JetInfo::LeadingTrackMomentumFraction() const
{
    std::vector<Constituent> consts = constituents();
    consts.erase(std::remove_if(consts.begin(), consts.end(), WrongDetector(SubDetector::track)), consts.end());
    std::sort(consts.begin(), consts.end(), MaxConstPt());
    float sum = std::accumulate(consts.rbegin(), consts.rend(), 0, AccuPt());
    return consts.front().Momentum().Pt() / sum;
}

float JetInfo::CoreEnergyFraction(const fastjet::PseudoJet &jet) const
{
    float energy = 0;
    float core_energy = 0;
    for (const auto & constituent : constituents()) if (constituent.sub_detector() == SubDetector::photon) {
            energy += constituent.Momentum().Et();
            if (jet.delta_R(fastjet::PseudoJet(constituent.Momentum())) < 0.2) core_energy += constituent.Momentum().Et();
        }
    if (energy == 0) return 0;
    else return core_energy / energy;
}

float JetInfo::ElectroMagneticFraction() const
{
    float em_energy = 0;
    float energy = 0;
    for (const auto & constituent : constituents()) {
        energy += constituent.Momentum().Et();
        if (constituent.sub_detector() == SubDetector::photon) em_energy += constituent.Momentum().Et();
    }
    if (energy == 0) return 0;
    else return em_energy / energy;
}

float JetInfo::ClusterMass() const
{
    fastjet::PseudoJet jet;
    for (const auto & constituent : constituents()) if (constituent.sub_detector() == SubDetector::photon) jet += constituent.Momentum();
    return jet.m();
}

float JetInfo::TrackMass() const
{
    fastjet::PseudoJet jet;
    for (const auto & constituent : constituents()) if (constituent.sub_detector() == SubDetector::track) jet += constituent.Momentum();
    return jet.m();
}

int JetInfo::Charge() const
{
    Debug("Charge");
    if(charge_ != LargeNumber()) return charge_;
    std::vector <Constituent > vertices = constituents();
    int charge = std::accumulate(vertices.begin(), vertices.end(), 0, [](int charge, const Constituent & constituent) {
        return charge + constituent.charge();
    });
    return charge;
}

bool SortByBdt::operator()(const fastjet::PseudoJet &jet_1, const fastjet::PseudoJet &jet_2)
{
    return (jet_1.user_info<analysis::JetInfo>().Bdt() > jet_2.user_info<analysis::JetInfo>().Bdt());
}
JetInfo JetInfo::operator+(const JetInfo &jet_info)
{
    JetInfo result;
    result.AddConstituents(jet_info.constituents());
    return result;
}

}
