# include "HJetInfo.hh"


HJetInfo::HJetInfo()
{

    Print(3, "Constructor");
//     Debug = 4;

}

void HJetInfo::AddConstituent(const int ConstituentId, const float Weight)
{

    Print(2, "Add Constituent", ConstituentId, Weight);

    JetFractions[ConstituentId] += Weight;

    Print(4, "Saved Weight", JetFractions[ConstituentId]);

}

float HJetInfo::GetWeightSum() const
{

    Print(2, "Get Weight Sum", JetFractions.size());

    float WeightSum = std::accumulate(begin(JetFractions), end(JetFractions), 0.0, [](const float Previous, const pair<int, float> &Pair) {

        return (Previous + Pair.second);

    });

    Print(4, "Weight Sum", WeightSum);

    return WeightSum;

}

float HJetInfo::GetFraction(const int ParticleId) const
{

    Print(2, "Get Fraction", ParticleId);

    if (GetWeightSum() == 0) {

        return 0;

    } else {

        return (JetFractions.at(ParticleId) / GetWeightSum());

    }
    
}

float HJetInfo::GetMaximalFraction() const
{

    Print(2, "Get Maximal Fraction");

    pair<int, float> MaximalWeight = *std::max_element(JetFractions.begin(), JetFractions.end(), SortPairs());

    if (GetWeightSum() == 0) {

        return 0;

    } else {

        return (MaximalWeight.second / GetWeightSum());

    }

}

bool HJetInfo::HasParticle(const int ParticleId) const
{

    Print(2, "Has Particle", ParticleId);

    if (JetFractions.find(ParticleId) == JetFractions.end()) return 0;

    return 1;

}

// float HJetInfo::GetMaximalFraction() const
// {
//
//     Print(2, "Get Maximal Fraction");
//
//     pair<int, float> MaximalPt = *max_element(JetFractions.begin(), JetFractions.end(), SortPairs());
//     std::nth_element(JetFractions.begin(), JetFractions.begin() + 1, JetFractions.end(), SortPairs());
//
//     if (GetWeightSum() == 0) {
//
//         return 0;
//
//     } else {
//
//         return (MaximalPt.second / GetWeightSum());
//
//     }
//
// }

int HJetInfo::GetMaximalId() const
{

    Print(2, "Get Maximal Id");

    pair<int, float> Max = *std::max_element(JetFractions.begin(), JetFractions.end(), SortPairs());

    return Max.first;

}

void HJetInfo::Clear()
{

    Print(2, "Clear");

    JetFractions.clear();

}

void HJetInfo::PrintAllInfos(int Severity) const
{

    Print(2, "Print All Infos");

    for (map<int, float>::const_iterator Pair = JetFractions.begin(); Pair != JetFractions.end(); ++Pair) {

        if (GetWeightSum() == 0) {

            Print(Severity, "Jet Fraction", (*Pair).first, 0);

        } else {

            Print(Severity, "Jet Fraction", (*Pair).first, (*Pair).second / GetWeightSum());

        }

    }

}

