# pragma once

# include "Triplet.hh"

namespace analysis{

class Quartet31 : public Multiplet<analysis::Triplet,analysis::Singlet>
{

public:

  using Multiplet<analysis::Triplet,analysis::Singlet>::Multiplet;

    analysis::Triplet & Triplet() const;

    fastjet::PseudoJet SingletJet() const;

    analysis::Singlet & Singlet() const;

protected:

    virtual  std::string ClassName() const {
        return "Quartet31";
    }

private:

};

}
