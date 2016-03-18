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
 * @brief BDT tagger for W, Z and Higgs bosons.
 * @author Jan Hajer
 * @copyright Copyright (C) 2015-2016 Jan Hajer
 * @date 2015
 * @license GPL 3
 *
 */
class BosonTagger : public TaggerTemplate<Doublet, ZHadronicBranch>
{

public:

    BosonTagger();

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const override;

    std::vector<Doublet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const override;

    std::string Name() const override;

    std::string LatexName() const override;

    Doublet Multiplet(boca::Doublet& doublet, const boca::PreCuts& pre_cuts, const TMVA::Reader& reader) const;

private:

    std::vector<Particle> Particles(Event const& event) const;

    Doublet CheckDoublet(Doublet doublet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Doublet const& doublet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Doublet const& doublet, PreCuts const& pre_cuts) const;

    std::vector<Doublet> Doublets(Event const& event, std::function<Doublet(Doublet&)> const& function) const;

    Reader<BottomTagger> bottom_reader_;

    Mass boson_mass_window;

};

}

}
