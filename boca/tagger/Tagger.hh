/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/generic/Types.hh"
#include "boca/fastjet/Sort.hh"
#include "boca/io/TreeBranch.hh"
#include "boca/fastjet/Vector.hh"
#include "boca/tagger/Base.hh"
#include "boca/physics/PreCuts.hh"
#include "boca/Filter.hh"
#include "boca/generic/Debug.hh"

namespace boca
{

/**
 * @brief %Tagger base class using Branch template
 *
 */
template<typename Multiplet_, typename Branch_>
class Tagger : public tagger::Base
{

public:

    double Bdt(Multiplet_ const& multiplet, TMVA::Reader const& reader) {
        FillBranch(multiplet);
        return tagger::Base::Bdt(reader);
    }

    bool Cut(Multiplet_ const& multiplet, TMVA::Reader const& reader, double effeciency) {
        FillBranch(multiplet);
        return tagger::Base::Cut(reader, effeciency);
    }

    std::vector<bool> Cuts(Multiplet_ const& multiplet, TMVA::Reader const& reader) {
        FillBranch(multiplet);
        auto steps = 50;
        // TODO why is this a 2?
        return Transform(IntegerRange(2, steps), [&](int effeciency) {
            return tagger::Base::Cut(reader, static_cast<double>(effeciency) / steps);
        });
    }

    Branch_& Branch() override {
        return branch_;
    }

    int SaveBdt(Event const& event, const PreCuts& pre_cuts, TMVA::Reader const& reader) override {
        return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    template<typename Input_>
    std::vector<Multiplet_> ReducedMultiplets(Input_ const& input, const PreCuts& pre_cuts, TMVA::Reader const& reader, std::size_t max = 4) {
        return ReduceResult(Multiplets(input, pre_cuts, reader), max);
    }

    Multiplet_ Multiplet() const {
      return {};
    }

protected:

    virtual std::vector<Multiplet_> Multiplets(std::vector<Jet> const&, PreCuts const&, TMVA::Reader const&) {
        Error("Never end up here! Must be overlaoded");
        return {};
    }

    template<typename Multiplet_2_>
    std::vector<Multiplet_2_> ReduceResult(std::vector<Multiplet_2_> multiplets, std::size_t max = 4) const {
        // DEBUG_CHECK(multiplets.size() >= max, multiplets.size());
        if (multiplets.empty()) return multiplets;
        multiplets = SortedByBdt(multiplets);
        multiplets.erase(multiplets.begin() + std::min(max, multiplets.size()), multiplets.end());
        return multiplets;
    }

    std::vector<Multiplet_> BestRapidity(std::vector<Multiplet_> multiplets, std::size_t number = 1) const {
        if (multiplets.size() <= number) return multiplets;
        multiplets = SortedByMaxDeltaRap(multiplets);
        multiplets.erase(multiplets.begin() + number, multiplets.end());
        return multiplets;
    }

    template<typename Multiplet_2_, typename Particle_>
    std::vector<Multiplet_2_> BestMatch(std::vector<Multiplet_2_> const& multiplets, std::vector<Particle_> const& particles, Id id = Id::none) const {
        if (Debug()) boca::Debug("multiplets", multiplets.size(), "particles", particles.size());
        if (multiplets.empty()) return multiplets;
        std::vector<Multiplet_2_> best;
        for (auto const & particle : particles) Insert(best, BestMatch(multiplets, particle, id));
        if (Debug()) boca::Debug("best", best.size());
        return best;
    }

    template<typename Multiplet_2_, typename Particle_>
    std::vector<Multiplet_2_> BestMatch(std::vector<Multiplet_2_> const& multiplets, Particle_ const& particle, Id id = Id::none) const {
        if (Debug()) boca::Debug("multiplets", multiplets.size());
        if (multiplets.empty()) return multiplets;
        auto close = CopyIfClose(multiplets, particle);
        close = id == Id::none ? SortedByBdt(close) : SortedByMassTo(close, id);
        if (Debug()) boca::Debug("close", close.size());
        if (close.empty()) return close;
        return {close.front()};
    }

    template<typename Multiplet_2_>
    std::vector<Multiplet_2_> RemoveBestMatch(std::vector<Multiplet_2_> const& multiplets, std::vector<Particle> const& particles) const {
        return RemoveIfClose(multiplets, particles);
    }

    template<typename Multiplet_2_>
    std::vector<Multiplet_2_> RemoveBestMatch(std::vector<Multiplet_2_> const& multiplets, std::vector<std::pair<Particle, Particle>> const& particles) const {
        return RemoveIfClose(multiplets, particles);
    }

    template<typename Multiplet_2_>
    std::vector<Multiplet_2_> BestMatches(std::vector<Multiplet_2_> multiplets, std::vector<Particle> const& particles, Tag tag, Id id = Id::none) const {
        if (Debug()) boca::Debug("multiplets", multiplets.size(), "particles", particles.size());
        if (multiplets.empty()) return multiplets;
        multiplets = SortedByBdt(multiplets);
        switch (tag) {
        case Tag::signal : return BestMatch(multiplets, particles, id);
        case Tag::background : return RemoveBestMatch(multiplets, particles);
        default : return multiplets;
        }
    }

    template<typename Multiplet_2_>
    std::vector<Multiplet_2_> BestMatches(std::vector<Multiplet_2_> multiplets, std::vector<std::pair<Particle, Particle>> const& particles, Tag tag, Id id = Id::none) const {
        if (Debug()) boca::Debug("multiplets", multiplets.size(), "particles", particles.size());
        if (multiplets.empty()) return multiplets;
        multiplets = SortedByBdt(multiplets);
        switch (tag) {
        case Tag::signal : return BestMatch(multiplets, particles, id);
        case Tag::background : return RemoveBestMatch(multiplets, particles);
        default : return multiplets;
        }
    }

    int SaveEntries(std::vector<Multiplet_> multiplets, int max = std::numeric_limits<int>::max())  {
        if (multiplets.size() > 1) multiplets = SortedByBdt(multiplets);
        if (multiplets.empty()) return 0;
        auto sum = std::min(static_cast<int>(multiplets.size()), max);
        for (auto counter : IntegerRange(sum)) {
            FillBranch(multiplets.at(counter));
//             std::lock_guard<std::mutex> guard(mutex_);
            TreeBranch().AddEntry(Branch());
        }
        return sum;
    }

    int SaveEntries(std::vector<Multiplet_> multiplets, std::vector<Particle> const& particles, Tag tag, Id id = Id::none) {
        if (Debug()) boca::Debug("multiplets", multiplets.size(), "particles", particles.size());
        return SaveEntries(BestMatches(multiplets, particles, tag, id));
    }

    int SaveEntries(std::vector<Multiplet_> multiplets, Tag tag) {
        switch (tag) {
        case Tag::signal : return SaveEntries(multiplets, 1);
        case Tag::background : return SaveEntries(multiplets);
        default : return {};
        }
    }

    int SaveEntries(std::vector<Multiplet_> multiplets, std::vector<std::pair<Particle, Particle>> const& particles, Tag tag, Id id = Id::none) {
        return SaveEntries(BestMatches(multiplets, particles, tag, id));
    }

    TClass& Class() const override {
        return *Branch_::Class();
    }

    void DefineVariables() override {
        ClearObservables();
        AddVariables();
        AddSpectators();
    }

    virtual auto Multiplets(Event const&, PreCuts const&, TMVA::Reader const&) -> std::vector<Multiplet_> = 0;

    std::vector<Multiplet_> Multiplets(Event const& event, TMVA::Reader const& reader) {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    };

private:

    Branch_ const& Branch() const override {
        return branch_;
    }

    void AddVariables() {
        Branch().Variables().AddFilter(Filter());
        for (auto & variable : Branch().Variables().Vector()) AddVariable(variable);
    }

    void AddSpectators() {
        for (auto & spectator : Branch().Spectators().Vector()) AddSpectator(spectator);
    }

    void FillBranch(Multiplet_ const& multiplet) {
        Branch().Fill(multiplet);
    }

    constexpr bool Debug() const {
        return false;
    }

    /**
    * @brief Branch storing the analysis results
    *
    */
    Branch_ branch_;

};

}
