# include "HJetInfo.hh"

HJetInfo::HJetInfo()
{

    Print(2, "Constructor");
//     Debug = 4;

}

void HJetInfo::AddConstituent(int ConstituentId, float ParticlePt)
{

    Print(1, "Add Constituent", ConstituentId);
    Print(3, "Constituent Pt", ParticlePt);

    JetFractions[ConstituentId] += ParticlePt;

    Print(3, "Saved Pt", JetFractions[ConstituentId]);


}

float HJetInfo::GetPtSum() const
{

    Print(1, "Get Sum");

    Print(3, "JetFraction size ", JetFractions.size());

    float Result = accumulate(begin(JetFractions), end(JetFractions), 0.0, [](const float Previous, const pair<int, float> &Pair) {

        return (Previous + Pair.second);

    });

    Print(3, "Pt Sum", Result);

    return Result;

}

float HJetInfo::GetFraction(int ParticleId)
{

    Print(1, "Get Fraction");

    if (GetPtSum() == 0) {

        return 0;

    } else {

        return (JetFractions[ParticleId] / GetPtSum());

    }
}

float HJetInfo::GetMaximalFraction() const
{

    Print(1, "Get Maximal Fraction");

    pair<int, float> MaximalPt = *max_element(JetFractions.begin(), JetFractions.end(), SortPairs());

    if (GetPtSum() == 0) {

        return 0;

    } else {

        return (MaximalPt.second / GetPtSum());

    }

}

int HJetInfo::GetMaximalId() const
{

    Print(1, "Get Maximal Id");

    pair<int, float> Max = *max_element(JetFractions.begin(), JetFractions.end(), SortPairs());

    return Max.first;

}

void HJetInfo::Clear()
{

    Print(1, "Clear");

    JetFractions.clear();

}

void HJetInfo::PrintAllInfos() const
{

    Print(1, "Print All Infos");

    for (map<int, float>::const_iterator Iterator = JetFractions.begin(); Iterator != JetFractions.end(); ++Iterator) {
        
        if (GetPtSum() == 0) {
            
            Print(-1, "FatJet", (*Iterator).first, 0);
            
        } else {
            
            Print(-1, "FatJet", (*Iterator).first, (*Iterator).second / GetPtSum());
            
        }
        
    }

}

