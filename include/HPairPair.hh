# ifndef HPairPair_hh
# define HPairPair_hh

# include "HJetLeptonPair.hh"

class hanalysis::HPairPair : public HTag
{

public:
    
    HPairPair(){}

    HPairPair(const HJetLeptonPair &NewPair1, const HJetLeptonPair &NewPair2);

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

    fastjet::PseudoJet GetPairJet() const {
        return (Pair1.GetPairJet() + Pair2.GetPairJet());
    }

    float GetPtSum() const {
        return (Pair1.GetPtSum() + Pair2.GetPtSum());
    }

    float GetBdt() const {
        return (Pair1.GetBdt() * Pair2.GetBdt());
    }

    float GetDeltaRap() const {
        return (std::abs(Pair1.GetPairJet().rap() - Pair2.GetPairJet().rap()));
    }

    float GetDeltaPhi() const {
        return (Pair1.GetPairJet().delta_phi_to(Pair2.GetPairJet()));
    }
    
protected:

    virtual inline std::string ClassName() const {
        return "HPairPair";
    };

    virtual inline std::string NameSpaceName() const {
        return "hanalysis";
    };


private:

    HPair Pair1;

    HPair Pair2;

    float Met;

};

#endif
