/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include <string>
#include "physics/Vector3.hh"

namespace boca
{

class Names
{
public:
    std::string const& Name()const;
    std::string const& LatexName()const;
    void SetName(std::string const& name);
    void SetLatexName(std::string const& latex_name);
private:
    std::string name_;
    std::string latex_name_;
};

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
private:
    std::vector<Vector3<float>> data_;
    Names x_axis_;
    Names y_axis_;
    Names title_;
};

}
