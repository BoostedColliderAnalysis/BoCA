# pragma once

# include "TCut.h"

# include "TMVA/Reader.h"

# include "ExRootAnalysis/ExRootTreeBranch.h"

# include "HBranch.hh"
# include "HJetDelphes.hh"
# include "Predicate.hh"

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
class hanalysis::HMva : public HObject
{

public:

    /**
    * @brief Constructor
    *
    */
    HMva();

    void SetTreeNames(const HStrings &tree_names) {
        signal_tree_names_ = tree_names;
        background_tree_names_ = tree_names;
    }

    void SetSignalTreeNames(const HStrings &signal_tree_names) {
      signal_tree_names_ = signal_tree_names;
    }

    void SetBackgroundTreeNames(const HStrings &background_tree_names) {
        background_tree_names_ = background_tree_names;
    }

    void SetInputTreeNames(const HStrings &signal_tree_names, const HStrings &background_tree_names) {
        signal_tree_names_ = signal_tree_names;
        background_tree_names_ = background_tree_names;
    }

    void SetBranchName(const std::string &branch_name) {
        branch_name_ = branch_name;
    }

    std::string GetBranchName() const {
        return branch_name_;
    }

    void SetTaggerName(const std::string &tagger_name) {
        tagger_name_ = tagger_name;
        branch_name_ = tagger_name;
        signal_name_ = tagger_name;
        signal_names_ = {tagger_name};
        background_name_ = "Not" + tagger_name;
        background_names_ = {background_name_};
        TestName = tagger_name;
    }

    std::string tagger_name() const {
        return tagger_name_;
    }

    std::string reader_name() const {
        return tagger_name_ + "Reader";
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

    std::string GetTestName() const {
        return TestName;
    }

    TCut GetCut() const {
        return Cut;
    }

    void SetAnalysisName(const std::string &analysis_name) {
      analysis_name_ = analysis_name;
    }

    std::string GetCutMethodName()const {
        return CutMethodName;
    }

    std::string BdtMethodName()const {
        return bdt_method_name;
    }

    std::string GetWeightBranchName()const {
        return WeightBranchName;
    }

    std::string GetBackgroundName() const {
        return background_name_;
    }

    std::string GetSignalName() const {
        return signal_name_;
    }

    virtual float GetBdt(TObject *Branch, const TMVA::Reader &Reader);

    HJets GranulatedJets(const HJets &NewEFlowJets);

    HJets GetJets(hanalysis::HEvent &Event, hanalysis::HJetTag &JetTag);

    HJets GetJets(hanalysis::HEvent &Event);

    HJets GetSubJets(const fastjet::PseudoJet &Jet, const int SubJetNumber);

    fastjet::PseudoJet GetMissingEt(hanalysis::HEvent &Event);

    virtual float ReadBdt(const TClonesArray &, const int) {
        Print(HError, "Read Bdt", "should be subclassed");
        float Bdt = 0;
        return Bdt;
    }

    HDetectorGeometry DetectorGeometry;

protected:

    virtual void DefineVariables() = 0;

    virtual inline std::string ClassName() const {
        return "HMva";
    }

    HObservable NewObservable(float &Value, const std::string &Title) const;

    HObservable NewObservable(float &Value, const std::string &Title, const std::string &Latex) const;

    void AddObservable(float &Value, const std::string &Title) {
        observables_.push_back(NewObservable(Value, Title));
    };

    void AddObservable(float &Value, const std::string &Title, const std::string &Latex) {
        observables_.push_back(NewObservable(Value, Title, Latex));
    };

    void AddSpectator(float &Value, const std::string &Title) {
        spectators_.push_back(NewObservable(Value, Title));
    };

    void ClearVectors() {
        observables_.clear();
        spectators_.clear();
    }

    int max_combi() {
        return max_combi_;
    }

//     void SetTreeBranch(ExRootTreeWriter &NewTreeWriter, TClass &Class, const hanalysis::HAnalysis::HStage Stage) {
//       switch (Stage) {
//         case HAnalysis::HTrainer :
//           TreeBranch = NewTreeWriter.NewBranch(GetTaggerName().c_str(), &Class);
//         case HAnalysis::HReader :
//           TreeBranch = NewTreeWriter.NewBranch(ReaderName().c_str(), &Class);
//       }
//     }

private:

    ExRootTreeBranch *TreeBranch;


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
    std::string TestName;

    std::string CutMethodName;

    std::string bdt_method_name;

    std::string branch_name_;

    std::string SpectatorBranchName;

    std::string WeightBranchName;

    std::string background_name_;

    std::string signal_name_;

    TCut Cut;

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

};
