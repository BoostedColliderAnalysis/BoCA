# pragma once

# include "HJet.hh"
# include "JetInfo.hh"
# include "TClonesArray.h"

/**
 * @brief Delphes jets
 *
 */
class analysis::hdelphes::HJet : public analysis::HJet
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

private:

    DetectorGeometry detector_geometry_;

    DetectorGeometry detector_geometry() const {
        return detector_geometry_;
    }

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    bool GetJets(const analysis::HFourVector::HJetDetails JetDetails);

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
    analysis::JetInfo GetJetId(const TClone &Clone) {
        Print(kDetailed, "Get Jet Id", Clone.Particles.GetEntriesFast());
        analysis::JetInfo jet_info;
        for (const int ParticleNumber : Range(Clone.Particles.GetEntriesFast())) {
            const Family family = GetBranchFamily(*Clone.Particles.At(ParticleNumber));
            Print(kDebug, "MotherId", family.particle().Id, family.mother_1().Id);
            jet_info.Addconstituent(Constituent(const_cast<TClone &>(Clone).P4(), family));
        }
        jet_info.PrintAllInfos(kDebug);
        return jet_info;
    }


    template<typename Particle, typename EFlow>
    bool GetIsolation(const EFlow &e_flow, const TClonesArray &clones_array) const {
        bool Isolated = true;
        for (int particle_number = 0; particle_number < clones_array.GetEntriesFast(); ++particle_number) {
            Particle &particle = static_cast<Particle &>(*clones_array.At(particle_number));
            Isolated = CheckIsolation(e_flow, particle);
        }
        return Isolated;
    }

    void DelphesTags(const delphes::Jet &JetClone);

    void GetTrackEFlow(const HJetDetails);

    void GetPhotonEFlow(const HJetDetails);

    void GetHadronEFlow(const HJetDetails);

    void GetMuonEFlow(const HJetDetails);

    fastjet::PseudoJet StructuredJet(const delphes::Jet &JetClone, const analysis::HFourVector::HJetDetails JetDetails);

    fastjet::PseudoJet Getconstituents(const TObject &Object, const analysis::HFourVector::HJetDetails JetDetails, const Constituent::SubDetector Detector = Constituent::kNone);

    inline std::string NameSpaceName() const {
        return "HDelphes";
    }

};
