# include "JetInfo.hh"

# include "Predicate.hh"

/**
 * @brief Constructor
 *
 *
 * choose HDetectorType according to LHC or 100TeV
 *
 * LHC: CMS
 * 100TeV: Spp
 *
 */


analysis::DetectorGeometry::DetectorGeometry()
{
    DetectorType detector_type = Spp;
//     HDetectorType DetectorType = CMS;
    switch (detector_type) {
    case CMS :
        JetMinPt = 20;
        JetConeSize = 0.5;
        MinCellResolution = .1;
        MinCellPt = .5;
        TrackerEtaMax = 2.5;
        TrackerDistanceMin = 0.1;
        TrackerDistanceMax = 1000;
        VertexMassMin = 0.1;
        JetDefinition = fastjet::JetDefinition(fastjet::antikt_algorithm, JetConeSize);
        SubJetDefinition = fastjet::JetDefinition(fastjet::kt_algorithm, JetConeSize);
    case Spp:
        JetMinPt = 40;
        JetConeSize = 0.5;
        MinCellResolution = .1;
        MinCellPt = .5;
        TrackerEtaMax = 3.5;
        TrackerDistanceMin = 0.1;
        TrackerDistanceMax = 1000;
        VertexMassMin = 0.1;
        JetDefinition = fastjet::JetDefinition(fastjet::antikt_algorithm, JetConeSize);
        SubJetDefinition = fastjet::JetDefinition(fastjet::kt_algorithm, JetConeSize);
    }
}

analysis::JetInfo::JetInfo()
{
    Print(kDebug, "Constructor");
}

analysis::JetInfo::JetInfo(const Constituent &constituent)
{
    constituents_.emplace_back(constituent);
}

analysis::JetInfo::JetInfo(const std::vector<Constituent> &constituents)
{
    constituents_ = constituents;
}

void analysis::JetInfo::Addconstituent(const Constituent &constituent) {
    constituents_.emplace_back(constituent);
}

void analysis::JetInfo::Addconstituents(const std::vector<Constituent> &constituents) {
    constituents_.insert(constituents_.end(), constituents.begin(), constituents.end());
}

void analysis::JetInfo::AddDaughter(const int daughter) {
    if (!constituents().empty()) {
        Print(kError, "constituents", constituents().size(), constituents().front().family().particle().Id);
        constituents().front().family().AddDaughter(daughter);
        return;
    }
    Print(kError, "No constituent");
}

std::vector<analysis::Constituent> analysis::JetInfo::constituents() const {
    return constituents_;
}

std::unordered_map<analysis::Family, float> analysis::JetInfo::FamilyFractions() {
    return family_fractions_;
}

int analysis::JetInfo::VertexNumber() const {
    return ApplyVertexResolution().size();
}

void analysis::JetInfo::AddFamily(const Family &family, const float weight)
{
    Print(kDebug, "Add constituent", family.particle().Id, family.mother_1().Id, weight);
    family_fractions_[family] += weight;
}

void analysis::JetInfo::ExtractFamilyFraction()
{
    Print(kInformation, "Extract Family Fraction");
    for (const auto & constituent : constituents()) family_fractions_[constituent.family()] += constituent.Momentum().Pt();
}

analysis::Family analysis::JetInfo::MaximalFamily()
{
    Print(kDebug, "Get Maximal Id");
    std::pair<Family, float> max = *std::max_element(family_fractions_.begin(), family_fractions_.end(), SortPairs());
    return max.first;
}

void analysis::JetInfo::AddParticle(const int constituent_id, const float weight)
{
    Print(kDebug, "Add constituent", constituent_id, weight);
    id_fractions_[constituent_id] += weight;
    Print(kDetailed, "Saved Weight", id_fractions_[constituent_id]);
}

void analysis::JetInfo::ExtractFraction(const int particle_id)
{
    Print(kInformation, "Extract Fraction", particle_id);
    ExtractFamilyFraction();
    for (auto pair = family_fractions_.begin(); pair != family_fractions_.end(); ++pair) {
        if ((*pair).first.particle().Id == particle_id || (*pair).first.mother_1().Id == particle_id) AddParticle(particle_id, (*pair).second);
        else if ((*pair).first.particle().Id == -particle_id || (*pair).first.mother_1().Id == -particle_id) AddParticle(-particle_id, (*pair).second);
        else AddParticle((*pair).first.particle().Id, (*pair).second);
    }
}

void analysis::JetInfo::ExtractFraction(const int particle_id, const int mother_id)
{
    Print(kInformation, "Extract Fraction", particle_id, mother_id);
    for (auto pair = family_fractions_.begin(); pair != family_fractions_.end(); ++pair) {
        if (std::abs((*pair).first.particle().Id) == particle_id && std::abs((*pair).first.mother_1().Id) == mother_id) AddParticle((*pair).first.particle().Id, (*pair).second);
        else AddParticle(IsrId, (*pair).second);
    }
}

void analysis::JetInfo::ExtractAbsFraction(const int particle_id)
{
    Print(kInformation, "Extract Fraction", particle_id);
    ExtractFamilyFraction();
    for (auto pair = family_fractions_.begin(); pair != family_fractions_.end(); ++pair) {
        if (std::abs((*pair).first.particle().Id) == particle_id || std::abs((*pair).first.mother_1().Id) == particle_id) AddParticle(particle_id, (*pair).second);
        else AddParticle((*pair).first.particle().Id, (*pair).second);
    }
}

float analysis::JetInfo::GetWeightSum() const
{
    Print(kDebug, "Get Weight Sum", id_fractions_.size());
    float weight_sum = std::accumulate(begin(id_fractions_), end(id_fractions_), 0.0, [](const float previous, const std::pair<int, float> &pair) {
        return (previous + pair.second);
    });
    Print(kDetailed, "Weight Sum", weight_sum);
    return weight_sum;
}

float analysis::JetInfo::Fraction(const int particle_id) const
{
    Print(kInformation, "Get Fraction", particle_id);
    if (!id_fractions_.count(particle_id)) return 0;
    if (GetWeightSum() == 0)   return 0;
    return (id_fractions_.at(particle_id) / GetWeightSum());
}

float analysis::JetInfo::MaximalFraction() const
{
    Print(kInformation, "Get Maximal Fraction");
    std::pair<int, float> maximal_weight = *std::max_element(id_fractions_.begin(), id_fractions_.end(), SortPairs());
    if (GetWeightSum() == 0) return 0;
    else return (maximal_weight.second / GetWeightSum());
}

int analysis::JetInfo::MaximalId() const
{
    Print(kDebug, "Get Maximal Id");
    std::pair<int, float> maximal_pair = *std::max_element(id_fractions_.begin(), id_fractions_.end(), SortPairs());
    return maximal_pair.first;
}

void analysis::JetInfo::PrintAllInfos(const Severity severity) const
{
    Print(kDebug, "Print All Infos");
    for (auto pair = id_fractions_.begin(); pair != id_fractions_.end(); ++pair) {
        if (GetWeightSum() == 0) Print(severity, "Jet Fraction", Name((*pair).first), 0);
        else Print(severity, "Jet Fraction", Name((*pair).first), (*pair).second / GetWeightSum());
    }
}

void analysis::JetInfo::PrintAllconstituentInfos(const Severity severity) const
{
    Print(kDebug, "Print All Family Infos");
    for (const auto constituent : constituents())
        Print(severity, "Jet Fraction", Name(constituent.family().particle().Id), Name(constituent.family().mother_1().Id), constituent.family().particle().Momentum.Pt(), constituent.family().mother_1().Momentum.Pt());
}
void analysis::JetInfo::PrintAllFamInfos(const Severity severity) const
{
    Print(kDebug, "Print All Family Infos");
    for (const auto &family_fraction : family_fractions_)
        Print(severity, "Family Fraction", Name(family_fraction.first.particle().Id), Name(family_fraction.first.mother_1().Id), family_fraction.first.particle().Momentum.Pt(), family_fraction.first.mother_1().Momentum.Pt());
}

fastjet::PseudoJet analysis::JetInfo::VertexJet() const
{
    std::vector <Constituent > vertices = ApplyVertexResolution();
    fastjet::PseudoJet Jet;
    for (const auto &vertex : vertices) Jet = fastjet::join(Jet, PseudoJet(vertex.Momentum()));
    return Jet;
}

struct AccuPerpDistance {
    float operator()(float result, const analysis::Constituent &constituent) {
        return (result + constituent.Position().Vect().Perp());
    }

};

float analysis::JetInfo::SumDisplacement() const
{
    Print(kDebug, "Get Jet Displacement");
    if (constituents_.empty()) return 0;
    std::vector <Constituent > vertices = ApplyVertexResolution();
    return std::accumulate(vertices.rbegin(), vertices.rend(), 0, AccuPerpDistance());
}

float analysis::JetInfo::MeanDisplacement() const
{
    Print(kDebug, "Get Jet Displacement");
    if (constituents_.empty()) return 0;
    std::vector <Constituent > vertices = ApplyVertexResolution();
    if (vertices.empty()) return 0;
    const float sum = std::accumulate(vertices.rbegin(), vertices.rend(), 0, AccuPerpDistance());
    return sum / vertices.size();
}

struct MaxPerpDistance {
    inline bool operator()(const analysis::Constituent &constituent_1, const analysis::Constituent &constituent_2) const {
        return (constituent_1.Position().Vect().Perp() > constituent_2.Position().Vect().Perp());
    }
};

float analysis::JetInfo::MaxDisplacement() const
{
    Print(kDebug, "Get Jet Displacement");
    if (constituents_.empty()) return 0;
    std::vector <Constituent > vertices = ApplyVertexResolution();
    if (vertices.empty()) return 0;
    std::sort(vertices.begin(), vertices.end(), MaxPerpDistance());
    return vertices.front().Position().Vect().Perp();
}

float analysis::JetInfo::VertexMass() const
{
    Print(kDebug, "Get Vertex Mass");
    std::vector <Constituent > vertices = ApplyVertexResolution();
    const float vertex_mass = std::accumulate(vertices.begin(), vertices.end(), Constituent()).Momentum().M();
    Print(kDebug, "Vertex Mass", vertex_mass);
    if (vertex_mass < detector_geometry_.VertexMassMin) return 0;
    return vertex_mass;
}

float analysis::JetInfo::VertexEnergy() const
{
    Print(kDebug, "Get Energy Fraction");
    std::vector <Constituent > vertices = ApplyVertexResolution();
    const float vertex_energy = std::accumulate(vertices.begin(), vertices.end(), Constituent()).Momentum().E();
    return vertex_energy;
}

std::vector<analysis::Constituent> analysis::JetInfo::ApplyVertexResolution() const
{
    Print(kDebug, "Apply Vertex Resolution");
    std::vector <Constituent > displaced_constituents;
    Print(kDebug, "Vertex Number", constituents().size());
    if (constituents().empty()) return displaced_constituents;
    for (const auto & constituent : constituents()) if (constituent.Position().Vect().Perp() > detector_geometry_.TrackerDistanceMin && constituent.Position().Vect().Perp() < detector_geometry_.TrackerDistanceMax && std::abs(constituent.Momentum().Rapidity()) < detector_geometry_.TrackerEtaMax) displaced_constituents.emplace_back(constituent);
    Print(kDebug, "Real Vertex Number", displaced_constituents.size());
    return displaced_constituents;
}

float analysis::JetInfo::ElectroMagneticRadius(const fastjet::PseudoJet &jet) const
{
    float energy = 0;
    float weight = 0;
    for (const auto & constituent : constituents()) if (constituent.sub_detector() == Constituent::kPhoton) {
            energy += constituent.Momentum().Et();
            weight += constituent.Momentum().Et() * jet.delta_R(fastjet::PseudoJet(constituent.Momentum()));
        }
    if (energy == 0) return 0;
    else return weight / energy;
}

float analysis::JetInfo::TrackRadius(const fastjet::PseudoJet &jet) const
{
    float energy = 0;
    float weight = 0;
    for (const auto & constituent : constituents()) if (constituent.sub_detector() == Constituent::kTrack) {
            energy += constituent.Momentum().Et();
            weight += constituent.Momentum().Et() * jet.delta_R(fastjet::PseudoJet(constituent.Momentum()));
        }
    if (energy == 0) return 0;
    else return weight / energy;
}


struct WrongDetector {
    WrongDetector(const analysis::Constituent::SubDetector sub_detector) {
        this->sub_detector_ = sub_detector;
    }
    bool operator()(const analysis::Constituent &constituent) {
        return (constituent.sub_detector() != sub_detector_);
    }
    analysis::Constituent::SubDetector sub_detector_;
};

struct MaxConstPt {
    bool operator()(const analysis::Constituent &constituent_1, const analysis::Constituent &constituent_2) {
        return (constituent_1.Momentum().Pt() > constituent_2.Momentum().Pt());
    }
};

struct AccuPt {
    float operator()(float result, const analysis::Constituent &constituent) {
        return (result + constituent.Momentum().Pt());
    }

};

float analysis::JetInfo::LeadingTrackMomentumFraction() const
{
    std::vector<Constituent> consts = constituents();
    consts.erase(std::remove_if(consts.begin(), consts.end(), WrongDetector(Constituent::kTrack)), consts.end());
    std::sort(consts.begin(), consts.end(), MaxConstPt());
    float sum = std::accumulate(consts.rbegin(), consts.rend(), 0, AccuPt());
    return consts.front().Momentum().Pt() / sum;
}

float analysis::JetInfo::CoreEnergyFraction(const fastjet::PseudoJet &jet) const
{
    float energy = 0;
    float core_energy = 0;
    for (const auto & constituent : constituents()) if (constituent.sub_detector() == Constituent::kPhoton) {
            energy += constituent.Momentum().Et();
            if (jet.delta_R(fastjet::PseudoJet(constituent.Momentum())) < 0.2) core_energy += constituent.Momentum().Et();
        }
    if (energy == 0) return 0;
    else return core_energy / energy;
}

float analysis::JetInfo::ElectroMagneticFraction() const
{
    float em_energy = 0;
    float energy = 0;
    for (const auto & constituent : constituents()) {
        energy += constituent.Momentum().Et();
        if (constituent.sub_detector() == Constituent::kPhoton) em_energy += constituent.Momentum().Et();
    }
    if (energy == 0) return 0;
    else return em_energy / energy;
}

float analysis::JetInfo::ClusterMass() const
{
    fastjet::PseudoJet jet;
    for (const auto & constituent : constituents()) if (constituent.sub_detector() == Constituent::kPhoton) jet += constituent.Momentum();
    return jet.m();
}

float analysis::JetInfo::TrackMass() const
{
    fastjet::PseudoJet jet;
    for (const auto & constituent : constituents()) if (constituent.sub_detector() == Constituent::kTrack) jet += constituent.Momentum();
    return jet.m();
}
