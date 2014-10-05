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

private:

    vector<PseudoJet> TagJets(vector<PseudoJet>);

    vector<PseudoJet> JetTagger(vector<PseudoJet>, vector<PseudoJet>, int);

    vector<PseudoJet> JetTagger(vector<PseudoJet>, vector<PseudoJet>);

    template <typename Template>
    HJetInfo GetJetId(Template *Clone) {

        Print(1, "Get Jet Id");
        
        HJetInfo JetInfo;
        TObject *Object;
        int ConstituentId;
        float ParticlePt;

        Print(2, "Number of Particle", Clone->Particles.GetEntriesFast());
        for (int ParticleNumber = 0; ParticleNumber < Clone->Particles.GetEntriesFast(); ++ParticleNumber) {

            Object = Clone->Particles.At(ParticleNumber);

            if (Object == 0) continue;

            ConstituentId = GetMotherId(Object);

            if (Object == 0) continue;
            GenParticle *ParticleClone;
            if (Object->IsA() == GenParticle::Class()) {
                ParticleClone = (GenParticle *) Object;
            } else {
                Print(-1, "it is", Object->ClassName());
                continue;
            }
            ParticlePt = ParticleClone->PT;

            JetInfo.AddConstituent(ConstituentId, ParticlePt);
            
        }
        
        Print(3,"Max fraction",JetInfo.GetMaximalFraction());

        Print(3, "Jet ID", JetInfo.GetMaximalId());

        return JetInfo;

    }


    int GetMotherId(TObject *);

    void GetTaggs(Jet *);

    PseudoJet GetConstituents(Jet *);

    TString ClassName() const {

        return ("HJetDelphes");

    };

};

#endif
