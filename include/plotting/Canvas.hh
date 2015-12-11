#pragma once

#include <string>
#include "TCanvas.h"

namespace boca
{

class Limits
{
public:
    Limits() {
        min_ = 0;
        max_ = 0;
    }
    Limits(float min, float max) {
        min_ = min;
        max_ = max;
    }
    void SetMin(float min) {
        min_ = min;
    }
    void SetMax(float max) {
        max_ = max;
    }
    float Min() const {
        return min_;
    }
    float Max() const {
        return max_;
    }
    operator bool() const {
        return min_ != 0. && max_ != 0.;
    }
    bool operator==(Limits const& limits) const {
        return limits.min_ == min_ && limits.max_ == max_;
    }
private:
    float min_;
    float max_;
};

class Canvas
{

public:

    Canvas(std::string const& path, std::string const& name, bool has_title = false);


    TCanvas const& canvas() const;

    TCanvas& canvas();

    void SetLog(float min = 0.001, float max = 1);

    void SetLog(Limits const& limits);

    std::string SaveAs(std::string const& name);

    std::string const& Title() const;

    std::string FileName() const;

protected:

    std::string path_;

    std::string title_;

private:

    /**
     * @brief Make plot backgrounds transparent
     *
     */
    void Fill();

    void SetMargins(bool has_title);

    TCanvas canvas_;

};

}
