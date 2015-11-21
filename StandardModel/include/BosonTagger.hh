/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "BottomTagger.hh"
#include "TaggerTemplate.hh"
#include "Doublet.hh"
#include "Reader.hh"

namespace boca
{

class Doublet;

namespace standardmodel
{


/**
 * @brief Derived Tagger class targeting W, Z and h bosons.
 * @author Jan Hajer
 * @copyright Copyright (C) 2015 Jan Hajer
 * @date 2015
 * @license GPL 3
 *
 */
class BosonTagger : public TaggerTemplate<Doublet, ZHadronicBranch>
{

public:

    BosonTagger();

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    std::vector<Doublet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    std::string Name() const final;

    std::string NiceName() const final;

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
