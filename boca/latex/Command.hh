#pragma once

#include <string>
#include <vector>

namespace boca
{

/**
* @brief LaTeX
*
*/
namespace latex
{

class Optional
{
public:

    Optional(std::string const& option);

    std::string Get() const;

private:

    std::string option_;

};

std::string Macro(std::string const& string);

class Command
{

public:

    template <typename... Arguments_>
    Command(std::string const& command, Arguments_... arguments) {
        command_ = command;
        Argument(arguments...);
    }

    template <typename... Arguments_>
    void Argument(std::string const& argument, Arguments_... arguments) {
        options_.emplace_back(argument);
        Argument(arguments...);
    }

    template <typename... Arguments_>
    void Argument(char const* argument, Arguments_... arguments) {
      options_.emplace_back(argument);
      Argument(arguments...);
    }

    template <typename... Arguments_>
    void Argument(int argument, Arguments_... arguments) {
        options_.emplace_back(std::to_string(argument));
        Argument(arguments...);
    }

    template <typename... Arguments_>
    void Argument(Optional const& option, Arguments_... arguments) {
        optional_.emplace_back(option.Get());
        Argument(arguments...);
    }

    template <typename... Arguments_>
    void Argument(bool add_line, Arguments_... arguments) {
        add_line_ = add_line;
        Argument(arguments...);
    }

    template <typename... Arguments_>
    void Optional(std::string const& argument, Arguments_... arguments) {
        optional_.emplace_back(argument);
        Optional(arguments...);
    }

    std::string str() const;

    operator std::string() {
        return str();
    }

    friend std::ostream& operator<<(std::ostream& stream, Command const& tex);

    void Argument() {}

private:

    void Optional() {}

    std::vector<std::string> options_;

    std::vector<std::string> optional_;

    std::string command_;

    bool add_line_ = false;

};

std::ostream& operator<<(std::ostream& stream, Command const& tex);

class UsePackage : public Command
{

public:

    template <typename... Arguments_>
    UsePackage(std::string const& package, Arguments_ ... arguments) :
        Command("usepackage", package) {
        Argument(arguments...);
    }

};

class SetCounter : public Command
{

public:

    SetCounter(const std::string& counter, int number);

};

class RenewCommand : public Command
{

public:

    template <typename Value>
    RenewCommand(std::string  const& command, Value value):
        Command("renewcommand", Command(command).str(), value) {}

};

class DocumentClass : public Command
{

public:

    template <typename... Arguments_>
    DocumentClass(const std::string& document_class, Arguments_ ... arguments):
        Command("documentclass", document_class, true) {
        Optional(arguments...);
    }
};

class Article : public DocumentClass
{

public:

    template <typename... Arguments_>
    Article(Arguments_ ... arguments) :
        DocumentClass("article", arguments...) {}
};

class Caption: public Command
{

public:

    Caption(const std::string& caption) : Command("caption", caption + ".") {}

};

class Environment
{

public:

    Environment(std::string const& name, bool new_line = true);

    template <typename... Arguments_>
    std::string Begin(Arguments_... arguments) {
        return (new_line_ ? "\n" : "") + Command("begin", name_, true, arguments...).str();
    }

    std::string End() const;

private:

    std::string name_;

    bool new_line_;


};

class Unit : public Command
{

public :

    Unit(std::string const& unit) :
        Command("unit", unit) {}

    template <typename Value_>
    Unit(std::string const& unit, Value_ value) :
        Command("unit", unit, boca::latex::Optional(std::to_string(value))) {}
};

class MultiColumn : public Command
{

public:

    MultiColumn(std::string const& name, int number, std::string const& alignment = "c") :
        Command("multicolumn", number, alignment, name) {}

};

}

}
