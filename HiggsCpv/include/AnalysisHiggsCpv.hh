#pragma once

#include "Analysis.hh"
#include "Debug.hh"

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
template <typename Tagger>
class Analysis : public analysis::Analysis<Tagger>
{

public:

    Analysis() {
        this->tagger().set_analysis_name(ProjectName());
        DetectorGeometry::set_detector_type(DetectorType::CMS);
    }

    void SetFiles(const Tag tag) {
        switch (tag) {
        case Tag::signal :
            //         NewSignalFile("pp-ttx0-bbbbllnunu-1", 0.02071);
            this->NewFile(tag, "pp-ttx0-bbbbllnunu-1", 0.008937);
            //         NewSignalFile("pp-ttx0-bbbbllnunu-0.5", 0.01193);
            break;
        case Tag::background :
            this->NewFile(tag, "pp-ttbb-bbbbllnunu", 3.457);
            break;
        }
    }

    std::string ProjectName() const {
        return  "HiggsCpv-1";
    }

    std::string ProcessName() {
        return "higgscpv";
    }

    /**
     * @brief Maximal number of Entries to analyse
     *
     */
    long EventNumberMax() const {
        return 5000;
        return 1000;
    }

protected:


    std::string FilePath() const {
        return "~/Projects/HiggsCpv/Analysis/";
    }

private:

    int PassPreCut(const Event& event) const {
        Jets particles = event.Partons().GenParticles();
        Jets higgs = CopyIfParticle(particles, Id::CP_violating_higgs);
        if(higgs.empty()) return 1;
        higgs = RemoveIfSingleMother(higgs);
        return higgs.size();
    }

};

}

}
