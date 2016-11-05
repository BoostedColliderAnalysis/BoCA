/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once
#include <boost/units/operators.hpp>

namespace boca
{

/**
 * @ingroup Math
 * @brief Line between two points
 */
template <template<typename> class Vector_, typename Value_>
class Line
{

    using Value_Square = typename boost::units::multiply_typeof_helper<Value_, Value_>::type;

public:

    /**
    * @name Constructor
    * @{
    */

    /**
    * @brief Default constructor
    */
    Line() {}

    /**
    * @brief Constructor accepting two vectors
    */
    Line(Vector_<Value_> const &point_1, Vector_<Value_> const &point_2) :
        point_1_(point_1),
        point_2_(point_2)
    {}

    //@}

    /**
    * @name Getter
    * @{
    */

    /**
    * @brief Vector of first point
    */
    Vector_<Value_> const &Point_1() const
    {
        return point_1_;
    }

    /**
    * @brief Vector of first point
    */
    Vector_<Value_> Point_1()
    {
        return point_1_;
    }

    /**
    * @brief Vector of second point
    */
    Vector_<Value_> const &Point_2() const
    {
        return point_2_;
    }

    /**
    * @brief Vector of second point
    */
    Vector_<Value_> Point_2()
    {
        return point_2_;
    }

    //@}

    /**
    * @name Distances
    * @{
    */

    /**
    * @brief Distance of point to line segment spanned between the two vectors
    */
    Value_ DistanceToSegment(Vector_<Value_> const &point) const
    {
        if (Mag2() == Value_Square(0)) return Distance_1(point); // v == w case
        auto parameter = Paramter(point);
        if (parameter < 0) return Distance_1(point); // Beyond the 'v' end of the segment
        if (parameter > 1) return Distance_2(point); // Beyond the 'w' end of the segment
        return DistanceToLine(point); // Projection falls on the segment
    }

    /**
    * @brief Distance of point to the line
    */
    Value_ DistanceToLine(Vector_<Value_> const &point) const
    {
        if (Mag2() == Value_Square(0)) return Distance_1(point); // v == w case
        return (point - Projection(point)).Mag();
    }

    //@}

    /**
    * @name Line vector
    * @{
    */

    /**
    * @brief Vector between the two points
    */
    Vector_<Value_> Vector() const
    {
        return point_2_ - point_1_;
    }

    /**
    * @brief Square of the magnitude of the vector
    */
    Value_Square Mag2() const
    {
        return Vector().Mag2();
    }

    /**
    * @brief Magnitude of the vector
    */
    Value_ Mag() const
    {
        return Vector().Mag();
    }

    //@}

    /**
    * @name Relation to a point
    * @{
    */

    /**
    * @brief vector between a point and the first point
    */
    Vector_<Value_> Vector_1(Vector_<Value_> const &point) const
    {
        return point - point_1_;
    }

    /**
    * @brief vector between a point and the second point
    */
    Vector_<Value_> Vector_2(Vector_<Value_> const &point) const
    {
        return point - point_2_;
    }

    /**
    * @brief Distance between the point and the first point
    */
    Value_ Distance_1(Vector_<Value_> const &point) const
    {
        return Vector_1(point).Mag();
    }

    /**
    * @brief Distance between the point and the second point
    */
    Value_ Distance_2(Vector_<Value_> const &point) const
    {
        return Vector_2(point).Mag();
    }

    /**
    * @brief Parameter along the line segment between the two points
    */
    double Paramter(Vector_<Value_> const &point) const
    {
        // Consider the line extending the segment, parameterized as v + t (w - v).
        // We find projection of point p onto the line.
        // It falls where t = [(p-v) . (w-v)] / |w-v|^2
        return point * Vector() / Mag2();
    }

    /**
    * @brief Projection of the point onto the line
    */
    Vector_<Value_> Projection(Vector_<Value_> const &point) const
    {
        return point_1_ + Vector() * Paramter(point);
    }

    //@}

    /**
     * @brief Output stream operator
     */
    friend auto &operator<<(std::ostream &stream, Line const &line)
    {
        stream << line.point_1_ << line.point_2_;
        return stream;
    }

private:

    Vector_<Value_> point_1_; // v

    Vector_<Value_> point_2_; // w

};

}
