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

    /**
     * Initialize variables and get LorentzVector from Jets
     */
    void Initialize();

    /**
    * Check whether the initialization of a certain class of event shapes
    * has been calculated and if not do so
    */
    //@{
    /**
    * Check if thrust related variables have been calculated and if not
    * do so
    */
    void CheckThrust() const;

    /**
    * Check if the linear tensor related variables have been calculated
    * and if not do so
    */
    void CheckLinTen() const;

    /**
    * Check if the quadratic tensor related variables have been
    * calculated and if not do so
    */
    void CheckSphericity() const;

    /**
    * Check if the hemisphere mass variables and jet broadenings have
    * been calculated and if not do so
    */
    void CheckHemispheres() const;
    //@}

    /**
    * Methods that actually calculate the event shapes
    */
    //@{
    /**
    * Calculate the hemisphere masses and jet broadenings
    */
    void CalcHemisphereMasses() const;

    /**
    * Calculate the thrust and related axes
    */
    void CalculateThrust() const;

    /**
    * Diagonalize the tensors @param linear switch between
    * diagonalization of linear/quadratic tensor. @param cmboost tells
    * whether to boost into cm frame of all momenta first, or not
    * (default off, and no interface to this).
    */
    void DiagonalizeTensors(bool linear, bool cmboost) const;

    /**
    * Quite general diagonalization of a symmetric Matrix T, given as an
    * array of doubles. The symmetry is not checked explicitly as this
    * is clear in the context. It uses an explicit generic solution of
    * the eigenvalue problem and no numerical approximation, based on
    * Cardano's formula. @param T Matrix to be diagonalised
    */
    std::vector<double> Eigenvalues(const double T[3][3]) const;

    /**
    * The eigenvector of @param T to a given eigenvalue @param lam
    */
    Vector3<double> Eigenvector(const double T[3][3], const double& lam) const;

    /**
    * The eigenvectors of @param T corresponding to the eigenvectors
    * @param lam . The ordering of the vectors corresponds to the
    * ordering of the eigenvalues.
    */
    std::vector<Vector3<double>> Eigenvectors(const double T[3][3], const std::vector<double>& lam) const;

    /**
    * Member to calculate the thrust
    * @param p The three vectors
    * @param t The thrust-squared (up to an Energy scale factor)
    * @param taxis The thrust axis
    */
    void CalcT(std::vector<Vector3<Momentum>> const& p, EnergySquare& t, Vector3< double >& taxis) const;

    /**
    * Member to calculate the major
    * @param p The three vectors
    * @param m The major-squared (up to an Energy scale factor)
    * @param maxis The major axis
    */
    void CalcM(std::vector<Vector3<Momentum>> const& p, EnergySquare& m, Vector3<double>& maxis) const;
    //@}

    /**
    * Vector of particle momenta to be analysed
    */
    std::vector<LorentzVector<Momentum>> lorentz_vectors_;

    /**
     * Whether ot not to boost to the CMS frame for the tensor diagonalizations
     */
    bool use_cm_boost_;

    /**
    * Various event shape axes
    */
    //@{
    /**
    * The thrust related axes
    */
    mutable std::vector<Vector3<double>> thrust_axis_;

    /**
    * The sphericity related axes
    */
    mutable std::vector<Vector3<double>> spher_axis_;

    /**
    * The linearised tensor axes
    */
    mutable std::vector<Vector3<double>> lin_ten_axis_;
    //@}

    /**
    * Values of axis related event shapes
    */
    //@{
    /**
    * Values of thrust related variables
    */
    mutable std::vector<double> thrust_;

    /**
    * Values of sphericity related variables
    */
    mutable std::vector<double> spher_;

    /**
    * Values of linearized tensor related variables
    */
    mutable std::vector<double> lin_ten_;
    //@}

    /**
    * Whether or not certain event axes have been calculated
    */
    //@{
    /**
    * Whether or not the thrust is calculated
    */
    mutable bool thrust_done_;

    /**
    * Whether or not the sphericity is calculated
    */
    mutable bool spher_done_;

    /**
    * Whether or not the linearizes tensor is calculated
    */
    mutable bool lin_ten_done_;

    /**
    * Whether or not the hemisphere masses have been calculated
    */
    mutable bool hem_done_;
    //@}

    /**
    * Hemisphere masses
    */
    //@{
    /**
    * The high hemisphere mass
    */
    mutable double m_plus_;

    /**
    * The low hemisphere mass
    */
    mutable double m_minus_;
    //@}

    /**
    * The jet broadenings
    */
    //@{
    /**
    * The wide jet broadening
    */
    mutable double b_plus_;

    /**
    * The narrow jet broadening
    */
    mutable double b_minus_;
    //@}

};

}
