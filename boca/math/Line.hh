/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once
#include "boca/physics/Units.hh"

namespace boca
{

/**
 * @ingroup Math
 * @brief Line between two points
 */
template <template<typename> class Vector_, typename Value_>
class Line
{
public:
    using Value_Square = typename boost::units::multiply_typeof_helper<Value_, Value_>::type;
    Line() {}
    Line(Vector_<Value_> const& point_1, Vector_<Value_> const& point_2) {
        point_1_ = point_1;
        point_2_ = point_2;
    }

    Value_ DistanceToSegment(Vector_<Value_> const& point) const {
        if (Mag2() == Value_Square(0)) return Distance_1(point); // v == w case
        auto parameter = Paramter(point);
        if (parameter < 0) return Distance_1(point); // Beyond the 'v' end of the segment
        if (parameter > 1) return Distance_2(point); // Beyond the 'w' end of the segment
        return DistanceToLine(point); // Projection falls on the segment
    }
    Value_ DistanceToLine(Vector_<Value_> const& point) const {
        if (Mag2() == Value_Square(0)) return Distance_1(point); // v == w case
        return (point - Projection(point)).Mag(); // second implementation
        return Area(point) / Mag(); // first implementation
    }
    template<typename Jet_>
    Value_ MinDistanceTo(Jet_ const& jet) const {
        auto phi = jet.Phi();
        auto distance_1 = DistanceToSegment(Vector_<Value_>(jet.Rap(), phi));
        phi = Wrap(phi);
        auto distance_2 = DistanceToSegment(Vector_<Value_>(jet.Rap(), phi));
        return std::min(distance_1, distance_2);
    }
    Vector_<Value_> const& Point_1() const {
        return point_1_;
    }
    Vector_<Value_> const& Point_2() const {
        return point_2_;
    }
    Value_ Mag() const {
        return Vector().Mag();
    }
    Value_Square Mag2() const {
        return Vector().Mag2();
    }
    Vector_<Value_> Vector() const {
        return point_2_ - point_1_;
    }
    Vector_<Value_> Vector_1(Vector_<Value_> const& point) const {
        return point - point_1_;
    }
    Vector_<Value_> Vector_2(Vector_<Value_> const& point) const {
        return point - point_2_;
    }
    Value_ Distance_1(Vector_<Value_> const& point) const {
        return Vector_1(point).Mag();
    }
    Value_ Distance_2(Vector_<Value_> const& point) const {
        return Vector_2(point).Mag();
    }
    double Paramter(Vector_<Value_> const& point) const {
        // Consider the line extending the segment, parameterized as v + t (w - v).
        // We find projection of point p onto the line.
        // It falls where t = [(p-v) . (w-v)] / |w-v|^2
        return point * Vector() / Mag2();
    }
    Vector_<Value_> Projection(Vector_<Value_> const& point) const {
        return point_1_ + Vector() * Paramter(point);
    }
    auto SignedArea() const {
        return point_1_ ^ point_2_;
    }
    Value_Square Area(Vector_<Value_> const& point) const {
        return abs((Vector() ^ point) + SignedArea());
    }
private:
    Vector_<Value_> point_1_; // v
    Vector_<Value_> point_2_; // w
};

}
