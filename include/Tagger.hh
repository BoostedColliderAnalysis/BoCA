# pragma once

# include "TMVA/Reader.h"
# include "Event.hh"
# include "Observable.hh"
# include "PreCuts.hh"

namespace analysis
{

/**
 * @brief Prepares multivariant analysis
 *
 */
class Tagger : public Object
{

public:

    enum Stage {
        kTrainer,
        kReader
    };

    Tagger();

    void AddSignalTreeName(const std::string signal_tree_name);

    void AddBackgroundTreeName(const std::string background_tree_name);

    std::string branch_name() const;

    void set_tagger_name(const std::string &tagger_name);

    std::string tagger_name() const;

    std::string factory_name() const;

    std::string signal_file_name(const Stage stage) const;

    std::string background_file_name(const Stage stage) const;

    std::string reader_name() const;

    std::string name(const Stage stage) const;

    std::string name(const Stage stage, const Tag tag) const;

    std::string analysis_name() const;

    std::vector<Observable> observables() const;

    std::vector<Observable> spectators() const;

    Strings signal_file_names() const;

    Strings signal_tree_names() const;

    void clear_tree_names();

    Strings background_file_names() const;

    Strings background_tree_names() const;

    TCut cut() const;

    virtual void set_analysis_name(const std::string &analysis_name);

    std::string bdt_method_name() const;

    std::string bdt_weight_name() const;

    std::string weight_branch_name() const;

    std::string background_name() const;

    std::string signal_name() const;

    virtual int GetBdt(Event &, PreCuts &, const TMVA::Reader &);

    virtual int Train(analysis::Event &, PreCuts &, const Tag);

    Jets SubJets(const fastjet::PseudoJet &jet, const int sub_jet_number);

    fastjet::PseudoJet GetMissingEt(analysis::Event &event);

    virtual float ReadBdt(const TClonesArray &, const int) const = 0;

    void SetTreeBranch(exroot::TreeWriter &tree_writer, const Stage stage);

protected:

    virtual void DefineVariables() = 0;

    virtual  std::string ClassName() const {
        return "Tagger";
    }

    Observable NewObservable(float &value, const std::string &title) const;

    Observable NewObservable(float &value, const std::string &title, const std::string &latex) const;

    void AddVariable(float &value, const std::string &title);

    void AddVariable(float &value, const std::string &title, const std::string &latex);

    void AddSpectator(float &value, const std::string &title);

    void ClearObservables();

    virtual int max_combi() const;

    virtual TClass &Class() const = 0;

    exroot::TreeBranch &tree_branch();

    float Bdt(const TMVA::Reader &reader);


private:

    /**
     * @brief Tree Branch pointer saving the results
     *
     */
    exroot::TreeBranch *tree_branch_;

    /**
     * @brief Name of the Analysis
     *
     */
    static std::string analysis_name_;

    /**
     * @brief Name of the Tagger
     *
     */
    std::string tagger_name_;

    /**
     * @brief Names of the Signal Files
     *
     */
    Strings signal_file_names_;

    /**
     * @brief Names of the Background Files
     *
     */
    Strings background_file_names_;

    /**
     * @brief Names of the backgrund trees
     *
     */
    Strings background_tree_names_;

    /**
     * @brief Names of the signal trees
     *
     */
    Strings signal_tree_names_;

    /**
     * @brief variables for the analysis
     *
     */
    std::vector<Observable> variables_;

    /**
     * @brief spectators for the analysis
     *
     */
    std::vector<Observable> spectators_;

};

}
