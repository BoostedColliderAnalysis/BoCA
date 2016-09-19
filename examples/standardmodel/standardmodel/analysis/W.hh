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


    void SetFiles(Phase const& phase) override
    {
        switch (phase.Tag()) {
        case Tag::signal :
            if (!this->template TaggerIs<tagger::Bottom>()) this->AddSignal(Process::ww);
            if (this->template TaggerIs<tagger::Bottom>()) this->AddSignal(Process::bb);
            if (this->template TaggerIs<tagger::Bottom>()) this->AddSignal(Process::tt_had);
            if (this->template TaggerIs<tagger::Bottom>()) this->AddSignal(Process::tt_lep);
            if (this->template TaggerIs<tagger::Bottom>()) this->AddSignal(Process::hh);
            break;
        case Tag::background :
            this->AddBackground(Process::zz);
            this->AddBackground(Process::qq);
            this->AddBackground(Process::gg);
            this->AddBackground(Process::cc);
            if (this->template TaggerIs<tagger::WHadronic>() && phase.Stage() == Stage::reader) this->AddBackground(Process::tt_had);
            if (!this->template TaggerIs<tagger::Bottom>()) this->AddBackground(Process::hh_bb);
            if (!this->template TaggerIs<tagger::Bottom>()) this->AddBackground(Process::bb);
            if (!this->template TaggerIs<tagger::Bottom>()) this->AddBackground(Process::tt_lep);
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
