#pragma once

#include <array>

namespace boca
{

template<typename Value_>
using Array3 = std::array<Value_, 3>;

template<template <typename> class Vector_, typename Value_>
class GradedVector
{
public:
    GradedVector() {}
    GradedVector(Vector_<Value_> vector, Value_ scalar) {
        Set(vector, scalar);
    }
    void Set(Vector_<Value_> vector, Value_ scalar) {
        vector_ = vector;
        scalar_ = scalar;
    }
    void Set(Vector_<Value_> vector) {
        vector_ = vector;
    }
    void Set(Value_ scalar) {
        scalar_ = scalar;
    }
    Vector_<Value_>& Vector() {
        return vector_;
    }
    Value_& Scalar() {
        return scalar_;
    }
    Vector_<Value_> Vector() const {
        return vector_;
    }
    Vector_<double> Normalize() const {
        return vector_ / scalar_;
    }
    Value_ Scalar() const {
        return scalar_;
    }
    GradedVector& operator+=(GradedVector const& graded_vector) {
        vector_ += graded_vector.vector_;
        scalar_ += graded_vector.scalar_;
        return *this;
    }
    GradedVector operator+(GradedVector const& graded_vector) {
      return GradedVector(*this) += graded_vector;
    }
    bool operator==(GradedVector const& graded_vector) const {
        return vector_ == graded_vector.vector_ && scalar_ == graded_vector.scalar_;
    }
    bool operator!=(GradedVector const& graded_vector) const {
        return vector_ != graded_vector.vector_ || scalar_ != graded_vector.scalar_;
    }

private:
    Vector_<Value_> vector_;
    Value_ scalar_ = Value_(0);
};


}
