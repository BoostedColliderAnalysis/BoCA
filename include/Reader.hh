#pragma once

#include "TMVA/Reader.h"

#include "Tagger.hh"
#include "PreCuts.hh"
// #include "Debug.hh"

namespace analysis {

/**
 * @brief read results of multivariant analysis
 * wrapper for TMVA::Reader
 *
 */
template<typename TaggerTemplate>
class Reader {

public:

    Reader() : reader_(Options()) {
//       Info();
      Initialize();
    }

    Reader(Stage stage) : reader_(Options()) {
//       Info();
        switch (stage) {
        case Stage::trainer :
            break;
        case Stage::reader :
          Initialize();
            break;
        }
    }

    void Initialize(){
//       Info();
//       std::streambuf* cout = std::cout.rdbuf();
//       std::ostringstream new_cout;
//       std::cout.rdbuf(new_cout.rdbuf());
      AddVariable();
      BookMva(TMVA::Types::EMVA::kBDT);
//       std::cout.rdbuf(cout);
    }

    int Bdt(const analysis::Event& event, const analysis::PreCuts& pre_cuts) const
    {
//       Info();
        return Tagger().GetBdt(event, pre_cuts, reader());
    }

    template <typename Input>
    auto Multiplets(const Input& input) const
    {
//       Info();
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
//       Info();
        return Tagger().Multiplet(input, reader());
    }

    template <typename Input1, typename Input2>
    auto Multiplet(const Input1& input_1, const Input2& input_2) const
    {
//       Info();
        return Tagger().Multiplet(input_1, input_2, reader());
    }

    template <typename Input>
    auto SubMultiplet(const Input& input, int number) const
    {
//       Info();
        return Tagger().SubMultiplet(input, reader(), number);
    }

    template <typename Input>
    auto SubMultiplet(const Input& input) const
    {
//       Info();
        return Tagger().SubMultiplet(input, reader());
    }

    const TaggerTemplate& Tagger() const
    {
//       Info();
      return tagger_;
    }

    void SetTreeBranch(exroot::TreeWriter& tree_writer,Stage stage)
    {
//       Info();
       Tagger().SetTreeBranch(tree_writer, stage);
    }

private:

  std::string Options() const{
//     Info();
      return "";
//       return "!V:!color:Silent";
    }

    TaggerTemplate& Tagger()
    {
//       Info();
      return tagger_;
    }

    TaggerTemplate tagger_;

    const TMVA::Reader& reader() const
    {
//       Info();
      return reader_;
    }

    TMVA::Reader& reader()
    {
//       Info();
      return reader_;
    }

    TMVA::Reader reader_;

    void BookMva(TMVA::Types::EMVA mva)
    {
//       Info();
        //TMVA::IMethod &method = *
      reader().BookMVA(Tagger().MethodName(mva), Tagger().WeightFileName(mva));
    }

    void AddVariable()
    {
//       Info();
        for (const auto& observable : Tagger().Variables()) reader().AddVariable(observable.expression(), &observable.value());
        for (const auto& spectator : Tagger().Spectators()) reader().AddSpectator(spectator.expression(), &spectator.value());
    }

};

}
