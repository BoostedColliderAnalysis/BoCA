# include "HJetInfo.hh"

hanalysis::HJetInfo::HJetInfo()
{
//     Debug = 4;
    Print(HDebug, "Constructor");
    BTag = 0;
}

void hanalysis::HJetInfo::AddConstituent(const int ConstituentId, const float Weight)
{
    Print(HDebug, "Add Constituent", ConstituentId, Weight);
    JetFractions[ConstituentId] += Weight;
    Print(HDetailed, "Saved Weight", JetFractions[ConstituentId]);
}

void hanalysis::HJetInfo::AddFamily(const HFamily Family, const float Weight)
{
    Print(HDebug, "Add Constituent", Family.ParticleId, Family.Mother1Id, Weight);
    JetFamily[Family] += Weight;
//   Print(HDetailed, "Saved Weight", JetFamily[Family].ParticleId, JetFamily[Family].Mother1Id);
}

float hanalysis::HJetInfo::GetWeightSum() const
{
    Print(HDebug, "Get Weight Sum", JetFractions.size());
    float WeightSum = std::accumulate(begin(JetFractions), end(JetFractions), 0.0, [](const float Previous, const std::pair<int, float> &Pair) {
        return (Previous + Pair.second);
    });
    Print(HDetailed, "Weight Sum", WeightSum);
    return WeightSum;
}

float hanalysis::HJetInfo::GetFamilyWeightSum() const
{
    Print(HDebug, "Get Weight Sum", JetFamily.size());
    float WeightSum = std::accumulate(begin(JetFamily), end(JetFamily), 0.0, [](const float Previous, const std::pair<HFamily, float> &Pair) {
        return (Previous + Pair.second);
    });
    Print(HDetailed, "Weight Sum", WeightSum);
    return WeightSum;
}

float hanalysis::HJetInfo::GetFraction(const int ParticleId) const
{
    Print(HInformation, "Get Fraction", ParticleId);
    if (!JetFractions.count(ParticleId)) return 0;
    if (GetWeightSum() == 0)   return 0;
    return (JetFractions.at(ParticleId) / GetWeightSum());
}

void hanalysis::HJetInfo::ExtractFraction(const int ParticleId)
{
    Print(HInformation, "Extract Fraction", ParticleId);
    for (std::unordered_map<HFamily, float>::const_iterator Pair = JetFamily.begin(); Pair != JetFamily.end(); ++Pair) {

        if ((*Pair).first.ParticleId == ParticleId || (*Pair).first.Mother1Id == ParticleId) AddConstituent(ParticleId, (*Pair).second);

        else if ((*Pair).first.ParticleId == -ParticleId || (*Pair).first.Mother1Id == -ParticleId) AddConstituent(-ParticleId, (*Pair).second);

        else AddConstituent((*Pair).first.ParticleId, (*Pair).second);
    }
}

void hanalysis::HJetInfo::ExtractFraction(const int ParticleId, const int MotherId)
{
    Print(HInformation, "Extract Fraction", ParticleId, MotherId);

    for (std::unordered_map<HFamily, float>::const_iterator Pair = JetFamily.begin(); Pair != JetFamily.end(); ++Pair) {

        if (std::abs((*Pair).first.ParticleId) == ParticleId && std::abs((*Pair).first.Mother1Id) == MotherId) AddConstituent((*Pair).first.ParticleId, (*Pair).second);

        else AddConstituent(IsrId, (*Pair).second);

    }
}

float hanalysis::HJetInfo::GetFamily(const HFamily Family) const
{
    Print(HInformation, "Get Fraction", Family.ParticleId);
    if (!JetFamily.count(Family)) return 0;
    if (GetWeightSum() == 0)   return 0;
    return (JetFamily.at(Family) / GetWeightSum());
}

float hanalysis::HJetInfo::GetMaximalFraction() const
{
    Print(HInformation, "Get Maximal Fraction");
    std::pair<int, float> MaximalWeight = *std::max_element(JetFractions.begin(), JetFractions.end(), SortPairs());
    if (GetWeightSum() == 0) {
        return 0;
    } else {
        return (MaximalWeight.second / GetWeightSum());
    }
}

bool hanalysis::HJetInfo::HasParticle(const int ParticleId) const
{
    Print(HInformation, "Has Particle", ParticleId);
    if (JetFractions.find(ParticleId) == JetFractions.end()) return 0;
    return 1;
}

int hanalysis::HJetInfo::GetMaximalId() const
{
    Print(HDebug, "Get Maximal Id");
    std::pair<int, float> Max = *std::max_element(JetFractions.begin(), JetFractions.end(), SortPairs());
    return Max.first;
}

void hanalysis::HJetInfo::Clear()
{
    Print(HInformation, "Clear");
    JetFractions.clear();
}

void hanalysis::HJetInfo::PrintAllInfos(const HSeverity Severity) const
{
    Print(HDebug, "Print All Infos");
    for (std::map<int, float>::const_iterator Pair = JetFractions.begin(); Pair != JetFractions.end(); ++Pair) {
        if (GetWeightSum() == 0) {
            Print(Severity, "Jet Fraction", GetParticleName((*Pair).first), 0);
        } else {
            Print(Severity, "Jet Fraction", GetParticleName((*Pair).first), (*Pair).second / GetWeightSum());
        }
    }
}

void hanalysis::HJetInfo::PrintAllFamilyInfos(const HSeverity Severity) const
{
    Print(HDebug, "Print All Infos");
    int Counter = 1;
    for (std::unordered_map<HFamily, float>::const_iterator Pair = JetFamily.begin(); Pair != JetFamily.end(); ++Pair) {
        if (GetFamilyWeightSum() == 0) {
            Print(Severity, "Jet Family Fraction", GetParticleName((*Pair).first.ParticleId), GetParticleName((*Pair).first.Mother1Id), 0);
        } else {
            Print(Severity, "Jet Family Fraction", Counter, GetParticleName((*Pair).first.ParticleId), GetParticleName((*Pair).first.Mother1Id), (*Pair).second / GetFamilyWeightSum());
        }
        ++Counter;
    }
}

float hanalysis::HJetInfo::GetJetDisplacement() const
{
    Print(HDebug, "Get Jet Displacement"); // TODO is there a way to get rid of the const?
    if (Vertices.size() == 0) return 0;
    std::vector<HConstituent> TempVertices = Vertices;
    std::sort(TempVertices.begin(), TempVertices.end(), SortByDistance());
    if (TempVertices.front().Position.Vect().Mag() > SecondaryVertexResolution) return TempVertices.front().Position.Vect().Mag();
    return 0;
}


float hanalysis::HJetInfo::GetVertexMass() const
{
    Print(HDebug, "Get Vertex Mass");
    std::vector <HConstituent > RealVertices = ApplyVertexResolution();
    HConstituent Vertex;
    const float VertexMass = std::accumulate(RealVertices.begin(), RealVertices.end(), Vertex).Momentum.M();
    if (VertexMass < .1) return 0;
    return VertexMass;
}

float hanalysis::HJetInfo::GetVertexEnergy() const
{
    Print(HDebug, "Get Energy Fraction");
    float VertexEnergy = 0;
    for (const auto & Vertex : Vertices) if (Vertex.Position.Vect().Mag() > SecondaryVertexResolution) VertexEnergy += Vertex.Momentum.E();
    return VertexEnergy;
}

std::vector<HConstituent> hanalysis::HJetInfo::ApplyVertexResolution() const
{
    Print(HDebug, "Apply Vertex Resolution");
    std::vector <HConstituent > RealVertices;
    if (Vertices.size() == 0) return RealVertices;
    for (std::vector <HConstituent >::const_iterator Vertex = Vertices.begin(); Vertex != Vertices.end(); ++Vertex) {
        if ((*Vertex).Position.Vect().Mag() < SecondaryVertexResolution) {
            RealVertices.push_back(*Vertex);
        }
    }
    return RealVertices;
}

