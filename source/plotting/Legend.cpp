/**
 * Copyright (C) 2015 Jan Hajer
 */
#include <boost/range/algorithm/max_element.hpp>
#include <boost/range/numeric.hpp>

#include "TLegendEntry.h"
#include "TList.h"
#include "TLatex.h"
#include "TPad.h"
#include "TPave.h"

#include "Types.hh"
#include "plotting/Legend.hh"
#include "plotting/Style.hh"
#include "plotting/Font.hh"
#include "plotting/Result.hh"

namespace boca
{

namespace
{

float Width(std::vector<std::string> const& entries)
{
    TLatex longest(0, 0, boost::range::max_element(entries, [](std::string const & entry_1, std::string const & entry_2) {
        TLatex latex_1(0, 0, entry_1.c_str());
        SetText(latex_1);
        TLatex latex_2(0, 0, entry_2.c_str());
        SetText(latex_2);
        return latex_1.GetXsize() < latex_2.GetXsize();
    })->c_str());
    float image_width = TextSize() * 0.7;
    return longest.GetXsize() + image_width;
}

float Height(std::vector<std::string> const& entries, std::string const& title)
{
    float height = boost::accumulate(entries, 0., [](double height, std::string const & entry) {
        TLatex latex(0, 0, entry.c_str());
        SetText(latex);
        return height + latex.GetYsize();
    });
    height += (entries.size() - 1) * TextSize() / 3;
    if (title.empty()) return height;
    TLatex latex(0, 0, title.c_str());
    SetText(latex);
    height += latex.GetYsize();
    height += TextSize() / 3;
    return height;
}

Point Position(Orientation orientation, float width, float height)
{
    float x_shift = 0.5;
    float y_shift = 0.5;
    float x_offset = width / 2;
    float y_offset = height / 2;
    if (is(orientation, Orientation::inside)) {
        FlagSwitch(orientation, [&](Orientation orientation) {
            switch (orientation) {
            case Orientation::left:
                x_shift = 0;
                x_offset = width;
                break;
            case Orientation::right:
                x_shift = 1;
                x_offset = - width;
                break;
            case Orientation::top:
                y_shift = 1;
                y_offset = - height;
                break;
            case Orientation::bottom:
                y_shift = 0;
                y_offset = - height;
                break;
            default : break;
            }
        });
    } else {
        FlagSwitch(orientation, [&](Orientation orientation) {
            switch (orientation) {
            case Orientation::left:
                x_shift = 0;
                x_offset = 0;
                break;
            case Orientation::right:
                x_shift = 1;
                x_offset = width;
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
    }
    float margin = TextSize() / 2;
    float x_unit = 1. - gPad->GetLeftMargin() - gPad->GetRightMargin() - 2. * margin;
    float y_unit = 1. - gPad->GetBottomMargin() - gPad->GetTopMargin() - 2. * margin;
    Point min;
    min.x = gPad->GetLeftMargin() + margin + x_shift * x_unit - x_offset;
    min.y = gPad->GetBottomMargin() + margin + y_shift * y_unit - y_offset;
    return min;
}

}

Legend::Legend(const std::string& title)
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

void Legend::Set(Point const& min, float width, float height, std::string const& title)
{
    SetCorners(min, width, height);
    SetTitle(title);
    SetStyle();
}

void Legend::SetOrientation(Orientation orientation, std::vector<std::string> const& entries, std::string const& title)
{
    float width = Width(entries);
    float height = Height(entries, title);
    Point min = Position(orientation, width, height);
    SetCorners(min, width, height);
}

void Legend::SetOrientation(Orientation orientation, std::string const& title)
{
    std::vector<std::string> entries;
    auto list = legend_.GetListOfPrimitives()->MakeIterator();
    TLegendEntry* entry;
    while (entry = static_cast<TLegendEntry*>(list->Next())) entries.emplace_back(entry->GetLabel());
    SetOrientation(orientation, entries, title);
    SetTitle(title);
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
//     legend_.SetFillStyle(0);
    legend_.SetFillColorAlpha(kWhite, 0.75);

    SetText(legend_);
    legend_.SetCornerRadius(0.1);
    legend_.Draw("arc");
}

void Legend::SetTitle(const std::string& title)
{
    if (title.empty()) return;
    legend_.SetHeader(title.c_str());
    SetText(static_cast<TLegendEntry&>(*legend_.GetListOfPrimitives()->First()));

}

}
