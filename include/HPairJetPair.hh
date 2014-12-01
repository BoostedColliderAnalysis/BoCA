# ifndef HPairJetPair_hh
# define HPairJetPair_hh

# include "HJetLeptonPair.hh"

class hanalysis::HPairJetPair : public HTag
{

public:
    
    HPairJetPair(){}

    HPairJetPair(const HPair &NewPair, const fastjet::PseudoJet &NewJet);

    ~HPairJetPair();

    float GetDeltaR() const {
        return Pair.GetPairJet().delta_R(Jet);
    }

    float GetInvariantMass() const {
        return GetPairJet().m();
    }

    fastjet::PseudoJet GetPairJet() const {
        return (Pair.GetPairJet() + Jet);
    }

    float GetPtSum() const {
        return (Pair.GetPtSum() + Jet.pt());
    }

    float GetBdt() const {
        return (Pair.GetBdt() * Jet.user_info<HJetInfo*>().GetBdt());
    }

    float GetDeltaRap() const {
        return (Pair.GetPairJet().rap() - Jet.rap());
    }

    float GetDeltaPhi() const {
        return (Pair.GetPairJet().delta_phi_to(Jet));
    }
    
protected:

    virtual inline std::string ClassName() const {
        return "HPairJetPair";
    };

    virtual inline std::string NameSpaceName() const {
        return "hanalysis";
    };


private:

    fastjet::PseudoJet Jet;

    HPair Pair;

};

#endif
