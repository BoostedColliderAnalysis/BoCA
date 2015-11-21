/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Vector2.hh"

namespace boca
{

template<typename Value>
class Line2
{
public:
    Line2() {}
    Line2(Vector2<Value> const& point_1, Vector2<Value> const& point_2) {
        point_1_ = point_1;
        point_2_ = point_2;
    }
    Value DistanceToSegment(Vector2<Value> const& point) const {
        if (Mod2() == 0) return Distance_1(point); // v == w case
        Value parameter = Paramter(point);
        if (parameter < 0) return Distance_1(point); // Beyond the 'v' end of the segment
        if (parameter > 1) return Distance_2(point); // Beyond the 'w' end of the segment
        return DistanceToLine(point); // Projection falls on the segment
    }
    Value DistanceToLine(Vector2<Value> const& point) const {
        if (Mod2() == 0) return Distance_1(point); // v == w case
        return (point - Projection(point)).Mod(); // second implementation
        return Area(point) / Mod(); // first implementation
    }
    Vector2<Value> Point_1() const {
        return point_1_;
    }
    Vector2<Value> Point_2() const {
        return point_2_;
    }
    Value Mod() const {
        return Vector().Mod();
    }
    Value Mod2() const {
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
    Value Paramter(Vector2<Value> const& point) const {
        // Consider the line extending the segment, parameterized as v + t (w - v).
        // We find projection of point p onto the line.
        // It falls where t = [(p-v) . (w-v)] / |w-v|^2
        return Vector_1(point) * Vector() / Mod2();
    }
    Vector2<Value> Projection(Vector2<Value> const& point) const {
        return point_1_ + Paramter(point) * Vector();
    }
    Value Area() const {
        return point_1_ ^ point_2_;
    }
    Value Area(Vector2<Value> const& point) const {
        return std::abs(Vector() ^ point + Area());
    }
private:
    Vector2<Value> point_1_; // v
    Vector2<Value> point_2_; // w
};

}
