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
class AnalysisCharged : public Analysis
{

public:

    AnalysisCharged(Tagger &tagger);

    std::vector< File > Files(const Tag tag);

     std::string ProcessName()const {
        return "Charged";
    }

     std::string ProjectName() const;

//     std::string StudyName(const HAnalysis::HTagger Tagger) const;

    void SetTrees();

private:

    enum HProcessType {Htb, ttbb, ttcc, ttjj, tt};
    enum ColliderType {LHC, FHC, LE};

    // in GeV
     int Mass() const;

    // in GeV
     int PreCut() const;


    float MissingEt();

    float LeptonPt();

     int EventNumberMax() const;;

     ColliderType collider_type() const;


     int BackgroundFileNumber() const;

    // in fb
    float SignalCrosssection() const;

     File BackgroundFile(const HProcessType Background) const;

    File BackgroundFile(const HProcessType Background, const int FileSum) const;

    std::string BackgroundTree(const HProcessType Background) const;

    float BackgroundCrosssection(const HProcessType Process) const;

    std::string ColliderName(const ColliderType Collider) const;

    std::string ProcessName(const HProcessType Process) const;

    int PassPreCut(const Event &event);

};

}

}
