/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include <boost/range/algorithm/sort.hpp>
#include <boost/range/algorithm/transform.hpp>

#include "plotting/Plot.hh"
#include "Vector.hh"
// #define DEBUGGING
#include "Debug.hh"

namespace boca
{

const Names& Plot::XAxis() const
{
    INFO0;
    return x_axis_;
}

const Names& Plot::YAxis() const
{
    INFO0;
    return y_axis_;
}

const Names& Plot::Title() const
{
    INFO0;
    return title_;
}

Names& Plot::XAxis()
{
    INFO0;
    return x_axis_;
}

Names& Plot::YAxis()
{
    INFO0;
    return y_axis_;
}

Names& Plot::Title()
{
    INFO0;
    return title_;
}

void Plot::Add(const Vector3< float >& point)
{
    INFO0;
    data_.emplace_back(point);
}

const std::vector< Vector3< float > >& Plot::Data() const
{
    INFO0;
    return data_;
}

void Plot::Join(const std::vector< Vector3< float > >& data)
{
    INFO0;
    data_ = boca::Join(data_, data);
}

std::vector< Vector3< float > > Plot::CoreData(std::function<bool (Vector3<float> const&, Vector3<float> const&)> const& function) const
{
    INFO0;
    std::vector<Vector3<float>> data = data_;
    boost::range::sort(data, [&](Vector3<float> const & a, Vector3<float> const & b) {
        return function(a, b);
    });
    int cut_off = data.size() / 25;
    data.erase(data.end() - cut_off, data.end());
    data.erase(data.begin(), data.begin() + cut_off);
    return data;
}
std::vector< float > Plot::XData() const
{
    std::vector<float> x_data(data_.size());
    boost::range::transform(data_, std::back_inserter(x_data), [](Vector3<float> const & vector) {
        return vector.X();
    });
    return x_data;
}
boca::Range< float > Plot::XRange() const
{
    return MinMax(XCoreData());
}
std::vector< float > Plot::XCoreData() const
{
  INFO0;
  std::vector<float> data = XData();
  boost::range::sort(data);
  int cut_off = data.size() / 25;
  data.erase(data.end() - cut_off, data.end());
  data.erase(data.begin(), data.begin() + cut_off);
  return data;
}

}
