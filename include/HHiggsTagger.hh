# ifndef HHiggsTagger_hh
# define HHiggsTagger_hh

# include "fastjet/tools/Filter.hh"

# include "HReconstruction.hh"

/**
 * @brief Higgs tagger as described in arXiv:0802.2470
 *
 * based on fastjet example 12
 *
 */
class hdelphes::HHiggsTagger : public HReconstruction
{

public:

    /**
     * @brief dipolarity of the HiggsJet
     *
     */
//     float DiPolarity;

    /**
     * @brief Jet tagged as Higgs
     *
     */
    PseudoJet HiggsJet;

    /**
     * @brief Originial fat jet
     *
     */
//     PseudoJet FatJet;

    /**
     * @brief Reconstruct the higgs fat jet
     *
     * @param  HJets InputJetVector
     * @param  HJets BottomVector
     * @param  HJets CharmVector
     * @return void
     */
    PseudoJet GetHiggsJet(const HJets&, const HJets&, const HJets&);

    /**
     * @brief constructor
     *
     */
    HHiggsTagger();

    /**
     * @brief destructor
     *
     */
    ~HHiggsTagger();

    void NewEvent();

private:

    /**
     * @brief Initial value
     *
     */
    int InitialValue;

    /**
     * @brief abitry user index used to identify bottoms
     *
     */
    int BottomUserIndex;

    /**
     * @brief abitry user index used to identify charms
     *
     */
    int CharmUserIndex;

    /**
     * @brief Vector of Fat Jet Pieces
     *
     */
    HJets FilteredJetPieces;

    /**
     * @brief Get vecto of all fatjets
     *
     * @param  InputJetVector
     * @return FatJetVector
     */
//     HJets GetFatJetVector(HJets);

    /**
     * @brief Get mass drop jet
     *
     * @param  FatJet
     * @return MassDropJet
     */
//     PseudoJet GetMassDropJet(PseudoJet);

    /**
     * @brief Filter Jets
     *
     * @param  MassDropJet
     * @param  FilterJetAlgorithm
     * @param  NumberHardestPieces
     * @return FilteredJet
     */
    PseudoJet GetFilteredJet(const PseudoJet&, const fastjet::JetAlgorithm&, const int);

    /**
     * @brief Compare subjets with particle quarks
     *
     * @param  ParticleJetVector
     * @param  ParticleUserIndex
     * @return void
     */
    void GetSubJetSource(const HJets&, const int);

    /**
     * @brief Apply Bottom tagger
     *
     * @return SubBJetCounter
     */
    int BTagger();

    /**
     * @brief Get Dipolarity
     *
     * @param FatJet ...
     * @return Dipolarity
     */
    float GetDipolarity(const PseudoJet &);

    /**
     * @brief Eta of Subjets and Constituent
     *
     */
    float Eta0, Eta1, Eta2;

    /**
     * @brief Phi of Subjets and Constituent
     *
     */
    float Phi0, Phi1, Phi2;

    /**
     * @brief Delta R between Subjets and Constituent
     *
     */
    float DeltaR01, DeltaR02, DeltaR12;

    float DeltaR12Sqr() {
        return pow(DeltaR12, 2);
    }

    float DeltaPhi() {
        return (Phi2 - Phi1);
    }

    float DeltaPhiSqr() {
        return pow(DeltaPhi(), 2);
    }

    float DeltaEta() {
        return -(Eta2 - Eta1);
    }

    float DeltaEtaSqr() {
        return pow(DeltaEta(), 2);
    }

    float EtaPhi() {
        return Eta2 * Phi1 - Eta1 * Phi2;
    }

    float DeltaEtaPhi() {
        return DeltaPhi() * DeltaEta();
    }

    float DeltaPhiEta0() {
        return DeltaPhi() * Eta0;
    }

    float DeltaEtaPhi0() {
        return DeltaEta() * Phi0;
    }

    void SetEtaPhi(PseudoJet &SubJet1, PseudoJet &SubJet2);

    float GetSubDeltaR();

    inline std::string ClassName() const {
        return ("HHiggsTagger");
    };

};

# endif
