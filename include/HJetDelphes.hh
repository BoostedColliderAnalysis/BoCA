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

    Jets GranulatedJets(const Jets &NewEFlowJets);

    Jets GetJets();

    Jets GetSubJets(const fastjet::PseudoJet &Jet, const int SubJetNumber);

private:


    HDetectorGeometry detector_geometry_;

    HDetectorGeometry detector_geometry() const{
      return detector_geometry_;
    }

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
    void TauTag(const delphes::Jet &JetClone);

    /**
     * @brief Get Gen Jet
     *
     */
    void GetGenJet();

//     std::vector<int *> BranchVector;

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    bool GetJets(const bool, const bool);

    template <typename TClone>
    hanalysis::HJetInfo GetJetId(const TClone &Clone) {
        Print(HDetailed, "Get Jet Id", Clone.Particles.GetEntriesFast());
        hanalysis::HJetInfo JetInfo;
        for (const int ParticleNumber : Range(Clone.Particles.GetEntriesFast())) {
          const HFamily BranchFamily = GetBranchFamily(*Clone.Particles.At(ParticleNumber));
            Print(HDebug, "MotherId", BranchFamily.ParticleId, BranchFamily.Mother1Id);
            JetInfo.AddConstituent(HConstituent(const_cast<TClone &>(Clone).P4(), BranchFamily));
        }
        JetInfo.PrintAllInfos(HDebug);
        return JetInfo;
    }


    template<typename TParticle, typename TEFlow>
    bool GetIsolation(const TEFlow &EFlowClone, const TClonesArray &ClonesArray) const {
        bool Isolated = true;
        for (int ParticleNumber = 0; ParticleNumber < ClonesArray.GetEntriesFast(); ++ParticleNumber) {
            TParticle &ParticleClone = static_cast<TParticle &>(*ClonesArray.At(ParticleNumber));
            Isolated = CheckIsolation(EFlowClone, ParticleClone);
        }
        return Isolated;
    }

    void DelphesTags(const delphes::Jet &JetClone);

    void GetTrackEFlow(const HJetDetails);

    void GetPhotonEFlow(const HJetDetails);

    void GetHadronEFlow(const HJetDetails);

    void GetMuonEFlow(const HJetDetails);

    fastjet::PseudoJet StructuredJet(const delphes::Jet &JetClone, const hanalysis::HFourVector::HJetDetails JetDetails);

    fastjet::PseudoJet GetConstituents(const TObject &Object, const hanalysis::HFourVector::HJetDetails JetDetails, const HConstituent::SubDetector Detector = HConstituent::HNone);

    inline std::string NameSpaceName() const {
        return "HDelphes";
    }

    inline std::string ClassName() const {
        return "HJet";
    };

};

#endif
