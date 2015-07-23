#pragma once

#include "Analysis.hh"

namespace analysis {

namespace toppartner {

/**
 *
 * @brief Top partner analysis
 *
 * \author Jan Hajer
 *
 */
template<typename Tagger>
class Analysis : public analysis::Analysis<Tagger> {

public:

    Analysis()
    {
        this->tagger().set_analysis_name(ProjectName());
    }

protected:

    std::string ProjectName() const final
    {
        return  std::to_string(PreCut()) + "GeV-hB";
    }

    void SetFiles(const Tag tag) final {
        switch (tag)
        {
        case Tag::signal :
            //         NewFile(tag,"pp-Tth-bbbbjjjjlv");
            //         NewFile(tag,"pp-TThh-bbbbbbjjlv");
            //             this->NewFile(tag, "pp-TT-tthh-bbbbbbjjlv", Crosssection(tag), NiceName(tag));
            //           this->NewFile(tag, "pp-TT-tthB-hBbbjjlv", 4.832, NiceName(tag));
            this->NewFile(tag, "pp-TT-tthB-bbbbjjjjlv", 2*0.264 * 1000, NiceName(tag));
            //         if(tagger().name() == "Bottom") NewFile(tag,"pp-ttbbj-bbbbjjlv");
            break;
        case Tag::background :
            //         NewFile(tag,"pp-ttbb-bbbbjjlv");
            //       NewFile(tag,"pp-tthjj-bbbbjjjjlv);
            //             this->NewFile(tag, "pp-tthjj-bbbbjjjjlv_" + std::to_string(PreCut()) + "GeV", Crosssection(tag), NiceName(tag));
          this->NewFile(tag, "PP-ttBJJ-" + std::to_string(PreCut()) + "GeV", 2*0.1754 * 1000, "ttB(jj)|_{200 GeV}");
          this->NewFile(tag, "PP-tthB-" + std::to_string(PreCut()) + "GeV", 2*0.02535 * 1000, "ttB(jj)|_{200 GeV}");
            //         NewFile(tag,"tt_inc-LE-0GeV_0");
            break;
        }
    }

    std::string ProcessName() const final
    {
        return "toppartner";
    }

    long EventNumberMax() const override
    {
        return 5000;
        return 3000;
        return 1000;
        return 100;
        return 10;
        return 500;
    }

    std::string FilePath() const final
    {
        return "~/Projects/TopPartner/Analysis/";
    }

private:

    int PreCut() const
    {
        return 200;
        return 0;
    }

    int Mass() const
    {
        return 2000;
    }

    int PassPreCut(const Event& event) const final
    {
        Jets particles = event.Partons().GenParticles();
        particles = RemoveIfSoft(particles, PreCut());
        Jets tops = CopyIfParticle(particles, Id::top);
        Jets higgs = CopyIfParticle(particles, Id::higgs);

        Jets tchannel = RemoveIfMother(higgs,Id::top);
        tchannel = RemoveIfMother(tchannel,Id::top_partner);

        Jets vectors = CopyIfParticles(particles, Id::Z, Id::W);
        if (tops.size() < 2 || (higgs.size() < 1 && vectors.size() < 1)) return 0;
        return 1;
    }

    float Crosssection(const Tag tag) const
    {
        switch (tag) {
        case Tag::signal :
            return SignalCrosssection();
        case Tag::background :
            return BackgroundCrosssection();
        }
    }

    float BackgroundCrosssection() const
    {
        switch (PreCut()) {
        case 0 :
            return 4.119;
        case 200 :
            return 0.44;
        }
    }

    float SignalCrosssection() const
    {
        switch (Mass()) {
        case 2000 :
            return 0.001971;
        }
    }

    std::string NiceName(const Tag tag) const
    {
        switch (tag) {
        case Tag::signal :
            return "#tilde t_{h}#tilde t_{l}";
        case Tag::background :
            return "tthjj (" + std::to_string(PreCut()) + " GeV)";
        }
    }

};

}

}
