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
#include "boca/EventShapes.hh"
#include "boca/generic/Vector.hh"
#include "boca/generic/Exception.hh"
// #define INFORMATION
#include "boca/generic/DEBUG.hh"
#include "boca/multiplets/Sort.hh"

namespace boca
{

EventShapes::EventShapes() {}

namespace
{

std::vector<LorentzVector<Momentum>> Boost(std::vector<LorentzVector<Momentum>> const& lorentz_vectors)
{
    auto boost = boost::accumulate(lorentz_vectors, LorentzVector<Momentum>()).BoostIntoRestFrame();
    return SortedByPt(Transform(lorentz_vectors, [&](LorentzVector<Momentum> const & lorentz_vector) -> LorentzVector<Momentum> {
        return lorentz_vector.Boosted(boost);
    }));
}

std::vector<Vector3<Momentum>> GetVectors(std::vector<LorentzVector<Momentum>> const& lorentz_vectors)
{
    return Transform(lorentz_vectors, [](LorentzVector<Momentum> const & lorentz_vector) {
        return lorentz_vector.Vector();
    });
}

}

EventShapes::EventShapes(std::vector<Jet> const& jets)
{
    INFO0;
    lorentz_vectors_ = Boost(Transform(jets, [](Jet const & jet) {
        return jet.Vector();
    }));
    vectors_ = GetVectors(lorentz_vectors_);
}

EventShapes::EventShapes(std::vector<LorentzVector<Momentum>> const& lorentz_vectors)
{
    INFO0;
    lorentz_vectors_ = Boost(lorentz_vectors);
    vectors_ = GetVectors(lorentz_vectors_);
}

std::vector< Vector3< Momentum > > EventShapes::Vectors() const
{
    INFO0;
    return vectors_;
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
    return lorentz_vector.T() > lorentz_vector.Vector() * Thrusts().at(0).Vector() ? lorentz_vector.Rapidity(Thrusts().at(0).Vector()) : 1e99_rad;
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
    return lorentz_vector.T() > lorentz_vector.Vector() * SphericalTensors().at(0).Vector() ? lorentz_vector.Rapidity(SphericalTensors().at(0).Vector()) : 1e99_rad;
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
        auto i = static_cast<int>(floor((-coschi + 1.) / 2 * hi.size()));
        auto j = static_cast<int>(floor((coschi + 1.) / 2 * hi.size()));
        return hi[i] - hi[j];
    } else return 1e99;
}

Array3<GradedVector3<double>> EventShapes::Thrusts() const
{
    INFO0;
    return thrusts_.Get([this]() {
        // algorithm based on Brandt/Dahmen Z Phys C1 (1978)
        switch (Vectors().size()) {
        case 0 : ;
        case 1 : return GetThrusts1();
        case 2 : return GetThrusts2();
        case 3 : return GetThrusts3();
        default : return GetThrusts4();
        }
    });
}

Array3<GradedVector3<double>> EventShapes::LinearTensors() const
{
    INFO0;
    return linear_tensors_.Get([this]() {
        return boost::accumulate(Vectors(), GradedMatrix3<Momentum>(), [](GradedMatrix3<Momentum>& sum, Vector3<Momentum> const & vector) {
            return vector.Mag2() > 0_eV * eV ? sum + GradedMatrix3<Momentum>(MatrixProduct(vector, vector) / vector.Mag(), vector.Mag()) : sum;
        }).Normalize().EigenSystem();
    });
}

Array3<GradedVector3<double>> EventShapes::SphericalTensors() const
{
    INFO0;
    return spherical_tensors_.Get([this]() {
        return boost::accumulate(Vectors(), GradedMatrix3<MomentumSquare>(), [](GradedMatrix3<MomentumSquare>& sum, Vector3<Momentum> const & vector) {
            return vector.Mag2() > 0_eV * eV ? sum + GradedMatrix3<MomentumSquare>(MatrixProduct(vector, vector), vector.Mag2()) : sum;
        }).Normalize().EigenSystem();
    });
}

HemisphereMasses EventShapes::HemisphereMasses() const
{
    INFO0;
    return hemishpere_masses_.Get([this]() {
        GradedLorentzVector<Momentum> positive;
        GradedLorentzVector<Momentum> negative;
        for (auto const & lorentz_vector : LorentzVectors()) {
            if (lorentz_vector.Vector() * ThrustAxis() > 0_eV) positive += {lorentz_vector, lorentz_vector.Perp(ThrustAxis())};
            else negative += {lorentz_vector, lorentz_vector.Perp(ThrustAxis())};
        }
        boca::HemisphereMasses hemisphere_masses;
        // masses
        hemisphere_masses.SetMasses(Range<EnergySquare>(negative.Vector().M2(), positive.Vector().M2()) / sqr(positive.Vector().E() + negative.Vector().E()));
        // jet broadening
        hemisphere_masses.SetBroadenings(Range<Energy>(negative.Scalar(), positive.Scalar()) / ScalarMomentum() / 2);
        return hemisphere_masses;
    });
}

Array3< GradedVector3< double >> EventShapes::GetThrusts1() const
{
    INFO0;
    Array3<GradedVector3<double>> thrusts;
    for (auto & thrust : thrusts) thrust.Set(-1);
    return thrusts;
}

namespace
{
Vector3<double> Mirror(Vector3<double> const& axis, Dim3 dimension)
{
    return axis[dimension] < 0 ? -axis : axis;
}
}

Array3< GradedVector3< double >> EventShapes::GetThrusts2() const
{
    INFO0;
    Array3<GradedVector3<double>> thrusts;
    auto thrust = Mirror(Vectors().at(0).Unit(), Dim3::z);
    thrusts.at(0).Set(thrust, 1);
    thrusts.at(1).Set(thrust.Orthogonal(), 0);
    thrusts.at(2).Set(thrusts.at(0).Vector().Cross(thrusts.at(1).Vector()), 0);
    return thrusts;
}

Array3< GradedVector3< double >> EventShapes::GetThrusts3() const
{
    INFO0;
    auto vectors = Vectors();
    vectors = boost::range::sort(vectors, [](Vector3<Momentum> const & vector_1, Vector3<Momentum> const &  vector_2) {
        return vector_1.Mag2() > vector_2.Mag2();
    });
    // thrust
    Array3<GradedVector3<double>> thrusts;
    auto scalar_momentum = ScalarMomentum();
    thrusts.at(0).Set(Mirror(vectors.at(0).Unit(), Dim3::z), 2. * vectors.at(0).Mag() / scalar_momentum);
    // major
    auto major = Mirror((vectors.at(1) - (thrusts.at(0).Vector() * vectors.at(1)) * thrusts.at(0).Vector()).Unit(), Dim3::x);
    thrusts.at(1).Set(major, (abs(vectors.at(1) * major) + abs(vectors.at(2) * major)) / scalar_momentum);
    // minor
    thrusts.at(2).Set(thrusts.at(0).Vector().Cross(thrusts.at(1).Vector()), 0);
    return thrusts;
}

Array3< GradedVector3< double >> EventShapes::GetThrusts4() const
{
    INFO0;
    // TODO special case with >= 4 coplanar particles will still fail. probably not too important...
    auto thrust = Thrust(Vectors());
    auto scalar_momentum = ScalarMomentum();
    Array3<GradedVector3<double>> thrusts;
    thrusts.at(0).Set(Mirror(thrust.Vector().Unit(), Dim3::z), thrust.Scalar() / scalar_momentum);
    //major
    auto major = Major(Transform(Vectors(), [&](Vector3<Momentum> const & vector) {
        return vector - (vector * thrusts.at(0).Vector()) * thrusts.at(0).Vector();
    }));
    thrusts.at(1).Set(Mirror(major.Vector().Unit(), Dim3::x), major.Scalar() / scalar_momentum);

    // minor
    if (thrusts.at(0).Vector() * thrusts.at(1).Vector() < 1e-10) {
        auto minor = thrusts.at(0).Vector().Cross(thrusts.at(1).Vector());
        thrusts.at(2).Set(minor, boost::accumulate(Vectors(), 0_eV, [&](Energy & sum, Vector3<Momentum> const & vector) {
            return sum + abs(minor * vector);
        }) / scalar_momentum);
    } else thrusts.at(2).Set(Vector3<double>(), -1);
    return thrusts;
}

GradedVector3<Momentum> EventShapes::Thrust(std::vector<Vector3<Momentum>> const& vectors) const
{
    INFO0;
    GradedVector3<Momentum> thrust;
    for (unsigned first = 1; first < Vectors().size(); ++first) {
        for (unsigned second = 0; second < first; ++second) {
            auto cross = Vectors().at(second).Cross(Vectors().at(first));
            Vector3<Momentum> total_vector;
            for (unsigned third = 0; third < Vectors().size(); ++third) if (third != second && third != first) total_vector += (vectors[third] * cross > 0_eV * eV * eV) ? vectors[third] : -vectors[third];
            std::vector<Vector3<Momentum>> candidates;
            candidates.emplace_back(total_vector - Vectors().at(second) - Vectors().at(first));
            candidates.emplace_back(total_vector - Vectors().at(second) + Vectors().at(first));
            candidates.emplace_back(total_vector + Vectors().at(second) - Vectors().at(first));
            candidates.emplace_back(total_vector + Vectors().at(second) + Vectors().at(first));
            for (auto & candidate : candidates) if (candidate.Mag2() > sqr(thrust.Scalar())) thrust.Set(candidate, candidate.Mag());
        }
    }
    return thrust;
}

GradedVector3<Momentum> EventShapes::Major(std::vector<Vector3<Momentum>> const& vectors) const
{
    INFO0;
    GradedVector3<Momentum> major;
    for (unsigned first = 0; first < Vectors().size(); ++first) {
        Vector3<Momentum> total_momentum;
        for (unsigned second = 0; second < Vectors().size(); ++second) if (second != first) total_momentum += (vectors[second] * vectors[first] > 0_eV * eV) ? vectors[second] : -vectors[second];
        std::vector<Vector3<Momentum>> candidates;
        candidates.emplace_back(total_momentum - vectors[first]);
        candidates.emplace_back(total_momentum + vectors[first]);
        for (auto & candidate : candidates) if (candidate.Mag2() > sqr(major.Scalar())) major.Set(candidate, candidate.Mag());
    }
    return major;
}

std::vector<double> EventShapes::EnergyEnergyCorrelation(int bins) const
{
    INFO0;
    std::vector<double> correlations(bins);
    if (LorentzVectors().size() < 2) return correlations;
    // hi is the histogram. It is understood that hi.front() contains
    // the bin [-1 < std::cos(chi) < -1+delta] and hi.back() the bin [1-delta
    // < std::cos(chi) < 1]. Here, delta = 2/hi.size().
    auto energy_square = sqr(boost::accumulate(LorentzVectors(), 0_eV, [](Energy & sum, LorentzVector<Momentum> const & lorentz_vector) {
        return sum + lorentz_vector.E();
    }));
    auto pairs = UnorderedPairs(LorentzVectors(), [&](LorentzVector<Momentum> const & lorentz_vector_1, LorentzVector<Momentum> const & lorentz_vector_2) {
        return std::make_pair(lorentz_vector_1, lorentz_vector_2);
    });
    auto delta = 2. / bins;
    for (auto & correlation : correlations) {
        auto cos_chi = Position(correlations, correlation) * delta - 1;
        for (auto const & pair : pairs) {
            auto diff = std::abs(cos_chi - boost::units::cos(pair.first.Angle(pair.second)));
            if (delta > diff) correlation += pair.first.E() * pair.second.E() / energy_square;
        }
    }
    return correlations;
}

Momentum EventShapes::ScalarMomentum() const
{
    return boost::accumulate(Vectors(), 0_eV, [](Momentum & sum, Vector3<Momentum> const & vector) {
        return sum + vector.Mag();
    });
}

}

