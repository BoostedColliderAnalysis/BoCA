# ifndef HJetTag_hh
# define HJetTag_hh

# include <set>
# include <unordered_set>

# include "HObject.hh"

class hanalysis::HFamily : public HObject
{

public:

    HFamily() {
        ParticlePosition = EmptyPosition;
        ParticleId = EmptyId;
        Mother1Position = EmptyPosition;
        Mother1Id = EmptyId;
        MarkerM = 0;
        Daughters.reserve(2);
    }

    HFamily(const int NewParticle) {
        ParticleId = NewParticle;
        Mother1Id = NewParticle;
        ParticlePosition = EmptyPosition;
        Mother1Position = EmptyPosition;
        MarkerM = 0;
        Daughters.reserve(2);
    }

    HFamily(const int NewParticle, const int NewMother1) {
        ParticleId = NewParticle;
        Mother1Id = NewMother1;
        ParticlePosition = EmptyPosition;
        Mother1Position = EmptyPosition;
        MarkerM = 0;
        Daughters.reserve(2);
    }

    HFamily(const int NewParticle, const int NewMother1, const int NewMother2) {
      ParticleId = NewParticle;
      Mother1Id = NewMother1;
      Mother2Id = NewMother2;
      ParticlePosition = EmptyPosition;
      Mother1Position = EmptyPosition;
      MarkerM = 0;
      Daughters.reserve(2);
    }

    HFamily(const int NewParticlePosition, const int NewParticleId, const int NewMotherPosition, const int NewMotherId) {
        ParticlePosition = NewParticlePosition;
        ParticleId = NewParticleId;
        Mother1Position = NewMotherPosition;
        Mother1Id = NewMotherId;
        MarkerM = 0;
        Daughters.reserve(2);
    }

    HFamily(const TLorentzVector &NewParticleVector, const TLorentzVector &NewMotherVector, const int NewParticlePosition, const int NewParticleId, const int NewMotherPosition, const int NewMotherId) {
        ParticleVector = NewParticleVector;
        MotherVector = NewMotherVector;
        ParticlePosition = NewParticlePosition;
        ParticleId = NewParticleId;
        Mother1Position = NewMotherPosition;
        Mother1Id = NewMotherId;
        MarkerM = 0;
        Daughters.reserve(2);
    }

    bool operator==(const HFamily &Family) const {
//         return (std::abs(ParticleId) == std::abs(Family.ParticleId)
//         && std::abs(Mother1Id) == std::abs(Family.Mother1Id)
//         && std::abs(Mother2Id) == std::abs(Family.Mother2Id));
        return (ParticleId == Family.ParticleId
                && Mother1Id == Family.Mother1Id
                && Daughters == Family.Daughters
//                 && Mother2Id == Family.Mother2Id
               );
    }

    void AddDaughter(const int NewDaughter){
      Daughters.push_back(NewDaughter);
    }


    int ParticlePosition;
    int ParticleId;
    int Mother1Position;
    int Mother1Id;
    int Mother2Position;
    int Mother2Id;
    std::vector<int> Daughters;
    float Pt;



    TLorentzVector ParticleVector;
    TLorentzVector MotherVector;

    void SetMarker() {
        MarkerM = 1;
    }
    void UnSetMarker() {
        MarkerM = 0;
    }
    bool Marker()const {
        return MarkerM;
    }

protected:

    bool MarkerM;

};

namespace std
{

template <>
struct hash<hanalysis::HFamily> {
    std::size_t operator()(const hanalysis::HFamily &Family) const {

        return ((std::hash<int>()(Family.ParticleId)
                 ^ (std::hash<int>()(Family.Mother1Id) << 1)) >> 1)
//                ^ (std::hash<int>()(Family.Mother2Id) << 1)
               ;
    }
};

}

/**
 * @brief defines how to tag a jet
 *
 */
class hanalysis::HJetTag : public HObject
{

public:

    /**
     * @brief Constructor
     *
     */
    HJetTag();

    /**
     * @brief Destructor
     *
     */
    ~HJetTag();

    /**
     * @brief decide on the branch id based on the former branch id and the particle id
     *
     */
    virtual int GetBranchId(const int ParticleId, int BranchId);

    HFamily GetBranchFamily(const hanalysis::HFamily &NodeFamily, hanalysis::HFamily &BranchFamily);


    std::set<HParticleId> HeavyParticles;

//     std::unordered_set<HFamily> HeavyFamily;

//     std::set<HFamilyId> HeavyParticleFamilies;

protected:

    /**
     * @brief set of Particle Ids defiend as initial state radiation
     *
     */
    std::set<HParticleId> RadiationParticles {ProtonId/*, GluonId, UpId, DownId, StrangeId, CharmId, UpDown0Id, UpDown1Id, UpUp1Id, DownDown1Id*/};

private:

    virtual inline std::string ClassName() const {
        return "HJetTag";

    };

};

# endif
