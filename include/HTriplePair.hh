# ifndef HTriplePair_hh
# define HTriplePair_hh

# include "HTriple.hh"

class hanalysis::HTriplePair : public HTag
{

public:

    HTriplePair() {}

    HTriplePair(const HTriple &NewTriple1, const HTriple &NewTriple2);

    ~HTriplePair();

    inline float GetInvariantMass()const {
        return GetPairJet().m();
    }

    inline float GetBetterTripleMass(const HParticleId ParticleId)const {
        return std::min(Triple1.GetTripleMassDifference(ParticleId),Triple2.GetTripleMassDifference(ParticleId));
    }

    inline float GetWorseTripleMass(const HParticleId ParticleId)const {
        return std::max(Triple1.GetTripleMassDifference(ParticleId),Triple2.GetTripleMassDifference(ParticleId));
    }

    inline float GetBetterPairMass(const HParticleId ParticleId)const {
        return std::min(Triple1.GetPairMassDifference(ParticleId),Triple2.GetPairMassDifference(ParticleId));
    }

    inline float GetWorsePairMass(const HParticleId ParticleId)const {
        return std::max(Triple1.GetPairMassDifference(ParticleId),Triple2.GetPairMassDifference(ParticleId));
    }

    inline float GetBetterJetMass(const HParticleId ParticleId)const {
        return std::min(Triple1.GetJet1MassDifference(ParticleId),Triple2.GetJet1MassDifference(ParticleId));
    }

    inline float GetWorseJetMass(const HParticleId ParticleId)const {
        return std::max(Triple1.GetJet1MassDifference(ParticleId),Triple2.GetJet1MassDifference(ParticleId));
    }

    inline float GetLargerTripleDeltaR() const {
        return std::max(Triple1.GetTripleDeltaR(),Triple2.GetTripleDeltaR());
    }

    inline float GetSmallerTripleDeltaR() const {
        return std::min(Triple1.GetTripleDeltaR(),Triple2.GetTripleDeltaR());
    }

    inline float GetLargerTripleDeltaRap() const {
        return std::max(Triple1.GetTripleDeltaRap(),Triple2.GetTripleDeltaRap());
    }

    inline float GetSmallerTripleDeltaRap() const {
        return std::min(Triple1.GetTripleDeltaRap(),Triple2.GetTripleDeltaRap());
    }
    
    inline float GetLargerTripleDeltaPhi() const {
      return std::max(Triple1.GetTripleDeltaPhi(),Triple2.GetTripleDeltaPhi());
    }
    
    inline float GetSmallerTripleDeltaPhi() const {
      return std::min(Triple1.GetTripleDeltaPhi(),Triple2.GetTripleDeltaPhi());
    }

    inline float GetPtSum()const {
        return (Triple1.GetTriplePtSum() + Triple1.GetTriplePtSum());
    }

    inline fastjet::PseudoJet GetPairJet() const {
        return (Triple1.GetTripleJet() + Triple2.GetTripleJet());
    }

//     inline float GetPtSum() const {
//         return (Triple1.GetTriplePtSum() + Triple2.GetTriplePtSum());
//     }

    inline float GetBdt() const {
        return (Triple1.GetBdt() * Triple2.GetBdt());
    }

//     inline float GetTag() const {
//         return (Triple1.GetTag() * Triple2.GetTag());
//     }

    inline float GetDeltaRap() const {
        return (std::abs(Triple1.GetTripleJet().rap() - Triple2.GetTripleJet().rap()));
    }

    inline float GetDeltaPhi() const {
        return (Triple1.GetTripleJet().delta_phi_to(Triple2.GetTripleJet()));
    }

    inline float GetDeltaR() const {
        return Triple1.GetTripleJet().delta_R(Triple2.GetTripleJet());
    }

    inline HTriple GetTriple1()const {
        return Triple1;
    }

    inline HTriple GetTriple2()const {
        return Triple2;
    }

    inline float GetMassDifferences(HParticleId ParticleId1,HParticleId ParticleId2,HParticleId ParticleId3) const {

        return Triple1.GetJet1MassDifference(ParticleId1)*      Triple1.GetPairMassDifference(ParticleId2)*      Triple1.GetTripleMassDifference(ParticleId3)*      Triple2.GetJet1MassDifference(ParticleId1)*      Triple2.GetPairMassDifference(ParticleId2)*      Triple2.GetTripleMassDifference(ParticleId3);

    }
    
    void SetError(const float NewError){Error = NewError;}
    float GetError() const {return Error;}

protected:

    virtual inline std::string ClassName() const {
        return "HTriplePair";
    };

private:


    HTriple Triple1;

    HTriple Triple2;

    float Error;
    
};

#endif
