/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once
#include <memory>

#include "TMVA/Reader.h"

#include "ReaderBase.hh"
#include "PreCuts.hh"
#include "Tagger.hh"
#include "Options.hh"
// #define INFORMATION
// #include "Debug.hh"
// #ifndef Info0
// #define Info0
// #endif

namespace boca
{

/**
 * @brief read results of multivariant analysis
 * wrapper for TMVA::Reader
 *
 */
template<typename TaggerTemplate>
class Reader : public ReaderBase
{

public:

    Reader() : reader_(new TMVA::Reader(Options())) {
        Initialize(Stage::reader);
    }

    Reader(Stage stage) : reader_(new TMVA::Reader(Options())) {
        Initialize(stage);
    }

    ~Reader() {
        std::lock_guard<std::mutex> guard(mutex_);
        delete reader_;
        reader_ = nullptr;
    }

    Reader(const Reader& that) :
        reader_(new TMVA::Reader(Options()))
        ,
        tagger_(that.tagger_) {
        Initialize(that.stage_);
    }

    Reader& operator=(Reader const& that) {
        if (&that == this) return *this;
        reader_ = new TMVA::Reader(Options());
        tagger_ = that.tagger_;
        Initialize(that.stage_);
        delete that.reader_;
        that.reader_ = nullptr;
        return *this;
    }

    void Initialize(Stage stage) {
        stage_ = stage;
        Tagger().Initialize();
        switch (stage) {
        case Stage::trainer : break;
        case Stage::reader : Initialize();
            break;
        }
    }

    void Initialize() {
        std::ofstream cout_file(Tagger().AnalysisName() + "/Reader.txt", std::ios_base::app | std::ios_base::out);
        std::streambuf* cout = std::cout.rdbuf();
        std::cout.rdbuf(cout_file.rdbuf());
        AddObservables();
        BookMva(TMVA::Types::EMVA::kBDT);
        std::cout.rdbuf(cout);
    }


//     Reader() : reader_(std::make_shared<TMVA::Reader>(Options())) {
// //         Info0;
//         stage_ = Stage::reader;
//         Initialize(stage_);
//     }
//
//     Reader(Stage stage) : reader_(std::make_shared<TMVA::Reader>(Options())) {
// //         INFO(Name(stage), tagger_.Name());
//         stage_ = stage;
//         Initialize(stage);
//     }
//
//     void Initialize(Stage stage) {
// //         INFO(Name(stage_), tagger_.Name());
//         switch (stage) {
//         case Stage::trainer :
//             Tagger().Initialize();
//             break;
//         case Stage::reader :
//             Tagger().Initialize();
//             Initialize();
//             break;
//         }
//     }
//
//     void Initialize() {
// //         INFO(Name(stage_), tagger_.Name());
//         std::ofstream cout_file(Tagger().AnalysisName() + "/Reader.txt", std::ios_base::app | std::ios_base::out);
//         std::streambuf* cout = std::cout.rdbuf();
//         std::cout.rdbuf(cout_file.rdbuf());
//         AddObservables();
//         BookMva(TMVA::Types::EMVA::kBDT);
//         std::cout.rdbuf(cout);
//     }

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
        } catch (std::exception const&) {
            multiplet.SetBdt(-1);
            return multiplet;
        }
    }

    template <typename Input>
    auto Multiplets(Input const& input) const {
        PreCuts pre_cuts;
        return Tagger().Multiplets(input, pre_cuts, reader());
    }

    template <typename Input>
    auto Jets(Input const& input) const {
        PreCuts pre_cuts;
        return Tagger().Jets(input, pre_cuts, reader());
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

    void NewBranch(exroot::TreeWriter& tree_writer, Stage stage) {
        Tagger().NewBranch(tree_writer, stage);
    }

    TMVA::Reader const& reader() const {
        return *reader_;
//         return *reader_.get();
    }

private:

    std::string Options() const {
        boca::Options options;
//         options.Add("V", false);
        options.Add("Color", false);
//         options.Add("Silent");
        return options;
    }

    void AddObservables() {
        std::lock_guard<std::mutex> guard(mutex_);
        for (auto const & observable : Tagger().Variables()) reader().AddVariable(observable.expression(), &observable.value());
        for (auto const & spectator : Tagger().Spectators()) reader().AddSpectator(spectator.expression(), &spectator.value());
    }

    TMVA::IMethod& BookMva(TMVA::Types::EMVA mva) {
        std::lock_guard<std::mutex> guard(mutex_);
        return *reader().BookMVA(Tagger().MethodName(mva), Tagger().WeightFileName(mva));
    }

    TMVA::Reader& reader() {
        return *reader_;
//         return *reader_.get();
    }

    TaggerTemplate& Tagger() {
        return tagger_;
    }

//     std::shared_ptr<TMVA::Reader> reader_;
    TMVA::Reader* reader_  = nullptr;

    TaggerTemplate tagger_;

    Stage stage_;


};

}
