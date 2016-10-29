/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/analysis/Analysis.hh"
#include "boca/Settings.hh"
// #define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

/**
* @brief Fermionic top partner
* @ingroup Examples
*
*/
namespace toppartner{

using namespace boca;

enum class Process
{
    TthLep,
    TthHad,
    TT,
    ttBjj,
    tthBjj,
    ttBBjj,
    ttBB,
    TTh,
    ttWWW,
    ttWWB,
    ttWBB,
    ttBBB,
    TThh,
    ttWWWW,
    ttWWWB,
    ttWWBB,
    ttWBBB,
    ttBBBB,
};

std::string Name(Process process);

latex::String LatexName(Process process);

bool MassDependent(Process process);

/**
* @brief Analyses
*
*/
namespace analysis{

/**
 *
 * @brief Top partner analysis
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger_>
class TopPartner : public boca::Analysis<Tagger_>
{
public:

    TopPartner() {
        INFO0;
// Settings::set_collider(Collider::lhc);
    }

protected:

    boca::Mass Mass() const {
        INFO0;
        return 4_TeV;
        return 2_TeV;
        return 1_TeV;
        return 500_GeV;
        return 8_TeV;
        return 1.5_TeV;
        return 6_TeV;
        return 10_TeV;
        return 1.5_TeV;
        return 3_TeV;
    }

    long TrainNumberMax() const override {
        INFO0;
        return 10000;
        return 1000;
        return 100;
        return 10;
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
        switch (Settings::Collider()) {
        case Collider::lhc : {
            switch (process) {
            case Process::TT :
                switch (static_cast<int>(Mass() / GeV)) {
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
                DEFAULT(toppartner::Name(process), pb);
            }
        }
        case Collider::future : {
            switch (process) {
            case Process::TthLep :
                switch (static_cast<int>(Mass() / GeV)) {
                case 1000 : return 0.003087_pb;
                    DEFAULT(Mass(), pb);
                }
            case Process::TthHad :
                switch (static_cast<int>(Mass() / GeV)) {
                case 500 : return 0.02534_pb;
                case 1000 : return 0.003087_pb;
                case 1500 : return 0.0006824_pb;
                case 2000 : return 0.0002097_pb;
                    DEFAULT(Mass(), pb);
                }
            case Process::TT :
                switch (static_cast<int>(Mass() / GeV)) {
                case 500 : return 6.726 * 2_pb;
                case 1000 : return 0.3919 * 2_pb;
                case 1500 : return 0.05993 * 2_pb;
                case 2000 : return 0.01468 * 2_pb;
                case 4000 : return 0.0003704 * 2_pb;
                case 8000 : return 4.924e-06 * 2_pb;
                    DEFAULT(Mass(), pb);
                }
            case Process::ttBjj :
                switch (static_cast<int>(PreCut() / GeV)) {
                case 0 : return 1.669 * 2_pb;
                    DEFAULT(Mass(), pb);
                }
            case Process::tthBjj :
                switch (static_cast<int>(PreCut() / GeV)) {
                case 0 : return 0.02535 * 2_pb;
                    DEFAULT(Mass(), pb);
                }
            case Process::TThh :
                switch (static_cast<int>(Mass() / GeV)) {
                case 500 : return 0.00365 * 2_pb;
                case 1000 : return 0.0001594 * 2_pb;
                case 2000 : return 5.939e-06 * 2_pb;
                case 4000 : return 1.44e-07 * 2_pb;
                case 8000 : return 1.489e-09 * 2_pb;
                    DEFAULT(Mass(), pb);
                }
            case Process::TTh :
                switch (static_cast<int>(Mass() / GeV)) {
                case 500 : return 0.7575 * 2_pb;
                case 1000 : return 0.02097 * 2_pb;
                case 2000 : return 0.0003506 * 2_pb;
                case 4000 : return 3.457e-6 * 2_pb;
                    DEFAULT(Mass(), pb);
                }
            case Process::ttBB : return 0.03206 * 2_pb;
            case Process::ttBBB : return 0.0003712 * 2_pb;
            case Process::ttWBB : return 0.0002817 * 2_pb;
            case Process::ttWWB : return 0.002644 * 2_pb;
            case Process::ttWWW : return 0.0003265 * 2_pb;
            case Process::ttWWWW : return 0.24093E-05 * 2_pb;
            case Process::ttWWWB : return 0.70031E-06 * 2_pb;
            case Process::ttWWBB : return 0.71735E-06 * 2_pb;
            case Process::ttWBBB : return 0.32324E-06 * 2_pb;
            case Process::ttBBBB : return 0.30222E-06 * 2_pb;
                DEFAULT(toppartner::Name(process), pb);
            }
        }
        DEFAULT(Name(Settings::Collider()), pb);
        }
    }

    auto FileName(Process process) const {
        INFO0;
//         std::string name = MassDependent(process) ? "pp" : "PP";
        std::string name = "PP";
        name += "-" + Name(process) + "-" + boca::Name(Settings::Collider());
        if (MassDependent(process)) name += "-" + boca::units::Name(Mass());
        return name;
    }

//     void NewFile(Tag tag, Process process) {
//         INFO0;
//         this->NewFile(tag, this->FileName(process), this->Crosssection(process), Names(toppartner::Name(process), LatexName(process)), Mass());
//     }

    boca::FileInfo File(Process process) {
        auto file = boca::FileInfo({this->FileName(process)}, Names(toppartner::Name(process), LatexName(process)), this->Crosssection(process), Mass());
        return file;
    }

    void AddSignal(Process process) {
        INFO0;
        boca::analysis::Base::AddSignal(File(process));
    }

    void AddBackground(Process process) {
        INFO0;
        boca::analysis::Base::AddBackground(File(process));
    }

};

}

}
