# ifndef HJetInfo_hh
# define HJetInfo_hh

# include <map>

# include "HObject.hh"

using std::map;
using std::accumulate;


class HJetInfo:public HObject, public PseudoJet::UserInfoBase
{

public:

    HJetInfo();

    void AddConstituent(int, float);

    float GetPtSum() const;

    float GetFraction(int);

    float GetMaximalFraction() const;
    
    int GetMaximalId() const;
    
    void PrintAllInfos() const;
    
    void Clear();

private:

    map<int, float> JetFractions;

    string ClassName() const {

        return ("HJetInfo");

    };

};

# endif
