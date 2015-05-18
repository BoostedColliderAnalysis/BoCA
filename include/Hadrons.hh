# pragma once

# include "TObjArray.h"

# include "ClonesArrays.hh"
# include "FourVector.hh"
# include "Predicate.hh"

namespace analysis{

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

    virtual ~Hadrons(){};

    /**
     * @brief Initialize New event
     */
    void NewEvent(const ClonesArrays &NewClonesArrays);

    void SetJetTag(HJetTag &NewJetTag) {
        jet_tag_ = &NewJetTag;
    }

    Jets GetJets() {
      NewEvent(*clones_arrays_);
//       if (!GotJets)
        GotJets = GetJets(Plain);
      return jets_;
    };

    Jets GetStructuredJets() {
      NewEvent(*clones_arrays_);
//         if (!GotJets)
          GotJets = GetJets(Structure);
        return jets_;
    };

    Jets GetTaggedJets() {
      NewEvent(*clones_arrays_);
//         if (!GotJets)
          GotJets = GetJets(Tagging);
        return jets_;
    };

    Jets GetTaggedJets(HJetTag &NewJetTag) {
      jet_tag_ = &NewJetTag;
      NewEvent(*clones_arrays_);
//         if (!GotJets)
          GotJets = GetJets(Tagging);
        return jets_;
    };

    Jets GetStructuredTaggedJets(HJetTag &NewJetTag) {
      jet_tag_ = &NewJetTag;
      NewEvent(*clones_arrays_);
//       if (!GotJets)
        GotJets = GetJets(TaggingStructure);
      return jets_;
    };

    Jets GetBottomJets() {
      //         if (!GotJets)
      NewEvent(*clones_arrays_);
          GotJets = GetJets(Plain);
        return BottomJets;
    };

    Jets GetEFlowJets() {
      if (!GotEFlow)
        GotEFlow = GetEFlow(Plain);
      return EFlowJets;
    };

    Jets GetIsolatedEFlowJets() {
      if (!GotEFlow) GotEFlow = GetEFlow(Isolation);
      return EFlowJets;
    };

    Jets GetTaggedEFlowJets() {
      if (!GotEFlow) GotEFlow = GetEFlow(Tagging);
      return EFlowJets;
    };

    Jets GetTaggedEFlowJets(HJetTag &NewJetTag) {
      jet_tag_ = &NewJetTag;
      if (!GotEFlow) GotEFlow = GetEFlow(Tagging);
      return EFlowJets;
    };

    Jets GetStructuredTaggedEFlowJets(HJetTag &NewJetTag) {
      jet_tag_ = &NewJetTag;
      if (!GotEFlow) GotEFlow = GetEFlow(TaggingStructure);
      return EFlowJets;
    };

    Jets GetStructuredEFlowJets() {
      Print(kInformation,"Get structured eflow", Structure);
      if (!GotEFlow) GotEFlow = GetEFlow(Structure);
      return EFlowJets;
    };

    Jets GetIsolatedTaggedEFlowJets() {
      if (!GotEFlow) GotEFlow = GetEFlow(TaggingIsolation);
      return EFlowJets;
    };

    Jets GetIsolatedTaggedEFlowJets(HJetTag &NewJetTag) {
      jet_tag_ = &NewJetTag;
      if (!GotEFlow) GotEFlow = GetEFlow(TaggingIsolation);
      return EFlowJets;
    };

    virtual float GetScalarHt();

    virtual fastjet::PseudoJet GetMissingEt();

    virtual Jets ClusteredJets(){
      Print(kError,"Get Sub Jets","should be subclassed");
      return GetJets();
    }

    virtual Jets GetSubJets(const fastjet::PseudoJet &, const int ){
      Print(kError,"Get Sub Jets","should be subclassed");
      return GetJets();
    }


protected:

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    virtual bool GetJets(const HJetDetails JetDetails);

    /**
     * @brief Analyses EFlow Variables of Jets
     *
     */
    virtual bool GetEFlow(const HJetDetails JetDetails);

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

    template<typename TParticle1, typename TParticle2>
    bool CheckIsolation(const TParticle1 &Particle1, const TParticle2 &Particle2, const float DeltaRIsolationMax) const {

        bool Isolated = 1;

        if (PseudoJet(const_cast<TParticle1 &>(Particle1).P4()).delta_R(PseudoJet(const_cast<TParticle2 &>(Particle2).P4())) < DeltaRIsolationMax) Isolated = 0;

        return Isolated;

    }

    template<typename TParticle1, typename TParticle2>
    bool CheckIsolation(const TParticle1 &Particle1, const TParticle2 &Particle2) const {

//         const float DeltaRIsolationMax = 0.01; // TODO decide on best value // This is quiet large
        const float DeltaRIsolationMax = 0; // TODO decide on best value // This is quiet large

        return CheckIsolation(Particle1, Particle2, DeltaRIsolationMax);

    }

    virtual inline std::string ClassName() const {
        return "HJet";
    };

private:

};

}
