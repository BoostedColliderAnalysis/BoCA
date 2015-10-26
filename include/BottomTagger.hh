/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Branches.hh"
#include "TaggerTemplate.hh"


namespace boca
{

/**
 * @brief Derived Tagger class for bottom jets.
 * @author Jan Hajer
 * @copyright Copyright (C) 2015 Jan Hajer
 * @date 2015
 * @license GPL 3
 *
 */
class BottomTagger : public TaggerTemplate<fastjet::PseudoJet, BottomBranch>
{

public:

    BottomTagger();

    /**
     * @brief Train the bottom tagger with pre cuts
     */
    int Train(Event const& event, PreCuts const& pre_cuts, Tag tag) const final;

    /**
     * @brief Return all jets of the event with bottom bdt value considering pre cuts
     *
     */
    boca::Jets Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final;

    /**
     * @brief Return all jets of the event with bottom bdt value considering pre cuts
     *
     */
    boca::Jets Jets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    /**
     * @brief calculate bottom bdt for subjets of given jet
     *
     */
    boca::Jets SubMultiplet(fastjet::PseudoJet const& jet, TMVA::Reader const& reader, int sub_jet_number) const;

    /**
     * @brief calculate bottom bdt for given jet
     *
     */
    fastjet::PseudoJet Multiplet(fastjet::PseudoJet const& jet, TMVA::Reader const& reader) const;

    std::string Name() const final;

    std::string NiceName() const final;

private:

    boca::Jets Particles(Event const& event) const;

    boca::Jets Jets(Event const& event, PreCuts const& pre_cuts, std::function<fastjet::PseudoJet(fastjet::PseudoJet&)> const& function) const;

    boca::Jets Multiplets(boca::Jets jets, boca::PreCuts const& pre_cuts, std::function<fastjet::PseudoJet(fastjet::PseudoJet&)> const& function, unsigned sub_jet_number = 1) const;

    bool Problematic(fastjet::PseudoJet const& jet, boca::PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(fastjet::PseudoJet const& jet, boca::PreCuts const& pre_cuts) const;





//     boca::Jets Multiplets(boca::Jets const& jets, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;
//
//     boca::Jets SubMultiplets(boca::Jets const& jets, boca::PreCuts const& pre_cuts, TMVA::Reader const& reader, size_t sub_jet_number) const;


    boca::Jets SubJets(boca::Jets const& jets, int sub_jet_number) const;


    Mass bottom_max_mass_;

};

}
