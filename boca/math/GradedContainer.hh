#pragma once

namespace boca
{

template<template <typename> class Container_, typename Value_>
class GradedContainer
{
public:
    GradedContainer() {}
    GradedContainer(Container_<Value_> vector, Value_ scalar) {
        Set(vector, scalar);
    }
    void Set(Container_<Value_> vector, Value_ scalar) {
        container_ = vector;
        scalar_ = scalar;
    }
    void Set(Container_<Value_> vector) {
        container_ = vector;
    }
    void Set(Value_ scalar) {
        scalar_ = scalar;
    }
    Container_<Value_>& Vector() {
        return container_;
    }
    Container_<Value_> Vector() const {
        return container_;
    }
    Container_<Value_>& Container() {
      return container_;
    }
    Container_<Value_> Container() const {
      return container_;
    }
    Container_<Value_>& Matrix() {
      return container_;
    }
    Container_<Value_> Matrix() const {
      return container_;
    }
    Container_<double> Normalize() const {
        return container_ / scalar_;
    }
    Value_ Scalar() const {
        return scalar_;
    }
    Value_& Scalar() {
        return scalar_;
    }
    GradedContainer& operator+=(GradedContainer const& graded_vector) {
        container_ += graded_vector.container_;
        scalar_ += graded_vector.scalar_;
        return *this;
    }
    GradedContainer operator+(GradedContainer const& graded_vector) {
      return *this += graded_vector;
    }
    bool operator==(GradedContainer const& graded_vector) const {
        return container_ == graded_vector.container_ && scalar_ == graded_vector.scalar_;
    }
    bool operator!=(GradedContainer const& graded_vector) const {
        return container_ != graded_vector.container_ || scalar_ != graded_vector.scalar_;
    }

private:
    Container_<Value_> container_;
    Value_ scalar_ = Value_(0);
};


}
