#pragma once

#include "boca/delphes/Forward.hh"
#include "boca/exroot/Forward.hh"

#include "boca/math/LorentzVectorBase.hh"

class TLorentzVector;

namespace boca
{

/**
 * @ingroup Math
 * @brief Lorentz vector
 */
template<typename Value_>
class LorentzVector : public LorentzVectorBase<Value_>
{
    using LorentzVectorBase<Value_>::LorentzVectorBase;
};

/**
 * @ingroup Math
 * @brief Momentum Lorentz vector
 */
template<>
class LorentzVector<Momentum> : public LorentzVectorBase<Momentum>
{

public:

    /**
     * @name Constructor
     * @{
     */

    using LorentzVectorBase<Momentum>::LorentzVectorBase;

    /**
     * @brief Default constructor
     */
    LorentzVector();

//     LorentzVector(LorentzVectorBase<Momentum> const& lorentz_vector);

    /**
     * @brief Constructor accepting root::TLorentzVector
     */
    LorentzVector(TLorentzVector const &lorentzvector);

    /**
     * @brief Constructor accepting exroot::Electron
     */
    LorentzVector(exroot::Electron const &electron);

    /**
     * @brief Constructor accepting exroot::GenJet
     */
    LorentzVector(exroot::GenJet const &jet);

    /**
     * @brief Constructor accepting exroot::GenParticle
     */
    LorentzVector(exroot::GenParticle const &particle);

    /**
     * @brief Constructor accepting exroot::Jet
     */
    LorentzVector(exroot::Jet const &jet);

    /**
     * @brief Constructor accepting exroot::LHEFParticle
     */
    LorentzVector(exroot::LHEFParticle const &particle);

    /**
     * @brief Constructor accepting exroot::Muon
     */
    LorentzVector(exroot::Muon const &muon);

    /**
     * @brief Constructor accepting exroot::Photon
     */
    LorentzVector(exroot::Photon const &photon);

    /**
     * @brief Constructor accepting exroot::Tau
     */
    LorentzVector(exroot::Tau const &tau);

    //@}

    /**
     * @name Setter
     * @{
     */

    /**
     * @brief Setter for px py pz e
     */
    void SetPxPyPzE(Momentum const&px, Momentum const&py, Momentum const&pz, const boca::Energy &energy);

    /**
     * @brief Setter for pt eta phi m
     */
    void SetPtEtaPhiM(Momentum const &pt, boca::Angle const &eta, boca::Angle const &phi, boca::Mass const &mass);


    /**
     * @brief Setter for pt eta phi e
     */
    void SetPtEtaPhiE(Momentum const &pt, boca::Angle const &eta, boca::Angle const &phi, boca::Energy const &energy);

    /**
     * @brief Setter for a exroot Particle
     */
    template<typename Particle>
    void LorentzVectorByEnergy(const Particle &particle)
    {
        SetPtEtaPhiE(particle.PT * GeV, particle.Eta * rad, particle.Phi * rad, particle.E * GeV);
    }

    /**
     * @brief Setter for a exroot Particle and a mass
     */
    template<typename Particle>
    void LorentzVectorByMass(const Particle &particle, boca::Mass const &mass)
    {
        SetPtEtaPhiM(particle.PT * GeV, particle.Eta * rad, particle.Phi * rad, mass);
    }

    /**
     * @brief Setter for a exroot Particle
     */
    template<typename Particle>
    void LorentzVectorByMass(const Particle &particle)
    {
        LorentzVectorByMass(particle, particle.Mass * GeV);
    }

    /**
     * @brief Setter for a exroot Particle
     */
    template<typename Particle>
    void LorentzVectorByM(const Particle &particle)
    {
        LorentzVectorByMass(particle, particle.M * GeV);
    }

    //@}

    /**
     * @name Accessor and Getter
     * @{
     */

    /**
    * @brief Px
    */
    Momentum Px() const;

    /**
    * @brief Py
    */
    Momentum Py() const;

    /**
    * @brief Pz
    */
    Momentum Pz() const;

    /**
    * @brief Energy
    */
    boca::Energy E() const;

    /**
    * @brief Energy
    */
    boca::Energy Energy() const;

    /**
    * @brief Px
    */
    Momentum &Px() ;

    /**
    * @brief Py
    */
    Momentum &Py() ;

    /**
    * @brief Pz
    */
    Momentum &Pz() ;

    /**
    * @brief Energy
    */
    boca::Energy &E() ;

    /**
    * @brief Energy
    */
    boca::Energy &Energy() ;

    //@}

    /**
     * @name Energy related variables
     * @{
     */

    /**
    * @brief Momentum
    */
    Momentum P() const;

    /**
    * @brief Transverse energy squared.
    */
    EnergySquare Et2() const;

    /**
    * @brief Transverse energy.
    */
    boca::Energy Et() const;

    /**
    * @brief Transverse energy w.r.t. given axis squared.
    */
    template<typename Value,  typename = OnlyIfNotQuantity<Value>>
    EnergySquare Et2(Vector3<Value> const &vector) const
    {
        return ScalarT2(vector);
    }

    /**
    * @brief Transverse energy w.r.t. given axis.
    */
    template<typename Value,  typename = OnlyIfNotQuantity<Value>>
    boca::Energy Et(Vector3<Value> const &vector) const
    {
        return ScalarT(vector);
    }

    /**
    * @brief Mass square
    */
    MassSquare M2() const;

    /**
    * @brief Mass
    */
    boca::Mass M() const;

    /**
    * @brief Mass
    */
    boca::Mass Mass() const;

    /**
    * @brief Transverse mass squared.
    */
    MassSquare Mt2() const;

    /**
    * @brief Transverse mass.
    */
    boca::Mass Mt() const;

    /**
    * @brief Transverse component of the spatial vector(R in cylindrical system).
    */
    Momentum Pt() const;

    /**
    * @brief Transverse component of the spatial vector w.r.t. given axis.
    */
    template<typename Value,  typename = OnlyIfNotQuantity<Value>>
    Momentum Pt(Vector3<Value> const &vector) const
    {
        return Perp(vector);
    }

    //@}
};

/**
 * @ingroup Math
 * @brief Length Lorentz vector
 */
template<>
class LorentzVector<Length> : public LorentzVectorBase<Length>
{
public:

    /**
     * @name Constructor
     * @{
     */

    using LorentzVectorBase<Length>::LorentzVectorBase;

    /**
     * @brief Default constructor
     */
    LorentzVector();

    /**
     * @brief Constructor accepting a delphes::Track
     */
    LorentzVector(::delphes::Track &track);

    /**
     * @brief Constructor accepting a delphes::GenParticle
     */
    LorentzVector(::delphes::GenParticle &particle);

    //@}

    /**
     * @brief Smearing of the for vector
     */
    void Smearing(const boca::Length &amount);

};

}

