/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "exroot/ExRootAnalysis.hh"

#include "Sort.hh"
#include "Tagger.hh"
#include "Singlet.hh"
#include "PreCuts.hh"
#include "Debug.hh"

namespace boca
{

/**
 * @brief Tagger base class using Branch template
 *
 */
template<typename MultipletTemplate, typename BranchTemplate>
class TaggerTemplate : public Tagger
{

public:

    float Bdt(MultipletTemplate const& multiplet, TMVA::Reader const& reader) const {
        Info();
        FillBranch(multiplet);
        return Tagger::Bdt(reader);
    }

//     void PreRequisits(Output output = Output::normal) {
//         Analysis<tagger> analysis;
//         Run(analysis, output);
//     }

    BranchTemplate& Branch() final {
        Info();
        return branch_;
    }

    int SaveBdt(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const final {
      return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

protected:

    std::vector<MultipletTemplate> ReduceResult(std::vector<MultipletTemplate> multiplets, size_t max = 4) const {
        Info();
        DebugCheck(multiplets.size() >= max, multiplets.size());
        if (multiplets.empty()) return multiplets;
        multiplets = SortedByBdt(multiplets);
        multiplets.erase(multiplets.begin() + std::min(max, multiplets.size()), multiplets.end());
        return multiplets;
    }

    std::vector<MultipletTemplate> BestMass(std::vector<MultipletTemplate> multiplets, Mass mass, size_t number = 1) const {
        Info();
        if (multiplets.size() <= number) return multiplets;
        multiplets = SortedByMassTo(multiplets, mass);
        multiplets.erase(multiplets.begin() + number, multiplets.end());
        return multiplets;
    }

    std::vector<MultipletTemplate> BestRapidity(std::vector<MultipletTemplate> multiplets, size_t number = 1) const {
        Info();
        if (multiplets.size() <= number) return multiplets;
        multiplets = SortedByMaxDeltaRap(multiplets);
        multiplets.erase(multiplets.begin() + number, multiplets.end());
        return multiplets;
    }

    template<typename T>
    std::vector<T> BestMatch(std::vector<T> const& multiplets, Jets const& particles, Id id = Id::empty) const {
        Info();
        std::vector<T> close = CopyIfClose(multiplets, particles);
        close = SortedByBdt(close);
        if (id != Id::empty) close = SortedByMassTo(close, id);
        return std::vector<T>(&close[0], &close[std::min(close.size(), particles.size())]);
    }

    template<typename T>
    std::vector<T> RemoveBestMatch(std::vector<T> const& multiplets, Jets const& particles) const {
        Info();
        return RemoveIfClose(multiplets, particles);
    }

    template<typename T>
    std::vector<T> BestMatches(std::vector<T> multiplets, Jets const& particles, Tag tag, Id id = Id::empty) const {
        Info();
        multiplets = SortedByBdt(multiplets);
        switch (tag) {
        case Tag::signal : return BestMatch(multiplets, particles, id);
        case Tag::background  : return RemoveBestMatch(multiplets, particles);
        }
    }

    int SaveEntries(std::vector<MultipletTemplate> multiplets, size_t max = LargeNumber()) const {
        Info();
        if (multiplets.empty()) return 0;
        if (multiplets.size() > 1) multiplets = SortedByBdt(multiplets);
        auto sum = std::min(multiplets.size(), max);
        for (auto const & counter : Range(sum)) {
            FillBranch(multiplets.at(counter));
            static_cast<BranchTemplate&>(*TreeBranch().NewEntry()) = Branch();
        }
        return sum;
    }

    int SaveEntries(std::vector<MultipletTemplate> multiplets, Jets particles, Tag tag, Id id = Id::empty) const {
        Info();
        return SaveEntries(BestMatches(multiplets, particles, tag, id));
    }

    int SaveEntries(std::vector<MultipletTemplate> multiplets, Tag tag) const {
      switch (tag) {
        case Tag::signal : return SaveEntries(multiplets, 1);
        case Tag::background : return SaveEntries(multiplets);
      }
    }

//
//     int SaveEntries(std::vector<MultipletTemplate> const& multiplets, Jets const& particles, Id id, Tag tag) const {
//         Jets type = CopyIfParticle(particles, id);
//         std::vector<MultipletTemplate> matches = BestMatches(multiplets, type, tag);
//         if (matches.size() > type.size()) matches = SortedByMassTo(matches, id);
//         return SaveEntries(std::vector<MultipletTemplate>(matches.begin(), matches.begin() + type.size()), type.size());
//     }
//
//
//     int SaveEntries(std::vector<MultipletTemplate> const& multiplets,Jets const& particles, int id, Tag tag) const {
//       Jets type = CopyIfExactParticle(particles, id);
//       std::vector<MultipletTemplate> matches = BestMatches(multiplets, type, tag);
//       if (matches.size() > type.size()) matches = SortedByMassTo(matches, id);
//       return SaveEntries(std::vector<MultipletTemplate>(matches.begin(), matches.begin() + type.size()), type.size());
//     }

    TClass& Class() const final {
        Info();
        return *BranchTemplate::Class();
    }

    void DefineVariables() override {
        Info();
        ClearObservables();
        AddVariables();
        AddSpectators();
    }

//     MultipletTemplate SetBdt(MultipletTemplate& multiplet, TMVA::Reader const& reader) {
//         multiplet.SetBdt(Bdt(multiplet, reader));
//         return multiplet;
//     }

    virtual std::vector<MultipletTemplate> Multiplets(Event const&, PreCuts const&, TMVA::Reader const&) const = 0;

    std::vector<MultipletTemplate> Multiplets(Event const& event, TMVA::Reader const& reader) const {
      Info();
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    };

private:

    const BranchTemplate& Branch() const final {
        Info();
        return branch_;
    }

    float ReadBdt(TClonesArray const& clones_array, int entry) const final {
        Info();
        return static_cast<BranchTemplate&>(*clones_array.At(entry)).Bdt;
    }

    void AddVariables() {
        Info();
        for (auto const & variable : Branch().Variables()) AddVariable(variable.value(), variable.name());
    }

    void AddSpectators() {
        Info();
        for (auto const & spectator : Branch().Spectators()) AddSpectator(spectator.value(), spectator.name());
    }

    void FillBranch(MultipletTemplate const& multiplet) const {
        Info();
        branch_.Fill(multiplet);
    }


    /**
     * @brief Branch storing the analysis results
     *
     */
    mutable BranchTemplate branch_;
};

template<>
inline void TaggerTemplate<fastjet::PseudoJet, BottomBranch>::FillBranch(fastjet::PseudoJet const& multiplet) const
{
    Info();
    branch_.Fill(Singlet(multiplet));
}

}


