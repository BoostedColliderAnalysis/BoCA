#pragma once

#include "Tagger.hh"
#include "Singlet.hh"
#include "TClonesArray.h"
#include "Predicate.hh"
#include "exroot/ExRootAnalysis.hh"

namespace analysis {

template<typename FileBranch>
class BranchTagger : public Tagger {

  const FileBranch& Branch() const final
  {
    return branch_;
  }

protected:

  FileBranch& Branch()
  {
    return branch_;
  }

    template<typename Multiplet>
    std::vector<Multiplet> ReduceResult(std::vector<Multiplet>& multiplets, size_t max = 4) const
    {
        if (multiplets.empty()) return multiplets;
        std::sort(multiplets.begin(), multiplets.end());
        multiplets.erase(multiplets.begin() + std::min(max, multiplets.size()), multiplets.end());
        return multiplets;
    }

    Jets ReduceResult(Jets& jets, size_t max = 4) const
    {
        if (jets.empty()) return jets;
        std::sort(jets.begin(), jets.end(), SortByBdt());
        jets.erase(jets.begin() + std::min(max, jets.size()), jets.end());
        return jets;
    }

    template<typename Multiplet>
    std::vector<Multiplet> BestMass(std::vector<Multiplet>& multiplets, float mass, size_t number = 1) const
    {
        if (multiplets.size() <= number) return multiplets;
        multiplets = SortedByMassTo(multiplets, mass);
        multiplets.erase(multiplets.begin() + number, multiplets.end());
        return multiplets;
    }

    template<typename Multiplet>
    std::vector<Multiplet> BestRapidity(std::vector<Multiplet>& multiplets, size_t number = 1) const
    {
        if (multiplets.size() <= number) return multiplets;
        multiplets = SortByMaxDeltaRap(multiplets);
        multiplets.erase(multiplets.begin() + number, multiplets.end());
        return multiplets;
    }

    template<typename Multiplet>
    std::vector<Multiplet> BestMatch(std::vector<Multiplet>& multiplets, const Jets& particles) const
    {
        if (multiplets.size() <= particles.size()) return multiplets;
        return CopyIfClose(multiplets, particles);
    }

    template<typename Multiplet>
    std::vector<Multiplet> RemoveBestMatch(std::vector<Multiplet>& multiplets, const Jets& particles) const
    {
        if (multiplets.size() <= particles.size()) return multiplets;
        return RemoveIfClose(multiplets, particles);
    }

    template<typename Multiplet>
    std::vector<Multiplet> BestMatches(std::vector<Multiplet>& multiplets, const Jets& particles, Tag tag) const
    {
        std::sort(multiplets.begin(), multiplets.end());
        switch (tag) {
        case Tag::signal :
            return BestMatch(multiplets, particles);
            break;
        case Tag::background  :
            return RemoveBestMatch(multiplets, particles);
            break;
        }
    }

    Jets BestMatches(Jets& jets, const Jets& particles, Tag tag) const
    {
        std::sort(jets.begin(), jets.end(), SortByBdt());
        switch (tag) {
        case Tag::signal :
            return BestMatch(jets, particles);
            break;
        case Tag::background  :
            return RemoveBestMatch(jets, particles);
            break;
        }
    }

    template<typename Multiplet>
    int SaveEntries(const std::vector<Multiplet>& multiplets, size_t max = LargeNumber()) const
    {
        if (multiplets.empty()) return 0;
//         std::sort(multiplets.begin(),multiplets.end());
        auto sum = std::min(multiplets.size(), max);
        for (const auto& counter : Range(sum)) {
            FillBranch(multiplets.at(counter));
            static_cast<FileBranch&>(*TreeBranch().NewEntry()) = Branch();
        }
        return sum;
    }

    int SaveEntries(const std::vector<fastjet::PseudoJet>& jets, size_t max = LargeNumber()) const
    {
        if (jets.empty()) return 0;
        for (const auto& counter : Range(std::min(jets.size(), max))) {
            FillBranch(Singlet(jets.at(counter)));
            static_cast<FileBranch&>(*TreeBranch().NewEntry()) = Branch();
        }
        return jets.size();
    }

    TClass& Class() const final
    {
        return *FileBranch::Class();
    }

    template<typename Multiplet>
    float Bdt(const Multiplet& multiplet, const TMVA::Reader& reader) const
    {
        FillBranch(multiplet);
        return Tagger::Bdt(reader);
    }

    float Bdt(const fastjet::PseudoJet& jet, const TMVA::Reader& reader) const
    {
        FillBranch(Singlet(jet));
        return Tagger::Bdt(reader);
    }

    void DefineVariables() override
    {
        ClearObservables();
        AddVariables();
        AddSpectators();
    }

private:

    float ReadBdt(const TClonesArray& clones_array, int entry) const final
    {
        return static_cast<FileBranch&>(*clones_array.At(entry)).Bdt;
    }

    void AddVariables()
    {
        for (const auto& variable : Branch().Variables())
            AddVariable(variable.value(), variable.name());
    }

    void AddSpectators()
    {
        for (const auto& spectator : Branch().Spectators())
            AddSpectator(spectator.value(), spectator.name());
    }

    template<typename Multiplet>
    void FillBranch(const Multiplet& multiplet) const
    {
        branch_.Fill(multiplet);
    }

    /**
     * @brief Branch storing the analysis results
     *
     */
    mutable FileBranch branch_;
};

}
