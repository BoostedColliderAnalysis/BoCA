/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "TCut.h"

#include "TMVA/Types.h"

#include "boca/generic/Vector.hh"
#include "boca/physics/Range.hh"
#include "boca/Observable.hh"
#include "boca/multivariant/Phase.hh"
#include "boca/Filter.hh"

namespace TMVA
{
class Reader;
}

namespace boca
{

class ResultBranch;
class PreCuts;
class Event;
class Jet;
class TreeWriter;
class TreeBranch;
/**
 * @brief Prepares multivariant analysis
 *
 */
class Tagger
{

public:

    virtual auto Name() const -> std::string = 0;

    virtual int SaveBdt(Event const&, PreCuts const&, TMVA::Reader const&) = 0;

    virtual auto Train(Event const&, PreCuts const&, const Tag) -> int = 0;

    virtual const ResultBranch& Branch() const = 0;

    virtual ResultBranch& Branch() = 0;

    virtual latex::String LatexName() const;

    virtual TMVA::Types::EMVA Mva() const;

    std::string MvaName() const;

    void Initialize(std::string const& analysis_name = "");

    std::vector<Observable> const& Variables() const;

    std::vector<Observable> const& Spectators() const;

    std::vector<std::string> TreeNames(Tag tag) const;

    std::vector<std::string> TreeNames(Phase const& phase) const;

    TCut Cut() const;

    std::string AnalysisName() const;

    std::string BranchName(Stage stage) const;

    std::string FactoryFileName() const;

    std::string ExportFileName() const;

    std::string ExportFileName(Stage stage, Tag tag) const;

    std::string ExportFileName(Phase const& phase) const;

    std::string ExportFolderName() const;

    std::string FolderName() const;

    std::string FileName(Stage stage, Tag tag) const;

    std::string FileName(Phase const& phase) const;

    std::string BranchName(Phase const& phase) const;

    std::string MethodName() const;

    std::string WeightFileName() const;

    std::string WeightFileExtension() const;

    std::string WeightBranchName() const;

    void AddTreeName(std::string const& signal_tree_name, Tag tag);

    void NewBranch(TreeWriter& tree_writer, boca::Stage stage);

    void ClearTreeNames();

    std::string ReaderName() const;

    std::string ReaderName(std::string const& name) const;

    virtual TClass& Class() const = 0;

protected:

    virtual void DefineVariables() = 0;

    std::vector<Jet>SubJets(Jet const& jet, int sub_jet_number) const;

    void AddVariable(Observable& observable);

    void AddSpectator(Observable& observable);

    void ClearObservables();

    boca::TreeBranch& TreeBranch() const;

    double Bdt(TMVA::Reader const& reader) const;

    bool Cut(TMVA::Reader const& reader, double eff) const;

    virtual boca::Filter Filter() const;

    Range<double> MvaRange() const;

private:

    std::string SignalFileName(Stage stage) const;

    std::string BackgroundFileName(Stage stage) const;

    std::string Root() const;

    std::string PathName(std::string const& file_name, std::string const& suffix = ".root") const;

    std::string WeightName() const;

    std::string BackgroundName() const;

    std::string BackgroundName(std::string const& name) const;

    std::string SignalName() const;

    std::string SignalName(std::string const& name) const;

    std::string TrainerName() const;

    std::string ExportName() const;

    std::string Name(Stage stage, Tag tag) const;

    std::string Name(Phase const& phase) const;

    std::string Name(Stage stage) const;

//     std::string BranchName(Stage stage, Tag tag) const;

    /**
     * @brief Tree Branch pointer saving the results
     *
     */
    boca::TreeBranch* tree_branch_;

    /**
     * @brief Name of the Analysis
     *
     */
//     static std::string analysis_name_;

    /**
     * @brief Names of the backgrund trees
     *
     */
    std::vector<std::string> background_tree_names_;

    /**
     * @brief Names of the signal trees
     *
     */
    std::vector<std::string> signal_tree_names_;

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
