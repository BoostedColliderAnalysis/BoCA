# pragma once

# include "TCut.h"

# include "TMVA/Reader.h"

# include "ExRootAnalysis/ExRootTreeBranch.h"
# include "ExRootAnalysis/ExRootTreeWriter.h"

# include "Branch.hh"
# include "HJetDelphes.hh"
# include "Predicate.hh"
# include "HEvent.hh"
# include "Doublet.hh"

class Observable
{

public:

    Observable(float &value, const std::string &expression, const std::string &title, const std::string &unit, const std::string &latex);

    float *value() const;

    std::string expression() const;

    std::string title() const;

    std::string unit() const;

    char type() const;

private:

    std::string expression_;

    std::string title_;

    std::string unit_;

    char type_;

    float *value_;

};


/**
 * @brief Prepares multivariant analysis
 *
 */
namespace hanalysis
{
// template <class ReturnType>
class Tagger : public HObject
{

public:

    enum Stage {
        kTrainer,
        kReader
    };

    Tagger();

    void AddSignalTreeName(const std::string signal_tree_name) {
        signal_tree_names_.emplace_back(signal_tree_name);
    }

    void AddBackgroundTreeName(const std::string background_tree_name) {
        background_tree_names_.emplace_back(background_tree_name);
    }

    std::string branch_name() const {
        return tagger_name_;
    }

    void set_tagger_name(const std::string &tagger_name) {
        tagger_name_ = tagger_name;
        signal_file_names_ = {tagger_name};
        background_file_names_ = {"Not" + tagger_name};
    }

    std::string tagger_name() const {
        return tagger_name_;
    }

    std::string reader_name() const {
        return tagger_name_ + "Reader";
    }

    std::string name(const Stage stage) const {
        switch (stage) {
        case kTrainer :
            return tagger_name();
        case kReader :
            return reader_name();
        }
    }

    std::string name(const Stage stage, const Tag tag) const {
        std::string name;
        switch (stage) {
        case kTrainer :
            name = tagger_name();
            break;
        case kReader :
            name = reader_name();
            break;
        }
        switch (tag) {
        case kSignal :
            return name;
        case kBackground :
            return "Not" + name;
        }
    }

    std::string analysis_name() const {
        Print(kError, "Analysis Name", analysis_name_);
        return analysis_name_;
    }

    std::vector<Observable> observables() const {
        return variables_;
    }

    std::vector<Observable> spectators() const {
        return spectators_;
    }


    Strings signal_file_names() const {
        return signal_file_names_;
    }

    Strings signal_tree_names() const {
        return signal_tree_names_;
    }

    Strings background_file_names() const {
        return background_file_names_;
    }

    Strings background_tree_names() const {
        return background_tree_names_;
    }

    TCut cut() const {
        return cut_;
    }

    virtual void set_analysis_name(const std::string &analysis_name) {
        analysis_name_ = analysis_name;
    }

    std::string bdt_method_name() const {
        return bdt_method_name_;
    }

    std::string weight_branch_name() const {
        return weight_branch_name_;
    }

    std::string background_name() const {
        return "Not" + tagger_name_;
    }

    std::string signal_name() const {
        return tagger_name_;
    }

//     virtual float GetBdt(TObject *Branch, const TMVA::Reader &Reader);

    virtual int GetBdt(HEvent &event, const TMVA::Reader &reader) {
        Print(kError, "Get Bdt", "should be subclassed");
    }

    virtual int Train(hanalysis::HEvent &, const Tag tag) {
        Print(kError, "Train", "Should be subclassed", tag);
        return 0;
    }

    virtual float GetBranches(hanalysis::HEvent &event, Stage stage, const Tag tag) {
        Print(kError, "get branches", "Should be subclassed", "should be deleted");
        return 0;
    }

    Jets GranulatedJets(const Jets &NewEFlowJets);

    Jets GetJets(hanalysis::HEvent &Event, hanalysis::HJetTag &JetTag);

    Jets GetJets(hanalysis::HEvent &Event);

    Jets GetSubJets(const fastjet::PseudoJet &Jet, const int SubJetNumber);

    fastjet::PseudoJet GetMissingEt(hanalysis::HEvent &Event);

    virtual float ReadBdt(const TClonesArray &, const int) {
        Print(kError, "Read Bdt", "should be subclassed");
        return 0;
    }

    DetectorGeometry detector_geometry() const {
        return detector_geometry_;
    }

    void SetTreeBranch(ExRootTreeWriter &tree_writer, const Stage stage) {
        tree_branch_ = tree_writer.NewBranch(name(stage).c_str(), &Class());
    }

    virtual float Bdt(HEvent &event, const TMVA::Reader &reader) const {
        Print(kError, "Bdt", "should be subclassed");
    }



//     template<typename Container, typename O1, typename O2>
//     void each_value_and_pair(Container &container, O1 val_fun, O2 pair_fun) {
//         auto iterator_1 = std::begin(container);
//         auto end = std::end(container);
//         if (iterator_1 == end) return;
//
//         for (; iterator_1 != std::prev(end); ++iterator_1) {
//             val_fun(*iterator_1);
//             for (auto iterator_2 = std::next(iterator_1); iterator_2 != end; ++iterator_2) {
//                 pair_fun(*iterator_2, *iterator_1);
//                 pair_fun(*iterator_1, *iterator_2);
//             }
//         }
//     }
//
//     main() {
//         std::vector<char> values;
//         // populate values
//         // ....
//         each_value_and_pair(values,
//         [](char c1) {
//             std::cout << "value: " << c1 << std::endl;
//         },
//         [](char c1, char c2) {
//             std::cout << "pair: " << c1 << "-" << c2 << std::endl;
//         });
//     }













//     template < class ValueType >
//     class BasicType
//     {
//     public:
//       typedef ValueType basic_type;
//       basic_type value() { return value_; }
//       basic_type value_;
//     };
//
//     template<class T>
//     typedef ReturnType t;
//     std::vector<t>
// //     virtual auto
//     GetMultiplets(HEvent &event, const TMVA::Reader &reader) {
//       Print(kError, "Bdt", "should be subclassed");
//       std::vector<t> v;
//       return v;
//     }

protected:

    virtual void DefineVariables() = 0;

    virtual inline std::string ClassName() const {
        return "HMva";
    }

    Observable NewObservable(float &value, const std::string &title) const;

    Observable NewObservable(float &value, const std::string &title, const std::string &latex) const;

    void AddVariable(float &value, const std::string &title) {
        variables_.emplace_back(NewObservable(value, title));
    };

    void AddVariable(float &value, const std::string &title, const std::string &latex) {
        variables_.emplace_back(NewObservable(value, title, latex));
    };

    void AddSpectator(float &value, const std::string &title) {
        spectators_.emplace_back(NewObservable(value, title));
    };

    void ClearVectors() {
        variables_.clear();
        spectators_.clear();
    }

    int max_combi() {
        return max_combi_;
    }

    virtual TClass &Class() const {
        Print(kError, "Class", "should be subclassed");
        return *Branch::Class();
    }

    ExRootTreeBranch &tree_branch() {
        return *tree_branch_;
    }

    float Bdt(const TMVA::Reader &reader);

private:

    ExRootTreeBranch *tree_branch_;


    /**
     * @brief Name of the Analysis
     *
     */
    static std::string analysis_name_;

    /**
     * @brief Name of the Analysis
     *
     */
    std::string tagger_name_;

    /**
     * @brief Name of the Signal File
     *
     */
    Strings signal_file_names_;

    std::string cut_method_name_;

    std::string bdt_method_name_;

    std::string weight_branch_name_;


    TCut cut_;

    /**
     * @brief Names of the Background Files
     *
     */
    Strings background_file_names_;

    Strings background_tree_names_;

    Strings signal_tree_names_;

    std::vector<Observable> variables_;

    std::vector<Observable> spectators_;

    int max_combi_;

    DetectorGeometry detector_geometry_;

};
}
