/**
 * Copyright (C) 2015 Jan Hajer
 */
#include <iomanip>
#include <boost/units/systems/si/io.hpp>
#include "fastjet/PseudoJet.hh"
#include "Debug.hh"

namespace boca {

std::string Shorten(std::string const& pretty_function, size_t brake)
{
    size_t begin1 = pretty_function.substr(0, brake).rfind(" ") + 1;
    size_t begin2 = pretty_function.substr(0, brake).rfind("::") + 1; // TODO should be +2 but corner case prevents it, hence the hack in the second last line
    size_t begin = std::max(begin1, begin2);
    size_t end = brake - begin;
    std::string name = pretty_function.substr(begin, end);
    name.erase(std::remove(name.begin(), name.end(), ':'), name.end());
    return name;
}

std::string Shorten2(std::string const& pretty_function, size_t brake)
{
    size_t colons = pretty_function.substr(0, brake).rfind("::");
    return (colons == std::string::npos) ? "::" : Shorten(pretty_function, colons);
}

std::string NameSpaceName(std::string const& pretty_function)
{
    size_t bracket = pretty_function.find("(");
    size_t colons = pretty_function.substr(0, bracket).rfind("::");
    return Shorten2(pretty_function, colons);
}

std::string ClassName(std::string const& pretty_function)
{
    size_t bracket = pretty_function.find("(");
    return Shorten2(pretty_function, bracket);
}

std::string FunctionName(std::string const& pretty_function)
{
    size_t bracket = pretty_function.find("(");
    return Shorten(pretty_function, bracket);
}

std::string FileName(std::string const& file)
{
    std::string name = file.rfind('/') ? file.substr(file.rfind('/') + 1) : file;
    return name.substr(0, name.find('.'));
}

int ValueLength()
{
    return 20;
}

void Log(std::string const& file, int line, std::string const& NameSpace, std::string const& Class, std::string const& function, bool final)
{
    std::cout << Column(25, file) << ColumnRight(3, line) << " " << Column(15, NameSpace) << Column(18, Class) << Column(20, function);
    if (final)
        std::cout << "\n";
}

void LogVariable(std::string const& variable, fastjet::PseudoJet const& jet)
{
    std::cout << Column(ValueLength(), variable) << Column(ValueLength(), jet.px()) << Column(ValueLength(), jet.py()) << Column(ValueLength(), jet.pz()) << Column(ValueLength(), jet.e());
}

void LogVariable(const std::string&, char const* value)
{
    std::cout << Column(ValueLength(), value);
}

// std::stringstream Left(int width){
//   std::stringstream stream;
//   stream  << boost::units::engineering_prefix << std::left << std::setw(width) << std::setfill(' ');
//   return stream;
// }
//
// std::stringstream Right(int width){
//   std::stringstream stream;
//   stream  << boost::units::engineering_prefix << std::right << std::setw(width) << std::setfill(' ');
//   return stream;
// }

}
