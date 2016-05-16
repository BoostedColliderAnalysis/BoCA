#pragma once

#include "boca/EventShapes.hh"
#include "boca/Analysis.hh"
#include "boca/standardmodel/TopLeptonicTagger.hh"
#include "boca/generic/DEBUG.hh"

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
        Settings::SetCollider(Collider::lhc);
//         this->PreCuts().PtLowerCut().Set(Id::higgs,200);
        //         this->PreCuts().MassLowerCut().Set(Id::higgs,105);
//         this->PreCuts().MassUpperCut().Set(Id::higgs,145);
        this->PreCuts().MassLowerCut().Set(Id::higgs, 50_GeV);
        this->PreCuts().MassUpperCut().Set(Id::higgs, 150_GeV);
        this->PreCuts().SetSemiLeptonic(false);
//         NoHiggs(-1);
//         SingleHiggs(-1);
    }

protected:

private:

    std::string AnalysisName() const override {
        return  "CPV-after-tahoe";
    }

    void SetFiles(Tag tag, Stage)override {
        switch (tag) {
        case Tag::signal :
	    //             this->NewFile(tag, "gg-tth", 0.0098);
          this->NewFile(tag, "pp-tth", 0.02267_pb, "tth");
	  //         this->NewFile(tag, "pp-ttx0-bbbbllnunu-1", 0.02071);
	  //             this->NewFile(tag, "pp-ttx0-bbbbllnunu-1", 0.008937);
	  //         this->NewFile(tag, "pp-ttx0-bbbbllnunu-0.5", 0.01193);
	  break;
        case Tag::background :
	  this->NewFile(tag, "pp-ttbb", 0.1266_pb, "ttbb");
	  //             this->NewFile(tag, "pp-ttbb-bbbbllnunu", 3.457);
            break;
        }
    }

    /**
     * @brief Maximal number of Entries to analyse
     *
     */
    long TrainNumberMax() const override {
        return 1000;
        return 5000;
        return 10000;
        return 100;
        return 10;
    }

    int PassPreCut(Event const& event, Tag) const override {
      //         if(this->template TaggerIs<WLeptonicTagger>()) return 0;
      //         if(this->template TaggerIs<TopLeptonicTagger>()) static_cast<TopLeptonicTagger&>(this->Tagger()).semi_leptonic = false;
       std::vector<Lepton> leptons = SortedByPt(event.Leptons().leptons());
        if (leptons.size() < 2) return 0;
//         if (leptons.at(1).Pt() < 40) return 0;
//        std::vector<Jet> jets = event.Hadrons().Jets();
//        std::vector<Jet>gen_particles = event.Partons().GenParticles();
//        std::vector<Jet> higgs = CopyIfParticles(gen_particles, Id::CP_violating_higgs, Id::higgs);
//         if (higgs.empty()) {
//         ERROR(NoHiggs(), higgs.size());
//             return 1;
//         }
//         if(higgs.front().Pt() < 200) return 0;
//         static int pre_cut=0;
//         ++pre_cut;
//         ERROR(pre_cut);
//         Particle particle = higgs.front().Info().constituents().front().family().Particle();
//         Particle mother1 = higgs.front().Info().constituents().front().family().Mother();
//         Particle mother2 = higgs.front().Info().constituents().front().family().mother_2();
//         Particle grand_mother = higgs.front().Info().constituents().front().family().GrandMother();
// //         ERROR(particle.Id(),mother1.Id(),mother2.Id(),grand_mother.Id());
//         higgs = RemoveIfSingleMother(higgs);
//         ERROR(SingleHiggs(), higgs.size());
//         return higgs.size();
        return 1;
    }


//     std::string FilePath() const override {
//         return this->WorkingPath();
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
