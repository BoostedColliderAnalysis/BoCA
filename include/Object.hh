#pragma once

#include "Global.hh"

namespace analysis
{
/**
 * @brief general base class for Analysis
 *
 */
class Object
{



public:

    Object();

//     void Print(const Severity severity, const std::string &description,const std::string class_name = __CLASS_NAME__,const std::string method_name = __func__) const;
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

private:

    /**
     * @brief Print Debug messages
     *
     * @param  std::string Function Name
     * @return void
     */
    void Printer(const std::string &Description) const;

    void Printer(const std::string &name_space_name, const std::string &class_name, const std::string &Description) const;

};

}
