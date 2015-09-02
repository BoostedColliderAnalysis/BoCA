#pragma once

#include "Analysis.hh"
#include "Vector.hh"
#include "Debug.hh"

namespace boca
{

/**
 * @brief Naturalness measurment
 *
 */
namespace naturalness
{

enum class Process
{
    Tth,
    TT,
    ttBjj,
    tthBjj,
    TThh
};

/**
 *
 * @brief Top partner analysis
 *
 * \author Jan Hajer
 *
 */
template<typename Tagger>
class AnalysisNaturalness : public boca::Analysis<Tagger>
{
public:

    AnalysisNaturalness() {
        DetectorGeometry::set_detector_type(DetectorType::CMS);
    }

protected:

    int Mass() const {
        return 4000;
        return 2000;
        return 1000;
        return 500;
        return 8000;
        return 10000;
    }

    long EventNumberMax() const override {
        return 100;
        return 1000;
        return 10;
    }

    std::string FilePath() const final {
        return "~/Projects/TopPartner/Analysis/";
    }

protected:

    int PreCut() const {
        return 0;
        return 200;
    }

    int JetPreCut() const {
        return 100;
        return 0;
    }

    float Crosssection(Process process) const {
        float crosssection;
        switch (process) {
        case Process::Tth : crosssection = 0.004964;
            break;
        case Process::TT :
            switch (Mass()) {
            case 2000 : crosssection = 0.264;
                break;
            case 10000 : crosssection = 2.485e-05;
                break;
            default : crosssection = 1;
                Error("wrong mass", Mass());
            }
            break;
        case Process::ttBjj :
            switch (PreCut()) {
            case 0 : crosssection = 1.669;
                break;
            case 200 : crosssection = 0.1754;
                break;
            }
            break;
        case Process::tthBjj :
            switch (PreCut()) {
            case 0 : crosssection = 0.02535;
                break;
            case 200 : crosssection = 0.02535;
                break;
            }
            break;
        case Process::TThh : crosssection = 3.057e-05;
            break;
        }
        return crosssection * 2 * 1000;
    }

    std::string Name(Process process) const {
        std::string name;
        switch (process) {
        case Process::TT : {
            switch (DetectorGeometry::detector_type()) {
            case DetectorType::CMS :
                name = "PP-TT-14TeV-" + std::to_string(Mass()) + "GeV";
                break;
            case DetectorType::Spp :
                name = "pp-TT-tthB-bbbbjjjjlv";
                break;
            }
        } break;
        case Process::ttBjj : {
            name = "PP-ttBJJ-14TeV";
            switch (PreCut()) {
            case 0 :
                name + "-0GeV";
                break;
            case 200 :
                name + "-200GeV";
                break;
            }
        } break;
        case Process::tthBjj : {
            name = "PP-tthB";
            switch (PreCut()) {
            case 0 : name + "-0GeV"; break;
            case 200 : name + "-200GeV"; break;
            }
        } break;
        case Process::Tth :
            name = "PP-Tth-ttBh";
            break;
        case Process::TThh :
            name = "PP-TThh";
            break;
        default :
            Error("no case");
        }
        switch (DetectorGeometry::detector_type()) {
        case DetectorType::CMS :
            name + "14TeV";
            break;
//           case DetectorType::Spp : ;
        }
        return name;
    }

    std::string NiceName(Process process) const {
        switch (process) {
        case Process::TT : return "#tilde t_{h}#tilde t_{l}";
        case Process::ttBjj : return "t_{l}t_{h}B^{0}jj";
        case Process::tthBjj : return "t_{l}t_{h}hB^{0}jj";
        case Process::Tth : return "#tilde t_{l}t_{h}h";
        case Process::TThh : return "#tilde t_{l}#tilde t_{h}hh";
        default: Error("no case");
        }
    }

    void NewFile(Tag tag, Process process) {
        AnalysisBase::NewFile(tag, this->Name(process), this->Crosssection(process), this->NiceName(process), Mass());
    }

};

}

}

