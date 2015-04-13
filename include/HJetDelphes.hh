# ifndef HJetDelphes_hh
# define HJetDelphes_hh

# include "HJet.hh"
# include "HJetInfo.hh"

# include "fastjet/JetDefinition.hh"

class HDetectorGeometry
{
public:
    enum HDetectorType {CMS, Spp};

    HDetectorGeometry(const HDetectorType DetectorType) {
        switch (DetectorType) {
        case CMS :
            JetMinPt = 20;
            JetConeSize = 0.5;
            MinCellResolution = .1;
            MinCellPt = .5;
            TrackerEtaMax = 2.5;
            JetDefinition = fastjet::JetDefinition(fastjet::antikt_algorithm, 1);
            SubJetDefinition = fastjet::JetDefinition(fastjet::kt_algorithm, 1);
        case Spp:
            JetMinPt = 40;
            JetConeSize = 0.5;
            MinCellResolution = .1;
            MinCellPt = .5;
            TrackerEtaMax = 5;
            JetDefinition = fastjet::JetDefinition(fastjet::antikt_algorithm, 1);
            SubJetDefinition = fastjet::JetDefinition(fastjet::kt_algorithm, 1);
        }
    }
    float JetMinPt;
    float JetConeSize;
    float MinCellPt;
    float MinCellResolution;
    float TrackerEtaMax;
    float JetRadiusParameter;
    fastjet::JetDefinition JetDefinition;
    fastjet::JetDefinition SubJetDefinition;
};

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

    HJets GranulatedJets(const HJets &NewEFlowJets);

    HJets GetJets();

    HJets GetSubJets(const fastjet::PseudoJet &Jet, const int SubJetNumber);

private:


    HDetectorGeometry DetectorGeometry;

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
