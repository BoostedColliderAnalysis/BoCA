#pragma once

#include <iostream>

namespace boca
{

template<typename Value>
class Bounds
{
public:
    Bounds() {
        min_ = Value(0);
        max_ = Value(0);
    }
    Bounds(Value min, Value max) {
        min_ = min;
        max_ = max;
        CheckHierachy();
    }
    void SetMin(Value min) {
        min_ = min;
        CheckHierachy();
    }
    void SetMax(Value max) {
        max_ = max;
        CheckHierachy();
    }
    Value Min() const {
        return min_;
    }
    Value Max() const {
        return max_;
    }
    operator bool() const {
        return min_ != Value(0) && max_ != Value(0);
    }
    bool operator==(Bounds<Value> const& bounds) const {
        return bounds.min_ == min_ && bounds.max_ == max_;
    }
private:
    void CheckHierachy() {
        if (min_ != Value(0) && max_ != Value(0) && min_ > max_) std::cout << "Minimal value: " << min_ << " is greater than maximal value: " << max_ << std::endl;
    }
    Value min_;
    Value max_;
};

}
