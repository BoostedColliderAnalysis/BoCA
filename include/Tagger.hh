# pragma once

# include "TCut.h"
# include "TClonesArray.h"

# include "TMVA/Reader.h"

# include "ExRootAnalysis/ExRootTreeBranch.h"
# include "ExRootAnalysis/ExRootTreeWriter.h"

# include "Branches.hh"
# include "Predicate.hh"
# include "Event.hh"
# include "Doublet.hh"

namespace analysis {

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


class PreCuts : public analysis::Object
{
public:
    void SetPtLowerCut(const HParticleId particle_id, const float value) {
        pt_lower_cut_[particle_id] = value;
    }

    float PtLowerCut(const HParticleId particle_id) {
        return pt_lower_cut_[particle_id];
    }

    void SetPtUpperCut(const HParticleId particle_id, const float value) {
        pt_upper_cut_[particle_id] = value;
    }

    float PtUpperCut(const HParticleId particle_id) {
        return pt_upper_cut_[particle_id];
    }

    void SetTrackerMaxEta(const HParticleId particle_id, const float value) {
        tracker_eta_upper_cut_[particle_id] = value;
    }

    float TrackerMaxEta(const HParticleId particle_id) {
        return tracker_eta_upper_cut_[particle_id];
    }

private:
    std::map<HParticleId, float> pt_lower_cut_;
    std::map<HParticleId, float> pt_upper_cut_;
    std::map<HParticleId, float> tracker_eta_upper_cut_;
};


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

    std::string factory_name() const {
        return "Mva" + tagger_name();
    }

    std::string signal_file_name(const Stage stage) const {
        const std::string file_name = analysis_name() + "/" + signal_name();
        switch (stage) {
        case kTrainer :
            return file_name;
        case kReader :
            return file_name + "Reader.root";
        }
    }

    std::string background_file_name(const Stage stage) const {
        const std::string file_name = analysis_name() + "/" + background_name();
        switch (stage) {
        case kTrainer :
            return file_name;
        case kReader :
            return file_name + "Reader.root";
        }
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

    void clear_tree_names() {
        signal_tree_names_.clear();
        background_tree_names_.clear();
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

    virtual int GetBdt(Event &, PreCuts &, const TMVA::Reader &) {
        Print(kError, "Get Bdt", "should be subclassed");
        return 0;
    }

    virtual int Train(analysis::Event &, PreCuts &, const Tag) {
        Print(kError, "Train", "Should be subclassed");
        return 0;
    }

    virtual float GetBranches(analysis::Event &, Stage , const Tag) {
        Print(kError, "get branches", "Should be subclassed", "should be deleted");
        return 0;
    }

    Jets GranulatedJets(const Jets &) {
        Print(kError, "get jets", "depreciated");
        return Jets {};
    }

    Jets GetJets(analysis::Event &, analysis::HJetTag &) {
        Print(kError, "get jets", "depreciated");
        return Jets {};
    }

    Jets GetJets(analysis::Event &) {
        Print(kError, "get jets", "depreciated");
        return Jets {};
    }

    Jets GetSubJets(const fastjet::PseudoJet &jet, const int sub_jet_number);

    fastjet::PseudoJet GetMissingEt(analysis::Event &event);

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

    virtual float Bdt(Event &, const TMVA::Reader &) const {
        Print(kError, "Bdt", "should be subclassed");
        return 0;
    }

protected:

    virtual void DefineVariables() = 0;

    virtual inline std::string ClassName() const {
        return "Tagger";
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

    template<typename Multiplet>
    std::vector<Multiplet> ReduceResult(std::vector<Multiplet> multiplet) {
        if (multiplet.empty()) return multiplet;
        std::sort(multiplet.begin(), multiplet.end());
        multiplet.erase(multiplet.begin() + std::min(max_combi(), int(multiplet.size())), multiplet.end());
        return multiplet;
    }

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
