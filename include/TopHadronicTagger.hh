#pragma once

#include "WHadronicTagger.hh"
#include "Triplet.hh"

namespace analysis {

/**
 * @brief Hadronic top BDT tagger
 *
 */
class TopHadronicTagger : public BranchTagger<TopHadronicBranch> {

public:

    TopHadronicTagger();

    int Train(const Event& event, const PreCuts& pre_cuts, Tag tag) const final;

    int TopHadronicId(const Event& event) const
    {
        return sgn(w_hadronic_reader_.Tagger().WHadronicId(event)) * to_int(Id::top);
    }

    int GetBdt(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const  final
    {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    std::vector<analysis::Triplet> Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    std::string Name() const final
    {
        return "TopHadronic";
    }

    std::string NiceName() const final
    {
        return "t_{h}";
    }

private:

    analysis::Triplet Triplet(const Doublet& doublet, const fastjet::PseudoJet& jet, const Jets& leptons, const PreCuts& pre_cuts, Tag tag, const bool check_overlap = false) const;

    analysis::Triplet Triplet(analysis::Triplet& triplet, const analysis::Jets& leptons, const analysis::PreCuts& pre_cuts, Tag tag) const;

    std::vector<analysis::Triplet> Triplets(const std::vector<Doublet>& doublets, const Jets& jets, const Jets& leptons, const PreCuts& pre_cuts, Tag tag) const;

    std::vector<analysis::Triplet> Triplets(const Doublet& doublet, const Jets& jets, const Jets& leptons, const PreCuts& pre_cuts, Tag tag) const;

    std::vector<analysis::Triplet> Multiplets(const Event& event, const TMVA::Reader& reader) const
    {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::vector<analysis::Triplet>  Multiplets(const std::vector<Doublet>& doublets, const Jets& jets, const Jets& leptons, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    std::vector<analysis::Triplet>  Multiplets(const Doublet& doublet, const Jets& jets, const Jets& leptons, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    analysis::Triplet Multiplet(const Doublet& doublet, const fastjet::PseudoJet& jet, const Jets& leptons, const PreCuts& pre_cuts, const TMVA::Reader& reader, const bool check_overlap = false) const;

    analysis::Triplet Multiplet(analysis::Triplet& triplet, const Jets& leptons, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    bool Problematic(const analysis::Triplet& triplet, const PreCuts& pre_cuts, Tag tag) const;

    bool Problematic(const analysis::Triplet& triplet, const PreCuts& pre_cuts) const;

    void NSubJettiness(analysis::Triplet& triplet) const;

    SubJettiness NSubJettiness(const fastjet::PseudoJet& jet) const;

    float LeptonPt(const analysis::Triplet& triplet, const Jets& leptons) const;

    Reader<BottomTagger> bottom_reader_;

    Reader<WHadronicTagger> w_hadronic_reader_;

    float top_mass_window_ ;

};

}

