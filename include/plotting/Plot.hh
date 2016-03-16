/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "Names.hh"
#include "physics/Range.hh"
#include "physics/Vector3.hh"

namespace boca
{

class Plot
{
public:
    Names const& XAxis()const;
    Names const& YAxis()const;
    Names const& Title()const;
    Names& XAxis();
    Names& YAxis();
    Names& Title();
    std::vector<Vector3<double>> const& Data() const;
    std::vector<double> XData() const;
    std::vector<double> XCoreData() const;
    std::vector<Vector3<double>> CoreData(std::function<bool (Vector3<double> const&, Vector3<double> const&)> const& function) const;
    void Add(Vector3<double> const& point);
    void Insert(std::vector<Vector3<double>> const& data);
    bool x_is_int = false;
    bool y_is_int = false;
    Range<double> XRange() const;
private:
    std::vector<Vector3<double>> data_;
    Names x_axis_;
    Names y_axis_;
    Names title_;
};

}
