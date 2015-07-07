#pragma once

#include "Analysis.hh"

namespace analysis
{

namespace heavyhiggs
{

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

    void SetTrees();

private:

    enum ProcessType {Hbb, ttbb, ttcc, ttjj, tt, H0};
    enum ColliderType {LHC, FHC, LE};

    int Mass() const;

    int PreCut() const;

    int EventNumberMax() const;;

    ColliderType collider_type() const;

    int BackgroundFileNumber() const;

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
