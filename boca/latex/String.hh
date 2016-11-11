#pragma once

#include <string>
#include <deque>
#include <vector>

namespace boca
{

namespace latex
{

enum class Medium
{
    plain,
    root,
    latex
};

std::string Name(Medium medium);

class StringHelper
{

public:

    StringHelper(std::string const& string = "");

    StringHelper(std::string const& string, bool formula);

    bool Formula() const;

    std::string str() const;

    std::string& str();

private:

    std::string string_;

    bool formula_ = false;

};

class String
{

public:

    String() {}

    String(char const* string);

    String(std::string const& string);

    String(std::string const& string, bool formula);

    std::string str(Medium medium) const;

    bool empty() const;

    String& operator+=(String const& latex);

    String operator+(String const& latex);

    friend String operator+(char const* string, String const& latex);

private:

    std::deque<StringHelper> latex_strings_;

};

String operator "" _TeX(char const*, size_t);

class Formula
{

public:

    template<typename... Arguments_>
    Formula(Arguments_ ...arguments) {
        Set(arguments...);
    }

    std::string str();

    operator std::string();

private:

    template<typename... Arguments_>
    void Set(std::string const& string, Arguments_ ... arguments) {
        strings_.emplace_back(string);
        Set(arguments...);
    }

    void Set() {};

    std::vector<std::string> strings_;

};

}

using Latex = latex::String;

using LatexString = latex::StringHelper;

}
