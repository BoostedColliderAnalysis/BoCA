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

#include <boost/range/numeric.hpp>

#include "boca/generic/Vector.hh"
#include "boca/generic/Exception.hh"
#include "boca/math/GradedMatrix3.hh"
#include "boca/math/GradedLorentzVector.hh"
#include "boca/multiplets/Sort.hh"
#include "boca/EventShapes.hh"

// #define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

EventShapes::EventShapes() {}

namespace
{

std::vector<LorentzVector<Momentum>> Boost(std::vector<LorentzVector<Momentum>> const &lorentz_vectors)
{
    auto boost = boost::accumulate(lorentz_vectors, LorentzVector<Momentum>()).BoostIntoRestFrame();
    return SortedByPt(Transform(lorentz_vectors, [&](LorentzVector<Momentum> const & lorentz_vector) -> LorentzVector<Momentum> {
        return lorentz_vector.Boosted(boost);
    }));
}

}

EventShapes::EventShapes(std::vector<Jet> const &jets)
{
    INFO0;
    lorentz_vectors_ = Boost(Transform(jets, [](Jet const & jet) {
        return jet.LorentzVector();
    }));
}

EventShapes::EventShapes(std::vector<LorentzVector<Momentum>> const &lorentz_vectors)
{
    INFO0;
    lorentz_vectors_ = Boost(lorentz_vectors);
}

std::vector< Vector3< Momentum > > EventShapes::Vectors() const
{
    INFO0;
    return vectors_.Get([this]() {
        return Transform(LorentzVectors(), [](LorentzVector<Momentum> const & lorentz_vector) {
            return lorentz_vector.Spatial();
        });
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
    return Transform(LinearTensors(), [](GradedVector3<double> const & event_shape) {
        return event_shape.Scalar();
    });
}

std::vector<Vector3<double>> EventShapes::LinTenEigenVectors() const
{
    INFO0;
    return Transform(LinearTensors(), [](GradedVector3<double> const & event_shape) {
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
    return Transform(SphericalTensors(), [](GradedVector3<double> const & event_shape) {
        return event_shape.Scalar();
    });
}
std::vector<Vector3<double>> EventShapes::SphericityEigenVectors() const
{
    INFO0;
    return Transform(SphericalTensors(), [](GradedVector3<double> const & event_shape) {
        return event_shape.Vector();
    });
}

double EventShapes::ScaledMomentum(LorentzVector<Momentum> const &lorentz_vector, Energy const &energy) const
{
    INFO0;
    return energy > 0_eV && lorentz_vector.Rho() > 0_eV ? std::log(energy / lorentz_vector.Rho()) : -1;
}

Momentum EventShapes::Pt(LorentzVector<Momentum> const &lorentz_vector) const
{
    INFO0;
    return lorentz_vector.Perp();
}

Angle EventShapes::Rapidity(LorentzVector<Momentum> const &lorentz_vector) const
{
    INFO0;
    return lorentz_vector.T() > lorentz_vector.Z() ? lorentz_vector.Rapidity() : 1e99_rad;
}

Momentum EventShapes::PtInT(LorentzVector<Momentum> const &lorentz_vector) const
{
    INFO0;
    return lorentz_vector.Spatial() * Thrusts().at(1).Vector();
}

Momentum EventShapes::PtOutT(LorentzVector<Momentum> const &lorentz_vector) const
{
    INFO0;
    return lorentz_vector.Spatial() * Thrusts().at(2).Vector();
}

Angle EventShapes::RapidityT(LorentzVector<Momentum> const &lorentz_vector) const
{
    INFO0;
    return lorentz_vector.T() > lorentz_vector.Spatial() * Thrusts().at(0).Vector() ? lorentz_vector.Rapidity(Thrusts().at(0).Vector()) : 1e99_rad;
}

Momentum EventShapes::PtInS(LorentzVector<Momentum> const &lorentz_vector) const
{
    INFO0;
    return lorentz_vector.Spatial() * SphericalTensors().at(1).Vector();
}

Momentum EventShapes::PtOutS(LorentzVector<Momentum> const &lorentz_vector) const
{
    INFO0;
    return lorentz_vector.Spatial() * SphericalTensors().at(2).Vector();
}

Angle EventShapes::RapidityS(LorentzVector<Momentum> const &lorentz_vector) const
{
    INFO0;
    return lorentz_vector.T() > lorentz_vector.Spatial() * SphericalTensors().at(0).Vector() ? lorentz_vector.Rapidity(SphericalTensors().at(0).Vector()) : 1e99_rad;
}

Array3<GradedVector3<double>> EventShapes::Thrusts() const
{
    INFO0;
    return thrusts_.Get([this]() {
        switch (Vectors().size()) {
        case 0 :
            ;
        case 1 :
            return Thrusts1();
        case 2 :
            return Thrusts2();
        case 3 :
            return Thrusts3();
        default :
            return Thrusts4();
        }
    });
}

Array3<GradedVector3<double>> EventShapes::LinearTensors() const
{
    INFO0;
    return linear_tensors_.Get([this]() {
        return boost::accumulate(Vectors(), GradedMatrix3<Momentum>(), [](auto & sum, auto const & vector) {
            return vector.Mag2() > 0_eV * eV ? sum + GradedMatrix3<Momentum>(MatrixProduct(vector, vector) / vector.Mag(), vector.Mag()) : sum;
        }).Normalize().EigenSystem();
    });
}

Array3<GradedVector3<double>> EventShapes::SphericalTensors() const
{
    INFO0;
    return spherical_tensors_.Get([this]() {
        return boost::accumulate(Vectors(), GradedMatrix3<MomentumSquare>(), [](auto & sum, auto const & vector) {
            return vector.Mag2() > 0_eV * eV ? sum + GradedMatrix3<MomentumSquare>(MatrixProduct(vector, vector), vector.Mag2()) : sum;
        }).Normalize().EigenSystem();
    });
}

HemisphereMasses EventShapes::HemisphereMasses() const
{
    INFO0;
    return hemishpere_masses_.Get([this]() {
        auto positive = GradedLorentzVector<Momentum> {};
        auto negative = GradedLorentzVector<Momentum> {};
        for (auto const &lorentz_vector : LorentzVectors())(lorentz_vector.Spatial() * ThrustAxis() > 0_eV ? positive : negative) += {lorentz_vector, lorentz_vector.Perp(ThrustAxis())};
        auto hemisphere_masses = boca::HemisphereMasses {};
        hemisphere_masses.SetMasses(Range<EnergySquare>(negative.Vector().M2(), positive.Vector().M2()) / sqr(positive.Vector().E() + negative.Vector().E()));
        hemisphere_masses.SetBroadenings(Range<Energy>(negative.Scalar(), positive.Scalar()) / ScalarMomentum() / 2);
        return hemisphere_masses;
    });
}

Array3< GradedVector3< double >> EventShapes::Thrusts1() const
{
    INFO0;
    auto thrusts = Array3<GradedVector3<double>> {};
    for (auto &thrust : thrusts) thrust.Set(-1);
    return thrusts;
}

namespace
{
Vector3<double> Mirror(Vector3<double> const &axis, Dim3 dimension)
{
    return axis[dimension] < 0 ? -axis : axis;
}
}

Array3< GradedVector3< double >> EventShapes::Thrusts2() const
{
    INFO0;
    auto thrusts = Array3<GradedVector3<double>> {};
    auto thrust = Mirror(Vectors().at(0).Unit(), Dim3::z);
    thrusts.at(0).Set(thrust, 1);
    thrusts.at(1).Set(thrust.Orthogonal(), 0);
    thrusts.at(2).Set(thrusts.at(0).Vector().Cross(thrusts.at(1).Vector()), 0);
    return thrusts;
}

Array3< GradedVector3< double >> EventShapes::Thrusts3() const
{
    INFO0;
    auto vectors = Vectors();
    vectors = boost::range::sort(vectors);
    // thrust
    auto thrusts = Array3<GradedVector3<double>> {};
    thrusts.at(0).Set(Mirror(vectors.at(0).Unit(), Dim3::z), 2. * vectors.at(0).Mag() / ScalarMomentum());
    // major
    auto major = Mirror((vectors.at(1) - (thrusts.at(0).Vector() * vectors.at(1)) * thrusts.at(0).Vector()).Unit(), Dim3::x);
    thrusts.at(1).Set(major, (abs(vectors.at(1) * major) + abs(vectors.at(2) * major)) / ScalarMomentum());
    // minor
    thrusts.at(2).Set(thrusts.at(0).Vector().Cross(thrusts.at(1).Vector()), 0);
    return thrusts;
}

Array3< GradedVector3< double >> EventShapes::Thrusts4() const
{
    INFO0;
    // TODO special case with >= 4 coplanar particles will still fail. probably not too important...
    auto thrust = Thrust(Vectors());
    auto thrusts = Array3<GradedVector3<double>> {};
    thrusts.at(0).Set(Mirror(thrust.Vector().Unit(), Dim3::z), thrust.Scalar() / ScalarMomentum());
    auto major = Major(Transform(Vectors(), [&](Vector3<Momentum> const & vector) {
        return vector - (vector * thrusts.at(0).Vector()) * thrusts.at(0).Vector();
    }));
    thrusts.at(1).Set(Mirror(major.Vector().Unit(), Dim3::x), major.Scalar() / ScalarMomentum());
    if (thrusts.at(0).Vector() * thrusts.at(1).Vector() > std::numeric_limits<double>::epsilon()) {
        ERROR("Major is not perpendicular to thrust");
        thrusts.at(2).Set(Vector3<double>(), -1);
        return thrusts;
    }
    auto minor = thrusts.at(0).Vector().Cross(thrusts.at(1).Vector());
    thrusts.at(2).Set(minor, boost::accumulate(Vectors(), 0_eV, [&](Energy & sum, Vector3<Momentum> const & vector) {
        return sum + abs(minor * vector);
    }) / ScalarMomentum());
    return thrusts;
}

GradedVector3<Momentum> EventShapes::Thrust(std::vector<Vector3<Momentum>> const &vectors) const
{
    INFO0;
    auto thrust = GradedVector3<Momentum> {};
    for (auto const &vector : vectors) {
        auto position_1 = Position(vectors, vector);
        for (auto const &vector_2 : vectors) {
            auto position_2 = Position(vectors, vector_2);
            if (position_1 >= position_2) continue;
            auto cross = vector_2.Cross(vector);
            auto total_vector = Vector3<Momentum> {};
            for (auto const &vector_3 :  vectors) {
                auto position_3 = Position(vectors, vector_3);
                if (position_3 != position_2 && position_3 != position_1) total_vector += (vector_3 * cross > 0_eV * eV * eV) ? vector_3 : -vector_3;
            }
            auto candidates = std::vector<Vector3<Momentum>> {};
            candidates.emplace_back(total_vector - vector_2 - vector);
            candidates.emplace_back(total_vector - vector_2 + vector);
            candidates.emplace_back(total_vector + vector_2 - vector);
            candidates.emplace_back(total_vector + vector_2 + vector);
            for (auto const &candidate : candidates) if (candidate.Mag2() > sqr(thrust.Scalar())) thrust.Set(candidate, candidate.Mag());
        }
    }
    return thrust;
}

GradedVector3<Momentum> EventShapes::Major(std::vector<Vector3<Momentum>> const &vectors) const
{
    INFO0;
    auto major = GradedVector3<Momentum> {};
    for (auto const &vector : vectors) {
        auto position = Position(vectors, vector);
        auto total_momentum = Vector3<Momentum> {};
        for (auto const &vector_2 : vectors) if (position != Position(vectors,  vector_2)) total_momentum += (vector_2 * vector > 0_eV * eV) ? vector_2 : -vector_2;
        std::vector<Vector3<Momentum>> candidates;
        candidates.emplace_back(total_momentum - vector);
        candidates.emplace_back(total_momentum + vector);
        for (auto const &candidate : candidates) if (candidate.Mag2() > sqr(major.Scalar())) major.Set(candidate, candidate.Mag());
    }
    return major;
}

Momentum EventShapes::ScalarMomentum() const
{
    return scalar_momentum_.Get([this]() {
        return boost::accumulate(Vectors(), 0_eV, [](Momentum & sum, Vector3<Momentum> const & vector) {
            return sum + vector.Mag();
        });
    });
}

}

