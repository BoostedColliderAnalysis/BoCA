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

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    std::vector<Doublet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

    std::string LatexName() const override;

    boost::optional<Doublet> Multiplet(boca::Doublet& doublet, const boca::PreCuts& pre_cuts, TMVA::Reader const& reader);

private:

    std::vector<Particle> Particles(Event const& event) const;

    boost::optional<Doublet> CheckDoublet(Doublet doublet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Doublet const& doublet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Doublet const& doublet, PreCuts const& pre_cuts) const;

    std::vector<Doublet> Doublets(Event const& event, std::function<boost::optional<Doublet>(Doublet&)> const& function);

    Reader<BottomTagger> bottom_reader_;

    Mass boson_mass_window;

};

}

}
