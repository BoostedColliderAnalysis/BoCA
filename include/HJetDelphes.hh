# ifndef HJetDelphes_hh
# define HJetDelphes_hh

# include "HJet.hh"
# include "JetInfo.hh"

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

    float GetScalarHt();

    fastjet::PseudoJet GetMissingEt();

    Jets GranulatedJets(const Jets &NewEFlowJets);

    Jets GetGranJets();

    Jets GetSubJets(const fastjet::PseudoJet &Jet, const int SubJetNumber);

private:


    DetectorGeometry detector_geometry_;

    DetectorGeometry detector_geometry() const{
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
    hanalysis::JetInfo GetJetId(const TClone &Clone) {
        Print(kDetailed, "Get Jet Id", Clone.Particles.GetEntriesFast());
        hanalysis::JetInfo jet_info;
        for (const int ParticleNumber : Range(Clone.Particles.GetEntriesFast())) {
          const HFamily BranchFamily = GetBranchFamily(*Clone.Particles.At(ParticleNumber));
            Print(kDebug, "MotherId", BranchFamily.ParticleId, BranchFamily.Mother1Id);
            jet_info.Addconstituent(Constituent(const_cast<TClone &>(Clone).P4(), BranchFamily));
        }
        jet_info.PrintAllInfos(kDebug);
        return jet_info;
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

    fastjet::PseudoJet Getconstituents(const TObject &Object, const hanalysis::HFourVector::HJetDetails JetDetails, const Constituent::SubDetector Detector = Constituent::HNone);

    inline std::string NameSpaceName() const {
        return "HDelphes";
    }

    inline std::string ClassName() const {
        return "HJet";
    };

};

#endif
