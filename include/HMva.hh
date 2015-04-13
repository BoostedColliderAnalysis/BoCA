# ifndef HMva_hh
# define HMva_hh

# include "TObjArray.h"
# include "TClonesArray.h"
# include "TCut.h"

# include "TMVA/Reader.h"

# include "ExRootAnalysis/ExRootTreeReader.h"
# include "ExRootAnalysis/ExRootTreeWriter.h"
# include "ExRootAnalysis/ExRootTreeBranch.h"

# include "HBranch.hh"
# include "HObject.hh"
# include "HJetInfo.hh"
# include "HEvent.hh"
# include "HJetDelphes.hh"
# include "Predicate.hh"
# include "HAnalysis.hh"

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

    void SetTreeNames(const HStrings &NewTreeNames) {
        SignalTreeNames = NewTreeNames;
        BackgroundTreeNames = NewTreeNames;
    }

    void SetSignalTreeNames(const HStrings &NewSignalTreeNames) {
        SignalTreeNames = NewSignalTreeNames;
    }

    void SetBackgroundTreeNames(const HStrings &NewBackgroundTreeNames) {
        BackgroundTreeNames = NewBackgroundTreeNames;
    }

    void SetInputTreeNames(const HStrings &NewSignalTreeNames, const HStrings &NewBackgroundTreeNames) {
        SignalTreeNames = NewSignalTreeNames;
        BackgroundTreeNames = NewBackgroundTreeNames;
    }

    void SetBranchName(const std::string &NewBranchName) {
        EventBranchName = NewBranchName;
    }

    std::string GetBranchName() const {
        return EventBranchName;
    }

    void SetTaggerName(const std::string &NewTaggerName) {
        TaggerName = NewTaggerName;
        EventBranchName = NewTaggerName;
        SignalName = NewTaggerName;
        SignalNames = {NewTaggerName};
        BackgroundName = "Not" + NewTaggerName;
        BackgroundNames = {BackgroundName};
        TestName = NewTaggerName;
    }

    std::string GetTaggerName() const {
        return TaggerName;
    }

    std::string ReaderName() const {
        const std::string Name = TaggerName + "Reader";
        return Name;
    }

    std::string GetAnalysisName() const {
        return AnalysisName;
    }

    std::vector<HObservable> observables() const {
        return observables_;
    }

    std::vector<HObservable> spectators() const {
        return spectators_;
    }


    HStrings GetSignalNames() const {
        return SignalNames;
    }

    HStrings GetSignalTreeNames() const {
        return SignalTreeNames;
    }

    HStrings GetBackgroundNames() const {
        return BackgroundNames;
    }

    HStrings GetBackgroundTreeNames() const {
        return BackgroundTreeNames;
    }

    std::string GetTestName() const {
        return TestName;
    }

//     HStrings GetTestTreeNames() const {
//         return TestTreeNames;
//     }


    TCut GetCut() const {
        return Cut;
    }

    void SetAnalysisName(const std::string &NewAnalysisName) {
        AnalysisName = NewAnalysisName;
    }

//     void SetTestTreeNames(const HStrings &NewTestTreeNames) {
//         TestTreeNames = NewTestTreeNames;
//     }

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
        return BackgroundName;
    }

    std::string GetSignalName() const {
        return SignalName;
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

//     HJets RemoveIfWrongAbsFamily(const HJets &jets, const int particle_id, int mother_id);
//
//     HJets RemoveIfWrongFamily(const HJets &jets, const int particle_id, int mother_id);
//
//     HJets RemoveIfWrongAbsStepFamily(const HJets &NewJets, const int ParticleId , const int Mother2Id);
//
//     HJets RemoveIfWrongAbsStepMother(const HJets &jets, const int mother_2_id);
//
//     HJets RemoveIfWrongParticle(const HJets &NewJets, const int ParticleId);
//
//     HJets RemoveIfWrongAbsParticle(const HJets &NewJets, const int ParticleId);
//
//     HJets RemoveIfWrongAbsMother(const HJets &NewJets, const int MotherId);
//
//     HJets RemoveIfAbsMother(const HJets &NewJets, const int MotherId);

protected:

//     HJets RemoveIfLetpons(HJets &Jets);
//
//     HJets RemoveIfQuark(HJets &Jets);

//     template<typename TMultiplet>
//     inline std::vector<TMultiplet> SortByDeltaRTo(std::vector<TMultiplet> &Multiplets, fastjet::PseudoJet Jet) {
//         std::sort(Multiplets.begin(), Multiplets.end(), MinDeltaR(Jet));
//         return Multiplets;
//     }
//
//     template <class HMultiplet>
//     inline std::vector<HMultiplet> SortByMaxDeltaRap(std::vector<HMultiplet> &Multiplets) {
//         std::sort(Multiplets.begin(), Multiplets.end(), MaxDeltaRap());
//         return Multiplets;
//     }
//
//     template <class HMultiplet>
//     inline std::vector<HMultiplet> SortByMassTo(std::vector<HMultiplet> &Multiplets, const float Mass) {
//         std::sort(Multiplets.begin(), Multiplets.end(), SortByMass(Mass));
//         return Multiplets;
//     }


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
    std::string AnalysisName;

    /**
     * @brief Name of the Analysis
     *
     */
    std::string TaggerName;

    /**
     * @brief Name of the Signal File
     *
     */
    HStrings SignalNames;

    /**
     * @brief Name of the Test File
     *
     */
    std::string TestName;

    std::string CutMethodName;

    std::string bdt_method_name;

    std::string EventBranchName;

    std::string SpectatorBranchName;

    std::string WeightBranchName;

    std::string BackgroundName;

    std::string SignalName;

    TCut Cut;

    /**
     * @brief Names of the Background Files
     *
     */
    HStrings BackgroundNames;

    HStrings BackgroundTreeNames;

    HStrings SignalTreeNames;

//     HStrings TestTreeNames;

    std::vector<HObservable> observables_;

    std::vector<HObservable> spectators_;

    int max_combi_;

};

# endif
