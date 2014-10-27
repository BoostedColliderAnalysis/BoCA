# ifndef HJetInfo_hh
# define HJetInfo_hh

# include <map>

# include "HObject.hh"

using std::map;
using std::pair;

/**
 * @brief Jet infos subclassed from Fastjet
 *
 */
class hanalysis::HJetInfo: public HObject, public PseudoJet::UserInfoBase
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

    map<int,float> GetJetFractions() const{

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

protected:

    inline string ClassName() const {

        return "HJetInfo";

    };

private:

    float GetWeightSum() const;

    map<int, float> JetFractions;

};

# endif
