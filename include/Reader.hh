/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Tagger.hh"
#include "PreCuts.hh"
#include "Options.hh"
#include "TMVA/Reader.h"

namespace boca
{

/**
 * @brief read results of multivariant analysis
 * wrapper for TMVA::Reader
 *
 */
template<typename TaggerTemplate>
class Reader
{

public:

    Reader() : reader_(Options()) {
        Initialize();
    }

    Reader(Stage stage) : reader_(Options()) {
        switch (stage) {
        case Stage::trainer :
            Tagger().Initialize();
            break;
        case Stage::reader :
            Initialize();
            break;
        }
    }

    void Initialize() {
        Tagger().Initialize();
        std::streambuf* cout = std::cout.rdbuf();
        std::ostringstream new_cout;
        std::cout.rdbuf(new_cout.rdbuf());
        AddVariable();
        BookMva(TMVA::Types::EMVA::kBDT);
        std::cout.rdbuf(cout);
    }

    int Bdt(Event const& event, PreCuts const& pre_cuts) const {
        return Tagger().SaveBdt(event, pre_cuts, reader());
    }

    template <typename Multiplet>
    float Bdt(Multiplet const& multiplet) const {
        return Tagger().Bdt(multiplet, reader());
    }

    template <typename Plet>
    Plet Multiplet(Plet multiplet, PreCuts const& pre_cuts) const {
        try {
            return Tagger().Multiplet(multiplet, pre_cuts, reader());
        } catch (char const*) {
            multiplet.SetBdt(-1);
            return multiplet;
        }
    }

    template <typename Input>
    auto Multiplets(Input const& input) const {
        PreCuts pre_cuts;
        return Tagger().Multiplets(input, pre_cuts, reader());
    }

//     template <typename Input1, typename Input2>
//     auto Multiplets(Input1 &input_1, Input2 &input_2) const {
//         return Tagger().Multiplets(input_1, input_2, reader());
//     }

    template <typename Input>
    auto Multiplet(Input const& input) const {
        return Tagger().Multiplet(input, reader());
    }

    template <typename Input1, typename Input2>
    auto Multiplet(Input1 const& input_1, Input2 const& input_2) const {
        return Tagger().Multiplet(input_1, input_2, reader());
    }

    template <typename Input>
    auto SubMultiplet(Input const& input, int number) const {
        return Tagger().SubMultiplet(input, reader(), number);
    }

    template <typename Input>
    auto SubMultiplet(Input const& input) const {
        return Tagger().SubMultiplet(input, reader());
    }

    TaggerTemplate const& Tagger() const {
        return tagger_;
    }

    void SetTreeBranch(exroot::TreeWriter& tree_writer, Stage stage) {
        Tagger().SetTreeBranch(tree_writer, stage);
    }

    TMVA::Reader const& reader() const {
        return reader_;
    }

private:

    std::string Options() const {
        boca::Options options;
//         options.Add("!V");
        options.Add("!Color");
//         options.Add("Silent");
        return options.str();
    }

    TaggerTemplate& Tagger() {
        return tagger_;
    }

    TaggerTemplate tagger_;

    TMVA::Reader& reader() {
        return reader_;
    }

    TMVA::Reader reader_;

    TMVA::IMethod &BookMva(TMVA::Types::EMVA mva) {
        return *reader().BookMVA(Tagger().MethodName(mva), Tagger().WeightFileName(mva));
    }

    void AddVariable() {
        for (auto const & observable : Tagger().Variables()) reader().AddVariable(observable.expression(), &observable.value());
        for (auto const & spectator : Tagger().Spectators()) reader().AddSpectator(spectator.expression(), &spectator.value());
    }

};

}
