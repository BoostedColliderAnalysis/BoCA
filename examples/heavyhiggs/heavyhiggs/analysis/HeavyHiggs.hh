#pragma once

#include "boca/analysis/Analysis.hh"
#include "boca/Settings.hh"
#include "boca/generic/DEBUG_MACROS.hh"

/**
 * @brief Heavy Higgs partner
 * @ingroup Examples
 *
 */
namespace heavyhiggs
{

using namespace boca;


enum class Process
{
    H0,
    Hbb,
    Htt,
    Htb,
    tt,
    tt2,
    tttt,
    tttwb,
    tttb,
    ttwbb,
    ttwcc,
    Htwb,
    ttwwbb,
    hbb,
    bb,
    cc,
    jj

};

std::string Name(Process process);

boca::latex::String LatexName(Process process);

/**
* @brief Analyses
*
*/
namespace analysis
{

/**
 *
 * @brief Analysis for heavy higgs
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger_>
class HeavyHiggs : public boca::Analysis<Tagger_>
{

public:

    HeavyHiggs() {
      Settings::SetCollider(Collider());
    }

    boca::Mass Mass() const {
        return 1_TeV;
        return 500_GeV;
        return 400_GeV;
        return 750_GeV;
        return 800_GeV;
        return 1.5_TeV;
        return 2_TeV;
        return 300_GeV;
        return 600_GeV;
        return 700_GeV;
        return 900_GeV;
        return 3_TeV;
        return 4_TeV;
        return 5_TeV;
        return 7_TeV;
        return 8_TeV;
        return 10_TeV;
        return 12_TeV;
        return 15_TeV;
        return 20_TeV;
    };

    long TrainNumberMax() const override {
        return 10000;
        return 100;
        return 100000;
        return 1000;
        return 500;
        return 10000000;
        return 1000000;
        return 10;
    };

    long ReadNumberMax() const override {
        return 10000000;
        return 100000;
        return 10000;
        return 100;
        return 1000;
        return 500;
        return 1000000;
        return 10;
    };

    boca::Collider Collider() const {
        return boca::Collider::lhc;
        return boca::Collider::future;
    };

    Momentum PreCut() const {
        switch (Collider()) {
        case boca::Collider::lhc :
            switch (static_cast<int>(Mass() / GeV)) {
            case 400 : return at_rest;
            case 500 : return at_rest;
            case 1000 : return 250_GeV;
            case 2000 : return 250_GeV;
            case 3000 : return 250_GeV;
            default : std::cout << "Switch default for Mass of " << Mass() << '\n';
                return at_rest;
            }
        case boca::Collider::future :
            switch (static_cast<int>(Mass() / GeV)) {
            case 400 : return at_rest;
            case 500 : return at_rest;
            case 1000 : return 300_GeV;
            case 2000 : return 300_GeV;
            case 4000 : return 1.5_TeV;
            case 6000 : return 2.5_TeV;
            case 10000 : return 2.5_TeV;
            case 15000 : return 2.5_TeV;
            case 20000 : return 2.5_TeV;
            default : std::cout << "Switch default for Mass of " << Mass() << '\n';
                return at_rest;
            }
        default : std::cout << "Switch default for Collider " << to_int(Collider()) << '\n';
            return at_rest;
        }
    };

    Momentum MissingEt() const {
        switch (Collider()) {
        case boca::Collider::lhc : return 30_GeV;
        case boca::Collider::future : return 60_GeV;
        default : std::cout << "Switch default for Collider " << to_int(Collider()) << '\n';
            return at_rest;
        }
    };

    Momentum LeptonPt() const {
        switch (Collider()) {
        case boca::Collider::lhc : return 50_GeV;
        case boca::Collider::future : return 100_GeV;
        default : std::cout << "Switch default for Collider " << to_int(Collider()) << '\n';
            return at_rest;
        }
    };

    Momentum BottomPt() const {
        switch (Collider()) {
        case boca::Collider::lhc : return 20_GeV;
        case boca::Collider::future : return 40_GeV;
        default : std::cout << "Switch default for Collider " << to_int(Collider()) << '\n';
            return at_rest;
        }
    };

    int FileNumber(Process process) const {
        switch (Collider()) {
        case boca::Collider::lhc :
            switch (process) {
            case Process::Hbb : return 1;
            case Process::ttwwbb : return 1;
            case Process::ttwbb : return 1;
            case Process::Htt : return 1;
            case Process::Htwb : return 1;
            case Process::tttt : return 1;
            case Process::tttwb : return 1;
            case Process::tt : return 20;
            default : std::cout << "Switch default for Process " << to_int(process) << '\n';
                return 1;
            }
        case boca::Collider::future :
            switch (process) {
            case Process::ttwwbb : return 2;
            case Process::ttwbb : return 1;
            default : std::cout << "Switch default for Process " << to_int(process) << '\n';
                return 1;
            }
        default : std::cout << "Switch default for Collider " << to_int(Collider()) << '\n';
            return 1;
        }
    }

    std::string Suffix(Process process) const {
        switch (process) {
        case Process::Hbb : return "";
        case Process::Htt : return "";
        case Process::Htwb : return "_" + boca::units::Name(Mass());
        case Process::ttwwbb : return "";
        case Process::ttwbb : return "";
        case Process::tttt : return "";
        case Process::tttwb : return "";
        case Process::tt : return "";
        default : std::cout << "Switch default for Process " << to_int(process) << '\n';
            return "";
        }
    }

    virtual boca::Crosssection Crosssection(Process process) const {
        switch (process) {
        case Process::Hbb :
            switch (this->Collider()) {
            case boca::Collider::lhc:
                switch (static_cast<int>(Mass() / GeV)) {
//                 case 500 : return 100_fb; // FIXME this is the wrong value
                case 500 : return 25.52_fb;
                case 1000 : return 1.278_fb;
                case 2000 : return 0.02190_fb;
                    DEFAULT(static_cast<int>(Mass() / GeV), fb);
                }
            case boca::Collider::future:
                switch (static_cast<int>(Mass() / GeV)) {
                case 500 : return 973.5_fb;
                case 1000 : return 123.0_fb;
                case 1500 : return 28.62_fb;
                case 2000 : return 9.485_fb;
                case 3000 : return 1.754_fb;
                case 4000 : return 0.4851_fb;
                case 5000 : return 0.1669_fb;
                case 6000 : return 0.06731_fb;
                case 7000 : return 0.02937_fb;
                case 8000 : return 0.01425_fb;
                case 10000 : return 0.003842_fb;
                case 12000 : return 0.001221_fb;
                case 15000 : return 0.0002650_fb;
                case 20000 : return 0.00002821_fb;
                    DEFAULT(static_cast<int>(Mass() / GeV), fb);
                }
                DEFAULT(to_int(this->Collider()), fb);
            }
        case Process::tt :
            switch (this->Collider()) {
            case boca::Collider::lhc:
                switch (static_cast<int>(PreCut() / GeV)) {
                case 0 : return 97.54 * 2 * 1000_fb;
                case 250 : return 5.698 * 2 * 1000_fb;
                    DEFAULT(static_cast<int>(PreCut() / GeV), fb);
                }
                DEFAULT(Name(Collider()), fb);
            }
        default : std::cout << "Switch default for Process " << to_int(process) << '\n';
            return 0_fb;
        }
    }

    void AddSignal(Process process) {
        NewFile(Tag::signal, process);
    }

    void AddBackground(Process process) {
        NewFile(Tag::background,  process);
    }

    virtual void NewFile(Tag tag, Process process) {
        boca::analysis::Base::AddFile(tag, {FileNames(process, tag), LatexName(process), this->Crosssection(process)});
    }

    std::vector<std::string> FileNames(Process process, Tag tag) const {
        if (FileNumber(process) == 1) return {FileName(process, tag)};
        std::vector<std::string> names;
        for (auto const & file_number : IntegerRange(FileNumber(process))) {
            if (file_number == 0) names.emplace_back(FileName(process, tag));
            else names.emplace_back(FileName(process, tag) + "_" + std::to_string(file_number));
        }
        return names;
    }

    virtual std::string FileName(Process process, Tag tag) const {
//         std::cout << "file name: " << Name(process) + Suffix(process) + "_" + Name(Collider()) << '\n';
        switch (tag) {
        case Tag::signal : return Name(process) + Suffix(process) + "-" + Name(Collider()) + "_" + boca::units::Name(Mass());
        case Tag::background : return Name(process) + Suffix(process) + "-" + Name(Collider()) + "-" + boca::units::Name(PreCut());
//         case Tag::background : return Name(process) + Suffix(process) + "_" + Name(Collider());
        default : std::cout << "Switch default for Tag " << to_int(tag) << '\n';
            return "";
        }
    }

private:

};

}

}
