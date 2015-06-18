# pragma once

# include "Analysis.hh"

namespace analysis
{

namespace higgscpv
{

/**
 *
 * @brief HAnalysis subclass defining the HiggsCPV Analysis
 *
 * \author Jan Hajer
 *
 */
class Analysis : public analysis::Analysis
{

public:


    Analysis(Tagger &tagger);

    void SetFiles(const Object::Tag tag);

    inline std::string ProjectName() const {
        return  "HiggsCpv";
    }

    std::string ProcessName();

    /**
     * @brief Maximal number of Entries to analyse
     *
     */
    inline int EventNumberMax() const {
        return 1000;
    }

protected:


    virtual inline std::string FilePath() const {
        return "~/Projects/HiggsCpv/Analysis/";
    }

    virtual inline std::string NameSpaceName() const {
        return "higgscpv";
    }

private:

    int PassPreCut(Event &event);

};

}

}
