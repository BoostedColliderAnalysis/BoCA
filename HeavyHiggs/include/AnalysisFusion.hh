#pragma once

#include "Analysis.hh"

namespace analysis
{

namespace heavyhiggs {

/**
 *
 * @brief HAnalysis subclass defining the HiggsCPV Analysis
 *
 * @author Jan Hajer
 *
 */
class AnalysisFusion : public Analysis
{

public:

      AnalysisFusion(Tagger &tagger);

    std::vector<File> Files(const Tag Tag);

     std::string ProcessName() const {
        return "Fusion";
    }

     std::string ProjectName() const;


//     std::string StudyName(const HAnalysis::Tagger Tagger) const;

//     void PrepareReader(const HAnalysis::HTagger Tagger, const HAnalysis::Tag Tag);

    void SetTrees();

private:

    enum ProcessType {Hbb, ttbb, ttcc, ttjj, tt, H0};
    enum ColliderType {LHC, FHC, LE};

    // in GeV
     int Mass() const;

    // in GeV
     int PreCut() const;

     int EventNumberMax() const;;

     ColliderType collider_type() const;

     int BackgroundFileNumber() const;


    // in fb
    float SignalCrosssection() const;

    float MissingEt();

    float LeptonPt();

     File BackgroundFile(const ProcessType Background) const;

    File BackgroundFile(const ProcessType Background, const int FileSum) const;

    std::string BackgroundTree(const ProcessType Process) const;

    float BackgroundCrosssection(const ProcessType Process) const;

    std::string ColliderName(const ColliderType Collider) const;

    std::string ProcessName(const ProcessType Process) const;

    int PassPreCut(const Event &event);

};

}

}
