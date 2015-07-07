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

    std::string ProjectName() const;

    std::string ProcessName() const;

    int Mass() const;

    int PreCut() const;

    int EventNumberMax() const;;

    enum ColliderType {LHC, FHC, LE};

    ColliderType collider_type() const;

    float MissingEt();

    float LeptonPt();


    int BackgroundFileNumber() const;

private:

    enum ProcessType {Hbb, ttbb, ttcc, ttjj, tt};

    float SignalCrosssection() const;

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
