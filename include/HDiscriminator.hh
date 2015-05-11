# ifndef HDiscriminator_hh
# define HDiscriminator_hh

# include "HReconstruction.hh"
# include "JetInfo.hh"

/**
 * @brief Jet Discriminator
 *
 *
 */
class hanalysis::HDiscriminator : public HReconstruction
{

public:

    /**
     * @brief Constructor
     *
     */
    HDiscriminator();

    /**
     * @brief Destructor
     *
     */
    ~HDiscriminator();

    /**
     * @brief Get Fat Higgs Jets
     * 
     */
    Jets GetCandidateJets(const Jets &, const float);

    Jets GetCandidateJetsForced(const Jets &, const float);

    static bool JetIsBad(const fastjet::PseudoJet &Jet);

private:

    inline std::string ClassName() const {
        return "HDiscriminator";
    };

};

# endif
