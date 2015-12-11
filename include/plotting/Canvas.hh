#pragma once

#include <string>
#include "TCanvas.h"

namespace boca
{

template<typename Value>
class Limits
{
public:
    Limits() {
        min_ = 0;
        max_ = 0;
    }
    Limits(Value min, Value max) {
        min_ = min;
        max_ = max;
    }
    void SetMin(Value min) {
        min_ = min;
    }
    void SetMax(Value max) {
        max_ = max;
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
    bool operator==(Limits<Value> const& limits) const {
        return limits.min_ == min_ && limits.max_ == max_;
    }
private:
    Value min_;
    Value max_;
};

class Canvas
{

public:

    Canvas(std::string const& path, std::string const& name, bool show_title = false);

    TCanvas const& canvas() const;

    TCanvas& canvas();

    template<typename Value>
    void SetLog(Limits<Value> const& limits)
    {
      if (!limits || (limits.Min() > Value(0) && limits.Min() / limits.Max() < 0.1)) canvas_.SetLogy();
    }

    std::string SaveAs(std::string const& name);

    std::string FileName() const;

protected :

    std::string const& Title() const;

private:

    /**
     * @brief Make plot backgrounds transparent
     *
     */
    void Fill();

    void SetMargins(bool show_title);

    TCanvas canvas_;

    std::string path_;

    std::string title_;

};

}
