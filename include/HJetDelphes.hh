# ifndef HJetDelphes_hh
# define HJetDelphes_hh

# include "classes/DelphesClasses.h"
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
    bool GetTaggedJets();

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
    void GetTau(Jet *);

    /**
     * @brief Analyses EFlow Variables of Jets
     *
     */
    bool GetEFlow();

    /**
     * @brief Analyses EFlow Variables of Jets
     *
     */
    bool GetEFlow(bool,bool);

    /**
     * @brief Analyses EFlow Variables of Jets
     *
     */
    bool GetTaggedEFlow();

    /**
     * @brief Get Gen Jet
     *
     * @param  ...
     * @return void
     */
    void GetGenJet();
    GenParticle *GetMotherParticle(GenParticle*);

//     template <typename Template>
//     void GetParticlete(HObject *Object){
//
//
//
//     }


private:

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    bool GetJets(bool,bool);

    vector<PseudoJet> TagJets(vector<PseudoJet>);

    vector<PseudoJet> JetTagger(vector<PseudoJet>, vector<PseudoJet>, int);

    vector<PseudoJet> JetTagger(vector<PseudoJet>, vector<PseudoJet>);

    template <typename Template>
    HJetInfo GetJetId(Template *Clone) {

        Print(1, "Get Jet Id");

	GenParticle *ParticleClone;
        HJetInfo JetInfo;
        TObject *Object;

        Print(2, "Number of Particle", Clone->Particles.GetEntriesFast());
        for (int ParticleNumber = 0; ParticleNumber < Clone->Particles.GetEntriesFast(); ++ParticleNumber) {

            Object = Clone->Particles.At(ParticleNumber);

            if (Object == 0) continue;

            if (Object->IsA() == GenParticle::Class()) {

                ParticleClone = (GenParticle *) Object;

            } else {

                Print(-1, "Object is", Object->ClassName());
                continue;
            }

            JetInfo.AddConstituent(GetMotherId(Object), ParticleClone->PT);

        }

        Print(3, "Jet ID", JetInfo.GetMaximalId(),JetInfo.GetMaximalFraction());

        return JetInfo;

    }


    template<typename ParticleTemplate,typename EFlowTemplate>
    bool GetIsolation(EFlowTemplate *EFlowClone,TClonesArray *ClonesArray) {

        bool Isolated = true;

        for (int ParticleNumber = 0; ParticleNumber < ClonesArray->GetEntriesFast(); ++ParticleNumber) {

            ParticleTemplate *ParticleClone = (ParticleTemplate *) ClonesArray->At(ParticleNumber);
            Isolated = CheckIsolation(EFlowClone, ParticleClone);

        }

        return Isolated;
    }


    int GetMotherId(TObject *);

    void GetDelphesTags(Jet *);

    PseudoJet GetConstituents(Jet *);

    string ClassName() const {

        return ("HJetDelphes");

    };

};

#endif
