# pragma once

# include "Tagger.hh"
# include "Branches.hh"
# include "Event.hh"
# include "HJetTag.hh"
# include "Reader.hh"
# include "BottomTagger.hh"
# include "Doublet.hh"

namespace analysis {

/**
 * @brief calculation regarding leptons
 *
 */
class HMvaHiggsTagger : public Tagger
{

public:

    HMvaHiggsTagger();

    HMvaHiggsTagger(const BottomTagger &NewBottomTagger);

    ~HMvaHiggsTagger();

    std::vector< HHiggsBranch * > GetBranches(Event &event, const Object::Tag State);

    std::vector<ParticleBranch *> GetconstituentBranches();

    void FillBranch(const Doublet &Pair);

private:

    BottomTagger bottom_tagger_;

    Reader BottomReader;

    HHiggsBranch Branch;

    HJetTag JetTag;

    void DefineVariables();

    void FillBranch(HHiggsBranch * const HiggsBranch, const Doublet &Pair);

    void FillBranch(const Kinematics &Vector);

    void FillBranch(ParticleBranch *const constituentBranch, const Kinematics &Vector);

    virtual inline std::string ClassName() const {
        return "HMvaHiggsTagger";
    };

};

}
