/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include <vector>
#include <string>

namespace boca
{

/**
 * @ingroup Boca
 * @defgroup Colors Colors
 * @brief Color definitions for plotting
 * @{
 */

/**
* @brief %Color base
*
*/
class Color
{
public:
    Color();
protected:
    virtual std::vector<double> red() const;
    virtual std::vector<double> green() const;
    virtual std::vector<double> blue() const;
    virtual std::vector<double> Length() const;
    virtual std::vector<int> &Palette() = 0;
private:
    void Initialize();
    void SetPalette();
};

/**
* @brief %Red
*
*/
class Red
{
public:
    static std::string Action();
private:
    std::vector<double> red() const;
    std::vector<int> &Palette();
    static std::vector<int> palette_;
};

/**
* @brief %Blue
*
*/
class Blue
{
public:
    static std::string Action();
private:
    std::vector<double> blue() const;
    std::vector<int> &Palette();
    static std::vector<int> palette_;
};

/**
* @brief %Heat map colors
*
*/
class Heat
{
public:
    static std::string Action();
private:
    std::vector<double> red() const;
    std::vector<double> green() const;
    std::vector<double> blue() const;
    std::vector<double> Length() const;
    std::vector<int> &Palette();
    static std::vector<int> palette_;
};

}
