/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Analysis.hh"
#include "DetectorGeometry.hh"
#include "physics/Units.hh"
#include "Debug.hh"

namespace boca
{

/**
 * @brief Standard Model analyses
 *
 */
namespace standardmodel
{

enum class Process
{
    tt,
    tt_lep,
    tt_had,
    hh,
    hh_bb,
    zz,
    zz_bb,
    ww,
    bb,
    cc,
    qq,
    gg
};

std::string ProcessName(Process process);

std::string LatexName(Process process);

std::string Name(Process process);


enum class Collider
{
    LHC, FHC, LE
};

std::string Name(Collider collider);

/**
 *
 * @brief Tagger ananlysis
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger>
class AnalysisStandardModel : public Analysis<Tagger>
{

public:

    AnalysisStandardModel() {
        if (collider_type() == Collider::LHC) DetectorGeometry::set_detector_type(DetectorType::CMS);
    }

protected:

    Momentum LowerPtCut() const {
        return 500_GeV;
        return 600_GeV;
        return 1_TeV;
        return 1.5_TeV;
        return 2_TeV;
        return 2.5_TeV;
        return 3_TeV;
        return 3.5_TeV;
        return 4_TeV;
        return 350_GeV;
        return 700_GeV;
        return 800_GeV;
        return 1.2_TeV;
    }

    Collider collider_type() const {
        return Collider::LHC;
        return Collider::LE;
        return Collider::FHC;
    }

    Momentum UpperPtCut() const {
        switch (Int(LowerPtCut())) {
        case 500 : return 600_GeV;
        case 600 : return 700_GeV;
        case 700 : return 1_TeV;
        case 1000 : return 1.5_TeV;
        case 1200 : return 1.5_TeV;
        case 1500 : return 2_TeV;
        case 2000 : return 2.5_TeV;
        case 2500 : return 3_TeV;
        case 3000 : return 3.5_TeV;
        case 3500 : return 4_TeV;
        case 4000 : return 4.5_TeV;
            Default(LowerPtCut(), at_rest);
        }
    }
    void NewFile(Tag tag, Process process) {
        boca::AnalysisBase::NewFile(tag, FileName(process), LatexName(process));
    }

    Momentum LowerQuarkCut() const {
        return LowerPtCut() * 1.01;
    }

    Momentum UpperQuarkCut() const {
        return UpperPtCut() * 0.99;
    }

private:

    long TrainNumberMax() const override {
        return 10000;
        return 1000;
        return 100;
        return 5000;
        return 500;
    }

    int BackgroundFileNumber() const {
        return 1;
        return 2;
        return 4;
        return 5;
        return 10;
    }

    Momentum MadGraphCut() const {
        switch (Int(LowerPtCut())) {
        case 500: return 500_GeV;
        case 600: return 500_GeV;
        case 700 : return 500_GeV;
        case 1000 : return 1_TeV;
        case 1200 : return 1_TeV;
        case 1500 : return 1_TeV;
        case 2000 : return 1_TeV;
        case 2500 : return 1_TeV;
        case 3000 : return 1_TeV;
        case 3500 : return 1_TeV;
        case 4000 : return 1_TeV;
            Default(LowerPtCut(), at_rest);
        }
    }

    std::string FileName(Process process) const {
        switch (collider_type()) {
        case Collider::LE : return ProcessName(process) + "_" + boca::Name(MadGraphCut());
        case Collider::LHC : return ProcessName(process) + "_14TeV-" + boca::Name(MadGraphCut());
            Default(ProcessName(process), "");
        }
    }

    std::string FilePath() const final {
        return this->WorkingPath() + "../";
    }

};

}

}
