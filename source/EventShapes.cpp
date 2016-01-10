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

#include <boost/math/constants/constants.hpp>
#include "EventShapes.hh"

namespace boca
{

void EventShapes::CalcHemisphereMasses() const
{
    LorentzVector<Momentum> pos, neg;
    Energy pden(0), epos(0), eneg(0);
    for (auto & elem : lorentz_vectors_) {
        if (elem.Vect() * ThrustAxis() > 0._GeV) {
            pos += elem;
// can be replaced with, once perp() is giving non-nan results
// for nearly parallel vectors.
// epos += lorentz_vectors_[ix].perp(ThrustAxis());
            epos += elem.Vect().Cross(ThrustAxis()).Mag();
        } else {
            neg += elem;
// see above
// eneg += lorentz_vectors_[ix].perp(ThrustAxis());
            eneg += elem.Vect().Cross(ThrustAxis()).Mag();
        }
        pden += elem.Vect().Mag();
    }
// denominator and masses
    EnergySquare den(sqr(pos.E() + neg.E()));
    m_plus_ = pos.M2() / den;
    m_minus_ = neg.M2() / den;
    if (m_plus_ < m_minus_) std::swap(m_plus_, m_minus_);
// jet broadening
    b_plus_ = 0.5 * epos / pden;
    b_minus_ = 0.5 * eneg / pden;
    if (b_plus_ < b_minus_) std::swap(b_plus_, b_minus_);
}

std::vector<double> EventShapes::Eigenvalues(const double T[3][3]) const
{

// b, c, d are the coefficients of the characteristic polynomial,
// a lambda^3 + b lambda^2 + c lambda + d
// where a is chosen to be +1.
    double t11, t12, t13, t22, t23, t33;
    t11 = T[0][0]; t12 = T[0][1]; t13 = T[0][2];
    t22 = T[1][1]; t23 = T[1][2]; t33 = T[2][2];
    double b = -(t11 + t22 + t33);
    double c = t11 * t22 + t11 * t33 + t22 * t33 - sqr(t12) - sqr(t13) - sqr(t23);
    double d = - t11 * t22 * t33 - 2.*t12 * t23 * t13 + t11 * sqr(t23) + t22 * sqr(t13) + t33 * sqr(t12);

// use Cardano's formula to compute the zeros
    double p = (3.*c - sqr(b)) / 3.;
    double q = (2.*sqr(b) * b - 9.*b * c + 27.*d) / 27.;
// check diskriminant to double precision
    std::vector<double> lambda;
    if (4.*p * sqr(p) + 27.*sqr(q) > 2.0e-16) {
        for (unsigned int i = 0; i < 3; ++i) lambda.emplace_back(-1.);
        std::cerr << "EventShapes::eigenvalues: found D = "
                  << 4.*p* sqr(p) + 27.*sqr(q)
                  << " > 0! No real Eigenvalues!\n";
    } else {
// get solutions
        double alpha = std::acos(-q / 2.*std::sqrt(-27. / (p * p * p))) / 3.;
        double w = std::sqrt(-4.*p / 3.);
        lambda.emplace_back(w * std::cos(alpha) - b / 3.);
        lambda.emplace_back(-w * std::cos(alpha + boost::math::constants::pi<double>() / 3.) - b / 3.);
        lambda.emplace_back(-w * std::cos(alpha - boost::math::constants::pi<double>() / 3.) - b / 3.);
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


Vector3<double> EventShapes::Eigenvector(const double T[3][3], const double& lam) const
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


std::vector<Vector3<double>> EventShapes::Eigenvectors(const double T[3][3], const std::vector<double>& lam) const
{
    std::vector<Vector3<double>> n;
    for (unsigned int i = 0; i < 3; ++i) {
        n.emplace_back(Eigenvector(T, lam[i]));
    }
    return n;
}

void EventShapes::DiagonalizeTensors(bool linear, bool cmboost) const
{
// initialize
    double Theta[3][3];
    for (auto & elem : Theta) for (int j = 0; j < 3; ++j) elem[j] = 0.0;
    double sum = 0.;
    Vector3<Momentum> sumvec;
    std::vector<double> lam;
    std::vector<Vector3<double>> n;
// get cm-frame
    LorentzVector<Momentum> pcm = LorentzVector<Momentum>();
    Vector3<double> beta;
    if (cmboost) {
        for (auto & elem : lorentz_vectors_) pcm += elem;
        beta = pcm.BoostIntoRestFrame();
    }
// get Theta_ij
    for (auto & elem : lorentz_vectors_) {
        LorentzVector<Momentum> dum(elem);
        if (cmboost) dum.Boost(beta);
        Vector3<Momentum> pvec = dum.Vect();
        double pvec_GeV[3] = {pvec.X() / GeV, pvec.Y() / GeV, pvec.Z() / GeV};
        if (pvec.Mag() > 0_GeV) {
            sumvec += pvec;
            if (linear) sum += pvec.Mag() / GeV;
            else sum += pvec.Mag2() / GeV2;
            for (int i = 0; i < 3; ++i) {
                for (int j = i; j < 3; ++j) {
                    if (linear) Theta[i][j] += (pvec_GeV[i]) * (pvec_GeV[j]) * GeV / (pvec.Mag());
                    else Theta[i][j] += (pvec_GeV[i]) * (pvec_GeV[j]);
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
    lam = Eigenvalues(Theta);
    n = Eigenvectors(Theta, lam);

    if (linear) {
        lin_ten_ = lam;
        lin_ten_axis_ = n;
    } else {
        spher_ = lam;
        spher_axis_ = n;
    }
}

void EventShapes::CalculateThrust() const
{
// explicitly calculate in units of GeV
// algorithm based on Brandt/Dahmen Z Phys C1 (1978)
// and 'tasso' code from HERWIG
// assumes all momenta in cm system, no explicit boost performed here!
// unlike for C and D

    thrust_.clear();
    thrust_axis_.clear();

    if (lorentz_vectors_.size() < 2) {
        for (int i = 0; i < 3; ++i) {
            thrust_.emplace_back(-1);
            thrust_axis_.emplace_back(Vector3<double>());
        }
        return;
    }

// thrust
    std::vector<Vector3<Momentum>> p;
    Energy psum = 0._GeV;
    for (auto & elem : lorentz_vectors_) {
        p.emplace_back(elem.Vect());
        psum += p.back().Mag();
    }

    Vector3<double> axis;
    if (p.size() == 2) {
        thrust_.emplace_back(1.0);
        thrust_.emplace_back(0.0);
        thrust_.emplace_back(0.0);
        axis = p[0].Unit();
        if (axis.Z() < 0) axis = -axis;
        thrust_axis_.emplace_back(axis);
        thrust_axis_.emplace_back(axis.Orthogonal());
        axis = thrust_axis_[0].Cross(thrust_axis_[1]);
        return;
    }

    if (p.size() == 3) {
        if (p[0].Mag2() < p[1].Mag2()) std::swap(p[0], p[1]);
        if (p[0].Mag2() < p[2].Mag2()) std::swap(p[0], p[2]);
        if (p[1].Mag2() < p[2].Mag2()) std::swap(p[1], p[2]);
// thrust
        axis = p[0].Unit();
        if (axis.Z() < 0) axis = -axis;
        thrust_.emplace_back(2.*p[0].Mag() / psum);
        thrust_axis_.emplace_back(axis);
// major
        axis = (p[1] - (axis * p[1]) * axis).Unit();
        if (axis.X() < 0) axis = -axis;
        thrust_.emplace_back((abs(p[1]*axis) + abs(p[2]*axis)) / psum);
        thrust_axis_.emplace_back(axis);
// minor
        thrust_.emplace_back(0.0);
        axis = thrust_axis_[0].Cross(thrust_axis_[1]);
        thrust_axis_.emplace_back(axis);
        return;
    }

// ACHTUNG special case with >= 4 coplanar particles will still fail.
// probably not too important...
    EnergySquare val;
    CalcT(p, val, axis);
    thrust_.emplace_back(sqrt(val) / psum);
    if (axis.Z() < 0) axis = -axis;
    thrust_axis_.emplace_back(axis.Unit());

//major
    Vector3<Momentum> par;
    for (unsigned int l = 0; l < lorentz_vectors_.size(); ++l) {
        par = (p[l] * axis.Unit()) * axis.Unit();
        p[l] = p[l] - par;
    }
    CalcM(p, val, axis);
    thrust_.emplace_back(sqrt(val) / psum);
    if (axis.X() < 0) axis = -axis;
    thrust_axis_.emplace_back(axis.Unit());

// minor
    if (thrust_axis_[0]*thrust_axis_[1] < 1e-10) {
        Energy eval = 0_GeV;
        axis = thrust_axis_[0].Cross(thrust_axis_[1]);
        thrust_axis_.emplace_back(axis);
        for (auto & elem : lorentz_vectors_)
            eval += abs(axis * elem.Vect());
        thrust_.emplace_back(eval / psum);
    } else {
        thrust_.emplace_back(-1.0);
        thrust_axis_.emplace_back(Vector3<double>());
    }
}

void EventShapes::CalcT(const std::vector<Vector3<Momentum>>& p, EnergySquare& t, Vector3<double>& taxis) const
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

void EventShapes::CalcM(const std::vector<Vector3<Momentum>>& p, EnergySquare& m, Vector3<double>& maxis) const
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

void EventShapes::BookEEC(std::vector<double>& hi) const
{
// hi is the histogram. It is understood that hi.front() contains
// the bin [-1 < std::cos(chi) < -1+delta] and hi.back() the bin [1-delta
// < std::cos(chi) < 1]. Here, delta = 2/hi.size().
    Energy Evis(0_GeV);
    for (unsigned int bin = 0; bin < hi.size(); ++bin) {
        double delta = 2. / hi.size();
        double coschi = -1 + bin * delta;
        if (lorentz_vectors_.size() > 1) {
            for (unsigned int i = 0; i < lorentz_vectors_.size() - 1; ++i) {
                Evis += lorentz_vectors_[i].E();
                for (unsigned int j = i + 1; j < lorentz_vectors_.size(); ++j) {
                    double diff = std::abs(coschi - boost::units::cos(lorentz_vectors_[i].Vect().Angle(lorentz_vectors_[j].Vect())));
                    if (delta > diff) hi[bin] += lorentz_vectors_[i].E() * lorentz_vectors_[j].E() / GeV2;
                }
            }
        }
        hi[bin] /= (Evis * Evis) / GeV2;
    }
}
EventShapes::EventShapes()
{
    Initialize();
}
EventShapes::EventShapes(const std::vector< Jet >& jets)
{
    Reset(jets);
}
void EventShapes::Reset(const std::vector< Jet >& jets)
{
    for (auto const & jet : jets) lorentz_vectors_.emplace_back(jet.Vector());
    Initialize();
}
void EventShapes::Initialize()
{
    thrust_done_ = false;
    spher_done_ = false;
    lin_ten_done_ = false;
    hem_done_ = false;
    use_cm_boost_ = false;
    m_plus_ = 0;
    m_minus_ = 0;
    b_plus_ = 0;
    b_minus_ = 0;
}
double EventShapes::Thrust() const
{
    CheckThrust();
    return thrust_[0];
}
double EventShapes::ThrustMajor() const
{
    CheckThrust();
    return thrust_[1];
}
double EventShapes::ThrustMinor() const
{
    CheckThrust();
    return thrust_[2];
}
double EventShapes::Oblateness() const
{
    CheckThrust();
    return thrust_[1] - thrust_[2];
}
Vector3< double > EventShapes::ThrustAxis() const
{
    CheckThrust();
    return thrust_axis_[0];
}
Vector3< double > EventShapes::MajorAxis() const
{
    CheckThrust();
    return thrust_axis_[1];
}
Vector3< double > EventShapes::MinorAxis() const
{
    CheckThrust();
    return thrust_axis_[2];
}
double EventShapes::CParameter() const
{
    CheckLinTen();
    return 3.*(lin_ten_[0] * lin_ten_[1] + lin_ten_[1] * lin_ten_[2]
               + lin_ten_[2] * lin_ten_[0]);
}
double EventShapes::DParameter() const
{
    CheckLinTen();
    return 27.*(lin_ten_[0] * lin_ten_[1] * lin_ten_[2]);
}
std::vector< double > EventShapes::LinTenEigenValues() const
{
    CheckLinTen();
    return lin_ten_;
}
std::vector< Vector3< double > > EventShapes::LinTenEigenVectors() const
{
    CheckLinTen();
    return lin_ten_axis_;
}
double EventShapes::Sphericity() const
{
    CheckSphericity();
    return 3. / 2.*(spher_[1] + spher_[2]);
}
double EventShapes::Aplanarity() const
{
    CheckSphericity();
    return 3. / 2.*spher_[2];
}
double EventShapes::Planarity() const
{
    CheckSphericity();
    return spher_[1] - spher_[2];
}
Vector3< double > EventShapes::SphericityAxis() const
{
    CheckSphericity();
    return spher_axis_[0];
}
std::vector< double > EventShapes::SphericityEigenValues() const
{
    CheckSphericity();
    return spher_;
}
std::vector< Vector3< double > > EventShapes::SphericityEigenVectors() const
{
    CheckSphericity();
    return spher_axis_;
}
double EventShapes::MHigh2() const
{
    CheckHemispheres();
    return m_plus_;
}
double EventShapes::MLow2() const
{
    CheckHemispheres();
    return m_minus_;
}
double EventShapes::MDiff2() const
{
    CheckHemispheres();
    return m_plus_ - m_minus_;
}
double EventShapes::BMax() const
{
    CheckHemispheres();
    return b_plus_;
}
double EventShapes::BMin() const
{
    CheckHemispheres();
    return b_minus_;
}
double EventShapes::BSum() const
{
    CheckHemispheres();
    return b_plus_ + b_minus_;
}
double EventShapes::BDiff() const
{
    CheckHemispheres();
    return b_plus_ - b_minus_;
}
double EventShapes::ScaledMomentum(LorentzVector<Momentum> const& p, const boca::Energy& Ebeam) const
{
    return ((Ebeam > 0_GeV && p.Vect().Mag() > 0_GeV) ? std::log(Ebeam / p.Vect().Mag()) : -1.);
}
Momentum EventShapes::Pt(const LorentzVector< Momentum >& p) const
{
    return p.Perp();
}
Angle EventShapes::Rapidity(LorentzVector<Momentum> const& p) const
{
    return (p.T() > p.Z() ? p.Rapidity() : 1e99_rad);
}
Momentum EventShapes::PtInT(LorentzVector<Momentum> const& p) const
{
    CheckThrust();
    return p.Vect() * thrust_axis_[1];
}
Momentum EventShapes::PtOutT(LorentzVector<Momentum> const& p) const
{
    CheckThrust();
    return p.Vect() * thrust_axis_[2];
}
Angle EventShapes::RapidityT(LorentzVector<Momentum> const& p) const
{
    CheckThrust();
    return (p.T() > p.Vect() * thrust_axis_[0] ? p.Rapidity(thrust_axis_[0]) : 1e99_rad);
}
Momentum EventShapes::PtInS(LorentzVector<Momentum> const& p) const
{
    CheckSphericity();
    return p.Vect() * spher_axis_[1];
}
Momentum EventShapes::PtOutS(LorentzVector<Momentum> const& p) const
{
    CheckSphericity();
    return p.Vect() * spher_axis_[2];
}
Angle EventShapes::RapidityS(LorentzVector<Momentum> const& p) const
{
    CheckSphericity();
    return (p.T() > p.Vect() * spher_axis_[0] ? p.Rapidity(spher_axis_[0]) : 1e99_rad);
}
void EventShapes::NormalizeEEC(std::vector< double >& hi, long int evts) const
{
    for (unsigned int bin = 0; bin < hi.size(); bin++) bin /= (hi.size() * evts);
}
double EventShapes::AEEC(std::vector< double >& hi, double& coschi) const
{
    if (coschi > 0. && coschi <= 1.) {
        int i = static_cast<int>(floor((-coschi + 1.) / 2.*hi.size()));
        int j = static_cast<int>(floor((coschi + 1.) / 2.*hi.size()));
        return hi[i] - hi[j];
    } else {
        return 1e99;
    }
}
void EventShapes::CheckThrust() const
{
    if (!thrust_done_) {
        thrust_done_ = true;
        CalculateThrust();
    }
}
void EventShapes::CheckLinTen() const
{
    if (!lin_ten_done_) {
        lin_ten_done_ = true;
        DiagonalizeTensors(true, use_cm_boost_);
    }
}
void EventShapes::CheckSphericity() const
{
    if (!spher_done_) {
        spher_done_ = true;
        DiagonalizeTensors(false, use_cm_boost_);
    }
}
void EventShapes::CheckHemispheres() const
{
    if (!hem_done_) {
        hem_done_ = true;
        CalcHemisphereMasses();
    }
}

}
