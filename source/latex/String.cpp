
#include <boost/algorithm/string/replace.hpp>

#include "boca/generic/Types.hh"
#include "boca/plotting/Font.hh"
#include "boca/latex/String.hh"
#include "boca/DetectorGeometry.hh"

// #define INFORMATION
#include "boca/generic/DEBUG.hh"

namespace boca
{

namespace latex
{

StringHelper::StringHelper(const std::string& string)
{
    INFO(string);
    string_ = string;
    formula_ = std::string(string).find("\\") == std::string::npos && std::string(string).find("^") == std::string::npos && std::string(string).find("_") == std::string::npos ? false : true;
}

StringHelper::StringHelper(const std::string& string, bool formula)
{
    INFO(string, formula);
    string_ = string;
    formula_ = formula;
}

bool StringHelper::Formula() const
{
    INFO0;
    return formula_;
}

std::string StringHelper::str() const
{
    INFO0;
    return string_;
}

std::string& StringHelper::str()
{
    INFO0;
    return string_;
}

namespace
{

std::string RootFormula(std::string const& string)
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
    case Medium::plain : return "Plain";
    case Medium::latex : return "Latex";
    case Medium::root : return "Root";
        DEFAULT(to_int(medium), "");
    }
}

String::String(const char* string)
{
    INFO(string);
    latex_strings_.emplace_back(string);
}

String::String(const std::string& string)
{
    INFO(string);
    latex_strings_.emplace_back(string);
}

String::String(const std::string& string, bool formula)
{
    INFO(string, formula);
    latex_strings_.emplace_back(string, formula);
}

std::string String::str(Medium medium) const
{
    INFO(Name(medium));
    std::string string;
    for (auto const & latex_string : latex_strings_) {
        if (latex_string.Formula()) switch (medium) {
            case Medium::latex : string += "$" + boost::replace_all_copy(latex_string.str(), "#", "\\") + "$";
                break;
            case Medium::root : string += RootFormula(boost::replace_all_copy(latex_string.str(), "\\", "#"));
                break;
            case Medium::plain : string += boost::replace_all_copy(boost::replace_all_copy(latex_string.str(), "\\", ""), "#", "");
                break;
            }
        else string += latex_string.str();
    }
    return string;
}

bool String::empty() const
{
    INFO0;
    return latex_strings_.empty();
}

String& String::operator+=(const String& latex)
{
    INFO0;
    for (auto const & latex_string : latex.latex_strings_) latex_strings_.emplace_back(latex_string);
    return *this;
}

String operator+(const char* string, const String& latex)
{
    INFO(string);
    auto copy = latex;
    copy.latex_strings_.emplace_front(string);
    return copy;
}

String String::operator+(String const& latex)
{
    INFO0;
    return *this += latex;
}

}

}
