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

#include "boca/generic/Types.hh"
#include "boca/plotting/Legend.hh"
#include "boca/plotting/Style.hh"
#include "boca/plotting/Font.hh"

// #define INFORMATION
#include "boca/generic/DEBUG.hh"

namespace boca
{

namespace
{

double RepresentationWidth()
{
    return TextHeight() * 0.7;
}

double EntrySeparation()
{
    return TextHeight() / 3;
}

Vector2<double> Position(Orientation orientation, double width, double height)
{
    INFO(width, height);
//     CHECK(is(orientation, Orientation::left | Orientation::right), to_int(orientation), "Should the legend be placed on the left or on the right?");
//     CHECK(is(orientation, Orientation::top | Orientation::bottom), to_int(orientation), "Should the legend be placed at the top or at the bottom?");
//     CHECK(is(orientation, Orientation::inside | Orientation::outside), "Should the legend beplaced inside or outside?");
//     CHECK(orientation == Orientation::outside, "On which side should the legend be placed?");
    auto x_shift = 0.5;
    auto y_shift = 0.5;
    auto x_offset = width / 2;
    auto y_offset = height / 2;
    INFO(Name(orientation));
    if (is(orientation, Orientation::outside)) {
        INFO("Outside");
        FlagSwitch(orientation, [&](Orientation orientation_1) {
            switch (orientation_1) {
            case Orientation::left:
                x_shift = 0;
                x_offset = width;
                break;
            case Orientation::right:
                x_shift = 1;
                x_offset = width;
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
        FlagSwitch(orientation, [&](Orientation orientation_1) {
            INFO("Inside");
            switch (orientation_1) {
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
    Vector2<double> min;
    auto margin = TextHeight() / 2;
    if (is(orientation, Orientation::outside)) {
        INFO("Outside");
        min.SetX(-margin + x_shift - x_offset);
        min.SetY(-margin + y_shift - y_offset);
    } else {
        INFO("Inside");
        auto x_unit = 1. - gPad->GetLeftMargin() - gPad->GetRightMargin() - 2. * margin;
        auto y_unit = 1. - gPad->GetBottomMargin() - gPad->GetTopMargin() - 2. * margin;
        min.SetX(gPad->GetLeftMargin() + margin + x_shift * x_unit - x_offset);
        min.SetY(gPad->GetBottomMargin() + margin + y_shift * y_unit - y_offset);
    }
    INFO(min.X(), min.Y());
    return min;
}

}

double Legend::Width(std::vector<latex::String> const& entries) const
{
    INFO(entries.size());
    TLatex longest(0, 0, boost::range::max_element(entries, [](latex::String const & entry_1, latex::String const & entry_2) {
        TLatex latex_1(0, 0, entry_1.str(latex::Medium::root).c_str());
        SetText(latex_1);
        TLatex latex_2(0, 0, entry_2.str(latex::Medium::root).c_str());
        SetText(latex_2);
        return latex_1.GetXsize() < latex_2.GetXsize();
    })->str(latex::Medium::root).c_str());
    auto extra_width = 0.5 * TextHeight();
    auto width = longest.GetXsize() + RepresentationWidth() + extra_width;
    return width * columns_;  // TODO must be more sofisticated
}

double Legend::Height(std::vector<latex::String> const& entries, latex::String const& title) const
{
    INFO(entries.size(), title.str(latex::Medium::root));
    auto height = boost::accumulate(entries, 0., [](double & sum, latex::String const & entry) {
        TLatex latex(0, 0, entry.str(latex::Medium::root).c_str());
        SetText(latex);
        INFO(entry.str(latex::Medium::root), latex.GetYsize());
        return sum + latex.GetYsize();
    });
    INFO(height);
    height += (entries.size() - 1) * EntrySeparation();
    height /= columns_; // TODO must be more sofisticated
    INFO(height);
    if (title.empty()) return height;
    TLatex latex(0, 0, title.str(latex::Medium::root).c_str());
    SetText(latex);
    height += latex.GetYsize();
    height += EntrySeparation();
    return height;
}

Legend::Legend(latex::String const& title)
{
    INFO0;
    SetTitle(title);
}

Legend::Legend()
{
    INFO0;
}


Legend::Legend(boca::Rectangle<double> const& rectangle, latex::String const& title)
{
    INFO0;
    SetCorners(rectangle);
    SetTitle(title);
}

Legend::Legend(Orientation orientation, std::vector<latex::String> const& entries, latex::String const& title)
{
    INFO0;
    SetOrientation(orientation, entries, title);
    SetTitle(title);
}

void Legend::Set(boca::Rectangle<double> const& rectangle, latex::String const& title)
{
    INFO0;
    SetCorners(rectangle);
    SetTitle(title);
}

void Legend::SetOrientation(Orientation orientation, std::vector<latex::String> const& entries, latex::String const& title)
{
    INFO0;
    auto width = Width(entries);
    auto height = Height(entries, title);
    auto min = Position(orientation, width, height);
    SetCorners(boca::Rectangle<double>(min, width, height));
}

void Legend::SetOrientation(Orientation orientation, latex::String const& title)
{
    INFO0;
    if (!legend_.GetListOfPrimitives()) return;
    std::vector<latex::String> entries;
    auto list = legend_.GetListOfPrimitives()->MakeIterator();
    TLegendEntry* entry;
    while ((entry = static_cast<TLegendEntry*>(list->Next()))) entries.emplace_back(entry->GetLabel());
    SetOrientation(orientation, entries, title);
    SetTitle(title);
}

void Legend::Draw()
{
    INFO0;
    if (!legend_.GetListOfPrimitives() || legend_.GetListOfPrimitives()->GetSize() == 0) return;
    legend_.SetCornerRadius(TextHeight() / Rectangle().Width() / 6);
    legend_.SetBorderSize(0);
    legend_.SetLineWidth(0);
    legend_.Draw("arc");
}

void Legend::AddEntry(TObject const& object, latex::String const& name)
{
    INFO(name.str(latex::Medium::root));
    legend_.AddEntry(&object, name.str(latex::Medium::root).c_str(), "l");
}

void Legend::AddEntry(TObject const& object, char const* name)
{
    INFO(name);
    legend_.AddEntry(&object, name, "l");
}

void Legend::TwoColumn()
{
    INFO0;
    columns_ = 2;
    legend_.SetNColumns(columns_);
    legend_.SetColumnSeparation(0.2);
}

void Legend::SetCorners(boca::Rectangle<double> const& rectangle)
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

void Legend::SetTitle(latex::String const& title)
{
    INFO0;
    if (title.empty()) return;
    legend_.SetHeader(title.str(latex::Medium::root).c_str());
    SetText(static_cast<TLegendEntry&>(*legend_.GetListOfPrimitives()->First()));

}

Rectangle< double > Legend::Rectangle()
{
    return {legend_.GetX1(), legend_.GetX2(), legend_.GetY1(), legend_.GetY2()};
}

}
