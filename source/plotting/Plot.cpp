/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include <boost/range/algorithm/sort.hpp>

#include "plotting/Plot.hh"
#include "Vector.hh"
// #define DEBUG
#include "Debug.hh"

namespace boca
{

const Names& Plot::XAxis() const
{
    Info0;
    return x_axis_;
}

const Names& Plot::YAxis() const
{
    Info0;
    return y_axis_;
}

const Names& Plot::Title() const
{
    Info0;
    return title_;
}

Names& Plot::XAxis()
{
    Info0;
    return x_axis_;
}

Names& Plot::YAxis()
{
    Info0;
    return y_axis_;
}

Names& Plot::Title()
{
    Info0;
    return title_;
}

void Plot::Add(const Vector3< float >& point)
{
    Info0;
    data_.emplace_back(point);
}

const std::vector< Vector3< float > >& Plot::Data() const
{
    Info0;
    return data_;
}

void Plot::Join(const std::vector< Vector3< float > >& data)
{
    Info0;
    data_ = boca::Join(data_, data);
}

std::vector< Vector3< float > > Plot::CoreData(std::function<bool (Vector3<float> const&, Vector3<float> const&)> const& function) const
{
    Info0;
    std::vector<Vector3<float>> data = data_;
    boost::range::sort(data, [&](Vector3<float> const & a, Vector3<float> const & b) {
        return function(a, b);
    });
    int cut_off = data.size() / 25;
    data.erase(data.end() - cut_off, data.end());
    data.erase(data.begin(), data.begin() + cut_off);
    return data;
}

}
