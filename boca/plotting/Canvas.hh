/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "TCanvas.h"

#include "boca/physics/Rectangle.hh"
#include "boca/generic/Debug.hh"

namespace boca
{

class Canvas
{

public:

    Canvas();

    Canvas(std::string const& path, std::string const& name, bool show_title = false);

    TCanvas const& canvas() const;

    TCanvas& canvas();

    template<typename Value>
    bool SetLog(Range<Value> const& range) {
        if(debug_) Debug("min: ", range.Min(), "max: ", range.Max());
        if (range.Min() < Value(0) || range.Min() / range.Max() > 50_mU) return false;
        if(debug_) Debug("set log", true);
        canvas_.SetLogy();
        return true;
    }

//     template<typename Value>
//     void SetLog(Rectangle<Value> const& range) {
//         if (range.XMin() > Value(0) && range.XMin() / range.XMax() < 0.02) canvas_.SetLogx();
//         if (range.YMin() > Value(0) && range.YMin() / range.YMax() < 0.02) canvas_.SetLogy();
//     }

    void SetLog();

    std::string SaveAs(std::string const& name);

    std::string FileName() const;

    virtual std::string FileBaseName() const;

    Canvas(Canvas const&) = default;

    Canvas(Canvas &&) = default;

    Canvas &operator=(Canvas const&) & = default;

    Canvas &operator=(Canvas &&) & = default;

protected :

    ~Canvas() {}

    std::string const& Title() const;

    std::string Path() const;

private:

    /**
     * @brief Make plot backgrounds transparent
     *
     */
    void Initialize();

    void SetMargins(bool show_title);

    TCanvas canvas_;

    std::string title_;

    std::string path_;

    bool debug_ = true;

};

}
