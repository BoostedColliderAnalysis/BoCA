/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "AnalysisTopPartner.hh"
#include "Debug.hh"

namespace boca
{

namespace naturalness
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

protected:

    std::string AnalysisName() const override {
        INFO0;
        return "Naturalness-Pair-" + boca::Name(this->PreCut()) + "-" + Name(DetectorGeometry::DetectorType()) + "-" + boca::Name(this->Mass()) + "-full";
    }

//     std::string ProcessName() const override {
//         INFO0;
//         return "Naturalness-Pair";
//     }

    void SetFiles(Tag tag, Stage)override {
        INFO0;
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag, Process::TT);
            break;
        case Tag::background :
            this->NewFile(tag, Process::ttBjj);
            this->NewFile(tag, Process::ttBB);
//             this->NewFile(tag, Process::tthBjj);
            break;
        }
    }

private:

    int PassPreCut(Event const&, Tag) const override {
        INFO0;
//        std::vector<Jet> particles = event.Partons().GenParticles();
//         particles = RemoveIfSoft(particles, this->PreCut());
//        std::vector<Jet> tops = CopyIfParticle(particles, Id::top);
//        std::vector<Jet> higgs = CopyIfParticle(particles, Id::higgs);
//        std::vector<Jet>vectors = CopyIfParticles(particles, Id::Z, Id::W);
//        std::vector<Jet> partner = CopyIfParticle(particles, Id::top_partner);

//        std::vector<Jet> tchannel = RemoveIfMother(higgs,Id::top);
//         tchannel = RemoveIfMother(tchannel,Id::top_partner);

//         ERROR(partner.size());

//         if (tops.size() < 2 || (higgs.size() < 1 && vectors.size() < 1)) return 0;
        return 1;
    }

};

}

}
