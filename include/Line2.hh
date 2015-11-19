/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Vector2.hh"

namespace boca
{

class Line2
{
public:
    Line2() {}
    Line2(Vector2 const& point_1, Vector2 const& point_2) {
        point_1_ = point_1;
        point_2_ = point_2;
    }
    float DistanceToSegment(Vector2 const& point) const {
        if (Mod2() == 0) return Distance_1(point); // v == w case
        float parameter = Paramter(point);
        if (parameter < 0) return Distance_1(point); // Beyond the 'v' end of the segment
        if (parameter > 1) return Distance_2(point); // Beyond the 'w' end of the segment
        return DistanceToLine(point); // Projection falls on the segment
    }
    float DistanceToLine(Vector2 const& point) const {
        if (Mod2() == 0) return Distance_1(point); // v == w case
        return Area(point) / Mod(); // first implementation
        return (point - Projection(point)).Mod(); // second implementation
    }
    Vector2 Point_1() const {
        return point_1_;
    }
    Vector2 Point_2() const {
        return point_2_;
    }
    float Mod() const {
        return Vector().Mod();
    }
    float Mod2() const {
        return Vector().Mod2();
    }
    Vector2 Vector() const {
        return point_2_ - point_1_;
    }
    Vector2 Vector_1(Vector2 const& point) const {
        return point - point_1_;
    }
    Vector2 Vector_2(Vector2 const& point) const {
        return point - point_2_;
    }
    float Distance_1(Vector2 const& point) const {
        return Vector_1(point).Mod();
    }
    float Distance_2(Vector2 const& point) const {
        return Vector_2(point).Mod();
    }
    float Paramter(Vector2 const& point) const {
        // Consider the line extending the segment, parameterized as v + t (w - v).
        // We find projection of point p onto the line.
        // It falls where t = [(p-v) . (w-v)] / |w-v|^2
        return Vector_1(point) * Vector() / Mod2();
    }
    Vector2 Projection(Vector2 const& point) const {
        return point_1_ + Paramter(point) * Vector();
    }
    float Area() const {
        return point_1_ ^ point_2_;
    }
    float Area(Vector2 const& point) const {
        return std::abs(Vector() ^ point + Area());
    }
private:
    Vector2 point_1_; // v
    Vector2 point_2_; // w
};

}
