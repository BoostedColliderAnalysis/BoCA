# ifndef HJetInfo_hh
# define HJetInfo_hh

# include <map>
# include <numeric>

# include "HObject.hh"

struct HConstituent {

    TLorentzVector Position;
    TLorentzVector Momentum;
    int MotherId;

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
class hanalysis::HJetInfo: public HObject, public fastjet::PseudoJet::UserInfoBase
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
     * @param  ID
     * @param  pT
     * @return void
     */
    void AddConstituent(const int ConstituentId, const float Weight);

    /**
     * @brief Get Fraction
     *
     * @param  ID
     * @return float
     */
    float GetFraction(const int ParticleId) const;

    std::map<int, float> GetJetFractions() const {
        return JetFractions;
    }

    /**
     * @brief Get dominant Fraction
     *
     * @return float
     */
    float GetMaximalFraction() const;

    /**
     * @brief Get dominant Id
     *
     * @return int
     */
    int GetMaximalId() const;

    /**
     * @brief Print List of all infos
     *
     * @return void
     */
    void PrintAllInfos(int Severity) const;

    /**
     * @brief Clear all infos
     *
     * @return void
     */
    void Clear();

    /**
     * @brief Check for Particle Id
     *
     * @param  ID
     * @return bool
     */
    bool HasParticle(const int ParticleId) const;

    void AddVertex(const HConstituent &Vertex) {
        Vertices.push_back(Vertex);
    }

    void SetVertices(const std::vector<HConstituent> &NewVertices) {
        Vertices = NewVertices;
    }

    void SetVertex(HConstituent &NewVertex) {
        Vertices.push_back(NewVertex);
    }

    void AddVertices(std::vector<HConstituent> &NewVertices) {
        Vertices.insert(Vertices.end(), NewVertices.begin(), NewVertices.end());
    }

    std::vector<HConstituent> GetVertices() const {
        return Vertices;
    }

    float GetJetDisplacement() {
        Print(HDebug, "Get Jet Displacement");

        if (Vertices.size() == 0) return 0;
        std::sort(Vertices.begin(), Vertices.end(), SortByDistance());
        return (Vertices.front().Position.Vect().Mag());
    }

    int GetVertexNumber() const {
        return Vertices.size();
    }

    float GetJetDisplacement() const;

    float GetVertexMass() const {
        Print(HDebug, "Get Vertex Mass");
        HConstituent Vertex;
        return (std::accumulate(Vertices.begin(), Vertices.end(), Vertex).Momentum.M());
    }


protected:

    inline std::string ClassName() const {
        return "HJetInfo";
    };

private:

    float GetWeightSum() const;

    std::map<int, float> JetFractions;

    std::vector<HConstituent> Vertices;

};

# endif
