# ifndef HJetDelphes_hh
# define HJetDelphes_hh

# include <fastjet/ClusterSequence.hh>

# include "HJet.hh"
# include "HJetInfo.hh"

/**
 * @brief stores all the information about the event topology
 *
 */
class HJetDelphes : public HJet
{

public:

    /**
     * @brief constructor
     *
     */
    HJetDelphes();

    /**
     * @brief Destructor
     *
     */
    ~HJetDelphes();

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    bool GetJets();

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    bool GetTaggedJets(const HJetTag * const);

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    bool GetStructuredJets();

    /**
     * @brief Get Tau Tag
     *
     * @return void
     */
    void GetTau(const Jet*const);

    /**
     * @brief Analyses EFlow Variables of Jets
     *
     */
    bool GetEFlow();

    /**
     * @brief Analyses EFlow Variables of Jets
     *
     */
    bool GetTaggedEFlow(const HJetTag * const);

    /**
     * @brief Get Gen Jet
     *
     * @param  ...
     * @return void
     */
    void GetGenJet();

private:

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    bool GetJets(const bool, const bool);
    
    vector<PseudoJet> TagJets(vector<PseudoJet>);

    vector<PseudoJet> JetTagger(vector<PseudoJet>, vector<PseudoJet>, int);

    vector<PseudoJet> JetTagger(vector<PseudoJet>, vector<PseudoJet>);

    template <typename Template>
    HJetInfo GetJetId(const Template &Clone) {

        Print(2, "Get Jet Id",Clone->Particles.GetEntriesFast());
        HJetInfo JetInfo;

        for (int ParticleNumber = 0; ParticleNumber < Clone->Particles.GetEntriesFast(); ++ParticleNumber) {

            const TObject*const Object = Clone->Particles.At(ParticleNumber);

            if (Object == 0) continue;
            if (Object->IsA() != GenParticle::Class()) continue;

            const GenParticle * const ParticleClone = (GenParticle *) Object;

            JetInfo.AddConstituent(GetMotherId(Object), ParticleClone->PT);

        }

        Print(4, "Jet ID", JetInfo.GetMaximalId(),JetInfo.GetMaximalFraction());
//         JetInfo.PrintAllInfos();

        return JetInfo;

    }


    template<typename ParticleTemplate,typename EFlowTemplate>
    bool GetIsolation(const EFlowTemplate * const EFlowClone,const TClonesArray * const ClonesArray) const {

        bool Isolated = true;

        for (int ParticleNumber = 0; ParticleNumber < ClonesArray->GetEntriesFast(); ++ParticleNumber) {

            ParticleTemplate *ParticleClone = (ParticleTemplate *) ClonesArray->At(ParticleNumber);
            Isolated = CheckIsolation(EFlowClone, ParticleClone);

        }

        return Isolated;
    }


    int GetMotherId(const TObject * const);

    int GetMotherId(GenParticle *, int);

//     int GetBranchId(int, int);

    void GetDelphesTags(const Jet *const);

    /**
     * @brief Analyses EFlow Variables of Jets
     *
     */
    bool GetEFlow(const bool, const bool);

    void GetTrackEFlow(const bool, const bool);

    void GetPhotonEFlow(const bool, const bool);

    void GetHadronEFlow(const bool, const bool);

    void GetMuonEFlow(const bool, const bool);

    PseudoJet GetConstituents(const Jet * const) const;

    string ClassName() const {

        return ("HJetDelphes");

    };

};

#endif
