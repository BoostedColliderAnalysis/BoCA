# ifndef Sextet_hh
# define Sextet_hh

# include "HTriplet.hh"

class hanalysis::HSextet : public HTag
{

public:

    HSextet() {
        Bdt=-10;
    }

    HSextet(const HTriplet &NewTriple1, const HTriplet &NewTriple2);

    ~HSextet();

//     inline float GetInvariantMass()const {
//         return GetPairJet().m();
//     }

    inline float GetBetterTripleMass(const HParticleId ParticleId)const {
        return std::min(Triple1.GetTripleMassDifference(ParticleId), Triple2.GetTripleMassDifference(ParticleId));
    }

    inline float GetWorseTripleMass(const HParticleId ParticleId)const {
        return std::max(Triple1.GetTripleMassDifference(ParticleId), Triple2.GetTripleMassDifference(ParticleId));
    }

    inline float GetBetterPairMass(const HParticleId ParticleId)const {
        return std::min(Triple1.GetDoubletMassDifference(ParticleId), Triple2.GetDoubletMassDifference(ParticleId));
    }

    inline float GetWorsePairMass(const HParticleId ParticleId)const {
        return std::max(Triple1.GetDoubletMassDifference(ParticleId), Triple2.GetDoubletMassDifference(ParticleId));
    }

    inline float GetBetterJetMass(const HParticleId ParticleId)const {
        return std::min(Triple1.GetJetMassDifference(ParticleId), Triple2.GetJetMassDifference(ParticleId));
    }

    inline float GetWorseJetMass(const HParticleId ParticleId)const {
        return std::max(Triple1.GetJetMassDifference(ParticleId), Triple2.GetJetMassDifference(ParticleId));
    }

    inline float GetLargerTripletDeltaR() const {
        return std::max(Triple1.GetDeltaR(), Triple2.GetDeltaR());
    }

    inline float GetSmallerTripletDeltaR() const {
        return std::min(Triple1.GetDeltaR(), Triple2.GetDeltaR());
    }

    inline float GetLargerTripletDeltaRap() const {
        return std::max(Triple1.GetDeltaRap(), Triple2.GetDeltaRap());
    }

    inline float GetSmallerTripletDeltaRap() const {
        return std::min(Triple1.GetDeltaRap(), Triple2.GetDeltaRap());
    }

    inline float GetLargerTripleDeltaPhi() const {
        return std::max(std::abs(Triple1.GetDeltaPhi()), std::abs(Triple2.GetDeltaPhi()));
    }

    inline float GetSmallerTripletDeltaPhi() const {
        return std::min(std::abs(Triple1.GetDeltaPhi()), std::abs(Triple2.GetDeltaPhi()));
    }

//     inline float GetPtSum()const {
//         return (Triple1.GetTripletJet().pt() + Triple1.GetTripletJet().pt());
//     }

    inline fastjet::PseudoJet GetSextetJet() const {
        return (Triple1.GetTripletJet() + Triple2.GetTripletJet());
    }

//     inline float GetPtSum() const {
//         return (Triple1.GetTriplePtSum() + Triple2.GetTriplePtSum());
//     }

//     inline void SetBdt(const float NewBdt) {
//         Bdt = NewBdt;
//     }

//     inline float GetBdt() const {
//         return Bdt;
//     }

//     inline float GetTag() const {
//         return (Triple1.GetTag() * Triple2.GetTag());
//     }

    inline float GetDeltaRap() const {
        return (std::abs(Triple1.GetTripletJet().rap() - Triple2.GetTripletJet().rap()));
    }

    inline float GetDeltaPhi() const {
        return (Triple1.GetTripletJet().delta_phi_to(Triple2.GetTripletJet()));
    }

    inline float GetDeltaR() const {
        return Triple1.GetTripletJet().delta_R(Triple2.GetTripletJet());
    }

    inline HTriplet GetTriplet1()const {
        return Triple1;
    }

    inline HTriplet GetTriplet2()const {
        return Triple2;
    }

    inline float GetMassDifferences(HParticleId ParticleId1, HParticleId ParticleId2, HParticleId ParticleId3) const {

        return Triple1.GetJetMassDifference(ParticleId1) *      Triple1.GetDoubletMassDifference(ParticleId2) *      Triple1.GetTripleMassDifference(ParticleId3) *      Triple2.GetJetMassDifference(ParticleId1) *      Triple2.GetDoubletMassDifference(ParticleId2) *      Triple2.GetTripleMassDifference(ParticleId3);

    }

    void SetError(const float NewError) {
        Error = NewError;
    }
    float GetError() const {
        return Error;
    }

protected:

    virtual inline std::string ClassName() const {
        return "Sextet";
    };

private:


    HTriplet Triple1;

    HTriplet Triple2;

    float Error;

};

#endif
