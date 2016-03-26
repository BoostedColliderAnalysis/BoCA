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

EventShapes::EventShapes() {}

EventShapes::EventShapes(std::vector<Jet> const& jets)
{
    INFO0;
    auto lorentz_vectors = Transform(SortedByPt(jets), [](Jet const & jet) {
        return jet.Vector();
    });
    if (use_cm_boost_) {
        Vector3<double> boost = boost::accumulate(lorentz_vectors, LorentzVector<Momentum>()).BoostIntoRestFrame();
        lorentz_vectors = Transform(lorentz_vectors, [&](LorentzVector<Momentum> const & lorentz_vector) -> LorentzVector<Momentum> {
            return lorentz_vector.Boosted(boost);
        });
    }
    lorentz_vectors_ = lorentz_vectors;
    vectors_ = Transform(lorentz_vectors, [](LorentzVector<Momentum> const & lorentz_vector) {
        return lorentz_vector.Vector();
    });
}

std::vector< Vector3< Momentum > > EventShapes::Vectors() const
{
    INFO0;
    return vectors_;
    return Transform(LorentzVectors(), [](LorentzVector<Momentum> const & lorentz_vector) {
        return lorentz_vector.Vector();
    });
}

std::vector< LorentzVector< Momentum > > EventShapes::LorentzVectors() const
{
    INFO(lorentz_vectors_.size());
    return lorentz_vectors_;
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
    return 27 * LinearTensors().at(0).Scalar() * LinearTensors().at(1).Scalar() * LinearTensors().at(2).Scalar();
}

std::vector<double> EventShapes::LinTenEigenValues() const
{
    INFO0;
    return Transform(LinearTensors(), [](EventShape<double> const & event_shape) {
        return event_shape.Scalar();
    });
}

std::vector<Vector3<double>> EventShapes::LinTenEigenVectors() const
{
    INFO0;
    return Transform(LinearTensors(), [](EventShape<double> const & event_shape) {
        return event_shape.Vector();
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
        return event_shape.Scalar();
    });
}
std::vector<Vector3<double>> EventShapes::SphericityEigenVectors() const
{
    INFO0;
    return Transform(SphericalTensors(), [](EventShape<double> const & event_shape) {
        return event_shape.Vector();
    });
}

double EventShapes::ScaledMomentum(LorentzVector<Momentum> const& lorentz_vector, Energy const& energy) const
{
    INFO0;
    return energy > 0_eV && lorentz_vector.Vector().Mag() > 0_eV ? std::log(energy / lorentz_vector.Vector().Mag()) : -1;
}

Momentum EventShapes::Pt(LorentzVector<Momentum> const& lorentz_vector) const
{
    INFO0;
    return lorentz_vector.Perp();
}

Angle EventShapes::Rapidity(LorentzVector<Momentum> const& lorentz_vector) const
{
    INFO0;
    return lorentz_vector.T() > lorentz_vector.Z() ? lorentz_vector.Rapidity() : 1e99_rad;
}

Momentum EventShapes::PtInT(LorentzVector<Momentum> const& lorentz_vector) const
{
    INFO0;
    return lorentz_vector.Vector() * Thrusts().at(1).Vector();
}

Momentum EventShapes::PtOutT(LorentzVector<Momentum> const& lorentz_vector) const
{
    INFO0;
    return lorentz_vector.Vector() * Thrusts().at(2).Vector();
}

Angle EventShapes::RapidityT(LorentzVector<Momentum> const& lorentz_vector) const
{
    INFO0;
    return (lorentz_vector.T() > lorentz_vector.Vector() * Thrusts().at(0).Vector() ? lorentz_vector.Rapidity(Thrusts().at(0).Vector()) : 1e99_rad);
}

Momentum EventShapes::PtInS(LorentzVector<Momentum> const& lorentz_vector) const
{
    INFO0;
    return lorentz_vector.Vector() * SphericalTensors().at(1).Vector();
}

Momentum EventShapes::PtOutS(LorentzVector<Momentum> const& lorentz_vector) const
{
    INFO0;
    return lorentz_vector.Vector() * SphericalTensors().at(2).Vector();
}

Angle EventShapes::RapidityS(LorentzVector<Momentum> const& lorentz_vector) const
{
    INFO0;
    return (lorentz_vector.T() > lorentz_vector.Vector() * SphericalTensors().at(0).Vector() ? lorentz_vector.Rapidity(SphericalTensors().at(0).Vector()) : 1e99_rad);
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

EventShapes::Vector<EventShape<double>> EventShapes::SphericalTensors() const
{
    INFO0;
    return spherical_tensors_.Get([this]() {
        return DiagonalizeSphericalTensors();
    });
}

HemisphereMasses EventShapes::HemisphereMasses() const
{
    INFO0;
    return hemishpere_masses_.Get([this]() {
        return GetHemisphereMasses();
    });
}

HemisphereMasses EventShapes::GetHemisphereMasses() const
{
    INFO0;
    LorentzVector<Momentum> positive;
    LorentzVector<Momentum> negative;
    Energy epos = 0_eV;
    Energy eneg = 0_eV;
    for (auto const & lorentz_vector : LorentzVectors()) {
        if (lorentz_vector.Vector() * ThrustAxis() > 0_eV) {
            positive += lorentz_vector;
            // can be replaced with, once perp() is giving non-nan results
            // for nearly parallel vectors.
            // epos += LorentzVectors()[ix].perp(ThrustAxis());
            epos += lorentz_vector.Vector().Cross(ThrustAxis()).Mag();
        } else {
            negative += lorentz_vector;
            // see above
            // eneg += LorentzVectors()[ix].perp(ThrustAxis());
            eneg += lorentz_vector.Vector().Cross(ThrustAxis()).Mag();
        }
    }
    boca::HemisphereMasses hemisphere_masses;
    // masses
    hemisphere_masses.SetMasses(Range<EnergySquare>(negative.M2(), positive.M2()) / sqr(positive.E() + negative.E()));
    // jet broadening
    hemisphere_masses.SetBroadenings(Range<Energy>(eneg, epos) / ScalarMomentum() / 2);
    return hemisphere_masses;
}

EventShapes::Vector<double> EventShapes::Eigenvalues(Matrix3<double> const& matrix) const
{
    INFO0;
    // b, c, d are the coefficients of the characteristic polynomial, a lambda^3 + b lambda^2 + c lambda + d  where a is chosen to be +1.
    double t11 = matrix[0][0];
    double t12 = matrix[0][1];
    double t13 = matrix[0][2];
    double t22 = matrix[1][1];
    double t23 = matrix[1][2];
    double t33 = matrix[2][2];
    double b = -(t11 + t22 + t33);
    double c = t11 * t22 + t11 * t33 + t22 * t33 - sqr(t12) - sqr(t13) - sqr(t23);
    double d = - t11 * t22 * t33 - 2. * t12 * t23 * t13 + t11 * sqr(t23) + t22 * sqr(t13) + t33 * sqr(t12);
    // use Cardano's formula to compute the zeros
    double p = (3. * c - sqr(b)) / 3.;
    double q = (2. * sqr(b) * b - 9. * b * c + 27. * d) / 27.;
    // check diskriminant to double precision
    Vector<double> eigenvalues;
    if (4 * p * sqr(p) + 27 * sqr(q) > 2.0e-16) {
        for (auto & eigenvalue : eigenvalues) eigenvalue = -1;
        std::cerr << "EventShapes::eigenvalues: found D = " << 4. * p* sqr(p) + 27. * sqr(q) << " > 0! No real Eigenvalues!\n";
        return eigenvalues;
    }
    // get solutions
    auto alpha = acos(-q / 2. * std::sqrt(-27. / (p * p * p))) / 3.;
    double w = std::sqrt(-4. * p / 3.);
    eigenvalues.at(0) = w * boost::units::cos(alpha) - b / 3.;
    eigenvalues.at(1) = -w * boost::units::cos(alpha + Pi() / 3.) - b / 3.;
    eigenvalues.at(2) = -w * boost::units::cos(alpha - Pi() / 3.) - b / 3.;
    // sort according to size of eigenvalues such that lambda[0] > lambda[1] > lambda[2]
    if (eigenvalues[0] < eigenvalues[1]) std::swap(eigenvalues[0], eigenvalues[1]);
    if (eigenvalues[0] < eigenvalues[2]) std::swap(eigenvalues[0], eigenvalues[2]);
    if (eigenvalues[1] < eigenvalues[2]) std::swap(eigenvalues[1], eigenvalues[2]);
    return eigenvalues;
}

Vector3<double> EventShapes::Eigenvector(Matrix3<double> const& matrix, const double& eigenvalue) const
{
    INFO0;
    // set up matrix of system to be solved
    double a11 = matrix[0][0] - eigenvalue;
    double a12 = matrix[0][1];
    double a13 = matrix[0][2];
    double a23 = matrix[1][2];
    double a33 = matrix[2][2] - eigenvalue;
    // intermediate steps from gauss type algorithm
    double b1 = a11 * a33 - sqr(a13);
    double b2 = a12 * a33 - a13 * a23;
    double b4 = a11 * a23 - a12 * a13;
    // eigenvector
    Vector3<double> eigenvector(b2, -b1, b4);
    return eigenvector.Unit();
}

EventShapes::Vector<Vector3<double>> EventShapes::Eigenvectors(Matrix3<double> const& matrix, Vector<double> const& eigenvalues) const
{
    INFO(eigenvalues.size());
    Vector<Vector3<double>> eigenvectors;
    for (auto & eigenvector : eigenvectors) eigenvector = Eigenvector(matrix, eigenvalues.at(Position(eigenvectors, eigenvector)));
    return eigenvectors;
}

EventShapes::Vector<EventShape<double>> EventShapes::EigenSystem(Matrix3<double> const& matrix) const
{
    INFO0;
    Vector<double> eigenvalues = Eigenvalues(matrix);
    Vector<Vector3<double>> eigenvectors = Eigenvectors(matrix, eigenvalues);
    Vector<EventShape<double>> eigensystem;
    for (auto const & eigenvalue : eigenvalues) {
        auto index = Position(eigenvalues, eigenvalue);
        eigensystem.at(index) = EventShape<double>(eigenvectors.at(index), eigenvalue);
    }
    return eigensystem;
}

EventShapes::Vector<EventShape<double>> EventShapes::DiagonalizeLinearTensors() const
{
    INFO0;
    Matrix3<Momentum> matrix;
    Momentum sum;
    for (auto vector : Vectors()) {
        if (vector.Mag2() <= 0_eV * eV) continue;
        sum += vector.Mag();
        matrix += MatrixProduct(vector, vector) / vector.Mag();
    }
    return EigenSystem(matrix / sum);

}

EventShapes::Vector<EventShape<double>> EventShapes::DiagonalizeSphericalTensors() const
{
    INFO0;
    Matrix3<MomentumSquare> matrix;
    MomentumSquare sum;
    for (auto vector : Vectors()) {
        if (vector.Mag2() <= 0_eV * eV) continue;
        sum += vector.Mag2();
        matrix += MatrixProduct(vector, vector);
    }
    return EigenSystem(matrix / sum);

}

EventShapes::Vector< EventShape< double >> EventShapes::GetThrusts() const
{
    INFO0;
    // explicitly calculate in units of GeV
    // algorithm based on Brandt/Dahmen Z Phys C1 (1978)
    // and 'tasso' code from HERWIG
    // assumes all momenta in cm system, no explicit boost performed here!
    // unlike for C and D
    switch (Vectors().size()) {
    case 0 : ;
    case 1 : return GetThrusts1();
    case 2 : return GetThrusts2();
    case 3 : return GetThrusts3();
    default : return GetThrusts4();
    }
}

EventShapes::Vector< EventShape< double >> EventShapes::GetThrusts1() const
{
    INFO0;
    Vector<EventShape<double>> thrusts;
    for (auto & thrust : thrusts) thrust.Set(-1);
    return thrusts;
}

namespace
{
Vector3<double> Mirror(Vector3<double> const& axis, Dimension3 dimension)
{
    return axis[dimension] < 0 ? -axis : axis;
}
}

EventShapes::Vector< EventShape< double >> EventShapes::GetThrusts2() const
{
    INFO0;
    Vector<EventShape<double>> thrusts;
    auto thrust = Mirror(Vectors().at(0).Unit(), Dimension3::z);
    thrusts.at(0).Set(thrust, 1);
    thrusts.at(1).Set(thrust.Orthogonal(), 0);
    thrusts.at(2).Set(thrusts.at(0).Vector().Cross(thrusts.at(1).Vector()), 0);
    return thrusts;
}

EventShapes::Vector< EventShape< double >> EventShapes::GetThrusts3() const
{
    INFO0;
    auto vectors = Vectors();
    if (vectors.at(0).Mag2() < vectors.at(1).Mag2()) std::swap(vectors.at(0), vectors.at(1));
    if (vectors.at(0).Mag2() < vectors.at(2).Mag2()) std::swap(vectors.at(0), vectors.at(2));
    if (vectors.at(1).Mag2() < vectors.at(2).Mag2()) std::swap(vectors.at(1), vectors.at(2));
    // thrust
    Vector<EventShape<double>> thrusts;
    auto scalar_momentum = ScalarMomentum();
    thrusts.at(0).Set(Mirror(vectors.at(0).Unit(), Dimension3::z), 2. * vectors.at(0).Mag() / scalar_momentum);
    // major
    auto major = Mirror((vectors.at(1) - (thrusts.at(0).Vector() * vectors.at(1)) * thrusts.at(0).Vector()).Unit(), Dimension3::x);
    thrusts.at(1).Set(major, (abs(vectors.at(1) * major) + abs(vectors.at(2) * major)) / scalar_momentum);
    // minor
    thrusts.at(2).Set(thrusts.at(0).Vector().Cross(thrusts.at(1).Vector()), 0);
    return thrusts;
}

EventShapes::Vector< EventShape< double >> EventShapes::GetThrusts4() const
{
    INFO0;
    // TODO special case with >= 4 coplanar particles will still fail. probably not too important...
    auto vectors = Vectors();
    auto thrust = Thrust(vectors);
    auto scalar_momentum = ScalarMomentum();
    Vector<EventShape<double>> thrusts;
    thrusts.at(0).Set(Mirror(thrust.Vector().Unit(), Dimension3::z), thrust.Scalar() / scalar_momentum);
    //major
    auto mod_vectors = Transform(vectors, [&](Vector3<Momentum> const & vector) {
        return vector - (vector * thrusts.at(0).Vector()) * thrusts.at(0).Vector();
    });
    auto major = Major(mod_vectors);
    thrusts.at(1).Set(Mirror(major.Vector().Unit(), Dimension3::x), major.Scalar() / scalar_momentum);

    // minor
    if (thrusts.at(0).Vector() * thrusts.at(1).Vector() < 1e-10) {
        auto minor = thrusts.at(0).Vector().Cross(thrusts.at(1).Vector());
        auto eval = boost::accumulate(vectors, 0_eV, [&](Energy & sum, Vector3<Momentum> const & vector) {
            return sum + abs(minor * vector);
        });
        thrusts.at(2).Set(minor, eval / scalar_momentum);
    } else thrusts.at(2).Set(Vector3<double>(), -1);
    return thrusts;
}

EventShape<Momentum> EventShapes::Thrust(std::vector<Vector3<Momentum>> const& vectors) const
{
    INFO0;
    EventShape<Momentum> thrust;
    for (unsigned first = 1; first < vectors.size(); ++first) {
        for (unsigned second = 0; second < first; ++second) {
            auto cross = vectors.at(second).Cross(vectors.at(first));
            Vector3<Momentum> total_vector;
            for (unsigned third = 0; third < vectors.size(); ++third) if (third != second && third != first) total_vector += (vectors[third] * cross > 0_eV * eV * eV) ? vectors[third] : -vectors[third];
            std::vector<Vector3<Momentum>> candidates;
            candidates.emplace_back(total_vector - vectors.at(second) - vectors.at(first));
            candidates.emplace_back(total_vector - vectors.at(second) + vectors.at(first));
            candidates.emplace_back(total_vector + vectors.at(second) - vectors.at(first));
            candidates.emplace_back(total_vector + vectors.at(second) + vectors.at(first));
            for (auto & candidate : candidates) if (candidate.Mag2() > sqr(thrust.Scalar())) thrust.Set(candidate, candidate.Mag());
        }
    }
    return thrust;
}

EventShape<Momentum> EventShapes::Major(std::vector<Vector3<Momentum>> const& vectors) const
{
    INFO0;
    EventShape<Momentum> major;
    for (unsigned first = 0; first < vectors.size(); ++first) {
        Vector3<Momentum> total_momentum;
        for (unsigned second = 0; second < vectors.size(); ++second) if (second != first) total_momentum += (vectors[second] * vectors[first] > 0_eV * eV) ? vectors[second] : -vectors[second];
        std::vector<Vector3<Momentum>> cpm;
        cpm.emplace_back(total_momentum - vectors[first]);
        cpm.emplace_back(total_momentum + vectors[first]);
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
    auto total_energy = boost::accumulate(LorentzVectors(), 0_eV, [](Energy & sum, LorentzVector<Momentum> const & lorentz_vector) {
        return sum + lorentz_vector.E();
    });
    for (auto & bin : hi) {
        double delta = 2. / hi.size();
        double coschi = -1 + Position(hi, bin) * delta;
        if (Vectors().size() < 2) continue;
        for (unsigned i = 0; i < Vectors().size() - 1; ++i) {
            for (unsigned j = i + 1; j < Vectors().size(); ++j) {
                double diff = std::abs(coschi - boost::units::cos(Vectors()[i].Angle(Vectors()[j])));
                if (delta > diff) bin += LorentzVectors()[i].E() * LorentzVectors()[j].E() / GeV2;
            }
        }

        hi[bin] /= (total_energy * total_energy) / GeV2;
    }
}

Momentum EventShapes::ScalarMomentum() const
{
    return boost::accumulate(Vectors(), 0_eV, [](Momentum & sum, Vector3<Momentum> const & vector) {
        return sum + vector.Mag();
    });
}

}
