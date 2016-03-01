/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <vector>
#include <string>

namespace boca
{

class Color
{
public:
    Color();
protected:
    virtual std::vector<double> red() const;
    virtual std::vector<double> green() const;
    virtual std::vector<double> blue() const;
    virtual std::vector<double> Length() const;
    virtual std::vector<int>& Palette() = 0;
private:
    void Initialize();
    void SetPalette();
};

class Red
{
public:
    static std::string Action();
private:
    std::vector<double> red() const;
    std::vector<int>& Palette();
    static std::vector<int> palette_;
};

class Blue
{
public:
    static std::string Action();
private:
    std::vector<double> blue() const;
    std::vector<int>& Palette();
    static std::vector<int> palette_;
};

class Heat
{
public:
    static std::string Action();
private:
    std::vector<double> red() const;
    std::vector<double> green() const;
    std::vector<double> blue() const;
    std::vector<double> Length() const;
    std::vector<int>& Palette();
    static std::vector<int> palette_;
};

// class Color
// {
// public:
//     void Red();
//     void Blue();
//     void Heat();
// };

}
