/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "BottomTagger.hh"
#include "TaggerTemplate.hh"
#include "multiplets/Doublet.hh"
#include "Reader.hh"

namespace boca
{

class Doublet;

namespace standardmodel
{

/**
 * @brief BDT tagger for higgs bosons decaying to jet pairs
 *
 */
class HiggsTagger : public TaggerTemplate<Doublet, HiggsBranch>
{

public:

    HiggsTagger();

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Doublet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    std::string LatexName() const override;

    std::vector<Particle> Particles(Event const& event) const;

private:

    std::vector<Doublet> Doublets(Event const& event, std::function<boost::optional<Doublet>(Doublet&)> const& function) const;

    boost::optional<Doublet> Multiplet(boca::Doublet& doublet, std::vector<Lepton>& leptons, const boca::PreCuts& pre_cuts, TMVA::Reader const& reader);

    boost::optional<Doublet> SetTag(boca::Doublet& doublet, std::vector<Lepton>& leptons, const boca::PreCuts& pre_cuts, boca::Tag tag);

    Doublet PrepareDoublet(const boca::Doublet& doublet, std::vector< boca::Lepton >& leptons);

    bool Problematic(Doublet const& doublet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Doublet const& doublet, PreCuts const& pre_cuts) const;

    boost::optional<Doublet> MassDrop(const boca::Doublet& doublet);

    Reader<BottomTagger> bottom_reader_;

    Mass higgs_mass_window;

};

}

}
