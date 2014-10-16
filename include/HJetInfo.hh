# ifndef HJetInfo_hh
# define HJetInfo_hh

# include <map>

# include "HObject.hh"

using std::map;
using std::accumulate;


class HJetInfo: public HObject, public PseudoJet::UserInfoBase
{

public:

    HJetInfo();

    void AddConstituent(const int, const float);

    float GetFraction(int) const;

    float GetMaximalFraction() const;

    int GetMaximalId() const;

    void PrintAllInfos() const;

    void Clear();

    bool HasParticle(const int) const;
    
protected:
    
    string ClassName() const {
        
        return ("HJetInfo");
        
    };

private:

    float GetPtSum() const;

    map<int, float> JetFractions;

};

# endif
