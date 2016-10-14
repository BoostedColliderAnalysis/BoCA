/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <boost/operators.hpp>

#include "fastjet/PseudoJet.hh"
#include "boca/math/LorentzVector.hh"

class TLorentzVector;

namespace boca
{

template<typename Value_>
class LorentzVector;

/**
* @ingroup FastJet
* @brief Wrapper for fastjet::PseudoJet adding BoCA related functions
*
*/
class PseudoJet : fastjet::PseudoJet
    , boost::totally_ordered<PseudoJet>
{

public:

    /**
    * @name Constructors
    * @{
    */

    /**
    * @brief Default Constructor
    */
    PseudoJet();

    /**
    * @brief Constructor accepting root TLorentzVector
    */
    PseudoJet(fastjet::PseudoJet const &pseudo_jet);

    /**
    * @brief Constructor accepting root TLorentzVector
    */
    PseudoJet(TLorentzVector const &vector);

    /**
    * @brief Constructor accepting momentum lorentz vector
    */
    PseudoJet(boca::LorentzVector<Momentum> const &vector);

    /**
    * @brief Constructor accepting a spatial momentum vector and the energy
    */
    PseudoJet(boca::Vector3<boca::Momentum> const& spatial, const boca::Energy &e);

    /**
    * @brief Constructor accepting a transversal momentum vector, the longitudianl momentum and the energy
    */
    PseudoJet(Vector2<boca::Momentum> const& transverse, Momentum const& z, boca::Energy const& e);

    /**
    * @brief Constructor accepting four momenta
    */
    PseudoJet(Momentum const& x, Momentum const& y, Momentum const& z, boca::Energy const& e);

    PseudoJet(PseudoJet const&) = default;

    PseudoJet(PseudoJet &&) = default;

    //@}

    void Reset(PseudoJet const &pseudo_jet);

    /**
    * @brief Rescale the jet momentum
    *
    * doesnt change the jet energy
    */
    void ScaleMomentum(double factor);

    /**
    * @name Accesors for base class
    * @{
    */

    /**
    * @brief Fastjet PseudoJet
    */
    fastjet::PseudoJet &FastJet();

    fastjet::PseudoJet const &FastJet() const;

    //@}

    /**
    * @name Accesor for UserInfo
    * @{
    */
    virtual UserInfoBase const &Info() const;

    virtual UserInfoBase &Info();

    bool HasInfo();

    //@}

    /**
    * @name Energy related accessors
    * @{
    */

    /**
    * @brief Transverse Momentum
    */
    Momentum Pt() const;

    /**
    * @brief Energy
    */
    boca::Energy Energy() const;

    /**
    * @brief Energy
    */
    boca::Energy E() const;

    /**
     * @brief Transverse energy square
     */
    boca::Energy Et2() const;

    /**
     * @brief transverse energy
     */
    boca::Energy Et() const;

    /**
    * @brief Mass
    */
    boca::Mass Mass() const;

    /**
    * @brief Mass square
    */
    boca::MassSquare MassSquare() const;

    /**
    * @brief X component
    */
    Momentum Px() const;

    /**
    * @brief Y component
    */
    Momentum Py() const;

    /**
    * @brief Z component
    */
    Momentum Pz() const;

    /**
    * @brief squared 3-vector modulus \f$p_x^2+p_y^2+p_z^2\f$
    */
    MomentumSquare ModP2() const;

    /**
    * @brief the 3-vector modulus \f$\sqrt{p_x^2+p_y^2+p_z^2}\f$
    */
    Momentum ModP() const;

    //@}

    /**
    * @name Angle related accessors
    * @{
    */

    /**
    * @brief Rapidity \f$y\f$
    */
    Angle Rap() const;

    /**
    * @brief Azimuth \f$\phi\f$ constrained to \f$[-\pi,\pi]\f$
    */
    Angle Phi() const;

    /**
    * @brief Difference \f$\Delta \phi\f$ to a jet constrained to \f$[-\pi,\pi]\f$
    */
    Angle DeltaPhiTo(PseudoJet const &jet) const;

    /**
    * @brief Difference \f$\Delta y\f$ to a jet
    */
    Angle DeltaRapTo(PseudoJet const &jet) const;

    /**
    * @brief Difference \f$\Delta R\f$ to a jet
    */
    Angle DeltaRTo(PseudoJet const &jet) const;

    //@}

    /**
    * @name Vectors
    * @{
    */

    /**
    * @brief Angular distance to a jet
    */
    Vector2<Angle> DeltaTo(PseudoJet const &jet) const;

    /**
    * @brief Vector of rapidity \f$y\f$ and azimuth \f$\phi\f$
    * @param wrap_phi use the given \f$[-\pi,\pi]\f$ or wrap it by \f$2 \pi\f$
    */
    Vector2<Angle> Angles(bool wrap_phi = false) const;

    /**
    * @brief Vector of rapidity \f$y\f$ and azimuth \f$\phi\f$ with minimal distance to jet
    */
    Vector2<Angle> AnglesMinTo(PseudoJet const &jet) const;

    /**
    * @brief Momentum lorentz vector
    */
    boca::LorentzVector< Momentum > LorentzVector() const;

    /**
    * @brief Momentum three vector
    */
    boca::Vector3<Momentum> Spatial() const;

    /**
    * @brief Transverse momentum vector \f$(p_x,  p_y)\f$
    */
    Vector2<Momentum> Transverse() const;

    //@}

    /**
    * @name Operators
    * @{
    */

    /**
    * @brief Less than comparable
    */
    bool operator<(PseudoJet const &jet) const;

    /**
    * @brief Equality comparable
    */
    bool operator==(const PseudoJet &pseudo_jet) const;

    PseudoJet &operator=(PseudoJet const&) & = default;

    PseudoJet &operator=(PseudoJet &&) & = default;

    //@}

    virtual ~PseudoJet() {}

protected:


};

}
