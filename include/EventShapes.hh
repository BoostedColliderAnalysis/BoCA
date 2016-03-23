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

namespace boca
{

template<typename Value_>
class EventShape
{
public:
    EventShape() {}
    EventShape(Vector3<Value_> vector, Value_ scalar) {
        Set(vector, scalar);
    }
    void Set(Vector3<Value_> vector, Value_ scalar) {
        vector_ = vector;
        scalar_ = scalar;
    }
    void Set(Vector3<Value_> vector) {
        vector_ = vector;
    }
    void Set(Value_ scalar) {
        scalar_ = scalar;
    }
    Vector3<Value_>& Vector() {
        return vector_;
    }
    Value_& Scalar() {
        return scalar_;
    }
    Vector3<Value_> const& Vector() const {
        return vector_;
    }
    Value_ const& Scalar() const {
        return scalar_;
    }
    EventShape& operator+=(EventShape<Value_> const& event_shape) {
        vector_ += event_shape.Vector();
        scalar_ += event_shape.Scalar();
        return *this;
    }
private:
    Vector3<Value_> vector_;
    Value_ scalar_ = Value_(0);
};


/**
 * Hemisphere masses
 */
class HemisphereMasses
{

public:
    void SetM(double m_minus, double m_plus) {
        if (m_plus < m_minus) std::swap(m_plus, m_minus);
        m_plus_ = m_plus;
        m_minus_ = m_minus;
    }
    void SetB(double b_minus, double b_plus) {
        if (b_plus < b_minus) std::swap(b_plus, b_minus);
        b_plus_ = b_plus;
        b_minus_ = b_minus;
    }
    double MHigh2() const {
        return m_plus_;
    }
    double MLow2() const {
        return m_minus_;
    }
    double MDiff2() const {
        return m_plus_ - m_minus_;
    }
    double BMax() const {
        return b_plus_;
    }
    double BMin() const {
        return b_minus_;
    }
    double BSum() const {
        return b_plus_ + b_minus_;
    }
    double BDiff() const {
        return b_plus_ - b_minus_;
    }
private:
    /**
     * The high hemisphere mass
     */
    double m_plus_ = 0;

    /**
     * The low hemisphere mass
     */
    double m_minus_ = 0;
//@}

    /**
     * The jet broadenings
     */
//@{
    /**
     * The wide jet broadening
     */
    double b_plus_ = 0;

    /**
     * The narrow jet broadening
     */
    double b_minus_ = 0;
//@}

};

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
    * Member to reset the particles to be considered
    */
    void Reset(std::vector<Jet> const& jets);

    /**
    * Member functions to return thrust related shapes
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
    * Jet mass related event shapes
    */
    //@{
    /**
    * The high hemishpere mass squared divided by the visible energy
    * squared
    */
    double MHigh2() const;

    /**
    * The low hemishpere mass squared divided by the visible energy
    * squared
    */
    double MLow2() const;

    /**
    * The difference between the
    * hemishpere masses squared divided by the visible energy squared
    */
    double MDiff2() const;

    //@}

    /**
    * Jet broadening related event shapes
    */
    //@{
    /**
    * The wide jet broadening
    */
    double BMax() const;

    /**
    * The narrow jet broadening
    */
    double BMin() const;

    /**
    * The sum of the jet broadenings
    */
    double BSum() const;

    /**
    * The difference of the jet broadenings
    */
    double BDiff() const;
    //@}

    /**
    * Single particle variables which do not depend on event shapes axes
    */
    //@{

    /**
    * The scaled momentum \f$\xi=-\log\left( p/E_{\rm beam}\right)\f$.
    */
    double ScaledMomentum(LorentzVector<Momentum> const& p, const Energy& Ebeam) const;

    /**
    * Transverse momentum with respect to the beam
    */
    Energy Pt(LorentzVector<Momentum> const& p) const;

    /**
    * Rapidity with respect to the beam direction
    */
    Angle Rapidity(LorentzVector<Momentum> const& p) const;
    //@}

    /**
    * Single particle variables related to one of the shape axis.
    */
    //@{

    /**
    * Transverse momentum with respect to the thrust axis in the event plane
    */
    Momentum PtInT(LorentzVector<Momentum> const& p) const;

    /**
    * Transverse momentum with respect to the thrust axis out of the
    * event plane
    */
    Momentum PtOutT(LorentzVector<Momentum> const& p) const;

    /**
    * Rapidity with respect to the thrust axis
    */
    Angle RapidityT(LorentzVector<Momentum> const& p) const;

    /**
    * Transverse momentum with respect to the sphericity axis in the
    * event plane
    */
    Momentum PtInS(LorentzVector<Momentum> const& p) const;

    /**
    * Transverse momentum with respect to the sphericity axis out of the
    * event plane
    */
    Momentum PtOutS(LorentzVector<Momentum> const& p) const;

    /**
    * Rapidity with respect to the sphericity axis
    */
    Angle RapidityS(LorentzVector<Momentum> const& p) const;
    //@}

    /**
    * Energy-energy correlation (EEC) @param hi is the histogram and has
    * to be provided externally It is understood that the range of the
    * histogam is -1 < cos(chi) < 1. hi.front() contains the bin [-1 <
    * cos(chi) < -1+delta] and hi.back() the bin [1-delta < cos(chi) <
    * 1]. delta = 2/hi.size(). We use classical indices to access the
    * vector.
    */
    void BookEEC(std::vector<double>& hi) const;

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
    using Matrix = Vector<Vector<double>>;

    /**
    * Check whether the initialization of a certain class of event shapes
    * has been calculated and if not do so
    */
    //@{
    /**
    * Check if thrust related variables have been calculated and if not
    * do so
    */
    Vector<EventShape<double>> Thrusts() const;

    /**
    * Check if the linear tensor related variables have been calculated
    * and if not do so
    */
    Vector<EventShape<double>> LinearTensors() const;

    /**
    * Check if the quadratic tensor related variables have been
    * calculated and if not do so
    */
    Vector<EventShape<double>> SphericalTensors() const;

    /**
    * Check if the hemisphere mass variables and jet broadenings have
    * been calculated and if not do so
    */
    HemisphereMasses HemispheresMasses() const;
    //@}

    /**
    * Methods that actually calculate the event shapes
    */
    //@{
    /**
    * Calculate the hemisphere masses and jet broadenings
    */
    HemisphereMasses GetHemisphereMasses() const;

    /**
    * Calculate the thrust and related axes
    */
    Vector<EventShape<double>> GetThrusts() const;

    /**
    * Diagonalize the tensors @param linear switch between
    * diagonalization of linear/quadratic tensor. @param cmboost tells
    * whether to boost into cm frame of all momenta first, or not
    * (default off, and no interface to this).
    */
    Vector<EventShape<double>> DiagonalizeTensors(bool linear) const;
    Vector<EventShape<double>> DiagonalizeLinearTensors() const;
    Vector<EventShape<double>> DiagonalizeSphericalTensors() const;

    /**
    * Quite general diagonalization of a symmetric Matrix T, given as an
    * array of doubles. The symmetry is not checked explicitly as this
    * is clear in the context. It uses an explicit generic solution of
    * the eigenvalue problem and no numerical approximation, based on
    * Cardano's formula. @param T Matrix to be diagonalised
    */
    Vector<double> Eigenvalues(Matrix const& matrix) const;

    Vector<EventShape<double>> EigenSystem(Matrix const& matrix) const;

    /**
     * The eigenvector of @param T to a given eigenvalue @param eigenvalue
    */
    Vector3<double> Eigenvector(Matrix const& matrix, const double& eigenvalue) const;

    /**
     * The eigenvectors of @param T corresponding to the eigenvalues
    * @param lam . The ordering of the vectors corresponds to the
    * ordering of the eigenvalues.
    */
    Vector<Vector3<double>> Eigenvectors(Matrix const& matrix, const Vector<double>& eigenvalues) const;

    /**
    * Member to calculate the thrust
    * @param p The three vectors
    * @param t The thrust-squared (up to an Energy scale factor)
    * @param taxis The thrust axis
    */
    EventShape< Momentum > CalcT(const std::vector< Vector3< boca::Momentum > >& vectors) const;

    /**
    * Member to calculate the major
    * @param p The three vectors
    * @param m The major-squared (up to an Energy scale factor)
    * @param maxis The major axis
    */
    EventShape< Momentum > CalcM(const std::vector< Vector3< boca::Momentum > >& vectors) const;
    //@}

    /**
    * Vector of particle momenta to be analysed
    */
    std::vector<LorentzVector<Momentum>> lorentz_vectors_;

    /**
     * Whether ot not to boost to the CMS frame for the tensor diagonalizations
     */
    bool use_cm_boost_ = false;

    /**
     * Various event shapes
     */
    //@{
    /**
     * The thrust related axes
     */
    Mutable<Vector<EventShape<double>>> thrusts_;

    /**
     * The sphericity related axes
     */
    Mutable<Vector<EventShape<double>>> spherical_tensors_;

    /**
     * The linearised tensor axes
     */
    Mutable<Vector<EventShape<double>>> linear_tensors_;
    //@}

    Mutable<HemisphereMasses> hemishpere_masses_;

};

}
