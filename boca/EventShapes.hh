// -*- C++ -*-
//
// EventShapes.h is a part of Herwig++ - A multi-purpose Monte Carlo
// event generator Copyright (C) 2002-2011 The Herwig Collaboration
//
// Herwig++ is licenced under version 2 of the GPL, see COPYING for
// details. Please respect the MCnet academic guidelines, see
// GUIDELINES for details.
//

// Jan Hajer - replaced ThePEG classes with BoCA classes

#pragma once

#include "boca/math/Matrix3.hh"
#include "boca/fastjet/Jet.hh"
#include "boca/HemisphereMasses.hh"

namespace boca
{

/**
 * @brief Calculates the event shapes for a given collection of jets.
 */
class EventShapes
{

public:

    /**
    * @name Constructors
    * @{
    */

    /**
    * @brief The default constructor.
    */
    EventShapes();

    /**
     * @brief The constructor accepting jets.
     */
    EventShapes(std::vector<Jet> const& jets);

    /**
     * @brief The constructor accepting lorentz vectors.
     */
    EventShapes(std::vector<LorentzVector<Momentum>> const& lorentz_vectors);
    //@}

    /**
    * @name Thrust related event shapes
    * @{
    */

    /**
    * @brief The thrust
    *
    * algorithm based on Brandt/Dahmen Z Phys C1 (1978)
    */
    double Thrust() const;

    /**
    * @brief The major
    */
    double ThrustMajor() const;

    /**
    * @brief The minor
    */
    double ThrustMinor() const;

    /**
    * @brief The oblateness
    */
    double Oblateness() const;

    /**
    * @brief The thrust axis
    */
    Vector3<double> ThrustAxis() const;

    /**
    * @brief The major axis
    */
    Vector3<double> MajorAxis() const;

    /**
    * @brief The minor axis
    */
    Vector3<double> MinorAxis() const;
    //@}

    /**
    * @name Linear momentum tensor related event shapes
    * @{
    */

    /**
    * @brief The C parameter
    */
    double CParameter() const;

    /**
    * @brief The D parameter
    */
    double DParameter() const;

    /**
    * @brief The eigenvalues in descending order
    */
    std::vector<double> LinTenEigenValues() const;

    /**
    * @brief The eigenvectors in order of descending eigenvalue
    */
    std::vector<Vector3<double>> LinTenEigenVectors() const;
    //@}

    /**
    * @name Quadratic momentum tensor related variables
    * @{
    */

    /**
    * @brief The sphericity
    */
    double Sphericity() const;

    /**
    * @brief The aplanarity
    */
    double Aplanarity() const;

    /**
    * @brief The planarity
    */
    double Planarity() const;

    /**
    * @brief The sphericity axis
    */
    Vector3<double> SphericityAxis() const;

    /**
    * @brief The sphericity eigenvalues
    */
    std::vector<double> SphericityEigenValues() const;

    /**
    * @brief The sphericity eigenvectors
    */
    std::vector<Vector3<double>> SphericityEigenVectors() const;
    //@}

    /**
     * @brief Hemisphere mass variables and jet broadenings
     */
    boca::HemisphereMasses HemisphereMasses() const;

    /**
    * @name Single particle variables which do not depend on event shapes axes
    * @{
    */

    /**
    * @brief The scaled momentum \f$\xi=-\log\left( p/E_{\rm beam}\right)\f$.
    */
    double ScaledMomentum(LorentzVector<Momentum> const& lorentz_vector, Energy const& energy) const;

    /**
    * @brief Transverse momentum with respect to the beam
    */
    Momentum Pt(LorentzVector<Momentum> const& lorentz_vector) const;

    /**
    * @brief Rapidity with respect to the beam direction
    */
    Angle Rapidity(LorentzVector<Momentum> const& lorentz_vector) const;
    //@}

    /**
    * @name Single particle variables related to one of the shape axis.
    * @{
    */

    /**
    * @brief Transverse momentum with respect to the thrust axis in the event plane
    */
    Momentum PtInT(LorentzVector<Momentum> const& lorentz_vector) const;

    /**
    * @brief Transverse momentum with respect to the thrust axis out of the
    * event plane
    */
    Momentum PtOutT(LorentzVector<Momentum> const& lorentz_vector) const;

    /**
    * @brief Rapidity with respect to the thrust axis
    */
    Angle RapidityT(LorentzVector<Momentum> const& lorentz_vector) const;

    /**
    * @brief Transverse momentum with respect to the sphericity axis in the
    * event plane
    */
    Momentum PtInS(LorentzVector<Momentum> const& lorentz_vector) const;

    /**
    * @brief Transverse momentum with respect to the sphericity axis out of the
    * event plane
    */
    Momentum PtOutS(LorentzVector<Momentum> const& lorentz_vector) const;

    /**
    * @brief Rapidity with respect to the sphericity axis
    */
    Angle RapidityS(LorentzVector<Momentum> const& lorentz_vector) const;
    //@}

private:

    /**
    * @name Accessors for certain class of event shapes
    * @{
    */

    /**
     * @brief Scalar sum of all momenta
     */
    Momentum ScalarMomentum() const;

    /**
    * @brief Accessor for the thrust related variables
    */
    Array3<GradedVector3<double>> Thrusts() const;

    /**
    * @brief Accessor for the linear tensor related variables
    */
    Array3<GradedVector3<double>> LinearTensors() const;

    /**
    * @brief Accessor for the quadratic tensor related variables
    */
    Array3<GradedVector3<double>> SphericalTensors() const;
    //@}

    /**
    * @name Methods that actually calculate the event shapes
    * @{
    */

    /**
     * @brief Calculate the thrust and related axes for less than two jets
     */
    Array3<GradedVector3<double>> Thrusts1() const;

    /**
     * @brief Calculate the thrust and related axes for two jets
     */
    Array3<GradedVector3<double>> Thrusts2() const;

    /**
     * @brief Calculate the thrust and related axes for three jets
     */
    Array3<GradedVector3<double>> Thrusts3() const;

    /**
     * @brief Calculate the thrust and related axes for more than three jets
     */
    Array3<GradedVector3<double>> Thrusts4() const;

    /**
    * @brief Calculate the thrust
    */
    GradedVector3<Momentum> Thrust(std::vector<Vector3<Momentum>> const& vectors) const;

    /**
    * @brief Calculate the major
    */
    GradedVector3<Momentum> Major(std::vector<Vector3<Momentum>> const& vectors) const;
    //@}

    /**
    * @name Accessors for jets and vectors
    * @{
    */

    /**
     * @brief Accessor for all jets of lorentz vectors
     */
    std::vector<LorentzVector<Momentum>> LorentzVectors() const;

    /**
     * @brief Accessor for vector of three momenta
     */
    std::vector<Vector3<Momentum>> Vectors() const;
    //@}

    /**
     * @name jets and lorentz vectors
     * @{
     */

    /**
    * @brief Vector of particle 4 momenta to be analysed
    */
    std::vector<LorentzVector<Momentum>> lorentz_vectors_;

    /**
     * @brief Vector of particle 3 momenta to be analysed
     */
    Mutable<std::vector<Vector3<Momentum>>> vectors_;
    //@}

    /**
     * @name Event shape related variables
     * @{
     */

    /**
     * @brief scalar sum of all momenta
     */
    Mutable<Momentum> scalar_momentum_;

    /**
     * @brief The hemisphere masses
     */
    Mutable<boca::HemisphereMasses> hemishpere_masses_;

    /**
     * @brief The thrust related axes
     */
    Mutable<Array3<GradedVector3<double>>> thrusts_;

    /**
     * @brief The sphericity related axes
     */
    Mutable<Array3<GradedVector3<double>>> spherical_tensors_;

    /**
     * @brief The linearised tensor axes
     */
    Mutable<Array3<GradedVector3<double>>> linear_tensors_;
    //@}

};

}
