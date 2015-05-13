# include "JetInfo.hh"
# include "HTagPrivate.hh"


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


DetectorGeometry::DetectorGeometry()
{

HDetectorType DetectorType = Spp;
//     HDetectorType DetectorType = CMS;
    switch (DetectorType) {
    case CMS :
        JetMinPt = 20;
        JetConeSize = 0.5;
        MinCellResolution = .1;
        MinCellPt = .5;
        TrackerEtaMax = 2.5;
        TrackerDistanceMin = 0.1;
        TrackerDistanceMax = 1000;
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
        JetDefinition = fastjet::JetDefinition(fastjet::antikt_algorithm, JetConeSize);
        SubJetDefinition = fastjet::JetDefinition(fastjet::kt_algorithm, JetConeSize);
    }
}



hanalysis::JetInfo::JetInfo() : detector_geometry_()
// : hanalysis::HTag(* new JetInfoPrivate)
{
//     Debug = 4;
    Print(kDebug, "Constructor");
}

// hanalysis::JetInfo::JetInfo(const int NewBTag) : detector_geometry_()
// // : hanalysis::HTag(* new JetInfoPrivate)
// {
//     BTagM = NewBTag;
// }

hanalysis::JetInfo::JetInfo(const Constituent &Newconstituent) : detector_geometry_()
// : hanalysis::HTag(* new JetInfoPrivate)
{
    constituents_.emplace_back(Newconstituent);
//     BTagM = 0;
}

hanalysis::JetInfo::JetInfo(const std::vector<Constituent> &Newconstituents) : detector_geometry_()
// : hanalysis::HTag(* new JetInfoPrivate)
{
    constituents_ = Newconstituents;
//     BTagM = 0;
}

// hanalysis::JetInfo::JetInfo(const std::vector<Constituent> &Newconstituents, const int NewBTag) : detector_geometry_()
// // : hanalysis::HTag(* new JetInfoPrivate)
// {
//     constituents_ = Newconstituents;
// //     BTagM = NewBTag;
// }

void hanalysis::JetInfo::AddFamily(const HFamily &Family, const float Weight)
{
    Print(kDebug, "Add constituent", Family.ParticleId, Family.Mother1Id, Weight);
    family_fractions_[Family] += Weight;
//   Print(kDetailed, "Saved Weight", IdFractions[Family]);
}

void hanalysis::JetInfo::ExtractFamilyFraction()
{

    Print(kInformation, "Extract Family Fraction");

    for (const auto & constituent : constituents()) {
        family_fractions_[constituent.Family()] += constituent.Momentum().Pt();
    }
}

hanalysis::HFamily hanalysis::JetInfo::MaximalFamily()
{

    Print(kDebug, "Get Maximal Id");
    std::pair<HFamily, float> Max = *std::max_element(family_fractions_.begin(), family_fractions_.end(), SortPairs());
    return Max.first;
}

void hanalysis::JetInfo::AddParticle(const int constituentId, const float Weight)
{
    Print(kDebug, "Add constituent", constituentId, Weight);
    id_fractions_[constituentId] += Weight;
    Print(kDetailed, "Saved Weight", id_fractions_[constituentId]);
}

void hanalysis::JetInfo::ExtractFraction(const int ParticleId)
{
    Print(kInformation, "Extract Fraction", ParticleId);
    ExtractFamilyFraction();
    for (std::unordered_map<HFamily, float>::const_iterator Pair = family_fractions_.begin(); Pair != family_fractions_.end(); ++Pair) {

        if ((*Pair).first.ParticleId == ParticleId || (*Pair).first.Mother1Id == ParticleId) AddParticle(ParticleId, (*Pair).second);

        else if ((*Pair).first.ParticleId == -ParticleId || (*Pair).first.Mother1Id == -ParticleId) AddParticle(-ParticleId, (*Pair).second);

        else AddParticle((*Pair).first.ParticleId, (*Pair).second);
    }
}

void hanalysis::JetInfo::ExtractFraction(const int ParticleId, const int MotherId)
{
    Print(kInformation, "Extract Fraction", ParticleId, MotherId);

    for (std::unordered_map<HFamily, float>::const_iterator Pair = family_fractions_.begin(); Pair != family_fractions_.end(); ++Pair) {

        if (std::abs((*Pair).first.ParticleId) == ParticleId && std::abs((*Pair).first.Mother1Id) == MotherId) AddParticle((*Pair).first.ParticleId, (*Pair).second);

        else AddParticle(IsrId, (*Pair).second);

    }
}

void hanalysis::JetInfo::ExtractAbsFraction(const int ParticleId)
{
    Print(kInformation, "Extract Fraction", ParticleId);
    ExtractFamilyFraction();
    for (std::unordered_map<HFamily, float>::const_iterator Pair = family_fractions_.begin(); Pair != family_fractions_.end(); ++Pair) {

        if (std::abs((*Pair).first.ParticleId) == ParticleId || std::abs((*Pair).first.Mother1Id) == ParticleId) AddParticle(ParticleId, (*Pair).second);

        else AddParticle((*Pair).first.ParticleId, (*Pair).second);
    }
}

float hanalysis::JetInfo::GetWeightSum() const
{
    Print(kDebug, "Get Weight Sum", id_fractions_.size());
    float WeightSum = std::accumulate(begin(id_fractions_), end(id_fractions_), 0.0, [](const float Previous, const std::pair<int, float> &Pair) {
        return (Previous + Pair.second);
    });
    Print(kDetailed, "Weight Sum", WeightSum);
    return WeightSum;
}

float hanalysis::JetInfo::Fraction(const int ParticleId) const
{
    Print(kInformation, "Get Fraction", ParticleId);
    if (!id_fractions_.count(ParticleId)) return 0;
    if (GetWeightSum() == 0)   return 0;
    return (id_fractions_.at(ParticleId) / GetWeightSum());
}

float hanalysis::JetInfo::MaximalFraction() const
{
    Print(kInformation, "Get Maximal Fraction");
    std::pair<int, float> MaximalWeight = *std::max_element(id_fractions_.begin(), id_fractions_.end(), SortPairs());
    if (GetWeightSum() == 0) {
        return 0;
    } else {
        return (MaximalWeight.second / GetWeightSum());
    }
}

int hanalysis::JetInfo::MaximalId() const
{
    Print(kDebug, "Get Maximal Id");
    std::pair<int, float> Max = *std::max_element(id_fractions_.begin(), id_fractions_.end(), SortPairs());
    return Max.first;
}

void hanalysis::JetInfo::PrintAllInfos(const HSeverity Severity) const
{
    Print(kDebug, "Print All Infos");
    for (std::map<int, float>::const_iterator Pair = id_fractions_.begin(); Pair != id_fractions_.end(); ++Pair) {
        if (GetWeightSum() == 0) {
            Print(Severity, "Jet Fraction", GetParticleName((*Pair).first), 0);
        } else {
            Print(Severity, "Jet Fraction", GetParticleName((*Pair).first), (*Pair).second / GetWeightSum());
        }
    }
}


void hanalysis::JetInfo::PrintAllconstituentInfos(const HSeverity Severity) const
{
    Print(kDebug, "Print All Family Infos");
    for (const auto constituent : constituents()) {
        Print(Severity, "Jet Fraction", GetParticleName(constituent.Family().ParticleId), GetParticleName(constituent.Family().Mother1Id), constituent.Family().ParticleVector.Pt(), constituent.Family().MotherVector.Pt());
    }
}
void hanalysis::JetInfo::PrintAllFamInfos(const HSeverity Severity) const
{
    Print(kDebug, "Print All Family Infos");
    for (const auto Family : family_fractions_) {
        Print(Severity, "Family Fraction", GetParticleName(Family.first.ParticleId), GetParticleName(Family.first.Mother1Id), Family.first.ParticleVector.Pt(), Family.first.MotherVector.Pt());
    }
}

fastjet::PseudoJet hanalysis::JetInfo::VertexJet() const
{
    std::vector <Constituent > vertices = ApplyVertexResolution();
    hanalysis::HFourVector Object;
    fastjet::PseudoJet Jet;
    for (const auto Vertex : vertices) Jet = fastjet::join(Jet, Object.PseudoJet(Vertex.Momentum()));
    return Jet;
}

struct AccuPerpDistance {
    float operator()(float result, const Constituent &constituent) {
        return (result + constituent.Position().Vect().Perp());
    }

};

float hanalysis::JetInfo::SumDisplacement() const
{
    Print(kDebug, "Get Jet Displacement");
    if (constituents_.size() == 0) return 0;
    std::vector <Constituent > vertices = ApplyVertexResolution();
    return std::accumulate(vertices.rbegin(), vertices.rend(), 0, AccuPerpDistance());
}

float hanalysis::JetInfo::MeanDisplacement() const
{
    Print(kDebug, "Get Jet Displacement");
    if (constituents_.size() == 0) return 0;
    std::vector <Constituent > vertices = ApplyVertexResolution();
    if (vertices.empty()) return 0;
    const float Sum = std::accumulate(vertices.rbegin(), vertices.rend(), 0, AccuPerpDistance());
    return Sum / vertices.size();
}

struct MaxPerpDistance {
  inline bool operator()(const Constituent &constituent1, const Constituent &constituent2) const {
    return (constituent1.Position().Vect().Perp() > constituent2.Position().Vect().Perp());
  }

};

float hanalysis::JetInfo::MaxDisplacement() const
{
    Print(kDebug, "Get Jet Displacement");
    if (constituents_.size() == 0) return 0;
    std::vector <Constituent > vertices = ApplyVertexResolution();
    if (vertices.empty()) return 0;
    std::sort(vertices.begin(), vertices.end(), MaxPerpDistance());
    return vertices.front().Position().Vect().Perp();
}


float hanalysis::JetInfo::VertexMass() const
{
    Print(kDebug, "Get Vertex Mass");
    std::vector <Constituent > vertices = ApplyVertexResolution();
    const float vertex_mass = std::accumulate(vertices.begin(), vertices.end(), Constituent()).Momentum().M();
    Print(kDebug, "Vertex Mass", vertex_mass);
    if (vertex_mass < .1) return 0;
    return vertex_mass;
}

float hanalysis::JetInfo::VertexEnergy() const
{
  Print(kDebug, "Get Energy Fraction");
  std::vector <Constituent > vertices = ApplyVertexResolution();
    const float vertex_energy = std::accumulate(vertices.begin(), vertices.end(), Constituent()).Momentum().E();
    return vertex_energy;
}

std::vector<Constituent> hanalysis::JetInfo::ApplyVertexResolution() const
{
    Print(kDebug, "Apply Vertex Resolution");
    std::vector <Constituent > displaced_constituents;
    Print(kDebug, "Vertex Number", constituents().size());
    if (constituents().size() == 0) return displaced_constituents;
    for (const auto & constituent : constituents()) if (constituent.Position().Vect().Perp() > detector_geometry().TrackerDistanceMin && constituent.Position().Vect().Perp() < detector_geometry().TrackerDistanceMax  && std::abs(constituent.Momentum().Rapidity()) < detector_geometry().TrackerEtaMax) displaced_constituents.emplace_back(constituent);
    Print(kDebug, "Real Vertex Number", displaced_constituents.size());
    return displaced_constituents;
}

float hanalysis::JetInfo::ElectroMagneticRadius(const fastjet::PseudoJet &Jet) const
{
    float Energy = 0;
    float Weight = 0;
    for (const auto & constituent : constituents()) if (constituent.sub_detector() == Constituent::HPhoton) {
            Energy += constituent.Momentum().Et();
            Weight += constituent.Momentum().Et() * Jet.delta_R(fastjet::PseudoJet(constituent.Momentum()));
        }
    if (Energy == 0) return 0;
    else return Weight / Energy;
}

float hanalysis::JetInfo::TrackRadius(const fastjet::PseudoJet &Jet) const
{
    float Energy = 0;
    float Weight = 0;
    for (const auto & constituent : constituents()) if (constituent.sub_detector() == Constituent::HTrack) {
            Energy += constituent.Momentum().Et();
            Weight += constituent.Momentum().Et() * Jet.delta_R(fastjet::PseudoJet(constituent.Momentum()));
        }
    if (Energy == 0) return 0;
    else return Weight / Energy;
}


struct WrongDetector {
    WrongDetector(const Constituent::SubDetector Detector) {
        this->Detector = Detector;
    }
    bool operator()(const Constituent &constituent) {
        return (constituent.sub_detector() != Detector);
    }
    Constituent::SubDetector Detector;
};

struct MaxPt {
    bool operator()(const Constituent &constituent1, const Constituent &constituent2) {
        return (constituent1.Momentum().Pt() > constituent2.Momentum().Pt());
    }
};


struct AccuPt {
    float operator()(float result, const Constituent &obj) {
        return (result + obj.Momentum().Pt());
    }

};

float hanalysis::JetInfo::LeadingTrackMomentumFraction() const
{
    std::vector<Constituent> Const = constituents();
    Const.erase(std::remove_if(Const.begin(), Const.end(), WrongDetector(Constituent::HTrack)), Const.end());
    std::sort(Const.begin(), Const.end(), MaxPt());
    float Sum = std::accumulate(Const.rbegin(), Const.rend(), 0, AccuPt());
    return Const.front().Momentum().Pt() / Sum;
}

float hanalysis::JetInfo::CoreEnergyFraction(const fastjet::PseudoJet &Jet) const
{
    float Energy = 0;
    float CoreEnergy = 0;
    for (const auto & constituent : constituents()) if (constituent.sub_detector() == Constituent::HPhoton) {
            Energy += constituent.Momentum().Et();
            if (Jet.delta_R(fastjet::PseudoJet(constituent.Momentum())) < 0.2) CoreEnergy += constituent.Momentum().Et();
        }
    if (Energy == 0) return 0;
    else return CoreEnergy / Energy;

}

// float hanalysis::JetInfo::CoreEnergyFraction(const fastjet::PseudoJet &Jet)
// {
//   float Energy = 0;
//   float CoreEnergy = 0;
//   for (const auto & constituent : constituents()) if (constituent.sub_detector() == Constituent::HPhoton) {
//     Energy += constituent.Momentum().Et();
//     if(Jet.delta_R(fastjet::PseudoJet(constituent.Momentum()))<0.2) CoreEnergy += constituent.Momentum().Et();
//   }
//   return CoreEnergy / Energy;
//
// }

float hanalysis::JetInfo::ElectroMagneticFraction() const
{
    float EMEnergy = 0;
    float Energy = 0;
    for (const auto & constituent : constituents()) {
        Energy += constituent.Momentum().Et();
        if (constituent.sub_detector() == Constituent::HPhoton) EMEnergy += constituent.Momentum().Et();
    }
    if (Energy == 0) return 0;
    else return EMEnergy / Energy;

}

float hanalysis::JetInfo::ClusterMass() const
{
    fastjet::PseudoJet Jet;
    for (const auto & constituent : constituents()) {
        if (constituent.sub_detector() == Constituent::HPhoton) Jet += constituent.Momentum();
    }
    return Jet.m();

}

float hanalysis::JetInfo::TrackMass() const
{
    fastjet::PseudoJet Jet;
    for (const auto & constituent : constituents()) {
        if (constituent.sub_detector() == Constituent::HTrack) Jet += constituent.Momentum();
    }
    return Jet.m();

}



