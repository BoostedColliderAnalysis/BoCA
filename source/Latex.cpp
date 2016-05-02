
#include <boost/algorithm/string/replace.hpp>

#include "boca/generic/Types.hh"
#include "boca/plotting/Font.hh"
#include "boca/Latex.hh"
#include "boca/DetectorGeometry.hh"

// #define INFORMATION
#include "boca/generic/DEBUG.hh"

namespace boca
{

LatexString::LatexString(const std::string& string)
{
    INFO(string);
    string_ = string;
    formula_ = std::string(string).find("\\") == std::string::npos && std::string(string).find("^") == std::string::npos && std::string(string).find("_") == std::string::npos ? false : true;
}

LatexString::LatexString(const std::string& string, bool formula)
{
    INFO(string, formula);
    string_ = string;
    formula_ = formula;
}

bool LatexString::Formula() const
{
    INFO0;
    return formula_;
}

std::string const& LatexString::String() const
{
    INFO0;
    return string_;
}

std::string& LatexString::String()
{
    INFO0;
    return string_;
}

namespace
{

std::string Formula(std::string const& string)
{
    INFO(string);
    return "#font[" + std::to_string(FontCode(Style::italic)) + "]{" + string + "}";
}

// std::string Text(std::string const& text)
// {
//     return "#font[" + std::to_string(FontCode(Style::normal)) + "]{" + text + "}";
// }

}

std::string Name(Medium medium)
{
    INFO0;
    switch (medium) {
    case Medium::latex : return "Latex";
    case Medium::root : return "Root";
        DEFAULT(to_int(medium), "");
    }
}

Latex::Latex(const char* string)
{
    INFO(string);
    latex_strings_.emplace_back(string);
}

Latex::Latex(const std::string& string)
{
    INFO(string);
    latex_strings_.emplace_back(string);
}

Latex::Latex(const std::string& string, bool formula)
{
    INFO(string, formula);
    latex_strings_.emplace_back(string, formula);
}

std::string Latex::str(Medium medium) const
{
    INFO(Name(medium));
    std::string string;
    for (auto const & latex_string : latex_strings_) {
        if (latex_string.Formula()) switch (medium) {
            case Medium::latex : string += "$" + boost::replace_all_copy(latex_string.String(), "#", "\\") + "$";
                break;
            case Medium::root : string += Formula(boost::replace_all_copy(latex_string.String(), "\\", "#"));
            break;
            case Medium::plain : string += boost::replace_all_copy(boost::replace_all_copy(latex_string.String(), "\\", ""), "#", "");
            break;
            }
        else string += latex_string.String();
    }
    return string;
}

// const char* Latex::c_str(Medium medium) const
// {
//     INFO(Name(medium));
//     char const* c_str = str(medium).c_str();
//     ERROR(c_str);
//     std::cout << c_str << std::endl;
//     return c_str;
// }

bool Latex::empty() const
{
    INFO0;
    return latex_strings_.empty();
}

Latex& Latex::operator+=(const Latex& latex)
{
    INFO0;
    for (auto const & latex_string : latex.latex_strings_) latex_strings_.emplace_back(latex_string);
    return *this;
}

//Latex& Latex::operator+=(const std::string& string)
// {
//   INFO0;
//   latex_strings_.emplace_back(string);
//   return *this;
// }

Latex operator+(const char* string, const Latex& latex)
{
    INFO(string);
    auto copy = latex;
    copy.latex_strings_.emplace_front(string);
    return copy;
}

Latex Latex::operator+(Latex const& latex)
{
    INFO0;
    return *this += latex;
}

}
