#pragma once

#include "TCanvas.h"

#include "physics/Bounds.hh"

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
        if (bounds.Min() > Value(0) && bounds.Min() / bounds.Max() < 0.1) canvas_.SetLogy();
    }

    void SetLog();

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
