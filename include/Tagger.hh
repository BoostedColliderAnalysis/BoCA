#pragma once

#include "TCut.h"
#include "TMVA/Types.h"
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

    std::vector<Observable> Variables() const;

    std::vector<Observable> Spectators() const;

    Strings SignalTreeNames() const;

    Strings BackgroundTreeNames() const;

    Strings TreeNames(Tag tag) const;

    virtual std::string Name() const = 0;

    std::string BranchName(Stage stage) const;

    std::string FactoryFileName() const;

    std::string ExportFileName() const;

    std::string ExportFileName(Stage stage, Tag tag) const;

    std::string ExportFolderName() const;

    std::string FileName(Stage stage, Tag tag) const;

    std::string SignalFileName(Stage stage) const;

    std::string BackgroundFileName(Stage stage) const;

    std::string MethodName(TMVA::Types::EMVA mva) const;

    std::string WeightFileName(TMVA::Types::EMVA mva) const;

    std::string WeightFileExtension() const;

    std::string WeightBranchName() const;

    virtual int GetBdt(const Event&, const PreCuts&, const TMVA::Reader&) const = 0;

    virtual int Train(const Event&, const PreCuts&, const Tag) const = 0;

    virtual float ReadBdt(const TClonesArray&, const int) const = 0;

    void SetTreeBranch(exroot::TreeWriter& tree_writer, Stage stage);

    virtual std::string NiceName() const;

    std::string AnalysisName() const;

    void ClearTreeNames();

    TCut Cut() const;

    static void SetAnalysisName(const std::string& analysis_name);

    virtual const ResultBranch& Branch() const = 0;

protected:

    Jets SubJets(const fastjet::PseudoJet& jet, int sub_jet_number) const;

    virtual void DefineVariables() = 0;

    Observable NewObservable(float& value, const std::string& title) const;

    void AddVariable(float& value, const std::string& title);

    void AddSpectator(float& value, const std::string& title);

    void ClearObservables();

    virtual TClass& Class() const = 0;

    exroot::TreeBranch& TreeBranch() const;

    float Bdt(const TMVA::Reader& reader) const;

private:

  std::string Root() const;

  std::string PathName(const std::string& file_name, const std::string& suffix = ".root") const;

    std::string ReaderName() const;

    std::string ReaderName(const std::string& name) const;

    std::string WeightName(TMVA::Types::EMVA mva) const;

    std::string BackgroundName() const;

    std::string BackgroundName(const std::string& name) const;

    std::string SignalName() const;

    std::string SignalName(const std::string& name) const;

    std::string TrainerName() const;

    std::string ExportName() const;

    std::string Name(Stage stage, Tag tag) const;

    std::string Name(Stage stage) const;

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
