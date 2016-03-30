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

#include "Jet.hh"
#include "Mutable.hh"
#include "HemisphereMasses.hh"
#include "GradedVector.hh"
#include "physics/Matrix3.hh"

namespace boca
{

/**
 *
 * The EventShapes class is designed so that certain event shapes, such
 * as the thrust are only calculated once per event given the speed of
 * the calculation.
 *
 */
class EventShapes
{
public:
    /**
    * The default constructor.
    */
    EventShapes();
    /**
     * The constructor accepting jets.
     */
    EventShapes(std::vector<Jet> const& jets);
    /**
     * The constructor accepting lorentz vectors.
     */
    EventShapes(std::vector<LorentzVector<Momentum>> const& lorentz_vectors);
    /**
    * Thrust related event shapes
    */
    //@{
    /**
    * The thrust
    */
    double Thrust() const;
    /**
    * The major
    */
    double ThrustMajor() const;
    /**
    * The minor
    */
    double ThrustMinor() const;
    /**
    * The oblateness
    */
    double Oblateness() const;
    /**
    * The thrust axis
    */
    Vector3<double> ThrustAxis() const;
    /**
    * The major axis
    */
    Vector3<double> MajorAxis() const;
    /**
    * The minor axis
    */
    Vector3<double> MinorAxis() const;
    //@}
    /**
    * Linear momentum tensor related event shapes
    */
    //@{
    /**
    * The C parameter
    */
    double CParameter() const;
    /**
    * The D parameter
    */
    double DParameter() const;
    /**
    * The eigenvalues in descending order
    */
    std::vector<double> LinTenEigenValues() const;
    /**
    * The eigenvectors in order of descending eigenvalue
    */
    std::vector<Vector3<double>> LinTenEigenVectors() const;
    //@}
    /**
    * Quadratic momentum tensor related variables
    */
    //@{
    /**
    * The sphericity
    */
    double Sphericity() const;
    /**
    * The aplanarity
    */
    double Aplanarity() const;
    /**
    * The planarity
    */
    double Planarity() const;
    /**
    * The sphericity axis
    */
    Vector3<double> SphericityAxis() const;
    /**
    * The sphericity eigenvalues
    */
    std::vector<double> SphericityEigenValues() const;
    /**
    * The sphericity eigenvectors
    */
    std::vector<Vector3<double>> SphericityEigenVectors() const;
    //@}
    /**
     * Hemisphere massvariables and jet broadenings
     */
    boca::HemisphereMasses HemisphereMasses() const;
    /**
    * Single particle variables which do not depend on event shapes axes
    */
    //@{
    /**
    * The scaled momentum \f$\xi=-\log\left( p/E_{\rm beam}\right)\f$.
    */
    double ScaledMomentum(LorentzVector<Momentum> const& lorentz_vector, Energy const& energy) const;
    /**
    * Transverse momentum with respect to the beam
    */
    Momentum Pt(LorentzVector<Momentum> const& lorentz_vector) const;
    /**
    * Rapidity with respect to the beam direction
    */
    Angle Rapidity(LorentzVector<Momentum> const& lorentz_vector) const;
    //@}
    /**
    * Single particle variables related to one of the shape axis.
    */
    //@{
    /**
    * Transverse momentum with respect to the thrust axis in the event plane
    */
    Momentum PtInT(LorentzVector<Momentum> const& lorentz_vector) const;
    /**
    * Transverse momentum with respect to the thrust axis out of the
    * event plane
    */
    Momentum PtOutT(LorentzVector<Momentum> const& lorentz_vector) const;
    /**
    * Rapidity with respect to the thrust axis
    */
    Angle RapidityT(LorentzVector<Momentum> const& lorentz_vector) const;
    /**
    * Transverse momentum with respect to the sphericity axis in the
    * event plane
    */
    Momentum PtInS(LorentzVector<Momentum> const& lorentz_vector) const;
    /**
    * Transverse momentum with respect to the sphericity axis out of the
    * event plane
    */
    Momentum PtOutS(LorentzVector<Momentum> const& lorentz_vector) const;
    /**
    * Rapidity with respect to the sphericity axis
    */
    Angle RapidityS(LorentzVector<Momentum> const& lorentz_vector) const;
    //@}

    /**
    * Energy-energy correlation (EEC) @param hi is the histogram and has
    * to be provided externally It is understood that the range of the
    * histogam is -1 < cos(chi) < 1. hi.front() contains the bin [-1 <
    * cos(chi) < -1+delta] and hi.back() the bin [1-delta < cos(chi) <
    * 1]. delta = 2/hi.size(). We use classical indices to access the
    * vector.
    */
    std::vector<double> EnergyEnergyCorrelation(int bins = 10) const;

    /**
    * Before writing the histogram it has to be normalized according to
    * the number of events.
    */
    void NormalizeEEC(std::vector<double>& hi, long evts) const;

    /**
    * The asymmetry of EEC is calculated from a given \f$\cos\chi\f$ and
    * EEC histogram, which is a std::vector<double> as described above.
    */
    double AEEC(std::vector<double>& hi, double& coschi) const;

private:

    template<typename Value_>
    using Vector = std::array<Value_, 3>;
    /**
    * Accessors for certain class of event shapes
    */
    //@{
    /**
    * Accessor for the thrust related variables
    */
    Vector<GradedVector3<double>> Thrusts() const;
    /**
    * Accessor for the linear tensor related variables
    */
    Vector<GradedVector3<double>> LinearTensors() const;
    /**
    * Accessor for the quadratic tensor related variables
    */
    Vector<GradedVector3<double>> SphericalTensors() const;
    //@}
    /**
    * Methods that actually calculate the event shapes
    */
    //@{
    /**
    * Calculate the hemisphere masses and jet broadenings
    */
    boca::HemisphereMasses GetHemisphereMasses() const;
    /**
    * Calculate the thrust and related axes
    */
    Vector<GradedVector3<double>> GetThrusts() const;
    /**
     * Calculate the thrust and related axes for less than two jets
     */
    Vector<GradedVector3<double>> GetThrusts1() const;
    /**
     * Calculate the thrust and related axes for two jets
     */
    Vector<GradedVector3<double>> GetThrusts2() const;
    /**
     * Calculate the thrust and related axes for three jets
     */
    Vector<GradedVector3<double>> GetThrusts3() const;
    /**
     * Calculate the thrust and related axes for more than three jets
     */
    Vector<GradedVector3<double>> GetThrusts4() const;
    /**
     * Diagonalize the linear tensors
     */
    Vector<GradedVector3<double>> DiagonalizeLinearTensors() const;
    /**
     * Diagonalize the quadratic tensor
     */
    Vector<GradedVector3<double>> DiagonalizeSphericalTensors() const;
    /**
    * Quite general diagonalization of a symmetric @param matrix, given as an
    * array of doubles. The symmetry is not checked explicitly as this
    * is clear in the context. It uses an explicit generic solution of
    * the eigenvalue problem and no numerical approximation, based on
    * Cardano's formula.
    */
    Vector<double> Eigenvalues(Matrix3<double> const& matrix) const;
    /**
     * The eigensystem of @param matrix
     */
    Vector<GradedVector3<double>> EigenSystem(Matrix3<double> const& matrix) const;
    /**
     * The eigenvector of @param matrix to a given eigenvalue @param eigenvalue
    */
    Vector3<double> Eigenvector(Matrix3<double> const& matrix, double const& eigenvalue) const;
    /**
     * The eigenvectors of @param matrix corresponding to the eigenvalues
    * @param eigenvalues. The ordering of the vectors corresponds to the
    * ordering of the eigenvalues.
    */
    Vector<Vector3<double>> Eigenvectors(Matrix3<double> const& matrix, Vector<double> const& eigenvalues) const;
    /**
    * Calculate the thrust
    * @param vectors The three vectors
    */
    GradedVector3<Momentum> Thrust(std::vector<Vector3<Momentum>> const& vectors) const;
    /**
    * Calculate the major
    * @param vectors The three vectors
    */
    GradedVector3<Momentum> Major(std::vector<Vector3<Momentum>> const& vectors) const;
    //@}
    /**
     * @brief Accessor for all vecor of LorentzVectors
     *
     */
    std::vector<LorentzVector<Momentum>> LorentzVectors() const;
    /**
     * @brief Accessor for vector of three momenta
     *
     */
    std::vector<Vector3<Momentum>> Vectors() const;
    /**
     * @brief scalar sum of all momenta
     */
    Momentum ScalarMomentum() const;
    /**
    * Vector of particle 4 momenta to be analysed
    */
    std::vector<LorentzVector<Momentum>> lorentz_vectors_;

    /**
     * Vector of particle 3 momenta to be analysed
     */
    std::vector<Vector3<Momentum>> vectors_;

    /**
     * Various event shapes
     */
    //@{
    /**
     * The thrust related axes
     */
    Mutable<Vector<GradedVector3<double>>> thrusts_;
    /**
     * The sphericity related axes
     */
    Mutable<Vector<GradedVector3<double>>> spherical_tensors_;
    /**
     * The linearised tensor axes
     */
    Mutable<Vector<GradedVector3<double>>> linear_tensors_;
    //@}
    /**
     * The hemisphere masses
     */
    Mutable<boca::HemisphereMasses> hemishpere_masses_;

};

}
