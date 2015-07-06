#pragma once

#include "AnalysisCopy.hh"

namespace analysis
{

namespace toppartner
{

/**
 *
 * @brief Top partner analysis
 *
 * \author Jan Hajer
 *
 */
template<typename Tagger>
class Analysis : public analysis::Analysis<Tagger>
{

public:

    Analysis() {
        this->tagger().set_analysis_name(ProjectName());
    }

protected:

    void SetFiles(const Tag tag) {
        switch (tag) {
        case Tag::signal :
            //         NewFile(tag,"pp-Tth-bbbbjjjjlv");
            //         NewFile(tag,"pp-TThh-bbbbbbjjlv");
            Analysis::NewFile(tag, "pp-TT-tthh-bbbbbbjjlv", 0.001971);
            //         if(tagger().name() == "Bottom") NewFile(tag,"pp-ttbbj-bbbbjjlv");
            break;
        case Tag::background :
            //         NewFile(tag,"pp-ttbb-bbbbjjlv");
            //       NewFile(tag,"pp-tthjj-bbbbjjjjlv);
            Analysis::NewFile(tag, "pp-tthjj-bbbbjjjjlv_" + std::to_string(PreCut()) + "GeV", 2.671);
            //         NewFile(tag,"tt_inc-LE-0GeV_0");
            break;
        }
    }

    std::string ProjectName() const {
        return  "TopPartner_" + std::to_string(PreCut()) + "GeV-test2";
    }

    std::string ProcessName() {
        return "toppartner";
    }

    /**
     * @brief Maximal number of Entries to analyse
     *
     */
    int EventNumberMax() const {
        return 1000;
    }

    virtual  std::string FilePath() const {
        return "~/Projects/TopPartner/Analysis/";
    }


private:

    int PreCut() const {
        return 100;
    }

    int PassPreCut(const Event &event) {
//     Info();
        Jets particles = event.Partons().GenParticles();
        particles = RemoveIfSoft(particles, PreCut());
        Jets tops = copy_if_abs_particle(particles, Id::top);
        Jets higgs = copy_if_abs_particle(particles, Id::higgs);
        if (tops.size() < 2 || higgs.size() < 1) return 0;
        return 1;
    }

};

}

}
