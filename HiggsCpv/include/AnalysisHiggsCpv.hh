#pragma once

#include "EventShapes.hh"
#include "Analysis.hh"
#include "JetInfo.hh"
#include "TopLeptonicTagger.hh"
#include "Debug.hh"

namespace boca
{

/**
 * @brief Higgs CPV analysis
 *
 */
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
class Analysis : public boca::Analysis<Tagger>
{

public:

    Analysis() {
        DetectorGeometry::set_detector_type(DetectorType::CMS);
//         this->pre_cuts().PtLowerCut().Set(Id::higgs,200);
        //         this->pre_cuts().MassLowerCut().Set(Id::higgs,105);
//         this->pre_cuts().MassUpperCut().Set(Id::higgs,145);
        this->pre_cuts().MassLowerCut().Set(Id::higgs, 50. * GeV);
        this->pre_cuts().MassUpperCut().Set(Id::higgs, 150. * GeV);
        this->pre_cuts().SetSemiLeptonic(false);
//         NoHiggs(-1);
//         SingleHiggs(-1);
    }

protected:

private:

    std::string AnalysisName() const final {
        return  "CPV-after-tahoe";
    }

    void SetFiles(Tag tag, Stage) final {
        switch (tag) {
        case Tag::signal :
	    //             this->NewFile(tag, "gg-tth", 0.0098);
          this->NewFile(tag, "pp-tth", 0.02267 * pb, "tth");
	  //         this->NewFile(tag, "pp-ttx0-bbbbllnunu-1", 0.02071);
	  //             this->NewFile(tag, "pp-ttx0-bbbbllnunu-1", 0.008937);
	  //         this->NewFile(tag, "pp-ttx0-bbbbllnunu-0.5", 0.01193);
	  break;
        case Tag::background :
	  this->NewFile(tag, "pp-ttbb", 0.1266 * pb, "ttbb");
	  //             this->NewFile(tag, "pp-ttbb-bbbbllnunu", 3.457);
            break;
        }
    }

    /**
     * @brief Maximal number of Entries to analyse
     *
     */
    long EventNumberMax() const final {
        return 1000;
        return 5000;
        return 10000;
        return 100;
        return 10;
    }

    int PassPreCut(Event const& event, Tag) const final {
      //         if(this->template TaggerIs<WLeptonicTagger>()) return 0;
      //         if(this->template TaggerIs<TopLeptonicTagger>()) static_cast<TopLeptonicTagger&>(this->tagger()).semi_leptonic = false;
        Jets leptons = fastjet::sorted_by_pt(event.Leptons().leptons());
        if (leptons.size() < 2) return 0;
//         if (leptons.at(1).pt() < 40) return 0;
//         Jets jets = event.Hadrons().Jets();
//         Jets gen_particles = event.Partons().GenParticles();
//         Jets higgs = CopyIfParticles(gen_particles, Id::CP_violating_higgs, Id::higgs);
//         if (higgs.empty()) {
//         Error(NoHiggs(), higgs.size());
//             return 1;
//         }
//         if(higgs.front().pt() < 200) return 0;
//         static int pre_cut=0;
//         ++pre_cut;
//         Error(pre_cut);
//         Particle particle = higgs.front().user_info<JetInfo>().constituents().front().family().Particle();
//         Particle mother1 = higgs.front().user_info<JetInfo>().constituents().front().family().Mother();
//         Particle mother2 = higgs.front().user_info<JetInfo>().constituents().front().family().mother_2();
//         Particle grand_mother = higgs.front().user_info<JetInfo>().constituents().front().family().GrandMother();
// //         Error(particle.Id(),mother1.Id(),mother2.Id(),grand_mother.Id());
//         higgs = RemoveIfSingleMother(higgs);
//         Error(SingleHiggs(), higgs.size());
//         return higgs.size();
        return 1;
    }


//     std::string FilePath() const final {
//         return this->working_path_; // < ------ does it work? might cause problems
//         return "~/Projects/HiggsCpv/Analysis/";
//         return "/Users/jingren/HEP/Research/JanH/tth-analysis/";
//     }


//     static int NoHiggs(int zero = -10) {
//         static int i = -1;
//         if (zero != -10) i = zero;
//         ++i;
//         return i;
//     }
//
//     static int SingleHiggs(int zero = -10) {
//         static int j = -1;
//         if (zero != -10) j = zero;
//         ++j;
//         return j;
//     }

};

}

}
