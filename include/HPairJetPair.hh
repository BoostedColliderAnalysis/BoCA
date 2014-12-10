# ifndef HPairJetPair_hh
# define HPairJetPair_hh

# include "HJetLeptonPair.hh"

class hanalysis::HPairJetPair : public HTag
{

public:

    HPairJetPair() {}

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

//     float GetPtSum() const {
//         return (Pair.GetPtSum() + Jet.pt());
//     }

    float GetJetPt() const {
        return Jet.pt();
    }

    float GetPairPt() const {
        return Pair.GetPtSum();
    }

    float GetBdt() const {
        return (Pair.GetBdt() * Jet.user_info<HJetInfo>().GetBdt());
    }

    float GetDeltaRap() const {
        return (std::abs(Pair.GetPairJet().rap() - Jet.rap()));
    }

    /// returns delta phi between -pi and pi
    float GetDeltaPhi() const {
        return (Pair.GetPairJet().delta_phi_to(Jet));
    }

    fastjet::PseudoJet GetJet() const {
        return Jet;
    }
    fastjet::PseudoJet GetPairJet1() const {
        return Pair.GetJet1();
    }
    fastjet::PseudoJet GetPairJet2() const {
        return Pair.GetJet2();
    }

protected:

    virtual inline std::string ClassName() const {
        return "HPairJetPair";
    };

private:

    fastjet::PseudoJet Jet;

    HPair Pair;

};

#endif
