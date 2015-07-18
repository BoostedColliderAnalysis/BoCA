#pragma once

#include "Analysis.hh"

namespace analysis {

namespace higgscpv {

/**
 *
 * @brief HAnalysis subclass defining the HiggsCPV Analysis
 *
 * \author Jan Hajer
 *
 */
template <typename Tagger>
class Analysis : public analysis::Analysis<Tagger> {

public:

    Analysis(){
        this->tagger().set_analysis_name(ProjectName());
    }

    void SetFiles(const Tag tag)
    {
        switch (tag) {
            case Tag::signal :
                //         NewSignalFile("pp-ttx0-bbbbllnunu-1", 0.02071);
                this->NewFile(tag,"pp-ttx0-bbbbllnunu-0", 0.008937);
                //         NewSignalFile("pp-ttx0-bbbbllnunu-0.5", 0.01193);
                break;
            case Tag::background :
                this->NewFile(tag,"pp-ttbb-bbbbllnunu", 3.457);
                break;
        }
    }

    std::string ProjectName() const
    {
        return  "HiggsCpv";
    }

    std::string ProcessName()
    {
        return "higgscpv";
    }

    /**
     * @brief Maximal number of Entries to analyse
     *
     */
    long EventNumberMax() const
    {
        return 5000;
        return 1000;
    }

protected:


    std::string FilePath() const
    {
        return "~/Projects/HiggsCpv/Analysis/";
    }

private:

    int PassPreCut(const Event& event) const
    {
        //   Jets particles = event.Partons().GenParticles();
        //   Jets tops = fastjet::sorted_by_pt(CopyIfParticle(particles, Id::top));
        //   remove_if_not_in_pt_window(tops, PreCut(), UpperCut());
        return 1;
    }

};

}

}
