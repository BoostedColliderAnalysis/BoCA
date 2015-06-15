# pragma once

# include "../../include/Branches.hh"

namespace toppartner {

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class TopPartnerBranch : public analysis::MultiBranch
{

public:

    TopPartnerBranch();

    template<typename Multiplet>
    void Fill(const Multiplet &multiplet) {
        analysis::MultiBranch::Fill(multiplet);
    }

private:

    ClassDef(TopPartnerBranch, 1)

};

/**
 *
 * @brief Higgs cpv tagger root tree structure
 *
 */
class HiggsPairBranch : public analysis::MultiBranch
{

public:

  HiggsPairBranch();

  template<typename Multiplet>
  void Fill(const Multiplet &multiplet) {
    analysis::MultiBranch::Fill(multiplet);
  }

private:

  ClassDef(HiggsPairBranch, 1)

};

class SignatureBranch : public analysis::MultiBranch
{

public:

  SignatureBranch();

  template<typename Multiplet>
  void Fill(const Multiplet &multiplet) {
    analysis::MultiBranch::Fill(multiplet);
  }

private:

  ClassDef(SignatureBranch, 1)

};

class EventBranch : public analysis::EventBranch
{

public:
  
  EventBranch();

  template<typename Multiplet>
  void Fill(const Multiplet &multiplet) {
    analysis::EventBranch::Fill(multiplet);
  }

private:

  ClassDef(EventBranch, 1)

};

}
