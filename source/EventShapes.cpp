// -*- C++ -*-
//
// EventShapes.cc is a part of Herwig++ - A multi-purpose Monte Carlo event generator
// Copyright (C) 2002-2011 The Herwig Collaboration
//
// Herwig++ is licenced under version 2 of the GPL, see COPYING for details.
// Please respect the MCnet academic guidelines, see GUIDELINES for details.
//
//
// This is the implementation of the non-inlined, non-templated member
// functions of the EventShapes class.
//

#include "EventShapes.hh"
#include "boost/units/cmath.hpp"

// using namespace Herwig;
namespace boca
{

// ThePEG::NoPIOClassDescription<EventShapes> EventShapes::initEventShapes;
// Definition of the static class description member.

// void EventShapes::Init()
// {
//
//     static ThePEG::ClassDocumentation<EventShapes> documentation
//     ("There is no documentation for the EventShapes class");
//
// }

void EventShapes::calcHemisphereMasses()
{
    LorentzVector<Momentum> pos, neg;
    Energy pden(0), epos(0), eneg(0);
    for (auto & elem : _pv) {
        if (elem.Vect() * thrustAxis() > 0._GeV) {
            pos += elem;
            // can be replaced with, once perp() is giving non-nan results
            //      for nearly parallel vectors.
            // epos += _pv[ix].perp(thrustAxis());
            epos += elem.Vect().Cross(thrustAxis()).Mag();
        } else {
            neg += elem;
            // see above
            //      eneg += _pv[ix].perp(thrustAxis());
            eneg += elem.Vect().Cross(thrustAxis()).Mag();
        }
        pden += elem.Vect().Mag();
    }
    // denominator and masses
    EnergySquare den(sqr(pos.E() + neg.E()));
    _mPlus = pos.M2() / den;
    _mMinus = neg.M2() / den;
    if (_mPlus < _mMinus) std::swap(_mPlus, _mMinus);
    // jet broadening
    _bPlus  = 0.5 * epos / pden;
    _bMinus = 0.5 * eneg / pden;
    if (_bPlus < _bMinus) std::swap(_bPlus, _bMinus);
}

std::vector<double> EventShapes::eigenvalues(const double T[3][3])
{

    // b, c, d are the coefficients of the characteristic polynomial,
    // a lambda^3 + b lambda^2 + c lambda + d
    // where a is chosen to be +1.
    double t11, t12, t13, t22, t23, t33;
    t11 = T[0][0]; t12 = T[0][1]; t13 = T[0][2];
    t22 = T[1][1]; t23 = T[1][2]; t33 = T[2][2];
    double b = -(t11 + t22 + t33);
    double c = t11 * t22 + t11 * t33 + t22 * t33 - sqr(t12) - sqr(t13) - sqr(t23);
    double d = - t11 * t22 * t33 - 2.*t12 * t23 * t13
               + t11 * sqr(t23) + t22 * sqr(t13) + t33 * sqr(t12);

    // use Cardano's formula to compute the zeros
    double p = (3.*c - sqr(b)) / 3.;
    double q = (2.*sqr(b) * b - 9.*b * c + 27.*d) / 27.;
    // check diskriminant to double precision
    std::vector<double> lambda;
    if (4.*p * sqr(p) + 27.*sqr(q) > 2.0e-16) {
        for (unsigned int i = 0; i < 3; ++i) {
            lambda.emplace_back(-1.);
        }
        std::cerr << "EventShapes::eigenvalues: found D = "
                  << 4.*p* sqr(p) + 27.*sqr(q)
                  << " > 0! No real Eigenvalues!\n";
    } else {
        // get solutions
        double alpha = std::acos(-q / 2.*std::sqrt(-27. / (p * p * p))) / 3.;
        double w = std::sqrt(-4.*p / 3.);
        lambda.emplace_back(w * std::cos(alpha) - b / 3.);
        lambda.emplace_back(-w * std::cos(alpha + M_PI / 3.) - b / 3.);
        lambda.emplace_back(-w * std::cos(alpha - M_PI / 3.) - b / 3.);
    }

    // sort according to size of eigenvalues
    // such that lambda[0] > lambda[1] > lambda[2]
    if (lambda[0] < lambda[1]) {
        std::swap(lambda[0], lambda[1]);
    }
    if (lambda[0] < lambda[2]) {
        std::swap(lambda[0], lambda[2]);
    }
    if (lambda[1] < lambda[2]) {
        std::swap(lambda[1], lambda[2]);
    }

    return lambda;
}


Vector3<double> EventShapes::eigenvector(const double T[3][3], const double& lam)
{
    // set up matrix of system to be solved
    double a11, a12, a13, a23, a33;
    a11 = T[0][0] - lam;
    a12 = T[0][1];
    a13 = T[0][2];
    a23 = T[1][2];
    a33 = T[2][2] - lam;

    // intermediate steps from gauss type algorithm
    double b1, b2, b4;
    b1 = a11 * a33 - sqr(a13);
    b2 = a12 * a33 - a13 * a23;
    b4 = a11 * a23 - a12 * a13;

    // eigenvector
    Vector3<double> u(b2, -b1, b4);

    return u.Unit();
}


std::vector<Vector3<double>> EventShapes::eigenvectors(const double T[3][3], const std::vector<double>& lam)
{
    std::vector<Vector3<double>> n;
    for (unsigned int i = 0; i < 3; ++i) {
        n.emplace_back(eigenvector(T, lam[i]));
    }
    return n;
}

void EventShapes::diagonalizeTensors(bool linear, bool cmboost)
{
    // initialize
    double Theta[3][3];
    for (auto & elem : Theta) {
        for (int j = 0; j < 3; ++j) {
            elem[j] = 0.0;
        }
    }
    double sum = 0.;
    Vector3<Momentum> sumvec;
    std::vector<double> lam;
    std::vector<Vector3<double>> n;
    // get cm-frame
    LorentzVector<Momentum> pcm = LorentzVector<Momentum>();
    Vector3<double> beta;
    if (cmboost) {
        for (auto & elem : _pv) {
            pcm += elem;
        }
        beta = pcm.BoostIntoRestFrame();
    }
    // get Theta_ij
    for (auto & elem : _pv) {
        LorentzVector<Momentum> dum(elem);
        if (cmboost) dum.Boost(beta);
        Vector3<Momentum> pvec = dum.Vect();
        double pvec_GeV[3] = {pvec.X() / GeV, pvec.Y() / GeV, pvec.Z() / GeV};
        if (pvec.Mag() > 0_GeV) {
            sumvec += pvec;
            if (linear) {
                sum += pvec.Mag() / GeV;
            } else {
                sum += pvec.Mag2() / GeV2;
            }
            for (int i = 0; i < 3; ++i) {
                for (int j = i; j < 3; ++j) {
                    if (linear) {
                        Theta[i][j] += (pvec_GeV[i]) * (pvec_GeV[j]) * GeV / (pvec.Mag());
                    } else {
                        Theta[i][j] += (pvec_GeV[i]) * (pvec_GeV[j]);
                    }
                }
            }
        }
    }
    for (auto & elem : Theta) {
        for (int j = 0; j < 3; ++j) {
            elem[j] /= sum;
        }
    }

    // diagonalize it
    lam = eigenvalues(Theta);
    n = eigenvectors(Theta, lam);

    if (linear) {
        _linTen = lam;
        _linTenAxis = n;
    } else {
        _spher = lam;
        _spherAxis = n;
    }
}

void EventShapes::calculateThrust()
{
    // explicitly calculate in units of GeV
    // algorithm based on Brandt/Dahmen Z Phys C1 (1978)
    // and 'tasso' code from HERWIG
    // assumes all momenta in cm system, no explicit boost performed here!
    // unlike for C and D

    _thrust.clear();
    _thrustAxis.clear();

    if (_pv.size() < 2) {
        for (int i = 0; i < 3; ++i) {
            _thrust.emplace_back(-1);
            _thrustAxis.emplace_back(Vector3<double>());
        }
        return;
    }

    // thrust
    std::vector<Vector3<Momentum>> p;
    Energy psum = 0._GeV;
    for (auto & elem : _pv) {
        p.emplace_back(elem.Vect());
        psum += p.back().Mag();
    }

    Vector3<double> axis;
    if (p.size() == 2) {
        _thrust.emplace_back(1.0);
        _thrust.emplace_back(0.0);
        _thrust.emplace_back(0.0);
        axis = p[0].Unit();
        if (axis.Z() < 0) axis = -axis;
        _thrustAxis.emplace_back(axis);
        _thrustAxis.emplace_back(axis.Orthogonal());
        axis = _thrustAxis[0].Cross(_thrustAxis[1]);
        return;
    }

    if (p.size() == 3) {
        if (p[0].Mag2() < p[1].Mag2()) std::swap(p[0], p[1]);
        if (p[0].Mag2() < p[2].Mag2()) std::swap(p[0], p[2]);
        if (p[1].Mag2() < p[2].Mag2()) std::swap(p[1], p[2]);
        // thrust
        axis = p[0].Unit();
        if (axis.Z() < 0) axis = -axis;
        _thrust.emplace_back(2.*p[0].Mag() / psum);
        _thrustAxis.emplace_back(axis);
        // major
        axis = (p[1] - (axis * p[1]) * axis).Unit();
        if (axis.X() < 0) axis = -axis;
        _thrust.emplace_back((abs(p[1]*axis) + abs(p[2]*axis)) / psum);
        _thrustAxis.emplace_back(axis);
        // minor
        _thrust.emplace_back(0.0);
        axis = _thrustAxis[0].Cross(_thrustAxis[1]);
        _thrustAxis.emplace_back(axis);
        return;
    }

    // ACHTUNG special case with >= 4 coplanar particles will still fail.
    // probably not too important...
    EnergySquare val;
    calcT(p, val, axis);
    _thrust.emplace_back(sqrt(val) / psum);
    if (axis.Z() < 0) axis = -axis;
    _thrustAxis.emplace_back(axis.Unit());

    //major
    Vector3<Momentum> par;
    for (unsigned int l = 0; l < _pv.size(); ++l) {
        par   = (p[l] * axis.Unit()) * axis.Unit();
        p[l]  = p[l] - par;
    }
    calcM(p, val, axis);
    _thrust.emplace_back(sqrt(val) / psum);
    if (axis.X() < 0) axis = -axis;
    _thrustAxis.emplace_back(axis.Unit());

    // minor
    if (_thrustAxis[0]*_thrustAxis[1] < 1e-10) {
        Energy eval = 0_GeV;
        axis = _thrustAxis[0].Cross(_thrustAxis[1]);
        _thrustAxis.emplace_back(axis);
        for (auto & elem : _pv)
            eval += abs(axis * elem.Vect());
        _thrust.emplace_back(eval / psum);
    } else {
        _thrust.emplace_back(-1.0);
        _thrustAxis.emplace_back(Vector3<double>());
    }
}

void EventShapes::calcT(const std::vector<Vector3<Momentum>>& p, EnergySquare& t, Vector3<double>& taxis)
{
    EnergySquare tval;
    t = 0_GeV * GeV;
    Vector3<EnergySquare> tv;
    Vector3<Momentum> ptot;
    std::vector<Vector3<Momentum>> cpm;
    for (unsigned int k = 1; k < p.size(); ++k) {
        for (unsigned int j = 0; j < k; ++j) {
            tv = p[j].Cross(p[k]);
            ptot = Vector3<Momentum>();
            for (unsigned int l = 0; l < p.size(); ++l) {
                if (l != j && l != k) {
                    if (p[l]*tv > 0_GeV * GeV * GeV) {
                        ptot += p[l];
                    } else {
                        ptot -= p[l];
                    }
                }
            }
            cpm.clear();
            cpm.emplace_back(ptot - p[j] - p[k]);
            cpm.emplace_back(ptot - p[j] + p[k]);
            cpm.emplace_back(ptot + p[j] - p[k]);
            cpm.emplace_back(ptot + p[j] + p[k]);
            for (auto & elem : cpm) {
                tval = elem.Mag2();
                if (tval > t) {
                    t = tval;
                    taxis = elem.Unit();
                }
            }
        }
    }
}

void EventShapes::calcM(const std::vector<Vector3<Momentum>>& p, EnergySquare& m, Vector3<double>& maxis)
{
    EnergySquare mval;
    m = 0_GeV * GeV;
    Vector3<Momentum> tv, ptot;
    std::vector<Vector3<Momentum>> cpm;
    for (unsigned int j = 0; j < p.size(); ++j) {
        tv = p[j];
        ptot = Vector3<Momentum>();
        for (unsigned int l = 0; l < p.size(); ++l) {
            if (l != j) {
                if (p[l]*tv > 0_GeV * GeV) {
                    ptot += p[l];
                } else {
                    ptot -= p[l];
                }
            }
        }
        cpm.clear();
        cpm.emplace_back(ptot - p[j]);
        cpm.emplace_back(ptot + p[j]);
        for (auto & elem : cpm) {
            mval = elem.Mag2();
            if (mval > m) {
                m = mval;
                maxis = elem.Unit();
            }
        }
    }
}

void EventShapes::bookEEC(std::vector<double>& hi)
{
    // hi is the histogram.  It is understood that hi.front() contains
    // the bin [-1 < std::cos(chi) < -1+delta] and hi.back() the bin [1-delta
    // < std::cos(chi) < 1].  Here, delta = 2/hi.size().
    Energy Evis(0_GeV);
    for (unsigned int bin = 0; bin < hi.size(); ++bin) {
        double delta = 2. / hi.size();
        double coschi = -1 + bin * delta;
        if (_pv.size() > 1) {
            for (unsigned int i = 0; i < _pv.size() - 1; ++i) {
                Evis += _pv[i].E();
                for (unsigned int j = i + 1; j < _pv.size(); ++j) {
                    double diff = std::abs(coschi - boost::units::cos(_pv[i].Vect().Angle(_pv[j].Vect())));
                    if (delta > diff) hi[bin] += _pv[i].E() * _pv[j].E() / GeV2;
                }
            }
        }
        hi[bin] /= (Evis * Evis) / GeV2;
    }
}

}
