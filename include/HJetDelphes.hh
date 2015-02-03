# ifndef HJetDelphes_hh
# define HJetDelphes_hh

# include "HJet.hh"
# include "HJetInfo.hh"

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
    void TauTag(const delphes::Jet *const);

    /**
     * @brief Get Gen Jet
     *
     */
    void GetGenJet();

    std::vector<int *> BranchVector;

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    bool GetJets(const bool, const bool);

    template <typename TClone>
    hanalysis::HJetInfo GetJetId(TClone &Clone) {
        Print(HDetailed, "Get Jet Id", Clone->Particles.GetEntriesFast());
        hanalysis::HJetInfo JetInfo;
        for (const int ParticleNumber : HRange(Clone->Particles.GetEntriesFast())) {
            TObject *Object = Clone->Particles.At(ParticleNumber);
            const HFamily BranchFamily = GetBranchFamily(Object);
            Print(HDebug, "MotherId", BranchFamily.ParticleId, BranchFamily.Mother1Id);
            JetInfo.AddConstituent(HConstituent(Clone->P4(),BranchFamily));
        }
        JetInfo.PrintAllInfos(HDebug);
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

    void DelphesTags(const delphes::Jet *const);

    void GetTrackEFlow(const HJetDetails);

    void GetPhotonEFlow(const HJetDetails);

    void GetHadronEFlow(const HJetDetails);

    void GetMuonEFlow(const HJetDetails);

    fastjet::PseudoJet StructuredJet(const delphes::Jet *const JetClone, const hanalysis::HFourVector::HJetDetails JetDetails);

    fastjet::PseudoJet GetConstituents(TObject *Object, hanalysis::HFourVector::HJetDetails JetDetails);

    inline std::string NameSpaceName() const {
        return "HDelphes";
    }

    inline std::string ClassName() const {
        return "HJet";
    };

};

#endif
