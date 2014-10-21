# include "HJetInfo.hh"

using std::pair;

HJetInfo::HJetInfo()
{

    Print(3, "Constructor");
//     Debug = 4;

}

void HJetInfo::AddConstituent(const int ConstituentId, const float Weight)
{

    Print(2, "Add Constituent", ConstituentId);
    Print(4, "Constituent Pt", Weight);

    JetFractions[ConstituentId] += Weight;

    Print(4, "Saved Pt", JetFractions[ConstituentId]);


}

float HJetInfo::GetPtSum() const
{

    Print(2, "Get Sum");

    Print(4, "JetFraction size ", JetFractions.size());

    float Result = accumulate(begin(JetFractions), end(JetFractions), 0.0, [](const float Previous, const pair<int, float> &Pair) {

        return (Previous + Pair.second);

    });

    Print(4, "Pt Sum", Result);

    return Result;

}

float HJetInfo::GetFraction(const int ParticleId) const
{

    Print(2, "Get Fraction");

    if (GetPtSum() == 0) {

        return 0;

    } else {

        return (JetFractions.at(ParticleId) / GetPtSum());

    }
}

float HJetInfo::GetMaximalFraction() const
{

    Print(2, "Get Maximal Fraction");

    pair<int, float> MaximalWeight = *max_element(JetFractions.begin(), JetFractions.end(), SortPairs());

    if (GetPtSum() == 0) {

        return 0;

    } else {

        return (MaximalWeight.second / GetPtSum());

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
//     if (GetPtSum() == 0) {
//
//         return 0;
//
//     } else {
//
//         return (MaximalPt.second / GetPtSum());
//
//     }
//
// }

int HJetInfo::GetMaximalId() const
{

    Print(2, "Get Maximal Id");

    pair<int, float> Max = *max_element(JetFractions.begin(), JetFractions.end(), SortPairs());

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

    for (map<int, float>::const_iterator Iterator = JetFractions.begin(); Iterator != JetFractions.end(); ++Iterator) {

        if (GetPtSum() == 0) {

            Print(Severity, "FatJet", (*Iterator).first, 0);

        } else {

            Print(Severity, "FatJet", (*Iterator).first, (*Iterator).second / GetPtSum());

        }

    }

}

