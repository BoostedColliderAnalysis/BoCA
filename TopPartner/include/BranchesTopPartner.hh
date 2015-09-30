#pragma once

#include "../../include/Branches.hh"

namespace boca
{

namespace naturalness
{

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class TopPartnerBranch : public MultiBranch
{
public:
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
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
class HiggsPairBranch : public MultiBranch
{
public:
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        MultiBranch::Fill(multiplet);
    }
private:
    ClassDef(HiggsPairBranch, 1)
};

class SignatureBranch : public MultiBranch
{
public:
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        MultiBranch::Fill(multiplet);
    }
private:
    ClassDef(SignatureBranch, 1)
};

class SignatureSingleBranch : public TChannelBranch
{
public:
    float VetoBdt;
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        TChannelBranch::Fill(multiplet);
        VetoBdt = multiplet.VetoBdt();
    }
    Observables Variables();
private:
    ClassDef(SignatureSingleBranch, 1)
};

class EventBranch : public boca::EventBranch
{
public:
    template<typename Multiplet>
    void Fill(Multiplet const& multiplet) {
        boca::EventBranch::Fill(multiplet);
    }
    Observables Variables();
private:
    ClassDef(EventBranch, 1)
};

}

}
