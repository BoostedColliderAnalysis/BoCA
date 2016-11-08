/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <boost/range/algorithm/max_element.hpp>
#include <boost/range/algorithm/min_element.hpp>
#include <boost/range/algorithm_ext/is_sorted.hpp>
#include <boost/range/algorithm_ext/erase.hpp>

#include "boca/math/Vector2.hh"
#include "boca/math/Range.hh"

namespace boca
{

/**
 * @ingroup Math
 * @brief Rectangle of two Ranges
 */
template<typename Value>
class Rectangle
{

public:

    Rectangle() {}

    Rectangle(Range<Value> x, Range<Value> y) :
        x_(x),
        y_(y)
    {}

    Rectangle(Vector2<Value> min, Vector2<Value> max) :
        x_( {min.X(), max.X()}),
        y_( {min.Y(), max.Y()})
    {}

    Rectangle(Vector2<Value> min, Value width, Value height) :
        x_( {min.X(), min.X() + width}),
        y_( {min.Y(), min.Y() + height})
    {}

    Rectangle(Value x_min, Value x_max, Value y_min, Value y_max) :
        x_( {x_min, x_max}),
        y_( {y_min, y_max})
    {}

    void SetX(Value const& min, Value const& max) {
        x_.Set(min, max);
    }

    void SetY(Value const& min, Value const& max) {
        y_.Set(min, max);
    }

    void SetX(Range<Value> const& x) {
        x_ = x;
    }

    void SetY(Range<Value> const& y) {
        y_ = y;
    }

    void SetX(std::pair<Value, Value> const& x) {
        x_.Set(x);
    }

    void SetY(std::pair<Value, Value> const& y) {
        y_.Set(y);
    }

    void ResetY() {
        y_ = Range<Value>();
    }

    void ResetX() {
        x_ = Range<Value>();
    }

    void SetXMin(Value x_min) {
        x_.SetMin(x_min);
    }

    void SetXMax(Value x_max) {
        x_.SetMax(x_max);
    }

    void SetYMin(Value y_min) {
        y_.SetMin(y_min);
    }

    void SetYMax(Value y_max) {
        y_.SetMax(y_max);
    }

    void Widen(Rectangle<Value> const& range) {
        x_.Widen(range.Horizontal());
        y_.Widen(range.Vertical());
    }

    void WidenX(Range<Value> const& x) {
        x_.Widen(x);
    }

    void WidenXMin(Value x_min) {
        x_.WidenMin(x_min);
    }

    void WidenXMax(Value x_max) {
        x_.WidenMax(x_max);
    }

    void WidenY(Range<Value> const& y) {
        y_.Widen(y);
    }

    void WidenYMin(Value y_min) {
        y_.WidenMin(y_min);
    }

    void WidenYMax(Value y_max) {
        y_.WidenMax(y_max);
    }

    Value XMin() const {
        return x_.Min();
    }

    Value XMax() const {
        return x_.Max();
    }

    Value YMin() const {
        return y_.Min();
    }

    Value YMax() const {
        return y_.Max();
    }

    Vector2<Value> Min() const {
        return {x_.Min(), y_.Min()};
    }

    Vector2<Value> Max() const {
        return {x_.Max(), y_.Max()};
    }

    Range<Value>& Horizontal()  {
        return x_;
    }

    Range<Value>& Vertical()  {
        return y_;
    }

    Range<Value> const& Horizontal() const {
        return x_;
    }

    Range<Value> const& Vertical() const {
        return y_;
    }

    Value Width() const {
        return x_.Length();
    }

    Value Height() const {
        return y_.Length();
    }

    template <typename Value2>
    void WidenY(Range<Value> const& bound_x, std::vector<Value2> const& xs1, std::vector<Value2> const& ys1) {
//         y_.Widen({0.001,1});
      //         std::cout << "bound min " << bound_x.Min() << " bound max " << bound_x.Max() << '\n';
      auto xs = xs1;
      boost::remove_erase(xs, 0);
      auto ys = ys1;
      boost::remove_erase(ys, 0);
        auto bound = Range<int>{};
        if (boost::range::is_sorted(xs, Smaller<Value2>())) {
//             std::cout << "smaller" << '\n';
            bound.SetMin(boost::range::lower_bound(xs, Value2(bound_x.Min())) - xs.begin());
            bound.SetMax(boost::range::upper_bound(xs, Value2(bound_x.Max())) - xs.begin());
        } else if (boost::range::is_sorted(xs, Larger<Value2>())) {
//             std::cout << "larger" << '\n';
            bound.SetMin(boost::range::lower_bound(xs, Value2(bound_x.Max()), Larger<Value2>()) - xs.begin());
            bound.SetMax(boost::range::upper_bound(xs, Value2(bound_x.Min()), Larger<Value2>()) - xs.begin());
        } else {
//             std::cout << "not sorted" << '\n';
            bound.SetMin(0);
            bound.SetMax(xs.size());
        }
//         std::cout << "min_x " << bound.Min() << " max_x " << bound.Max() << '\n';
        auto bound_y = Range<Value2>{};
        auto min = std::min_element(ys.begin() + bound.Min(), ys.begin() + bound.Max());
//         , SmallerButNonZero<Value2>());
        bound_y.SetMin(*min);
        bound_y.SetMax(*std::max_element(ys.begin() + bound.Min(), ys.begin() + bound.Max()));
//         std::cout << "min " << bound_y.Min() << " max " << bound_y.Max() << '\n';
        y_.Widen(bound_y);
    }

    template <typename Value2>
    void WidenX(Range<Value> const& y, std::vector<Value2> const& xs, std::vector<Value2> const& ys) {
        auto min_y = boost::range::upper_bound(ys, Value2(y.Min())) - ys.begin();
        auto max_y = boost::range::lower_bound(ys, Value2(y.Max())) - ys.begin();
        auto min = std::min_element(xs.begin() + min_y, xs.begin() + max_y, SmallerButNonZero<Value2>());
        auto max = std::max_element(xs.begin() + min_y, xs.begin() + max_y);
        x_.Widen( {std::min(*min, *max), std::max(*min, *max)});
    }

    /**
     * @brief Output stream operator
     */
    friend auto &operator<<(std::ostream &stream, Rectangle const &rectangle)
    {
        stream << rectangle.x_ << rectangle.y_;
        return stream;
    }

private:

    template <typename Value_2_>
    std::function<bool(Value_2_ value_1, Value_2_ value_2)> Smaller() {
        return [](Value_2_ value_1, Value_2_ value_2) {
            return value_1 < value_2;
        };
    }

    template <typename Value_2_>
    std::function<bool(Value_2_ value_1, Value_2_ value_2)> SmallerButNonZero() {
        return [](Value_2_ value_1, Value_2_ value_2) {
            return value_1 != 0 ? value_1 < value_2 : value_1 > value_2;
        };
    }

    template <typename Value_2_>
    std::function<bool(Value_2_ value_1, Value_2_ value_2)> Larger() {
        return [](Value_2_ value_1, Value_2_ value_2) {
            return value_1 > value_2;
        };
    }

    Range<Value> x_;
    Range<Value> y_;

};

}

