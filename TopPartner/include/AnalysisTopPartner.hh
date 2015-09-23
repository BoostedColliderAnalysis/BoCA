#pragma once

#include "Analysis.hh"
#include "Vector.hh"
#include "Units.hh"
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
// DetectorGeometry::set_detector_type(DetectorType::CMS);
    }

protected:

    boca::Mass Mass() const {
        return 2000. * GeV;
        return 4000. * GeV;
        return 6000. * GeV;
        return 10000. * GeV;
        return 8000. * GeV;
        return 1500. * GeV;
        return 1000. * GeV;
        return 500. * GeV;
        return 3000. * GeV;
    }

    long EventNumberMax() const override {
        return 1000;
        return 100;
        return 5000;
        return 10000;
        return 10;
    }

protected:

    Momentum PreCut() const {
        return 0. * GeV;
        return 200. * GeV;
    }

    Momentum JetPreCut() const {
        return 0. * GeV;
        return 100. * GeV;
    }

    boca::Crosssection Crosssection(Process process) const {
        switch (DetectorGeometry::detector_type()) {
        case DetectorType::CMS : {
            switch (process) {
            case Process::TT :
                switch (Int(Mass())) {
                case 500 : return 0.5156 * 2 * pb;
                case 1000 : return 0.01041 * 2 * pb;
                case 1500 : return 0.0005753 * 2 * pb;
                case 2000 : return 4.787e-05 * 2 * pb;
                case 3000 : return 5.019e-07 * 2 * pb;
                case 4000 : return 7.022e-09 * 2 * pb;
                default :
                    Error("wrong mass", Mass());
                    return pb;
                }
            case Process::ttBjj : return 0.03024 * 2 * pb;
            case Process::ttBB : return 0.0004068 * 2 * pb;
            default :
                Error("wrong process", Name(process));
                return pb;
            }
        }
        case DetectorType::Spp : {
            switch (process) {
            case Process::Tth :
                switch (Int(Mass())) {
                case 2000 : return 0.001065 * 2 * pb;
                case 4000 : return 4.212e-5 * 2 * pb;
                case 6000 : return 4.7344e-6 * 2 * pb;
                case 8000 : return 8.466e-7 * 2 * pb;
                default :
                    Error("wrong mass", Mass());
                    return pb;
                }
            case Process::TT :
                switch (Int(Mass())) {
                case 2000 : return 0.138 * 2 * pb;
                case 4000 : return 0.003493 * 2 * pb;
                case 6000 : return 0.0003115 * 2 * pb;
                case 8000 : return 4.655e-5 * 2 * pb;
                case 10000 : return 9.101e-06 * 2 * pb;
                default :
                    Error("wrong mass", Mass());
                    return pb;
                }
            case Process::ttBjj :
                switch (Int(PreCut())) {
                case 0 : return 1.669 * 2 * pb;
                case 200 : return 0.1754 * 2 * pb;
                default :
                    Error("wrong pre cut", PreCut());
                    return pb;
                }
            case Process::tthBjj :
                switch (Int(PreCut())) {
                case 0 : return 0.02535 * 2 * pb;
                case 200 : return 0.02535 * 2 * pb;
                default :
                    Error("wrong pre cut", PreCut());
                    return pb;
                }
            case Process::TThh :
                switch (Int(Mass())) {
                case 2000 : return 1.143e-7 * 2 * pb;
                case 4000 : return 9.95e-10 * 2 * pb;
                case 6000 : return 3.579e-11 * 2 * pb;
                case 8000 : return 2.305e-12 * 2 * pb;
                case 10000 : return 2.029e-13 * 2 * pb;
                default :
                    Error("wrong mass", Mass());
                    return pb;
                }
            case Process::ttBB : return 0.03206 * 2 * pb;
            default :
                Error("wrong process", Name(process));
                return pb;
            }
        }
        }
    }

    std::string Name(Process process) const {
        std::string name;
        switch (process) {
        case Process::TT : {
            switch (DetectorGeometry::detector_type()) {
            case DetectorType::CMS : return "PP-TT-14TeV-" + boca::Name(Mass()) + "";
            case DetectorType::Spp : return "PP-TT-100TeV-" + boca::Name(Mass()) + "";
            default : Error("wrong detector type");
            }
        }
        case Process::ttBjj : {
            switch (DetectorGeometry::detector_type()) {
            case DetectorType::CMS : return "PP-ttBJJ-14TeV";
            case DetectorType::Spp : return "PP-ttBJJ-100TeV";
            default : Error("wrong detector type");
            }
        }
        case Process::tthBjj : {
            return "PP-tthB";
            switch (Int(PreCut())) {
            case 0 : return name + "-0GeV";
            case 200 : return name + "-200GeV";
            default : Error("wrong pre cut");
            }
        }
        case Process::Tth : {
            switch (DetectorGeometry::detector_type()) {
            case DetectorType::CMS : return "PP-Tth-14TeV-" + boca::Name(Mass()) + "";
            case DetectorType::Spp : return "PP-Tth-100TeV-" + boca::Name(Mass()) + "";
            default : Error("wrong detector type");
            }
        }
        case Process::TThh : {
            switch (DetectorGeometry::detector_type()) {
            case DetectorType::CMS : return "PP-TThh-14TeV-" + boca::Name(Mass()) + "";
            case DetectorType::Spp : return "PP-TThh-100TeV-" + boca::Name(Mass()) + "";
            default : Error("wrong detector type");
            }
        }
        case Process::ttBB :
            switch (DetectorGeometry::detector_type()) {
            case DetectorType::CMS : return "PP-ttBB-14TeV";
            case DetectorType::Spp : return "PP-ttBB-100TeV";
            default : Error("wrong detector type");
            }
        default : Error("wrong process");
        }
        return "";
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
        return "";
    }

    void NewFile(Tag tag, Process process) {
        AnalysisBase::NewFile(tag, this->Name(process), this->Crosssection(process), this->NiceName(process), Mass());
    }

};

}

}

