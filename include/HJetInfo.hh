# ifndef HJetInfo_hh
# define HJetInfo_hh

# include <map>
# include <unordered_map>
# include <numeric>

# include "HTag.hh"
# include "HJetTag.hh"
# include "HFourVector.hh"

class HConstituent {

public:

    HConstituent() {};

    HConstituent(const TLorentzVector &NewMomentum,const TLorentzVector NewPosition,const hanalysis::HFamily& NewFamily) {
        MomentumM = NewMomentum;
        PositionM = NewPosition;
        FamilyM = NewFamily;
    }

    HConstituent(const TLorentzVector &NewMomentum,const hanalysis::HFamily& NewFamily) {
        MomentumM = NewMomentum;
        FamilyM = NewFamily;
    }

    void SetPosition(const TLorentzVector &NewPosition) {
        PositionM = NewPosition;
    }

    void SetPosition(const float X,const float Y, const float Z, const float T) {
        PositionM.SetXYZT(X,Y,Z,T);
    }

    void SetMomentum(const TLorentzVector &NewMomentum) {
        MomentumM = NewMomentum;
    }

    void SetFamily(const hanalysis::HFamily &NewFamily) {
        FamilyM = NewFamily;
    }

    TLorentzVector Position() const {
        return PositionM;
    }

    TLorentzVector Momentum() const {
        return MomentumM;
    }

    hanalysis::HFamily Family() const {
        return FamilyM;
    }

    HConstituent operator+(HConstituent &Constituent) {
//         HConstituent NewVertex;
//         NewVertex.Position = this->Position + Constituent.Position;
//         NewVertex.Momentum = this->Momentum + Constituent.Momentum;
        Constituent.PositionM += this->PositionM;
        Constituent.MomentumM += this->MomentumM;
        return Constituent;
    }

private:

    TLorentzVector PositionM;

    TLorentzVector MomentumM;

    hanalysis::HFamily FamilyM;

//     int MotherId;
//     HConstituent& operator=(HConstituent other)
//     {
//         std::swap(*this, other);
//         return *this;
//     }

};

struct SortByDistance {
    inline bool operator()(const HConstituent &Constituent1, const HConstituent &Constituent2) const {
        return (Constituent1.Position().Vect().Mag() > Constituent2.Position().Vect().Mag());
    }

};


/**
 * @brief Jet infos subclassed from Fastjet
 *
 */
class hanalysis::HJetInfo: public HTag, public fastjet::PseudoJet::UserInfoBase
{

public:

    /**
     * @brief Constructor
     *
     */
    HJetInfo();

    HJetInfo(const int NewBTag) {
        BTagM = NewBTag;
    };

    HJetInfo(const HConstituent &NewConstituent) {
        ConstituentsM.push_back(NewConstituent);
        BTagM=0;
    };

    HJetInfo(const std::vector<HConstituent> &NewConstituents) {
        ConstituentsM = NewConstituents;
        BTagM=0;
    };

    HJetInfo(const std::vector<HConstituent> &NewConstituents, const int NewBTag) {
        ConstituentsM = NewConstituents;
        BTagM=NewBTag;
    };

    void AddConstituent(const HConstituent &NewConstituent) {
        ConstituentsM.push_back(NewConstituent);
    }

    void AddConstituents(const std::vector<HConstituent> &NewConstituents) {
        ConstituentsM.insert(ConstituentsM.end(),NewConstituents.begin(),NewConstituents.end());
    }

    std::vector<HConstituent> Constituents() const {
        return ConstituentsM;
    }

    inline void SetBTag(const int NewBTag) {
        BTagM = NewBTag;
    }

    inline int BTag() const {
        return BTagM;
    }

    float VertexMass() const;

    float MaxDisplacement() const;

    float MeanDisplacement() const;

    float SumDisplacement() const;

    int VertexNumber() const {
        return ApplyVertexResolution().size();
    }

    fastjet::PseudoJet VertexJet() const;

    float VertexEnergy() const;

    void ExtractFraction(const int ParticleId);

    void ExtractFraction(const int ParticleId, const int MotherId);

    void PrintAllInfos(const hanalysis::HObject::HSeverity Severity) const;

    float MaximalFraction() const;

    float Fraction(const int ParticleId) const;

    int MaximalId() const;

protected:

//     HJetInfo(HJetInfoPrivate & JetInfoPrivate);

    inline std::string ClassName() const {
        return "HJetInfo";
    }

private:

  void ExtractFamilyFraction();

    void AddParticle(const int ConstituentId, const float Weight);

    void AddFamily(const HFamily &Family, const float Weight);
//
//     void AddFamily(const HFamily Family, const float Weight);
//
//     void CalculateJetFamily();
//
//     float GetFamily(const HFamily Family) const;
//
//     float GetFamilyFraction(const HFamily Family) const;
//
//     std::map<int, float> GetJetFractions() const {
//         return JetFractions;
//     }
//
//     void SetJetFractions(std::map<int, float> NewJetFractions) {
//         JetFractions = NewJetFractions;
//     }
//
//     void PrintAllFamilyInfos(const hanalysis::HObject::HSeverity Severity) const;
//
//     void Clear();
//
//     bool HasParticle(const int ParticleId) const;
//
//     void SetConstituents(const std::vector<HConstituent> &NewConstituents) {
//         ConstituentsM = NewConstituents;
//     }
//
//     void SetVertex(const HConstituent &NewVertex) {
//         ConstituentsM.clear();// FIXME carefull do we assume everywhere that this is not dangerouse
//         ConstituentsM.push_back(NewVertex);
//     }
//
//     void AddVertices(const std::vector<HConstituent> &NewVertices) {
//         ConstituentsM.insert(ConstituentsM.end(), NewVertices.begin(), NewVertices.end());
//     }
//
//     std::vector<HConstituent> GetVertices() const {
//         return ConstituentsM;
//     }
//
//     inline std::unordered_map<HFamily, float> GetJetFamily()const {
//         return JetFamily;
//     }
//
//     inline void SetJetFamily(const std::unordered_map<HFamily, float> &NewJetFamily) {
//         JetFamily = NewJetFamily;
//     }
//
//
//
//     float GetFamilyWeightSum() const;
//
    float GetWeightSum() const;

    std::vector<HConstituent> ApplyVertexResolution() const;

    std::vector<HConstituent> ConstituentsM;

    std::unordered_map<HFamily, float> FamilyFractions;

    std::map<int, float> IdFractions;

    float SecondaryVertexResolution = 0.1;

    int BTagM;

};

# endif
