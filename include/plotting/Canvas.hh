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
    void SetLog(Bounds<Value> const& bounds) {
        //       std::cout << bounds.Min() << " " <<  bounds.Max() <<std::endl;
        if (bounds.Min() > Value(0) && bounds.Min() / bounds.Max() < 0.1) canvas_.SetLogy();
    }

    template<typename Value>
    void SetLog(Rectangle<Value> const& bounds) {
        if (bounds.XMin() > Value(0) && bounds.XMin() / bounds.XMax() < 0.01) canvas_.SetLogx();
        if (bounds.YMin() > Value(0) && bounds.YMin() / bounds.YMax() < 0.01) canvas_.SetLogy();
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
