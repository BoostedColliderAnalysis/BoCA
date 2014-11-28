# include "HJetInfo.hh"


hanalysis::HJetInfo::HJetInfo()
{

    Print(HDebug, "Constructor");
//     Debug = 4;

}

void hanalysis::HJetInfo::AddConstituent(const int ConstituentId, const float Weight)
{

    Print(HDebug, "Add Constituent", ConstituentId, Weight);

    JetFractions[ConstituentId] += Weight;

    Print(HDetailed, "Saved Weight", JetFractions[ConstituentId]);

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

float hanalysis::HJetInfo::GetFraction(const int ParticleId) const
{

    Print(HInformation, "Get Fraction", ParticleId);

    if (!JetFractions.count(ParticleId)) return 0;

    if (GetWeightSum() == 0)   return 0;

    return (JetFractions.at(ParticleId) / GetWeightSum());

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

            Print(Severity, "Jet Fraction", (*Pair).first, 0);

        } else {

            Print(Severity, "Jet Fraction", (*Pair).first, (*Pair).second / GetWeightSum());

        }

    }

}
namespace hanalysis
{
float HJetInfo::GetJetDisplacement() const
{

    Print(HDebug, "Get Jet Displacement");
    // TODO is there a way to get rid of the const?
    if (Vertices.size() == 0) return 0;
    std::vector<HConstituent> TempVertices = Vertices;
    std::sort(TempVertices.begin(), TempVertices.end(), SortByDistance());
    return (TempVertices.front().Position.Vect().Mag());
}
}


