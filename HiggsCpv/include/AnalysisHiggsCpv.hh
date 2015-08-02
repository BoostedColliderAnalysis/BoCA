#pragma once

#include "EventShapes.hh"
#include "Analysis.hh"
#include "JetInfo.hh"
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
//         this->pre_cuts().SetPtLowerCut(Id::higgs,100);
        NoHiggs(-1);
        SingleHiggs(-1);
    }

    void SetFiles(Tag tag) final {
        switch (tag) {
        case Tag::signal :
          this->NewFile(tag, "gg-tth", 0.0098);
//             this->NewFile(tag, "pp-tth", 0.02267);
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
        return  "CPV-test";
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
        return 10;
        return 10000;
        return 5000;
    }

protected:


    std::string FilePath() const final {
        return "~/Projects/HiggsCpv/Analysis/";
    }

private:

    int PassPreCut(const Event& event, Tag) const final {
      if(this->tagger().Name() == "WLeptonic") return 0;
//         Jets jets = event.Hadrons().Jets();
        Jets gen_particles = event.Partons().GenParticles();
        Jets higgs = CopyIfParticles(gen_particles, Id::CP_violating_higgs,Id::higgs);
        if (higgs.empty()) {
//         Error(NoHiggs(), higgs.size());
          return 1;
        }
//         Particle particle = higgs.front().user_info<JetInfo>().constituents().front().family().particle();
//         Particle mother1 = higgs.front().user_info<JetInfo>().constituents().front().family().mother_1();
//         Particle mother2 = higgs.front().user_info<JetInfo>().constituents().front().family().mother_2();
//         Particle grand_mother = higgs.front().user_info<JetInfo>().constituents().front().family().grand_mother();
// //         Error(particle.id(),mother1.id(),mother2.id(),grand_mother.id());
//         higgs = RemoveIfSingleMother(higgs);
//         Error(SingleHiggs(), higgs.size());
        return higgs.size();
    }

static int NoHiggs(int zero = -10){
  static int i = -1;
  if(zero != -10) i = zero;
  ++i;
  return i;
}

static int SingleHiggs(int zero = -10){
  static int j = -1;
  if(zero != -10) j = zero;
  ++j;
  return j;
}

};

}

}
