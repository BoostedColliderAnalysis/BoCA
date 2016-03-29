#pragma once

#include "physics/Vector3.hh"

namespace boca
{

template<typename Value_>
class GradedVector
{
public:
    GradedVector() {}
    GradedVector(Vector3<Value_> vector, Value_ scalar) {
        Set(vector, scalar);
    }
    void Set(Vector3<Value_> vector, Value_ scalar) {
        vector_ = vector;
        scalar_ = scalar;
    }
    void Set(Vector3<Value_> vector) {
        vector_ = vector;
    }
    void Set(Value_ scalar) {
        scalar_ = scalar;
    }
    Vector3<Value_>& Vector() {
        return vector_;
    }
    Value_& Scalar() {
        return scalar_;
    }
    Vector3<Value_> Vector() const {
        return vector_;
    }
    Value_ Scalar() const {
        return scalar_;
    }
    GradedVector& operator+=(GradedVector<Value_> const& graded_vector) {
        vector_ += graded_vector.vector_;
        scalar_ += graded_vector.scalar_;
        return *this;
    }
    bool operator==(GradedVector<Value_> const& graded_vector) {
        return vector_ == graded_vector.vector_ && scalar_ == graded_vector.scalar_;
    }
    bool operator!=(GradedVector<Value_> const& graded_vector) {
      return vector_ != graded_vector.vector_ || scalar_ != graded_vector.scalar_;
    }

private:
    Vector3<Value_> vector_;
    Value_ scalar_ = Value_(0);
};

}
