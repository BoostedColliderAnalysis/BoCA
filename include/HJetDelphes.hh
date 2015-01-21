# ifndef HJetDelphes_hh
# define HJetDelphes_hh

// # include <sstream>

# include "HJet.hh"
# include "HJetInfo.hh"

// struct HConstituent{
//
//   TLorentzVector Momentum;
//   TLorentzVector Position;
//   int MotherId;
//
// };

/**
 * @brief Delphes jets
 *
 */
class hanalysis::hdelphes::HJet : public hanalysis::HJet
{

public:

    /**
     * @brief constructor
     *
     */
    HJet();

    /**
     * @brief Destructor
     *
     */
    ~HJet();

    /**
     * @brief Initialize new event
     *
     * @return void
     */
//     void NewEvent(const hanalysis::HClonesArray *const NewClonesArrays);

    float GetScalarHt();

    fastjet::PseudoJet GetMissingEt();

private:

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    bool GetJets(const hanalysis::HFourVector::HJetDetails JetDetails);

    /**
     * @brief Analyses EFlow Variables of Jets
     *
     */
    bool GetEFlow(const HJetDetails JetDetails);

    /**
     * @brief Get Tau Tag
     *
     * @return void
     */
    void GetTau(const delphes::Jet *const);

    /**
     * @brief Get Gen Jet
     *
     * @param  ...
     * @return void
     */
    void GetGenJet();

    std::vector<int *> BranchVector;

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    bool GetJets(const bool, const bool);

//     HJets TagJets(HJets);

//     HJets JetTagger(HJets, HJets, int);

//     HJets JetTagger(HJets, HJets);

    template <typename TClone>
    hanalysis::HJetInfo GetJetId(const TClone &Clone) {

        Print(HDetailed, "Get Jet Id", Clone->Particles.GetEntriesFast());

        hanalysis::HJetInfo JetInfo;

        for (const int ParticleNumber : HRange(Clone->Particles.GetEntriesFast())) {

            TObject *Object = Clone->Particles.At(ParticleNumber);
//             const int MotherId = GetMotherId(Object);
            const HFamily BranchFamily = GetBranchFamily(Object);
            Print(HDebug, "MotherId", BranchFamily.ParticleId, BranchFamily.Mother1Id);

            const delphes::GenParticle *const ParticleClone = (delphes::GenParticle *) Object;
            JetInfo.AddFamily(BranchFamily, std::abs(ParticleClone->PT));

        }

        JetInfo.PrintAllFamilyInfos(HDebug);
        return JetInfo;

    }


    template<typename TParticle, typename TEFlow>
    bool GetIsolation(const TEFlow *const EFlowClone, const TClonesArray *const ClonesArray) const {

        bool Isolated = true;

        for (int ParticleNumber = 0; ParticleNumber < ClonesArray->GetEntriesFast(); ++ParticleNumber) {

            TParticle *ParticleClone = (TParticle *) ClonesArray->At(ParticleNumber);
            Isolated = CheckIsolation(EFlowClone, ParticleClone);

        }

        return Isolated;
    }

    void GetDelphesTags(const delphes::Jet *const);

    void GetTrackEFlow(const HJetDetails);

    void GetPhotonEFlow(const HJetDetails);

    void GetHadronEFlow(const HJetDetails);

    void GetMuonEFlow(const HJetDetails);

    fastjet::PseudoJet GetConstituents(const delphes::Jet *const JetClone, const hanalysis::HFourVector::HJetDetails JetDetails);

    HConstituent GetConstituent(TObject *Object, hanalysis::HJet::HJetDetails JetDetails);

    fastjet::PseudoJet GetConstituentJet(TObject *Object, hanalysis::HFourVector::HJetDetails JetDetails);

    inline std::string NameSpaceName() const {
        return "HDelphes";
    }

    inline std::string ClassName() const {
        return "HJet";
    };

};

#endif
