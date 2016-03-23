#pragma once

#include <iostream>
#include <utility>
#include "physics/Units.hh"
#include "physics/Math.hh"

namespace boca
{

template<typename Value>
class Range
{
public:
    Range() :
        min_(InitialMin()),
        max_(InitialMax())
    {}

    Range(Value min, Value max) :
        min_(min),
        max_(max) {
        CheckHierachy();
    }

    template<typename Value_2>
    Range(Value_2 min, Value_2 max) :
        min_(Value(min)),
        max_(Value(max)) {
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

    void Set(Value min, Value max) {
        min_ = min;
        max_ = max;
        CheckHierachy();
    }

    void Set(std::pair<Value, Value> const pair) {
        min_ = pair.first;
        max_ = pair.second;
        CheckHierachy();
    }

    void Widen(Range<Value> const& bound) {
        WidenMin(bound.Min());
        WidenMax(bound.Max());
    }

    void WidenMin(Value min) {
        if (min > min_) return;
//         if (min == 0) return;
        min_ = min;
    }

    void WidenMax(Value max) {
        if (max < max_) return;
        max_ = max;
    }

    Value Min() const {
        return min_;
    }

    Value Max() const {
        return max_;
    }

    Value Floor() const {
        return FloorToDigits(min_);
    }

    Value Ceil() const {
        return CeilToDigits(max_);
    }

    bool Inside(Value value) {
        return value > min_ && value < max_;
    }

    bool Outside(Value value) {
        return value < min_ || value > max_;
    }

    template<typename Value_2>
    Value Constrain(Value_2 value) {
        if (Value(value) > Max()) value = Max();
        if (Value(value) < Min()) value = Min();
        return value;
    }

    Value Length() const {
        return max_ - min_;
    }

    operator bool() const {
        return min_ != InitialMin() && max_ != InitialMax();
    }

    //FIXME why is the return dimension for quantities not correct?
    template<typename Value2>
    friend Range<ValueQuotient<Value, Value2>> operator/(Range const& range, Value2 const& scalar) {
        return {range.Min() / scalar, range.Max() / scalar};
    }

    void Log() {
        if (min_ != Value(0)) min_ = std::log10(min_);
        if (max_ != Value(0)) max_ = std::log10(max_);
    }

private:
    void CheckHierachy() {
        if (min_ != InitialMin() && max_ != InitialMax() && min_ > max_) std::cout << "Minimal value: " << min_ << " is greater than maximal value: " << max_ << std::endl;
    }
    Value InitialMin() const {
        return std::numeric_limits<Value>::max();
    }
    Value InitialMax() const {
        return std::numeric_limits<Value>::lowest();
    }

    Value min_;
    Value max_;
};

template <typename Value>
Range<Value> MinMax(std::vector<Value> const& vector)
{
    auto minmax = std::minmax_element(vector.begin(), vector.end());
    return {*minmax.first, *minmax.second};
}

template <typename Iterator, typename Value>
Range<Value> MinMax(Iterator begin, Iterator end)
{
    auto minmax = std::minmax_element(begin, end);
    return {*minmax.first, *minmax.second};
}

}
