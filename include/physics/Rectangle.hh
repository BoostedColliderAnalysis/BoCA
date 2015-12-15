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

    void UpdateX(Bounds<Value> const& x) {
        x_.Update(x);
    }

    void UpdateXMin(Value x_min) {
        x_.UpdateMin(x_min);
    }

    void UpdateXMax(Value x_max) {
        x_.UpdateMax(x_max);
    }

    void UpdateY(Bounds<Value> const& y) {
        y_.Update(y);
    }

    void UpdateYMin(Value y_min) {
        y_.UpdateMin(y_min);
    }

    void UpdateYMax(Value y_max) {
        y_.UpdateMax(y_max);
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

private:

    Bounds<Value> x_;
    Bounds<Value> y_;

};

}
