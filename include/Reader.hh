#pragma once

#include "Tagger.hh"
#include "PreCuts.hh"
#include "TMVA/Reader.h"

namespace analysis {

/**
 * @brief read results of multivariant analysis
 * wrapper for TMVA::Reader
 *
 */
template<typename TaggerTemplate>
class Reader {

public:

    Reader()
    {
        AddVariable();
        BookMva(TMVA::Types::EMVA::kBDT);
    }

    Reader(Stage stage)
    {
        switch (stage) {
        case Stage::trainer :
            break;
        case Stage::reader :
            AddVariable();
            BookMva(TMVA::Types::EMVA::kBDT);
            break;
        }
    }

    int Bdt(const analysis::Event& event, const analysis::PreCuts& pre_cuts) const
    {
        return Tagger().GetBdt(event, pre_cuts, reader());
    }

    template <typename Input>
    auto Multiplets(const Input& input) const
    {
        PreCuts pre_cuts;
        return Tagger().Multiplets(input, pre_cuts, reader());
    }

//     template <typename Input1, typename Input2>
//     auto Multiplets(Input1 &input_1, Input2 &input_2) const {
//         return Tagger().Multiplets(input_1, input_2, reader());
//     }

    template <typename Input>
    auto Multiplet(const Input& input) const
    {
        return Tagger().Multiplet(input, reader());
    }

    template <typename Input1, typename Input2>
    auto Multiplet(const Input1& input_1, const Input2& input_2) const
    {
        return Tagger().Multiplet(input_1, input_2, reader());
    }

    template <typename Input>
    auto SubMultiplet(const Input& input, int number) const
    {
        return Tagger().SubMultiplet(input, reader(), number);
    }

    template <typename Input>
    auto SubMultiplet(const Input& input) const
    {
        return Tagger().SubMultiplet(input, reader());
    }

    const TaggerTemplate& Tagger() const
    {
      return tagger_;
    }

    void SetTreeBranch(exroot::TreeWriter& tree_writer,Stage stage)
    {
       Tagger().SetTreeBranch(tree_writer, stage);
    }

private:

    TaggerTemplate& Tagger()
    {
      return tagger_;
    }

    TaggerTemplate tagger_;

    const TMVA::Reader& reader() const
    {
      return reader_;
    }

    TMVA::Reader& reader()
    {
      return reader_;
    }

    TMVA::Reader reader_;

    void BookMva(TMVA::Types::EMVA mva)
    {
        //TMVA::IMethod &method = *
      reader().BookMVA(Tagger().MethodName(mva), Tagger().WeightFileName(mva));
    }

    void AddVariable()
    {
        for (const auto& observable : Tagger().Variables()) reader().AddVariable(observable.expression(), &observable.value());
        for (const auto& spectator : Tagger().Spectators()) reader().AddSpectator(spectator.expression(), &spectator.value());
    }

};

}
