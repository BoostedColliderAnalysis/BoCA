#pragma once

#include <iostream>
#include "physics/Units.hh"
#include "physics/Math.hh"

namespace boca
{

template<typename Value>
class Bounds
{
public:
    Bounds() :
        min_(std::numeric_limits<Value>::max()),
        max_(std::numeric_limits<Value>::lowest())
    {}

    Bounds(Value min, Value max) :
        min_(min),
        max_(max) {
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

    void Update(Bounds<Value> const& bound) {
        UpdateMin(bound.Min());
        UpdateMax(bound.Max());
    }

    void UpdateMin(Value min) {
        if (min > min_) return;
        if (min == 0) return;
        min_ = min;
    }

    void UpdateMax(Value max) {
        if (max < max_) return;
        max_ = max;
    }

    Value Min() const {
        return min_;
    }

    Value Max() const {
        return max_;
    }

    Value Floor() const{
      return FloorToDigits(min_);
    }

    Value Ceil() const {
      return CeilToDigits(max_);
    }

    bool Inside(Value value){
      return value > min_ && value < max_;
    }

    Value Length() const {
        return max_ - min_;
    }

    operator bool() const {
        return min_ != std::numeric_limits<Value>::max() && max_ != std::numeric_limits<Value>::lowest();
    }

    //FIXME why is the return dimension for quantities not correct?
    template<typename Value2>
    friend Bounds<ValueQuotient<Value, Value2>> operator/(Bounds const& bounds, Value2 const& scalar) {
        return {Min() / scalar, Max() / scalar};
    }

private:
    void CheckHierachy() {
        if (min_ != std::numeric_limits<Value>::max() && max_ != std::numeric_limits<Value>::lowest() && min_ > max_) std::cout << "Minimal value: " << min_ << " is greater than maximal value: " << max_ << std::endl;
    }
    Value min_;
    Value max_;
};

template <typename Value>
Bounds<Value> MinMax(std::vector<Value> const& vector)
{
  auto minmax = std::minmax_element(vector.begin(), vector.end());
  return {*minmax.first, *minmax.second};
}

}
