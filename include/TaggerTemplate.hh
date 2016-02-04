/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

// #include "TClonesArray.h"

#include "exroot/ExRootAnalysis.hh"

#include "Sort.hh"
#include "Tagger.hh"
#include "PreCuts.hh"
#include "Filter.hh"
// #define INFORMATION
// #include "Debug.hh"

namespace boca
{

/**
 * @brief Tagger base class using Branch template
 *
 */
template<typename Multiplet_, typename Branch_>
class TaggerTemplate : public Tagger
{

public:

    float Bdt(Multiplet_ const& multiplet, TMVA::Reader const& reader) const {
        FillBranch(multiplet);
        return Tagger::Bdt(reader);
    }

    bool Cut(Multiplet_ const& multiplet, TMVA::Reader const& reader, float effeciency) const {
        FillBranch(multiplet);
        return Tagger::Cut(reader, effeciency);
    }

    std::vector<bool> Cuts(Multiplet_ const& multiplet, TMVA::Reader const& reader) const {
        FillBranch(multiplet);
        std::vector<bool> passed;
        int steps = 50;
        // TODO why is this a 2?
        for (auto const & effeciency : Range(2, steps)) passed.emplace_back(Tagger::Cut(reader, float(effeciency) / steps));
        return passed;
    }

    Branch_& Branch() final {
        return branch_;
    }

    int SaveBdt(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const final {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

protected:

    std::vector<Multiplet_> ReduceResult(std::vector<Multiplet_> multiplets, size_t max = 4) const {
        // DEBUG_CHECK(multiplets.size() >= max, multiplets.size());
        if (multiplets.empty()) return multiplets;
        multiplets = SortedByBdt(multiplets);
        multiplets.erase(multiplets.begin() + std::min(max, multiplets.size()), multiplets.end());
        return multiplets;
    }

    std::vector<Multiplet_> BestRapidity(std::vector<Multiplet_> multiplets, size_t number = 1) const {
        if (multiplets.size() <= number) return multiplets;
        multiplets = SortedByMaxDeltaRap(multiplets);
        multiplets.erase(multiplets.begin() + number, multiplets.end());
        return multiplets;
    }

    template<typename Multiplet_2>
    std::vector<Multiplet_2> BestMatch(std::vector<Multiplet_2> const& multiplets, std::vector<Particle> const& particles, Id id = Id::empty) const {
        std::vector<Multiplet_2> close = CopyIfClose(multiplets, particles);
        close = SortedByBdt(close);
        if (id != Id::empty) close = SortedByMassTo(close, id);
        return std::vector<Multiplet_2>(&close[0], &close[std::min(close.size(), particles.size())]);
    }

    template<typename Multiplet_2>
    std::vector<Multiplet_2> RemoveBestMatch(std::vector<Multiplet_2> const& multiplets, std::vector<Particle> const& particles) const {
        return RemoveIfClose(multiplets, particles);
    }

    template<typename Multiplet_2>
    std::vector<Multiplet_2> BestMatches(std::vector<Multiplet_2> multiplets, std::vector<Particle> const& particles, Tag tag, Id id = Id::empty) const {
        if (multiplets.empty()) return multiplets;
        multiplets = SortedByBdt(multiplets);
        switch (tag) {
        case Tag::signal : return BestMatch(multiplets, particles, id);
        case Tag::background : return RemoveBestMatch(multiplets, particles);
        default : return multiplets;
        }
    }

    int SaveEntries(std::vector<Multiplet_> multiplets, int max = std::numeric_limits<int>::max()) const {
        if (multiplets.empty()) return 0;
        if (multiplets.size() > 1) multiplets = SortedByBdt(multiplets);
        auto sum = std::min(int(multiplets.size()), max);
        for (auto const & counter : Range(sum)) {
            FillBranch(multiplets.at(counter));
            std::lock_guard<std::mutex> guard(mutex_);
            static_cast<Branch_&>(*TreeBranch().NewEntry()) = Branch();
        }
        return sum;
    }

    int SaveEntries(std::vector<Multiplet_> multiplets, std::vector<Particle> particles, Tag tag, Id id = Id::empty) const {
        return SaveEntries(BestMatches(multiplets, particles, tag, id));
    }

    int SaveEntries(std::vector<Multiplet_> multiplets, Tag tag) const {
        switch (tag) {
        case Tag::signal : return SaveEntries(multiplets, 1);
        case Tag::background : return SaveEntries(multiplets);
        default : return {};
        }
    }

    TClass& Class() const final {
        return *Branch_::Class();
    }

    void DefineVariables() override {
        ClearObservables();
        AddVariables();
        AddSpectators();
    }

    virtual auto Multiplets(Event const&, PreCuts const&, TMVA::Reader const&) const -> std::vector<Multiplet_> = 0;

    std::vector<Multiplet_> Multiplets(Event const& event, TMVA::Reader const& reader) const {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    };

private:

    Branch_ const& Branch() const final {
        return branch_;
    }

    void AddVariables() {
        Branch().Variables().AddFilter(Filter());
        for (auto & variable : Branch().Variables().Vector()) AddVariable(variable);
    }

    void AddSpectators() {
        for (auto & spectator : Branch().Spectators().Vector()) AddSpectator(spectator);
    }

    void FillBranch(Multiplet_ const& multiplet) const {
        branch_.Fill(multiplet);
    }

    /**
    * @brief Branch storing the analysis results
    *
    */
    mutable Branch_ branch_;

};

}

