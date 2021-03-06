/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/analysis/Analysis.hh"
#include "boca/Settings.hh"

/**
 * @brief Standard Model
 * @ingroup Examples
 *
 */
namespace standardmodel
{

using namespace boca;

/**
* @brief Standard model analyses
*
*/
namespace analysis
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

latex::String LatexName(Process process);

std::string Name(Process process);

/**
 *
 * @brief Standard model analysis base
 *
 */
template<typename Tagger_>
class StandardModel : public Analysis<Tagger_>
{

public:

    StandardModel() {
        Settings::SetCollider(Collider());
    }

protected:

    Momentum LowerPtCut() const {
        return 500_GeV;
        return 1_TeV;
        return 750_GeV;
        return 600_GeV;
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

    boca::Collider Collider() const {
        return boca::Collider::lhc;
        return boca::Collider::future;
    }

    Momentum UpperPtCut() const {
        switch (static_cast<int>(LowerPtCut() / GeV)) {
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
        default : std::cout << "Switch default for LowerPtCut of " << LowerPtCut() << '\n';
            return at_rest;
        }
    }

    void AddSignal(Process process) {
        boca::analysis::Base::AddSignal(File(process));
    }

    void AddBackground(Process process) {
        boca::analysis::Base::AddBackground(File(process));
    }

    Momentum LowerQuarkCut() const {
        return LowerPtCut() * 1.01;
    }

    Momentum UpperQuarkCut() const {
        return UpperPtCut() * 0.99;
    }

private:

    long TrainNumberMax() const override {
        return 500;
        return 10000;
        return 1000;
        return 100;
        return 5000;
    }

    int BackgroundFileNumber() const override {
        return 1;
        return 2;
        return 4;
        return 5;
        return 10;
    }

    Momentum MadGraphCut() const {
        switch (static_cast<int>(LowerPtCut() / GeV)) {
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
        default : std::cout << "Switch default for LowerPtCut of " << LowerPtCut() << '\n';
            return at_rest;
        }
    }

    std::string FileName(Process process) const {
        switch (Collider()) {
        case boca::Collider::future : return ProcessName(process) + "_" + boca::units::Name(MadGraphCut());
        case boca::Collider::lhc : return ProcessName(process) + "_14TeV-" + boca::units::Name(MadGraphCut());
        default : std::cout << "Switch default for process " << ProcessName(process) << '\n';
            return "";
        }
    }

//     std::string FilePath() const override {
//         return this->WorkingPath() + "../";
//     }

    boca::FileInfo File(Process process) const {
        auto file = boca::FileInfo({FileName(process)}, {Name(process), LatexName(process)});
        file.SetPath("../");
        return file;
    }

};

}

}
