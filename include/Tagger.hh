# pragma once

# include "TCut.h"

# include "TMVA/Reader.h"

# include "ExRootAnalysis/ExRootTreeBranch.h"
# include "ExRootAnalysis/ExRootTreeWriter.h"

# include "HBranch.hh"
# include "HJetDelphes.hh"
# include "Predicate.hh"
# include "HEvent.hh"

class HObservable
{

public:

    HObservable(float &value, const std::string &expression, const std::string &title, const std::string &unit, const std::string &latex);

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
class hanalysis::Tagger : public HObject
{

public:

    enum Stage {
        kTrainer,
        kReader
    };

    /**
    * @brief Constructor
    *
    */
    Tagger();

    void SetTreeNames(const HStrings &tree_names) {
        signal_tree_names_ = tree_names;
        background_tree_names_ = tree_names;
    }

    void SetSignalTreeNames(const HStrings &signal_tree_names) {
        signal_tree_names_ = signal_tree_names;
    }

    void AddSignalTreeName(const std::string signal_tree_name) {
        signal_tree_names_.push_back(signal_tree_name);
    }

    void AddBackgroundTreeName(const std::string background_tree_name) {
        background_tree_names_.push_back(background_tree_name);
    }

    void SetBackgroundTreeNames(const HStrings &background_tree_names) {
        background_tree_names_ = background_tree_names;
    }

    void SetInputTreeNames(const HStrings &signal_tree_names, const HStrings &background_tree_names) {
        signal_tree_names_ = signal_tree_names;
        background_tree_names_ = background_tree_names;
    }

//     void SetBranchName(const std::string &branch_name) {
//         branch_name_ = branch_name;
//     }

    std::string GetBranchName() const {
//         return branch_name_;
        return tagger_name_;
    }

    void SetTaggerName(const std::string &tagger_name) {
        tagger_name_ = tagger_name;
//         branch_name_ = tagger_name;
//         signal_name_ = tagger_name;
        signal_names_ = {tagger_name};
//         background_name_ = "Not" + tagger_name;
        background_names_ = {"Not" + tagger_name};
//         test_name_ = tagger_name;
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
        if (tag == kBackground) return "Not" + name;
        else return name;
    }

    std::string analysis_name() const {
        return analysis_name_;
    }

    std::vector<HObservable> observables() const {
        return observables_;
    }

    std::vector<HObservable> spectators() const {
        return spectators_;
    }


    HStrings GetSignalNames() const {
        return signal_names_;
    }

    HStrings GetSignalTreeNames() const {
        return signal_tree_names_;
    }

    HStrings GetBackgroundNames() const {
        return background_names_;
    }

    HStrings GetBackgroundTreeNames() const {
        return background_tree_names_;
    }

//     std::string GetTestName() const {
//         return test_name_;
//     }

    TCut GetCut() const {
        return cut_;
    }

    void SetAnalysisName(const std::string &analysis_name) {
        analysis_name_ = analysis_name;
    }

    std::string GetCutMethodName()const {
        return cut_method_name_;
    }

    std::string BdtMethodName()const {
        return bdt_method_name_;
    }

    std::string GetWeightBranchName()const {
        return weight_branch_name_;
    }

    std::string GetBackgroundName() const {
//         return background_name_;
        return "Not" + tagger_name_;
    }

    std::string GetSignalName() const {
//         return signal_name_;
        return tagger_name_;
    }

    virtual float GetBdt(TObject *Branch, const TMVA::Reader &Reader);

    virtual int GetBdt(HEvent &event, const TMVA::Reader &reader) {
      Print(HError, "Get Bdt", "should be subclassed");
    }

    virtual int Train(hanalysis::HEvent &, const Tag tag) {
        Print(HError, "Train", "Should be subclassed", tag);
        return 0;
    }

    virtual float GetBranches(hanalysis::HEvent &event, Stage stage, const Tag tag) {
        Print(HError, "get branches", "Should be subclassed", "should be deleted");
        return 0;
    }

    HJets GranulatedJets(const HJets &NewEFlowJets);

    HJets GetJets(hanalysis::HEvent &Event, hanalysis::HJetTag &JetTag);

    HJets GetJets(hanalysis::HEvent &Event);

    HJets GetSubJets(const fastjet::PseudoJet &Jet, const int SubJetNumber);

    fastjet::PseudoJet GetMissingEt(hanalysis::HEvent &Event);

    virtual float ReadBdt(const TClonesArray &, const int) {
        Print(HError, "Read Bdt", "should be subclassed");
        return 0;
    }

    HDetectorGeometry DetectorGeometry;

    void SetTreeBranch(ExRootTreeWriter &tree_writer, const Stage stage) {
        switch (stage) {
        case kTrainer :
            tree_branch_ = tree_writer.NewBranch(tagger_name().c_str(), &Class());
            break;
        case kReader :
            tree_branch_ = tree_writer.NewBranch(reader_name().c_str(), &Class());
            break;
        }
    }

    virtual float Bdt(HEvent &event, const TMVA::Reader &reader) const {
        Print(HError, "Bdt", "should be subclassed");
    }

protected:

    virtual void DefineVariables() = 0;

    virtual inline std::string ClassName() const {
        return "HMva";
    }

    HObservable NewObservable(float &value, const std::string &title) const;

    HObservable NewObservable(float &value, const std::string &title, const std::string &latex) const;

    void AddObservable(float &value, const std::string &title) {
        observables_.push_back(NewObservable(value, title));
    };

    void AddObservable(float &value, const std::string &title, const std::string &latex) {
        observables_.push_back(NewObservable(value, title, latex));
    };

    void AddSpectator(float &value, const std::string &title) {
        spectators_.push_back(NewObservable(value, title));
    };

    void ClearVectors() {
        observables_.clear();
        spectators_.clear();
    }

    int max_combi() {
        return max_combi_;
    }

    virtual TClass &Class() const {
        return *HBranch::Class();
    }

    ExRootTreeBranch &TreeBranch() {
        return *tree_branch_;
    }

    float Bdt(const TMVA::Reader &reader);

//     HReader &reader(){
//       return reader_;
//     }

private:

    ExRootTreeBranch *tree_branch_;


    /**
     * @brief Name of the Analysis
     *
     */
    std::string analysis_name_;

    /**
     * @brief Name of the Analysis
     *
     */
    std::string tagger_name_;

    /**
     * @brief Name of the Signal File
     *
     */
    HStrings signal_names_;

    /**
     * @brief Name of the Test File
     *
     */
//     std::string test_name_;

    std::string cut_method_name_;

    std::string bdt_method_name_;

//     std::string branch_name_;

//     std::string SpectatorBranchName;

    std::string weight_branch_name_;

//     std::string background_name_;

//     std::string signal_name_;

    TCut cut_;

    /**
     * @brief Names of the Background Files
     *
     */
    HStrings background_names_;

    HStrings background_tree_names_;

    HStrings signal_tree_names_;

    std::vector<HObservable> observables_;

    std::vector<HObservable> spectators_;

    int max_combi_;

//     HReader reader_;

};
