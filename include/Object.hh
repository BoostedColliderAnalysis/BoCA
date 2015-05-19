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
    inline void Print(const Severity severity, const std::string &Description) const {
        if (severity > DebugLevel) return;
        Printer(Description);
        std::cout << std::endl;
    }

    /**
     * @brief Print a debug messages
     *
     */
    template<typename Severity, typename Value>
    inline void Print(const Severity severity, const std::string &Description, const Value value) const {
        if (severity > DebugLevel) return;
        Printer(Description);
        std::cout << " " << value << std::endl;
    }

    /**
     * @brief Print a debug messages
     *
     */
    template<typename Severity, typename Value, typename Value2>
    inline void Print(const Severity severity, const std::string &Description, const Value value, const Value2 value2) const {
        if (severity > DebugLevel) return;
        const char Separator = ' ';
        const int FunctionWidth = 10;
        Printer(Description);
        std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << value;
        std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << value2;
        std::cout << std::endl;
    }

    /**
     * @brief Print a debug messages
     *
     */
    template<typename Severity, typename Value, typename Value2, typename Value3>
    inline void Print(const Severity severity, const std::string &Description, const Value value, const Value2 value2, const Value3 value3) const {
        if (severity > DebugLevel) return;
        const char Separator = ' ';
        const int FunctionWidth = 10;
        Printer(Description);
        std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << value;
        std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << value2;
        std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << value3;
        std::cout << std::endl;
    }

    template<typename Severity, typename Value, typename Value2, typename Value3, typename Value4>
    inline void Print(const Severity severity, const std::string &Description, const Value value, const Value2 value2, const Value3 value3, const Value4 value4) const {
        if (severity > DebugLevel) return;
        const char Separator = ' ';
        const int FunctionWidth = 15;
        Printer(Description);
        std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << value;
        std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << value2;
        std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << value3;
        std::cout << std::left << std::setw(FunctionWidth) << std::setfill(Separator) << value4;
        std::cout << std::endl;
    }

    template<typename Severity>
    inline void Print(const Severity severity, const std::string &Description, const fastjet::PseudoJet &Jet) const {
        if (severity > DebugLevel) return;
        Print(severity, Description, Jet.e(), Jet.px(), Jet.py(), Jet.pz());
    }

    template<typename Severity>
    void Print(const Severity severity, const std::string &Description, float Momentum[]) const {
        if (severity > DebugLevel) return;
        Print(severity, Description, Momentum[0], Momentum[1], Momentum[2], Momentum[3]);
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

    template <typename Value>
    inline int sgn(const Value value) const {
        return (Value(0) < value) - (value < Value(0));
    }

    /**
     * @brief Calcualte distance in eta phi space
     *
     * @param  Rap1
     * @param  Phi1
     * @param  Rap2
     * @param  Phi2
     * @return float distance
     */
    float GetDistance(const float, const float, const float, const float) const;

    /**
     * @brief Calcualte distance from center in eta phi space
     *
     * @param  Rap
     * @param  Phi
     * @return float distance
     */
    float GetDistance(const float, const float) const;

    /**
     * @brief Take care of phi angles around pi
     *
     */
    float GetDeltaPhi(const float Phi, const float ReferencePhi) const;

    virtual inline std::string NameSpaceName() const {
        return ("hanalysis");
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

    std::string GetParticleName(const int particle_id) const;

    float GetParticleMass(const analysis::Object::ParticleId particle_id) const;


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
    Severity DebugLevel;

    /**
     * @brief A large number
     *
     */
    static const int LargeNumber = 999999999;

    /**
     * @brief Top quark mass
     *
     */
    constexpr static float TopMass = 173.5;

    /**
     * @brief Higgs boson mass
     *
     */
    constexpr static float HiggsMass = 125;

    /**
     * @brief Z bsoson mass
     *
     */
    constexpr static float ZMass = 91.188;

    /**
     * @brief W bsoson mass
     *
     */
    constexpr static float WMass = 80.39;

    /**
     * @brief Tau lepton mass
     *
     */
    constexpr static float TauMass = 1.776;

    /**
     * @brief Muon mass
     *
     */
    constexpr static float MuonMass = 0.1134;

    /**
     * @brief Electron mass
     *
     */
    constexpr static float ElectronMass = 0.000511;

    /**
     * @brief Neutrino mass (0)
     *
     */
    constexpr static float NeutrinoMass = 0;

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

    /**
     * @brief Pi
     *
     */
    constexpr static float Pi = 3.14159265;

    /**
     * @brief 2 * pi
     *
     */
    constexpr static float TwoPi = 2 * Pi;

    /**
     * @brief 1 sigma deviation
     *
     */
    constexpr static float OneSigma = 0.6827;

    /**
     * @brief 2 sigma deviation
     *
     */
    constexpr static float TwoSigma = 0.9545;

    /**
     * @brief 3 sigma deviation
     *
     */
    constexpr static float ThreeSigma = 0.9973;

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
