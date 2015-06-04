# pragma once

# include "Global.hh"

namespace analysis{

/**
 * @brief general base class for HAnalysis
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
    inline void Print(const Severity severity, const std::string &description) const {
        if (severity > debug_level_) return;
        Printer(description);
        std::cout << std::endl;
    }

    /**
     * @brief Print a debug messages
     *
     */
    template<typename Severity, typename Value>
    inline void Print(const Severity severity, const std::string &description, const Value value) const {
        if (severity > debug_level_) return;
        Printer(description);
        std::cout << " " << value << std::endl;
    }

    /**
     * @brief Print a debug messages
     *
     */
    template<typename Severity, typename Value, typename Value2>
    inline void Print(const Severity severity, const std::string &description, const Value value, const Value2 value2) const {
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
    inline void Print(const Severity severity, const std::string &description, const Value value, const Value2 value2, const Value3 value3) const {
        if (severity > debug_level_) return;
        const char Separator = ' ';
        const int FunctionWidth = 10;
        Printer(description);
        std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << value;
        std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << value2;
        std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << value3;
        std::cout << std::endl;
    }

    template<typename Severity, typename Value, typename Value2, typename Value3, typename Value4>
    inline void Print(const Severity severity, const std::string &description, const Value value, const Value2 value2, const Value3 value3, const Value4 value4) const {
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
    inline void Print(const Severity severity, const std::string &description, const fastjet::PseudoJet &Jet) const {
        if (severity > debug_level_) return;
        Print(severity, description, Jet.e(), Jet.px(), Jet.py(), Jet.pz());
    }

    template<typename Severity>
    void Print(const Severity severity, const std::string &description, float momentum[]) const {
        if (severity > debug_level_) return;
        Print(severity, description, momentum[0], momentum[1], momentum[2], momentum[3]);
    }

    enum ParticleId {
        EmptyId = 0, ///< 0
        DownId = 1,///< \f$d\f$
        UpId = 2,///< \f$u\f$
        StrangeId = 3,///< \f$s\f$
        CharmId = 4,///< \f$c\f$
        BottomId = 5,///< \f$b\f$
        TopId = 6,///< \f$t\f$
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

    /**
     * @brief Calcualte distance in eta phi space
     *
     * @param  Rap1
     * @param  Phi1
     * @param  Rap2
     * @param  Phi2
     * @return float distance
     */
    float Distance(const float, const float, const float, const float) const;

    /**
     * @brief Calcualte distance from center in eta phi space
     *
     * @param  Rap
     * @param  Phi
     * @return float distance
     */
    float Distance(const float, const float) const;

    /**
     * @brief Take care of phi angles around pi
     *
     */
    float DeltaPhi(const float Phi, const float ReferencePhi) const;

    virtual inline std::string NameSpaceName() const {
        return ("analysis");
    }

    virtual inline std::string ClassName() const {

        return ("Object");

    };

    enum Status {
        kNoStatus = 0,
        kStable = 1,
        kUnstable = 2,
        kGenerator = 3
    };

    std::string Name(const int particle_id) const;

    float Mass(const analysis::Object::ParticleId particle_id) const;


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
    void Printer(const std::string &description) const;

};

}
