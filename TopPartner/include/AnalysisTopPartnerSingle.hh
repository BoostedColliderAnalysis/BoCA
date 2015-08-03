#pragma once

#include "Analysis.hh"
#include "Debug.hh"

namespace analysis
{

namespace toppartner
{

enum class Process
{
    Tth,
    TT,
    ttBjj,
    tthBjj
};

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
        this->tagger().SetAnalysisName(ProjectName());
    }

protected:

    std::string ProjectName() const final {
        return  ProcessName() + "-" + std::to_string(PreCut()) + "GeV-jet-precut-100";
    }

    void SetFiles(Tag tag) final {
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag, "pp-Tth-ttBh-Bhbbjjlv", 2 * 0.04332 * 1000, NiceName(Process::Tth));
            break;
        case Tag::background :
            this->NewFile(tag, "PP-ttBJJ-" + std::to_string(PreCut()) + "GeV", 2 * 0.1754 * 1000, NiceName(Process::ttBjj));
            this->NewFile(tag, "PP-tthB-" + std::to_string(PreCut()) + "GeV", 2 * 0.02535 * 1000, NiceName(Process::tthBjj));
            this->NewFile(tag, "pp-TT-tthB-bbbbjjjjlv", 2 * 0.264 * 1000, NiceName(Process::TT));
            break;
        }
    }

    std::string ProcessName() const final {
        return "Naturalness";
    }

    long EventNumberMax() const override {
        return 5000;
        return 1000;
        return 3000;
        return 500;
        return 100;
        return 10;
    }

    std::string FilePath() const final {
        return "~/Projects/TopPartner/Analysis/";
    }

private:

    int PreCut() const {
        return 0;
        return 200;
    }

    int JetPreCut() const {
      return 100;
      return 0;
    }

    int Mass() const {
        return 2000;
    }

    int PassPreCut(const Event& event, Tag tag) const final {
        Jets jets = fastjet::sorted_by_pt(event.Hadrons().Jets());
        if(jets.size()<3) return 0;
        if(jets.at(2).pt() < JetPreCut()) return 0;


        Jets particles = event.Partons().GenParticles();
        particles = RemoveIfSoft(particles, PreCut());
        Jets tops = CopyIfParticle(particles, Id::top);
        Jets higgs = CopyIfParticle(particles, Id::higgs);
        Jets vectors = CopyIfParticles(particles, Id::Z, Id::W);
        Jets partner = CopyIfParticle(particles, Id::top_partner);
        if (tag == Tag::signal && partner.size() != 1) {
            return 0;
        }
        if (tops.size() < 2 || (higgs.size() < 1 && vectors.size() < 1)) {
            return 0;
        }
        return 1;
    }

    float Crosssection(Process process) const {
        switch (process) {
        case Process::Tth : return 2 * 0.04332 * 1000;
        case Process::TT : return 2 * 0.264 * 1000;
        case Process::ttBjj :
            switch (PreCut()) {
            case 0 : return 2 * 1.669 * 1000;
            case 200 : return 2 * 0.1754 * 1000;
            }
        case Process::tthBjj :
            switch (PreCut()) {
            case 0 : return 2 * 0.02535 * 1000;
            case 200 : return 2 * 0.02535 * 1000;
            }
        }
    }

    std::string NiceName(Process process) const {
        switch (process) {
        case Process::TT :
            return "#tilde t_{h}#tilde t_{l}";
        case Process::ttBjj :
            return "t_{l}t_{h}Bjj";
        case Process::tthBjj :
            return "t_{l}t_{h}hBjj";
        case Process::Tth :
            return "#tilde t_{l}t_{h}h";
        }
//         (" + std::to_string(PreCut()) + " GeV)";
    }

};

}

}
