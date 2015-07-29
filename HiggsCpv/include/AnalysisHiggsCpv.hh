#pragma once

#include "EventShapes.hh"
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
        this->tagger().SetAnalysisName(ProjectName());
        DetectorGeometry::set_detector_type(DetectorType::CMS);
    }

    void SetFiles(Tag tag) final {
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag, "pp-tth", 0.02267);
            //         this->NewFile(tag, "pp-ttx0-bbbbllnunu-1", 0.02071);
//             this->NewFile(tag, "pp-ttx0-bbbbllnunu-1", 0.008937);
            //         this->NewFile(tag, "pp-ttx0-bbbbllnunu-0.5", 0.01193);
            break;
        case Tag::background :
            this->NewFile(tag, "pp-ttbb", 0.1266);
//             this->NewFile(tag, "pp-ttbb-bbbbllnunu", 3.457);
            break;
        }
    }

    std::string ProjectName() const final {
        return  "CPV-new";
    }

    std::string ProcessName() const final {
        return "higgscpv";
    }

    /**
     * @brief Maximal number of Entries to analyse
     *
     */
    long EventNumberMax() const final {
        return 1000;
        return 10000;
        return 5000;
        return 100;
    }

protected:


    std::string FilePath() const final {
        return "~/Projects/HiggsCpv/Analysis/";
    }

private:

    int PassPreCut(const Event& event, Tag) const final {
//         Jets jets = event.Hadrons().Jets();

        Jets gen_particles = event.Partons().GenParticles();
        Jets higgs = CopyIfParticle(gen_particles, Id::CP_violating_higgs);
        if (higgs.empty()) return 1;
        higgs = RemoveIfSingleMother(higgs);
        return higgs.size();
    }

};

}

}
