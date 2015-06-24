# pragma once

# include "Analysis.hh"

namespace analysis
{

namespace top
{

/**
 *
 * @brief HAnalysis subclass defining the Top Tagger ananlysis
 *
 * @author Jan Hajer
 *
 */
class Analysis : public analysis::Analysis
{

public:

    Analysis(Tagger &tagger);

    void SetFiles(const Object::Tag tag);

    std::string ProjectName() const;

    enum Decay {kLeptonic, kHadronic, kSemi};

    Decay TopDecay() const;

protected:

    virtual  std::string FilePath() const;

    virtual  std::string NameSpaceName() const;

private:

    enum Process {Hbb, ttbb, ttcc, ttjj, bbjj, tt, bb, cc, qq, gg, wg, wq, wc, wb, wu, wcb, wbu, ttlep, tthad, hh, ww, zz};

    enum Collider {LHC, FHC, LE};

    void NewSignalFile(const Process process);

    void NewBackgroundFile(const Process process);

    std::string FileName(const Process process) const;

    // in GeV
    int LowerPtCut() const;

    // in GeV
    int UpperPtCut() const;

    // in GeV
    int MadGraphCut() const;

    int  LowerQuarkCut() const;

    int UpperQuarkCut() const;

    int EventNumberMax() const;

    Collider collider_type() const;

    int BackgroundFileNumber() const;

    File BackgroundFile(const Process process) const;

    File BackgroundFile(const Process process, const int file_sum) const;

    std::string BackgroundTree(const Process Process) const;

    std::string ColliderName(const Collider collider) const;

    std::string ProcessName(const Process process) const;

    int PassPreCut(Event &event);

    std::string NiceName(const Process process) const;

};

}

}
