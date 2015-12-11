/**
 * Copyright (C) 2015 Jan Hajer
 */
#include <boost/range/algorithm/max_element.hpp>
#include <boost/range/numeric.hpp>

#include "TLegendEntry.h"
#include "TList.h"
#include "TLatex.h"
#include "TPad.h"

#include "Types.hh"
#include "plotting/Legend.hh"
#include "plotting/Style.hh"
#include "plotting/Font.hh"
#include "plotting/Result.hh"

namespace boca
{

Legend::Legend(const std::__cxx11::string& title)
{
    SetTitle(title);
    SetStyle();
}

Legend::Legend()
{
    SetStyle();
}


Legend::Legend(Point const& min, float width, float height, std::string const& title)
{
    SetCorners(min, width, height);
    SetTitle(title);
    SetStyle();
}

Legend::Legend(Orientation orientation, std::vector<std::string> const& entries, std::string const& title)
{
    SetOrientation(orientation, entries, title);
    SetTitle(title);
    SetStyle();
}

void Legend::SetOrientation(Orientation orientation, std::vector<std::string> const& entries, std::string const& title)
{
    //     std::vector<TLatex> latexes;
    //     for (auto const& entry : entries) {
    //         TLatex latex(0, 0, entry.c_str());
    //         SetTextStyle(latex);
    //         latexes.emplace_back(latex);
    //     }
    //     TLatex longest = *boost::range::max_element(latexes, [](TLatex & latex_1, TLatex & latex_2) {
    //         return latex_1.GetXsize() < latex_2.GetXsize();
    //     });

    TLatex longest(0, 0, boost::range::max_element(entries, [](std::string const & entry_1, std::string const & entry_2) {
        TLatex latex_1(0, 0, entry_1.c_str());
        SetTextStyle(latex_1);
        TLatex latex_2(0, 0, entry_2.c_str());
        SetTextStyle(latex_2);
        return latex_1.GetXsize() < latex_2.GetXsize();
    })->c_str());

    float image_width = TextSize() * 2;
    float width = longest.GetXsize() + image_width;

    float height = boost::accumulate(entries, 0., [](double height, std::string const & entry) {
        TLatex latex(0, 0, entry.c_str());
        SetTextStyle(latex);
        return height + latex.GetYsize();
    });
    height += (entries.size() - 1) * TextSize() / 2;

    if (!title.empty()) {
        TLatex latex(0, 0, title.c_str());
        SetTextStyle(latex);
        height += latex.GetYsize();
        height += TextSize() / 2;
    }
    // default values for Orientation::center
    float x_shift = 0.5;
    float y_shift = 0.5;
    float x_offset = width / 4; // FIXME why is this necessary; why not 1/2?
    float y_offset = height / 2;
    FlagSwitch(orientation, [&](Orientation orientation) {
        switch (orientation) {
        case Orientation::left:
            x_shift = 0;
            x_offset = 0;
            break;
        case Orientation::right:
            x_shift = 1;
            x_offset = width / 2; // FIXME why is this necessary; why not 1?
            break;
        case Orientation::top:
            y_shift = 1;
            y_offset = height;
            break;
        case Orientation::bottom:
            y_shift = 0;
            y_offset = 0;
            break;
        default : break;
        }
    });
    float margin = TextSize() / 2;
    float x_unit = 1. - gPad->GetLeftMargin() - gPad->GetRightMargin() - 2. * margin;
    float y_unit = 1. - gPad->GetBottomMargin() - gPad->GetTopMargin() - 2. * margin;
    Point min;
    min.x = gPad->GetLeftMargin() + margin + x_shift * x_unit - x_offset;
    min.y = gPad->GetBottomMargin() + margin + y_shift * y_unit - y_offset;
    SetCorners(min, width, height);

}

void Legend::SetOrientation(Orientation orientation, std::string const& title)
{
    std::vector<std::string> entries;
    auto list = legend_.GetListOfPrimitives()->MakeIterator();
    TLegendEntry * entry;
    while(entry = static_cast<TLegendEntry *>(list->Next())) entries.emplace_back(entry->GetLabel());
    SetOrientation(orientation, entries, title);
}

void Legend::Draw()
{
    legend_.Draw();
}

void Legend::AddEntry(TObject const& object, std::string const& name)
{
    legend_.AddEntry(&object, name.c_str(), "l");
}

void Legend::TwoColumn()
{
    legend_.SetNColumns(2);
    legend_.SetColumnSeparation(0.2);
}

void Legend::SetCorners(Point const& min, float width, float height)
{
    legend_.SetX1(min.x);
    legend_.SetX2(min.x + width);
    legend_.SetY1(min.y);
    legend_.SetY2(min.y + height);
}

void Legend::SetStyle()
{
    legend_.SetBorderSize(0);
    legend_.SetFillStyle(0);
    //     legend.SetFillColorAlpha(kWhite, 0.1);
    SetTextStyle(legend_);
    legend_.Draw();
}

void Legend::SetTitle(const std::__cxx11::string& title)
{
    if (!title.empty()) {
        legend_.SetHeader(title.c_str());
        SetTextStyle(static_cast<TLegendEntry&>(*legend_.GetListOfPrimitives()->First()));
    }
}
}
