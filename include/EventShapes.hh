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

private:

    void Initialize();

public:

    /**
    * Member functions to return thrust related shapes
    */
    //@{
    /**
    * The thrust
    */
    double Thrust();

    /**
    * The major
    */
    double ThrustMajor();

    /**
    * The minor
    */
    double ThrustMinor();

    /**
    * The oblateness
    */
    double Oblateness();

    /**
    * The thrust axis
    */
    Vector3<double> ThrustAxis();

    /**
    * The major axis
    */
    Vector3<double> MajorAxis();

    /**
    * The minor axis
    */
    Vector3<double> MinorAxis();
    //@}

    /**
    * Linear momentum tensor related event shapes
    */
    //@{
    /**
    * The C parameter
    */
    double CParameter();

    /**
    * The D parameter
    */
    double DParameter();

    /**
    * The eigenvalues in descending order
    */
    std::vector<double> LinTenEigenValues();


    /**
    * The eigenvectors in order of descending eigenvalue
    */
    std::vector<Vector3<double>> LinTenEigenVectors();

    //@}

    /**
    * Quadratic momentum tensor related variables
    */
    //@{
    /**
    * The sphericity
    */
    double Sphericity();

    /**
    * The aplanarity
    */
    double Aplanarity();


    /**
    * The planarity
    */
    double Planarity();

    /**
    * The sphericity axis
    */
    Vector3<double> SphericityAxis();


    /**
    * The sphericity eigenvalues
    */
    std::vector<double> SphericityEigenValues();

    /**
    * The sphericity eigenvectors
    */
    std::vector<Vector3<double>> SphericityEigenVectors();

    //@}

    /**
    * Jet mass related event shapes
    */
    //@{
    /**
    * The high hemishpere mass squared divided by the visible energy
    * squared
    */
    double MHigh2();

    /**
    * The low hemishpere mass squared divided by the visible energy
    * squared
    */
    double MLow2();

    /**
    * The difference between the
    * hemishpere masses squared divided by the visible energy squared
    */
    double MDiff2();

    //@}

    /**
    * Jet broadening related event shapes
    */
    //@{
    /**
    * The wide jet broadening
    */
    double BMax();

    /**
    * The narrow jet broadening
    */
    double BMin();

    /**
    * The sum of the jet broadenings
    */
    double BSum();


    /**
    * The difference of the jet broadenings
    */
    double BDiff();
    //@}

    /**
    * Single particle variables which do not depend on event shapes axes
    */
    //@{

    /**
    * The scaled momentum \f$\xi=-\log\left( p/E_{\rm beam}\right)\f$.
    */
    double ScaledMomentum(const LorentzVector<Momentum>& p, const Energy& Ebeam);

    /**
    * Transverse momentum with respect to the beam
    */
    Energy Pt(const LorentzVector<Momentum>& p);

    /**
    * Rapidity with respect to the beam direction
    */
    Angle Rapidity(const LorentzVector<Momentum>& p);
    //@}

    /**
    * Single particle variables related to one of the shape axis.
    */
    //@{

    /**
    * Transverse momentum with respect to the thrust axis in the event plane
    */
    Momentum PtInT(const LorentzVector<Momentum>& p);

    /**
    * Transverse momentum with respect to the thrust axis out of the
    * event plane
    */
    Momentum PtOutT(const LorentzVector<Momentum>& p);

    /**
    * Rapidity with respect to the thrust axis
    */
    Angle RapidityT(const LorentzVector<Momentum>& p);

    /**
    * Transverse momentum with respect to the sphericity axis in the
    * event plane
    */
    Momentum PtInS(const LorentzVector<Momentum>& p);

    /**
    * Transverse momentum with respect to the sphericity axis out of the
    * event plane
    */
    Momentum PtOutS(const LorentzVector<Momentum>& p);

    /**
    * Rapidity with respect to the sphericity axis
    */
    Angle RapidityS(const LorentzVector<Momentum>& p);
    //@}


    /**
    * Energy-energy correlation (EEC) @param hi is the histogram and has
    * to be provided externally It is understood that the range of the
    * histogam is -1 < cos(chi) < 1. hi.front() contains the bin [-1 <
    * cos(chi) < -1+delta] and hi.back() the bin [1-delta < cos(chi) <
    * 1]. delta = 2/hi.size(). We use classical indices to access the
    * vector.
    */
    void BookEEC(std::vector<double>& hi);

    /**
    * Before writing the histogram it has to be normalized according to
    * the number of events.
    */
    void NormalizeEEC(std::vector<double>& hi, long evts);

    /**
    * The asymmetry of EEC is calculated from a given \f$\cos\chi\f$ and
    * EEC histogram, which is a std::vector<double> as described above.
    */
    double AEEC(std::vector<double>& hi, double& coschi);

private:

    /**
    * Check whether the initialization of a certain class of event shapes
    * has been calculated and if not do so
    */
    //@{
    /**
    * Check if thrust related variables have been calculated and if not
    * do so
    */
    void CheckThrust();

    /**
    * Check if the linear tensor related variables have been calculated
    * and if not do so
    */
    void CheckLinTen();

    /**
    * Check if the quadratic tensor related variables have been
    * calculated and if not do so
    */
    void CheckSphericity();

    /**
    * Check if the hemisphere mass variables and jet broadenings have
    * been calculated and if not do so
    */
    void CheckHemispheres();
    //@}

    /**
    * Methods that actually calculate the event shapes
    */
    //@{
    /**
    * Calculate the hemisphere masses and jet broadenings
    */
    void CalcHemisphereMasses();

    /**
    * Calculate the thrust and related axes
    */
    void CalculateThrust();

    /**
    * Diagonalize the tensors @param linear switch between
    * diagonalization of linear/quadratic tensor. @param cmboost tells
    * whether to boost into cm frame of all momenta first, or not
    * (default off, and no interface to this).
    */
    void DiagonalizeTensors(bool linear, bool cmboost);

    /**
    * Quite general diagonalization of a symmetric Matrix T, given as an
    * array of doubles. The symmetry is not checked explicitly as this
    * is clear in the context. It uses an explicit generic solution of
    * the eigenvalue problem and no numerical approximation, based on
    * Cardano's formula. @param T Matrix to be diagonalised
    */
    std::vector<double> Eigenvalues(const double T[3][3]);

    /**
    * The eigenvector of @param T to a given eigenvalue @param lam
    */
    Vector3<double> eigenvector(const double T[3][3], const double& lam);

    /**
    * The eigenvectors of @param T corresponding to the eigenvectors
    * @param lam . The ordering of the vectors corresponds to the
    * ordering of the eigenvalues.
    */
    std::vector<Vector3<double>> Eigenvectors(const double T[3][3], const std::vector<double>& lam);

    /**
    * Member to calculate the thrust
    * @param p The three vectors
    * @param t The thrust-squared (up to an Energy scale factor)
    * @param taxis The thrust axis
    */
    void CalcT(const std::vector<Vector3<Momentum>>& p, EnergySquare& t, Vector3<double>& taxis);

    /**
    * Member to calculate the major
    * @param p The three vectors
    * @param m The major-squared (up to an Energy scale factor)
    * @param maxis The major axis
    */
    void CalcM(const std::vector<Vector3<Momentum>>& p, EnergySquare& m, Vector3<double>& maxis);
    //@}

private:

    /**
    * Vector of particle momenta to be analysed
    */
    std::vector<LorentzVector<Momentum>> lorentz_vectors_;

    /**
    * Various event shape axes
    */
    //@{
    /**
    * The thrust related axes
    */
    std::vector<Vector3<double>> thrust_axis_;

    /**
    * The sphericity related axes
    */
    std::vector<Vector3<double>> spher_axis_;

    /**
    * The linearised tensor axes
    */
    std::vector<Vector3<double>> lin_ten_axis_;
    //@}

    /**
    * Values of axis related event shapes
    */
    //@{
    /**
    * Values of thrust related variables
    */
    std::vector<double> thrust_;

    /**
    * Values of sphericity related variables
    */
    std::vector<double> spher_;

    /**
    * Values of linearized tensor related variables
    */
    std::vector<double> lin_ten_;
    //@}

    /**
    * Whether or not certain event axes have been calculated
    */
    //@{
    /**
    * Whether or not the thrust is calculated
    */
    bool thrust_done_;

    /**
    * Whether or not the sphericity is calculated
    */
    bool spher_done_;

    /**
    * Whether or not the linearizes tensor is calculated
    */
    bool lin_ten_done_;

    /**
    * Whether or not the hemisphere masses have been calculated
    */
    bool hem_done_;
    //@}

    /**
    * Whether ot not to boost to the CMS frame for the tensor diagonalizations
    */
    bool use_cm_boost_;

    /**
    * Hemisphere masses
    */
    //@{
    /**
    * The high hemisphere mass
    */
    double m_plus_;

    /**
    * The low hemisphere mass
    */
    double m_minus_;
    //@}

    /**
    * The jet broadenings
    */
    //@{
    /**
    * The wide jet broadening
    */
    double b_plus_;

    /**
    * The narrow jet broadening
    */
    double b_minus_;
    //@}
};

}
