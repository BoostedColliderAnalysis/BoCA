#pragma once

#include "Analysis.hh"
#include "Vector.hh"

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
    H0, Hbb, Htt, Htb, tt, tt2, tttt, tttb, ttwbb, ttwcc, Htwb, ttwwbb

};

enum class Collider
{
    LHC, FHC, LE
};

std::string Name(Collider collider);

std::string Name(Process process);

std::string NiceName(Process process);

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
        return 300.*GeV;
        return 400.*GeV;
        return 500.*GeV;
        return 600.*GeV;
        return 700.*GeV;
        return 800.*GeV;
        return 900.*GeV;
        return 1000.*GeV;
        return 2000.*GeV;
        return 3000.*GeV;
        return 4000.*GeV;
        return 5000.*GeV;
        return 7000.*GeV;
        return 8000.*GeV;
        return 10000.*GeV;
        return 12000.*GeV;
        return 15000.*GeV;
        return 20000.*GeV;
    };

    Momentum PreCut() const {
        switch (collider_type()) {
        case Collider::LHC :
            switch (Int(Mass())) {
            case 500 : return 0.*GeV;
            case 1000 : return 250.*GeV;
            case 2000 : return 250.*GeV;
            case 3000 : return 250.*GeV;
            default : return 0.*GeV;
            }
        case Collider::LE :
            switch (Int(Mass())) {
            case 500 : return 0.*GeV;
            case 1000 : return 300.*GeV;
            case 2000 : return 300.*GeV;
            case 4000 : return 1500.*GeV;
            case 6000 : return 2500.*GeV;
            case 10000 : return 2500.*GeV;
            case 15000 : return 2500.*GeV;
            case 20000 : return 2500.*GeV;
            default : return 0.*GeV;
            }
        default : return 0.*GeV;
        }
    };

    long EventNumberMax() const override {
        return 10000000;
        return 1000000;
        return 100000;
        return 10000;
        return 1000;
        return 500;
        return 10;
    };

    Collider collider_type() const {
        return Collider::LE;
        return Collider::LHC;
    };

    Momentum MissingEt() const {
        switch (collider_type()) {
        case Collider::LHC : return 30.*GeV;
        case Collider::LE : return 60.*GeV;
        default : return 0.*GeV;
        }
    };

    Momentum LeptonPt() const {
        switch (collider_type()) {
        case Collider::LHC : return 50.*GeV;
        case Collider::LE : return 100.*GeV;
        default : return 0.*GeV;
        }
    };

    Momentum BottomPt() const {
        switch (collider_type()) {
        case Collider::LHC : return 20.*GeV;
        case Collider::LE : return 40.*GeV;
        default : return 0.*GeV;
        }
    };

    int FileNumber(Process process) const {
        switch (collider_type()) {
        case Collider::LHC :
            switch (process) {
            case Process::ttwwbb : return 1;
            case  Process::ttwbb : return 1;
            default : return 1;
            }
        case Collider::LE :
            switch (process) {
            case  Process::ttwwbb : return 2;
            case  Process::ttwbb : return 1;
            default : return 1;
            }
        default : return 1;
        }
    }

    std::string Suffix(Process process) const {
        switch (process) {
        case Process::Htt : return "_" + boca::Name(Mass());
        case Process::Htwb : return "_" + boca::Name(Mass());
        case Process::ttwwbb : return "";
        case Process::ttwbb : return "";
        default : return "";
        }
    }

    virtual void NewFile(Tag tag, Process process) {
        boca::AnalysisBase::NewFile(tag, FileNames(process, tag), NiceName(process));
    }

    virtual void NewFile(Tag tag, Crosssection crosssection, Process process) {
        boca::AnalysisBase::NewFile(tag, FileNames(process, tag), crosssection, NiceName(process), Mass());
    }

    Strings FileNames(Process process, Tag tag) const {
        if (FileNumber(process) == 1) return {FileName(process, tag)};
        Strings names;
        for (auto const & file_number : Range(FileNumber(process))) {
            if (file_number == 0) names.emplace_back(FileName(process, tag));
            else names.emplace_back(FileName(process, tag) + "_" + std::to_string(file_number));
        }
        return names;
    }

    virtual std::string FileName(Process process, Tag tag) const {
        switch (tag) {
        case Tag::signal:
            return Name(process) + Suffix(process) + "_" + Name(collider_type());
        case Tag::background:
            return Name(process) + Suffix(process) + "_" + Name(collider_type());
        }
    }

private:

};

}

}
