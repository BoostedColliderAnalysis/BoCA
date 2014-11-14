# ifndef HDiscriminator_hh
# define HDiscriminator_hh

# include "HReconstruction.hh"
# include "HJetInfo.hh"

/**
 * @brief Jet Discriminator
 *
 *
 */
class hdelphes::HDiscriminator : public HReconstruction
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
     * @param  EFlow Jet Vector
     * @return Candidates
     */
    HJets GetCandidateJets(const HJets &, const float);

    HJets GetCandidateJetsForced(const HJets &, const float);

    static bool JetIsBad(const fastjet::PseudoJet &Jet);

private:

    inline std::string ClassName() const {
        return "HDiscriminator";
    };

};

# endif
