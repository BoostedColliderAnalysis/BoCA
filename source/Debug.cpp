#include "Debug.hh"

namespace analysis
{

std::string Shorten(const std::string &pretty_function, std::size_t brake)
{
    std::size_t begin1 = pretty_function.substr(0, brake).rfind(" ") + 1;
    std::size_t begin2 = pretty_function.substr(0, brake).rfind("::") + 1; // TODO should be +2 but corner case prevents it, hence the hack in the second last line
    std::size_t begin = std::max(begin1, begin2);
    std::size_t end = brake - begin;
    std::string name = pretty_function.substr(begin, end);
    name.erase(std::remove(name.begin(), name.end(), ':'), name.end());
    return name;
}

std::string Shorten2(const std::string &pretty_function, std::size_t brake)
{
    std::size_t colons = pretty_function.substr(0, brake).rfind("::");
    return (colons == std::string::npos) ? "::" : Shorten(pretty_function, colons);
}

std::string NameSpaceName(const std::string &pretty_function)
{
    std::size_t bracket = pretty_function.find("(");
    std::size_t colons = pretty_function.substr(0, bracket).rfind("::");
    return Shorten2(pretty_function, colons);
}

std::string ClassName(const std::string &pretty_function)
{
    std::size_t bracket = pretty_function.find("(");
    return Shorten2(pretty_function, bracket);
}

std::string FunctionName(const std::string &pretty_function)
{
    std::size_t bracket = pretty_function.find("(");
    return Shorten(pretty_function, bracket);
}

std::string FileName(const std::string &file)
{
    const std::string name = file.rfind('/') ? file.substr(file.rfind('/') + 1) : file;
    return name.substr(0, name.find('.'));
}

int ValueLength()
{
    return 20;
}

void Log(const std::string &file, const int line, const std::string &NameSpace, const std::string &Class, const std::string &function, bool final)
{
    std::cout << Column(25, file) << ColumnRight(3, line) << " " << Column(15, NameSpace) << Column(18, Class) << Column(20, function);
    if (final) std::cout << std::endl;
}

void LogVariable(const std::string &variable, const fastjet::PseudoJet jet)
{
    std::cout << Column(ValueLength(), jet.px()) << Column(ValueLength(), jet.px()) << Column(ValueLength(), jet.pz()) << Column(ValueLength(), jet.e());
}

// void LogVariable(const std::string &variable, const std::string &value)
// {
//     std::cout << Column(15, value);
// }

void LogVariable(const std::string &variable, const char *value)
{
    std::cout << Column(ValueLength(), value);
}

}
