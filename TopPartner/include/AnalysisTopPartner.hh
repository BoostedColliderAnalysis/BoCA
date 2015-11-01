/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Analysis.hh"
#include "Vector.hh"
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
    TThh
};

std::string Name(Process process);

std::string NiceName(Process process);

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
        Info0;
// DetectorGeometry::set_detector_type(DetectorType::CMS);
    }

protected:

    boca::Mass Mass() const {
        Info0;
        return 2000. * GeV;
        return 1000. * GeV;
        return 4000. * GeV;
        return 6000. * GeV;
        return 10000. * GeV;
        return 8000. * GeV;
        return 1500. * GeV;
        return 500. * GeV;
        return 3000. * GeV;
    }

    long EventNumberMax() const override {
        Info0;
        return 1000;
        return 10000;
        return 100;
        return 5000;
        return 10;
    }

protected:

    Momentum PreCut() const {
        Info0;
        return 0. * GeV;
        return 200. * GeV;
    }

    Momentum JetPreCut() const {
        Info0;
        return 0. * GeV;
        return 100. * GeV;
    }

    boca::Crosssection Crosssection(Process process) const {
        Info0;
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
                    Default(Mass(), pb);
                }
            case Process::ttBjj : return 0.03024 * 2 * pb;
            case Process::ttBB : return 0.0004068 * 2 * pb;
                Default(Name(process), pb);
            }
        }
        case DetectorType::Spp : {
            switch (process) {
            case Process::TthLep :
                switch (Int(Mass())) {
                case 1000 : return 0.004304 * pb;
                case 2000 : return 0.0002919 * pb;
                case 4000 : return 1.154e-05 * pb;
                case 6000 : return 4.7344e-6 * pb;
                case 8000 : return 8.466e-7 * pb;
                case 10000 : return 1.97e-7 * pb;
                    Default(Mass(), pb);
                }
            case Process::TthHad :
                switch (Int(Mass())) {
                case 1000 : return 0.004304 * pb;
                case 2000 : return 0.0002919 * pb;
                case 4000 : return 1.154e-05 * pb;
                case 6000 : return 4.7344e-6 * pb;
                case 8000 : return 8.466e-7 * pb;
                case 10000 : return 1.97e-7 * pb;
                    Default(Mass(), pb);
                }
            case Process::TT :
                switch (Int(Mass())) {
                case 1000 : return 2.499 * 2 * pb;
                case 2000 : return 0.09375 * 2 * pb;
                case 4000 : return 0.002363 * 2 * pb;
                case 6000 : return 0.0003115 * 2 * pb;
                case 8000 : return 4.655e-5 * 2 * pb;
                case 10000 : return 9.101e-06 * 2 * pb;
                    Default(Mass(), pb);
                }
            case Process::ttBjj :
                switch (Int(PreCut())) {
                case 0 : return 1.669 * 2 * pb;
                case 200 : return 0.1754 * 2 * pb;
                    Default(Mass(), pb);
                }
            case Process::tthBjj :
                switch (Int(PreCut())) {
                case 0 : return 0.02535 * 2 * pb;
                case 200 : return 0.02535 * 2 * pb;
                    Default(Mass(), pb);
                }
            case Process::TThh :
                switch (Int(Mass())) {
                case 2000 : return 1.143e-7 * 2 * pb;
                case 4000 : return 9.95e-10 * 2 * pb;
                case 6000 : return 3.579e-11 * 2 * pb;
                case 8000 : return 2.305e-12 * 2 * pb;
                case 10000 : return 2.029e-13 * 2 * pb;
                    Default(Mass(), pb);
                }
            case Process::ttBB : return 0.03206 * 2 * pb;
                Default(Name(process), pb);
            }
        }
        Default(Name(DetectorGeometry::detector_type()), pb);
        }
    }

    std::string FileName(Process process) const {
        Info0;
        std::string name = "PP-" + Name(process) + "-" + boca::Name(DetectorGeometry::detector_type());
        if (MassDependent(process)) name += "-" + boca::Name(Mass());
        return name;
    }

    void NewFile(Tag tag, Process process) {
        Info0;
        AnalysisBase::NewFile(tag, this->FileName(process), this->Crosssection(process), NiceName(process), Mass());
    }

};

}

}

