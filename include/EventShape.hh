#pragma once

#include "physics/Vector3.hh"

namespace boca
{

template<typename Value_>
class EventShape
{
public:
    EventShape() {}
    EventShape(Vector3<Value_> vector, Value_ scalar) {
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
    Vector3<Value_> const& Vector() const {
        return vector_;
    }
    Value_ const& Scalar() const {
        return scalar_;
    }
    EventShape& operator+=(EventShape<Value_> const& event_shape) {
        vector_ += event_shape.Vector();
        scalar_ += event_shape.Scalar();
        return *this;
    }
private:
    Vector3<Value_> vector_;
    Value_ scalar_ = Value_(0);
};

}
