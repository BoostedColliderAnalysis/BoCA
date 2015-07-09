#pragma once

#include "Analysis.hh"

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

    std::string ProjectName() const final {
        return  std::to_string(PreCut()) + "GeV-test2";
    }

    void SetFiles(const Tag tag) final {
        switch (tag) {
        case Tag::signal :
            //         NewFile(tag,"pp-Tth-bbbbjjjjlv");
            //         NewFile(tag,"pp-TThh-bbbbbbjjlv");
//             Analysis::NewFile(tag, "pp-TT-tthh-bbbbbbjjlv", Crosssection(tag), NiceName(tag));
//           Analysis::NewFile(tag, "pp-TT-tthB-hBbbjjlv", 4.832, NiceName(tag));
          Analysis::NewFile(tag, "pp-TT-tthB-bbbbjjjjlv", 0.264, NiceName(tag));
            //         if(tagger().name() == "Bottom") NewFile(tag,"pp-ttbbj-bbbbjjlv");
            break;
        case Tag::background :
            //         NewFile(tag,"pp-ttbb-bbbbjjlv");
            //       NewFile(tag,"pp-tthjj-bbbbjjjjlv);
            Analysis::NewFile(tag, "pp-tthjj-bbbbjjjjlv_" + std::to_string(PreCut()) + "GeV", Crosssection(tag), NiceName(tag));
            //         NewFile(tag,"tt_inc-LE-0GeV_0");
            break;
        }
    }

    std::string ProcessName() {
        return "toppartner";
    }

    long EventNumberMax() const override {
        return 100;
        return 1000;
        return 10;
        return 500;
        return 3000;
    }

    std::string FilePath() const final {
        return "~/Projects/TopPartner/Analysis/";
    }

private:

    int PreCut() const {
        return 200;
        return 0;
    }

    int Mass() const {
        return 2000;
    }

    int PassPreCut(const Event &event) const {
        Jets particles = event.Partons().GenParticles();
        particles = RemoveIfSoft(particles, PreCut());
        Jets tops = CopyIfAbsParticle(particles, Id::top);
        Jets higgs = CopyIfAbsParticle(particles, Id::higgs);
        if (tops.size() < 2 || higgs.size() < 1) return 0;
        return 1;
    }

    float Crosssection(const Tag tag) const {
        switch (tag) {
        case Tag::signal :
            return SignalCrosssection();
        case Tag::background :
            return BackgroundCrosssection();
        }
    }

    float BackgroundCrosssection() const {
        switch (PreCut()) {
          case 0 :
            return 4.119;
        case 200 :
            return 0.44;
        }
    }

    float SignalCrosssection() const {
        switch (Mass()) {
        case 2000 :
            return 0.001971;
        }
    }

    std::string NiceName(const Tag tag) const {
        switch (tag) {
        case Tag::signal :
            return "TT";
        case Tag::background :
            return "tthjj (" + std::to_string(PreCut()) + " GeV)";
        }
    }

};

}

}
