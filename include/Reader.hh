/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "TMVA/Reader.h"

#include "ReaderBase.hh"
#include "PreCuts.hh"
#include "Phase.hh"
#include "Options.hh"
#include "Sort.hh"
#include "Event.hh"

namespace boca
{

/**
 * @brief read results of multivariant analysis
 * wrapper for TMVA::Reader
 *
 */
template<typename Tagger_>
class Reader : public ReaderBase
{

public:

    Reader(Stage stage = Stage::reader) :
        reader_(Options()) {
        stage_ = stage;
        Initialize();
    }

    Reader(Reader const& reader) :
        reader_(Options()),
        stage_(reader.stage_),
        tagger_(reader.tagger_) {
        Initialize();
    }

    Reader(Reader const && reader) :
        reader_(Options()),
        stage_(std::move(reader.stage_)),
        tagger_(std::move(reader.tagger_)) {
        Initialize();
    }

    void Initialize() {
        Tagger().Initialize();
        if (stage_ == Stage::trainer) return;
        std::ofstream cout_file(Tagger().AnalysisName() + "/Reader.txt", std::ios_base::app | std::ios_base::out);
        std::streambuf* cout = std::cout.rdbuf();
        std::cout.rdbuf(cout_file.rdbuf());
        AddObservables();
        BookMva();
        std::cout.rdbuf(cout);
    }

    int Bdt(Event const& event, PreCuts const& pre_cuts) const {
        return Tagger().SaveBdt(event, pre_cuts, TReader());
    }

    template <typename Multiplet_>
    float Bdt(Multiplet_ const& multiplet) const {
        return Tagger().Bdt(multiplet, TReader());
    }

    template <typename Multiplet_>
    Multiplet_ Multiplet(Multiplet_ multiplet, PreCuts const& pre_cuts) const {
        try {
            return Tagger().Multiplet(multiplet, pre_cuts, TReader());
        } catch (std::exception const&) {
            multiplet.SetBdt(Tagger().MvaRange().Min());
            return multiplet;
        }
    }

    template <typename Input_>
    auto Multiplets(Input_ const& input, std::size_t number = 4) const {
        PreCuts pre_cuts;
        return Tagger().ReducedMultiplets(input, pre_cuts, TReader(), number);
    }

    template <typename Input_>
    auto Jets(Input_ const& input) const {
        PreCuts pre_cuts;
        return Tagger().Jets(input, pre_cuts, TReader());
    }

    auto Particles(Event const& event) const {
        return Tagger().Particles(event);
    }

    auto Multiplet(Jet& input) const {
        return Tagger().Multiplet(input, TReader());
    }

    template <typename Input_>
    auto Multiplet(Input_ const& input) const {
        return Tagger().Multiplet(input, TReader());
    }

    template <typename Input_1_, typename Input_2_>
    auto Multiplet(Input_1_ const& input_1, Input_2_ const& input_2) const {
        return Tagger().Multiplet(input_1, input_2, TReader());
    }

    template <typename Input_>
    auto SubMultiplet(Input_ const& input, int number) const {
        return Tagger().SubMultiplet(input, TReader(), number);
    }

    template <typename Input_>
    auto SubMultiplet(Input_ const& input) const {
        return Tagger().SubMultiplet(input, TReader());
    }

    Tagger_ const& Tagger() const {
        return tagger_;
    }

    void NewBranch(exroot::TreeWriter& tree_writer, Stage stage) {
        Tagger().NewBranch(tree_writer, stage);
    }

    template<typename Multiplet_>
    auto Transform(Event const& event) const {
        std::vector<Multiplet_> multiplets;
        for (auto const & multiplet : Multiplets(event)) {
            Multiplet_ new_multiplet;
            new_multiplet.Enforce(multiplet);
            multiplets.emplace_back(new_multiplet);
        }
        return multiplets;
    }

protected:

    TMVA::Reader const& TReader() const {
        return reader_;
    }

private:

    std::string Options() const {
        boca::Options options("Color", false);
//         options.Add("V", false);
//         options.Add("Silent");
        return options;
    }

    void AddObservables() {
        std::lock_guard<std::mutex> guard(mutex_);
        for (auto const & variable : Tagger().Variables()) TReader().AddVariable(variable.Expression(), &variable.Value());
        for (auto const & spectator : Tagger().Spectators()) TReader().AddSpectator(spectator.Expression(), &spectator.Value());
    }

    TMVA::IMethod& BookMva() {
        std::lock_guard<std::mutex> guard(mutex_);
        std::cout << Tagger().MethodName() << "  " << Tagger().WeightFileName() << std::endl;
        return *TReader().BookMVA(Tagger().MethodName(), Tagger().WeightFileName());
    }

    TMVA::Reader& TReader() {
        return reader_;
    }

    Tagger_& Tagger() {
        return tagger_;
    }

    TMVA::Reader reader_;

    Tagger_ tagger_;

    Stage stage_;

};

}

