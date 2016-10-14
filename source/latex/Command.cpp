#include <boost/range/adaptor/indexed.hpp>

#include "boca/latex/Command.hh"

namespace boca
{

namespace latex
{

Optional::Optional(const std::string& option)
{
    option_ = option;
}

std::string Optional::Get() const
{
    return option_;
}

std::string Macro(const std::string& string)
{
    return "\\" + string;
}

std::string Command::str() const
{
    auto string = Macro(command_);
    if (!optional_.empty()) {
        string += "[";
        //FIXME Does this 0 belong here?
        for (auto optional : boost::adaptors::index(optional_, 0)) string += (optional.index() ? ", " : "") +  optional.value();
        string += "]";
    }
    if (!options_.empty()) for (const auto & option : options_) string += "{" + option + "}";
    return string + (add_line_ ? '\n' : '\0');
}

std::ostream& operator<<(std::ostream& stream, const Command& tex)
{
    stream << tex.str() << '\n';
    return stream;
}

SetCounter::SetCounter(const std::string& counter, int number) :
    Command("setcounter", counter, number) {}

Environment::Environment(const std::string& name, bool new_line):
    name_(name),
    new_line_(new_line) {}

std::string Environment::End() const
{
    return Command("end", name_, true).str();
}

}

}
