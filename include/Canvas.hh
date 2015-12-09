#pragma once

#include <string>
#include "TCanvas.h"

namespace boca
{

class Canvas
{

public:

    Canvas();

    TCanvas& canvas();

    void SetLog(float min = 0.001, float max = 1);

    std::string SaveAs(std::string const& name);

private:

    /**
     * @brief Make plot backgrounds transparent
     *
     */
    void Fill();

    void SetMargin();

    std::string ExportFileSuffix() const;

    TCanvas canvas_;

};

}
