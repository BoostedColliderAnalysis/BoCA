/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "physics/Vector2.hh"
#include "physics/Bounds.hh"

namespace boca
{

template<typename Value>
class Rectangle
{

public:

    Rectangle() {
        x_min_ = Value(0);
        x_max_ = Value(0);
        y_min_ = Value(0);
        y_max_ = Value(0);
    }

    Rectangle(Bounds<Value> x, Bounds<Value> y) {
        x_min_ = x.Min();
        x_max_ = x.Max();
        y_min_ = y.Min();
        y_max_ = y.Max();
    }

    Rectangle(Vector2<Value> min, Vector2<Value> max) {
        x_min_ = min.X();
        x_max_ = max.X();
        y_min_ = min.Y();
        y_max_ = max.Y();
        CheckHierachy();
    }

    Rectangle(Vector2<Value> min, Value width, Value height) {
        x_min_ = min.X();
        x_max_ = min.X() + width;
        y_min_ = min.Y();
        y_max_ = min.Y() + height;
        CheckHierachy();
    }

    Rectangle(Value x_min, Value x_max, Value y_min, Value y_max) {
        x_min_ = x_min;
        x_max_ = x_max;
        y_min_ = y_min;
        y_max_ = y_max;
        CheckHierachy();
    }

    Value const& XMin() const {
        return x_min_;
    }

    Value const& XMax() const {
        return x_max_;
    }

    Value const& YMin() const {
        return y_min_;
    }

    Value const& YMax() const {
        return y_max_;
    }

    Vector2<Value> Min() const {
        return {x_min_, y_min_};
    }

    Vector2<Value> Max() const {
        return {x_max_, y_max_};
    }

    Bounds<Value> Horizontal() const {
        return {x_min_, x_max_};
    }

    Bounds<Value> Vertical() const {
        return {y_min_, y_max_};
    }

    Value Width() const {
        return x_max_ - x_min_;
    }

    Value Height() const {
        return y_max_ - y_min_;
    }

    void SetXMin(Value x_min) {
        x_min_ = x_min;
        CheckHierachy();
    }

    void SetXMax(Value x_max) {
        x_max_ = x_max;
        CheckHierachy();
    }

    void SetYMin(Value y_min) {
        y_min_ = y_min;
        CheckHierachy();
    }

    void SetYMax(Value y_max) {
        y_max_ = y_max;
        CheckHierachy();
    }

private:

    void CheckHierachy() {
        if (x_min_ != Value(0) && x_max_ != Value(0) && x_min_ > x_max_) std::cout << "Minimal x value: " << x_min_ << " is greater than maximal x value: " << x_max_ << std::endl;
        if (y_min_ != Value(0) && y_max_ != Value(0) && y_min_ > y_max_) std::cout << "Minimal y value: " << y_min_ << " is greater than maximal y value: " << y_max_ << std::endl;
    }
    Value x_min_;
    Value y_min_;
    Value x_max_;
    Value y_max_;

};

}
