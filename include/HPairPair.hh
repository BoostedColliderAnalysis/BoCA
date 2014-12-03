# ifndef HPairPair_hh
# define HPairPair_hh

# include "HJetLeptonPair.hh"
# include "WIMPMASS.h"

class hanalysis::HPairPair : public HTag
{

public:

    HPairPair() {}

    HPairPair(const HJetLeptonPair &NewPair1, const HJetLeptonPair &NewPair2);

    HPairPair(const HJetLeptonPair &NewPair1, const HJetLeptonPair &NewPair2, const float NewMet);

    void SetMet(const float NewMet) {
        Met = NewMet;
    }

    ~HPairPair();

    float GetDeltaR() const {
        return Pair1.GetPairJet().delta_R(Pair2.GetPairJet());
    }

    float GetInvariantMass() const {
        return GetPairJet().m();
    }

    inline float GetMassDifference(const int ParticleMass) const {
        return std::abs(GetInvariantMass() - ParticleMass);
    }

    inline float GetMissDifference(const HParticleId ParticleId) const {
        return std::abs(GetInvariantMass() - GetParticleMass(ParticleId));
    }

    fastjet::PseudoJet GetPairJet() const {
        return (Pair1.GetPairJet() + Pair2.GetPairJet());
    }

    float GetPtSum() const {
        return (Pair1.GetPtSum() + Pair2.GetPtSum());
    }

    float GetBdt() const {
        return (Pair1.GetBdt() * Pair2.GetBdt());
    }

    float GetTag() const {
        return (Pair1.GetTag() * Pair2.GetTag());
    }

    float GetDeltaRap() const {
        return (std::abs(Pair1.GetPairJet().rap() - Pair2.GetPairJet().rap()));
    }

    float GetDeltaPhi() const {
        return (Pair1.GetPairJet().delta_phi_to(Pair2.GetPairJet()));
    }

    void GetMt2() {
        event22 evt;
        evt.p5 = GetMomentum(Pair1.GetJet1());
        evt.p5 = GetMomentum(Pair1.GetJet1());
        evt.p3 = GetMomentum(Pair1.GetJet2());
        evt.p6 = GetMomentum(Pair2.GetJet1());
        evt.p4 = GetMomentum(Pair2.GetJet2());
        evt.pmiss = Met;



        std::cout << "Visible momenta and the missing transverse momentum:" << std::endl;
        std::cout << "p3 = " << evt.p3[0] << "   " << evt.p3[1] << "   "
                  << evt.p3[2] << "   " << evt.p3[3] << std::endl;
        std::cout << "p4 = " << evt.p4[0] << "   " << evt.p4[1] << "   "
                  << evt.p4[2] << "   " << evt.p4[3] << std::endl;
        std::cout << "p5 = " << evt.p5[0] << "   " << evt.p5[1] << "   "
                  << evt.p5[2] << "   " << evt.p5[3] << std::endl;
        std::cout << "p6 = " << evt.p6[0] << "   " << evt.p6[1] << "   "
                  << evt.p6[2] << "   " << evt.p6[3] << std::endl;
        std::cout << "pmiss x,y = " << "   " << evt.pmiss[1] << "   " << evt.pmiss[2] << std::endl;


        int nsols;
        double p1[4][4], p2[4][4];
        evt.solve22(evt, 0, WMass, TopMass, nsols, p1, p2);

        for (int isol = 0; isol < nsols; isol ++) {
            std::cout << std::endl << "solution " << isol << std::endl;
            std::cout << "p1 = " << p1[isol][0] << "  " << p1[isol][1] << "  "
                      << p1[isol][2] << "  " << p1[isol][3] << std::endl;
            std::cout << "p2 = " << p2[isol][0] << "  " << p2[isol][1] << "  "
                      << p2[isol][2] << "  " << p2[isol][3] << std::endl;
        }

    }

protected:

    virtual inline std::string ClassName() const {
        return "HPairPair";
    };

private:

    float GetMomentum(fastjet::PseudoJet Jet) {
        float Momentum[4];
        Momentum[0] = Jet.E();
        Momentum[1] = Jet.px();
        Momentum[2] = Jet.py();
        Momentum[3] = Jet.pz();
        return Momentum;
    };

    HPair Pair1;

    HPair Pair2;

    float Met;

};

#endif
