#pragma once

#include "Analysis.hh"
#include "Debug.hh"

namespace analysis {

namespace standardmodel {

enum class Process {
    tt, tt_lep, tt_had, hh, hh_bb, zz, zz_bb, ww, bb, cc, qq, gg
};

std::string Name(const Process process);

std::string NiceName(const Process process);


enum class Collider {
    LHC, FHC, LE
};

std::string Name(const Collider collider);

/**
 *
 * @brief Tagger ananlysis
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger>
class AnalysisStandardModel : public Analysis<Tagger> {

protected:

    long EventNumberMax() const override
    {
//             return 100;
        //     return 1000;
        return 5000;
    }

    std::string FileName(const Process process) const
    {
        return Name(process) + "_" + std::to_string(MadGraphCut()) + "GeV";
    }

    std::string FilePath() const final
    {
        return "~/Projects/Tagger/";
    }

    int LowerPtCut() const
    {
        //         return 350;
        //         return 700;
        //         return 800;
        //     return 500;
        return 1000;
        //     return 1200;
    }

    int UpperPtCut() const
    {
        switch (LowerPtCut()) {
        case 700 :
            return 1000;
        case 1000 :
            return 1500;
        case 1200 :
            return 1500;
        case 500:
            return 1000;
        default :
            Error("no pt upper cut");
            return 0;
        }
    }

    int MadGraphCut() const
    {
        switch (LowerPtCut()) {
        case 500:
            return 500;
        case 700 :
            return 500;
        case 1000 :
            return 1000;
        case 1200 :
          return 1000;
        default :
          Error("no madgraph cut");
          return 0;
        }
    }

    int LowerQuarkCut() const
    {
        return LowerPtCut() * 0.9;
    }

    int UpperQuarkCut() const
    {
        return UpperPtCut() * 1.1;
    }

    Collider collider_type() const
    {
        //       return Collider::LHC;
        //       return Collider::FHC;
        return Collider::LE;
    }

    int BackgroundFileNumber() const
    {
        return 1;
        //         return 2;
        //       return 4;
        //       return 5;
        //       return 10;
    }

    void NewFile(const Tag tag, const Process process)
    {
        analysis::AnalysisBase::NewFile(tag, FileName(process), NiceName(process));
    }

};

}

}
