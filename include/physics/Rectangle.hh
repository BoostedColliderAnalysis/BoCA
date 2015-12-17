/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <boost/range/algorithm/max_element.hpp>
#include <boost/range/algorithm/min_element.hpp>

#include "physics/Vector2.hh"
#include "physics/Bounds.hh"

namespace boca
{

template<typename Value>
class Rectangle
{

public:

    Rectangle() {}

    Rectangle(Bounds<Value> x, Bounds<Value> y) :
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

    void SetX(Bounds<Value> const& x) {
        x_ = x;
    }

    void SetY(Bounds<Value> const& y) {
        y_ = y;
    }

    void ResetY() {
        y_ = Bounds<Value>();
    }

    void ResetX() {
        x_ = Bounds<Value>();
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

    void WidenX(Bounds<Value> const& x) {
        x_.Widen(x);
    }

    void WidenXMin(Value x_min) {
        x_.WidenMin(x_min);
    }

    void WidenXMax(Value x_max) {
        x_.WidenMax(x_max);
    }

    void WidenY(Bounds<Value> const& y) {
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

    Bounds<Value> const& Horizontal() const {
        return x_;
    }

    Bounds<Value> const& Vertical() const {
        return y_;
    }

    Value Width() const {
        return x_.Length();
    }

    Value Height() const {
        return y_.Length();
    }

    template <typename Value2>
    void WidenY(Bounds<Value> const& x, std::vector<Value2> const& xs, std::vector<Value2> const& ys) {
//         std::cout << x.Min() << "  " <<  x.Max() << std::endl;
//         for (auto & x : xs) std::cout << x << std::endl;
        int min_x;
        int max_x;
        if (std::is_sorted(xs.begin(), xs.end(), [](Value2 a, Value2 b) {
        return a < b;
    })) {
            std::cout << "smaller" << std::endl;
            min_x = boost::range::lower_bound(xs, Value2(x.Min())) - xs.begin();
            max_x = boost::range::upper_bound(xs, Value2(x.Max())) - xs.begin();
        } else
            if (std::is_sorted(xs.begin(), xs.end(), [](Value2 a, Value2 b) {
        return a > b;
            })) {
              y_.Widen( {*boost::range::min_element(ys), *boost::range::max_element(ys)});
              if(y_ == Bounds<Value>(0,0)) y_ = Bounds<Value>(0.001,1);
              return;
            std::cout << "larger" << std::endl;
            min_x = boost::range::upper_bound(xs, Value2(x.Max())) - xs.begin();
            max_x = boost::range::lower_bound(xs, Value2(x.Min())) - xs.begin();
        } else std::cout << "not sorted" << std::endl;
//         if (min_x == 0) min_x = boost::range::upper_bound(xs, Value2(x.Min()), [](Value2 a, Value2 b) {
//             return a > b;
//         }) - xs.begin();
//         if (max_x == 0) max_x = boost::range::upper_bound(xs, Value2(x.Max()), [](Value2 a, Value2 b) {
//             return a > b;
//         }) - xs.begin();
//         std::cout << min_x << "  " <<  max_x << std::endl;
        auto min = std::min_element(ys.begin() + min_x, ys.begin() + max_x, [](Value2 a, Value2 b) {
            return a != 0 ? a < b : a > b;
        });
        auto max = std::max_element(ys.begin() + min_x, ys.begin() + max_x);
//         std::for_each(ys.begin() + min_x, ys.begin() + max_x, [](auto & a) {
//             std::cout << a << std::endl;
//         });
//         std::cout << *min << "  " <<  *max << std::endl;
        y_.Widen( {std::min(*min, *max), std::max(*min, *max)});
        //FIXME remove this ugly hack
        if(y_ == Bounds<Value>(0,0)) y_ = Bounds<Value>(0.001,1);
    }

    template <typename Value2>
    void WidenX(Bounds<Value> const& y, std::vector<Value2> const& xs, std::vector<Value2> const& ys) {
        int min_y = boost::range::upper_bound(ys, Value2(y.Min())) - ys.begin();
        int max_y = boost::range::lower_bound(ys, Value2(y.Max())) - ys.begin();
        auto min = std::min_element(xs.begin() + min_y, xs.begin() + max_y, [](Value2 a, Value2 b) {
            return a != 0 ? a < b : a > b;
        });
        auto max = std::max_element(xs.begin() + min_y, xs.begin() + max_y);
        x_.Widen( {std::min(*min, *max), std::max(*min, *max)});
    }

private:

    Bounds<Value> x_;
    Bounds<Value> y_;

};

}

