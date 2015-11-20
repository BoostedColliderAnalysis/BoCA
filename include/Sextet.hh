#pragma once

#include "Triplet.hh"

namespace analysis {

/**
 * @brief A sextet of 2 triplets
 *
 */
class Sextet : public TwoBody<Triplet, Triplet> {

public:

    using TwoBody<Triplet, Triplet>::TwoBody;

    const Triplet& Triplet1() const;

    const Triplet& Triplet2() const;

    float HardTopPt() const
    {
        return std::max(Triplet1().Jet().pt(), Triplet2().Jet().pt());
    }

    float SoftTopPt() const
    {
        return std::min(Triplet1().Jet().pt(), Triplet2().Jet().pt());
    }

    float GetLargertripletDeltaR() const
    {
        return std::max(Triplet1().DeltaR(), Triplet2().DeltaR());
    }

    float GetSmallertripletDeltaR() const
    {
        return std::min(Triplet1().DeltaR(), Triplet2().DeltaR());
    }

    float GetLargertripletDeltaRap() const
    {
        return std::max(Triplet1().DeltaRap(), Triplet2().DeltaRap());
    }

    float GetSmallertripletDeltaRap() const
    {
        return std::min(Triplet1().DeltaRap(), Triplet2().DeltaRap());
    }

    float GetLargerTripleDeltaPhi() const
    {
        return std::max(std::abs(Triplet1().DeltaPhi()), std::abs(Triplet2().DeltaPhi()));
    }

    float GetSmallertripletDeltaPhi() const
    {
        return std::min(std::abs(Triplet1().DeltaPhi()), std::abs(Triplet2().DeltaPhi()));
    }

    float GetBetterTripleMass(Id id) const
    {
        return std::min(Triplet1().MassDifferenceTo(id), Triplet2().MassDifferenceTo(id));
    }

    float GetWorseTripleMass(Id id) const
    {
        return std::max(Triplet1().MassDifferenceTo(id), Triplet2().MassDifferenceTo(id));
    }

    float GetBetterPairMass(Id id) const
    {
        return std::min(Triplet1().Doublet().MassDifferenceTo(id), Triplet2().Doublet().MassDifferenceTo(id));
    }

    float GetWorsePairMass(Id id) const
    {
        return std::max(Triplet1().Doublet().MassDifferenceTo(id), Triplet2().Doublet().MassDifferenceTo(id));
    }

    float GetBetterJetMass(Id id) const
    {
        return std::min(Triplet1().MassDifferenceTo(id), Triplet2().MassDifferenceTo(id));
    }

    float GetWorseJetMass(Id id) const
    {
        return std::max(Triplet1().MassDifferenceTo(id), Triplet2().MassDifferenceTo(id));
    }
    float Dipolarity1() const{
      return  Multiplet::Dipolarity(Triplet1().Singlet(), Triplet2().Singlet());
    }
    float Dipolarity2() const{
      return  Multiplet::Dipolarity(Triplet2().Singlet(), Triplet1().Singlet());
    }
    float Pull1() const{
      return  Multiplet::Pull(Triplet1().Singlet(), Triplet2().Singlet());
    }
    float Pull2() const{
      return  Multiplet::Pull(Triplet2().Singlet(), Triplet1().Singlet());
    }

};

}
