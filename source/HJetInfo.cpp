# include "HJetInfo.hh"
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


HDetectorGeometry::HDetectorGeometry()
{

//  HDetectorType DetectorType = Spp;
   HDetectorType DetectorType = CMS;
  const float jet_radius_parameter = 1;
    switch (DetectorType) {
    case CMS :
        JetMinPt = 20;
        JetConeSize = 0.5;
        MinCellResolution = .1;
        MinCellPt = .5;
        TrackerEtaMax = 2.5;
        TrackerDistanceMin = 0.1;
        TrackerDistanceMax = 1000;
        JetDefinition = fastjet::JetDefinition(fastjet::antikt_algorithm, jet_radius_parameter);
        SubJetDefinition = fastjet::JetDefinition(fastjet::kt_algorithm, jet_radius_parameter);
    case Spp:
        JetMinPt = 40;
        JetConeSize = 0.5;
        MinCellResolution = .1;
        MinCellPt = .5;
        TrackerEtaMax = 3.5;
        TrackerDistanceMin = 0.1;
        TrackerDistanceMax = 1000;
        JetDefinition = fastjet::JetDefinition(fastjet::antikt_algorithm, jet_radius_parameter);
        SubJetDefinition = fastjet::JetDefinition(fastjet::kt_algorithm, jet_radius_parameter);
    }
}



hanalysis::HJetInfo::HJetInfo() : detector_geometry_()
// : hanalysis::HTag(* new HJetInfoPrivate)
{
//     Debug = 4;
    Print(HDebug, "Constructor");
    BTagM = 0;
}

hanalysis::HJetInfo::HJetInfo(const int NewBTag) : detector_geometry_()
// : hanalysis::HTag(* new HJetInfoPrivate)
{
    BTagM = NewBTag;
}

hanalysis::HJetInfo::HJetInfo(const HConstituent &NewConstituent) : detector_geometry_()
// : hanalysis::HTag(* new HJetInfoPrivate)
{
    constituents_.push_back(NewConstituent);
    BTagM = 0;
}

hanalysis::HJetInfo::HJetInfo(const std::vector<HConstituent> &NewConstituents) : detector_geometry_()
// : hanalysis::HTag(* new HJetInfoPrivate)
{
    constituents_ = NewConstituents;
    BTagM = 0;
}

hanalysis::HJetInfo::HJetInfo(const std::vector<HConstituent> &NewConstituents, const int NewBTag) : detector_geometry_()
// : hanalysis::HTag(* new HJetInfoPrivate)
{
    constituents_ = NewConstituents;
    BTagM = NewBTag;
}

void hanalysis::HJetInfo::AddFamily(const HFamily &Family, const float Weight)
{
    Print(HDebug, "Add Constituent", Family.ParticleId, Family.Mother1Id, Weight);
    FamilyFractionsM[Family] += Weight;
//   Print(HDetailed, "Saved Weight", IdFractions[Family]);
}

void hanalysis::HJetInfo::ExtractFamilyFraction()
{

    Print(HInformation, "Extract Family Fraction");

    for (const auto & Constituent : Constituents()) {
        FamilyFractionsM[Constituent.Family()] += Constituent.Momentum().Pt();
    }
}

hanalysis::HFamily hanalysis::HJetInfo::MaximalFamily()
{

    Print(HDebug, "Get Maximal Id");
    std::pair<HFamily, float> Max = *std::max_element(FamilyFractionsM.begin(), FamilyFractionsM.end(), SortPairs());
    return Max.first;
}

void hanalysis::HJetInfo::AddParticle(const int ConstituentId, const float Weight)
{
    Print(HDebug, "Add Constituent", ConstituentId, Weight);
    IdFractions[ConstituentId] += Weight;
    Print(HDetailed, "Saved Weight", IdFractions[ConstituentId]);
}

void hanalysis::HJetInfo::ExtractFraction(const int ParticleId)
{
    Print(HInformation, "Extract Fraction", ParticleId);
    ExtractFamilyFraction();
    for (std::unordered_map<HFamily, float>::const_iterator Pair = FamilyFractionsM.begin(); Pair != FamilyFractionsM.end(); ++Pair) {

        if ((*Pair).first.ParticleId == ParticleId || (*Pair).first.Mother1Id == ParticleId) AddParticle(ParticleId, (*Pair).second);

        else if ((*Pair).first.ParticleId == -ParticleId || (*Pair).first.Mother1Id == -ParticleId) AddParticle(-ParticleId, (*Pair).second);

        else AddParticle((*Pair).first.ParticleId, (*Pair).second);
    }
}

void hanalysis::HJetInfo::ExtractFraction(const int ParticleId, const int MotherId)
{
    Print(HInformation, "Extract Fraction", ParticleId, MotherId);

    for (std::unordered_map<HFamily, float>::const_iterator Pair = FamilyFractionsM.begin(); Pair != FamilyFractionsM.end(); ++Pair) {

        if (std::abs((*Pair).first.ParticleId) == ParticleId && std::abs((*Pair).first.Mother1Id) == MotherId) AddParticle((*Pair).first.ParticleId, (*Pair).second);

        else AddParticle(IsrId, (*Pair).second);

    }
}

void hanalysis::HJetInfo::ExtractAbsFraction(const int ParticleId)
{
    Print(HInformation, "Extract Fraction", ParticleId);
    ExtractFamilyFraction();
    for (std::unordered_map<HFamily, float>::const_iterator Pair = FamilyFractionsM.begin(); Pair != FamilyFractionsM.end(); ++Pair) {

        if (std::abs((*Pair).first.ParticleId) == ParticleId || std::abs((*Pair).first.Mother1Id) == ParticleId) AddParticle(ParticleId, (*Pair).second);

        else AddParticle((*Pair).first.ParticleId, (*Pair).second);
    }
}

float hanalysis::HJetInfo::GetWeightSum() const
{
    Print(HDebug, "Get Weight Sum", IdFractions.size());
    float WeightSum = std::accumulate(begin(IdFractions), end(IdFractions), 0.0, [](const float Previous, const std::pair<int, float> &Pair) {
        return (Previous + Pair.second);
    });
    Print(HDetailed, "Weight Sum", WeightSum);
    return WeightSum;
}

float hanalysis::HJetInfo::Fraction(const int ParticleId) const
{
    Print(HInformation, "Get Fraction", ParticleId);
    if (!IdFractions.count(ParticleId)) return 0;
    if (GetWeightSum() == 0)   return 0;
    return (IdFractions.at(ParticleId) / GetWeightSum());
}

float hanalysis::HJetInfo::MaximalFraction() const
{
    Print(HInformation, "Get Maximal Fraction");
    std::pair<int, float> MaximalWeight = *std::max_element(IdFractions.begin(), IdFractions.end(), SortPairs());
    if (GetWeightSum() == 0) {
        return 0;
    } else {
        return (MaximalWeight.second / GetWeightSum());
    }
}

int hanalysis::HJetInfo::MaximalId() const
{
    Print(HDebug, "Get Maximal Id");
    std::pair<int, float> Max = *std::max_element(IdFractions.begin(), IdFractions.end(), SortPairs());
    return Max.first;
}

void hanalysis::HJetInfo::PrintAllInfos(const HSeverity Severity) const
{
    Print(HDebug, "Print All Infos");
    for (std::map<int, float>::const_iterator Pair = IdFractions.begin(); Pair != IdFractions.end(); ++Pair) {
        if (GetWeightSum() == 0) {
            Print(Severity, "Jet Fraction", GetParticleName((*Pair).first), 0);
        } else {
            Print(Severity, "Jet Fraction", GetParticleName((*Pair).first), (*Pair).second / GetWeightSum());
        }
    }
}


void hanalysis::HJetInfo::PrintAllConstituentInfos(const HSeverity Severity) const
{
    Print(HDebug, "Print All Family Infos");
    for (const auto Constituent : Constituents()) {
        Print(Severity, "Jet Fraction", GetParticleName(Constituent.Family().ParticleId), GetParticleName(Constituent.Family().Mother1Id), Constituent.Family().ParticleVector.Pt(), Constituent.Family().MotherVector.Pt());
    }
}
void hanalysis::HJetInfo::PrintAllFamInfos(const HSeverity Severity) const
{
    Print(HDebug, "Print All Family Infos");
    for (const auto Family : FamilyFractionsM) {
        Print(Severity, "Family Fraction", GetParticleName(Family.first.ParticleId), GetParticleName(Family.first.Mother1Id), Family.first.ParticleVector.Pt(), Family.first.MotherVector.Pt());
    }
}

fastjet::PseudoJet hanalysis::HJetInfo::VertexJet() const
{
    std::vector <HConstituent > vertices = ApplyVertexResolution();
    hanalysis::HFourVector Object;
    fastjet::PseudoJet Jet;
    for (const auto Vertex : vertices) Jet = fastjet::join(Jet, Object.PseudoJet(Vertex.Momentum()));
    return Jet;
}

struct AccuPerpDistance {
    float operator()(float result, const HConstituent &constituent) {
        return (result + constituent.Position().Vect().Perp());
    }

};

float hanalysis::HJetInfo::SumDisplacement() const
{
    Print(HDebug, "Get Jet Displacement");
    if (constituents_.size() == 0) return 0;
    std::vector <HConstituent > vertices = ApplyVertexResolution();
    return std::accumulate(vertices.rbegin(), vertices.rend(), 0, AccuPerpDistance());
}

float hanalysis::HJetInfo::MeanDisplacement() const
{
    Print(HDebug, "Get Jet Displacement");
    if (constituents_.size() == 0) return 0;
    std::vector <HConstituent > vertices = ApplyVertexResolution();
    if (vertices.size() < 1) return 0;
    const float Sum = std::accumulate(vertices.rbegin(), vertices.rend(), 0, AccuPerpDistance());
    return Sum / vertices.size();
}

struct MaxPerpDistance {
  inline bool operator()(const HConstituent &Constituent1, const HConstituent &Constituent2) const {
    return (Constituent1.Position().Vect().Perp() > Constituent2.Position().Vect().Perp());
  }

};

float hanalysis::HJetInfo::MaxDisplacement() const
{
    Print(HDebug, "Get Jet Displacement");
    if (constituents_.size() == 0) return 0;
    std::vector <HConstituent > vertices = ApplyVertexResolution();
    if (vertices.size() < 1) return 0;
    std::sort(vertices.begin(), vertices.end(), MaxPerpDistance());
    return vertices.front().Position().Vect().Perp();
}


float hanalysis::HJetInfo::VertexMass() const
{
    Print(HDebug, "Get Vertex Mass");
    std::vector <HConstituent > vertices = ApplyVertexResolution();
    const float vertex_mass = std::accumulate(vertices.begin(), vertices.end(), HConstituent()).Momentum().M();
    Print(HDebug, "Vertex Mass", vertex_mass);
    if (vertex_mass < .1) return 0;
    return vertex_mass;
}

float hanalysis::HJetInfo::VertexEnergy() const
{
  Print(HDebug, "Get Energy Fraction");
  std::vector <HConstituent > vertices = ApplyVertexResolution();
    const float vertex_energy = std::accumulate(vertices.begin(), vertices.end(), HConstituent()).Momentum().E();
    return vertex_energy;
}

std::vector<HConstituent> hanalysis::HJetInfo::ApplyVertexResolution() const
{
    Print(HDebug, "Apply Vertex Resolution");
    std::vector <HConstituent > displaced_constituents;
    Print(HDebug, "Vertex Number", constituents().size());
    if (constituents().size() == 0) return displaced_constituents;
    for (const auto & constituent : constituents()) if (constituent.Position().Vect().Perp() > detector_geometry().TrackerDistanceMin && constituent.Position().Vect().Perp() < detector_geometry().TrackerDistanceMax  && std::abs(constituent.Momentum().Rapidity()) < detector_geometry().TrackerEtaMax) displaced_constituents.push_back(constituent);
    Print(HDebug, "Real Vertex Number", displaced_constituents.size());
    return displaced_constituents;
}

float hanalysis::HJetInfo::ElectroMagneticRadius(const fastjet::PseudoJet &Jet) const
{
    float Energy = 0;
    float Weight = 0;
    for (const auto & Constituent : Constituents()) if (Constituent.sub_detector() == HConstituent::HPhoton) {
            Energy += Constituent.Momentum().Et();
            Weight += Constituent.Momentum().Et() * Jet.delta_R(fastjet::PseudoJet(Constituent.Momentum()));
        }
    if (Energy == 0) return 0;
    else return Weight / Energy;
}

float hanalysis::HJetInfo::TrackRadius(const fastjet::PseudoJet &Jet) const
{
    float Energy = 0;
    float Weight = 0;
    for (const auto & Constituent : Constituents()) if (Constituent.sub_detector() == HConstituent::HTrack) {
            Energy += Constituent.Momentum().Et();
            Weight += Constituent.Momentum().Et() * Jet.delta_R(fastjet::PseudoJet(Constituent.Momentum()));
        }
    if (Energy == 0) return 0;
    else return Weight / Energy;
}


struct WrongDetector {
    WrongDetector(const HConstituent::SubDetector Detector) {
        this->Detector = Detector;
    }
    bool operator()(const HConstituent &Constituent) {
        return (Constituent.sub_detector() != Detector);
    }
    HConstituent::SubDetector Detector;
};

struct MaxPt {
    bool operator()(const HConstituent &Constituent1, const HConstituent &Constituent2) {
        return (Constituent1.Momentum().Pt() > Constituent2.Momentum().Pt());
    }
};


struct AccuPt {
    float operator()(float result, const HConstituent &obj) {
        return (result + obj.Momentum().Pt());
    }

};

float hanalysis::HJetInfo::LeadingTrackMomentumFraction() const
{
    std::vector<HConstituent> Const = Constituents();
    Const.erase(std::remove_if(Const.begin(), Const.end(), WrongDetector(HConstituent::HTrack)), Const.end());
    std::sort(Const.begin(), Const.end(), MaxPt());
    float Sum = std::accumulate(Const.rbegin(), Const.rend(), 0, AccuPt());
    return Const.front().Momentum().Pt() / Sum;
}

float hanalysis::HJetInfo::CoreEnergyFraction(const fastjet::PseudoJet &Jet) const
{
    float Energy = 0;
    float CoreEnergy = 0;
    for (const auto & Constituent : Constituents()) if (Constituent.sub_detector() == HConstituent::HPhoton) {
            Energy += Constituent.Momentum().Et();
            if (Jet.delta_R(fastjet::PseudoJet(Constituent.Momentum())) < 0.2) CoreEnergy += Constituent.Momentum().Et();
        }
    if (Energy == 0) return 0;
    else return CoreEnergy / Energy;

}

// float hanalysis::HJetInfo::CoreEnergyFraction(const fastjet::PseudoJet &Jet)
// {
//   float Energy = 0;
//   float CoreEnergy = 0;
//   for (const auto & Constituent : Constituents()) if (Constituent.sub_detector() == HConstituent::HPhoton) {
//     Energy += Constituent.Momentum().Et();
//     if(Jet.delta_R(fastjet::PseudoJet(Constituent.Momentum()))<0.2) CoreEnergy += Constituent.Momentum().Et();
//   }
//   return CoreEnergy / Energy;
//
// }

float hanalysis::HJetInfo::ElectroMagneticFraction() const
{
    float EMEnergy = 0;
    float Energy = 0;
    for (const auto & Constituent : Constituents()) {
        Energy += Constituent.Momentum().Et();
        if (Constituent.sub_detector() == HConstituent::HPhoton) EMEnergy += Constituent.Momentum().Et();
    }
    if (Energy == 0) return 0;
    else return EMEnergy / Energy;

}

float hanalysis::HJetInfo::ClusterMass() const
{
    fastjet::PseudoJet Jet;
    for (const auto & Constituent : Constituents()) {
        if (Constituent.sub_detector() == HConstituent::HPhoton) Jet += Constituent.Momentum();
    }
    return Jet.m();

}

float hanalysis::HJetInfo::TrackMass() const
{
    fastjet::PseudoJet Jet;
    for (const auto & Constituent : Constituents()) {
        if (Constituent.sub_detector() == HConstituent::HTrack) Jet += Constituent.Momentum();
    }
    return Jet.m();

}



