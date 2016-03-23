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
#include <boost/range/numeric.hpp>
#include "EventShapes.hh"
#include "Vector.hh"
// #define INFORMATION
#include "DEBUG.hh"
#include "Sort.hh"

namespace boca
{

EventShapes::EventShapes()
{
    INFO0;
}

EventShapes::EventShapes(const std::vector< Jet >& jets)
{
    INFO0;
    Reset(jets);
}

void EventShapes::Reset(const std::vector< Jet >& jets)
{
    INFO0;
    lorentz_vectors_ = Transform(SortedByPt(jets), [](Jet const & jet) {
        return jet.Vector();
    });
}

double EventShapes::Thrust() const
{
    INFO0;
    return Thrusts().at(0).Scalar();
}

double EventShapes::ThrustMajor() const
{
    INFO0;
    return Thrusts().at(1).Scalar();
}

double EventShapes::ThrustMinor() const
{
    INFO0;
    return Thrusts().at(2).Scalar();
}

double EventShapes::Oblateness() const
{
    INFO0;
    return Thrusts().at(1).Scalar() - Thrusts().at(2).Scalar();
}

Vector3< double > EventShapes::ThrustAxis() const
{
    INFO0;
    return Thrusts().at(0).Vector();
}

Vector3< double > EventShapes::MajorAxis() const
{
    INFO0;
    return Thrusts().at(1).Vector();
}

Vector3< double > EventShapes::MinorAxis() const
{
    INFO0;
    return Thrusts().at(2).Vector();
}

double EventShapes::CParameter() const
{
    INFO0;
    return 3 * (LinearTensors().at(0).Scalar() * LinearTensors().at(1).Scalar() + LinearTensors().at(1).Scalar() * LinearTensors().at(2).Scalar() + LinearTensors().at(2).Scalar() * LinearTensors().at(0).Scalar());
}

double EventShapes::DParameter() const
{
    INFO0;
    return 27 * (LinearTensors().at(0).Scalar() * LinearTensors().at(1).Scalar() * LinearTensors().at(2).Scalar());
}

std::vector<double> EventShapes::LinTenEigenValues() const
{
    INFO0;
    return Transform(LinearTensors(), [](EventShape<double> const & event_shape) {
        return  event_shape.Scalar();
    });
}

std::vector<Vector3<double>> EventShapes::LinTenEigenVectors() const
{
    INFO0;
    return Transform(LinearTensors(), [](EventShape<double> const & event_shape) {
        return  event_shape.Vector();
    });
}

double EventShapes::Sphericity() const
{
    INFO0;
    return 3. / 2 * (SphericalTensors().at(1).Scalar() + SphericalTensors().at(2).Scalar());
}

double EventShapes::Aplanarity() const
{
    INFO0;
    return 3. / 2 * SphericalTensors().at(2).Scalar();
}

double EventShapes::Planarity() const
{
    INFO0;
    return SphericalTensors().at(1).Scalar() - SphericalTensors().at(2).Scalar();
}

Vector3< double > EventShapes::SphericityAxis() const
{
    INFO0;
    return SphericalTensors().at(0).Vector();
}

std::vector<double> EventShapes::SphericityEigenValues() const
{
    INFO0;
    return Transform(SphericalTensors(), [](EventShape<double> const & event_shape) {
        return  event_shape.Scalar();
    });
}
std::vector<Vector3<double>> EventShapes::SphericityEigenVectors() const
{
    INFO0;
    return Transform(SphericalTensors(), [](EventShape<double> const & event_shape) {
        return  event_shape.Vector();
    });
}

double EventShapes::MHigh2() const
{
    INFO0;
    return HemispheresMasses().MHigh2();
}

double EventShapes::MLow2() const
{
    INFO0;
    return HemispheresMasses().MLow2();
}

double EventShapes::MDiff2() const
{
    INFO0;
    return HemispheresMasses().MDiff2();
}

double EventShapes::BMax() const
{
    INFO0;
    return HemispheresMasses().BMax();
}

double EventShapes::BMin() const
{
    INFO0;
    return HemispheresMasses().BMin();
}

double EventShapes::BSum() const
{
    INFO0;
    return HemispheresMasses().BSum();
}

double EventShapes::BDiff() const
{
    INFO0;
    return HemispheresMasses().BDiff();
}

double EventShapes::ScaledMomentum(LorentzVector<Momentum> const& lorentz_vector, const boca::Energy& energy) const
{
    INFO0;
    return ((energy > 0_eV && lorentz_vector.Vect().Mag() > 0_eV) ? std::log(energy / lorentz_vector.Vect().Mag()) : -1.);
}

Momentum EventShapes::Pt(const LorentzVector< Momentum >& p) const
{
    INFO0;
    return p.Perp();
}

Angle EventShapes::Rapidity(LorentzVector<Momentum> const& p) const
{
    INFO0;
    return (p.T() > p.Z() ? p.Rapidity() : 1e99_rad);
}

Momentum EventShapes::PtInT(LorentzVector<Momentum> const& p) const
{
    INFO0;
    return p.Vect() * Thrusts().at(1).Vector();
}

Momentum EventShapes::PtOutT(LorentzVector<Momentum> const& p) const
{
    INFO0;
    return p.Vect() * Thrusts().at(2).Vector();
}

Angle EventShapes::RapidityT(LorentzVector<Momentum> const& p) const
{
    INFO0;
    return (p.T() > p.Vect() * Thrusts().at(0).Vector() ? p.Rapidity(Thrusts().at(0).Vector()) : 1e99_rad);
}

Momentum EventShapes::PtInS(LorentzVector<Momentum> const& p) const
{
    INFO0;
    return p.Vect() * SphericalTensors().at(1).Vector();
}

Momentum EventShapes::PtOutS(LorentzVector<Momentum> const& p) const
{
    INFO0;
    return p.Vect() * SphericalTensors().at(2).Vector();
}

Angle EventShapes::RapidityS(LorentzVector<Momentum> const& p) const
{
    INFO0;
    return (p.T() > p.Vect() * SphericalTensors().at(0).Vector() ? p.Rapidity(SphericalTensors().at(0).Vector()) : 1e99_rad);
}

void EventShapes::NormalizeEEC(std::vector<double>& hi, long int evts) const
{
    INFO0;
    for (auto & bin : hi) bin /= (hi.size() * evts);
}

double EventShapes::AEEC(std::vector<double>& hi, double& coschi) const
{
    INFO0;
    if (coschi > 0. && coschi <= 1.) {
        int i = static_cast<int>(floor((-coschi + 1.) / 2 * hi.size()));
        int j = static_cast<int>(floor((coschi + 1.) / 2 * hi.size()));
        return hi[i] - hi[j];
    } else return 1e99;
}

EventShapes::Vector<EventShape<double>> EventShapes::Thrusts() const
{
    INFO0;
    return thrusts_.Get([this]() {
        return GetThrusts();
    });
}

EventShapes::Vector<EventShape<double>> EventShapes::LinearTensors() const
{
    INFO0;
    return linear_tensors_.Get([this]() {
        return DiagonalizeLinearTensors();
    });
}

EventShapes::Vector<EventShape< double > > EventShapes::DiagonalizeLinearTensors() const
{
    return DiagonalizeTensors(true);
}

EventShapes::Vector<EventShape<double>> EventShapes::SphericalTensors() const
{
    INFO0;
    return spherical_tensors_.Get([this]() {
        return DiagonalizeSphericalTensors();
    });
}

EventShapes::Vector<EventShape< double > > EventShapes::DiagonalizeSphericalTensors() const
{
    return DiagonalizeTensors(false);
}

HemisphereMasses EventShapes::HemispheresMasses() const
{
    INFO0;
    return hemishpere_masses_.Get([this]() {
        return GetHemisphereMasses();
    });
}

HemisphereMasses EventShapes::GetHemisphereMasses() const
{
    INFO0;
    LorentzVector<Momentum> pos;
    LorentzVector<Momentum> neg;
    Energy pden(0);
    Energy epos(0);
    Energy eneg(0);
    for (auto const & lorentz_vector : lorentz_vectors_) {
        if (lorentz_vector.Vect() * ThrustAxis() > 0_eV) {
            pos += lorentz_vector;
            // can be replaced with, once perp() is giving non-nan results
            // for nearly parallel vectors.
            // epos += lorentz_vectors_[ix].perp(ThrustAxis());
            epos += lorentz_vector.Vect().Cross(ThrustAxis()).Mag();
        } else {
            neg += lorentz_vector;
            // see above
            // eneg += lorentz_vectors_[ix].perp(ThrustAxis());
            eneg += lorentz_vector.Vect().Cross(ThrustAxis()).Mag();
        }
        pden += lorentz_vector.Vect().Mag();
    }
    // denominator and masses
    EnergySquare den = sqr(pos.E() + neg.E());
    HemisphereMasses hemisphere_masses;
    hemisphere_masses.SetM(neg.M2() / den, pos.M2() / den);
    // jet broadening
    hemisphere_masses.SetB(0.5 * eneg / pden, 0.5 * epos / pden);
    return hemisphere_masses;
}

EventShapes::Vector<double> EventShapes::Eigenvalues(Matrix const& T) const
{
    INFO0;

    // b, c, d are the coefficients of the characteristic polynomial,
    // a lambda^3 + b lambda^2 + c lambda + d
    // where a is chosen to be +1.
    double t11 = T[0][0];
    double t12 = T[0][1];
    double t13 = T[0][2];
    double t22 = T[1][1];
    double t23 = T[1][2];
    double t33 = T[2][2];
    double b = -(t11 + t22 + t33);
    double c = t11 * t22 + t11 * t33 + t22 * t33 - sqr(t12) - sqr(t13) - sqr(t23);
    double d = - t11 * t22 * t33 - 2 * t12 * t23 * t13 + t11 * sqr(t23) + t22 * sqr(t13) + t33 * sqr(t12);

    // use Cardano's formula to compute the zeros
    double p = (3 * c - sqr(b)) / 3.;
    double q = (2 * sqr(b) * b - 9 * b * c + 27 * d) / 27.;
    // check diskriminant to double precision
    Vector<double> eigenvalues;
    if (4 * p * sqr(p) + 27 * sqr(q) > 2.0e-16) {
        for (auto & eigenvalue : eigenvalues) eigenvalue = -1;
        std::cerr << "EventShapes::eigenvalues: found D = " << 4 * p* sqr(p) + 27 * sqr(q) << " > 0! No real Eigenvalues!\n";
    } else {
        // get solutions
        double alpha = std::acos(-q / 2 * std::sqrt(-27. / (p * p * p))) / 3.;
        double w = std::sqrt(-4 * p / 3.);
        eigenvalues.at(0) = w * std::cos(alpha) - b / 3;
        eigenvalues.at(1) = -w * std::cos(alpha + boost::math::constants::pi<double>() / 3.) - b / 3;
        eigenvalues.at(2) = -w * std::cos(alpha - boost::math::constants::pi<double>() / 3.) - b / 3;
    }

    // sort according to size of eigenvalues
    // such that lambda[0] > lambda[1] > lambda[2]
    if (eigenvalues[0] < eigenvalues[1]) std::swap(eigenvalues[0], eigenvalues[1]);
    if (eigenvalues[0] < eigenvalues[2]) std::swap(eigenvalues[0], eigenvalues[2]);
    if (eigenvalues[1] < eigenvalues[2]) std::swap(eigenvalues[1], eigenvalues[2]);
    return eigenvalues;
}

Vector3<double> EventShapes::Eigenvector(Matrix const& T, const double& lam) const
{
    INFO0;
    // set up matrix of system to be solved
    double a11 = T[0][0] - lam;
    double a12 = T[0][1];
    double a13 = T[0][2];
    double a23 = T[1][2];
    double a33 = T[2][2] - lam;

    // intermediate steps from gauss type algorithm
    double b1 = a11 * a33 - sqr(a13);
    double b2 = a12 * a33 - a13 * a23;
    double b4 = a11 * a23 - a12 * a13;

    // eigenvector
    Vector3<double> eigenvector(b2, -b1, b4);
    return eigenvector.Unit();
}

EventShapes::Vector<Vector3<double>> EventShapes::Eigenvectors(Matrix const& matrix, const Vector<double>& eigenvalues) const
{
    INFO(eigenvalues.size());
    Vector<Vector3<double>> eigenvectors;
    for (auto & eigenvector : eigenvectors) eigenvector = Eigenvector(matrix, eigenvalues.at(Position(eigenvectors, eigenvector)));
    return eigenvectors;
}

EventShapes::Vector<EventShape<double>> EventShapes::EigenSystem(Matrix const& matrix) const
{
    INFO0;
    Vector<double> eigenvalues = Eigenvalues(matrix);
    Vector<Vector3<double>> eigenvectors = Eigenvectors(matrix, eigenvalues);
    Vector<EventShape<double>> eigensystem;
    for (auto const & eigenvalue : eigenvalues) eigensystem.at(Position(eigenvalues, eigenvalue)) = EventShape<double>(eigenvectors.at(Position(eigenvalues, eigenvalue)), eigenvalue);
    return eigensystem;
}

EventShapes::Vector<EventShape<double>> EventShapes::DiagonalizeTensors(bool linear) const
{
    INFO0;
    // initialize
//     Matrix theta(boost::extents[3][3]);
    Matrix matrix;
    for (auto & vector : matrix) for (auto & scalar : vector) scalar = 0;

    // get cm-frame
    Vector3<double> beta = use_cm_boost_ ? beta = boost::accumulate(lorentz_vectors_, LorentzVector<Momentum>()).BoostIntoRestFrame() : Vector3<double>();
    // get theta_ij
    EventShape<Momentum> sum;
    for (auto lorentz_vector : lorentz_vectors_) {
        if (use_cm_boost_) lorentz_vector.Boost(beta);
        Vector3<Momentum> pvec = lorentz_vector.Vect();
        Vector<double> array = {pvec.X() / GeV, pvec.Y() / GeV, pvec.Z() / GeV};
        if (pvec.Mag() > 0_eV) {
            sum += EventShape<Momentum>(pvec, (linear ?  pvec.Mag() : pvec.Mag2() / GeV));
            for (int i = 0; i < 3; ++i) for (int j = i; j < 3; ++j) matrix[i][j] += array[i] * array[j] * (linear ? double(GeV / pvec.Mag()) : 1.);
        }
    }
    for (auto & vector : matrix) for (auto & scalar : vector) scalar /= double(sum.Scalar() / GeV);

    // diagonalize it
    return EigenSystem(matrix);
}

EventShapes::Vector< EventShape< double >> EventShapes::GetThrusts() const
{
    INFO0;
    // explicitly calculate in units of GeV
    // algorithm based on Brandt/Dahmen Z Phys C1 (1978)
    // and 'tasso' code from HERWIG
    // assumes all momenta in cm system, no explicit boost performed here!
    // unlike for C and D

    // thrust
    auto vectors = Transform(lorentz_vectors_, [](LorentzVector<Momentum> const & lorentz_vector) {
        return lorentz_vector.Vect();
    });
    auto total_momentum = boost::accumulate(vectors, 0_eV, [](Momentum & sum, Vector3<Momentum> const & vector) {
        return sum + vector.Mag();
    });
    Vector<EventShape<double>> thrusts;
    switch (vectors.size()) {
    case 0 : ;
    case 1 : for (auto & thrust : thrusts) thrust.Set(-1);
        return thrusts;
    case 2 : {
        auto axis = vectors.at(0).Unit();
        if (axis.Z() < 0) axis = -axis;
        thrusts.at(0).Set(axis, 1);
        thrusts.at(1).Set(axis.Orthogonal(), 0);
        thrusts.at(2).Set(thrusts.at(0).Vector().Cross(thrusts.at(1).Vector()), 0);
        return thrusts;
    }
    case 3 : {
        if (vectors.at(0).Mag2() < vectors.at(1).Mag2()) std::swap(vectors.at(0), vectors.at(1));
        if (vectors.at(0).Mag2() < vectors.at(2).Mag2()) std::swap(vectors.at(0), vectors.at(2));
        if (vectors.at(1).Mag2() < vectors.at(2).Mag2()) std::swap(vectors.at(1), vectors.at(2));
        // thrust
        auto axis = vectors.at(0).Unit();
        if (axis.Z() < 0) axis = -axis;
        thrusts.at(0).Set(axis, 2. * vectors.at(0).Mag() / total_momentum);
        // major
        axis = (vectors.at(1) - (axis * vectors.at(1)) * axis).Unit();
        if (axis.X() < 0) axis = -axis;
        thrusts.at(1).Set(axis, (abs(vectors.at(1) * axis) + abs(vectors.at(2) * axis)) / total_momentum);
        // minor
        thrusts.at(2).Set(thrusts.at(0).Vector().Cross(thrusts.at(1).Vector()), 0);
        return thrusts;
    }
    default : // TODO special case with >= 4 coplanar particles will still fail. probably not too important...
        auto thrust = CalcT(vectors);
        auto axis = thrust.Vector().Unit();
        if (axis.Z() < 0) axis = -axis;
        thrusts.at(0).Set(axis, thrust.Scalar() / total_momentum);

        //major
        std::vector<Vector3<Momentum>> mod_vectors = Transform(vectors, [&](Vector3<Momentum> const & vector) {
            return vector - (vector * axis) * axis;
        });
        auto major = CalcM(mod_vectors);
        axis = major.Vector().Unit();
        if (axis.X() < 0) axis = -axis;
        thrusts.at(1).Set(axis, major.Scalar() / total_momentum);

        // minor
        if (thrusts.at(0).Vector() * thrusts.at(1).Vector() < 1e-10) {
            axis = thrusts.at(0).Vector().Cross(thrusts.at(1).Vector());
            auto eval = boost::accumulate(vectors, 0_eV, [&](Energy & sum, Vector3<Momentum> const & vector) {
                return sum + abs(axis * vector);
            });
            thrusts.at(2).Set(axis, eval / total_momentum);
        } else thrusts.at(2).Set(Vector3<double>(), -1);
        return thrusts;
    }
}

EventShape<Momentum> EventShapes::CalcT(const std::vector<Vector3<Momentum>>& vectors) const
{
    INFO0;
    EventShape<Momentum> thrust;
    for (unsigned first = 1; first < vectors.size(); ++first) {
        for (unsigned second = 0; second < first; ++second) {
            auto tv = vectors.at(second).Cross(vectors.at(first));
            Vector3<Momentum> ptot;
            for (unsigned third = 0; third < vectors.size(); ++third) if (third != second && third != first) {
                    if (vectors[third] * tv > 0_eV * eV * eV)  ptot += vectors[third];
                    else ptot -= vectors[third];
                }
            std::vector<Vector3<Momentum>> cpm;
            cpm.emplace_back(ptot - vectors.at(second) - vectors.at(first));
            cpm.emplace_back(ptot - vectors.at(second) + vectors.at(first));
            cpm.emplace_back(ptot + vectors.at(second) - vectors.at(first));
            cpm.emplace_back(ptot + vectors.at(second) + vectors.at(first));
            for (auto & elem : cpm) if (elem.Mag2() > sqr(thrust.Scalar())) thrust.Set(elem, elem.Mag());
        }
    }
    return thrust;
}

EventShape<Momentum> EventShapes::CalcM(const std::vector<Vector3<Momentum>>& vectors) const
{
    INFO0;
    EventShape<Momentum> major;
    for (unsigned first = 0; first < vectors.size(); ++first) {
        auto tv = vectors[first];
        Vector3<Momentum> ptot;
        for (unsigned second = 0; second < vectors.size(); ++second) {
            if (second != first) {
                if (vectors[second]*tv > 0_eV * eV) ptot += vectors[second];
                else ptot -= vectors[second];
            }
        }
        std::vector<Vector3<Momentum>> cpm;
        cpm.emplace_back(ptot - vectors[first]);
        cpm.emplace_back(ptot + vectors[first]);
        for (auto & elem : cpm) if (elem.Mag2() > sqr(major.Scalar())) major.Set(elem, elem.Mag());
    }
    return major;
}

void EventShapes::BookEEC(std::vector<double>& hi) const
{
    INFO0;
    // hi is the histogram. It is understood that hi.front() contains
    // the bin [-1 < std::cos(chi) < -1+delta] and hi.back() the bin [1-delta
    // < std::cos(chi) < 1]. Here, delta = 2/hi.size().
    Energy Evis(0_eV);
    for (unsigned bin = 0; bin < hi.size(); ++bin) {
        double delta = 2. / hi.size();
        double coschi = -1 + bin * delta;
        if (lorentz_vectors_.size() > 1) {
            for (unsigned i = 0; i < lorentz_vectors_.size() - 1; ++i) {
                Evis += lorentz_vectors_[i].E();
                for (unsigned j = i + 1; j < lorentz_vectors_.size(); ++j) {
                    double diff = std::abs(coschi - boost::units::cos(lorentz_vectors_[i].Vect().Angle(lorentz_vectors_[j].Vect())));
                    if (delta > diff) hi[bin] += lorentz_vectors_[i].E() * lorentz_vectors_[j].E() / GeV2;
                }
            }
        }
        hi[bin] /= (Evis * Evis) / GeV2;
    }
}

}
