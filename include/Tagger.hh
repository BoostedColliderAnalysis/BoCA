/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "TCut.h"

#include "TMVA/Types.h"

#include "Observable.hh"
#include "Identification.hh"
#include "Branches.hh"
#include "Vector.hh"
#include "Event.hh"
#include "Exception.hh"

namespace TMVA
{
class Reader;
}

class ExRootTreeWriter;
class ExRootTreeBranch;
namespace exroot
{
typedef ::ExRootTreeWriter TreeWriter;
typedef ::ExRootTreeBranch TreeBranch;
}

namespace boca
{

class PreCuts;
typedef std::vector<std::string> Strings;
typedef std::vector<Jet> Jets;

enum class Stage
{
    trainer,
    reader
};

std::string Name(Stage stage);

/**
 * @brief Prepares multivariant analysis
 *
 */
class Tagger
{

public:

    virtual std::string Name() const = 0;

    virtual int SaveBdt(Event const&, PreCuts const&, TMVA::Reader const&) const = 0;

    virtual int Train(Event const&, PreCuts const&, const Tag) const = 0;

//     virtual float ReadBdt(TClonesArray const&, int) const = 0;

    virtual const ResultBranch& Branch() const = 0;

    virtual ResultBranch& Branch() = 0;

    virtual std::string NiceName() const;

    virtual TMVA::Types::EMVA Mva() const;

    void Initialize();

    static void SetAnalysisName(std::string const& analysis_name);

    std::vector<Observable> const& Variables() const;

    std::vector<Observable> const& Spectators() const;

    Strings TreeNames(Tag tag) const;

    TCut Cut() const;

    std::string AnalysisName() const;

    std::string BranchName(Stage stage) const;

    std::string FactoryFileName() const;

    std::string ExportFileName() const;

    std::string ExportFileName(Stage stage, Tag tag) const;

    std::string ExportFolderName() const;

    std::string FolderName() const;

    std::string FileName(Stage stage, Tag tag) const;

    std::string MethodName() const;

    std::string WeightFileName() const;

    std::string WeightFileExtension() const;

    std::string WeightBranchName() const;

    void AddTreeName(std::string const& signal_tree_name, Tag tag);

    void NewBranch(exroot::TreeWriter& tree_writer, Stage stage);

    void ClearTreeNames();

    std::string ReaderName() const;

    std::string ReaderName(std::string const& name) const;

    static std::mutex mutex_;

protected:

    virtual TClass& Class() const = 0;

    virtual void DefineVariables() = 0;

   std::vector<Jet>SubJets(Jet const& jet, int sub_jet_number) const;

    Observable NewObservable(float& value, std::string const& title) const;

    void AddVariable(float& value, std::string const& title);

    void AddSpectator(float& value, std::string const& title);

    void ClearObservables();

    exroot::TreeBranch& TreeBranch() const;

    float Bdt(TMVA::Reader const& reader) const;

    bool Cut(TMVA::Reader const& reader, float eff) const;

    template<typename Multiplet>
    Multiplet SetTag(Multiplet& multiplet, Tag tag) const {
        multiplet.SetTag(tag);
        return multiplet;
    }

    template<typename Multiplet>
    Multiplet SetBdt(Multiplet& multiplet, TMVA::Reader const& reader) const {
        multiplet.SetBdt(Bdt(multiplet, reader));
        return multiplet;
    }

    template<typename Multiplet>
    std::vector<Multiplet> SetClosestLepton(Event const& event, std::vector<Multiplet>& multiplets) const {
       std::vector<Lepton> leptons = event.Leptons().leptons();
        if (leptons.empty()) return multiplets;
        for (auto & multiplet : multiplets) {
            try {
                SetClosestLepton(multiplet, leptons);
            } catch (std::exception const&) {
                continue;
            }
        }
        return multiplets;
    }

    template<typename Multiplet>
    Multiplet SetClosestLepton(Multiplet& multiplet,std::vector<Jet>& leptons) const {
        if (leptons.empty()) leptons.emplace_back(multiplet.Jet() * (DetectorGeometry::LeptonMinPt() / multiplet.Pt()));
        auto lepton = ClosestJet(leptons, multiplet);
        multiplet.LeptonPt = lepton.pt();
        multiplet.LeptonDeltaR = lepton.delta_R(multiplet.Jet());
        return multiplet;
    }

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

    std::string Name(Stage stage) const;

    std::string BranchName(Stage stage, Tag tag) const;


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
