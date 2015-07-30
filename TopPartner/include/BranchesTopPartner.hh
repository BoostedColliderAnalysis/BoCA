#pragma once

#include "../../include/Branches.hh"

namespace analysis {

namespace toppartner {

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class TopPartnerBranch : public MultiBranch {

public:

    template<typename Multiplet>
    void Fill(const Multiplet& multiplet)
    {
        MultiBranch::Fill(multiplet);
    }

private:

    ClassDef(TopPartnerBranch, 1)

};

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class HiggsPairBranch : public MultiBranch {

public:

    template<typename Multiplet>
    void Fill(const Multiplet& multiplet)
    {
        MultiBranch::Fill(multiplet);
    }

private:

    ClassDef(HiggsPairBranch, 1)

};

class SignatureBranch : public MultiBranch {

public:

    template<typename Multiplet>
    void Fill(const Multiplet& multiplet)
    {
        MultiBranch::Fill(multiplet);
    }

private:

    ClassDef(SignatureBranch, 1)

};

class EventBranch : public analysis::EventBranch {

public:
    template<typename Multiplet>
    void Fill(const Multiplet& multiplet)
    {
        analysis::EventBranch::Fill(multiplet);
    }
    Observables Variables() const;
    Observables Spectators() const;

private:

    ClassDef(EventBranch, 1)

};

}

}
