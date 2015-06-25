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

    enum Severity {
        kError,
        kNotification,
        kInformation,
        kDebug,
        kDetailed
    };

    enum Tag {kBackground = 0, kSignal = 1};

    template <typename Severity>
     void Print(const Severity severity, const std::string &description) const {
        if (severity > debug_level_) return;
        Printer(description);
        std::cout << std::endl;
    }

    /**
     * @brief Print a debug messages
     *
     */
    template<typename Severity, typename Value>
     void Print(const Severity severity, const std::string &description, const Value value) const {
        if (severity > debug_level_) return;
        Printer(description);
        std::cout << " " << value << std::endl;
    }

    /**
     * @brief Print a debug messages
     *
     */
    template<typename Severity, typename Value, typename Value2>
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
    template<typename Severity, typename Value, typename Value2, typename Value3>
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

    template<typename Severity, typename Value, typename Value2, typename Value3, typename Value4>
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

    template<typename Severity>
     void Print(const Severity severity, const std::string &description, const fastjet::PseudoJet &Jet) const {
        if (severity > debug_level_) return;
        Print(severity, description, Jet.e(), Jet.px(), Jet.py(), Jet.pz());
    }

    template<typename Severity>
    void Print(const Severity severity, const std::string &description, float momentum[]) const {
        if (severity > debug_level_) return;
        Print(severity, description, momentum[0], momentum[1], momentum[2], momentum[3]);
    }

    enum ParticleId {
        EmptyId = 0,
        DownId = 1,
        UpId = 2,
        StrangeId = 3,
        CharmId = 4,
        BottomId = 5,
        TopId = 6,
        TopPartnerId = 8,
        ElectronId = 11,
        ElectronNeutrinoId = 12,
        MuonId = 13,
        MuonNeutrinoId = 14,
        TauId = 15,
        TauNeutrinoId = 16,
        GluonId = 21,
        PhotonId = 22,
        ZId = 23,
        WId = 24,
        HiggsId = 25,
        HeavyHiggsId = 35,
        CPOddHiggsId = 36,
        ChargedHiggsId = 37,
        AnyId = 86,
        IsrId = 87,
        MarkerId = 88,
        MixedJetId = 90,
        ClusterId = 91,
        StringId = 92,
        Pi0MesonId = 111,
        Rho0MesonId = 113,
        K0LMesonId = 130,
        PionId = 211,
        RhoMesonId = 213,
        RapMesonId = 221,
        OmegaMesonId = 223,
        K0SMesonId = 310,
        KMeson0Id = 311,
        KMeson0SId = 313,
        KMesonId = 321,
        KMesonSId = 323,
        RapPMesonId = 331,
        DMesonId = 411,
        DMesonSId = 413,
        DMesonS2Id = 415,
        DMeson0Id = 421,
        DMesonS0Id = 423,
        RapCMesonId = 441,
        BMeson0Id = 511,
        BMeson0SId = 513,
        BMesonId = 521,
        BMesonSId = 523,
        BMesonS0Id = 531,
        BMesonSS0Id = 533,
        DownDown1Id = 1103,
        UpDown0Id = 2101,
        UpDown1Id = 2103,
        DeltaBaryonId = 1114,
        NeutronId = 2112,
        UpUp1Id = 2203,
        ProtonId = 2212,
        DeltaBaryon2Id = 2224,
        CpvHiggsId = 5000000
    };

protected:

    virtual  std::string NameSpaceName() const {
        return ("analysis");
    }

    virtual  std::string ClassName() const {
        return ("Object");
    }

    enum Status {
        kNoStatus = 0,
        kStable = 1,
        kUnstable = 2,
        kGenerator = 3
    };

    std::string Name(const int particle_id) const;

    float Mass(const ParticleId particle_id) const;


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
