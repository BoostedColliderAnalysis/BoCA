# ifndef HJetPairTagger_hh
# define HJetPairTagger_hh

# include "HBottomTagger.hh"
# include "HDoublet.hh"


class HJetPairTag : public hanalysis::HJetTag
{

public:
  virtual int GetBranchId(const int ParticleId, int BranchId){

    Print(HDebug, "Get Branch Id", GetParticleName(ParticleId), GetParticleName(BranchId));

    if (
      HeavyParticles.find(static_cast<HParticleId>(std::abs(ParticleId))) != end(HeavyParticles)
    ) {
      BranchId = ParticleId;
    } else if (
      RadiationParticles.find(static_cast<HParticleId>(std::abs(ParticleId))) != end(RadiationParticles)
    ) {
      BranchId = IsrId;
    }

    Print(HDebug, "Branch Id", GetParticleName(BranchId));

    return BranchId;

  }

protected:

  virtual inline std::string ClassName() const {
    return "HJetPairTag";
  }

};

/**
 * @brief JetPair BDT tagger
 *
 */
class hanalysis::HJetPairTagger : public HMva
{

public:

  HJetPairTagger(HBottomTagger *NewBottomTagger);

  ~HJetPairTagger();

    void FillBranch(const HDoublet &Pair);

    std::vector< HWBranch * > GetBranches(HEvent *const Event, const HObject::HTag Tag);

    std::vector<HParticleBranch *> GetConstituentBranches();

    std::vector<HDoublet> GetBdt(HJets &Jets, const hanalysis::HReader *const WReader);

protected:

    virtual inline std::string ClassName() const {
      return "HJetPairTagger";
    }

private:

    void DefineVariables();

    void FillBranch(HWBranch *const WBranch, const HDoublet &Doublet);

    void FillBranch(const HKinematics &Vector);

    void FillBranch(HParticleBranch *const ConstituentBranch, const HKinematics &Vector);

    hanalysis::HObject::HTag GetTag(const HDoublet &Doublet);

    HBottomTagger *BottomTagger;

    HReader *BottomReader;

    HWBranch *Branch;

    HJetPairTag *JetTag;

};

#endif
