#include "Debug.hh"

namespace analysis
{

std::string Shorten(const std::string &pretty_function, std::size_t brake)
{
    std::size_t begin1 = pretty_function.substr(0, brake).rfind(" ") + 1;
    std::size_t begin2 = pretty_function.substr(0, brake).rfind("::") + 2;
    std::size_t begin = std::max(begin1, begin2);
    std::size_t end = brake - begin;
    return pretty_function.substr(begin, end);
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
    return file.rfind('/') ? file.substr(file.rfind('/') + 1) : file;
}

void Log0(const std::string &file, const int line, const std::string &NameSpace, const std::string &Class, const std::string &function, bool final)
{
    std::cout << Column(25, file) <<  Column(5, line) << Column(15, NameSpace) << Column(15, Class) << Column(10, function);
    if (final) std::cout << std::endl;
}
void LogVariable(const std::string &variable, const fastjet::PseudoJet jet)
{
    std::cout << Column(15, jet.px()) << Column(15, jet.px()) << Column(15, jet.pz()) << Column(15, jet.e());
}

}
