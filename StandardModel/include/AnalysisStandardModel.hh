#pragma once

#include "Analysis.hh"
#include "DetectorGeometry.hh"
#include "Debug.hh"

namespace analysis {

namespace standardmodel {

enum class Process {
    tt, tt_lep, tt_had, hh, hh_bb, zz, zz_bb, ww, bb, cc, qq, gg
};

std::string Name(Process process);

std::string NiceName(Process process);


enum class Collider {
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
class AnalysisStandardModel : public Analysis<Tagger> {

protected:

    int LowerPtCut() const
    {
        //         return 350;
        //         return 700;
        //         return 800;
        //     return 500;
        return 1000;
        //     return 1200;
    }

    long EventNumberMax() const override
    {
        return 5000;
//             return 1000;
//             return 100;
    }

    int BackgroundFileNumber() const
    {
        return 1;
        //         return 2;
        //       return 4;
        //       return 5;
        //       return 10;
    }

    Collider collider_type() const
    {
        //       return Collider::LHC;
        //       return Collider::FHC;
        return Collider::LE;
    }

    std::string FilePath() const final
    {
        return "~/Projects/Tagger/";
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

    void NewFile(Tag tag, Process process)
    {
        analysis::AnalysisBase::NewFile(tag, FileName(process), NiceName(process));
    }

    std::string FileName(Process process) const
    {
        return Name(process) + "_" + std::to_string(MadGraphCut()) + "GeV";
    }

};

}

}
