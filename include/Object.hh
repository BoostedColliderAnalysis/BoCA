# pragma once

# include "Global.hh"

namespace analysis
{

//    std::string ClassName(const std::string &pretty_function)  {
//     std::size_t colons = pretty_function.find("::");
//     if (colons == std::string::npos) return "::";
//     std::size_t begin = pretty_function.substr(0, colons).rfind(" ") + 1;
//     std::size_t end = colons - begin;
//     return pretty_function.substr(begin, end);
//   }
//
  //   #define __CLASS_NAME__ ClassName(__PRETTY_FUNCTION__)
//
//    std::string MethodName(const std::string &pretty_function)  {
//     std::size_t colons = pretty_function.find("::");
//     std::size_t begin = pretty_function.substr(0, colons).rfind(" ") + 1;
//     std::size_t end = pretty_function.rfind("(") - begin;
//     return pretty_function.substr(begin, end) + "()";
//   }
//
  //   #define __METHOD_NAME__ MethodName(__PRETTY_FUNCTION__)

/**
 * @brief general base class for Analysis
 *
 */
class Object
{



public:

    Object();

     void Print(const Severity severity, const std::string &description) const;

    /**
     * @brief Print a debug messages
     *
     */
    template<typename Value>
     void Print(const Severity severity, const std::string &description, const Value value) const {
        if (severity > debug_level_) return;
        Printer(description);
        std::cout << " " << value << std::endl;
    }

    /**
     * @brief Print a debug messages
     *
     */
    template<typename Value, typename Value2>
     void Print(const Severity severity, const std::string &description, const Value value, const Value2 value2) const {
        if (severity > debug_level_) return;
        const char Separator = ' ';
        const int FunctionWidth = 10;
        Printer(description);
        std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << value;
        std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << value2;
        std::cout << std::endl;
    }

    /**
     * @brief Print a debug messages
     *
     */
    template<typename Value, typename Value2, typename Value3>
     void Print(const Severity severity, const std::string &description, const Value value, const Value2 value2, const Value3 value3) const {
        if (severity > debug_level_) return;
        const char Separator = ' ';
        const int FunctionWidth = 15;
        Printer(description);
        std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << value;
        std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << value2;
        std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << value3;
        std::cout << std::endl;
    }

    template<typename Value, typename Value2, typename Value3, typename Value4>
     void Print(const Severity severity, const std::string &description, const Value value, const Value2 value2, const Value3 value3, const Value4 value4) const {
        if (severity > debug_level_) return;
        const char Separator = ' ';
        const int FunctionWidth = 15;
        Printer(description);
        std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << value;
        std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << value2;
        std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << value3;
        std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << value4;
        std::cout << std::endl;
    }

     void Print(const Severity severity, const std::string &description, const fastjet::PseudoJet &Jet) const;

    void Print(const Severity severity, const std::string &description, float momentum[]) const;

protected:

    virtual  std::string NameSpaceName() const {
        return ("analysis");
    }

    virtual  std::string ClassName() const {
        return ("Object");
    }

    /**
     * @brief Debug level
     *
     * 0: Errors
     * 1: Analysis Information
     * 2: event Information
     * 3: Detailed Information
     * 4: Step by Step Information
     *
     */
    Severity debug_level_;

    /**
     * @brief Initial user index
     *
     */
    static const int EmptyUserIndex = -1;

    /**
     * @brief Position outside of a vector
     *
     */
    static const int EmptyPosition = -1;

private:

    /**
     * @brief Print Debug messages
     *
     * @param  std::string Function Name
     * @return void
     */
    void Printer(const std::string &Description) const;

};

}
