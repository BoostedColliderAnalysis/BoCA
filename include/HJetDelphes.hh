# ifndef HJetDelphes_hh
# define HJetDelphes_hh

// # include <fastjet/ClusterSequence.hh>

# include "HJet.hh"

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
    void NewEvent(const hanalysis::HClonesArray*const NewClonesArrays);

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    bool GetJets(const HJetDetails);

    /**
     * @brief Analyses EFlow Variables of Jets
     *
     */
    bool ReadEFlow(const HJetDetails);

    /**
     * @brief Get Tau Tag
     *
     * @return void
     */
    void GetTau(const Jet *const);

    /**
     * @brief Get Gen Jet
     *
     * @param  ...
     * @return void
     */
    void GetGenJet();

    float GetScalarHt();

private:
    
    vector<int> Topology;

    vector<int *> BranchVector;

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    bool GetJets(const bool, const bool);

    vector<PseudoJet> TagJets(vector<PseudoJet>);

    vector<PseudoJet> JetTagger(vector<PseudoJet>, vector<PseudoJet>, int);

    vector<PseudoJet> JetTagger(vector<PseudoJet>, vector<PseudoJet>);

    template <typename TClone>
    hanalysis::HJetInfo GetJetId(const TClone &Clone) {

        Print(3, "Get Jet Id", Clone->Particles.GetEntriesFast());

        hanalysis::HJetInfo JetInfo;

        for (int ParticleNumber = 0; ParticleNumber < Clone->Particles.GetEntriesFast(); ++ParticleNumber) {

            const TObject *const Object = Clone->Particles.At(ParticleNumber);
            const int MotherId = GetMotherId(Object);
            Print(3,"MotherId",MotherId);


            const GenParticle *const ParticleClone = (GenParticle *) Object;
            JetInfo.AddConstituent(MotherId, fabs(ParticleClone->PT));

        }

        JetInfo.PrintAllInfos(4);
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


    int GetMotherId(const TObject *const);

    int GetMotherId(int BranchId, int Position);

    void GetDelphesTags(const Jet *const);

    void GetTrackEFlow(const HJetDetails);

    void GetPhotonEFlow(const HJetDetails);

    void GetHadronEFlow(const HJetDetails);

    void GetMuonEFlow(const HJetDetails);

    PseudoJet GetConstituents(const Jet *const) const;

    inline string ClassName() const {

        return "HDelphes: HJet";

    };

};

#endif
