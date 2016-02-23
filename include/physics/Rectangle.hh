/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <boost/range/algorithm/max_element.hpp>
#include <boost/range/algorithm/min_element.hpp>
#include <boost/range/algorithm_ext/is_sorted.hpp>

#include "physics/Vector2.hh"
#include "physics/Range.hh"

namespace boca
{

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

    Range<Value> & Horizontal()  {
      return x_;
    }

    Range<Value> & Vertical()  {
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
    void WidenY(Range<Value> const& bound_x, std::vector<Value2> const& xs, std::vector<Value2> const& ys) {
//         y_.Widen({0.001,1});
        std::cout << "bound min " << bound_x.Min() << " bound max " << bound_x.Max() << std::endl;
        Range<int> bound;
        if (boost::range::is_sorted(xs, Smaller<Value2>())) {
            std::cout << "smaller" << std::endl;
            bound.SetMin(boost::range::lower_bound(xs, Value2(bound_x.Min())) - xs.begin());
            bound.SetMax(boost::range::upper_bound(xs, Value2(bound_x.Max())) - xs.begin());
        } else if (boost::range::is_sorted(xs, Larger<Value2>())) {
            std::cout << "larger" << std::endl;
            bound.SetMin(boost::range::lower_bound(xs, Value2(bound_x.Max()), Larger<Value2>()) - xs.begin());
            bound.SetMax(boost::range::upper_bound(xs, Value2(bound_x.Min()), Larger<Value2>()) - xs.begin());
        } else {
            std::cout << "not sorted" << std::endl;
            bound.SetMin(0);
            bound.SetMax(xs.size());
        }
        std::cout << "min_x " << bound.Min() << " max_x " << bound.Max() << std::endl;
        Range<Value2> bound_y;
        bound_y.SetMin(*std::min_element(ys.begin() + bound.Min(), ys.begin() + bound.Max(), SmallerButNonZero<Value2>()));
        bound_y.SetMax(*std::max_element(ys.begin() + bound.Min(), ys.begin() + bound.Max()));
        std::cout << "min " << bound_y.Min() << " max " << bound_y.Max() << std::endl;
        y_.Widen(bound_y);
    }

    template <typename Value2>
    void WidenX(Range<Value> const& y, std::vector<Value2> const& xs, std::vector<Value2> const& ys) {
        int min_y = boost::range::upper_bound(ys, Value2(y.Min())) - ys.begin();
        int max_y = boost::range::lower_bound(ys, Value2(y.Max())) - ys.begin();
        auto min = std::min_element(xs.begin() + min_y, xs.begin() + max_y, SmallerButNonZero<Value2>());
        auto max = std::max_element(xs.begin() + min_y, xs.begin() + max_y);
        x_.Widen( {std::min(*min, *max), std::max(*min, *max)});
    }

private:

    template <typename Value2>
    std::function<bool(Value2 a, Value2 b)> Smaller() {
        return [](Value2 a, Value2 b) {
            return a < b;
        };
    }

    template <typename Value2>
    std::function<bool(Value2 a, Value2 b)> SmallerButNonZero() {
        return [](Value2 a, Value2 b) {
            return a != 0 ? a < b : a > b;
        };
    }

    template <typename Value2>
    std::function<bool(Value2 a, Value2 b)> Larger() {
        return [](Value2 a, Value2 b) {
            return a > b;
        };
    }

    Range<Value> x_;
    Range<Value> y_;

};

}

