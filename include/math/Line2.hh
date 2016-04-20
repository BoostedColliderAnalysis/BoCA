/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "math/Vector2.hh"

namespace boca
{

template<typename Value>
class Line2
{
public:
    typedef typename boost::units::multiply_typeof_helper<Value, Value>::type ValueSquare;
    Line2() {}
    Line2(Vector2<Value> const& point_1, Vector2<Value> const& point_2) {
        point_1_ = point_1;
        point_2_ = point_2;
    }

    Value DistanceToSegment(Vector2<Value> const& point) const {
        if (Mod2() == ValueSquare(0)) return Distance_1(point); // v == w case
        auto parameter = Paramter(point);
        if (parameter < 0) return Distance_1(point); // Beyond the 'v' end of the segment
        if (parameter > 1) return Distance_2(point); // Beyond the 'w' end of the segment
        return DistanceToLine(point); // Projection falls on the segment
    }
    Value DistanceToLine(Vector2<Value> const& point) const {
        if (Mod2() == ValueSquare(0)) return Distance_1(point); // v == w case
        return (point - Projection(point)).Mod(); // second implementation
        return Area(point) / Mod(); // first implementation
    }
    template<typename Jet_>
    Angle Distance(Jet_ const& jet) const {
        auto phi = jet.Phi();
        auto distance_1 = DistanceToSegment(Vector2<Angle>(jet.Rap(), phi));
        phi = Wrap(phi);
        auto distance_2 = DistanceToSegment(Vector2<Angle>(jet.Rap(), phi));
        return std::min(distance_1, distance_2);
    }
    Vector2<Value> const& Point_1() const {
        return point_1_;
    }
    Vector2<Value> const& Point_2() const {
        return point_2_;
    }
    Value Mod() const {
        return Vector().Mod();
    }
    ValueSquare Mod2() const {
        return Vector().Mod2();
    }
    Vector2<Value> Vector() const {
        return point_2_ - point_1_;
    }
    Vector2<Value> Vector_1(Vector2<Value> const& point) const {
        return point - point_1_;
    }
    Vector2<Value> Vector_2(Vector2<Value> const& point) const {
        return point - point_2_;
    }
    Value Distance_1(Vector2<Value> const& point) const {
        return Vector_1(point).Mod();
    }
    Value Distance_2(Vector2<Value> const& point) const {
        return Vector_2(point).Mod();
    }
    double Paramter(Vector2<Value> const& point) const {
        // Consider the line extending the segment, parameterized as v + t (w - v).
        // We find projection of point p onto the line.
        // It falls where t = [(p-v) . (w-v)] / |w-v|^2
        return point * Vector() / Mod2();
    }
    Vector2<Value> Projection(Vector2<Value> const& point) const {
        return point_1_ + Vector() * Paramter(point);
    }
    ValueSquare SignedArea() const {
        return point_1_ ^ point_2_;
    }
    ValueSquare Area(Vector2<Value> const& point) const {
        return boost::units::abs((Vector() ^ point) + SignedArea());
    }
private:
    Vector2<Value> point_1_; // v
    Vector2<Value> point_2_; // w
};

}
