#pragma once

#include "Analysis.hh"

namespace boca
{

/**
 * @brief Heavy higgs analyses
 *
 */

namespace heavyhiggs
{


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
    ttwwbb

};

enum class Collider
{
    LHC,
    FHC,
    LE
};

std::string Name(Collider collider);

std::string Name(Process process);

std::string LatexName(Process process);

/**
 *
 * @brief Analysis for heavy higgs
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger>
class AnalysisHeavyHiggs : public Analysis<Tagger>
{

public:

    boca::Mass Mass() const {
        return 750_GeV;
        return 800_GeV;
        return 1.5_TeV;
        return 2_TeV;
        return 500_GeV;
        return 1_TeV;
        return 300_GeV;
        return 400_GeV;
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
        return 100;
        return 10000;
        return 100000;
        return 1000;
        return 500;
        return 10000000;
        return 1000000;
        return 10;
    };

    long ReadNumberMax() const override {
        return 100000;
        return 10000;
        return 100;
        return 1000;
        return 500;
        return 10000000;
        return 1000000;
        return 10;
    };

    boca::heavyhiggs::Collider Collider() const {
        return boca::heavyhiggs::Collider::LHC;
        return boca::heavyhiggs::Collider::LE;
    };

    Momentum PreCut() const {
        switch (Collider()) {
        case boca::heavyhiggs::Collider::LHC :
            switch (Int(Mass())) {
            case 500 : return at_rest;
            case 1000 : return 250_GeV;
            case 2000 : return 250_GeV;
            case 3000 : return 250_GeV;
            default : std::cout << "Switch default for Mass of " << Mass() << std::endl;
                return at_rest;
            }
        case boca::heavyhiggs::Collider::LE :
            switch (Int(Mass())) {
            case 500 : return at_rest;
            case 1000 : return 300_GeV;
            case 2000 : return 300_GeV;
            case 4000 : return 1.5_TeV;
            case 6000 : return 2.5_TeV;
            case 10000 : return 2.5_TeV;
            case 15000 : return 2.5_TeV;
            case 20000 : return 2.5_TeV;
            default : std::cout << "Switch default for Mass of " << Mass() << std::endl;
                return at_rest;
            }
        default : std::cout << "Switch default for Collider " << to_int(Collider()) << std::endl;
            return at_rest;
        }
    };

    Momentum MissingEt() const {
        switch (Collider()) {
        case boca::heavyhiggs::Collider::LHC : return 30_GeV;
        case boca::heavyhiggs::Collider::LE : return 60_GeV;
        default : std::cout << "Switch default for Collider " << to_int(Collider()) << std::endl;
            return at_rest;
        }
    };

    Momentum LeptonPt() const {
        switch (Collider()) {
        case boca::heavyhiggs::Collider::LHC : return 50_GeV;
        case boca::heavyhiggs::Collider::LE : return 100_GeV;
        default : std::cout << "Switch default for Collider " << to_int(Collider()) << std::endl;
            return at_rest;
        }
    };

    Momentum BottomPt() const {
        switch (Collider()) {
        case boca::heavyhiggs::Collider::LHC : return 20_GeV;
        case boca::heavyhiggs::Collider::LE : return 40_GeV;
        default : std::cout << "Switch default for Collider " << to_int(Collider()) << std::endl;
            return at_rest;
        }
    };

    int FileNumber(Process process) const {
        switch (Collider()) {
        case boca::heavyhiggs::Collider::LHC :
            switch (process) {
            case Process::ttwwbb : return 1;
            case Process::ttwbb : return 1;
            case Process::Htt : return 1;
            case Process::Htwb : return 1;
            case Process::tttt : return 1;
            case Process::tttwb : return 1;
            default : std::cout << "Switch default for Process " << to_int(process) << std::endl;
                return 1;
            }
        case boca::heavyhiggs::Collider::LE :
            switch (process) {
            case Process::ttwwbb : return 2;
            case Process::ttwbb : return 1;
            default : std::cout << "Switch default for Process " << to_int(process) << std::endl;
                return 1;
            }
        default : std::cout << "Switch default for Collider " << to_int(Collider()) << std::endl;
            return 1;
        }
    }

    std::string Suffix(Process process) const {
        switch (process) {
        case Process::Htt :
        case Process::Htwb : return "_" + boca::Name(Mass());
        case Process::ttwwbb :
        case Process::ttwbb :
        case Process::tttt :
        case Process::tttwb : return "";
        default : std::cout << "Switch default for Process " << to_int(process) << std::endl;
            return "";
        }
    }

    virtual boca::Crosssection Crosssection(Process) const {
        std::cout << "No Crosssection" << std::endl;
        return 0_fb;
    };

    virtual void NewFile(Tag tag, Process process) {
        boca::AnalysisBase::NewFile(tag, FileNames(process, tag), this->Crosssection(process), LatexName(process));
    }

    virtual void NewFile(Tag tag, boca::Crosssection crosssection, Process process) {
        boca::AnalysisBase::NewFile(tag, FileNames(process, tag), crosssection, LatexName(process), Mass());
    }

    std::vector<std::string> FileNames(Process process, Tag tag) const {
        if (FileNumber(process) == 1) return {FileName(process, tag)};
        std::vector<std::string> names;
        for (auto const & file_number : Range(FileNumber(process))) {
            if (file_number == 0) names.emplace_back(FileName(process, tag));
            else names.emplace_back(FileName(process, tag) + "_" + std::to_string(file_number));
        }
        return names;
    }

    virtual std::string FileName(Process process, Tag tag) const {
        switch (tag) {
        case Tag::signal : return Name(process) + Suffix(process) + "_" + Name(Collider());
        case Tag::background : return Name(process) + Suffix(process) + "_" + Name(Collider());
        default : std::cout << "Switch default for Tag " << to_int(tag) << std::endl;
            return "";
        }
    }

private:

};

}

}
