# ifndef HJetInfo_hh
# define HJetInfo_hh

# include <map>

# include "HObject.hh"

using std::map;
using std::accumulate;


/**
 * @brief Jet infos subclassed from Fastjet
 *
 */
class HJetInfo: public HObject, public PseudoJet::UserInfoBase
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
    void AddConstituent(const int, const float);

    /**
     * @brief Get Fraction
     *
     * @param  ID
     * @return float
     */
    float GetFraction(int) const;

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
    void PrintAllInfos(int) const;

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
