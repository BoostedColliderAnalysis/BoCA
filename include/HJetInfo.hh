# ifndef HJetInfo_hh
# define HJetInfo_hh

# include <map>
# include <unordered_map>
# include <numeric>

# include "HTag.hh"
# include "HJetTag.hh"

struct HConstituent {

    TLorentzVector Position;
    TLorentzVector Momentum;
    int MotherId;
    hanalysis::HFamily Family;

    HConstituent operator+(const HConstituent &Vertex) {
        HConstituent NewVertex;
        NewVertex.Position = this->Position + Vertex.Position;
        NewVertex.Momentum = this->Momentum + Vertex.Momentum;
        return NewVertex;
    }

//     HConstituent& operator=(HConstituent other)
//     {
//         std::swap(*this, other);
//         return *this;
//     }

};

struct SortByDistance {

    inline bool operator()(const HConstituent &Vertex1, const HConstituent &Vertex2) const {
        return (Vertex1.Position.Vect().Mag() > Vertex2.Position.Vect().Mag());
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

    /**
     * @brief Add Constituent...
     *
     */
    void AddConstituent(const int ConstituentId, const float Weight);

    void AddFamily(const HFamily Family, const float Weight);

    /**
     * @brief Get Fraction
     *
     */
    float GetFraction(const int ParticleId) const;

    void ExtractFraction(const int ParticleId);

    void ExtractFraction(const int ParticleId, const int MotherId);

    float GetFamily(const HFamily Family) const;

    float GetFamilyFraction(const HFamily Family) const;

    std::map<int, float> GetJetFractions() const {
        return JetFractions;
    }

    /**
     * @brief Get dominant Fraction
     *
     */
    float GetMaximalFraction() const;

    /**
     * @brief Get dominant Id
     *
     */
    int GetMaximalId() const;

    /**
     * @brief Print List of all infos
     *
     */
    void PrintAllInfos(const hanalysis::HObject::HSeverity Severity) const;

    void PrintAllFamilyInfos(const hanalysis::HObject::HSeverity Severity) const;

    /**
     * @brief Clear all infos
     *
     */
    void Clear();

    /**
     * @brief Check for Particle Id
     *
     */
    bool HasParticle(const int ParticleId) const;

    void AddVertex(const HConstituent &Vertex) {
        Vertices.push_back(Vertex);
    }

    void SetVertices(const std::vector<HConstituent> &NewVertices) {
        Vertices = NewVertices;
    }

    void SetVertex(const HConstituent &NewVertex) {
        Vertices.push_back(NewVertex);
    }

    void AddVertices(const std::vector<HConstituent> &NewVertices) {
        Vertices.insert(Vertices.end(), NewVertices.begin(), NewVertices.end());
    }

    std::vector<HConstituent> GetVertices() const {
        return Vertices;
    }

//     float GetJetDisplacement() {
//         Print(HDebug, "Get Jet Displacement");
//
//         if (Vertices.size() == 0) {
//             Print(HError, "No secondary Vertices");
//             return 0;
//         }
//         std::sort(Vertices.begin(), Vertices.end(), SortByDistance());
//         return (Vertices.front().Position.Vect().Mag());
//     }

    int GetVertexNumber() const {
        return Vertices.size();
    }

    float GetJetDisplacement() const;

    float GetVertexMass() const;

    float GetVertexEnergy() const;

    inline void SetBTag(const int NewBTag){
      BTag = NewBTag;
    }

    inline int GetBTag() const {
      return BTag;
    }

protected:

    inline std::string ClassName() const {
        return "HJetInfo";
    };

private:

    std::vector<HConstituent> ApplyVertexResolution() const;

    float SecondaryVertexResolution = 0.1;

    float GetWeightSum() const;

    float GetFamilyWeightSum() const;

    std::map<int, float> JetFractions;

    std::unordered_map<HFamily, float> JetFamily;

    std::vector<HConstituent> Vertices;

    int BTag;

};




# endif
