/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "Names.hh"
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
    std::vector<Vector3<float>> const& Data() const;
    std::vector<Vector3<float>> CoreData(std::function<bool (Vector3<float> const&, Vector3<float> const&)> const& function) const;
    void Add(Vector3<float> const& point);
    void Join(std::vector<Vector3<float>> const& data);
    bool x_is_int = false;
    bool y_is_int = false;
private:
    std::vector<Vector3<float>> data_;
    Names x_axis_;
    Names y_axis_;
    Names title_;
};

}
