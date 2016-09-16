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
class SubDom : public TopPartner<Tagger_>
{

protected:

    std::string Name() const override {
        return "Naturalness-SubDom-" + boca::Name(Settings::Collider()) + "-" + boca::units::Name(this->Mass()) + "-first";
    }

    void SetFiles(Tag tag, Stage) override {
        switch (tag) {
        case Tag::signal :
            this->NewFile(tag, Process::TTh);
            break;
        case Tag::background :
            this->NewFile(tag, Process::ttWWW);
            this->NewFile(tag, Process::ttWWB);
            this->NewFile(tag, Process::ttWBB);
            this->NewFile(tag, Process::ttBBB);
            break;
        }
    }

private:

    bool PassPreCut(boca::Event const&) const override {
//         if (event.Jets().size() < 5) return false;
//         if (event.Leptons().empty()) return false;
        return true;
    }

};

}

}
