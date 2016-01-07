// -*- C++ -*-
//
// EventShapes.h is a part of Herwig++ - A multi-purpose Monte Carlo
// event generator Copyright (C) 2002-2011 The Herwig Collaboration
//
// Herwig++ is licenced under version 2 of the GPL, see COPYING for
// details.  Please respect the MCnet academic guidelines, see
// GUIDELINES for details.
//

#pragma once

// #include "ThePEG/Vectors/Lorentz5Vector.h"
// #include "ThePEG/EventRecord/Particle.h"
#include "Jet.hh"
#include "physics/Vector3.hh"

namespace boca
{

/**
 *
 * The EventShapes class is designed so that certain event shapes, such
 * as the thrust are only calculated once per event given the speed of
 * the calculation.
 *
 */
class EventShapes //: public ThePEG::Interfaced
{

public:

    /**
     * The default constructor.
     */
    EventShapes() :
        _thrustDone(false),
        _spherDone(false),
        _linTenDone(false),
        _hemDone(false),
        _useCmBoost(false),
        _mPlus(),
        _mMinus(),
        _bPlus(),
        _bMinus()
    {}

    /**
     *  Member to reset the particles to be considered
     */
    void reset(std::vector<Jet> const& part) {
        _pv.resize(part.size());
        for (unsigned int ix = 0; ix < part.size(); ++ix) _pv[ix] = part[ix].Vector();
//       _pv = part;
        _thrustDone = false;
        _spherDone  = false;
        _linTenDone = false;
        _hemDone    = false;
        _useCmBoost = false;
    }


public:

    /**
     *  Member functions to return thrust related shapes
     */
    //@{
    /**
     *  The thrust
     */
    double thrust() {
        checkThrust();
        return _thrust[0];
    }

    /**
     *  The major
     */
    double thrustMajor() {
        checkThrust();
        return _thrust[1];
    }

    /**
     *  The minor
     */
    double thrustMinor() {
        checkThrust();
        return _thrust[2];
    }

    /**
     *  The oblateness
     */
    double oblateness() {
        checkThrust();
        return _thrust[1] - _thrust[2];
    }

    /**
     *  The thrust axis
     */
    Vector3<double> thrustAxis() {
        checkThrust();
        return _thrustAxis[0];
    }

    /**
     *  The major axis
     */
    Vector3<double> majorAxis() {
        checkThrust();
        return _thrustAxis[1];
    }

    /**
     *  The minor axis
     */
    Vector3<double> minorAxis() {
        checkThrust();
        return _thrustAxis[2];
    }
    //@}

    /**
     * Linear momentum tensor related event shapes
     */
    //@{
    /**
     *  The C parameter
     */
    double CParameter() {
        checkLinTen();
        return 3.*(_linTen[0] * _linTen[1] + _linTen[1] * _linTen[2]
                   + _linTen[2] * _linTen[0]);
    }

    /**
     *  The D parameter
     */
    double DParameter() {
        checkLinTen();
        return 27.*(_linTen[0] * _linTen[1] * _linTen[2]);
    }

    /**
     *  The eigenvalues in descending order
     */
    std::vector<double> linTenEigenValues() {
        checkLinTen();
        return _linTen;
    }


    /**
     *  The eigenvectors in order of descending eigenvalue
     */
    std::vector<Vector3<double>> linTenEigenVectors() {
        checkLinTen();
        return _linTenAxis;
    }

    //@}

    /**
     * Quadratic momentum tensor related variables
     */
    //@{
    /**
     *  The sphericity
     */
    double sphericity() {
        checkSphericity();
        return 3. / 2.*(_spher[1] + _spher[2]);
    }

    /**
     *  The aplanarity
     */
    double aplanarity() {
        checkSphericity();
        return 3. / 2.*_spher[2];
    }


    /**
     *  The planarity
     */
    double planarity() {
        checkSphericity();
        return _spher[1] - _spher[2];
    }

    /**
     *  The sphericity axis
     */
    Vector3<double> sphericityAxis() {
        checkSphericity();
        return _spherAxis[0];
    }


    /**
     *  The sphericity eigenvalues
     */
    std::vector<double> sphericityEigenValues() {
        checkSphericity();
        return _spher;
    }

    /**
     *  The sphericity eigenvectors
     */
    std::vector<Vector3<double>> sphericityEigenVectors() {
        checkSphericity();
        return _spherAxis;
    }  //@}

    /**
     * Jet mass related event shapes
     */
    //@{
    /**
     *  The high hemishpere mass squared divided by the visible energy
     *  squared
     */
    double Mhigh2() {
        checkHemispheres();
        return _mPlus;
    }

    /**
     *  The low hemishpere mass squared divided by the visible energy
     *  squared
     */
    double Mlow2() {
        checkHemispheres();
        return _mMinus;
    }

    /**
     *  The difference between the
     * hemishpere masses squared divided by the visible energy squared
     */
    double Mdiff2() {
        checkHemispheres();
        return _mPlus - _mMinus;
    }

    //@}

    /**
     * Jet broadening related event shapes
     */
    //@{
    /**
     *  The wide jet broadening
     */
    double Bmax() {
        checkHemispheres();
        return _bPlus;
    }

    /**
     *  The narrow jet broadening
     */
    double Bmin() {
        checkHemispheres();
        return _bMinus;
    }

    /**
     *  The sum of the jet broadenings
     */
    double Bsum() {
        checkHemispheres();
        return _bPlus + _bMinus;
    }


    /**
     *  The difference of the jet broadenings
     */
    double Bdiff() {
        checkHemispheres();
        return _bPlus - _bMinus;
    }
    //@}

    /**
     *  Single particle variables which do not depend on event shapes axes
     */
    //@{

    /**
     *  The scaled momentum \f$\xi=-\log\left( p/E_{\rm beam}\right)\f$.
     */
    double getXi(const LorentzVector<Momentum>& p, const Energy& Ebeam) {
        return ((Ebeam > 0_GeV && p.Vect().Mag() > 0_GeV) ? std::log(Ebeam / p.Vect().Mag()) : -1.);
    }

    /**
     *  Transverse momentum with respect to the beam
     */
    Energy getPt(const LorentzVector<Momentum>& p) {
        return p.Perp();
    }

    /**
     *  Rapidity with respect to the beam direction
     */
    Angle getRapidity(const LorentzVector<Momentum>& p) {
        return (p.T() > p.Z() ? p.Rapidity() : 1e99_rad);
    }
    //@}

    /**
     * Single particle variables related to one of the shape axis.
     */
    //@{
    /**
     *  Transverse momentum with respect to the thrust axis in the event plane
     */
    Energy ptInT(const LorentzVector<Momentum>& p) {
        checkThrust();
        return p.Vect() * _thrustAxis[1];
    }

    /**
     *  Transverse momentum with respect to the thrust axis out of the
     *  event plane
     */
    Energy ptOutT(const LorentzVector<Momentum>& p) {
        checkThrust();
        return p.Vect() * _thrustAxis[2];
    }

    /**
     *  Rapidity with respect to the thrust axis
     */
    Angle yT(const LorentzVector<Momentum>& p) {
        checkThrust();
        return (p.T() > p.Vect() * _thrustAxis[0] ? p.Rapidity(_thrustAxis[0]) : 1e99_rad);
    }

    /**
     *  Transverse momentum with respect to the sphericity axis in the
     *  event plane
     */
    Energy ptInS(const LorentzVector<Momentum>& p) {
        checkSphericity();
        return p.Vect() * _spherAxis[1];
    }

    /**
     *  Transverse momentum with respect to the sphericity axis out of the
     *  event plane
     */
    Energy ptOutS(const LorentzVector<Momentum>& p) {
        checkSphericity();
        return p.Vect() * _spherAxis[2];
    }

    /**
     *  Rapidity with respect to the sphericity axis
     */
    Angle yS(const LorentzVector<Momentum>& p) {
        checkSphericity();
        return (p.T() > p.Vect() * _spherAxis[0] ? p.Rapidity(_spherAxis[0]) : 1e99_rad);
    }
    //@}


    /**
     * Energy-energy correlation (EEC) @param hi is the histogram and has
     * to be provided externally It is understood that the range of the
     * histogam is -1 < cos(chi) < 1.  hi.front() contains the bin [-1 <
     * cos(chi) < -1+delta] and hi.back() the bin [1-delta < cos(chi) <
     * 1].  delta = 2/hi.size(). We use classical indices to access the
     * vector.
     */
    void bookEEC(std::vector<double>& hi);

    /**
     * Before writing the histogram it has to be normalized according to
     * the number of events.
     */
    void normalizeEEC(std::vector<double>& hi, long evts) {
        for (unsigned int bin = 0; bin < hi.size(); bin++) bin /= (hi.size() * evts);
    }

    /**
     * The asymmetry of EEC is calculated from a given \f$\cos\chi\f$ and
     * EEC histogram, which is a std::vector<double> as described above.
     */
    double AEEC(std::vector<double>& hi, double& coschi) {
        if (coschi > 0. && coschi <= 1.) {
            int i = static_cast<int>(floor((-coschi + 1.) / 2.*hi.size()));
            int j = static_cast<int>(floor((coschi + 1.) / 2.*hi.size()));
            return hi[i] - hi[j];
        } else {
            return 1e99;
        }
    }

public:

    /**
     * The standard Init function used to initialize the interfaces.
     * Called exactly once for each class by the class description system
     * before the main function starts or when this class is dynamically
     * loaded.
     */
//     static void Init();

protected:

    /** @name Clone Methods. */
    //@{
    /**
     * Make a simple clone of this object.  @return a pointer to the new
     * object.
     */
//   virtual ThePEG::IBPtr clone() const override { return new_ptr(*this); }

    /** Make a clone of this object, possibly modifying the cloned object
     * to make it sane.  @return a pointer to the new object.
     */
//   virtual ThePEG::IBPtr fullclone() const override { return new_ptr(*this); }
    //@}

private:

    /**
     *  Check whether the initialization of a certain class of event shapes
     *  has been calculated and if not do so
     */
    //@{
    /**
     *  Check if thrust related variables have been calculated and if not
     *  do so
     */
    void checkThrust() {
        if (!_thrustDone) {
            _thrustDone = true;
            calculateThrust();
        }
    }

    /**
     *  Check if the linear tensor related variables have been calculated
     *  and if not do so
     */
    void checkLinTen() {
        if (!_linTenDone) {
            _linTenDone = true;
            diagonalizeTensors(true, _useCmBoost);
        }
    }

    /**
     *  Check if the quadratic tensor related variables have been
     *  calculated and if not do so
     */
    void checkSphericity() {
        if (!_spherDone) {
            _spherDone = true;
            diagonalizeTensors(false, _useCmBoost);
        }
    }

    /**
     *  Check if the hemisphere mass variables and jet broadenings have
     *  been calculated and if not do so
     */
    void checkHemispheres() {
        if (!_hemDone) {
            _hemDone = true;
            calcHemisphereMasses();
        }
    }
    //@}

    /**
     *  Methods that actually calculate the event shapes
     */
    //@{
    /**
     *  Calculate the hemisphere masses and jet broadenings
     */
    void calcHemisphereMasses();

    /**
     * Calculate the thrust and related axes
     */
    void calculateThrust();

    /**
     * Diagonalize the tensors @param linear switch between
     * diagonalization of linear/quadratic tensor.  @param cmboost tells
     * whether to boost into cm frame of all momenta first, or not
     * (default off, and no interface to this).
     */
    void diagonalizeTensors(bool linear, bool cmboost);

    /**
     * Quite general diagonalization of a symmetric Matrix T, given as an
     * array of doubles.  The symmetry is not checked explicitly as this
     * is clear in the context.  It uses an explicit generic solution of
     * the eigenvalue problem and no numerical approximation, based on
     * Cardano's formula.  @param T Matrix to be diagonalised
     */
    std::vector<double> eigenvalues(const double T[3][3]);

    /**
     * The eigenvector of @param T to a given eigenvalue @param lam
     */
    Vector3<double> eigenvector(const double T[3][3], const double& lam);

    /**
     * The eigenvectors of @param T corresponding to the eigenvectors
     * @param lam . The ordering of the vectors corresponds to the
     * ordering of the eigenvalues.
     */
    std::vector<Vector3<double>> eigenvectors(const double T[3][3], const std::vector<double>& lam);

    /**
     *  Member to calculate the thrust
     * @param p The three vectors
     * @param t The thrust-squared (up to an Energy scale factor)
     * @param taxis The thrust axis
     */
    void calcT(const std::vector<Vector3<Momentum>>& p, EnergySquare& t, Vector3<double>& taxis);

    /**
     *  Member to calculate the major
     * @param p The three vectors
     * @param m The major-squared (up to an Energy scale factor)
     * @param maxis The major axis
     */
    void calcM(const std::vector<Vector3<Momentum>>& p, EnergySquare& m, Vector3<double>& maxis);
    //@}

private:

    /**
     * The static object used to initialize the description of this class.
     * Indicates that this is a concrete class with persistent data.
     */
//     static ThePEG::NoPIOClassDescription<EventShapes> initEventShapes;

    /**
     * The assignment operator is private and must never be called.
     * In fact, it should not even be implemented.
     */
    EventShapes& operator=(const EventShapes&);

private:

    /**
     *  Vector of particle momenta to be analysed
     */
//     std::vector<LorentzVector<Momentum>> _pv;
    std::vector<LorentzVector<Momentum>> _pv;

    /**
     *  Various event shape axes
     */
    //@{
    /**
     *  The thrust related axes
     */
    std::vector<Vector3<double>> _thrustAxis;

    /**
     *  The sphericity related axes
     */
    std::vector<Vector3<double>> _spherAxis;

    /**
     *  The linearised tensor axes
     */
    std::vector<Vector3<double>> _linTenAxis;
    //@}

    /**
     *  Values of axis related event shapes
     */
    //@{
    /**
     *  Values of thrust related variables
     */
    std::vector<double> _thrust;

    /**
     *  Values of sphericity related variables
     */
    std::vector<double> _spher;

    /**
     *  Values of linearized tensor related variables
     */
    std::vector<double> _linTen;
    //@}

    /**
     *  Whether or not certain event axes have been calculated
     */
    //@{
    /**
     *  Whether or not the thrust is calculated
     */
    bool _thrustDone;

    /**
     *  Whether or not the sphericity is calculated
     */
    bool _spherDone;

    /**
     *  Whether or not the linearizes tensor is calculated
     */
    bool _linTenDone;

    /**
     *  Whether or not the hemisphere masses have been calculated
     */
    bool _hemDone;
    //@}

    /**
     *  Whether ot not to boost to the CMS frame for the tensor diagonalizations
     */
    bool _useCmBoost;

    /**
     *  Hemisphere masses
     */
    //@{
    /**
     *  The high hemisphere mass
     */
    double _mPlus;

    /**
     *  The low hemisphere mass
     */
    double _mMinus;
    //@}

    /**
     *  The jet broadenings
     */
    //@{
    /**
     *  The wide jet broadening
     */
    double _bPlus;

    /**
     *  The narrow jet broadening
     */
    double _bMinus;
    //@}
};

}
