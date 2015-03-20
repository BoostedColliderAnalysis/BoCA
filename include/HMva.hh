# ifndef HMva_hh
# define HMva_hh

# include "TObjArray.h"
# include "TClonesArray.h"
# include "TCut.h"

# include "TMVA/Reader.h"

# include "ExRootAnalysis/ExRootTreeReader.h"
# include "ExRootAnalysis/ExRootTreeWriter.h"
# include "ExRootAnalysis/ExRootTreeBranch.h"

# include "fastjet/JetDefinition.hh"

# include "HBranch.hh"
# include "HObject.hh"
# include "HJetInfo.hh"
# include "HEvent.hh"

struct SortByMass {
    SortByMass(const float NewMass) {
        Mass = NewMass;
    }
    template <typename TMultiplet>
    inline bool operator()(const TMultiplet &Multiplet1, const TMultiplet &Multiplet2) {
        if (Multiplet1.Jet().m() != Multiplet2.Jet().m()) return std::abs(Multiplet1.Jet().m() - Mass) < std::abs(Multiplet2.Jet().m() - Mass);
        else return Multiplet1.Bdt() > Multiplet2.Bdt();
    }
    float Mass;
};

struct MinDeltaR {
    MinDeltaR(const fastjet::PseudoJet &NewParticle) {
        Particle = NewParticle;
    }
    template <typename TMultiplet>
    inline bool operator()(const TMultiplet &Multiplet1, const TMultiplet &Multiplet2) {
        return Multiplet1.Jet().delta_R(Particle)  < Multiplet2.Jet().delta_R(Particle);
    }
    inline bool operator()(const fastjet::PseudoJet &Jet1, const fastjet::PseudoJet &Jet2) {
        return Jet1.delta_R(Particle)  < Jet2.delta_R(Particle);
    }
    fastjet::PseudoJet Particle;
};

struct MaxDeltaRap {
    template <typename TMultiplet>
    inline bool operator()(const TMultiplet &Multiplet1, const TMultiplet &Multiplet2) {
        return (Multiplet1.DeltaRap() > Multiplet2.DeltaRap());
    }
};


struct WrongId {
    WrongId(const int NewId) {
        Id = NewId;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        hanalysis::HJetInfo JetInfo = Jet.user_info<hanalysis::HJetInfo>();
        hanalysis::HFamily Family = JetInfo.Constituents().front().Family();
        return (Family.ParticleId != Id);
    }
    int Id;
};

struct WrongAbsId {
    WrongAbsId(const int NewId) {
        Id = NewId;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        hanalysis::HJetInfo JetInfo = Jet.user_info<hanalysis::HJetInfo>();
        hanalysis::HFamily Family = JetInfo.Constituents().front().Family();
        return (std::abs(Family.ParticleId) != Id);
    }
    int Id;
};

struct WrongAbsFamily {
    WrongAbsFamily(const int NewId, const int NewMother) {
        Id = NewId;
        Mother = NewMother;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        hanalysis::HJetInfo JetInfo = Jet.user_info<hanalysis::HJetInfo>();
        hanalysis::HFamily Family = JetInfo.Constituents().front().Family();
        return (std::abs(Family.ParticleId) != Id || std::abs(Family.Mother1Id) != Mother);
    }
    int Id;
    int Mother;
};

struct WrongFamily {
    WrongFamily(const int NewId, const int NewMother) {
        Id = NewId;
        Mother = NewMother;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        hanalysis::HJetInfo JetInfo = Jet.user_info<hanalysis::HJetInfo>();
        hanalysis::HFamily Family = JetInfo.Constituents().front().Family();
        return (Family.ParticleId != Id || Family.Mother1Id != Mother);
    }
    int Id;
    int Mother;
};

struct WrongMother {
    WrongMother(const int NewMother) {
        Mother = NewMother;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        hanalysis::HJetInfo JetInfo = Jet.user_info<hanalysis::HJetInfo>();
        hanalysis::HFamily Family = JetInfo.Constituents().front().Family();
        return Family.Mother1Id != Mother;
    }
    int Mother;
};

struct WrongAbsMother {
    WrongAbsMother(const int NewMother) {
        Mother = NewMother;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        hanalysis::HJetInfo JetInfo = Jet.user_info<hanalysis::HJetInfo>();
        hanalysis::HFamily Family = JetInfo.Constituents().front().Family();
        return std::abs(Family.Mother1Id) != Mother;
    }
    int Mother;
};

struct WrongAbsStepFamily {
    WrongAbsStepFamily(const int NewParticleId, const int NewMother2) {
        Mother2 = NewMother2;
        ParticleId = NewParticleId;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        hanalysis::HJetInfo JetInfo = Jet.user_info<hanalysis::HJetInfo>();
        hanalysis::HFamily Family = JetInfo.Constituents().front().Family();
        return (std::abs(Family.ParticleId) != ParticleId || std::abs(Family.Mother2Id) != Mother2);
    }
    int Mother2;
    int ParticleId;
};

struct WrongAbsStepMother {
    WrongAbsStepMother(const int NewMother2) {
        Mother2 = NewMother2;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        hanalysis::HJetInfo JetInfo = Jet.user_info<hanalysis::HJetInfo>();
        hanalysis::HFamily Family = JetInfo.Constituents().front().Family();
        return std::abs(Family.Mother2Id) != Mother2;
    }
    int Mother2;
};

struct WrongLeptons {
    bool operator()(const fastjet::PseudoJet &Jet) {
        hanalysis::HJetInfo JetInfo = Jet.user_info<hanalysis::HJetInfo>();
        hanalysis::HFamily Family = JetInfo.Constituents().front().Family();
        return (std::abs(Family.ParticleId) == Family.ElectronId ||
                std::abs(Family.ParticleId) == Family.MuonId ||
                std::abs(Family.ParticleId) == Family.TauId ||
                std::abs(Family.ParticleId) == Family.TauNeutrinoId ||
                std::abs(Family.ParticleId) == Family.MuonNeutrinoId ||
                std::abs(Family.ParticleId) == Family.ElectronNeutrinoId
               );
    }
};

struct WrongQuark {
  bool operator()(const fastjet::PseudoJet &Jet) {
    hanalysis::HJetInfo JetInfo = Jet.user_info<hanalysis::HJetInfo>();
    hanalysis::HFamily Family = JetInfo.Constituents().front().Family();
    return (std::abs(Family.ParticleId) == Family.UpId ||
    std::abs(Family.ParticleId) == Family.DownId ||
    std::abs(Family.ParticleId) == Family.CharmId ||
    std::abs(Family.ParticleId) == Family.StrangeId ||
    std::abs(Family.ParticleId) == Family.BottomId ||
    std::abs(Family.ParticleId) == Family.TopId
    );
  }
};

struct LargeDistance {
    LargeDistance(const fastjet::PseudoJet NewJet, const float NewDistance) {
        JetM = NewJet;
        Distance = NewDistance;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        return (JetM.delta_R(Jet) > Distance);
    }
    fastjet::PseudoJet JetM;
    float Distance;
};

struct SmallDistance {
    SmallDistance(const fastjet::PseudoJet NewJet, const float NewDistance) {
        JetM = NewJet;
        Distance = NewDistance;
    }
    bool operator()(const fastjet::PseudoJet &Jet) {
        return (JetM.delta_R(Jet) < Distance);
    }
    fastjet::PseudoJet JetM;
    float Distance;
};

class HDetectorGeometry
{
public:
    enum HDetectorType {CMS, Spp};

    HDetectorGeometry(const HDetectorType DetectorType) {
        switch (DetectorType) {
        case CMS :
            JetMinPt = 20;
            JetConeSize = 0.5;
            MinCellResolution = .1;
            MinCellPt = .5;
            TrackerEtaMax = 2.5;
            JetDefinition = fastjet::JetDefinition(fastjet::kt_algorithm, 1);
        case Spp:
            JetMinPt = 40;
            JetConeSize = 0.5;
            MinCellResolution = .1;
            MinCellPt = .5;
            TrackerEtaMax = 5;
            JetDefinition = fastjet::JetDefinition(fastjet::kt_algorithm, 1);
        }
    }
    float JetMinPt;
    float JetConeSize;
    float MinCellPt;
    float MinCellResolution;
    float TrackerEtaMax;
    float JetRadiusParameter;
    fastjet::JetDefinition JetDefinition;
};

class HObservable //: public hanalysis::HObject
{

public:

    HObservable() {};

    HObservable(float *const NewValue, const std::string &NewExpression, const std::string &NewTitle, const std::string &NewUnit, const std::string &NewLatex) {

//         Print(HDebug, "Float Constructor", *NewValue);

        Value = NewValue;
        Expression = NewExpression;
        Title = NewTitle;
        Unit = NewUnit;
        Latex = NewLatex;
        Type = 'F';
    }



    HObservable(int *const NewValue, const std::string &NewExpression, const std::string &NewTitle, const std::string &NewUnit, const std::string &NewLatex) {

//         Print(HInformation, "Int Constructor", *NewValue);

        Value = (float *)NewValue;
        Expression = NewExpression;
        Title = NewTitle;
        Unit = NewUnit;
        Latex = NewLatex;
        Type = 'I';

    }

//     HObservable(const float NewValue, const std::string &NewExpression, const std::string &NewTitle, const std::string &NewUnit, const std::string &NewLatex) {
//
//       //         Print(HDebug, "Float Constructor", *NewValue);
//
//       Value = NewValue;
//       Expression = NewExpression;
//       Title = NewTitle;
//       Unit = NewUnit;
//       Latex = NewLatex;
//       Type = 'F';
//     }
//
//
//
//     HObservable(const int NewValue, const std::string &NewExpression, const std::string &NewTitle, const std::string &NewUnit, const std::string &NewLatex) {
//
//       //         Print(HInformation, "Int Constructor", *NewValue);
//
//       Value = (float)NewValue;
//       Expression = NewExpression;
//       Title = NewTitle;
//       Unit = NewUnit;
//       Latex = NewLatex;
//       Type = 'I';
//
//     }

    float *GetValue() {
        return Value;
    }

//     void SetValue(const float *NewValue);

//     void SetValue(const int *NewValue);

    std::string Expression;

    std::string Title;

    std::string Unit;

    char Type;

    std::string Latex;

private:

    float *Value;

    inline std::string ClassName() const {
        return "HObservable";
    }

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

//     HMva(const HMva &NewMva);

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

    std::vector<HObservable> GetObservables() const {
        return Observables;
    }

    void SetObservables(const std::vector<HObservable> &NewObservables) {
        Observables = NewObservables;
    }

    std::vector<HObservable> GetSpectators() const {
        return Spectators;
    }

    void SetSpectators(const std::vector<HObservable> &NewSpectators) {
        Spectators = NewSpectators;
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

    HStrings GetTestTreeNames() const {
        return TestTreeNames;
    }


//     float GetSignalEfficiency() const {
//         return SignalEfficiency;
//     }

//     float GetLuminosity() const {
//         return Luminosity;
//     }

    TCut GetCut() const {
        return Cut;
    }

    void SetAnalysisName(const std::string &NewAnalysisName) {
        AnalysisName = NewAnalysisName;
    }

    void SetTestTreeNames(const HStrings &NewTestTreeNames) {
        TestTreeNames = NewTestTreeNames;
    }

    std::string GetCutMethodName()const {
        return CutMethodName;
    }

    std::string GetBdtMethodName()const {
        return BdtMethodName;
    }

    std::string GetWeightBranchName()const {
        return WeightBranchName;
    }

//     bool LaTeX()const {
//         return DoLatex;
//     }

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

    virtual float ReadBdt(const TClonesArray &, const int) {
        Print(HError, "Read Bdt", "should be subclassed");
        float Bdt = 0;
        return Bdt;
    }

    HDetectorGeometry DetectorGeometry;

    inline HJets RemoveIfWrongAbsFamily(const HJets &NewJets, const int ParticleId, int MotherId) {
        HJets Jets = NewJets;
        Jets.erase(std::remove_if(Jets.begin(), Jets.end(), WrongAbsFamily(ParticleId, MotherId)), Jets.end());
        return Jets;
    }

    inline HJets RemoveIfWrongFamily(const HJets &NewJets, const int ParticleId, int MotherId) {
        HJets Jets = NewJets;
        Jets.erase(std::remove_if(Jets.begin(), Jets.end(), WrongFamily(ParticleId, MotherId)), Jets.end());
        return Jets;
    }

    inline HJets RemoveIfWrongAbsStepFamily(const HJets &NewJets, const int ParticleId , const int Mother2Id) {
        HJets Jets = NewJets;
        Jets.erase(std::remove_if(Jets.begin(), Jets.end(), WrongAbsStepFamily(ParticleId, Mother2Id)), Jets.end());
        return Jets;
    }

    inline HJets RemoveIfWrongAbsStepMother(const HJets &NewJets, const int Mother2Id) {
        HJets Jets = NewJets;
        Jets.erase(std::remove_if(Jets.begin(), Jets.end(), WrongAbsStepMother(Mother2Id)), Jets.end());
        return Jets;
    }

    inline HJets RemoveIfWrongParticle(const HJets &NewJets, const int ParticleId) {
        HJets Jets = NewJets;
        Jets.erase(std::remove_if(Jets.begin(), Jets.end(), WrongId(ParticleId)), Jets.end());
        return Jets;
    }

    inline HJets RemoveIfWrongAbsParticle(const HJets &NewJets, const int ParticleId) {
        HJets Jets = NewJets;
        Jets.erase(std::remove_if(Jets.begin(), Jets.end(), WrongAbsId(ParticleId)), Jets.end());
        return Jets;
    }

    inline HJets RemoveIfWrongAbsMother(const HJets &NewJets, const int MotherId) {
        HJets Jets = NewJets;
        Jets.erase(std::remove_if(Jets.begin(), Jets.end(), WrongAbsMother(MotherId)), Jets.end());
        return Jets;
    }

protected:

    ExRootTreeBranch *TreeBranch;


    inline HJets RemoveIfLetpons(HJets &Jets) {
        Jets.erase(std::remove_if(Jets.begin(), Jets.end(), WrongLeptons()), Jets.end());
        return Jets;
    }

    inline HJets RemoveIfQuark(HJets &Jets) {
      Jets.erase(std::remove_if(Jets.begin(), Jets.end(), WrongQuark()), Jets.end());
      return Jets;
    }



    template<typename TMultiplet>
    inline std::vector<TMultiplet> SortByDeltaRTo(std::vector<TMultiplet> &Multiplets, fastjet::PseudoJet Jet) {
        std::sort(Multiplets.begin(), Multiplets.end(), MinDeltaR(Jet));
        return Multiplets;
    }

    template <class HMultiplet>
    inline std::vector<HMultiplet> SortByMaxDeltaRap(std::vector<HMultiplet> &Multiplets) {
        std::sort(Multiplets.begin(), Multiplets.end(), MaxDeltaRap());
        return Multiplets;
    }

    template <class HMultiplet>
    inline std::vector<HMultiplet> SortByMassTo(std::vector<HMultiplet> &Multiplets, const float Mass) {
        std::sort(Multiplets.begin(), Multiplets.end(), SortByMass(Mass));
        return Multiplets;
    }


    virtual void DefineVariables() = 0;

    virtual inline std::string ClassName() const {
        return "HMva";
    }

    template<typename TValue>
    HObservable NewObservable(TValue *const Value, const std::string &Title) const {

        Print(HDebug, "New Observable", *Value);
        const std::string Expression = EventBranchName + "." + Title;
        HObservable Observable(Value, Expression, Title, "", "");
        return Observable;

    }

    template<typename TValue>
    HObservable NewObservable(TValue *const Value, const std::string &Title, const std::string &Latex) const {

        Print(HDebug, "New Observable", *Value);
        const std::string Expression = EventBranchName + "." + Title;
        HObservable Observable(Value, Expression, Title, "", Latex);
        return Observable;

    }

//     template<typename TValue>
//     HObservable NewObservable(const TValue Value, const std::string &Title) const {
//
//         Print(HDebug, "New Observable", Value);
//         const std::string Expression = EventBranchName + "." + Title;
//         HObservable Observable(Value, Expression, Title, "", "");
//         return Observable;
//
//     }
//
//     template<typename TValue>
//     HObservable NewObservable(const TValue Value, const std::string &Title, const std::string &Latex) const {
//
//         Print(HDebug, "New Observable", *Value);
//         const std::string Expression = EventBranchName + "." + Title;
//         HObservable Observable(Value, Expression, Title, "", Latex);
//         return Observable;
//
//     }



//     bool DoLatex;

//     int Luminosity;

//     float SignalEfficiency;

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

    std::string BdtMethodName;

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

    HStrings TestTreeNames;

    /**
     * @brief Vector containing the pointer to the Observable data
     *
     */
    std::vector<HObservable> Observables;

    std::vector<HObservable> Spectators;

    int MaxCombi;

//     float MinCellResolution;

private:

};

# endif
