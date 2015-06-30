#pragma once

#include "Analysis.hh"

namespace analysis
{

/**
 * @brief Namespace for the heavy higgs analyses
 *
 */

namespace heavyhiggs
{

/**
 *
 * @brief HAnalysis subclass defining the HiggsCPV Analysis
 *
 * @author Jan Hajer
 *
 */
class AnalysisNeutral : public Analysis
{

public:

    AnalysisNeutral(Tagger &tagger);

    void SetTrees();

    std::vector<File> Files(const Tag tag);

     std::string ProjectName() const {
//        return  ProcessName() + "-" + ColliderName(collider_type()) + "-" + std::to_string(PreCut()) + "GeV-" + std::to_string(Mass()) + "GeV-Eta2.5";
        return  ProcessName() + "-" + ColliderName(collider_type()) + "-" + std::to_string(PreCut()) + "GeV-" + std::to_string(Mass()) + "GeV";
    }

     std::string ProcessName() const {
        return "Neutral";
    }

    // in GeV
     int Mass() const;

    // in GeV
     int PreCut() const;

     int EventNumberMax() const {
//            return 10000000;
//                   return 1000000;
//         return 100000;
        return 10000;
//                 return 1000;
//                         return 500;
//                         return 10;
    };



    enum ColliderType {LHC, FHC, LE};


     ColliderType collider_type() const {
        return LHC;
//       return FHC;
//        return LE;
    }

    float MissingEt();

    float LeptonPt();


     int BackgroundFileNumber() const;

private:

    enum ProcessType {Hbb, ttbb, ttcc, ttjj, tt};

    // in fb
    float SignalCrosssection() const;

     File BackgroundFile(const ProcessType Background) const;

    File BackgroundFile(const ProcessType Background, const int FileSum) const;

    std::string BackgroundTree(const ProcessType Process) const;

    float BackgroundCrosssection(const ProcessType Process) const;

    std::string ColliderName(const ColliderType Collider) const;

    std::string ProcessName(const ProcessType Process) const;


    int PassPreCut(Event &event);

};

}

}
