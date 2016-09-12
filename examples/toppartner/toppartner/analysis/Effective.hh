/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#pragma once

#include "toppartner/analysis/TopPartner.hh"

namespace toppartner{

namespace analysis{

/**
 *
 * @brief Top partner analysis
 *
 * @author Jan Hajer
 *
 */
template<typename Tagger_>
class Effective : public TopPartner<Tagger_>
{

protected:

    std::string Name() const override {
        return "Naturalness-Effective-" + boca::Name(Settings::Collider()) + "-" + boca::units::Name(this->Mass()) + "-latex";
    }

    void SetFiles(Tag tag, Stage)override {
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag, Process::TThh);
            break;
        case Tag::background :
            this->NewFile(tag, Process::ttWWWW);
            this->NewFile(tag, Process::ttWWWB);
            this->NewFile(tag, Process::ttWWBB);
            this->NewFile(tag, Process::ttWBBB);
            this->NewFile(tag, Process::ttBBBB);
            break;
        }
    }

private:

    int PassPreCut(boca::Event const&, Tag) const override {
//         if (event.Jets().size() < 5) return 0;
//         if (event.Leptons().empty()) return 0;
        return 1;
    }

};

}

}
