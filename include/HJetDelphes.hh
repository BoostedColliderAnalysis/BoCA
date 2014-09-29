# ifndef HJetDelphes_hh
# define HJetDelphes_hh

# include "HJet.hh"
# include "classes/DelphesClasses.h"

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
     * @brief Get Gen Jet
     *
     * @param  ...
     * @return void
     */
    void GetGenJet();


private:

    int JetId;

//     Jet *JetClone;

//     TObject* IdentifyObject(TObject *Object);
// 
//     template<typename Template>
//     TObject *GetParticleId(Template Particle) {
// 
//         int ParticleId = Particle->PID;
// //         Print(-1,"PID",ParticleId);
// 
//         if (abs(ParticleId) == BottomId
//                 && (abs(JetId) != TopId
//                     || abs(JetId) != CpvHiggsId)) {
//             JetId = ParticleId;
//         } else if (abs(ParticleId) == TopId && abs(JetId) != HeavyHiggsId) {
//             JetId = ParticleId;
//         } else if (abs(ParticleId) == HeavyHiggsId || abs(ParticleId) == CpvHiggsId) {
//             JetId = ParticleId;
//         }
// //         Print(-1,"PID",JetId);
//         
//         Print(-1,"M1",Particle->M1);
// 
//         TObject *Object;// = JetClone->Particles.At(Particle->M1);
//         
// //         GenParticle *mother = (GenParticle *) ClonesArrays->ParticleClonesArray->At(Particle->M1);
//         
// //         Print(-1,mother->PID);
// 
//         return Object;
// 
//     }

    virtual TString ClassName() {
        return ("HJetDelphes");
    };

};

#endif
