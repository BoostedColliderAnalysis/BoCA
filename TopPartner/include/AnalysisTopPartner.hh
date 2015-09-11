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
    ttBBjj,
    ttBB,
    TThh
};

std::string Name(Process process)
{
    switch (process) {
    case Process::Tth : return "Tth";
    case Process::TT : return "TT";
    case Process::ttBjj : return "ttBjj";
    case Process::tthBjj : return "tthBjj";
    case Process::ttBBjj : return "ttBBjj";
    case Process::ttBB : return "ttBB";
    case Process::TThh : return "TThh";
    }
}

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
//         DetectorGeometry::set_detector_type(DetectorType::CMS);
    }

protected:

    int Mass() const {
        return 6000;
        return 4000;
        return 2000;
        return 8000;
        return 10000;
        return 1500;
        return 1000;
        return 500;
        return 3000;
    }

    long EventNumberMax() const override {
        return 5000;
        return 10000;
        return 1000;
        return 100;
        return 10;
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
        float crosssection = 2 * 1000;
        switch (DetectorGeometry::detector_type()) {
        case DetectorType::CMS : {
            switch (process) {
            case Process::TT :
                switch (Mass()) {
                case 500 : return crosssection *= 0.5156;
                case 1000 : return crosssection *= 0.01041;
                case 1500 : return crosssection *= 0.0005753;
                case 2000 : return crosssection *= 4.787e-05;
                case 3000 : return crosssection *= 5.019e-07;
                case 4000 : return crosssection *= 7.022e-09;
                default :
                    Error("wrong mass", Mass());
                    return crosssection;
                }
            case Process::ttBjj : return crosssection *= 0.03024;
            case Process::ttBB : return crosssection *= 0.0004068;
            default :
                Error("wrong process", Name(process));
                return crosssection;
            }
        }
        case DetectorType::Spp : {
            switch (process) {
            case Process::Tth :
                switch (Mass()) {
                case 2000 : return crosssection *= 0.001065;
                case 4000 : return crosssection *= 4.212e-5;
                case 6000 : return crosssection *= 4.7344e-6;
                case 8000 : return crosssection *= 8.466e-7;
                default :
                    Error("wrong mass", Mass());
                    return crosssection;
                }
            case Process::TT :
                switch (Mass()) {
                case 2000 : return crosssection *= 0.138;
                case 4000 : return crosssection *= 0.003493;
                case 6000 : return crosssection *= 0.0003115;
                case 8000 : return crosssection *= 4.655e-5;
                case 10000 : return crosssection *= 9.101e-06;
                default :
                    Error("wrong mass", Mass());
                    return crosssection;
                }
            case Process::ttBjj :
                switch (PreCut()) {
                case 0 : return crosssection *= 1.669;
                case 200 : return crosssection *= 0.1754;
                default :
                    Error("wrong pre cut", PreCut());
                    return crosssection;
                }
            case Process::tthBjj :
                switch (PreCut()) {
                case 0 : return crosssection *= 0.02535;
                case 200 : return crosssection *= 0.02535;
                default :
                    Error("wrong pre cut", PreCut());
                    return crosssection;
                }
            case Process::TThh : return crosssection *= 3.057e-05;
            case Process::ttBB : return crosssection *= 0.03206;
            default :
                Error("wrong process", Name(process));
                return crosssection;
            }
        }
        }
    }

    std::string Name(Process process) const {
        std::string name;
        switch (process) {
        case Process::TT : {
            switch (DetectorGeometry::detector_type()) {
            case DetectorType::CMS : return "PP-TT-14TeV-" + std::to_string(Mass()) + "GeV";
            case DetectorType::Spp : return "PP-TT-100TeV-" + std::to_string(Mass()) + "GeV";
            }
        }
        case Process::ttBjj : {
            switch (DetectorGeometry::detector_type()) {
            case DetectorType::CMS : return "PP-ttBJJ-14TeV";
            case DetectorType::Spp : return "PP-ttBJJ-100TeV";
            }
        }
        case Process::tthBjj : {
            return "PP-tthB";
            switch (PreCut()) {
            case 0 : return name + "-0GeV";
            case 200 : return name + "-200GeV";
            }
        }
        case Process::Tth :  {
            switch (DetectorGeometry::detector_type()) {
            case DetectorType::CMS : return "PP-Tth-14TeV-" + std::to_string(Mass()) + "GeV";
            case DetectorType::Spp : return "PP-Tth-100TeV-" + std::to_string(Mass()) + "GeV";
            }
        }
        case Process::TThh : return "PP-TThh";
        case Process::ttBB :
            switch (DetectorGeometry::detector_type()) {
            case DetectorType::CMS : return "PP-ttBB-14TeV";
            case DetectorType::Spp : return "PP-ttBB-100TeV";
            }
        default :
            Error("no case");
        }
    }

    std::string NiceName(Process process) const {
        switch (process) {
        case Process::TT : return "#tilde t_{h}#tilde t_{l}";
        case Process::ttBjj : return "t_{l}t_{h}B^{0}jj";
        case Process::tthBjj : return "t_{l}t_{h}hB^{0}jj";
        case Process::Tth : return "#tilde t_{l}t_{h}h";
        case Process::TThh : return "#tilde t_{l}#tilde t_{h}hh";
        case Process::ttBB : return "t_{l}t_{h}B^{0}B^{0}";
        default: Error("no case");
        }
    }

    void NewFile(Tag tag, Process process) {
        AnalysisBase::NewFile(tag, this->Name(process), this->Crosssection(process), this->NiceName(process), Mass());
    }

};

}

}

