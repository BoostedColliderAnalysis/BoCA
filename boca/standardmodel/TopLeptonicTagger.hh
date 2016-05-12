/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/standardmodel/BottomTagger.hh"
#include "boca/standardmodel/WLeptonicTagger.hh"
#include "boca/multiplets/Triplet.hh"
#include "boca/multivariant/Reader.hh"

namespace boca
{

namespace standardmodel
{

/**
 * @brief BDT tagger for leptonically decaying top quarks
 *
 */
class TopLeptonicTagger : public TaggerTemplate<Triplet, TopLeptonicBranch>
{

public:

    TopLeptonicTagger(Id id = Id::top);

    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) override;

    using TaggerTemplate::Multiplets;

    std::vector<Triplet> Multiplets(Event const& event, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::vector<Particle> Particles(boca::Event const& event) const;

    std::string Name() const override;

    latex::String LatexName() const override;

    boca::Filter Filter() const override;

private:

    bool Problematic(Triplet const& triplet, PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(Triplet const& triplet, PreCuts const& pre_cuts) const;

    std::vector<Triplet> Triplets(Event const& event, std::function<Triplet(Triplet&)> const& function);

    Stage InitializeLeptonicReader();

    Id id_;

    bool use_w_;

    Reader<BottomTagger> bottom_reader_;

    Reader<WLeptonicTagger> w_leptonic_reader_;

    Mass top_mass_window_;

    Mass top_mass_shift_;

//     std::vector<std::shared_ptr<Tagger>> Prerequisite() {
//         return
// //         Combine(
//         {new BottomTagger, new  WLeptonicTagger}
// //         , bottom_reader_.Tagger().Prerequisite(), w_leptonic_reader_.Tagger().Prerequisite())
// ;
//     }

};

}

}
