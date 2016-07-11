#pragma once

#include <iostream>
#include <utility>
#include "boca/physics/Units.hh"
#include "boca/math/Math.hh"

namespace boca
{

template<typename Value_>
class Range
{
public:
    Range() :
        min_(InitialMin()),
        max_(InitialMax())
    {}

    Range(Value_ min, Value_ max) :
        min_(min),
        max_(max) {
        ImposeHierachy();
    }

    Range(Value_ degenerate) :
        min_(degenerate),
        max_(degenerate) {}

    template<typename Value_2_>
    Range(Value_2_ min, Value_2_ max) :
        min_(Value_(min)),
        max_(Value_(max)) {
        ImposeHierachy();
    }

    template<typename Value_2_>
    Range(Range<Value_2_> const& range) :
        min_(Value_(range.Min())),
        max_(Value_(range.Max())) {
        ImposeHierachy();
    }

    void SetMin(Value_ min) {
        min_ = min;
        ImposeHierachy();
    }

    void SetMax(Value_ max) {
        max_ = max;
        ImposeHierachy();
    }

    void Set(Value_ min, Value_ max) {
        min_ = min;
        max_ = max;
        ImposeHierachy();
    }

    void Set(std::pair<Value_, Value_> const pair) {
        min_ = pair.first;
        max_ = pair.second;
        ImposeHierachy();
    }

    void Widen(Range<Value_> const& bound) {
        WidenMin(bound.Min());
        WidenMax(bound.Max());
    }

    void Widen(double factor) {
        min_ /= factor;
        max_ *= factor;
    }

    void WidenMin(Value_ min) {
        if (min > min_) return;
        if (min == Value_(0)) return;
        min_ = min;
    }

    void WidenMax(Value_ max) {
        if (max < max_) return;
        max_ = max;
    }

    Value_ Min() const {
        return min_;
    }

    Value_ Max() const {
        return max_;
    }

    Value_ Floor() const {
        return FloorToDigits(min_);
    }

    Value_ Ceil() const {
        return CeilToDigits(max_);
    }

    bool Inside(Value_ value) {
        return value > min_ && value < max_;
    }

    bool Outside(Value_ value) {
        return value < min_ || value > max_;
    }

    template<typename Value_2_>
    Value_ Constrain(Value_2_ value) {
        if (Value_(value) > Max()) value = Max();
        if (Value_(value) < Min()) value = Min();
        return value;
    }

    Value_ Length() const {
        return max_ - min_;
    }

    Value_ Sum() const {
        return max_ + min_;
    }

    operator bool() const {
        return min_ != InitialMin() && max_ != InitialMax();
    }

    template<typename Value_2_>
    Range<ValueProduct<Value_, Value_2_>> Scale(Value_2_ const& scalar) const {
        return {Min()* scalar, Max()* scalar};
    }

    template<typename Value_2_>
    friend Range<ValueProduct<Value_, Value_2_>> operator*(Range const& range, Value_2_ const& scalar) {
        return range.Scale(scalar);
    }

    template<typename Value_2_>
    friend Range<ValueQuotient<Value_, Value_2_>> operator/(Range const& range, Value_2_ const& scalar) {
        return range.Scale(1. / scalar);
    }

    void Log() {
        if (min_ != Value_(0)) min_ = std::log10(min_);
        if (max_ != Value_(0)) max_ = std::log10(max_);
    }

private:
    void ImposeHierachy() {
        if (min_ != InitialMin() && max_ != InitialMax() && min_ > max_) std::swap(min_, max_);
    }
    Value_ InitialMin() const {
        return std::numeric_limits<Value_>::max();
    }
    Value_ InitialMax() const {
        return std::numeric_limits<Value_>::lowest();
    }

    Value_ min_;
    Value_ max_;
};

template <typename Value_>
Range<Value_> MinMax(std::vector<Value_> const& vector)
{
    auto minmax = std::minmax_element(vector.begin(), vector.end());
    return {*minmax.first, *minmax.second};
}

template <typename Iterator_, typename Value_>
Range<Value_> MinMax(Iterator_ begin, Iterator_ end)
{
    auto minmax = std::minmax_element(begin, end);
    return {*minmax.first, *minmax.second};
}

}
