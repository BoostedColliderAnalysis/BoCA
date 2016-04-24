/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include <boost/range/algorithm/sort.hpp>
#include <boost/range/algorithm/transform.hpp>

#include "boca/plotting/Plot.hh"
#include "boca/generic/Vector.hh"
// #define DEBUGGING
#include "boca/generic/DEBUG.hh"

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

void Plot::Add(const Vector3< double >& point)
{
    INFO0;
    data_.emplace_back(point);
}

const std::vector< Vector3< double > >& Plot::Data() const
{
    INFO0;
    return data_;
}

void Plot::Insert(std::vector<Vector3<double>> const& data)
{
    INFO0;
    boca::Insert(data_, data);
}

std::vector< Vector3< double > > Plot::CoreData(std::function<bool (Vector3<double> const&, Vector3<double> const&)> const& function) const
{
    INFO0;
    auto data = data_;
    boost::range::sort(data, [&](Vector3<double> const & a, Vector3<double> const & b) {
        return function(a, b);
    });
    int cut_off = data.size() / 25;
    data.erase(data.end() - cut_off, data.end());
    data.erase(data.begin(), data.begin() + cut_off);
    return data;
}
std::vector< double > Plot::XData() const
{
    std::vector<double> x_data(data_.size());
    boost::range::transform(data_, std::back_inserter(x_data), [](Vector3<double> const & vector) {
        return vector.X();
    });
    return x_data;
}
boca::Range< double > Plot::XRange() const
{
    return MinMax(XCoreData());
}
std::vector< double > Plot::XCoreData() const
{
  INFO0;
  auto data = XData();
  boost::range::sort(data);
  int cut_off = data.size() / 25;
  data.erase(data.end() - cut_off, data.end());
  data.erase(data.begin(), data.begin() + cut_off);
  return data;
}

}
