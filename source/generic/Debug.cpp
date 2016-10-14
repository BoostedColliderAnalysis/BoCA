/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/multiplets/Jet.hh"
#include "boca/multiplets/Particle.hh"
#include "boca/generic/Debug.hh"

namespace boca {

std::string Shorten(std::string const& pretty_function, std::size_t brake)
{
    auto begin1 = pretty_function.substr(0, brake).rfind(" ") + 1;
    auto begin2 = pretty_function.substr(0, brake).rfind("::") + 1; // TODO should be +2 but corner case prevents it, hence the hack in the second last line
    auto begin = std::max(begin1, begin2);
    auto end = brake - begin;
    auto name = pretty_function.substr(begin, end);
    name.erase(std::remove(name.begin(), name.end(), ':'), name.end());
    return name;
}

std::string Shorten2(std::string const& pretty_function, std::size_t brake)
{
    auto colons = pretty_function.substr(0, brake).rfind("::");
    return (colons == std::string::npos) ? "::" : Shorten(pretty_function, colons);
}

std::string NameSpaceName(std::string const& pretty_function)
{
    auto bracket = pretty_function.find("(");
    auto colons = pretty_function.substr(0, bracket).rfind("::");
    return Shorten2(pretty_function, colons);
}

std::string ClassName(std::string const& pretty_function)
{
    auto bracket = pretty_function.find("(");
    return Shorten2(pretty_function, bracket);
}

std::string FunctionName(std::string const& pretty_function)
{
    auto bracket = pretty_function.find("(");
    return Shorten(pretty_function, bracket);
}

std::string FileName(std::string const& file)
{
    auto name = file.rfind('/') ? file.substr(file.rfind('/') + 1) : file;
    return name.substr(0, name.find('.'));
}

int ValueLength()
{
    return 20;
}

void Log(std::string const& file, int line, std::string const& NameSpace, std::string const& Class, std::string const& function, bool final)
{
    std::cout << Column(25, file) << ColumnRight(3, line) << " " << Column(15, NameSpace) << Column(18, Class) << Column(20, function);
    if (final) std::cout << '\n';
}

void Debug(bool final)
{
  if (final) std::cout << '\n';
}

void LogVariable(std::string const& variable, Particle const& jet)
{
    std::cout << Column(ValueLength(), variable) << Column(ValueLength(), jet.Px()) << Column(ValueLength(), jet.Py()) << Column(ValueLength(), jet.Pz()) << Column(ValueLength(), jet.E());
}

void LogVariable(std::string const& variable, Jet const& jet)
{
  std::cout << Column(ValueLength(), variable) << Column(ValueLength(), jet.Px()) << Column(ValueLength(), jet.Py()) << Column(ValueLength(), jet.Pz()) << Column(ValueLength(), jet.E());
}


void LogVariable(std::string const&, char const* value)
{
    std::cout << Column(ValueLength(), value);
}
void Error(const std::string& variable)
{
    std::cout << "Error: " << variable << '\n';
    std::cout << '\n';
}

}
