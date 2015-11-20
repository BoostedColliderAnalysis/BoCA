#pragma once

#include "TClonesArray.h"
#include "exroot/ExRootAnalysis.hh"

#include "Tagger.hh"
#include "Singlet.hh"
#include "Sort.hh"
#include "Vector.hh"
#include "Math.hh"
#include "Types.hh"

namespace analysis
{

template<typename BranchTemplate>
class BranchTagger : public Tagger
{

    const BranchTemplate& Branch() const final {
        return branch_;
    }

protected:

    BranchTemplate& Branch() {
        return branch_;
    }

    template<typename Multiplet>
    std::vector<Multiplet> ReduceResult(std::vector<Multiplet> multiplets, size_t max = 4) const {
        if (multiplets.empty()) return multiplets;
        std::sort(multiplets.begin(), multiplets.end());
        multiplets.erase(multiplets.begin() + std::min(max, multiplets.size()), multiplets.end());
        return multiplets;
    }

    Jets ReduceResult(Jets jets, size_t max = 4) const {
        if (jets.empty()) return jets;
        jets = SortedByBdt(jets);
        jets.erase(jets.begin() + std::min(max, jets.size()), jets.end());
        return jets;
    }

    template<typename Multiplet>
    std::vector<Multiplet> BestMass(std::vector<Multiplet> multiplets, float mass, size_t number = 1) const {
        if (multiplets.size() <= number) return multiplets;
        multiplets = SortedByMassTo(multiplets, mass);
        multiplets.erase(multiplets.begin() + number, multiplets.end());
        return multiplets;
    }

    template<typename Multiplet>
    std::vector<Multiplet> BestRapidity(std::vector<Multiplet> multiplets, size_t number = 1) const {
        if (multiplets.size() <= number) return multiplets;
        multiplets = SortedByMaxDeltaRap(multiplets);
        multiplets.erase(multiplets.begin() + number, multiplets.end());
        return multiplets;
    }

    template<typename Multiplet>
    std::vector<Multiplet> BestMatch(const std::vector<Multiplet>& multiplets, const Jets& particles) const {
        return CopyIfClose(multiplets, particles);
    }

    template<typename Multiplet>
    std::vector<Multiplet> RemoveBestMatch(const std::vector<Multiplet>& multiplets, const Jets& particles) const {
        return RemoveIfClose(multiplets, particles);
    }

    template<typename Multiplet>
    std::vector<Multiplet> BestMatches(std::vector<Multiplet> multiplets, const Jets& particles, Tag tag) const {
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

    Jets BestMatches(Jets jets, const Jets& particles, Tag tag) const {
        jets = SortedByBdt(jets);
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
    int SaveEntries(std::vector<Multiplet> multiplets, Jets & particles, Tag tag, Id id) const {
      multiplets = BestMatches(multiplets, particles, tag);
      if (multiplets.empty()) return 0;
      if (multiplets.size() > 1) {
        if(id == Id::empty) std::sort(multiplets.begin(), multiplets.end());
        else if(tag == Tag::signal) multiplets = SortedByMassTo(multiplets, Mass(id));
      }
      auto sum = multiplets.size();
      if(tag == Tag::signal) sum = std::min(multiplets.size(), particles.size());
      for (const auto & counter : Range(sum)) {
        FillBranch(multiplets.at(counter));
        static_cast<BranchTemplate&>(*TreeBranch().NewEntry()) = Branch();
      }
      return sum;
    }
    
//     template<typename Multiplet>
//     int SaveEntries(std::vector<Multiplet> multiplets, size_t max = LargeNumber(), Tag tag) const {
//       if (multiplets.empty()) return 0;
//       if (multiplets.size() > 1) std::sort(multiplets.begin(), multiplets.end());
//       auto sum = std::min(multiplets.size(), max);
//       if(tag == Tag::signal) sum = std::min(multiplets.size(), max);
//       for (const auto & counter : Range(sum)) {
//         FillBranch(multiplets.at(counter));
//         static_cast<BranchTemplate&>(*TreeBranch().NewEntry()) = Branch();
//       }
//       return sum;
//     }

    template<typename Multiplet>
    int SaveEntries(std::vector<Multiplet> multiplets, size_t max = LargeNumber()) const {
        if (multiplets.empty()) return 0;
        if (multiplets.size() > 1) std::sort(multiplets.begin(), multiplets.end());
        auto sum = std::min(multiplets.size(), max);
        for (const auto & counter : Range(sum)) {
            FillBranch(multiplets.at(counter));
            static_cast<BranchTemplate&>(*TreeBranch().NewEntry()) = Branch();
        }
        return sum;
    }

    int SaveEntries(std::vector<fastjet::PseudoJet> jets, size_t max = LargeNumber()) const {
        if (jets.empty()) return 0;
        if (jets.size() > 1) jets = SortedByBdt(jets);
        auto sum = std::min(jets.size(), max);
        for (const auto & counter : Range(sum)) {
            FillBranch(Singlet(jets.at(counter)));
            static_cast<BranchTemplate&>(*TreeBranch().NewEntry()) = Branch();
        }
        return sum;
    }

    template<typename Multiplet>
    int SaveEntries(std::vector<Multiplet> multiplets, Jets particles, Tag tag) const {
        return SaveEntries(BestMatches(multiplets, particles, tag));
    }

    int SaveEntries(std::vector<fastjet::PseudoJet> jets, Jets particles, Tag tag) const {
        return SaveEntries(BestMatches(jets, particles, tag));
    }

//     template<typename Multiplet>
//     int SaveEntries(const std::vector<Multiplet>& multiplets, const Jets& particles, Id id, Tag tag) const {
//         Jets type = CopyIfParticle(particles, id);
//         std::vector<Multiplet> matches = BestMatches(multiplets, type, tag);
//         if (matches.size() > type.size()) matches = SortedByMassTo(matches, id);
//         return SaveEntries(std::vector<Multiplet>(matches.begin(), matches.begin() + type.size()), type.size());
//     }
//
//     template<typename Multiplet>
//     int SaveEntries(const std::vector<Multiplet>& multiplets,const Jets& particles, int id, Tag tag) const {
//       Jets type = CopyIfExactParticle(particles, id);
//       std::vector<Multiplet> matches = BestMatches(multiplets, type, tag);
//       if (matches.size() > type.size()) matches = SortedByMassTo(matches, id);
//       return SaveEntries(std::vector<Multiplet>(matches.begin(), matches.begin() + type.size()), type.size());
//     }

    TClass& Class() const final {
        return *BranchTemplate::Class();
    }

    template<typename Multiplet>
    float Bdt(const Multiplet& multiplet, const TMVA::Reader& reader) const {
        FillBranch(multiplet);
        return Tagger::Bdt(reader);
    }

    float Bdt(const fastjet::PseudoJet& jet, const TMVA::Reader& reader) const {
        FillBranch(Singlet(jet));
        return Tagger::Bdt(reader);
    }

    void DefineVariables() override {
        ClearObservables();
        AddVariables();
        AddSpectators();
    }

private:

    float ReadBdt(const TClonesArray& clones_array, int entry) const final {
        return static_cast<BranchTemplate&>(*clones_array.At(entry)).Bdt;
    }

    void AddVariables() {
        for (const auto & variable : Branch().Variables()) AddVariable(variable.value(), variable.name());
    }

    void AddSpectators() {
        for (const auto & spectator : Branch().Spectators()) AddSpectator(spectator.value(), spectator.name());
    }

    template<typename Multiplet>
    void FillBranch(const Multiplet& multiplet) const {
        branch_.Fill(multiplet);
    }

    /**
     * @brief Branch storing the analysis results
     *
     */
    mutable BranchTemplate branch_;
};

}
