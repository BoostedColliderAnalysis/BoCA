# ifndef HJetInfo_hh
# define HJetInfo_hh

# include "HObject.hh"
# include <map>

using std::accumulate;
using std::map;
using std::max_element;


class HJetInfo: public PseudoJet::UserInfoBase, public HObject
{

public:

    HJetInfo() {

        JetFractions[EmptyId] = 0;
        JetFractions[BottomId] = 0;
        JetFractions[-BottomId] = 0;
        JetFractions[TopId] = 0;
        JetFractions[-TopId] = 0;
        JetFractions[HeavyHiggsId] = 0;
        JetFractions[-HeavyHiggsId] = 0;
        JetFractions[CpvHiggsId] = 0;
        JetFractions[-CpvHiggsId] = 0;

    };

    void Constituent(int ConstituentId, float ParticlePt) {

        JetFractions[ConstituentId] += ParticlePt;

    }

    float GetSum() {

        Print(1, "Get Sum");

        const float result = accumulate(begin(JetFractions), end(JetFractions), 0, [](const float Previous, const pair<int, float> &Pair) {
            
            return Previous + Pair.second;
            
        });

        Print(-1, "Get Sum", result);

        return result;

    }

    float GetFraction(int ParticleId) {

        return JetFractions[ParticleId] / GetSum();

    }

    float GetMaximalFraction() {

        pair<int, float> Max = *max_element(JetFractions.begin(), JetFractions.end(), SortPairs());

        return Max.second / GetSum();

    }


private:

    map<int, float> JetFractions;



};

# endif
