# pragma once

# include "TObjArray.h"

# include "ClonesArrays.hh"
# include "FourVector.hh"
# include "Predicate.hh"

namespace analysis
{

/**
 * @brief Base class for jets
 *
 */
class Hadrons : public FourVector
{

public:

    /**
     * @brief constructor
     *
     */
    Hadrons();

    virtual ~Hadrons() {};

    /**
     * @brief Initialize New event
     */
    void NewEvent(const ClonesArrays &clones_arrays);

    void Setjet_tag(JetTag &jet_tag) {
        jet_tag_ = &jet_tag;
    }

    Jets GetJets() {
        NewEvent(*clones_arrays_);
//       if (!GotJets)
        GotJets = GetJets(kPlain);
        return jets_;
    };

    Jets GetStructuredJets() {
        NewEvent(*clones_arrays_);
//         if (!GotJets)
        GotJets = GetJets(kStructure);
        return jets_;
    };

    Jets GetTaggedJets() {
        NewEvent(*clones_arrays_);
//         if (!GotJets)
        GotJets = GetJets(kTagging);
        return jets_;
    };

    Jets GetTaggedJets(JetTag &Newjet_tag) {
        jet_tag_ = &Newjet_tag;
        NewEvent(*clones_arrays_);
//         if (!GotJets)
        GotJets = GetJets(kTagging);
        return jets_;
    };

    Jets GetStructuredTaggedJets(JetTag &Newjet_tag) {
        jet_tag_ = &Newjet_tag;
        NewEvent(*clones_arrays_);
//       if (!GotJets)
        GotJets = GetJets(kTaggingStructure);
        return jets_;
    };

    Jets GetBottomJets() {
        //         if (!GotJets)
        NewEvent(*clones_arrays_);
        GotJets = GetJets(kPlain);
        return BottomJets;
    };

    Jets GetEFlowJets() {
        if (!GotEFlow)
            GotEFlow = GetEFlow(kPlain);
        return EFlowJets;
    };

    Jets GetIsolatedEFlowJets() {
        if (!GotEFlow) GotEFlow = GetEFlow(kIsolation);
        return EFlowJets;
    };

    Jets GetTaggedEFlowJets() {
        if (!GotEFlow) GotEFlow = GetEFlow(kTagging);
        return EFlowJets;
    };

    Jets GetTaggedEFlowJets(JetTag &Newjet_tag) {
        jet_tag_ = &Newjet_tag;
        if (!GotEFlow) GotEFlow = GetEFlow(kTagging);
        return EFlowJets;
    };

    Jets GetStructuredTaggedEFlowJets(JetTag &Newjet_tag) {
        jet_tag_ = &Newjet_tag;
        if (!GotEFlow) GotEFlow = GetEFlow(kTaggingStructure);
        return EFlowJets;
    };

    Jets GetStructuredEFlowJets() {
        Print(kInformation, "Get structured eflow", kStructure);
        if (!GotEFlow) GotEFlow = GetEFlow(kStructure);
        return EFlowJets;
    };

    Jets GetIsolatedTaggedEFlowJets() {
        if (!GotEFlow) GotEFlow = GetEFlow(kTaggingIsolation);
        return EFlowJets;
    };

    Jets GetIsolatedTaggedEFlowJets(JetTag &Newjet_tag) {
        jet_tag_ = &Newjet_tag;
        if (!GotEFlow) GotEFlow = GetEFlow(kTaggingIsolation);
        return EFlowJets;
    };

    virtual float GetScalarHt();

    virtual fastjet::PseudoJet GetMissingEt();

    virtual Jets ClusteredJets() {
        Print(kError, "Get Sub Jets", "should be subclassed");
        return GetJets();
    }

    virtual Jets GetSubJets(const fastjet::PseudoJet &, const int) {
        Print(kError, "Get Sub Jets", "should be subclassed");
        return GetJets();
    }


protected:

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    virtual bool GetJets(const JetDetail jet_detail);

    /**
     * @brief Analyses EFlow Variables of Jets
     *
     */
    virtual bool GetEFlow(const JetDetail jet_detail);

    /**
     * @brief Get Gen Jet
     *
     * @param  ...
     * @return void
     */
    virtual void GetGenJet();

    bool GotEFlow;

    bool GotJets;

    /**
     * @brief std::vector of Jet Lorentz Vectors
     *
     */
    Vectors JetLorentzVectors;

    /**
     * @brief Tau Lorentz Vector Vector
     *
     */
    Vectors TauLorentzVectors;

    /**
     * @brief Anti Tau Lorentz Vector Vector
     *
     */
    Vectors AntiTauLorentzVectors;

    /**
     * @brief Vector of EFlow JetCandidates
     *
     */
    Jets EFlowJets;

    /**
     * @brief Vector of generator level Charm Pseudo Jets
     *
     */
    Jets jets_;

    /**
     * @brief Vector of generator level Bottom Pseudo Jets
     *
     */
    Jets BottomJets;

    /**
     * @brief Vector of generator level Charm Pseudo Jets
     *
     */
    Jets CharmJets;

    /**
     * @brief Vector of EFlow JetCandidates
     *
     */
    Jets GenJets;

    /**
     * @brief std::vector of Bottom Lorentz Vectors with their pull
     *
     */
    Vectors BottomLorentzVectors;

    template<typename Particle_1, typename Particle_2>
    bool CheckIsolation(const Particle_1 &particle_1, const Particle_2 &particle_2, const float delta_r_isolation_max) const {
        bool isolated = false;
        if (PseudoJet(const_cast<Particle_1 &>(particle_1).P4()).delta_R(PseudoJet(const_cast<Particle_2 &>(particle_2).P4())) < delta_r_isolation_max) isolated = true;
        return isolated;
    }

    template<typename Particle_1, typename Particle_2>
    bool CheckIsolation(const Particle_1 &particle_1, const Particle_2 &particle_2) const {
        //         const float delta_r_isolation_max = 0.01; // TODO decide on best value // This is quiet large
        const float delta_r_isolation_max = 0; // TODO decide on best value // This is quiet large
        return CheckIsolation(particle_1, particle_2, delta_r_isolation_max);
    }

    virtual inline std::string ClassName() const {
        return "Hadrons";
    };

private:

};

}
