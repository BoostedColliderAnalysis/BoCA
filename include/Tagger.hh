#pragma once

#include "TCut.h"
#include "Observable.hh"
#include "Identification.hh"
#include "fastjet/PseudoJet.hh"
#include "Branches.hh"

namespace TMVA {
class Reader;
}

class ExRootTreeWriter;
class ExRootTreeBranch;
namespace exroot {
typedef ::ExRootTreeWriter TreeWriter;
typedef ::ExRootTreeBranch TreeBranch;
}

namespace analysis {

class Event;
class PreCuts;
typedef std::vector<std::string> Strings;
typedef std::vector<fastjet::PseudoJet> Jets;

enum class Stage {
    trainer,
    reader
};

std::string Name(Stage stage);

/**
 * @brief Prepares multivariant analysis
 *
 */
class Tagger {

public:

    void AddSignalTreeName(const std::string& signal_tree_name);

    void AddBackgroundTreeName(const std::string& background_tree_name);

    std::string branch_name() const;

    virtual std::string Name() const = 0;

    std::string factory_name() const;

    std::string export_name() const;

    std::string signal_file_name(Stage stage) const;

    std::string background_file_name(Stage stage) const;

    std::string reader_name() const;

    std::string reader(const std::string& name) const;

    std::string Name(Stage stage) const;

    std::string Name(Stage stage, Tag tag) const;

    std::string analysis_name() const;

    std::vector<Observable> variables() const;

    std::vector<Observable> spectators() const;

    Strings signal_file_names() const;

    Strings signal_tree_names() const;

    void ClearTreeNames();

    Strings background_file_names() const;

    Strings background_tree_names() const;

    TCut cut() const;

    static void set_analysis_name(const std::string& analysis_name);

    std::string bdt_method_name() const;

    std::string bdt_weight_name() const;

    std::string weight_file_extension() const;

    std::string weight_branch_name() const;

    std::string background_name() const;

    std::string background(const std::string& name) const;

    std::string signal_name() const;

    std::string signal(const std::string& name) const;

    virtual int GetBdt(const Event&, const PreCuts&, const TMVA::Reader&) const = 0;

    virtual int Train(const Event&, const PreCuts&, const Tag) const = 0;

    Jets SubJets(const fastjet::PseudoJet& jet, int sub_jet_number) const;

    virtual float ReadBdt(const TClonesArray&, const int) const = 0;

    void SetTreeBranch(exroot::TreeWriter& tree_writer, Stage stage);

    virtual const ResultBranch& branch() const = 0;

    virtual ResultBranch& branch() = 0;

    virtual std::string NiceName() const;

protected:

    virtual void DefineVariables() = 0;

    Observable NewObservable(float& value, const std::string& title) const;

    void AddVariable(float& value, const std::string& title);

    void AddSpectator(float& value, const std::string& title);

    void ClearObservables();

    virtual int CandidatesMax() const;

    virtual TClass& Class() const = 0;

    exroot::TreeBranch& tree_branch() const;

    float Bdt(const TMVA::Reader& reader) const;

private:

    /**
     * @brief Tree Branch pointer saving the results
     *
     */
    exroot::TreeBranch* tree_branch_;

    /**
     * @brief Name of the Analysis
     *
     */
    static std::string analysis_name_;

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
