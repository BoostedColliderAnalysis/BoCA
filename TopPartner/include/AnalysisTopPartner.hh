/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "Analysis.hh"
#include "DetectorGeometry.hh"
// #define INFORMATION
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
    TthLep,
    TthHad,
    TT,
    ttBjj,
    tthBjj,
    ttBBjj,
    ttBB,
    TThh,
    ttWWWW,
    ttWWWB,
    ttWWBB,
    ttWBBB,
    ttBBBB,
};

std::string Name(Process process);

std::string LatexName(Process process);

bool MassDependent(Process process);

/**
 *
 * @brief Top partner analysis
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger>
class AnalysisNaturalness : public boca::Analysis<Tagger>
{
public:

    AnalysisNaturalness() {
        INFO0;
// DetectorGeometry::set_detector_type(DetectorType::CMS);
    }

protected:

    auto Mass() const {
        INFO0;
        return 1_TeV;
        return 2_TeV;
        return 4_TeV;
        return 6_TeV;
        return 10_TeV;
        return 8_TeV;
        return 1.5_TeV;
        return 500_GeV;
        return 3_TeV;
    }

    long TrainNumberMax() const override {
        INFO0;
        return 1000;
        return 10000;
        return 10;
        return 100;
        return 5000;
    }

protected:

    auto PreCut() const {
        INFO0;
        return 0_GeV;
        return 200_GeV;
    }

    auto JetPreCut() const {
        INFO0;
        return 0_GeV;
        return 100_GeV;
    }

    auto Crosssection(Process process) const {
        INFO0;
        switch (DetectorGeometry::DetectorType()) {
        case DetectorType::CMS : {
            switch (process) {
            case Process::TT :
                switch (Int(Mass())) {
                case 500 : return 0.5156 * 2_pb;
                case 1000 : return 0.01041 * 2_pb;
                case 1500 : return 0.0005753 * 2_pb;
                case 2000 : return 4.787e-05 * 2_pb;
                case 3000 : return 5.019e-07 * 2_pb;
                case 4000 : return 7.022e-09 * 2_pb;
                    DEFAULT(Mass(), pb);
                }
            case Process::ttBjj : return 0.03024 * 2_pb;
            case Process::ttBB : return 0.0004068 * 2_pb;
                DEFAULT(Name(process), pb);
            }
        }
        case DetectorType::Spp : {
            switch (process) {
            case Process::TthLep :
                switch (Int(Mass())) {
                case 1000 : return 0.004304_pb;
                case 2000 : return 0.0002919_pb;
                case 4000 : return 1.154e-05_pb;
                case 6000 : return 4.7344e-6_pb;
                case 8000 : return 8.466e-7_pb;
                case 10000 : return 1.97e-7_pb;
                    DEFAULT(Mass(), pb);
                }
            case Process::TthHad :
                switch (Int(Mass())) {
                case 1000 : return 0.004304_pb;
                case 2000 : return 0.0002919_pb;
                case 4000 : return 1.154e-05_pb;
                case 6000 : return 4.7344e-6_pb;
                case 8000 : return 8.466e-7_pb;
                case 10000 : return 1.97e-7_pb;
                    DEFAULT(Mass(), pb);
                }
            case Process::TT :
                switch (Int(Mass())) {
                case 1000 : return 2.499 * 2_pb;
                case 2000 : return 0.09375 * 2_pb;
                case 4000 : return 0.002363 * 2_pb;
                case 6000 : return 0.0003115 * 2_pb;
                case 8000 : return 4.655e-5 * 2_pb;
                case 10000 : return 9.101e-06 * 2_pb;
                    DEFAULT(Mass(), pb);
                }
            case Process::ttBjj :
                switch (Int(PreCut())) {
                case 0 : return 1.669 * 2_pb;
                case 200 : return 0.1754 * 2_pb;
                    DEFAULT(Mass(), pb);
                }
            case Process::tthBjj :
                switch (Int(PreCut())) {
                case 0 : return 0.02535 * 2_pb;
                case 200 : return 0.02535 * 2_pb;
                    DEFAULT(Mass(), pb);
                }
            case Process::TThh :
                switch (Int(Mass())) {
                case 1000 : return 7.101e-07 * 2_pb;
                case 2000 : return 3.059e-08 * 2_pb;
                case 4000 : return 9.95e-10 * 2_pb;
                case 6000 : return 3.579e-11 * 2_pb;
                case 8000 : return 2.305e-12 * 2_pb;
                case 10000 : return 2.029e-13 * 2_pb;
                    DEFAULT(Mass(), pb);
                }
            case Process::ttBB : return 0.03206 * 2_pb;
            case Process::ttWWWW : return 0.24093E-05 * 2_pb;
            case Process::ttWWWB : return 0.70031E-06 * 2_pb;
            case Process::ttWWBB : return 0.71735E-06 * 2_pb;
            case Process::ttWBBB : return 0.32324E-06 * 2_pb;
            case Process::ttBBBB : return 0.30222E-06 * 2_pb;
                DEFAULT(Name(process), pb);
            }
        }
        DEFAULT(Name(DetectorGeometry::DetectorType()), pb);
        }
    }

    auto FileName(Process process) const {
        INFO0;
//         std::string name = MassDependent(process) ? "pp" : "PP";
        std::string name = "PP";
        name += "-" + Name(process) + "-" + boca::Name(DetectorGeometry::DetectorType());
        if (MassDependent(process)) name += "-" + boca::Name(Mass());
        return name;
    }

    void NewFile(Tag tag, Process process) {
        INFO0;
        AnalysisBase::NewFile(tag, this->FileName(process), this->Crosssection(process), LatexName(process), Mass());
    }

};

}

}

