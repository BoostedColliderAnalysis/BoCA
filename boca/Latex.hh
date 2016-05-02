#pragma once

#include <string>
#include <deque>

namespace boca
{

enum class Medium
{
    plain,
    root,
    latex
};

std::string Name(Medium medium);

class LatexString
{

public:

    LatexString(std::string const& string = "");

    LatexString(std::string const& string, bool formula);

    bool Formula() const;

    std::string const& String() const;

    std::string & String();

private:

    std::string string_;

    bool formula_ = false;

};

class Latex
{

public:

    Latex() {}

    Latex(char const* string);

    Latex(std::string const& string);

    Latex(std::string const& string, bool formula);

    std::string str(Medium medium) const;

//     char const* c_str(Medium medium) const;

    bool empty() const;

    Latex& operator+=(Latex const& latex);

//     Latex& operator+=(std::string const& string);

    Latex operator+(Latex const& latex);

    friend Latex operator+(char const* string, Latex const& latex);

private:

    std::deque<LatexString> latex_strings_;

};

}
