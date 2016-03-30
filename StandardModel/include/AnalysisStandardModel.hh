/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "Analysis.hh"
#include "DetectorGeometry.hh"

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
        if (Collider() == boca::standardmodel::Collider::LHC) DetectorGeometry::SetDetectorType(DetectorType::CMS);
    }

protected:

    Momentum LowerPtCut() const {
        return 750_GeV;
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

    boca::standardmodel::Collider Collider() const {
        return boca::standardmodel::Collider::LHC;
        return boca::standardmodel::Collider::LE;
        return boca::standardmodel::Collider::FHC;
    }

    Momentum UpperPtCut() const {
        switch (int(LowerPtCut() / GeV)) {
        case 750 : return 1_TeV;
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
        default : std::cout << "Switch default for LowerPtCut of " << LowerPtCut() << std::endl;
            return at_rest;
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
        return 100;
        return 1000;
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
        switch (int(LowerPtCut() / GeV)) {
        case 500: return 500_GeV;
        case 600: return 500_GeV;
        case 700 : return 500_GeV;
        case 750 : return 750_GeV;
        case 1000 : return 1_TeV;
        case 1200 : return 1_TeV;
        case 1500 : return 1_TeV;
        case 2000 : return 1_TeV;
        case 2500 : return 1_TeV;
        case 3000 : return 1_TeV;
        case 3500 : return 1_TeV;
        case 4000 : return 1_TeV;
        default : std::cout << "Switch default for LowerPtCut of " << LowerPtCut() << std::endl;
            return at_rest;
        }
    }

    std::string FileName(Process process) const {
        switch (Collider()) {
        case boca::standardmodel::Collider::LE : return ProcessName(process) + "_" + boca::Name(MadGraphCut());
        case boca::standardmodel::Collider::LHC : return ProcessName(process) + "_14TeV-" + boca::Name(MadGraphCut());
        default : std::cout << "Switch default for process " << ProcessName(process) << std::endl;
            return "";
        }
    }

    std::string FilePath() const override {
        return this->WorkingPath() + "../";
    }

};

}

}
