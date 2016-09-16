#pragma once

#include "standardmodel/analysis/StandardModel.hh"
#include "standardmodel/tagger/WHadronic.hh"

namespace standardmodel
{

namespace analysis
{

/**
 *
 * @brief HAnalysis subclass defining the W Tagger ananlysis
 *
 * @author Jan Hajer
 *
 */
template <typename Tagger_>
class W : public StandardModel<Tagger_>
{

public:

    W()
    {
        this->PreCuts().PtLowerCut().Set(Id::W, this->LowerPtCut());
        this->PreCuts().PtUpperCut().Set(Id::W, this->UpperPtCut());
//         this->PreCuts().MassUpperCut().Set(Id::W, 200_GeV);
        //     PreCuts().TrackerMaxEta().Set(Id::top, Settings::TrackerEtaMax);
        this->PreCuts().ConsiderBuildingBlock().Set(Id::W, false);
    }

    static Decay WDecay()
    {
        return Decay::hadronic;
        return Decay::leptonic;
    }

private:

    std::string Name() const override
    {
        return boca::Name(this->Collider()) + "-" + boca::units::Name(this->LowerPtCut()) + "-bottom";
    }


    void SetFiles(Tag tag, Stage stage)override
    {
        switch (tag) {
        case Tag::signal :
            if (!this->template TaggerIs<tagger::Bottom>()) this->NewFile(tag, Process::ww);
            if (this->template TaggerIs<tagger::Bottom>()) this->NewFile(tag, Process::bb);
            if (this->template TaggerIs<tagger::Bottom>()) this->NewFile(tag, Process::tt_had);
            if (this->template TaggerIs<tagger::Bottom>()) this->NewFile(tag, Process::tt_lep);
            if (this->template TaggerIs<tagger::Bottom>()) this->NewFile(tag, Process::hh);
            break;
        case Tag::background :
            this->NewFile(tag, Process::zz);
            this->NewFile(tag, Process::qq);
            this->NewFile(tag, Process::gg);
            this->NewFile(tag, Process::cc);
            if (this->template TaggerIs<tagger::WHadronic>() && stage == Stage::reader) this->NewFile(tag, Process::tt_had);
            if (!this->template TaggerIs<tagger::Bottom>()) this->NewFile(tag, Process::hh_bb);
            if (!this->template TaggerIs<tagger::Bottom>()) this->NewFile(tag, Process::bb);
            if (!this->template TaggerIs<tagger::Bottom>()) this->NewFile(tag, Process::tt_lep);
            break;
        }
    }

    bool PassPreCut(boca::Event const &event) const override
    {
        return true;
        auto particles = SortedByPt(event.GenParticles());
        if ((particles.at(0).Pt() > this->LowerQuarkCut() && particles.at(0).Pt() < this->UpperQuarkCut()) && (particles.at(1).Pt() > this->LowerQuarkCut() &&  particles.at(1).Pt() < this->UpperQuarkCut())) return true;
        return false;
    }

};

}

}
