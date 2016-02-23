/**
 * Copyright (C) 2015-2016 Jan Hajer
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

// #define INFORMATION
#include "Debug.hh"

namespace boca
{

namespace
{

float RepresentationWidth()
{
    return TextHeight() * 0.7;
}

float EntrySeparation()
{
    return TextHeight() / 3;
}

Vector2<float> Position(Orientation orientation, float width, float height)
{
    INFO(width, height);
//     CHECK(is(orientation, Orientation::left | Orientation::right), to_int(orientation), "Should the legend be placed on the left or on the right?");
//     CHECK(is(orientation, Orientation::top | Orientation::bottom), to_int(orientation), "Should the legend be placed at the top or at the bottom?");
//     CHECK(is(orientation, Orientation::inside | Orientation::outside), "Should the legend beplaced inside or outside?");
//     CHECK(orientation == Orientation::outside, "On which side should the legend be placed?");
    float x_shift = 0.5;
    float y_shift = 0.5;
    float x_offset = width / 2;
    float y_offset = height / 2;
    if (is(orientation, Orientation::outside)) {
        INFO("Outside");
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
            INFO("Inside");
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
    Vector2<float> min;
    float margin = TextHeight() / 2;
    if (is(orientation, Orientation::outside)) {
        INFO("Outside");
        min.SetX(-margin + x_shift - x_offset);
        min.SetY(-margin + y_shift - y_offset);
    } else {
        INFO("Inside");
        float x_unit = 1. - gPad->GetLeftMargin() - gPad->GetRightMargin() - 2. * margin;
        float y_unit = 1. - gPad->GetBottomMargin() - gPad->GetTopMargin() - 2. * margin;
        min.SetX(gPad->GetLeftMargin() + margin + x_shift * x_unit - x_offset);
        min.SetY(gPad->GetBottomMargin() + margin + y_shift * y_unit - y_offset);
    }
    return min;
}

}

float Legend::Width(std::vector<std::string> const& entries) const
{
    INFO(entries.size());
    TLatex longest(0, 0, boost::range::max_element(entries, [](std::string const & entry_1, std::string const & entry_2) {
        TLatex latex_1(0, 0, entry_1.c_str());
        SetText(latex_1);
        TLatex latex_2(0, 0, entry_2.c_str());
        SetText(latex_2);
        return latex_1.GetXsize() < latex_2.GetXsize();
    })->c_str());
    float extra_width = 0.3 * TextHeight();
    float width = longest.GetXsize() + RepresentationWidth() + extra_width;
    return width * columns_;  // TODO must be more sofisticated
}

float Legend::Height(std::vector<std::string> const& entries, std::string const& title) const
{
  INFO(entries.size(), title);
    float height = boost::accumulate(entries, 0., [](double height, std::string const & entry) {
        TLatex latex(0, 0, entry.c_str());
        SetText(latex);
        return height + latex.GetYsize();
    });
    height += (entries.size() - 1) * EntrySeparation();
    height /= columns_; // TODO must be more sofisticated
    if (title.empty()) return height;
    TLatex latex(0, 0, title.c_str());
    SetText(latex);
    height += latex.GetYsize();
    height += EntrySeparation();
    return height;
}

Legend::Legend(std::string const& title)
{
    INFO0;
    SetTitle(title);
}

Legend::Legend()
{
    INFO0;
}


Legend::Legend(boca::Rectangle<float> const& rectangle, std::string const& title)
{
    INFO0;
    SetCorners(rectangle);
    SetTitle(title);
}

Legend::Legend(Orientation orientation, std::vector<std::string> const& entries, std::string const& title)
{
    INFO0;
    SetOrientation(orientation, entries, title);
    SetTitle(title);
}

void Legend::Set(boca::Rectangle<float> const& rectangle, std::string const& title)
{
    INFO0;
    SetCorners(rectangle);
    SetTitle(title);
}

void Legend::SetOrientation(Orientation orientation, std::vector<std::string> const& entries, std::string const& title)
{
    INFO0;
    float width = Width(entries);
    float height = Height(entries, title);
    Vector2<float> min = Position(orientation, width, height);
    SetCorners(boca::Rectangle<float>(min, width, height));
}

void Legend::SetOrientation(Orientation orientation, std::string const& title)
{
    INFO0;
    std::vector<std::string> entries;
    auto list = legend_.GetListOfPrimitives()->MakeIterator();
    TLegendEntry* entry;
    while ((entry = static_cast<TLegendEntry*>(list->Next()))) entries.emplace_back(entry->GetLabel());
    SetOrientation(orientation, entries, title);
    SetTitle(title);
}

void Legend::Draw()
{
    INFO0;
    legend_.SetCornerRadius(TextHeight() / Rectangle().Width() / 6);
    legend_.SetBorderSize(0);
    legend_.SetLineWidth(0);
    legend_.Draw("arc");
}

void Legend::AddEntry(TObject const& object, std::string const& name)
{
    INFO0;
    legend_.AddEntry(&object, name.c_str(), "l");
}

void Legend::TwoColumn()
{
    INFO0;
    columns_ = 2;
    legend_.SetNColumns(2);
    legend_.SetColumnSeparation(0.2);
}

void Legend::SetCorners(boca::Rectangle<float> const& rectangle)
{
    INFO(rectangle.XMin(), rectangle.XMax(), rectangle.YMin(), rectangle.YMax());
    legend_.SetX1(rectangle.XMin());
    legend_.SetX2(rectangle.XMax());
    legend_.SetY1(rectangle.YMin());
    legend_.SetY2(rectangle.YMax());
    SetStyle();
}

void Legend::SetStyle()
{
    INFO0;
    SetText(legend_);
    legend_.SetFillColorAlpha(kWhite, 0.75);
    legend_.SetMargin(RepresentationWidth() / Rectangle().Width());
}

void Legend::SetTitle(std::string const& title)
{
    INFO0;
    if (title.empty()) return;
    legend_.SetHeader(title.c_str());
    SetText(static_cast<TLegendEntry&>(*legend_.GetListOfPrimitives()->First()));

}

Rectangle< double > Legend::Rectangle()
{
    return {legend_.GetX1(), legend_.GetX2(), legend_.GetY1(), legend_.GetY2()};
}

}
