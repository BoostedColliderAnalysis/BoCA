#pragma once

#include "AnalysisTopPartner.hh"
#include "Debug.hh"

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
class AnalysisPair : public AnalysisNaturalness<Tagger>
{

public:

    AnalysisPair() {
        this->tagger().SetAnalysisName(ProjectName());
    }

protected:

    std::string ProjectName() const final {
      return ProcessName() + "-" + std::to_string(this->PreCut()) + "GeV-" + std::to_string(this->Mass()) + "GeV" ;
    }

    std::string ProcessName() const final {
        return "Naturalness-Pair";
    }

    void SetFiles(Tag tag) final {
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag, Process::TT);
            break;
        case Tag::background :
            this->NewFile(tag, Process::ttBjj);
            this->NewFile(tag, Process::tthBjj);
            break;
        }
    }

private:

    int PassPreCut(const Event&, Tag) const final {
//         Jets particles = event.Partons().GenParticles();
//         particles = RemoveIfSoft(particles, this->PreCut());
//         Jets tops = CopyIfParticle(particles, Id::top);
//         Jets higgs = CopyIfParticle(particles, Id::higgs);
//         Jets vectors = CopyIfParticles(particles, Id::Z, Id::W);
//         Jets partner = CopyIfParticle(particles, Id::top_partner);

//         Jets tchannel = RemoveIfMother(higgs,Id::top);
//         tchannel = RemoveIfMother(tchannel,Id::top_partner);

//         Error(partner.size());

//         if (tops.size() < 2 || (higgs.size() < 1 && vectors.size() < 1)) return 0;
        return 1;
    }

};

}

}
