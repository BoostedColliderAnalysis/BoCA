/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "TCanvas.h"

#include "physics/Rectangle.hh"

namespace boca
{

class Canvas
{

public:

    Canvas(std::string const& path, std::string const& name, bool show_title = false);

    TCanvas const& canvas() const;

    TCanvas& canvas();

    template<typename Value>
    void SetLog(Range<Value> const& range) {
        //       std::cout << range.Min() << " " <<  range.Max() <<std::endl;
        if (range.Min() > Value(0) && range.Min() / range.Max() < 0.1) canvas_.SetLogy();
    }

    template<typename Value>
    void SetLog(Rectangle<Value> const& range) {
        if (range.XMin() > Value(0) && range.XMin() / range.XMax() < 0.01) canvas_.SetLogx();
        if (range.YMin() > Value(0) && range.YMin() / range.YMax() < 0.01) canvas_.SetLogy();
    }

    void SetLog();

    std::string SaveAs(std::string const& name);

    std::string FileName() const;

    virtual std::string FileBaseName() const;

protected :

    std::string const& Title() const;

    std::string Path() const;

private:

    /**
     * @brief Make plot backgrounds transparent
     *
     */
    void Fill();

    void SetMargins(bool show_title);

    TCanvas canvas_;

    std::string title_;

    std::string path_;

};

}
